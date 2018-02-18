#pragma once
#include <iostream>
#include <string>

using namespace std;

class Request_HTTP {
public:
    string method_request;
    string url_request;
    string httpNum_request;
	string message_request;

	Request_HTTP();
	void newMethod(string method);
	void newURL(string url);
	void newhttpNum(string httpNum);
	void newMessage();
};

