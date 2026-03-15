export module enrollment;

import std;
import database;


using std::string;
using std::vector;
using std::print;
using std::println;


export class Enrollment {
private:
    string student_id;
    string course_id;
    double score;

public:

    Enrollment(string sid, string cid, double sc = 0.0);

    string info();


    void display();


    void update_score(double new_score);

    void save_to_database(Database& db);

    void delete_from_database(Database& db);

    static vector<Enrollment> load_all_from_database(Database& db);
};


Enrollment::Enrollment(string sid, string cid, double sc)
    : student_id(sid), course_id(cid), score(sc) {}

string Enrollment::info() {
    return std::format("学生ID: {}, 课程ID: {}, 成绩: {:.1f}", student_id, course_id, score);
}

void Enrollment::display() {
    println("{}", info());
}

void Enrollment::update_score(double new_score) {
    score = new_score;
}

void Enrollment::save_to_database(Database& db) {
    string sql = std::format(
        "INSERT INTO enrolls (stu_id, cou_id, score) "
        "VALUES ('{}', '{}', {:.1f}) "
        "ON CONFLICT (stu_id, cou_id) DO UPDATE SET "
        "score = EXCLUDED.score",
        student_id, course_id, score
    );
    db.execute(sql);
}

void Enrollment::delete_from_database(Database& db) {
    string sql = std::format(
        "DELETE FROM enrolls WHERE stu_id = '{}' AND cou_id = '{}'",
        student_id, course_id
    );
    db.execute(sql);
}

vector<Enrollment> Enrollment::load_all_from_database(Database& db) {
    vector<Enrollment> enrollments;
    auto results = db.query("SELECT stu_id, cou_id, score FROM enrolls");

    for (std::size_t i = 1; i < results.size(); i++) {
        auto row = results[i];
        if (row.size() >= 3) {
            double score = row[2].empty() ? 0.0 : std::stod(row[2]);
            enrollments.emplace_back(row[0], row[1], score);
        }
    }

    return enrollments;
}
