#!/usr/bin/env bash

CODE=dspwhitelist
USER1=bob
USER2=alice

# add remove multiple accounts
cleos -v push action $CODE add '["alice", "ipfsservice1","package1"]' -p $CODE
cleos -v push action $CODE add '["bob", "ipfsservice1","package1"]' -p $CODE
cleos -v push action $CODE remove '["bob", "ipfsservice1","package1"]' -p $CODE
cleos -v push action $CODE remove '["alice", "ipfsservice1","package1"]' -p $CODE

# check whitelist (pass)
cleos -v push action $CODE add '["bob", "ipfsservice1","package1"]' -p $CODE
cleos -v push action $CODE checklist '["bob", "ipfsservice1","package1"]' -p $CODE

# check whitelist (fail)
cleos -v push action $CODE checklist '["alice", "ipfsservice1","package1"]' -p $CODE

# check whitelist from no-whitelisted services (pass)
cleos -v push action $CODE checklist '["alice", "randomservice","package1"]' -p $CODE
