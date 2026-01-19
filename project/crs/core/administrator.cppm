// core/administrator.cppm
export module crs.core.administrator;

import crs.core.user; // 导入基类模块
import <iostream>;
import <string>;

export namespace crs::core {

class Administrator : public User {
public:
    Administrator(const std::string& id, const std::string& name, const std::string& password)
        : User(id, name, password) {}

    // 重写基类函数
    void displayInfo() const override {
        std::cout << "Administrator: " << name << " (ID: " << id << ")" << std::endl;
        std::cout << "  Has full system privileges." << std::endl;
    }

    // 实现纯虚函数
    void login() override {
        std::cout << "Administrator " << name << " logged in with elevated privileges." << std::endl;
    }

    // 管理员特有方法（示例）
    void createUserAccount(const User& newUser) {
        // 此处应实现创建用户账户的逻辑（简化为打印）
        std::cout << "Created new user account for: " << newUser.getName()
                  << " (Type: ";

        if (dynamic_cast<const Student*>(&newUser)) {
            std::cout << "Student";
        } else if (dynamic_cast<const Teacher*>(&newUser)) {
            std::cout << "Teacher";
        } else if (dynamic_cast<const Administrator*>(&newUser)) {
            std::cout << "Administrator";
        } else {
            std::cout << "Unknown";
        }

        std::cout << ")" << std::endl;
    }
};

} // namespace crs::core
