#!/bin/bash

# This script was executed from inside the cas directory seen in the C++ code above

# Generate root CA
echo "Generating rootCA"
mkdir rootCA
cd rootCA
openssl genrsa -out rootCA-key.pem 4096
openssl req -x509 -new -nodes -key rootCA-key.pem -subj "/C=NL/ST=UTRECHT/O=Some company/CN=rootca" -sha256 -days 1024 -out rootCA-crt.pem
cd ..

# Generate server certificate
echo "\nGenerating server certificate"
mkdir server
cd server
openssl genrsa -out server-key.pem 2048
openssl req -new -sha256 -key server-key.pem -subj "/C=NL/ST=UTRECHT/O=Some company/CN=Some ip" -out server-csr.pem
openssl x509 -req -in server-csr.pem -CA ../rootCA/rootCA-crt.pem -CAkey ../rootCA/rootCA-key.pem -CAcreateserial -out server-crt.pem -days 500 -sha256
cd ..

# Generate client certificate
echo "\nGenerating client certificate"
mkdir client
cd client
openssl genrsa -out client-key.pem 2048
openssl req -new -sha256 -key client-key.pem -subj "/C=NL/ST=UTRECHT/O=Some company/CN=Some ip" -out client-csr.pem
openssl x509 -req -in client-csr.pem -CA ../rootCA/rootCA-crt.pem -CAkey ../rootCA/rootCA-key.pem -CAcreateserial -out client-crt.pem -days 500 -sha256
openssl pkcs12 -export -clcerts -in client-crt.pem -inkey client-key.pem -out client.p12 -password pass:
cd ..
