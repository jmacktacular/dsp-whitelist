#pragma once

#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract("dspwhitelist")]] dspwhitelist : public contract {
public:
   using contract::contract;

    /**
     * Construct a new contract given the contract name
     *
     * @param {name} receiver - The name of this contract
     * @param {name} code - The code name of the action this contract is processing.
     * @param {datastream} ds - The datastream used
     */
    dspwhitelist( name receiver, name code, eosio::datastream<const char*> ds )
        : contract( receiver, code, ds ),
            _whitelist( get_self(), get_self().value )
    {}

   /**
    * Notify dspwhitelist contract when selectpkg action occurs
    *
    * Staking is unavailable if account did not selectpkg
    */
   [[eosio::on_notify("dappservices::selectpkg")]]
   void on_selectpkg(name owner, name provider, name service, name package);

   /**
    * Add - adds user to whitelist table
    *
    * @param {name} account - EOSIO account name to whitelist
    * @param {name} service - DSP service (ex: ipfsservic1)
    * @param {name} package - DSP package name (ex: package1)
    */
   [[eosio::action]]
   void add( name account, name service, name package );

   /**
    * Remove - removes user from whitelist table
    *
    * @param {name} account - EOSIO account name to whitelist
    * @param {name} service - DSP service (ex: ipfsservic1)
    * @param {name} package - DSP package name (ex: package1)
    */
   [[eosio::action]]
   void remove( name account, name service, name package );

   /**
    * checklist - checks if account name is authorized to use this package
    *
    * @param {name} account - EOSIO account name to whitelist
    * @param {name} service - DSP service (ex: ipfsservic1)
    * @param {name} package - DSP package name (ex: package1)
    */
   [[eosio::action]]
   void checklist( name account, name service, name package );

private:
   /**
    * TABLE `whitelist`
    *
    * @example
    *
    * {
    *   "id": 0,
    *   "account": "myaccount",
    *   "service": "ipfsservice1",
    *   "package": "package1"
    * }
    */
   struct [[eosio::table("whitelist")]] whitelist_row {
      uint64_t       id;
      name           account;
      name           service;
      name           package;

      uint64_t primary_key() const { return id; }
      uint64_t by_account() const { return account.value; }
      uint64_t by_service() const { return service.value; }
   };

   typedef eosio::multi_index<
      "whitelist"_n, whitelist_row,
      indexed_by<"byaccount"_n, const_mem_fun<whitelist_row, uint64_t, &whitelist_row::by_account>>,
      indexed_by<"byservice"_n, const_mem_fun<whitelist_row, uint64_t, &whitelist_row::by_service>>
   > whitelist_table;

   // local instances of the multi indexes
   whitelist_table            _whitelist;

   // private methods
   bool account_exists( name account, name service, name package );
   bool service_exists( name service );
};

