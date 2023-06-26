#include "Header/Server.h"
#include "Header/usings.h"
#include "Header/DataTransfer.h"
#include "Header/Server.h"
#include "Header/Graph.h"
    // Constructor
    SERVER::SERVER() {

    };
    SERVER::~SERVER()
    {

    };
    // Destructor
    

    void SERVER::HandleClientWrapper(SOCKET conn) {//execption wrapper for handle client 
        try {
            HandleClient(conn);
        }
        catch (const std::exception& e) {
            cerr << "Exception caught in client thread: " << e.what() << '\n';
            return;
        }
        catch (...) {
            cerr << "Unknown exception caught in client thread.\n";
            return;
        }
    }


    void SERVER::HandleClient(SOCKET  conn)//create CONNECTION object for new client and call HandleConnection,
        //infinite loop that will run on a thread and handle communtion to client
    {
        
            CONNECTION connection = CONNECTION(conn);
            connection.HandleConnection();
            closesocket(conn);
            return;
       
    }

    
     //run the server
	void SERVER::run()
	{
        
            WSADATA wsData; // details about WINSOCK implentation
            WORD ver = MAKEWORD(2, 2); //winsock version

            int wsOk = WSAStartup(ver, &wsData); //init winsock.h
            if (wsOk != 0) //error catching
            {
                std::cerr << "Can't initialize Winsock! Quitting" << std::endl;
                return;
            }

            SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
            if (listening == INVALID_SOCKET)
            {
                std::cerr << "Can't create a socket! Quitting" << std::endl;
                WSACleanup();
                return;
            }

            sockaddr_in hint{}; //data structure for configuring socket connection
            hint.sin_family = AF_INET; //TCP
            hint.sin_port = htons(PORT); //PORT
            hint.sin_addr.S_un.S_addr = INADDR_ANY; //IP

            if (bind(listening, reinterpret_cast<sockaddr*>(&hint), sizeof(hint)) == SOCKET_ERROR)//bind server
            {
                std::cerr << "Failed to bind the socket. Error: " << WSAGetLastError() << std::endl;
                closesocket(listening);
                WSACleanup();
                return;
            }

            if (listen(listening, SOMAXCONN) == SOCKET_ERROR)//start listening 
            {
                std::cerr << "Failed to listen for incoming connections. Error: " << WSAGetLastError() << std::endl;
                closesocket(listening);
                WSACleanup();
                return;
            }

            std::cout << "Server is up and running." << std::endl;
            std::cout << "Listening for incoming connections on port " << PORT << std::endl;

            while (true)
            {
                sockaddr_in client{}; //data strutcure to represent client
                int clientSize = sizeof(client);
                SOCKET conn = accept(listening, reinterpret_cast<sockaddr*>(&client), &clientSize); //accept CONNECTION

                if (conn == INVALID_SOCKET)
                {
                    std::cerr << "Failed to accept the client connection. Error: " << WSAGetLastError() << std::endl;
                    closesocket(listening);
                    WSACleanup();
                    return;
                }
                // Client Thread Creation
                std::thread clientThread(&SERVER::HandleClient, this, conn);
                clientThread.detach(); // Detach and init the thread and allow it to run independently
                
            }

            closesocket(listening);
            WSACleanup();
        
	}

    
