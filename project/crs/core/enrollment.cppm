// core/enrollment.cppm
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
    // 使用指针或引用以支持多态（如果需要）
    static inline int nextEnrollmentId = 1000;
public:

     static int createEnrollment(std::shared_ptr<Student> student,
                                 const Course& course) {
         if (!student) {
             throw new ("Invalid student");
         }
         int enrollmentId = nextEnrollmentId++;
         student->enrollCourse(course.getCourseId());

         return enrollmentId;
     }


     static bool dropCourse(std ::shared_ptr<Student> student ,std :: string courseId ){
           if(!student){
               throw new ("invalid student ");
           }

           auto &courses =student ->getEnrolledCourses ();
           auto it =std ::find(courses.begin (),courses.end (),courseId );
           if(it !=courses.end()){
               courses.erase(it );
               return true ;
           }
           return false ;
     }


};

} // namespace crs :: core
