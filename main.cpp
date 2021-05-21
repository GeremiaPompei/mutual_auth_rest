#include <stdlib.h>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

using namespace std;
using namespace httplib;

void startServerSSL() 
{
    SSLServer svrs("../server/server-crt.pem", "../server/server-key.pem", "../rootCA/rootCA-crt.pem");
    svrs.Post("/", [](const Request &req, Response &res) {
        string str;
        if(req.body == "{\"password\": \"secret\"}")
            str = "success";
        else
            str = "error";
        res.set_content("{\"result\": \"" + str + "\"}", "application/json");
    });
    svrs.Get("/", [](const Request &req, Response &res) {
        res.set_content("{\"result\": \"success\"}", "application/json");
    });
    svrs.Delete("/", [](const Request &req, Response &res) {
        res.set_content("{\"result\": \"success\"}", "application/json");
    });
    svrs.Put("/", [](const Request &req, Response &res) {
        string str;
        if(req.body == "{\"password\": \"secret\"}")
            str = "success";
        else
            str = "error";
        res.set_content("{\"result\": \"" + str + "\"}", "application/json");
    });
    svrs.set_error_handler([](const Request &req, Response &res) {
        res.set_content("{\"result\": \"error\"}", "application/json");
    });
    cout << "HTTPS server start!" << endl;
    svrs.listen("0.0.0.0", 4443);
}
    
void startServer() 
{
    Server svr;
    svr.Get("/", [](const Request &req, Response &res) {
        res.set_content("<a href='https://0.0.0.0:4443/'>Enter SSL</a>", "text/html");
    });
    cout << "HTTP server start!" << endl;
    svr.listen("0.0.0.0", 8080);
}

void startPing(int sec) 
{
    while(sec > 0) {
        sleep(sec);
        Client cli("https://0.0.0.0:4443", "../client/client-crt.pem", "../client/client-key.pem");
        cli.set_ca_cert_path("../rootCA/rootCA-crt.pem");
        cli.enable_server_certificate_verification(false);
        auto res = cli.Get("/");
        cout << "https get : status = " + to_string(res->status) + " - body = " + res->body << endl;
        res = cli.Delete("/");
        cout << "https delete : status = " + to_string(res->status) + " - body = " + res->body << endl;
        string body = "{\"password\": \"secret\"}";
        res = cli.Post("/", body.c_str(), "application/json");
        cout << "https post : status = " + to_string(res->status) + " - body = " + res->body << endl;
        res = cli.Put("/", body.c_str(), "application/json");
        cout << "https put : status = " + to_string(res->status) + " - body = " + res->body << endl;
    }
}

int main(int argc, char** argv) {
    int sec = 2;
    if(argc > 1) sec = atoi(argv[1]);
    thread serverSSL(startServerSSL), server(startServer), pingSSL(startPing, sec);
    serverSSL.join();
    server.join();
    pingSSL.join();
}
