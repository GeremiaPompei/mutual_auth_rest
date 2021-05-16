#include <stdlib.h>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

using namespace std;
using namespace httplib;

void startServerSSL() 
{
    SSLServer svrs("../server/server-crt.pem", "../server/server-key.pem", "../rootCA/rootCA-crt.pem");
    svrs.Get("/", [](const Request &req, Response &res) {
        res.set_content("Successful! You are in!", "text/plain");
    });
    svrs.listen("0.0.0.0", 4443);
}
    
void startServer() 
{
    Server svr;
    svr.Get("/", [](const Request &req, Response &res) {
        res.set_content("<a href='https://0.0.0.0:4443/'>Enter SSL</a>", "text/html");
    });
    svr.listen("0.0.0.0", 8080);
}

void startClientSSL(int sec) 
{
    while(true) {
        sleep(sec);
        Client cli("https://0.0.0.0:4443", "../client/client-crt.pem", "../client/client-key.pem");
        cli.set_ca_cert_path("../rootCA/rootCA-crt.pem");
        cli.enable_server_certificate_verification(false);
        auto res = cli.Get("/");
        cout << "https: status = " + to_string(res->status) + " - body = " + res->body << endl;
    }
}

void startClient(int sec) 
{
    while(true) {
        sleep(sec);
        Client cli("http://0.0.0.0:8080");
        auto res = cli.Get("/");
        cout << "http: status = " + to_string(res->status) + " - body = " + res->body << endl;
    }
}

int main(int argc, char** argv) {
    thread serverSSL(startServerSSL), server(startServer), clientSSL(startClientSSL, 2), client(startClient, 2);
    serverSSL.join();
    server.join();
    clientSSL.join();
    client.join();
}
