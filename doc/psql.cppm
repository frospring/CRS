module;//全局混用头文件和模块
//module:提供c++程序和数据库的接口,提供插入，查询，删除的方式
//Description:
/*this files is build by author: tangshengqing2024051604041 at 2026-01-07*/
//email address:2052448030@qq.com
#include<libpq-fe.h>//导入postgresql的头文件
export module registrar:psql;


import std;


using std::print;


export void test()
{
    print("hello,sql\n");

}



