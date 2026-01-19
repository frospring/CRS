// core/student.cppm
export module crs.core.student;

import crs.core.user; // 导入基类模块
import <vector>;
import <string>;
import <iostream>;

export namespace crs::core {

class Student : public User {
private:
    std::vector<std::string> enrolledCourses; // 选修课程列表

public:
    Student(const std::string& id, const std::string& name, const std::string& password)
        : User(id, name, password) {}

    // 重写基类函数
    void displayInfo() const override {
        std::cout << "Student: " << name << " (ID: " << id << ")" << std::endl;
        if (!enrolledCourses.empty()) {
            std::cout << "  Enrolled Courses: ";
            for (const auto& course : enrolledCourses) {
                std::cout << course << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "  No courses enrolled." << std::endl;
        }
    }

    // 实现纯虚函数
    void login() override {
        std::cout << "Student " << name << " logged in." << std::endl;
    }

    // 学生特有方法
    void enrollCourse(const std::string& course) {
        enrolledCourses.push_back(course);
        std::cout << "Enrolled in course: " << course << std::endl;
    }

    const std::vector<std::string>& getEnrolledCourses() const {
        return enrolledCourses;
    }
};

} // namespace crs::core
