#pragma once

#include <eosio/eosio.hpp>

using namespace eosio;

CONTRACT dspwl : public contract {
   public:
      using contract::contract;

      //We only watch for selectpkg because you can't be staked/unstaked if a package isn't selected
      [[eosio::on_notify("dappservices::selectpkg")]]
      void on_selectpkg(name owner, name provider, name service, name package);
      
      ACTION addwl( name account );
      ACTION remwl( name account );

      void checklist( name account );
   private:

      TABLE whitelist_tbl {
         name  account;
         uint64_t primary_key()const { return account.value; }
      };

      typedef eosio::multi_index< "whitelist"_n, whitelist_tbl> whitelist_mi;
};

