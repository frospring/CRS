module;//全局混用头文件和模块
//module:提供c++程序和数据库的接口,提供插入，查询，删除的方式,使用sql语句调用对应的函数连接到数据库接口
//Description:
/*this files is build by author: tangshengqing2024051604041 at 2026-01-07*/
//email address:2052448030@qq.com
#include<libpq-fe.h>//导入postgresql的头文件
export module studentCourse:psql;

// ---------student --datatable: major1: C_programs , major2: Data_Structure  major3:Advanced_Math 以便于用来对数据库的列进行操作



import std;


using std::print;
using std::string;


//常用数据库sql语句

//=----------------------------------------创建表的sql语句

const string &creaStudentTable = "create table student("
        " id bigint primary key,"
        " name varchar(20) not null,"
        " maxcredits int check (maxcredits  >=0 and maxcredits <=100)"
")";

const string &creaCourseTable = "create table course("
            "id bigint primary key,"
            "name varchar(20) not null"
            ")";

const string &creaStudentCourseTable = "create table studentcourse("
            "student_id bigint references student(id),"
            "course_id bigint references course(id),"
            "primary key(student_id,course_id)"
    ")";

const string &createTeachertable = "create table teacher("
            "id bigint primary key,"
            "name varchar(20) not null,"
           "course varchar(20)"
    ")";

const string &createTeacherCourseTable ="create table teachercourse("
            "teacher_id bigint references student(id),"
            "course_id bigint references course(id),"
            "primary key(teacher_id,course_id)"
    ")";



//------------------------------------学生类sql
const string showStudentTableStr="select * from student ";//sql查学生表

const string showStudentTableStrOrdeBy="select * from Student Order BY id ASC";//正序查询学生表

//------------------------------------老师类sql
const string showTeacherTableStr="select * from teacher ";//sql查老师

//-------------------------------------课程类sql
const string showCourseTableStr="select * from course ";//sql查课程

//-------------------------------------学生选课课程关系sql

const string showStudentRollCourseTableStr="select name from course where id in (select course_id from studentcourse where student_id = ";//查看关系表
const string deleteStudentControlCourseTableStr="delete from studentcourse where ";//删除选课的拼接语句
const string insertStudentControlCourseTableStr="insert into studentcourse (course_id,student_id) values ";//选课的拼接语句



//------------------------------------老师学生关系sql

const string showCourseHaveStudentTableStr="select * from teacherstudent";







//--------------------------------------------------------------接口类声明--------------------------------------------------------------------------------------------
//创建接口类
export class Psql{


public:
    //创建连接，反馈连接
    Psql();

    static Psql& getControlsql();//获取静态管理对象

    void selectTable(const char *input);//查的接口

    void controlTable(const char *input);//插入接口
    void insertTable(const string &table,const string &date1,const string &date2);//插入接口
    void insertTeacherTable(const string &table,const string &date1,const string &date2,const string &date3);//插入接口2

    void InitleTable();//初始化创建表的操作，在计算机中创建表
     void createTable(const string &ss);//创建表


private:
    const char *constr;//连接到的口
    PGconn* conclass;//连接端口对象

};

//------------------------------------------------------------------数据库和程序的命令接口实现----------------------------------------------







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

    //显示登陆用户
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

//控制函数接口--删
void Psql::controlTable(const char *input){
      PGresult *res=PQexec(conclass,input);//查询获取对象指针
      if(PQresultStatus(res)==PGRES_COMMAND_OK)
      {
          print("---sucessfully {}\n",PQcmdTuples(res));
      }else{
          print("---error {}\n",PQresultErrorMessage(res));
      }


}


//控制函数接口--增-插入
void Psql::insertTable(const string &table,const string &date1,const string &date2){

     string isExist;
    if(table!="teachercourse"&&table!="studentcourse")//studentcourse和teachercourse的属性特殊性，单独分类
    {
        isExist = "select count(*) from " + table + " where id = " +date1;//先查看存在不再插入


    }else if(table=="teachercourse"){
         isExist = "select count(*) from " + table + " where course_id = " +date1+" AND teacher_id = "+date2;//先查看存在不再插入
    }else if(table=="studentcourse")
    {
         isExist = "select count(*) from " + table + " where studet_id = " +date1+" AND course_id =" +date2;//先查看存在不再插入
    }


   // print("{}",isExist);

     PGresult *res=PQexec(conclass,isExist.c_str());//查询获取对象指针


    if(PQresultStatus(res)==PGRES_TUPLES_OK)
    {
        print("已经插入到表\n",PQcmdTuples(res));
    }else{

        //不存在，插入
         string insert;
        if(table =="student")
        {
            insert = "INSERT INTO student (id, name) VALUES ("+date1+"),('"+date2+"')";

        }else if(table=="course")
        {
            insert = "INSERT INTO course (id, name) VALUES ("+date1+"),('"+date2+"')";

        }else if(table=="studentcourse")
        {
            insert = "INSERT INTO studentcourse (student_id,course_id) VALUES ("+date1+"),('"+date2+"')";

        }else if(table=="teachercourse")
        {
            insert = "INSERT INTO teachercourse (teacher_id,course_id) VALUES ("+date1+"),('"+date2+"')";

        }
        PGresult *res1=PQexec(conclass,insert.c_str());

        if(PQresultStatus(res1)==PGRES_COMMAND_OK)
        {
            print("---sucessfully {}\n",PQcmdTuples(res));
        }else{
            print("---error {}\n",PQresultErrorMessage(res));
        }


    }
}//插入接口

void Psql::insertTeacherTable(const string &table,const string &date1,const string &date2,const string &date3){
    print("j");


}

//初始化创建表的操作，在计算机中创建表


void Psql::InitleTable(){
    const string studentTable="student";
    const string courseTable="course";
    const string studentCourseTable="studentcourse";


    const string teacherTable="teacher";
    const string teacherCourseTable="teachercourse";

    createTable(studentTable);
    createTable(courseTable);
    createTable(studentCourseTable);
    createTable(teacherTable);
    createTable(teacherCourseTable);

 }
//创建表

void Psql::createTable(const string &ss){

    string table = "SELECT COUNT(*) FROM pg_catalog.pg_tables "
                   "WHERE tablename =  '"+ss + "'  AND schemaname = 'public'";



    PGresult *res = PQexec(this->conclass,table.c_str());//执行sql命令//查询表是否存在然后选择创建的操作
    int count = std::atoi(PQgetvalue(res,0,0));

    if(count==1)
    {
        std::print("{}表 存在，初始化完毕\n",ss);
    }else{
         //std::cout<<table<<"\n";
        std::print("{}表 不存在，创建表中...\n",ss);

        if(ss=="student")
        {
            controlTable(creaStudentTable.c_str());

        }else if (ss=="course")
        {
            controlTable(creaCourseTable.c_str());

        }else if(ss=="studentcourse")
        {
             controlTable(creaStudentCourseTable.c_str());

        }else if(ss=="teacher")
        {
            controlTable(createTeachertable.c_str());

        }else if(ss=="teachercourse")
        {
            controlTable(createTeacherCourseTable.c_str());

        }



    }

}




