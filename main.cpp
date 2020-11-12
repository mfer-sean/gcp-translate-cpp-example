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

  // Get token from environment var.
  // You can also do the same in your code.
  // curl equivalent:
  // curl -s "http://metadata.google.internal/computeMetadata/v1/instance/service-accounts/default/token" -H "Metadata-Flavor: Google" | jq -r .access_token
  // GCP access tokens expire after 60 minutes.
  char * gcp_token_val = getenv( "GCP_TOKEN" );
  cout << "GCP Token: " << gcp_token_val << endl;


  // initialize RestClient
  RestClient::init();
  
  // get a connection object to start configuring our request
  RestClient::Connection* conn = new RestClient::Connection("https://translation.googleapis.com/language/translate");  
  
  //begin set headers
  RestClient::HeaderFields headers;

  //set content type header
  headers["Content-Type"] = "application/json; charset=utf-8";

  //set auth header
  std::string authString; 
  authString.append("Bearer ");
  authString.append(gcp_token_val);
  headers["Authorization"] = authString;

  //finish set headers
  conn->SetHeaders(headers);

  // prep request body
  std::string request_body = "{\"q\": [\"Hello world\", \"My name is Jeff\"],\"target\": \"de\"}";
  cout <<  endl << "Translate request body: \n" << request_body << endl << endl;

  // Send the request to Google servers
  RestClient::Response r = conn->post("/v2", request_body);

  // output request info
  cout << "Translate request response_body: " << endl;
  cout << r.body << endl;

  // output response info
  cout << "Translate request response_code: " << endl;
  cout << r.code << endl;

  // deinit RestClient. After calling this you have to call RestClient::init()
  // again before you can use it
  RestClient::disable();

  cout << ">>>> C++ End!\n" ; 
}
