#!/bin/bash
echo ">> bash script start"

# Compile main.cpp into executable, also linking curl and restclient libraries
g++ -std=c++11 -lrestclient-cpp -lcurl main.cpp

# Get token for current Service Account, and save as evironment variable - will be used by executable.
export GCP_TOKEN="$(gcloud auth application-default print-access-token)" 
# You can also do the same in your code.
# curl equivalent:
# curl -s "http://metadata.google.internal/computeMetadata/v1/instance/service-accounts/default/token" -H "Metadata-Flavor: Google" | jq -r .access_token
# GCP access tokens expire after 60 minutes.

#run compiled cpp executable
./a.out 

echo ">> bash script end"