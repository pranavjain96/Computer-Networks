#include "response.h"
#include <sstream>

ResponseHTTP::ResponseHTTP() {
	httpNum = "HTTP/1.0";
	error_code = "400 Bad Request";
	htmlbody = "";
}

void ResponseHTTP::newHTTPNum(string v) {
	httpNum = v;
}

void ResponseHTTP::newerrorCode(string c) {
	error_code = c;
}

void ResponseHTTP::newhtmlBody(string d) {
	htmlbody = d;
}

void ResponseHTTP::newMessage() {
	//stringstream message_new;
	//message_new << httpNum << " " << error_code << "\r\n" << htmlbody << "\r\n";
	message_response = httpNum + " " + error_code + "\r\n" + htmlbody + "\r\n";
}

void ResponseHTTP::requestMessage(string rm) {
	message_request = rm;
}

void ResponseHTTP::decodeMessage() {
	const int max_buf = sizeof(httpNum) + sizeof(error_code) + sizeof(htmlbody) + 5;	//max size of input buffer
	char buf[max_buf];		//input buffer 
	memset(&buf, '\0', max_buf);	//initialise buffer to empty
	int j = 0;				//index of where we are in input buffer
	int i = 0;				//index of where we are in request message string

	//while char not space, store chars in buffer - this is requested method
	while (message_request[i] != ' ' && j < max_buf) {
		buf[j] = message_request[i];
		i++;
		j++;
	}
	method_request = string(buf);

	//reset buffer and increase index by 1 to skip over the space character
	memset(&buf, '\0', max_buf);
	j = 0;
	i++;
	//then while char not space, store chars in buffer - this is url
	while (message_request[i] != ' ' && j < max_buf) {
		buf[j] = message_request[i];
		i++;
		j++;
	}
	url_request = string(buf);

	//reset buffer to empty, and move past space character to then read requested version
	memset(&buf, '\0', max_buf);
	j = 0;
	i++;
	//then while char not \r, store chars in buffer - this is requested version
	while (message_request[i] != '\r' && j < max_buf) {
		buf[j] = message_request[i];
		i++;
		j++;
	}
	httpNum = string(buf);
}

void ResponseHTTP::decodeURL() {
	const int max_buf = 30;	//max size of input buffer
	char buf[max_buf];		//input buffer 
	memset(&buf, '\0', max_buf);	//initialise buffer to empty
	int j = 0;				//index of where we are in input buffer
	int i = 7;				//index of where we are in request url string - start at 7 to skip "http://"

	//now get hostname
	while (url_request[i] != ':' && j < max_buf) {
		buf[j] = url_request[i];
		i++;
		j++;
	}
	host = string(buf);
	//reset buffer
	memset(&buf, '\0', max_buf);
	j = 0;
	i++;

	//now get port number
	while (url_request[i] != '/' && j < max_buf) {
		buf[j] = url_request[i];
		i++;
		j++;
	}
	port_num = atoi(buf);
	//reset buffer
	memset(&buf, '\0', max_buf);
	j = 0;
	i++;

	//now get file directory
	while (url_request[i] != '\0' && j < max_buf) {
		buf[j] = url_request[i];
		i++;
		j++;
	}
	directory = string(buf);

}
