#include "Header/usings.h"
#include "Header/Graph.h"
#include "Header/DataTransfer.h"



/**
 * Converts a vector of booleans to a vector of floats if true on bool
 *
 * @param boolVec The vector of booleans to convert.
 * @param index used for recursive calls. Defaults to 0 for the initial call.
 * @return A vector of floats
 */
vector<float> boolVecToFloatsVec(const vector<bool>& boolVec) {
    vector<float> floatsVec;

    for (size_t index = 0; index < boolVec.size(); index++) {
        if (!boolVec[index]) {
            float x_val = (static_cast<float>(index) * X_STEP) + X_MIN;
            floatsVec.push_back(x_val);
        }
    }

    return floatsVec;
}




bool isFloatBetween(float start, float end, const vector<float>& v, size_t index = 0) {
    // Base case: If we have reached the end of the vector
    if (index == v.size()) {
        return false;
    }

    // Check if the current float is between start and end
    if (v[index] >= start &&v[index] <= end) {
        return true;
    }

    // Recursive case: Check the next float in the vector
    return isFloatBetween(start, end, v, index + 1);
}








// Merges two sorted vectors of floats into a single sorted vector.
 //This function assumes that both input vectors are sorted in ascending order.
 
 //param vec1 The first sorted vector of floats.
 //param vec2 The second sorted vector of floats.
 //return A merged vector containing all elements from vec1 and vec2, sorted in ascending order.

vector<float> mergeBOUNDRIES(const vector<float>& vec1, const vector<float>& vec2) {
    vector<float> mergedVec;

    // Base cases: if either vector is empty, return the other vector
    if (vec1.empty())
        return vec2;
    if (vec2.empty())
        return vec1;

    // Compare the first elements of both vectors
    if (vec1[0] < vec2[0]) {
        // Append the smaller element to the merged vector and recursively merge the remaining elements
        mergedVec.push_back(vec1[0]);
        vector<float> remainingVec = mergeBOUNDRIES(vector<float>(vec1.begin() + 1, vec1.end()), vec2);
        mergedVec.insert(mergedVec.end(), remainingVec.begin(), remainingVec.end());
    }
    else {
        // Append the smaller element to the merged vector and recursively merge the remaining elements
        mergedVec.push_back(vec2[0]);
        vector<float> remainingVec = mergeBOUNDRIES(vec1, vector<float>(vec2.begin() + 1, vec2.end()));
        mergedVec.insert(mergedVec.end(), remainingVec.begin(), remainingVec.end());
    }

    return mergedVec;
}

void addMinMaxToIntersects(MinMax_Obj data, vector<float>& x_intersects)
{
    const vector<pair<float, float>>& min = data.first;
    const vector<pair<float, float>>& max = data.second;

    for (const auto& pair : min) {
        float x = pair.first;
        float y = pair.second;

        if ((0.2 >= y && y >= 0) || (-0.2 <= y && 0 >= y)) {
            x_intersects.push_back(x);
        }
    }
    for (const auto& pair : max) {
        float x = pair.first;
        float y = pair.second;

        if ((0.2 >= y && y >= 0) || (-0.2 <= y && 0 >= y)) {
            x_intersects.push_back(x);
        }
    }
    return;
}