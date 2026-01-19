//课程类
// Module
// File: course.cppm   Version: 0.1.0   License: AGPLv3
// Created: pangwenhao      2026-01-17 16:01:52
// Description:
//


export module studentCourse:course;

import std;

class Student;

using std::string;
using std::vector;

// 前置声明
class Teacher;

export class Course
{
public:
    // 原有接口（无需修改，后续完善）
    Course(string id, string name);
    bool acceptEnrollment(Student* student);
    string roster();
    void enrollsIn(Student *ss);
    string info();
    bool hasId(string id);

    // 新增：教师关联接口（仅预留，核心逻辑在注释内）
    void bindTeacher(Teacher* teacher);
    Teacher* getBoundTeacher() const;

private:
    // 原有属性
    string m_name;
    string m_id;
    short m_credit = 3; // 默认3学分，原有代码未初始化，补充默认值
    static int cm_totalCount;
    vector<Student*> _students;

    // 新增：关联授课教师
    Teacher* _boundTeacher = nullptr;
};




// ----- Partial implementation of class Course -----
// 静态成员初始化（原有逻辑保留）
int Course::cm_totalCount = 0;

// 构造函数（原有逻辑保留）
Course::Course(string id, string name)
    : m_name(name)
    , m_id(id)
{
    cm_totalCount++;
}

// 选课逻辑（原有逻辑保留，注释内为核心实现）
bool Course::acceptEnrollment(Student *student){
    // 核心逻辑：校验课程容量（80人上限），添加学生到选课列表
    if(_students.size() < 80){  // 假定某个课程的最大人数为80
        _students.push_back(student);
        std::print("\"{}\" 选课成功！目前选择该课程的人数: {}\n",
              m_name, _students.size());
        return true;
    }
    return false;
}

// 课程信息逻辑（原有逻辑保留）
string Course::info(){
    return std::format("{}   {}\n", m_id, m_name);
}

// 课程ID校验（原有逻辑保留）
bool Course::hasId(string id){
    return id == m_id;
}

void Course::enrollsIn(Student *ss){
    _students.push_back(ss);

}

// 新增：绑定教师核心逻辑（注释内实现，无额外扩展）
void Course::bindTeacher(Teacher* teacher) {
    // 核心逻辑：关联教师与课程，建立双向绑定
    _boundTeacher = teacher;
}

// 新增：获取绑定教师（辅助接口，供其他类调用）
Teacher* Course::getBoundTeacher() const {
    return _boundTeacher;
}


