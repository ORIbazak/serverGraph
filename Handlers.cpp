#include "Header/usings.h"
#include "Header/Server.h"
#include "Header/OutOfClass.h"
#include "flags.h"


int SERVER::CONNECTION::HandleNewValidFUNC(string& str)
{
    try {
        Parser parse = Parser();
        exp = parse.tokenize(str); // Tokenize the input string using the Parser.



        // Checking if the function is a constant function
        if (!hasVariable(str)) // if func doesnt HAVE X
        {
            // handle constFunction:
            is_constant_func = true;
            token t = parse.Solve(exp);
            if (t.token_type == INTEGER_TYPE)
            {
                constant_y = t.type.Ival;
            }
            else
            {
                constant_y = t.type.Fval;
            }
            return SUCCESS_RESPONSE;
        }


        // Handling non-constant function

        parse.GenerateCordinates(exp, x, y, defined);
        more_def = parse.find_boundries(x, y, defined, exp);
        minMaxData = parse.find_min_max(x, y, defined, more_def, exp);

        vector<float> orig_boundries = boolVecToFloatsVec(defined);

        if (size(more_def) > 0)
        {


            boundries = mergeBOUNDRIES(more_def, orig_boundries);
        }
        else
        {
            boundries = orig_boundries;
        }

        if (areYvalsTheSame(y))// All y-values are the same, indicating a constant function.

        {
            is_constant_func = true;
            constant_y = y[0];
        }

        return SUCCESS_RESPONSE;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught in HandleNewValidFUNC: " << e.what() << '\n';
        return ERROR_RESPONSE;
    }
    catch (...)
    {
        std::cerr << "Unknown exception caught in HandleNewValidFUNC.\n";
        return ERROR_RESPONSE;
    }

    



}

int SERVER::CONNECTION::HandleREQUEST(RequestType& type)// main function that takes the request type parsed in HandleConnection and sends desired response or closes connection;
{
    try
    {
        Parser parse = Parser();

        switch (type)
        {
        case(RequestType::reset):
        {

            resetData();
            return sendVerfication();
        }
        case(RequestType::newFunc):
        {
            string func_str = ParseFunc();
            cout << "new FUNC " << func_str << endl;
            int result = HandleNewValidFUNC(func_str);
            return sendVerfication();


        }
        case(RequestType::terminate):
        {

            cout << clientSocket << "CONN TERMINATED" << endl;
            return TERMINATE_RESPONSE;
        }

        case(RequestType::DRAW):
        {
            string MSG;
            cout << "REQUEST TO DRAW" << endl;
            MSG += is_constant_func ? '1' : '0';
            MSG += ';';
            if (is_constant_func)
            {



                MSG = MSG + (std::to_string(constant_y)) + ";"; //addfloat y and ; to represent end of yval
                MSG = AESencrypt(AESkey, MSG);
                send(clientSocket, MSG.c_str(), static_cast<int>(MSG.size()), 0);
                return SUCCESS_RESPONSE;


            }

            else {

                MSG += more_def.size() > 0 ? '1' : '0';
                MSG = AESencrypt(AESkey, MSG);//encrypt via AES
                send(clientSocket, MSG.c_str(), static_cast<int>(MSG.size()), 0);
                SLEEP//sleep to make sure data is acceptted before sending again
                    sendCordinates(more_def.size() > 0);
                return SUCCESS_RESPONSE;

            }
        }

        case(RequestType::boundries): //find boundries, prepare to send via communication protocol nad send to client
        {
            string MSG = convertToDelimitedString(boundries);
            MSG = AESencrypt(AESkey, MSG);

            send(clientSocket, MSG.c_str(), static_cast<int>(MSG.size()), 0);
            return SUCCESS_RESPONSE;

        }





        case(RequestType::MinMax): //get minmax , prepare the string according to communication protocol and send to client
        {
     
            printMinMax(minMaxData);
            string MSG = prepareMinMaxSTR(minMaxData);
            MSG = AESencrypt(AESkey, MSG);

            send(clientSocket, MSG.c_str(), static_cast<int>(MSG.size()), 0);

            return SUCCESS_RESPONSE;

        }
        case (RequestType::intersects):
        {
            

                cout << "RECIEVED REQUEST TO SEND INTERSECTS" << endl;

                string MSG;
                char c;
                    vector<float> intersects = parse.find_x_old(x, y, defined, exp); //find x_intersect
                    addMinMaxToIntersects(minMaxData, intersects);
                     MSG+= std::to_string(size(intersects)>0);
                     c = HAS_X_2_HAS_Y;
                    MSG +=static_cast<char>(c);
                 
                    token t = parse.Solve(parse.assignValue(exp, 0));
                    float y_val = 0;
                    if (t.token_type == INTEGER_TYPE)y_val = t.type.Ival;
                    if (t.token_type == FLOAT_TYPE)y_val = t.type.Fval;
                    bool has_y_intersect = t.token_type != NOT_DEFINED_TYPE;
                    MSG += static_cast<char>(has_y_intersect) + '0';
                    c = Y_BOOL_2_VAL;
                    MSG += static_cast<char>(c);

                    if (has_y_intersect) MSG += convertToStringWithThreeDecimalPlaces(y_val);
                    c = DATA_SWAP;
                    MSG += static_cast<char>(c);
                   
                   if (size(intersects) > 0) MSG += convertToDelimitedString(intersects);
                   c = END_OF_DATA;
                    MSG += static_cast<char>(c);
                    





                    MSG = AESencrypt(AESkey, MSG);
               
                    send(clientSocket, MSG.c_str(), static_cast<int>(MSG.size()), 0);

                    return SUCCESS_RESPONSE;

                }
                
                
                
            

        }
        return ERROR_RESPONSE;


        
    }
    catch (const std::exception& e)//catch exeception and dispaly it 
    {
        std::cerr << "Exception caught in HandleREQUEST: " << e.what() << '\n';

        return ERROR_RESPONSE;
    }
    catch (...)
    {
        std::cerr << "Unknown exception caught in HandleREQUEST.\n";

        return ERROR_RESPONSE;
    }
    
}


