#include <Arduino.h>
#include "Client.h"


class RestClient {

  public:
    RestClient(Client& netClient, const char* _host);
    RestClient(Client& netClient, const char* _host, int _port);

    //Generic HTTP Request
    int request(const char* method, String path, String body);
    // Set a Request Header
    void setHeader(String header);
    // Set Content-Type Header
    void setContentType(String contentTypeValue);

    // GET path
    int get(String path);
    // POST path and body
    int post(String path, String body);

    // PUT path and body
    int put(String path, String body);

    // DELETE path
    int del(String path);
    // DELETE path and body
    int del(String path, String body);
    String readResponse() {return responseBody;};

  private:
    Client* client;
    int getResponse();
    const char* host;
    int port;
    int num_headers;
    String headers[10];
	  String contentType;
    String responseBody;
    int timeout;
    long requestStart;
};
