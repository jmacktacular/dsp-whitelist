#!/usr/bin/env bash

CODE=dspwhitelist

eosio-cpp -abigen -R resource -contract $CODE -o $CODE.wasm src/$CODE.cpp -I include
