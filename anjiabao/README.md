此项目作为智能合约开发人员开发智能合约的样例和参考。

# 功能
为拥有区块链账户的众多用户提供通信录存储服务。


# 项目文件
## 代码源文件
addressbook.hpp  
addressbook.cpp  
## 李嘉图合约描述文件
addressbook.clauses.md 合约总体的约定条款  
addressbook.contracts.md 合约action的约定条款  
## 项目构建配置文件
Makefile 编译合约的命令配置，构建工具make使用它来编译构建项目文件。  



# 开发编译环境
代码完成后需要编译，编译需要一个专门的合约编译工具CDT(Contract Development Tools).  
可以使用官方已有的docker镜像（boscore/cdt:v3.0.2）来构建开发环境  
本样例中，有一个脚本文件runcdt.sh.  
在合约代码根目录下执行下面语句，即可进入编译环境。

```
./runcdt.sh
```
runcdt.sh会从官方的docker仓库自动下载CDT镜像到本地仓库，并进入容器（如果你的主机不能连网，可自行下载镜像包，然后docker load到本地仓库）。
然后，就可以继续build合约。



# Build合约
构建工具为make，make使用Makefile来构建。  
执行：    

```
$make
```
生成的可执行合约文件在build目录下： 
addressbook.abi
addressbook.wasm

# Actions
action是交易调用的函数   
## 添加联系人
ACTION addressbook::add( name account, string name, uint8_t age,  uint64_t phonenumber, string address )
## 删除联系人
ACTION addressbook::remove(name account, uint64_t id)
## 修改联系人
ACTION addressbook::update(name account, uint64_t id, string name, uint8_t age,  uint64_t phonenumber, string address)
- account: 为交易发起人(actor)的账户、

## 清空联系人
ACTION clean(name account, int32_t batchsize, string confirm);
## 系统action，合约账户不再使用时，用于清理记录，回收内存。
ACTION syscleantab(name table, std::vector scope, int32t batchsize, string confirm);      
ACTION sysclean(int32t batchsize, string confirm);   
syscleantab:必须实现,按照表的名字和scope清除表数据  
sysclean:可选，尽量实现。清除合约中所有表数据。
- table：表名  
- scope:数组，表的范围，一次可以指定多个范围。  
- batchsize: 最多清除的记录数。适当设置，是为了防止删除太多的表记录执行会超时失败。记录非常多时，可以多次调用，分批删除表记录。  
- confirm: 执行确认码，为合约账户的名字，降低误操作的可能性。  

# 交易与查询范例
```
alias cl='cleos --url http://127.0.0.1:3921  --wallet-url http://127.0.0.1:3923'
其中：
  -u,--url TEXT=http://127.0.0.1:8888/
                              the http/https URL where nodeos is running
  --wallet-url TEXT=unix:///home/zhanghan/eosio-wallet/keosd.sock
                              the http/https URL where keosd is running
```

## 发交易
```
cl push action ab add '["ab.test.1", "zhangsan", 18, 13811094444,  "北京通州"]' -p ab.test.1@default
                |         |                                                     |
		合约账户名 交易发起账户                                     交易发起账户权限
```
 -p,--permission TEXT ...    An account and permission level to authorize, as in 'account@permission'

## 查询
```
$cl get table ab ab.test.1 addressbooks
               |   |            |——表名
	           |   之前的交易发起人账户
	           合约账户 
---------------------
{
  "rows": [{
      "id": 0,
      "name": "zhangsan",
      "age": 18,
      "phonenumber": "13811094444",
      "address": "北京通州"
    }
  ],
  "more": false
}
```

# 系统action  
有两个action是为系统管理员提供的，当合约不再使用的时候，区块链系统管理员用来清空表的数据，回收内存。  
```
# 测试链账户
- 合约账户 ab
- 用户账户 ab.test.1  权限:default 
```


# 资源
[开发人员门户](https://developers.eos.io)   
[eosio.cdt开发手册 v1.6](https://developers.eos.io/manuals/eosio.cdt/v1.6/index)

