module;//全局混用头文件和模块
//module:提供c++程序和数据库的接口,提供插入，查询，删除的方式,使用sql语句调用对应的函数连接到数据库接口
//Description:
/*this files is build by author: tangshengqing2024051604041 at 2026-01-07*/
//email address:2052448030@qq.com
#include<libpq-fe.h>//导入postgresql的头文件
export module registrar:psql;

// ---------student --datatable: major1: C_programs , major2: Data_Structure  major3:Advanced_Math 以便于用来对数据库的列进行操作



import std;


using std::print;
using std::string;


//常用数据库sql语句

//------------------------------------学生类sql
const string showStudentTableStr="select * from student ";

const string showStudentTableStrOrdeBy="select * from Student Order BY id ASC";//正序查询学生表

//------------------------------------老师类sql
const string showTeacherTableStr="select * from teacher ";

//-------------------------------------课程类sql
const string showCourseTableStr="select * from course ";

//-------------------------------------学生选课课程关系sql

const string showStudentRollCourseTableStr="select * from studentcourse ";//查看关系表
const string updateStudentTableStr="update  studentcourse SET ";



//------------------------------------老师学生关系sql

const string showCourseHaveStudentTableStr="select * from teacherstudent";












//为不同用户设置不同的权限
export typedef enum User{
    Teacher,
    Student,

};




//--------------------------------------------------------------接口类声明----------------------------------------------
//创建接口类
export class Psql{
    friend void sqlFuncsystem(User who);

public:
    //创建连接，反馈连接
    Psql();

    static Psql& getControlsql();//获取静态管理对象

    void selectTable(const char *input);//查的接口

    void insertTable(const char *input);//插入接口

    void dropTable(const char *input);//删除接口


private:
    const char *constr;//连接到的端口
    PGconn* conclass;//连接端口对象

};



//--------------------------------------------------------------工具函数声明----------------------------------------------
string sqlselectSqlConnStr(const string &sqlcon,const string &id);//拼接查询sql语句返回where限制的sql语句，更精确的查找或者删除，
string sqlupdatetSqlConnStr(const string &sqlcoq,const string &id,bool roll);//拼接更新sql语句SET限制的sql语句,bool用来判断是选还是退（取消选则的课）

//设置登陆对象的函数方法，设置权限不同
void TeacherControl(Psql &ps);//老师登陆
void StudentControl(Psql &ps);//学生登陆



//选和退选课程的操作，传输课程名字，映射到对应的列上面去，roll=true为选课，roll=false为退课
void StudentWithCourse(Psql &ps,const string& Notin,const string& id,bool roll);




//------------------------------------------------------------------数据库和程序的命令接口实现

