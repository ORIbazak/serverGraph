#include "Header/usings.h"
#include "Header/Parse.h"
#include "Header/OutOfClass.h"
#include "Header/Graph.h"
#include "Header/DataTransfer.h"
#include "Header/calc_macros.h"
pair<vector<pair<float, float>>, vector<pair<float, float>>>  Parser::find_min_max(const vector<float>& x, const vector<float>& y, const vector<bool>& DEFINED, vector<float>&more_def ,vector<token> exp)
{//first for min, second for MAX
    //each vector in pair holds pair of x,y of minmax cordinates
    pair<vector<pair<float, float>>, vector<pair<float, float>>> min_max;
    pair<float, float> edge;
    bool flip = false;
    bool direction = false;
    int j = 0;
    while (j + JUMP < RANGE) 
    {
        flip = false;
        if (y[j] > y[j + 1]) 
        {
            direction = GOING_DOWN;
        }
        else
        {
            direction = GOING_UP;
        }
        switch (direction)
        {
        case (GOING_DOWN):
        {
            while (j + INTEGER_JUMP <RANGE ) 
            {
                if (DEFINED[j] && DEFINED[j+INTEGER_JUMP] && isFloatBetween(x[j], x[j + INTEGER_JUMP], more_def))
                {//break if direction chages due to +-assymptoes
                    flip = true;
                    direction = !direction;
                    break;
                }
                if (DEFINED[j] && DEFINED[j + INTEGER_JUMP] && y[j + INTEGER_JUMP] > y[j])
                {
                    //minmax suspition
                    break;
                }
                
                  j += JUMP;


            }
            if (j + INTEGER_JUMP >= RANGE)
            {
                return min_max;
            }
            if (!flip)
            {
                //if not +-assymptote, take func and calc min max cor
                edge = find_min_max_cordinates(x[j], exp, direction);
                
                    if (edge.first!=X_MAX+1&& Y_MAX+1 != edge.second&&Y_MAX >= edge.second && Y_MIN <= edge.second&& !Too_Close_MINMAX_TO_BOUNDRY(more_def, edge.first))

                        min_max.first.push_back(edge);


                
            }
            break;

        }

        case GOING_UP:
        {

            while (j + INTEGER_JUMP < RANGE)
            {
                if (DEFINED[j] && DEFINED[j+INTEGER_JUMP] && isFloatBetween(x[j], x[j + INTEGER_JUMP], more_def))
                {
                    flip = true;
                    direction = !direction;
                    break;
                }
                if (DEFINED[j] && DEFINED[j + INTEGER_JUMP] && y[j + INTEGER_JUMP] < y[j])
                {
                    break;
                }
                j += JUMP;
            }
            if (j + INTEGER_JUMP >= RANGE)
            {
                return min_max;
            }

            if (!flip)
            {
                //if not +-assymptote, take func and calc min max cor
                edge = find_min_max_cordinates(x[j], exp, direction);

                if (edge.first != X_MAX + 1 && Y_MAX + 1 != edge.second && Y_MAX >= edge.second && Y_MIN <= edge.second && !Too_Close_MINMAX_TO_BOUNDRY(more_def, edge.first))

                    min_max.second.push_back(edge);

            }

            break;
        }

        }
        if (flip)
        {
            while (isFloatBetween(x[j], x[j + INTEGER_JUMP], more_def))
            {
                j++;
            }
        }
        else
        {
            while (edge.first > x[j])
            {
                j++;
            }
        }
    }

    return min_max;
}




///BOUNDRIES

//find boundries that changed sign from one side to another( +- assymptotes)
vector<float> Parser::find_boundries(vector<float>& x, vector<float>& y, vector<bool>& defined, vector<token>& exp)
{

    vector<float> x_vals;

    int j = 0;
    bool direction = false;
    while (j + INTEGER_JUMP < RANGE)
    {
        if (defined[j] && defined[j+INTEGER_JUMP]&& y[j] * y[j + INTEGER_JUMP] < 0)//detect sign change
        {
            float a = x[j];
            a = is_boundry(x[j], exp,y[j]);
            if (a != X_MAX + 1) x_vals.push_back(a); //XMAX is not possible , means flaot is not boundry to be added


            while (j +INTEGER_JUMP< RANGE && y[j] * y[j + INTEGER_JUMP] < 0) j += JUMP;
        }
        else
        {
            j += JUMP;
        }



    }

    return x_vals; //return 



}

