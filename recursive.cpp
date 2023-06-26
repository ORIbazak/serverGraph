#include "Header/usings.h"
#include "Header/Parse.h"
#include "Header/OutOfClass.h"
#include "Header/usings.h"
#include "Header/calc_macros.h"
pair<float, float>  Parser::find_min_max_cordinates(float min, vector<token>& exp, bool& direction, float i)//recrusive function 
{
    //recusible check if there is minmax berwteen min and min+1
    if (i >= 1)

        return pair<float, float>(X_MAX+1,Y_MAX+1);//not found ,return not possinle values

    vector<token> left = assignValue(exp, min + i);
    vector <token> right = assignValue(exp, min + i + static_cast<float>((2* reccursive_jump)));
    token left_token = Solve(left); token right_token = Solve(right);
    float l_val = 0; float r_val = 0;
    if (left_token.token_type == INTEGER_TYPE) { l_val = left_token.type.Ival; }
    if (left_token.token_type == FLOAT_TYPE) { l_val = left_token.type.Fval; }
    if (right_token.token_type == INTEGER_TYPE) { r_val = right_token.type.Ival; }
    if (right_token.token_type == FLOAT_TYPE) { r_val = right_token.type.Fval; }
    if (l_val == r_val) { return(std::make_pair(min + i + reccursive_jump, l_val)); }// if same height, return it
    switch (direction)
    {
    case (GOING_DOWN):
    {
        if (l_val > r_val)
        {
            //same direction , recall func
            return find_min_max_cordinates(min, exp, direction, i + 0.02f);
        }
        else
        {
            //direction cheaned, foundminmax
            float x_val = min + i + reccursive_jump;
            token answer_token = Solve(assignValue(exp, x_val));
            float y_val = 0;
            if (answer_token.token_type == INTEGER_TYPE) { y_val = answer_token.type.Ival; }
            if (answer_token.token_type == FLOAT_TYPE) { y_val = answer_token.type.Fval; }
            return std::make_pair(round_float(x_val), round_float(y_val));

        }
    }
    case GOING_UP:
    {
        if (r_val > l_val)
        {//same direction , recall func
            return find_min_max_cordinates(min, exp, direction, i + 2*reccursive_jump);
        }
        else
        {//direction cheaned, foundminmax
            float x_val = min + i + static_cast<float>((2 * reccursive_jump));
            token answer_token = Solve(assignValue(exp, x_val));
            float y_val = 0;
            if (answer_token.token_type == INTEGER_TYPE) { y_val = answer_token.type.Ival; }
            if (answer_token.token_type == FLOAT_TYPE) { y_val = answer_token.type.Fval; }
            return std::make_pair<float, float>(round_float(x_val), round_float(y_val));

        }
    }
    }


}




//INTERSECTS


float   Parser::recurive_x_calcualte(const vector<float>& x, int j, vector<token>& exp)
//takes expression , x values, index of suspect x values, and check if theres is intersect with X between x and x+1;
{
    for (float i = 0; i < 1; i +=  reccursive_jump)


    {
        vector<token> solveAble = assignValue(exp, x[j] + i);
        token t = Solve(solveAble);
        float answer = 0;
        if (t.token_type != NOT_DEFINED_TYPE)
        {
            if (t.token_type == INTEGER_TYPE) answer = t.type.Ival;
            else if (t.token_type == FLOAT_TYPE)  answer = t.type.Fval;

            if ((0 < answer && answer < 0.3) || (answer > -0.3 && 0 > answer < 0.3) || answer == 0)
            {
                float rounded = round_float(x[j] + i);  // Round to two decimal places

                return rounded;
            }



        }

    }

    return X_MAX+1;

}



//boundries



float Parser::check_sign_nearby(const vector <token>& exp, float val)
{
    //takes expression and val, ad check if its +- assymptote (calc calsoe vakues and see if gap is big enough and vals dirrenct signs)
    vector<token>left = assignValue(exp, val -0.011);
    vector<token>right = assignValue(exp, val + 1 +0.0001); //take two close values 
    token left_token = Solve(left); token right_token = Solve(right);
    float l_val = 0; float r_val = 0;
    if (left_token.token_type == INTEGER_TYPE) { l_val = left_token.type.Ival; }
    if (left_token.token_type == FLOAT_TYPE) { l_val = left_token.type.Fval; }
    if (right_token.token_type == INTEGER_TYPE) { r_val = right_token.type.Ival; }
    if (right_token.token_type == FLOAT_TYPE) { r_val = right_token.type.Fval; }
    if (right_token.token_type == NOT_DEFINED_TYPE|| left_token.token_type == NOT_DEFINED_TYPE) { return check_sign_nearby(exp, val +reccursive_jump/2); }
    if (l_val* r_val < 0&& std::fabs(l_val) + std::fabs(r_val) >2) //flag to check not intersect , cgheck if irrenet signs and enough distance
    {
        return val;
    }
    else
    {
        return X_MAX + 1;
    }
}

float Parser::is_boundry(float min, const vector<token>& exp, float y_val, float i )
{
    //recursibe fucntion that tkaes expression ,x val and y_val , and check if there is +-asyymptote between x and x+1
    
    int sign = 0;
    
        if (y_val >0){
            sign =1;
             }
        else
        {
            sign = -1;
        }
    
    if (i == min + 1)
    {
        return X_MAX + 1;
    }

    vector<token> solveable = assignValue(exp, min + i);
    token t = Solve(solveable);
    if (t.token_type == NOT_DEFINED_TYPE)
    {
        float f = check_sign_nearby(exp, min+i);
        if (f == min+i) return f;
    }
    float new_val = 0;
   if (t.token_type == INTEGER_TYPE) { new_val = t.type.Ival; }
    if (t.token_type == FLOAT_TYPE) { new_val = t.type.Fval; }
    if (new_val * y_val<=0)
    {
        return check_sign_nearby(exp, min + i);
    }
    return is_boundry(min, exp,new_val , i += static_cast<float>(reccursive_jump));



}


float Parser::find_x( float min, const vector<token> & exp,float previous_val , int index)
{
    if (index == 1)
    {
        return X_MAX + 1;
    }
    float y_val=0;
    vector<token> vec = assignValue(exp, min + index);
    token solve = Solve(vec);
    if (solve.token_type == FLOAT_TYPE)
    {
        y_val = solve.type.Fval;

    }
    if (solve.token_type == NOT_DEFINED_TYPE)
    {
        index++;
        return find_x(min, exp, previous_val, index);

    }
    if (solve.token_type ==INTEGER_TYPE)
    {
        y_val = solve.type.Ival;
    }
    if (previous_val * min < 0)
    {
        return min + index;
    }
    index++;
    return find_x(min, exp, y_val, index);
}