//初始化连接
Psql::Psql():constr("host=localhost dbname=postgres user=postgres password= port=5432"),conclass(nullptr){
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
          print("---sucessfully {}\n",PQcmdTuples(res));
      }else{
          print("---error {}\n",PQresultErrorMessage(res));
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




//--------------------------------------------------------------------用户操作函数实现


string sqlselectSqlConnStr(const string &sqlcon,const string &id){
            string Add = sqlcon+" where id ="+id;
            return Add;
}//拼接常用sql语句返回where限制的sql语句，更精确的查找或者删除，



string sqlupdatetSqlConnStr(const string &sqlcon,const string& Notin,const string &id,bool roll){

    string Add;
    if(Notin=="C_programs")
    {
        if(roll==false)
        {
             Add = sqlcon+" major1 = null "+" where id ="+id;//对应c课程退选
        }else{
            Add = sqlcon+" major1 = 'C_programs' "+" where id ="+id;//对应c课程选
        }

    }else if(Notin=="Data_Structure")
    {
        if(roll==false)
        {
            Add = sqlcon+" major2 = null "+" where id ="+id;//对应数据库课程退选
        }else{
            Add = sqlcon+" major2 = 'Data_Structure' "+" where id ="+id;//对应数据库课程选
        }

    }else if(Notin=="Advanced_Math"){
        if(roll==false)
        {
             Add = sqlcon+" major3 = null "+" where id ="+id;//对应数学课程退选
        }else{
             Add = sqlcon+" major3 = 'Advanced_Math' "+" where id ="+id;//对应数学课程选
        }

    }
    return Add;

}//拼接更新sql语句SET限制的sql语句


//退选课程的操作，传输课程名字，映射到对应的列上面去


//选课程的操作，传输课程名字，映射到对应的列上面去
void StudentWithCourse(Psql &ps,const string& Notin,const string& id,bool roll){
    const string &notrollcourse=sqlupdatetSqlConnStr(updateStudentTableStr.c_str(),Notin,id,roll);//获取到特定的列
    if(notrollcourse=="")
    {
        print("输入错误，请检测课程是否存在或拼写错误,注意拼写的下划线，然后重试\n");
    }else{
        ps.insertTable(notrollcourse.c_str());
    }


}





//教师管理数据库--有删除操作
void TeacherControl(Psql &ps){

}

//学生操作数据库--待传入id号
void StudentControl(Psql &ps){

    //test
     ps.selectTable(showStudentTableStrOrdeBy.c_str());


    //用于控制学生的功能程序循环
    bool run=true;
    while(run)
    {
        //清除输入缓冲区内容

        print("===select your function\n");
        print("1: 展示当前已选课表\n");
        print("2: 退选课表\n");
        print("3: 选课\n");
        print("4: 退出功能\n");

        char c;
        std::cin>>c;



        switch(c)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            case '1':{
            //传入id,查看学生id所对应的所选课程基本信息
                string sid="101";
                string sql= sqlselectSqlConnStr(showStudentTableStr,sid);
                ps.selectTable(sql.c_str());
                break;
                }
            case '2':{

            //传入tid,输入退选课程，在退选函数中进行操作
                string tid="101";
                print("输入你想退选的课程\n");
                string notroll;
                std::cin>>notroll;
                StudentWithCourse(ps,notroll,tid,false);//退选函数

                break;
                }
            case '3':{
                string tid="101";
                print("输入你想选的课程\n");
                string roll;
                std::cin>>roll;
                StudentWithCourse(ps,roll,tid,true);//退选函数
                }
                break;
            case '4':
                run=false;
                break;
            defalut:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                break;



        }





    }


    ps.selectTable(showStudentTableStr.c_str());


}


//测试函数
export void sqlFuncsystem(User who)
{
    Psql &ps=Psql::getControlsql();



    if(who==Student)
    {

         StudentControl(ps);

    }else if(who==Teacher)
    {
        //教师登陆

    }


    /*
    // 1. 插入学生表
    ps.insertTable("INSERT INTO student (id, name) VALUES (101, '张三')");
    ps.insertTable("INSERT INTO student (id, name) VALUES (102, '李四')");
    ps.insertTable("INSERT INTO student (id, name) VALUES (103, '王五')");
    ps.insertTable("INSERT INTO student (id, name) VALUES (104, '赵六')");
    ps.insertTable("INSERT INTO student (id, name) VALUES (105, '孙七')");

    // 2. 插入课程表
    ps.insertTable("INSERT INTO course (id, name) VALUES (1, 'C_programs')");
    ps.insertTable("INSERT INTO course (id, name) VALUES (2, 'Data_Structure')");
    ps.insertTable("INSERT INTO course (id, name) VALUES (3, 'Advanced_Math')");

    // 3. 插入选课关系表
    ps.insertTable("INSERT INTO studentcourse (student_id, course_id) VALUES (101, 1)");
    ps.insertTable("INSERT INTO studentcourse  (student_id, course_id) VALUES (102, 2)");
    ps.insertTable("INSERT INTO studentcourse  (student_id, course_id) VALUES (103, 3)");
    ps.insertTable("INSERT INTO studentcourse  (student_id, course_id) VALUES (104, 1)");
    ps.insertTable("INSERT INTO studentcourse (student_id, course_id) VALUES (105, 2)");

*/

}
