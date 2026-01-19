//学生类// Module
// File: student.cppm   Version: 0.1.0   License: AGPLv3
// Created: pangwenhao      2026-01-17 16:02:41
// Description:
//

export module studentCourse:student;
import std;

class Course;

using std::string;
using std::vector;

// 前置声明


export class Student
{
public:
    // 原有接口（无需修改，后续完善）
    Student(string id, string name);
    void enrollsIn(Course* course);
    string schedule();
    string info();
    bool hasId(string id);

private:
    // 原有属性
    string m_name;
    string m_id;
    vector<Course*> _courses;
};

// ----- Partial implementation of class Student -----
// 构造函数（原有逻辑保留，注释内为核心初始化）
Student::Student(string id, string name)
    : m_name(name)
    , m_id(id)
{}

// 学生信息逻辑（原有逻辑保留）
string Student::info()
{
    // 核心逻辑：拼接学生ID+姓名，返回格式化字符串
    return std::format("{}   {}\n", m_id, m_name);
}

// 学生ID校验（原有逻辑保留）
bool Student::hasId(string id)
{
    // 核心逻辑：校验传入ID与学生自身ID是否一致
    return id == m_id;
}

void Student::enrollsIn(Course* course){
    _courses.push_back(course);
}




