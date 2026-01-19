//老师类// Module
// File: teacher.cppm   Version: 0.1.0   License: AGPLv3
// Created: pangwenhao      2026-01-17 16:01:32
// Description:
//

export module studentCourse:teacher;
import std;

class Course;
class Student;

using std::string;
using std::vector;

// 前置声明


export class Teacher
{

public:
    // 教师类接口（预留，后续完善，注释内实现核心构造与逻辑）
    Teacher(string id, string name, string courseDirection);
    string info();
    bool hasId(string id);
    void addTaughtCourse(Course* course);
    string getTaughtCoursesRoster();
    const string &findeId();//用于验证id号

private:
    // 教师类核心属性
    string m_id;       // 教师ID
    string m_name;     // 教师姓名
    string m_courseDirection; // 主讲方向
    vector<Course*> _taughtCourses; // 授课课程列表
};

// ----- Partial implementation of class Teacher -----
// 构造函数（核心逻辑：初始化教师属性）
Teacher::Teacher(string id, string name, string courseDirection)
    : m_id(id), m_name(name), m_courseDirection(courseDirection)
{}

// 教师信息逻辑（核心逻辑：返回格式化教师信息）
string Teacher::info()
{
    return std::format("{}   {}   主讲方向：{}\n", m_id, m_name, m_courseDirection);
}



// 教师ID校验（核心逻辑：校验传入ID与教师自身ID是否一致）
bool Teacher::hasId(string id)
{
    return id == m_id;
}


 const string& Teacher::findeId(){
    return this->m_id;
}//用于验证id号


