export module course;

import std;
import database;

using std::string;
using std::vector;
using std::print;
using std::println;

export class Course {
private:
    string course_id;
    string course_name;
    double credit;
    int capacity;
    int selected_count;
    string teacher_id;
    string course_time;
    string course_address;

public:

    Course(string id, string name, double credit, int capacity,
           string teacher_id, string time, string address, int selected = 0);

    string info();

    void display();

    bool has_id(string id);

    bool is_full();

    int available_seats();

    bool enroll_student();

    void drop_student();

    static Course load_from_database(Database& db, string id);

    void save_to_database(Database& db);
};


Course::Course(string id, string name, double credit, int capacity,
               string teacher_id, string time, string address, int selected)
    : course_id(id), course_name(name), credit(credit), capacity(capacity),
      selected_count(selected), teacher_id(teacher_id),
      course_time(time), course_address(address) {}

string Course::info() {
    return std::format("课程ID: {}, 名称: {}, 学分: {:.1f}, 容量: {}/{}, 时间: {}, 地点: {}",
                     course_id, course_name, credit, selected_count, capacity, course_time, course_address);
}

void Course::display() {
    println("{}", info());
}

bool Course::has_id(string id) {
    return course_id == id;
}

bool Course::is_full() {
    return selected_count >= capacity;
}

int Course::available_seats() {
    return capacity - selected_count;
}

bool Course::enroll_student() {
    if (is_full()) return false;
    selected_count++;
    return true;
}

void Course::drop_student() {
    if (selected_count > 0) {
        selected_count--;
    }
}

Course Course::load_from_database(Database& db, string id) {
    string sql = std::format(
        "SELECT id, name, credit, capacity, selected_count, teacher_id, time, address "
        "FROM courses WHERE id = '{}'", id
    );
    auto results = db.query(sql);

    if (results.size() > 1) {
        auto row = results[1];
        if (row.size() >= 8) {
            double credit = std::stod(row[2]);
            int capacity = std::stoi(row[3]);
            int selected = row[4].empty() ? 0 : std::stoi(row[4]);
            return Course(row[0], row[1], credit, capacity, row[5], row[6], row[7], selected);
        }
    }

    return Course("", "", 0.0, 0, "", "", "");
}

void Course::save_to_database(Database& db) {
    string sql = std::format(
        "INSERT INTO courses (id, name, credit, capacity, selected_count, teacher_id, time, address) "
        "VALUES ('{}', '{}', {:.1f}, {}, {}, '{}', '{}', '{}') "
        "ON CONFLICT (id) DO UPDATE SET "
        "name = EXCLUDED.name, credit = EXCLUDED.credit, capacity = EXCLUDED.capacity, "
        "selected_count = EXCLUDED.selected_count, teacher_id = EXCLUDED.teacher_id, "
        "time = EXCLUDED.time, address = EXCLUDED.address",
        course_id, course_name, credit, capacity, selected_count,
        teacher_id, course_time, course_address
    );
    db.execute(sql);
}
