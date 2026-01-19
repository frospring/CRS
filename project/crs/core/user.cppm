// core/user.cppm
export module crs.core.user;

import <string>;
import <iostream>;

export namespace crs::core {

class User {
protected:
    std::string id;
    std::string name;
    std::string password;

public:
    User(const std::string& id, const std::string& name, const std::string& password)
        : id(id), name(name), password(password) {}

    virtual ～User() = default; // 虚析构函数

    // 基本信息获取
    const std::string& getId() const { return id; }
    const std::string& getName() const { return name; }

    // 虚函数，子类可重写
    virtual void displayInfo() const {
        std::cout << "User: " << name << " (ID: " << id << ")" << std::endl;
    }

    // 纯虚函数，强制子类实现
    virtual void login() = 0;
};

} // namespace crs::core
