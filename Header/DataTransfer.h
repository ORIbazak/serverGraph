#pragma once
#include "usings.h"

#include "Graph.h"

#define MinMax_Obj pair<vector<pair<float, float>>, vector<pair<float, float>>>


//request enum case 

enum class RequestType {
    newFunc = 1,
    intersects = 2,
    MinMax = 3,
    boundries = 4,
    terminate = 5,
    DRAW = 6,
    reset = 7,
};

// add openssl lib to ;omer
#pragma comment(lib,"OpenSSL/lib/libcrypto.lib")
#pragma comment(lib,"OpenSSL/lib/libssl.lib") 

const size_t BUF_SIZE = 1000; //max string is 20, 1000 is enough
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include <chrono>

#define PORT 1500
#define SUCCESS_RESPONSE 0
#define ERROR_RESPONSE 1 
#define TERMINATE_RESPONSE 2
#define AES_BLOCK_SIZE 16
#define BASE_64_BLOCK 3
const string AESkey = "ORICOHENBAZAK:)";//AES KEY




#define SLEEP std::this_thread::sleep_for(std::chrono::seconds(2));//sleep to make sure data is acceptted before sending again

string AESencrypt(const string& key,  string& str);//ecntupy and decrypt data
string AESdecrypt(const string& key,   string& str);
string base64encode(const string& str);
string base64decode(const string& str);


 string EncryptFunc(const string& str);