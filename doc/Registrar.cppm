//module:
//Description:
/*this files is build by author: tangshengqing2024051604041 at 2026-01-16*/
//email address:2052448030@qq.com


export module studentCourse:registrar;


import std;

import :psql;//导入接口文件
using std::string;

//---------------------------------------------------------实现-------------------------------------------------------------//










































//---------------------------------------------------------实现-------------------------------------------------------------//





//为不同用户设置不同的权限
export typedef enum User{
    Teacher,
    Student,

};





//--------------------------------------------------------------工具函数声明--------------------------------------------------------------------------------------------



//拼接查询sql语句返回where限制的sql语句，更精确的查找或者删除，
string sqlselectSqlConnStr(const string &sqlcon,const string &id);

//拼接更新sql语句SET限制的sql语句,bool用来判断是选还是退（取消选则的课）
string sqlControlStudentCourseStr(const int& Notin,const string &id,bool roll);

//设置登陆对象的函数方法，设置权限不同
void TeacherControl(Psql &ps);//老师登陆
void StudentControl(Psql &ps);//学生登陆



//选和退选课程的操作，传输课程名字，映射到对应的列上面去，roll=true为选课，roll=false为退课
void StudentWithCourse(Psql &ps,const int& Notin,const string& id,bool roll);




//优化界面类

void pressAnyKeyToConntinue();




//--------------------------------------------------------------------用户操作函数实现----------------------------------------------

//优化操作
void pressAnyKeyToConntinue(){
    print("请按任意键继续..\n");
    std::getchar();

}



//拼接常用sql语句返回where限制的sql语句，更精确的查找
string sqlselectSqlConnStr(const string &sqlcon,const string &id){
            string Add = sqlcon+id+")";
            return Add;
}


//拼接控制学生选课表的增加或者删除
string sqlControlStudentCourseStr(const int& Notin,const string &id,bool roll){
//1———C——programs,   2----Data_Structure , 3-----Advanced_Math的数据id映射关系操作studentcourse
    //roll为判断选课还是退选，然后拼接sql语句
    string Add;

    switch (Notin) {
    case 1:{
        if(roll==false)//false为退选，true为选课
        {
             Add = deleteStudentControlCourseTableStr+ " course_id = 1 AND student_id = "+id;//更新删除，两个主键确定一行，然后把这行都设置为null
        }else{
            Add = insertStudentControlCourseTableStr+"(1,"+id+")";
        }
    }
        break;
    case 2:{
        if(roll==false)
        {
            Add = deleteStudentControlCourseTableStr+ " course_id = 2 AND student_id = "+id;//对应数据库课程退选
        }else{
            Add = insertStudentControlCourseTableStr+"(2,"+id+")";//对应数据库课程选
        }
    }
        break;
    case 3:{
        if(roll==false)
        {
             Add = deleteStudentControlCourseTableStr+ " course_id = 3 AND student_id = "+id;//对应数学课程退选
        }else{
             Add = insertStudentControlCourseTableStr+"(3,"+id+")";//对应数学课程选
        }
    }
        break;
    default:
        break;
    }

    return Add;

}





//选和退选课程的操作，传输课程名字，映射到对应的列上面去
void StudentWithCourse(Psql &ps,const int& Notin,const string& id,bool roll){
    const string &controlcourse=sqlControlStudentCourseStr(Notin,id,roll);//获取到特定的列
    if(controlcourse=="")
    {
        print("输入错误，请检测课程是否存在或拼写错误,注意拼写的下划线，然后重试\n");
    }else{
        ps.controlTable(controlcourse.c_str());
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

        int c;
        std::cin>>c;



        switch(c)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            case 1:{
            //传入id,查看学生id所对应的所选课程基本信息
                string sid="101";
                string sql= sqlselectSqlConnStr(showStudentRollCourseTableStr,sid);
                ps.selectTable(sql.c_str());

                pressAnyKeyToConntinue();
                break;

            }

            case 2:{

            //传入tid,输入退选课程，在退选函数中进行操作
                string tid="101";
                print("输入你想退选的课程,输入课程对应的数字id\n");
                ps.selectTable(showCourseTableStr.c_str());
                int notroll;
                std::cin>>notroll;
                StudentWithCourse(ps,notroll,tid,false);//退选函数

                pressAnyKeyToConntinue();

                break;
                }
            case 3:{
                string tid="101";
                print("输入你想选的课程,输入课程对应的数字id\n");
                ps.selectTable(showCourseTableStr.c_str());
                int roll;
                std::cin>>roll;
                StudentWithCourse(ps,roll,tid,true);//退选函数

                pressAnyKeyToConntinue();

                }
                break;
            case 4:
                run=false;
                break;
            defalut:

                break;
        }

        //清除错误状态，匹配下次的输入
        std::cin.clear();

         while (std::cin.get() != '\n');//清除错误输入的字符
        std::system("printf \"\\033c\"");

    }

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
    ps.controlTable("INSERT INTO student (id, name) VALUES (101, '张三')");
    ps.controlTable("INSERT INTO student (id, name) VALUES (102, '李四')");
    ps.controlTable("INSERT INTO student (id, name) VALUES (103, '王五')");
    ps.controlTable("INSERT INTO student (id, name) VALUES (104, '赵六')");
    ps.controlTable("INSERT INTO student (id, name) VALUES (105, '孙七')");

    // 2. 插入课程表
    ps.controlTable("INSERT INTO course (id, name) VALUES (1, 'C_programs')");
    ps.controlTable("INSERT INTO course (id, name) VALUES (2, 'Data_Structure')");
    ps.controlTable("INSERT INTO course (id, name) VALUES (3, 'Advanced_Math')");

    // 3. 插入选课关系表
    ps.controlTable("INSERT INTO studentcourse (student_id, course_id) VALUES (101, 1)");
     ps.controlTable("INSERT INTO studentcourse (student_id, course_id) VALUES (101, 2)");
      ps.controlTable("INSERT INTO studentcourse (student_id, course_id) VALUES (101, 3)");
    ps.controlTable("INSERT INTO studentcourse  (student_id, course_id) VALUES (102, 2)");
    ps.controlTable("INSERT INTO studentcourse  (student_id, course_id) VALUES (103, 3)");
    ps.controlTable("INSERT INTO studentcourse  (student_id, course_id) VALUES (104, 1)");
    ps.controlTable("INSERT INTO studentcourse (student_id, course_id) VALUES (105, 2)");

*/

}
