//module:
//Description:
/*this files is build by author: tangshengqing2024051604041 at 2026-01-16*/
//email address:2052448030@qq.com


export module studentCourse:registrar;


import std;

import :psql;//导入接口文件
using std::string;

//---------------------------------------------------------实现-------------------------------------------------------------//
// File: registrar.cppm   Version: 0.1.0   License: AGPLv3
// Created: pangwenhao      2026-01-17 16:02:04
// Description:
//
// Module: Registrar

import std;
using std::string;
using std::vector;

// 前置声明
class Student;
class Course;
class Teacher;

export class Registrar
{
public:
    // 原有接口（无需修改，后续完善）
    static Registrar& singleton();
    void studentEnrollsInCourse(string sid, string cid);
    void studentSchedule(const string& sid);
    void courseRoster(string cid);
    void initialize();

    // 新增：教师管理接口（预留，后续完善）
    void addTeacher(Teacher* teacher);
    void bindTeacherToCourse(string tid, string cid);
    void teacherTaughtCourses(string tid);

private:
    // 原有构造函数（禁止直接实例化，单例模式）
    Registrar();
    // 原有查找接口
    Student* findStudentById(const string& id);
    Course* findCourseById(const string& id);
    // 新增：查找教师接口
    Teacher* findTeacherById(const string& id);

    // 原有属性
    vector<Course*> _courses;
    vector<Student*> _students;
    // 新增：教师列表
    vector<Teacher*> _teachers;
};

// ----- The implementaion of class Registrar -----
// 单例实现（原有逻辑保留）
Registrar &Registrar::singleton(){
    static Registrar instance;
    return instance;
}

// 学生选课调度（原有逻辑保留，注释内为核心调度）
void Registrar::studentEnrollsInCourse(string sid, string cid){
    // 核心逻辑：查找学生与课程，调用学生选课接口
    Student* student = findStudentById(sid);
    Course* course = findCourseById(cid);
    if (student && course) {
        student->enrollsIn(course);
    }
}

// 学生课表查询（原有逻辑保留）
void Registrar::studentSchedule(const string &sid)
{
    // 核心逻辑：查找学生，调用学生课表接口并打印
    auto s = findStudentById(sid);
    if (s) { // 增加空指针判断，避免崩溃
        std::print("{}\n",s->schedule());
    }
}

// 课程花名册查询（原有逻辑保留）
void Registrar::courseRoster(string cid){
    // 核心逻辑：查找课程，调用课程花名册接口并打印
    auto c = findCourseById(cid);
    if (c) { // 增加空指针判断，避免崩溃
        std::print("{}\n", c->roster());
    }
}

// 系统初始化（原有逻辑保留，新增教师初始化）
void Registrar::initialize(){
    // 1. 原有逻辑：初始化学生
    _students.push_back(new Student("S001", "Thomas"));
    _students.push_back(new Student("S002", "Jerry"));
    _students.push_back(new Student("S003", "Baker"));
    _students.push_back(new Student("S004", "Tom"));
    _students.push_back(new Student("S005", "Musk"));

    // 2. 原有逻辑：初始化课程
    _courses.push_back(new Course("CS101", "C Programming"));
    _courses.push_back(new Course("CS201", "Data structure"));
    _courses.push_back(new Course("MATH101", "Advanced Math"));

    // 3. 新增逻辑：初始化教师并绑定课程
    auto t1 = new Teacher("T001", "Professor Lee", "Computer Science");
    auto t2 = new Teacher("T002", "Dr. Wang", "Mathematics");
    _teachers.push_back(t1);
    _teachers.push_back(t2);

    // 绑定教师与课程
    bindTeacherToCourse("T001", "CS101");
    bindTeacherToCourse("T001", "CS201");
    bindTeacherToCourse("T002", "MATH101");
}

// 私有构造函数（原有逻辑保留）
Registrar::Registrar(){}

// 查找学生（原有逻辑保留）
Student *Registrar::findStudentById(const string &id){
    // 核心逻辑：遍历学生列表，匹配ID返回学生对象
    for (auto& student :_students) {
        if (student->hasId(id))
            return student;
    }
    return nullptr;
}

// 查找课程（原有逻辑保留）
Course *Registrar::findCourseById(const string &id){
    // 核心逻辑：遍历课程列表，匹配ID返回课程对象
    for (auto& course : _courses) {
        if (course->hasId(id) )
            return course;
    }
    return nullptr;
}

// 新增：查找教师（核心逻辑：遍历教师列表，匹配ID返回教师对象）
Teacher* Registrar::findTeacherById(const string& id) {
    for (auto& teacher : _teachers) {
        if (teacher->hasId(id))
            return teacher;
    }
    return nullptr;
}

// 新增：添加教师（核心逻辑：将教师加入系统列表）
void Registrar::addTeacher(Teacher* teacher) {
    if (teacher && !findTeacherById(teacher->hasId(teacher->info()))) {
        _teachers.push_back(teacher);
    }
}

// 新增：绑定教师与课程（核心逻辑：调度教师与课程的双向绑定）
void Registrar::bindTeacherToCourse(string tid, string cid) {
    auto teacher = findTeacherById(tid);
    auto course = findCourseById(cid);
    if (teacher && course) {
        teacher->addTaughtCourse(course);
    }
}

// 新增：查询教师授课列表（核心逻辑：调度教师授课花名册接口并打印）
void Registrar::teacherTaughtCourses(string tid) {
    auto teacher = findTeacherById(tid);
    if (teacher) {
        std::print("{}\n", teacher->getTaughtCoursesRoster());
    }
}








































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
