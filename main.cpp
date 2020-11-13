#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>     /* getenv */
#include <stdint.h>
#include <string>
#include "restclient-cpp/connection.h"
#include "restclient-cpp/restclient.h"
#include "json.hpp" ///<nlohmann/json.hpp>

using namespace std;

// If running on GCP, get token for current Service Account, and return token
// curl equivalent:
// curl -s "http://metadata.google.internal/computeMetadata/v1/instance/service-accounts/default/token" -H "Metadata-Flavor: Google" | jq -r .access_token
// FYI GCP access tokens expire after 60 minutes.
std::string getToken() {
  // initialize RestClient
  RestClient::init();
  
  // get a connection object to start configuring our request
  RestClient::Connection* conn = new RestClient::Connection("http://metadata.google.internal/computeMetadata/v1/instance/service-accounts/default");  
  
  //begin set headers
  RestClient::HeaderFields headers;
  //set content type header
  headers["Metadata-Flavor"] = "Google";  
  //finish set headers
  conn->SetHeaders(headers);

  // Send the request to Google servers
  RestClient::Response r = conn->get("/token");

  using json = nlohmann::json;

  json j = json::parse(r.body);

  std::string token = j["access_token"];

  // deinit RestClient. After calling this you have to call RestClient::init()
  // again before you can use it
  RestClient::disable();

  return token;
}

// given token and translate request body, send out translate request.
void translate (std::string token, std::string request_body) {
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
  authString.append(token);
  headers["Authorization"] = authString;

  //finish set headers
  conn->SetHeaders(headers);

  // prep request body
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

}



int main(

) {
  cout << ">>>> C++ Start!\n" ; 

  // Get token from environment var.
  // You can also create token using http request in your c++ code.
  // curl equivalent:
  // curl -s "http://metadata.google.internal/computeMetadata/v1/instance/service-accounts/default/token" -H "Metadata-Flavor: Google" | jq -r .access_token
  // GCP access tokens expire after 60 minutes.
  std::string gcp_token_val = getenv( "GCP_TOKEN" );
  

  // If there is no token environment variable set from run.sh, get token ourselves.
  if (gcp_token_val.empty()) {
    gcp_token_val = getToken();
  }

  cout << "GCP Token: " << gcp_token_val << endl;

  std::string request_body = "{\"q\": [\"Hello world\", \"My name is Jeff\"],\"target\": \"de\"}";
  translate(gcp_token_val, request_body);

  cout << ">>>> C++ End!\n" ; 
}
