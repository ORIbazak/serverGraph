#include "Header/usings.h"
#include "Header/DataTransfer.h"
#include "Header/Graph.h"
#include "Header/Server.h"

//print vectors.
void PrintCordinates(const vector<float>& x, const vector<float>& y, const vector<bool>& defined)
{
    for (size_t i = 0; i < RANGE; i++)
    {
        
        bool a = defined[i];
            cout << "(" << x[i] << " , " << y[i] << ")" << "state"<<a << endl;
        
    }
}

//print minmax data structers.
void printMinMax(const pair<vector<pair<float, float>>, vector<pair<float, float>>>& data)
{
    // Print minimum values
    cout << "MINIMUM:" << endl;
    for (const auto& pair : data.first) {
        std::cout << "(" << pair.first << ", " << pair.second << ")\n";
    }

    // Print maximum values
    cout << "MAXIMUM:" << endl;
    for (const auto& pair : data.second) {
        std::cout << "(" << pair.first << ", " << pair.second << ")\n";
    }
}


//print new Client info on server console.
void SERVER::CONNECTION::logClientInfo()
{
    char host[NI_MAXHOST];     // Client's remote name
    char service[NI_MAXSERV];  // PORT the client is connected on

    ZeroMemory(host, NI_MAXHOST); //set the memory of the buffers to zero.
    ZeroMemory(service, NI_MAXSERV);

    if (getnameinfo(reinterpret_cast<sockaddr*>(&clientSocket), sizeof(clientSocket), //extract the socket name and port from the SOCKET structure
        host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        std::cout << "*****" << host << " CONNECTED ON PORT " << service << std::endl;
    }
    else //if the connection is not assosiated with a domain, get a string representaion of the IP and print it with PORT
    {
        inet_ntop(AF_INET, &(reinterpret_cast<sockaddr_in*>(&clientSocket))->sin_addr,
            host, NI_MAXHOST);
        std::cout << "*****" << host << " CONNECTED ON PORT " << service <<
            ntohs((reinterpret_cast<sockaddr_in*>(&clientSocket))->sin_port) << std::endl;
    }
}