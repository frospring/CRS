export module teacher;

import std;
import database;

using std::string;
using std::vector;
using std::print;
using std::println;

export class Teacher {
private:
    string teacher_id;
    string teacher_name;
    string department;

public:
    Teacher(string id, string name, string dept);

    string info();

    void display();

    bool has_id(string id);

    static Teacher load_from_database(Database& db, string id);

    void save_to_database(Database& db);
};


Teacher::Teacher(string id, string name, string dept)
    : teacher_id(id), teacher_name(name), department(dept) {}

string Teacher::info() {
    return std::format("教师ID: {}, 姓名: {}, 学院: {}", teacher_id, teacher_name, department);
}

void Teacher::display() {
    println("{}", info());
}

bool Teacher::has_id(string id) {
    return teacher_id == id;
}

Teacher Teacher::load_from_database(Database& db, string id) {
    string sql = std::format("SELECT id, name, dept FROM teachers WHERE id = '{}'", id);
    auto results = db.query(sql);

    if (results.size() > 1) {
        auto row = results[1];
        if (row.size() >= 3) {
            return Teacher(row[0], row[1], row[2]);
        }
    }

    return Teacher("", "", "");
}

void Teacher::save_to_database(Database& db) {
    string sql = std::format(
        "INSERT INTO teachers (id, name, dept) "
        "VALUES ('{}', '{}', '{}') "
        "ON CONFLICT (id) DO UPDATE SET "
        "name = EXCLUDED.name, dept = EXCLUDED.dept",
        teacher_id, teacher_name, department
    );
    db.execute(sql);
}
