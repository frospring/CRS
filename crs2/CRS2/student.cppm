export module student;

import std;
import database;

using std::string;
using std::vector;
using std::print;
using std::println;

export class Course;

export class Student {
private:
    string student_id;
    string student_name;
    double total_score;
    double total_credit;
    vector<Course*> enrolled_courses;

public:
    // 初始化基础信息
    Student(string id, string name);

    // 基础信息
    Student(string id, string name, double score, double credit);

    // 拼接学生完整信息
    string info();

    // 打印学生信息
    void display();

    // 校验学生
    bool has_id(string id);

    // 学生选课
    void enroll_in_course(Course* course);

    // 从数据库加载指定ID的学生信息
    static Student load_from_database(Database& db, string id);

    // 更新数据库
    void save_to_database(Database& db);

    void add_course_score(double score, double credit);
};

Student::Student(string id, string name)
    : student_id(id), student_name(name), total_score(0.0), total_credit(0.0) {}

Student::Student(string id, string name, double score, double credit)
    : student_id(id), student_name(name), total_score(score), total_credit(credit) {}

string Student::info() {
    return std::format("ID: {}, 姓名: {}, 总学分: {:.1f}, 绩点: {:.2f}",
                     student_id, student_name, total_credit,
                     total_credit > 0 ? total_score / total_credit : 0.0);
}

void Student::display() {
    println("{}", info());
}

bool Student::has_id(string id) {
    return student_id == id;
}

void Student::enroll_in_course(Course* course) {
}

Student Student::load_from_database(Database& db, string id) {
    string sql = std::format("SELECT id, name, total_score, total_credit FROM students WHERE id = '{}'", id);
    auto results = db.query(sql);

    if (results.size() > 1) {
        auto row = results[1];
        if (row.size() >= 4) {
            double score = row[2].empty() ? 0.0 : std::stod(row[2]);
            double credit = row[3].empty() ? 0.0 : std::stod(row[3]);
            return Student(row[0], row[1], score, credit);
        }
    }

    return Student("", "");
}

void Student::save_to_database(Database& db) {
    string sql = std::format(
        "INSERT INTO students (id, name, total_score, total_credit) "
        "VALUES ('{}', '{}', {:.2f}, {:.2f}) "
        "ON CONFLICT (id) DO UPDATE SET "
        "name = EXCLUDED.name, total_score = EXCLUDED.total_score, total_credit = EXCLUDED.total_credit",
        student_id, student_name, total_score, total_credit
    );
    db.execute(sql);
}

void Student::add_course_score(double score, double credit) {
    total_score += score * credit;
    total_credit += credit;
}
