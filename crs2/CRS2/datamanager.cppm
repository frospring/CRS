module;

#include <libpq-fe.h>

export module database;

import std;

using std::string;
using std::vector;
using std::print;
using std::println;


const string create_student_table = R"(
CREATE TABLE IF NOT EXISTS students (
    id VARCHAR(20) PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    total_score FLOAT DEFAULT 0.0,
    total_credit FLOAT DEFAULT 0.0
))";

const string create_teacher_table = R"(
CREATE TABLE IF NOT EXISTS teachers (
    id VARCHAR(20) PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    dept VARCHAR(50) NOT NULL
))";

const string create_course_table = R"(
CREATE TABLE IF NOT EXISTS courses (
    id VARCHAR(20) PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    credit FLOAT NOT NULL CHECK(credit>0),
    capacity INT NOT NULL CHECK(capacity>0),
    selected_count INT DEFAULT 0,
    teacher_id VARCHAR(20) REFERENCES teachers(id),
    time VARCHAR(30),
    address VARCHAR(50)
))";

const string create_enrollment_table = R"(
CREATE TABLE IF NOT EXISTS enrolls (
    stu_id VARCHAR(20) REFERENCES students(id) ON DELETE CASCADE,
    cou_id VARCHAR(20) REFERENCES courses(id) ON DELETE CASCADE,
    score FLOAT DEFAULT 0.0 CHECK(score>=0 AND score<=100),
    PRIMARY KEY(stu_id, cou_id)
))";

const string select_students = "SELECT * FROM students ORDER BY id";
const string select_teachers = "SELECT * FROM teachers ORDER BY id";
const string select_courses = "SELECT * FROM courses ORDER BY id";
const string select_enrollments = "SELECT * FROM enrolls";


export class Database {
private:
    const char* conn_string;
    PGconn* connection;

public:

    Database();

    ~Database();

    void create_tables();

    void load_sample_data();

    void execute(const string& sql);

    vector<vector<string>> query(const string& sql);

    bool is_connected() const;
};

Database::Database() : conn_string("host=localhost dbname=course_db user=zkw password=zkw1663802680 port=5432"), connection(nullptr) {
    connection = PQconnectdb(conn_string);
    if (PQstatus(connection) != CONNECTION_OK) {
        println("连接失败: {}", PQerrorMessage(connection));
        std::exit(0);
    }

    println("数据库连接成功");
    println("数据库: {}", PQdb(connection));
    println("用户: {}", PQuser(connection));
}

Database::~Database() {
    if (connection) {
        PQfinish(connection);
        println("数据库连接已关闭");
    }
}

void Database::create_tables() {
    execute(create_student_table);
    execute(create_teacher_table);
    execute(create_course_table);
    execute(create_enrollment_table);
    println("表创建完成");
}

void Database::load_sample_data() {
    auto result = query("SELECT COUNT(*) FROM students");
    if (!result.empty() && result[0][0] != "0") {
        println("数据库中已有数据");
        return;
    }

    vector<string> sample_data = {
        "INSERT INTO students (id, name) VALUES ('S001','张三'),('S002','李四'),('S003','王五')",
        "INSERT INTO teachers VALUES ('T001','李教授','计算机学院'),('T002','王讲师','软件工程学院')",
        "INSERT INTO courses VALUES ('C001','C++20模块化开发',3.0,60,0,'T001','周一3-4节','一号楼203'),"
        "('C002','数据库原理',2.5,50,0,'T002','周三1-2节','二号楼105')"
    };

    for (const auto& sql : sample_data) {
        execute(sql);
    }

    println("示例数据加载完成");
}

void Database::execute(const string& sql) {
    PGresult* result = PQexec(connection, sql.c_str());

    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        println("执行失败: {}", PQresultErrorMessage(result));
    }

    PQclear(result);
}

vector<vector<string>> Database::query(const string& sql) {
    PGresult* result = PQexec(connection, sql.c_str());
    vector<vector<string>> results;

    if (PQresultStatus(result) == PGRES_TUPLES_OK) {
        int rows = PQntuples(result);
        int cols = PQnfields(result);

        // 按字段名精准设置列宽
        auto print_col = [](const string& col_name, const string& value) {
            if (col_name == "id")          std::print("{:<8}", value);
            else if (col_name == "name")   std::print("{:<15}", value);
            else if (col_name == "total_score") std::print("{:<12}", value);
            else if (col_name == "total_credit") std::print("{:<12}", value);
            else if (col_name == "dept")   std::print("{:<12}", value);
            else if (col_name == "credit") std::print("{:<10}", value);
            else if (col_name == "capacity") std::print("{:<10}", value);
            else if (col_name == "selected_count") std::print("{:<15}", value);
            else if (col_name == "teacher_id") std::print("{:<10}", value);
            else if (col_name == "time")   std::print("{:<10}", value);
            else if (col_name == "address") std::print("{:<12}", value);
            else if (col_name == "stu_id") std::print("{:<8}", value);
            else if (col_name == "cou_id") std::print("{:<8}", value);
            else if (col_name == "score")  std::print("{:<8}", value);
            else if (col_name == "count")  std::print("{:<8}", value);
            else                           std::print("{:<10}", value);
        };

        for (int j = 0; j < cols; j++) {
            string col_name = PQfname(result, j);
            print_col(col_name, col_name);
        }
        std::print("\n");

        for (int j = 0; j < cols; j++) {
            string col_name = PQfname(result, j);
            if (col_name == "id")          std::print("{:<8}", string(8, '-'));
            else if (col_name == "name")   std::print("{:<15}", string(15, '-'));
            else if (col_name == "total_score") std::print("{:<12}", string(12, '-'));
            else if (col_name == "total_credit") std::print("{:<12}", string(12, '-'));
            else if (col_name == "dept")   std::print("{:<12}", string(12, '-'));
            else if (col_name == "credit") std::print("{:<10}", string(10, '-'));
            else if (col_name == "capacity") std::print("{:<10}", string(10, '-'));
            else if (col_name == "selected_count") std::print("{:<15}", string(15, '-'));
            else if (col_name == "teacher_id") std::print("{:<10}", string(10, '-'));
            else if (col_name == "time")   std::print("{:<10}", string(10, '-'));
            else if (col_name == "address") std::print("{:<12}", string(12, '-'));
            else if (col_name == "stu_id") std::print("{:<8}", string(8, '-'));
            else if (col_name == "cou_id") std::print("{:<8}", string(8, '-'));
            else if (col_name == "score")  std::print("{:<8}", string(8, '-'));
            else if (col_name == "count")  std::print("{:<8}", string(8, '-'));
            else                           std::print("{:<10}", string(10, '-'));
        }
        std::print("\n");

        // 输出数据
        for (int i = 0; i < rows; i++) {
            vector<string> row;
            for (int j = 0; j < cols; j++) {
                const char* val = PQgetvalue(result, i, j);
                string cell = val ? val : "";
                row.push_back(cell);

                string col_name = PQfname(result, j);
                print_col(col_name, cell); // 按字段名匹配列宽
            }
            results.push_back(row);
            std::print("\n");
        }

    } else {
        // 错误信息逻辑
        std::print("查询失败: {}\n", PQresultErrorMessage(result));
    }

    PQclear(result);
    return results;
}

bool Database::is_connected() const {
    return connection && PQstatus(connection) == CONNECTION_OK;
}


