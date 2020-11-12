#!/bin/bash
echo ">> bash script start"
g++ -lrestclient-cpp -lcurl main.cpp
export GCP_TOKEN="$(gcloud auth application-default print-access-token)" 
./a.out 
echo ">> bash script end"