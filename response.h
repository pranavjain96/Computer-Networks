#pragma once
#include <iostream>
#include <string>

using namespace std;

class ResponseHTTP {
public:
	//variables
	string message_response;
	string httpNum;
	string error_code;
	string htmlbody;
	//break down of requested url
	string message_request;
	string method_request;
	string url_request;
	string host;
	int port_num;
	string directory;

	//methods
	//to create response
	ResponseHTTP();
	void newHTTPNum(string v);
	void newerrorCode(string c);
	void newhtmlBody(string d);
	void newMessage();

	//to decode http request
	void requestMessage(string rm);
	void decodeMessage();
	void decodeURL();

};
