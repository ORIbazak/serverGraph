#include "Header/usings.h"
#include "Header/Parse.h"
#include "Header/calc_macros.h"





vector<float>  Parser::find_x_old(const vector<float>& x, const vector<float>& y, const vector<bool>& DEFINED, vector<token> exp)
{
    vector<float> x_vals;
    
    for (int i = 0; i < RANGE; i+=JUMP)
    {
        if (DEFINED[i]) {
            if (i+INTEGER_JUMP<RANGE && ((y[i] <= X_INTERSECT_FLAG && y[i] >= 0) || (-X_INTERSECT_FLAG <= y[i] && y[i] <= 0))&&y[i]*y[i+INTEGER_JUMP]<0) {
                switch (y[i] > 0) {
                case true: // case number is between 0 to 1

                    if (y[i + 1] < y[i])
                    {  // checks if next value is smaller
                        int j = i;

                        while (j < RANGE - 1 && y[j + 1] > 0 && y[j + 1] < y[j]) j++;  // if true, goes through ARR until find the smallest val
                        if (y[j] < ALMOST_ZERO)
                            x_vals.push_back(x[j]);   // if close enough to zero, pushes it as x intersect
                            else
                            {
                                float intersect = recurive_x_calcualte(x, j, exp);
                                 x_vals.push_back(intersect); 

                            }// find intersects, pushes it to vector
                        while (j<RANGE&& y[j] > -X_INTERSECT_FLAG)
                        {
                            j++;
                        }
                        if (j == RANGE)return x_vals;
                        i = j;
                    }
                    else {  // if the next value is bigger
                        if (y[i] < ALMOST_ZERO)
                        {

                            x_vals.push_back(x[i]);
                        }// if close enough to zero, pushes it as x intersect
                        else
                            x_vals.push_back(recurive_x_calcualte(x, i, exp));

                        // if not, finds intersect and pushes it to vector
                    }
                    break;

                case false:

                    if (y[i] == 0)
                    {
                        x_vals.push_back(x[i]);
                    }
                    else {
                        if (y[i + 1] > y[i]) {  // if next value is bigger
                            int j = i;
                            while (j < RANGE - 1 && y[j + 1] < 0 && y[j + 1] > y[j])
                                j++;  // if true, goes through ARR until find the smallest val
                            if (y[j] > -ALMOST_ZERO)
                            {
                           
                                    x_vals.push_back(x[j]);
                            }// if close enough to zero, pushes it as x intersect
                            else
                            {
                                float intersect = recurive_x_calcualte(x,j, exp);

                                 x_vals.push_back(intersect); 
                                // find intersects, pushes it to vector

                            }
                            while (j < RANGE && y[j]< X_INTERSECT_FLAG)
                            {
                                j++;
                            }
                            if (j == RANGE)return x_vals;
                            i = j;
                        }
                        else {  // if the next value is smaller
                            if (y[i] > -ALMOST_ZERO)
                                 x_vals.push_back(x[i]);  // if close enough to zero, pushes it as x intersect
                                else
                                {
                                    float intersect = recurive_x_calcualte(x, i, exp);

                                      x_vals.push_back(intersect);   // if not, finds intersect and pushes it to vector
                                }
                        }
                    }
                    break;

                }
            }
        }
    }

    return x_vals;
}