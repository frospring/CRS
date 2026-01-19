// core/teacher.cppm
export module crs.core.teacher;

import crs.core.user; // 导入基类模块
import <vector>;
import <string>;
import <iostream>;

export namespace crs::core {

class Teacher : public User {
private:
    std::vector<std::string> teachingCourses; // 教授课程列表

public:
    Teacher(const std::string& id, const std::string& name, const std::string& password)
        : User(id, name, password) {}

    // 重写基类函数
    void displayInfo() const override {
        std::cout << "Teacher: " << name << " (ID: " << id << ")" << std::endl;
        if (!teachingCourses.empty()) {
            std::cout << "  Teaching Courses: ";
            for (const auto& course : teachingCourses) {
                std::cout << course << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "  No courses assigned." << std::endl;
        }
    }

    // 实现纯虚函数
    void login() override {
        std::cout << "Teacher " << name << " logged in." << std::endl;
    }

    // 教师特有方法
    void assignCourse(const std::string& course) {
        teachingCourses.push_back(course);
        std::cout << "Assigned to teach course: " << course << std::endl;
    }

    const std::vector<std::string>& getTeachingCourses() const {
        return teachingCourses;
    }
};

} // namespace crs::core
