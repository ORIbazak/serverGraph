#include "Header/Parse.h"
#include "Header/usings.h"



//SOLVE

token  Parser::Solve(const vector<token>& exp)// main solving function
//input : math exericse
//output: token with enum and semi structs the hold his answers
{
    vector<token> v;
    bool found = false;
    for (int i = 0; i < exp.size(); i++)
    {
        if (exp[i].token_type == OPERATOR_TYPE)
        {
            if (exp[i].type.op_type == PAR_CLOSE_OP) //detect closing OP (inner bracket)
            {
                found = true;


                for (int j = i - 1; j >= 0; j--) {
                    if (exp[j].token_type == OPERATOR_TYPE)
                    {
                        if (exp[j].type.op_type == PAR_OPEN_OP) //detect inner exression
                        {
                            for (int k = j + 1; k <= i - 1; k++) { v.push_back(exp[k]); }; //copy it into new expression
                            token instuff = Solve(v);
                            if (instuff.token_type == NOT_DEFINED_TYPE) //expression not defined (invaild Pow,divide by zero)
                            {
                                return instuff;
                            }
                            v.clear();
                            //create new expression with solved inner expression 
                            for (int k = 0; k <= j - 1; k++) { v.push_back(exp[k]); };
                            v.push_back(instuff);
                            for (int k = i + 1; k < exp.size(); k++) { v.push_back(exp[k]); };
                            return Solve(v); //recall one semi solved funtions.

                        }
                    }
                }

            }
        }
    }
    return calcPow(exp);//calc solving POW operatinos on inner bracket expression (or on expression if not brackets)
}




//plusMinus
token  Parser::calcPlusMinus(const vector<token>& exp)
//takes match exrecise and solve it (only plus and minmus  thats left)
{
    if (exp[0].token_type == NOT_DEFINED_TYPE)//if not defined, return it 
    {
        return exp[0];
    }

    for (int i = 0; i < exp.size(); i++)
    {


        if (exp[i].token_type == OPERATOR_TYPE) { //detect remanging operator
            vector<token> v;
            for (int j = 0; j <= i - 2; j++) {//save tokens that arent realted to current recursive call calculation
                v.push_back(exp[j]);
            }
            float before = 0; // calc answer based on operator specifed in enum type.op_type
            if (exp[i - 1].token_type == INTEGER_TYPE)
            {
                before = exp[i - 1].type.Ival;
            }
            else {
                before = exp[i - 1].type.Fval;
            }
            float after = 0;
            if (exp[i + 1].token_type == INTEGER_TYPE)
            {
                after = exp[i + 1].type.Ival;
            }
            else {
                after = exp[i + 1].type.Fval;
            }

            float ans = 0;
            switch (exp[i].type.op_type) {
            case PLUS_OP: //calc 
                ans = before + after;
                break;
            case MINUS_OP:
                ans = before - after;
                break;
            }
            token t;
            if (std::round(ans) == ans)//save answer
            {
                t.token_type = INTEGER_TYPE;
                t.type.Ival = ans;

            }
            else {
                t.token_type = FLOAT_TYPE;
                t.type.Fval = ans;

            }

            v.push_back(t);
            for (int k = i + 2; k < exp.size(); k++) {//save tokens that arent realted to current recursive call calculation

                v.push_back(exp[k]);
            }
            return calcPlusMinus(v); //recall func on semi solved vector


        }


    }
    return exp[0]; //return token holding answer
}


//calcPOW
token  Parser::calcPow(const vector<token>& exp)
{
    //calc pow operations in expression
    vector<token> v;
    for (int i = 0; i < exp.size(); i++)
    {
        if (exp[i].token_type == OPERATOR_TYPE)
        {
            if (exp[i].type.op_type == POW_OP) //find pow 
            {
                for (int j = 0; j <= i - 2; j++) v.push_back(exp[j]);//save tokens that arent realted to current recursive call calculation
                float before = 0;
                if (exp[i - 1].token_type == INTEGER_TYPE)
                {
                    before = exp[i - 1].type.Ival;
                }
                else {
                    before = exp[i - 1].type.Fval;
                }
                float after = 0;
                if (exp[i + 1].token_type == INTEGER_TYPE)
                {
                    after = exp[i + 1].type.Ival;
                }
                else
                {
                    after = exp[i + 1].type.Fval;
                }
                if (validate_pow(before, after))//check if operation valid, if yes calc answer
                {
                    float answer = std::pow(before, after);
                    token t;
                    if (std::round(answer) == answer)
                    {
                        t.token_type = INTEGER_TYPE;
                        t.type.Ival = std::round(answer);
                    }
                    else {
                        t.token_type = FLOAT_TYPE;
                        t.type.Fval = answer;
                    }
                    v.push_back(t);
                    for (int k = i + 2; k < exp.size(); k++) v.push_back(exp[k]);//save tokens that arent realted to current recursive call calculation
                    return calcPow(v);//call to solve more pow  operations

                }
                else//if not its not defined, return is immiedtly
                {
                    token not_defined;
                    not_defined.token_type = NOT_DEFINED_TYPE;
                    return not_defined;
                }
            }
        }

    }


    return  calcKefelHiluk(exp);//calc kefel hiluk if no pow are left 




}


token  Parser::calcKefelHiluk(const vector<token>& exp)
{

    //calc KefelHilukoperations in expression

    vector<token> v;
    for (int i = 0; i < exp.size(); i++)
    {
        if (exp[i].type.op_type == MULTIPLY_OP || exp[i].type.op_type == DIVIDE_OP)//find op 
        {


            for (int j = 0; j <= i - 2; j++)  v.push_back(exp[j]);//save tokens that arent realted to current recursive call calculation
            float before = 0;
            float after = 0;
            if (exp[i - 1].token_type == INTEGER_TYPE)
            {
                before = exp[i - 1].type.Ival;
            }
            else {
                before = exp[i - 1].type.Fval;
            }
            if (exp[i + 1].token_type == INTEGER_TYPE)
            {
                after = exp[i + 1].type.Ival;
            }
            else {
                after = exp[i + 1].type.Fval;
            }

            float ans = 0;
            switch (exp[i].type.op_type) {//calc based on op 
            case DIVIDE_OP:
                if (after != 0)
                {
                    ans = before / after;
                    break;
                }
                else
                {
                    token not_defined;// if divided by zero, sert token to not defined and return it
                    not_defined.token_type = NOT_DEFINED_TYPE;
                    return not_defined;
                }

            case MULTIPLY_OP:
                ans = before * after;
                break;
            }
            token t;
            if (std::round(ans) == ans)
            {
                t.token_type = INTEGER_TYPE;
                t.type.Ival = std::round(ans);
            }
            else
            {
                t.token_type = FLOAT_TYPE;
                t.type.Fval = ans;
            }
            v.push_back(t);
            for (int k = i + 2; k < exp.size(); k++) v.push_back(exp[k]);//save tokens that arent realted to current recursive call calculation
            return calcKefelHiluk(v); //call to solve more KefelHiluk  operations

        }

    }

    return calcPlusMinus(exp);//calc plus minus  if no pow are left 



}