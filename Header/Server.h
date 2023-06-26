#pragma once
#include "usings.h"
#include "Parse.h"
#include "DataTransfer.h"





class SERVER {
public:
	// Constructor
	SERVER();

	// Destructor
	~SERVER();

	class CONNECTION
	{
	private: 
		vector<token> exp;
		bool is_constant_func;
		float constant_y;
		SOCKET clientSocket;
		vector<float> x;
		vector<float> y;
		vector<bool> defined;
		vector<float> more_def;
		vector<float>boundries;
		string recv_message;
		MinMax_Obj minMaxData;

	public:
		

		int bytesRead;
		char* BUF;
		CONNECTION(SOCKET& socket);
		~CONNECTION();
		int HandleREQUEST(RequestType& type);
		int sendVerfication();
		void resetData();
		int sendCordinates(bool has_more_def);
	
		string convertToDelimitedString(vector<float>& arr);

		string boolToString(vector<bool>& arr);


		RequestType getRequestType(char& c);
		int HandleNewValidFUNC(string& str);

		string ParseFunc();

		void HandleConnection();

		void logClientInfo();
		string prepareMinMaxSTR(const pair<vector<pair<float, float>>, const vector<pair<float, float>>> minmax);

	};

public:
	void run();
	void HandleClientWrapper(SOCKET conn);
	void HandleClient(SOCKET  conn);


	



};

string convertToStringWithThreeDecimalPlaces(float f); //convert to 3 dots after point
