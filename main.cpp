#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>     /* getenv */
#include <stdint.h>
#include <string>
#include "restclient-cpp/connection.h"
#include "restclient-cpp/restclient.h"


using namespace std;

int main(

) {
  cout << ">>>> C++ Start!\n" ; 


  // initialize RestClient
  // RestClient::init();
  
  char * gcp_token_val = getenv( "GCP_TOKEN" );
  cout << "GCP Token: " << gcp_token_val << endl;


  // initialize RestClient
  RestClient::init();
  // get a connection object
  RestClient::Connection* conn = new RestClient::Connection("https://translation.googleapis.com/language/translate");  
  

  // set headers
  RestClient::HeaderFields headers;
  headers["Content-Type"] = "application/json; charset=utf-8";


  std::string authString; //= new char[1000];
  authString.append("Bearer ");
  authString.append(gcp_token_val);

  headers["Authorization"] = authString;
  conn->SetHeaders(headers);
  // authString.append("");


  RestClient::Response r = conn->post("/v2", "{\"q\": [\"Hello world\", \"My name is Jeff\"],\"target\": \"de\"}");

  cout << "Translate request response_body: " << endl;
  cout << r.body << endl;

  cout << "Translate request response_code: " << endl;
  cout << r.code << endl;

  RestClient::disable();

  cout << ">>>> C++ End!\n" ; 
}
