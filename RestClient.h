#include <Arduino.h>
#include "Client.h"


class RestClient {

  public:
    RestClient(Client& netClient, const char* _host);
    RestClient(Client& netClient, const char* _host, int _port);

    //Generic HTTP Request
    int request(const char* method, String path, String body);
    // Set a Request Header
    void setHeader(String);
    // Set Content-Type Header
    void setContentType(String);

    // GET path
    int get(const char*);

    // POST path and body
    int post(const char* path, const char* body);

    // PUT path and body
    int put(const char* path, const char* body);

    // DELETE path
    int del(const char*);
    // DELETE path and body
    int del(const char*, const char*);
    // get HTTP response:
    String readResponse(){ return responseBody;};
    // TO DO: add cookie functions

  private:
    Client* client;
    int getResponse();
    // void write(const char*);
    const char* host;
    int port;
    int num_headers;
    String headers[10];
	  String contentType;
    String responseBody;      // body of the HTTP response
    long requestStart;        // time the request started
    int timeout;              // timeout to avoid blocking
};
