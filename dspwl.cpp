#include "dspwl.hpp"


void dspwl::on_selectpkg(name owner, name provider, name service, name package) {
   if(provider == _self) {
      checklist(owner);
   }
}

void dspwl::addwl( name account )
{
   require_auth(_self);
   whitelist_mi whitelist( _self, _self.value );
   auto row = whitelist.find( account.value );
   check(row == whitelist.end(), "This account is already whitelisted");
   whitelist.emplace( _self, [&]( auto& a ){
      a.account = account;
   });
}

void dspwl::remwl( name account )
{
   require_auth(_self);
   whitelist_mi whitelist( _self, _self.value );
   auto row = whitelist.find( account.value );
   check(row != whitelist.end(), "This account is not whitelisted");
   whitelist.erase(row);
}

void dspwl::checklist( name account ) {
   whitelist_mi whitelist( _self, _self.value );
   const auto& row = whitelist.get( account.value, "Your account is not whitelisted");   
}

