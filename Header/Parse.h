#pragma once

#include "usings.h"
#include "Graph.h"
#include "Header/calc_macros.h"


//defintions for tokenize
#define POW '^'
#define PLUS '+'
#define MINUS '-'
#define DIVIDE '/'
#define MULTIPLY '*'
#define PAR_OPEN '('
#define PAR_CLOSE ')'
#define DOT '.'









enum op_t {
    POW_OP = 0,
    PLUS_OP = 1,
    MINUS_OP = 2,
    MULTIPLY_OP = 3,
    DIVIDE_OP = 4,
    PAR_OPEN_OP = 5,
    PAR_CLOSE_OP = 6,
    NUM_OP

};


enum t_type {
    OPERATOR_TYPE = 7,
    FLOAT_TYPE = 8,
    INTEGER_TYPE = 9,
    VARIABLE_TYPE = 10,
    NOT_DEFINED_TYPE,
};

struct token {

    t_type token_type;

    struct {
        int Ival;
        op_t op_type = NUM_OP;
        float Fval;

    }type;

};

class Parser {

public:
    vector<token> assignValue(vector<token> exp, float val);

    // Constructor
    Parser();

    // Destructor
    ~Parser();




    //SOLVER
    vector<token> tokenize(const string& str);
    void GenerateCordinates(vector<token>exp, vector<float>& x, vector<float>& y, vector<bool>& IS_DEFINED);
    token Solve(const vector<token>& exp);


    //ANALYZER

    //MINMAX
    pair<vector<pair<float, float>>, vector<pair<float, float>>> find_min_max(const vector<float>& x, const vector<float>& y, const vector<bool>& DEFINED,  vector<float>& more_def, vector<token> exp);//1st min 2nd max9
    
    //intersects
    
    vector<float> find_x_intersects(const vector<float>& x, const vector<float>& y, const vector<bool>& DEFINED, vector<token> exp);
   
    
    vector<float> find_x_old(const vector<float>& x, const vector<float>& y, const vector<bool>& DEFINED, vector<token> exp);




    //BOUNDRIES


    vector<float> find_boundries(vector<float>& x, vector<float>& y, vector<bool>& defined, vector<token>& exp);
    vector<float> find_intersects_with_x(const vector<float>& x, const vector<float>& y, const vector<bool>& defined,const vector<token>&exp);

     

private:

    bool Too_Close_MINMAX_TO_BOUNDRY(const vector<float>& v, float suspect); 
    
    inline bool Too_Close_X_TO_Y(float suspect)
    {
        return (suspect <= Y_INTERSECT_FLAG && -Y_INTERSECT_FLAG <= suspect);
    }
    float check_sign_nearby(const vector <token>& exp, float i);


    //SOLVER
    token calcPlusMinus(const vector<token>& exp);
    token calcKefelHiluk(const vector<token>& exp);
    token calcPow(const vector<token>& exp);
    bool check_defined(vector<token>& exp);

    bool validate_pow(float base, float power);


    //ANALYZER

    //MINMAX
    float is_boundry(float min, const vector<token>& exp, float y_val, float i = 0);
    
    pair<float, float> find_min_max_cordinates(float min, vector<token>& exp, bool& direction , float i = 0 );
    //INTERSECTS
    float  recurive_x_calcualte(const vector<float>& x, int j, vector<token>& exp);
    //BOUNDRIES
   // float is_boundry(float min, vector<token>& exp, float i=0, float previous_gap=0);



    float find_x(float min, const vector<token>& exp, float previous_val, int index=0);


};


