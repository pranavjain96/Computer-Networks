#include "request.h"
#include <sstream>
using namespace std;
Request_HTTP::Request_HTTP() {
    //default error code of not ok
    method_request = "GET";
    url_request = "http://localhost:4000/index.html";
    httpNum_request = "HTTP/1.0";
}

void Request_HTTP::newMethod(string method) {
    method_request = method;
}

void Request_HTTP::newURL(string url) {
    url_request = url;
}

void Request_HTTP::newhttpNum(string httpNum) {
    httpNum_request= httpNum;
}

void Request_HTTP::newMessage() {
    stringstream message_new;
    message_new << method_request  << " " << url_request << " " << httpNum_request << "\r\n" << "\r\n";
    message_request = message_new.str();
}
