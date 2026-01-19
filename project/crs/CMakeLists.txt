cmake_minimum_required(VERSION 3.28) # 建议版本，若必须用4.1.1请参考下方注释
# 若强制使用 CMake 4.1.1，请取消下一行注释并修改上方版本号
# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")

project(CourseRegistrationSystem LANGUAGES CXX)

# 设置 C++23 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 若使用 CMake 4.1.1，此处设置方式可能不同，通常直接通过 target_compile_features 控制
# set(CMAKE_CXX_MODULE_STD ON)

# 定义源文件列表
set(CRS_CORE_MODULES
    core/user.cppm
    core/student.cppm
    core/teacher.cppm
    core/administrator.cppm
    core/course.cppm
    core/enrollment.cppm
)

set(CRS_UTILS_MODULES
    utils/logger.cppm
    utils/validator.cppm
    utils/menu.cppm
)

# 主程序源文件
set(CRS_SOURCES
    main.cpp
)

# 创建可执行文件
add_executable(crs ${CRS_SOURCES})

# 设置 C++ 标准（CMake 3.28+ 推荐方式）
target_compile_features(crs PRIVATE cxx_std_23)

# 收集模块文件
target_sources(crs PRIVATE
    FILE_SET cxx_modules TYPE CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${CRS_CORE_MODULES} ${CRS_UTILS_MODULES}
)

# 包含目录（确保编译器能找到头文件或模块接口）
target_include_directories(crs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
