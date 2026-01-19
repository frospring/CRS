// core/administrator.cppm (最终修正版)
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
        // 通过 RTTI 判断用户类型
        if (const auto* student = dynamic_cast<const Student*>(&newUser)) {
            std::cout << "Created new user account for: " << student->getName()
                      << " (Type: Student)" << std::endl;
        } else if (const auto* teacher = dynamic_cast<const Teacher*>(&newUser)) {
            std::cout << "Created new user account for: " << teacher->getName()
                      << " (Type: Teacher)" << std::endl;
        } else if (const auto* admin = dynamic_cast<const Administrator*>(&newUser)) {
            std::cout << "Created new user account for: " << admin->getName()
                      << " (Type: Administrator)" << std::endl;
        } else {
            std::cout << "Created new user account for: " << newUser.getName()
                      << " (Type: Unknown)" << std::endl;
        }
    }
};

}
