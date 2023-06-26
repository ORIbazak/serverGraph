#include "Header/usings.h""
#include "Header/Server.h"
#include "Header/usings.h"
#include "Header/DataTransfer.h"
#include "Header/Server.h"
#include "Header/Graph.h"
#include "Header/Parse.h"
#include "flags.h"





string convertToStringWithThreeDecimalPlaces(float f) //convert to 3 dots after point
{
    std::ostringstream streamObj;

    // Add Fixed-Point Notation
    streamObj << std::fixed;

    // Set precision to 3
    streamObj << std::setprecision(3);

    // Add float to stream
    streamObj << f;

    // Get string from output string stream
    string strObjRounded = streamObj.str();


    return strObjRounded;
}

string SERVER::CONNECTION::convertToDelimitedString(vector<float>& arr) {
    //convert data via communication protocol: floats with ; between each float, p implies end of string
    string protocoled = "";
    for (int i = 0; i < arr.size(); i++) //go through the arr
    {
        if (arr[i] > Y_MAX || arr[i] < Y_MIN) arr[i] = Y_MAX + 1;//save storage, doesnt matter wont be display anyways

        string rounded = convertToStringWithThreeDecimalPlaces(arr[i]);
        protocoled += rounded;
        protocoled += ';';
    }
    protocoled += static_cast<char>(END_OF_DATA); //add pause sign
    return protocoled;
}
string SERVER::CONNECTION::boolToString(vector<bool>& arr) {
    string protocoloed = "";
    for (size_t i = 0; i < RANGE; i++)
    {
        protocoloed += arr[i] ? "1" : "0"; //add the the string one for true zero for false

    }
    protocoloed += static_cast<char>(END_OF_DATA); //add pause sign
    return protocoloed;
}



int SERVER::CONNECTION::sendCordinates(bool has_more_def) //send cordinates for x,y,defined , moredef(if existant)  fpr non constant functions.
{
    //y_vals
    string y_vals_str = convertToDelimitedString(y);
    cout << "y_vals_str" << y_vals_str;
    string encrypted_y_vals_str = EncryptFunc(y_vals_str);

    //send Y vals
    send(clientSocket, encrypted_y_vals_str.c_str(), static_cast<int>(encrypted_y_vals_str.size()), 0);
    cout << "SENT Y_VALS /n" << endl;
    SLEEP //sleep to make sure data is acceptted before sending again

    //get X vals
    string x_vals_str = convertToDelimitedString(x);
    string encrypted_x_vals_str = EncryptFunc(x_vals_str);

    //send X_vals
    send(clientSocket, encrypted_x_vals_str.c_str(), static_cast<int>(encrypted_x_vals_str.size()), 0);
    cout << "SENT X_VALS /n" << endl;

    SLEEP //sleep to make sure data is acceptted before sending again


    //defined
    //send defined

    string defined_str = boolToString(defined);
    string encrypted_defined_vals_str = EncryptFunc(defined_str);

    send(clientSocket, encrypted_defined_vals_str.c_str(), static_cast<int>(encrypted_defined_vals_str.size()), 0);
    cout << "SENT D_VALS /n" << endl;

    SLEEP //sleep to make sure data is acceptted before sending again


    //additional defined
    if (has_more_def)
    {

        string more_def_str = convertToDelimitedString(more_def);

        string encrypted_more_def_str = EncryptFunc(more_def_str);

        send(clientSocket, encrypted_more_def_str.c_str(), static_cast<int>(encrypted_more_def_str.size()), 0);
        cout << "SENT MORE D_VALS /n" << endl;
    }

    return SUCCESS_RESPONSE;

}


string SERVER::CONNECTION::prepareMinMaxSTR(const pair<vector<pair<float, float>>,const  vector<pair<float, float>>> minmax) {
    //inpurs  MinMaxdata structure and prepare it for sending by converting it to string with communication protocol - flaots with ;
    //between , first for minimum second maxiumum, B implies going from min to max, p implies end of string in buffer.
    const vector<pair<float, float>>& firstPair = minmax.first;
    const vector<pair<float, float>>& secondPair = minmax.second;

    std::string result;

    // Add floats from the first pair (separated by ; and ,)
    for (const auto& pair : firstPair) {
        result += std::to_string(pair.first) + "," + std::to_string(pair.second) + ";";
    }

    // Add 'B' character to separate the first pair from the second pair
    result += static_cast<char>(DATA_SWAP);

    // Add floats from the second pair (separated by , and ;)
    for (const auto& pair : secondPair) {
        result += std::to_string(pair.first) + "," + std::to_string(pair.second) + ";";
    }

    // Add 'P' character to indicate the end of the string
    result += static_cast<char>(END_OF_DATA);

    return result;
}



int SERVER::CONNECTION::sendVerfication() //send OK back to client
{
    string OK = "ANY";
    send(clientSocket, OK.c_str(), static_cast<int>(OK.size()), 0);
    return 0;
}

