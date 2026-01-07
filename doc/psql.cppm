module;//全局混用头文件和模块
//module:提供c++程序和数据库的接口,提供插入，查询，删除的方式,使用sql语句调用对应的函数连接到数据库接口
//Description:
/*this files is build by author: tangshengqing2024051604041 at 2026-01-07*/
//email address:2052448030@qq.com
#include<libpq-fe.h>//导入postgresql的头文件
export module registrar:psql;


import std;


using std::print;



//创建接口类
export class Psql{
    friend void sqlFuncsystem();

public:
    //创建连接，反馈连接
    Psql();

    static Psql& getControlsql();//获取静态管理对象

    void selectTable(const char *input);

    void insertTable(const char *input);

    void dropTable(const char *input);

private:
    const char *constr;//连接到的端口
    PGconn* conclass;//连接端口对象

};


//初始化连接
Psql::Psql():constr("host=localhost dbname=postgres user=postgres password=root port=5432"),conclass(nullptr){
    conclass=PQconnectdb(constr);//连接到数据库

    //查看是连接成功，否则终止程序
    if(PQstatus(conclass)!=CONNECTION_OK)
    {
        print("connect to psql error , pogress will exit \n");
        std::exit(0);
    }
    print("...connect database  Sucessfully!!\n");
    print("==== connect information ====\n");
    print("\tdatabaseName: {}\n",PQdb(conclass));
    print("\tloginUser: {}\n",PQuser(conclass));

}

Psql& Psql::getControlsql(){
    static Psql ps;

    return ps;
}//获取静态管理对象


//查询函数接口
void Psql::selectTable(const char *input){
    PGresult *res=PQexec(conclass,input);//查询获取对象指针

    //查询成功则会输出信息
    if(PQresultStatus(res)==PGRES_TUPLES_OK)
    {
        int row=PQntuples(res);
        int cols = PQnfields(res);

        for(int j=0;j<cols;j++)
        {
               print("===========",input);
        }

        print("\n");//换行


        //打印列名
        for(int j=0;j<cols;j++)
        {
              print("\t{} ",PQfname(res,j));//获取到列索引的列名字
        }

        print("\n");//换行

        for(int i=0;i<row;i++){
            for(int j=0;j<cols;j++)
            {
                const char*va=PQgetvalue(res,i,j);//获取i行0列的信息
                print("\t{} ",va);
            }
            print("\n");
        }


        for(int j=0;j<cols;j++)
        {
               print("===========",input);
        }

        print("\n");//换行

    }else{
       print("Query failed: {}\n", PQresultErrorMessage(res));//打印具体错误
    }


}

//增加函数接口
void Psql::insertTable(const char *input){
      PGresult *res=PQexec(conclass,input);//查询获取对象指针
      if(PQresultStatus(res)==PGRES_COMMAND_OK)
      {
          print("---Insert sucessfully {}\n",PQcmdTuples(res));
      }else{
          print("---Insert error {}\n",PQresultErrorMessage(res));
      }


}

//删除函数接口
void Psql::dropTable(const char *input){
     PGresult *res=PQexec(conclass,input);
     if(PQresultStatus(res)==PGRES_COMMAND_OK)
     {
         print("---delete sucessfully {}\n",PQcmdTuples(res));
     }else{
         print("---delete error {}\n",PQresultErrorMessage(res));
     }


}


//测试函数
export void sqlFuncsystem()
{

    Psql &ps=Psql::getControlsql();
/*
    ps.insertTable("insert into student (id,name,major,maxcredits) values(101,'张三','computer','88')");
    ps.insertTable("insert into student (id,name,major,maxcredits) values(102,'李四','math','91')");
    ps.insertTable("insert into student (id,name,major,maxcredits) values(103,'王五','physics','85')");
    ps.insertTable("insert into student (id,name,major,maxcredits) values(104,'赵六','chemistry','92')");
    ps.insertTable("insert into student (id,name,major,maxcredits) values(105,'孙七','biology','89')");
    //ps.dropTable("delete from student where id = 2 ");
*/
    ps.selectTable("select * from student");


}



