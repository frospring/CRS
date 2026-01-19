// main.cpp (最终修正版)
import crs.core.student;      // 导入学生模块
import crs.core.teacher;      // 导入教师模块
import crs.core.administrator; // 导入管理员模块
import crs.core.course;        // 导入课程模块
import crs.core.enrollment;    // 导入选课管理器模块
import crs.utils.logger;       // 导入日志工具
import crs.utils.validator;    // 导入验证工具
import crs.utils.menu;         // 导入菜单工具

#include <iostream>
#include <memory>

int main() {
     try{
         // 创建用户实例
         auto student1=std ::make_shared<crs ::core ::Student >("S001","Alice","password123 ");
         auto teacher1=std ::make_shared<crs ::core ::Teacher >("T001","Prof.Bob","profpass ");
         auto admin1=std ::make_shared<crs ::core ::Administrator >("A001","AdminCarol","adminpass ");

         // 创建课程实例
         crs ::core ::Course mathCourse("MATH101","Calculus I",4 );
         crs ::core ::Course physicsCourse("PHYS101","Physics I",3 );

         // 使用选课管理器
         auto enrollmentId=crs ::core ::EnrollmentManager ::
             createEnrollment(student1 ,mathCourse );

          LOG_INFO("Created enrollment with ID:"<<enrollmentId );

          // 显示信息
          student1 ->displayInfo();
          teacher1 ->displayInfo();
          admin1 ->displayInfo();

          LOG_DEBUG("Program completed successfully.");

     }catch(const std ::exception &e){

          LOG_ERROR(e.what ());
          return -1 ;

     }


     return 0 ;

}
