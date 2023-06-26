#include "Header/usings.h"
#include "Header/Parse.h"
#include "Header/OutOfClass.h"



Parser::Parser()//constructor
{

};
Parser::~Parser() {//destructor

}



//tokenize
vector<token>  Parser::tokenize(const string& str) {
    vector<token> v;
    //takes input string and coverts in into tokenize expression that can later be used for aclaution cordinates
    for (int i = 0; i < str.size(); i++)
    {
        token t;
        if (str[i] == 'X' || str[i] == 'x')
        {
            t.token_type = VARIABLE_TYPE;
            if (i > 0 && isdigit(str[i - 1]))//handle if there is int and X right afterwards
            {
                token tMulti;
                tMulti.token_type = OPERATOR_TYPE;
                tMulti.type.op_type = MULTIPLY_OP;
                v.push_back(tMulti);

            }

        }
        if (str[i] == POW)
        {
            t.token_type = OPERATOR_TYPE;
            t.type.op_type = POW_OP;
        }
        if (str[i] == PAR_OPEN)
        {
            t.token_type = OPERATOR_TYPE;
            t.type.op_type = PAR_OPEN_OP;
            if (i > 0 && ((str[i - 1] == PAR_CLOSE) || (isdigit(str[i - 1]))))
            {
                token tMulti;
                tMulti.type.op_type = MULTIPLY_OP; // handles )(
                tMulti.token_type = OPERATOR_TYPE;
                v.push_back(tMulti);
            }


        }

        if (str[i] == PAR_CLOSE) {
            t.token_type = OPERATOR_TYPE;
            t.type.op_type = PAR_CLOSE_OP;

        }

        if (str[i] == PLUS) {
            t.token_type = OPERATOR_TYPE;
            t.type.op_type = PLUS_OP;


        }
        if (str[i] == MINUS)
        {
            t.token_type = OPERATOR_TYPE;
            if (i == 0 || is_sign(str[i - 1]) || str[i] == PAR_OPEN) // handle if the minus serve as sign rather as operator
            {


                t.type.op_type = MULTIPLY_OP;

                token tone;
                tone.type.Ival = -1;
                tone.token_type = INTEGER_TYPE;


                v.push_back(tone);
            }
            else {
                t.type.op_type = MINUS_OP;
            }

        }

        if (str[i] == MULTIPLY) {
            t.token_type = OPERATOR_TYPE;
            t.type.op_type = MULTIPLY_OP;


        }
        if (str[i] == DIVIDE) {
            t.token_type = OPERATOR_TYPE;
            t.type.op_type = DIVIDE_OP;
        }
        if (isdigit(str[i]))
        {


            string str2;
            {

                bool isFloat = false;


                int j = i;
                while (isdigit(str[j]) || str[j] == DOT) {

                    str2 += str[j];
                    if (str[j] == DOT)
                    {
                        isFloat = true;
                    }

                    j++;

                }
                i = j - 1;

                if (isFloat)
                {
                    t.token_type = FLOAT_TYPE;

                    t.type.Fval = std::stof(str2);

                }
                else
                {
                    t.token_type = INTEGER_TYPE;
                    t.type.Ival = std::stoi(str2);


                }
            }

        }

        v.push_back(t);

    }
    return v;
}





//ASSIGNVALUE


vector<token>  Parser::assignValue(vector<token> exp, float val)
//takes vector of token and sets value X to param val in all apearances
{
    if (std::round(val) == val)
    {
        for (int i = 0; i < exp.size(); i++)
        {
            if (exp[i].token_type == VARIABLE_TYPE)
            {
                exp[i].token_type = INTEGER_TYPE;
                exp[i].type.Ival = val;

            }
        }
    }
    else
    {
        for (int i = 0; i < exp.size(); i++)
        {
            if (exp[i].token_type == VARIABLE_TYPE)
            {
                exp[i].token_type = FLOAT_TYPE;
                exp[i].type.Fval = val;

            }
        }
    }
    return exp; //return solveable expression
}



//generateCORD
void  Parser::GenerateCordinates(vector<token>exp, vector<float>& x, vector<float>& y, vector<bool>& IS_DEFINED)
{
    //fills reference to vectors in values of function, and sets defined to false in index i if x in index i not defiend
    for (int i = 0; i < RANGE; i++)
    {

        x[i] = X_MIN + (i)*X_STEP;
        vector<token> equation = assignValue(exp, x[i]);

        if (check_defined(equation))
        {
            Parser parse = Parser();
            token t = Solve(equation);

            if (t.token_type == FLOAT_TYPE)
            {

                y[i] = t.type.Fval;
               





            }
            else if (t.token_type == INTEGER_TYPE)
            {
                y[i] = t.type.Ival;
                //save storage, doesnt matter wont be display anyways
            }
            else {
                IS_DEFINED[i] = false;
            }

        }
        else
        {
            IS_DEFINED[i] = false;


        }
        


    }


}


bool  Parser::check_defined(vector<token>& exp)//check if there is division in zero in token
{
    for (int i = 0; i < size(exp) - 1; i++)
    {
        if (exp[i].type.op_type == DIVIDE_OP && exp[i + 1].token_type == INTEGER_TYPE && exp[i].type.Ival == 0)return false;
    }
    return true;
}

bool  Parser::validate_pow(float base, float power)//check if pow operation in defined
{
    return true;
    if (base == power && base == 0)return false; // not if base and power are 0
    if (power < 0 && base < 0)return false;//not if both are negative
    if (base < 0 && std::round(log2(power) == log2(power))) return false; //not for negaticve base with even power
    return true;

}


bool Parser::Too_Close_MINMAX_TO_BOUNDRY(const vector<float>& v, float suspect) {
    for (float value : v) {//checks if minmax to clsoe to boundry (very similar checks, makes sure +-asyumptote wont count as minmax_
        if (std::fabs(value - suspect) < MIN_MAX_CLOSE_TO_BOUNDRY_FLAG) {
            return true;
        }
    }
    return false;
}

