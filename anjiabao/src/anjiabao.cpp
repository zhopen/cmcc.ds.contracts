#include "anjiabao.hpp"
using namespace eosio;

ACTION anjiabao::groupadd(name account, group_param param) {
   require_auth( account );
   groups_t groups(_self,  _self.value);
   groups.emplace(_self,
                        [&]( auto& row ){
                           row.id          = anjiabaos.available_primary_key();
                           row.name        = param.prod_offer_id;
                           row.age         = param.poidlabel;
                           row.phonenumber = param.hash_phone;
                           row.group_state = param.group_state;
                           row.update_date = param.update_date;
                           row.address     = param.customer_locate;
                           row.created_date= param.created_date;
                        }
                     );
}

ACTION anjiabao::groupremove(name account, uint64_t id) {
   require_auth(account);
   groups_t groups(_self, _self.value);
   auto itr = groups.find(id);
   anjiabaos.erase(itr);
}

ACTION anjiabao::groupupdate(name account, group_param param) {
   require_auth(account);
   groups_t groups(_self, _self.value);
   auto itr = groups.find(id);
   anjiabaos.modify( itr,
		                _self,
                        [&]( auto& row ){
						   row.name        = param.prod_offer_id;
						   row.age         = param.poidlabel;
						   row.phonenumber = param.hash_phone;
						   row.group_state = param.group_state;
						   row.update_date = param.update_date;
						   row.address     = param.customer_locate;
						   row.created_date= param.created_date;
                        }
               );
}

ACTION anjiabao::groupclean( name account, int32_t batchsize, string confirm) {
	require_auth(account);

	check(confirm=="131313", "Confirm code is false!");
	if(batchsize == 0)
		batchsize =  1000;

	int32_t count=0;
	groups_t groups(_self, _self.value);
	auto itr = groups.begin();
	auto end = groups.end();
	while(itr != end) {
	   itr = groups.erase(itr);
	   count++;
	   if(batchsize < 0)
		   continue;
	   if(count >= batchsize)
		   break;
	}
}

ACTION anjiabao::memberadd(name account, group_param param) {
   require_auth( account );
   members_t members(_self,  _self.value);
   members.emplace(_self,
                        [&]( auto& row ){
                           row.id          = anjiabaos.available_primary_key();
                           row.name        = param.prod_offer_id;
                           row.age         = param.poidlabel;
                           row.phonenumber = param.hash_phone;
                           row.group_state = param.group_state;
                           row.update_date = param.update_date;
                           row.address     = param.customer_locate;
                           row.created_date= param.created_date;
                        }
                     );
}

ACTION anjiabao::memberremove(name account, uint64_t id) {
   require_auth(account);
   members_t members(_self, _self.value);
   auto itr = members.find(id);
   anjiabaos.erase(itr);
}

ACTION anjiabao::memberupdate(name account, group_param param) {
   require_auth(account);
   members_t members(_self, _self.value);
   auto itr = members.find(id);
   members.modify( itr,
		                _self,
                        [&]( auto& row ){
						   row.name        = param.prod_offer_id;
						   row.age         = param.poidlabel;
						   row.phonenumber = param.hash_phone;
						   row.group_state = param.group_state;
						   row.update_date = param.update_date;
						   row.address     = param.customer_locate;
						   row.created_date= param.created_date;
                        }
               );
}

ACTION anjiabao::memberclean( name account, int32_t batchsize, string confirm) {
	require_auth(account);

	check(confirm=="131313", "Confirm code is false!");
	if(batchsize == 0)
		batchsize =  1000;

	int32_t count=0;
	members_t members(_self, _self.value);
	auto itr = members.begin();
	auto end = members.end();
	while(itr != end) {
	   itr = members.erase(itr);
	   count++;
	   if(batchsize < 0)
		   continue;
	   if(count >= batchsize)
		   break;
	}
}

//清除所有的表的所有数据
ACTION anjiabao::sysclean(int32_t batchsize, string confirm) {
	require_auth(permission_level(_self, name("active")));
    //TODO: 清除所有的表
	//...
}

//按照表清除表数据
ACTION anjiabao::syscleantab(name table, std::vector<string> scope, int32_t batchsize, string confirm) {
	require_auth(permission_level(_self, name("active")));

    check(name(confirm)==_self, "Confirm code is false!");

    int32_t count=0;
	if(batchsize == 0)
		batchsize =  1000;

	auto scopeitr=scope.begin();
	auto scopeend=scope.end();
	while(scopeitr != scopeend) {
		if(table == name("groups")) {
			groups_t groups(_self, name(*scopeitr++).value);
			auto itr = groups.begin();
			auto end = groups.end();
			while(itr != end) {
			   itr = groups.erase(itr);
			   count++;
			   if(batchsize < 0)
				   continue;
			   if(count >= batchsize)
				   return;
			}
		} else if(table == name("members")) {
			members_t members(_self, name(*scopeitr++).value);
			auto itr = members.begin();
			auto end = members.end();
			while(itr != end) {
			   itr = members.erase(itr);
			   count++;
			   if(batchsize < 0)
				   continue;
			   if(count >= batchsize)
				   return;
			}
		}

	}
}
