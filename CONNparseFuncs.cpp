#include "Header/usings.h"
#include "Header/DataTransfer.h"
#include "Header/Server.h"
#include "Header/Graph.h"
#include "Header/Server.h"

//Checks if all y - values in the given vector are the same.
//@param y The vector of y - values to be checked.
//return True if all y - values are the same, false otherwise.
bool areYvalsTheSame(const vector<float>& y, size_t index) {

   const float firstElement = y[0];
    if (index == y.size() - 1) return true;
    if (firstElement != y[index]) return false;
    
    return areYvalsTheSame(y, ++index);
}




string SERVER::CONNECTION::ParseFunc()
//gets function from string
{
    int i = 0;
    while (i < recv_message.size() && recv_message[i] != ';') i++; //ignore the request type (char and then ;)
    i++;

    string func;
    while (i < recv_message.size() && recv_message[i] != ';') //get func until ;
    {
        func += recv_message[i];
        i++;
    }
    return func;
}


RequestType SERVER::CONNECTION::getRequestType(char& c) // get request type based on char
{
    switch (static_cast<int>(c - '0')) //get NUMERIC VALUE and chech its value
    {
    case (static_cast<int>(RequestType::intersects)): //if intersects
    {
        return RequestType::intersects;

    }
    case (static_cast<int>(RequestType::newFunc)): //if newFunc
    {
        return RequestType::newFunc;

    }
    case (static_cast<int>(RequestType::terminate)): //if terminate
    {
        return RequestType::terminate;

    }
    case (static_cast<int>(RequestType::MinMax)): //if mixmax
    {
        return RequestType::MinMax;

    }
    case (static_cast<int>(RequestType::boundries)): //if boundries
    {
        return RequestType::boundries;

    }
    case (static_cast<int>(RequestType::DRAW)): //if DRAW
    {
        return RequestType::DRAW;

    }
    case (static_cast<int>(RequestType::reset)): //if reset
    {
        return RequestType::reset;

    }

    break;
    }

}
