#include <eosio/eosio.hpp>
using namespace eosio;
using std::string;

//合约类，类名与文件名一致
CONTRACT addressbook : public eosio::contract
{
	public:
		using contract::contract;

	private:
		//表对象的类型（即表中的row/record）
		TABLE addressbook_t   
		{
		uint64_t id;
		string   name;
		uint8_t  age;
		uint64_t phonenumber;
		string   address;

		uint64_t primary_key() const {return id;}  //主键（primary key），但必须是唯一的无符号64位整型（uint64_t）
		uint64_t by_phonenumber() const {return phonenumber;}
		};


	public:
		//typedef：用来为复杂的类型声明定义简单的别名
		//Multi-Index模板类，是EOS提供的访问数据库的C++接口，使智能合约能够读取和修改EOS数据库中的数据
		//multi_index表的名称，最长12个字符，只能由小写字母、数字1-5、“.”组成。
		//第一个参数是表名，第二个参数是表对象的类型，其余为可变参数Indices（二级索引），二级索引的数量不能超过16个。
		//索引名：最多13个字符，是小写字母、0-5、“.”
		//.索引支持的格式如下：uint64_t, uint128_t, double, long double,eosio::checksum256
		//CRUD函数:
		//	增：emplace
		//	删：erase
		//	改：modify
		//	查：get/find
		typedef eosio::multi_index<name("addressbooks"), addressbook_t,
								 indexed_by<name("phonenumber"), const_mem_fun<addressbook_t, uint64_t, &addressbook_t::by_phonenumber>>
								>addressbooks_t;

		ACTION add( name account, string name, uint8_t age,  uint64_t phonenumber, string address );
		ACTION remove(name account, uint64_t id);
		ACTION update(name account, uint64_t id, string name, uint8_t age,  uint64_t phonenumber, string address);
		ACTION clean(name account, int32_t batchsize, string confirm);
		ACTION syscleantab(name table, std::vector<string> scope, int32_t batchsize, string confirm);
		ACTION sysclean(int32_t batchsize, string confirm);

};

//--合约的命名规则--
//-Action名
//	长度要小于等于12
//	字符范围12345abcdefghijklmnopqrstuvwxyz
//-Table名
//	最多只能包含12个字母字符，
//	字符范围12345abcdefghijklmnopqrstuvwxyz.
//-表Stuct体名与字段名
//	结构体名长度都要小于等于13
//  下面的字段名字都是合法的。
//	TABLE CERTIFICATE
//	{
//		uint64_t id;
//		uint64_t validTime;
//		string cert;
//      string node_name;
//	};
//
//-类名
//	最多只能包含12个字母字符，小写，类名要和文件名一样
//-Scope名
//	<=13个字符
//	可用字符：[a-z1-5.]
//	.不能在最后