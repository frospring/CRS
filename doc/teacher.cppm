//老师类// Module
// File: teacher.cppm   Version: 0.1.0   License: AGPLv3
// Created: pangwenhao      2026-01-17 16:01:32
// Description:
//

export module studentCourse:teacher;
import std;
import :course; // 导入Course模块

using std::string;
using std::vector;

// 前置声明
class Course;

export class Teacher
{
public:
    // 教师类接口（预留，后续完善，注释内实现核心构造与逻辑）
    Teacher(string id, string name, string courseDirection);
    string info();
    bool hasId(string id);
    void addTaughtCourse(Course* course);
    string getTaughtCoursesRoster();

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

// 添加授课课程（核心逻辑：关联教师与课程，双向绑定）
void Teacher::addTaughtCourse(Course* course)
{
    // 1. 核心逻辑：添加课程到教师授课列表
    _taughtCourses.push_back(course);
    // 2. 核心逻辑：反向绑定课程与教师
    course->bindTeacher(this);
    std::print("教师{}已绑定课程{}\n", m_name, course->info());
}

// 获取授课课程花名册汇总（核心逻辑：拼接所有授课课程的学生信息）
string Teacher::getTaughtCoursesRoster()
{
    auto rst = std::format("{}的授课课程汇总：\n", m_name);
    for (auto course : _taughtCourses) {
        rst += course->roster() + "\n";
    }
    return rst;
}
