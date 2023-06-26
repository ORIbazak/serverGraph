#pragma once
#include "usings.h"
#include "Parse.h"
#include "DataTransfer.h"
bool areYvalsTheSame(const vector<float>& y,size_t index =0);
vector<float> boolVecToFloatsVec(const vector<bool>& boolVec);
vector<float> mergeBOUNDRIES(const std::vector<float>& vec1, const std::vector<float>& vec2);



bool isFloatBetween(float start, float end, const std::vector<float>& floatVector, size_t index = 0);


//prints
void printMinMax(const pair<vector<pair<float, float>>, vector<pair<float, float>>>& data);

void PrintCordinates(const vector<float>& x, const vector<float>& y, const vector<bool>& defined);





inline bool hasVariable(const string& str)
{
	return (std::count(str.begin(), str.end(), 'x') > 0 || std::count(str.begin(), str.end(), 'X') > 0);
}
inline float roundTo2DecimalPlaces(float number) {
    return std::round(number * 100) / 100;
}
inline bool is_sign(char c)
{


    return ((c == MINUS) || (c == PLUS) || (c == MULTIPLY) || (c == DIVIDE) || (c == POW));

}




//data

inline float round_float(float f)
{
    return  std::round((f) * 100) / 100;
}

void addMinMaxToIntersects(MinMax_Obj data, vector<float>& x_intersects);