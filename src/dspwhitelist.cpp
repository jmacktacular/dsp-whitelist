#include "dspwhitelist.hpp"


[[eosio::on_notify("dappservices::selectpkg")]]
void dspwhitelist::on_selectpkg(name owner, name provider, name service, name package)
{
   if ( provider == get_self() ) checklist( owner, service, package );
}

void dspwhitelist::add( name account, name service, name package )
{
   require_auth( get_self() );
   print("exists:", account_exists( account, service, package ), "\n");
   check( !account_exists( account, service, package ), "account already whitelisted");

   _whitelist.emplace( get_self(), [&]( auto& row ){
      row.id = _whitelist.available_primary_key();
      row.account = account;
      row.service = service;
      row.package = package;
   });
}

void dspwhitelist::remove( name account, name service, name package )
{
   require_auth( get_self() );
   check( account_exists( account, service, package ), "account does not exist");

   auto by_account = _whitelist.get_index<"byaccount"_n>();
   auto itr = by_account.find(account.value);

   for (auto itr = by_account.begin(); itr != by_account.end(); itr++) {
      if (itr->account == account && itr->service == service && itr->package == package) {
         by_account.erase(itr);
         return;
      }
   }
}

void dspwhitelist::checklist( name account, name service, name package )
{
   // ignore check is no accounts are whitelisted under that service
   if ( !service_exists( service ) ) return;
   check( account_exists( account, service, package ), "account is not whitelisted to select this DSP package");
}

/**
 * account exists = true
 * does not exists = false
 */
bool dspwhitelist::account_exists( name account, name service, name package )
{
   auto by_account = _whitelist.get_index<"byaccount"_n>();
   auto itr = by_account.find(account.value);

   // TO-DO
   // implemnt lower & upper itr to speed up account lookup
   // auto lower_itr = index.lower_bound(account.value);
   // auto upper_itr = index.upper_bound(account.value);

   for (auto itr = by_account.begin(); itr != by_account.end(); itr++) {
      if (itr->account == account && itr->service == service && itr->package == package) {
         return true;
      }
   }
   return false;
}

/**
 * service exists = true
 * does not exists = false
 */
bool dspwhitelist::service_exists( name service )
{
   auto by_service = _whitelist.get_index<"byservice"_n>();
   auto itr = by_service.find(service.value);

   return itr != by_service.end();
}
