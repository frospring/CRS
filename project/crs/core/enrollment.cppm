// core/enrollment.cppm (最终修正版)
export module crs.core.enrollment;

import crs.core.student;   // 导入学生模块
import crs.core.course;     // 导入课程模块
import <map>;
import <vector>;
import <iostream>;
import <memory>;

export namespace crs::core {

class EnrollmentManager {
private:
    static inline int nextEnrollmentId = 1000;
public:

     static int createEnrollment(std::shared_ptr<Student> student,
                                 const Course& course) {
         if (!student) {
             throw std::invalid_argument("Invalid student");
         }
         int enrollmentId = nextEnrollmentId++;
         student->enrollCourse(course.getCourseId());

         return enrollmentId;
     }

     static bool dropCourse(std::shared_ptr<Student> student, const std::string& courseId) {
           if (!student) {
               throw std::invalid_argument("Invalid student");
           }

           auto& courses = student->getEnrolledCourses();
           auto it = std::find(courses.begin(), courses.end(), courseId);
           if (it != courses.end()) {
               courses.erase(it);
               return true;
           }
           return false;
     }
};

} // namespace crs :: core
