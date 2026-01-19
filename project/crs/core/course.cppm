// core/course.cppm
export module crs.core.course;

import <string>;
import <iostream>;

export namespace crs::core {

class Course {
private:
    std::string courseId;
    std::string courseName;
    int credits;

public:
    Course(const std::string& id, const std::string& name, int cred = 3)
        : courseId(id), courseName(name), credits(cred) {}

    // 访问器和修改器
    const std::string& getCourseId() const { return courseId; }
    const std::string& getCourseName() const { return courseName; }

    int getCredits() const { return credits; }

    void setCredits(int cred) { credits = cred; }

    // 显示课程信息
    void displayInfo() const {
        std::cout << "Course: [" << courseId << "] "
                  << courseName
                  << " (" << credits << " credits)"
                  << std::endl;
    }
};

} // namespace crs::core
