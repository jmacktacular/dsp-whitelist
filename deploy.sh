#!/usr/bin/env bash

CODE=dspwhitelist

cleos wallet unlock --password $(cat ~/eosio-wallet/.pass)

# Create accounts
cleos create account eosio $CODE EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV

# Setup eosio.code permissions
cleos set account permission $CODE active '
    {
        "threshold": 1,
        "keys": [{"key": "EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV","weight": 1}],
        "accounts": [{"permission": {"actor": "dspwhitelist","permission": "eosio.code"},"weight": 1}]
    }
' owner

# Deploy smart contracts
cleos set contract $CODE ./ $CODE.wasm $CODE.abi