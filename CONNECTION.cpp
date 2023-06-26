#include "Header/usings.h"
#include "Header/DataTransfer.h"
#include "Header/Server.h"
#include "Header/Graph.h"
#include "Header/Parse.h"
#include "Header/OutOfClass.h"

SERVER::CONNECTION::CONNECTION(SOCKET& socket)
//constructor assiging conenction with client, init attributes to defult

    : clientSocket(socket),
    exp(),
    x(RANGE, 0),
    y(RANGE, 999),
    defined(RANGE, true),
    boundries(0, true),
    bytesRead(0),
    recv_message(""),
    is_constant_func(false),
    constant_y(0.0),
    minMaxData({ {}, {} }),
    BUF(new char[BUF_SIZE])
{
    memset(BUF, 0, BUF_SIZE);
}
    


SERVER::CONNECTION::~CONNECTION()
{
    //constructor, deleter buffer
    delete[] BUF;
}



void SERVER::CONNECTION::resetData() //reset data if new func
{
    exp.clear();
    std::fill(x.begin(), x.end(), 0);
    std::fill(y.begin(), y.end(), 999);
    std::fill(defined.begin(), defined.end(), true);
    boundries.clear();
    bytesRead = 0;
    recv_message = "";
    is_constant_func = false;
    constant_y = 0.0;
    std::fill(BUF, BUF + BUF_SIZE, 0);
}













void SERVER::CONNECTION::HandleConnection()
{
    try
    {
        logClientInfo();// Log information about the connected client.

        while (true)
        {
            // Receiving and processing data from the client

            string str;

            int bytesRead = recv(clientSocket, BUF, static_cast<int>(BUF_SIZE), 0);
            recv_message= string(BUF, 0, bytesRead);
            
            
           

  
                recv_message = AESdecrypt(AESkey, recv_message);
                cout << "recv_message" << recv_message << endl;
                char flag = recv_message[0];
                RequestType request = getRequestType(flag);
                cout << "REQUEST" << static_cast<int>(request) << endl;
                int result = HandleREQUEST(request);
                if (result == TERMINATE_RESPONSE || result == ERROR_RESPONSE)
                {
                    return; // Return from the function if termination or an error occurred.
                }
                memset(BUF, 0, static_cast<int>(BUF_SIZE));
            
        }
    }
    catch (const std::exception& e)//catch exception
    {
        std::cerr << "Exception caught in HandleConnection: " << e.what() << '\n';
        return;
    }
    catch (...)
    {
        std::cerr << "Unknown exception caught in HandleConnection.\n";
        return;

    }
}









