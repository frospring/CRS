// utils/validator.cppm (最终修正版)
export module crs.utils.validator;

import <regex>;
import <stdexcept>;
import <iostream>;
import <string>;

export namespace crs::utils {

class Validator {
public:

    static inline bool isValidUserId(const char* userId) {
        if (!userId || strlen(userId) == 0) {
            return false;
        }
        // 简单的用户ID验证：只允许字母、数字、下划线，长度1-20
        const static std::regex pattern("^[a-zA-Z0-9_]{1,20}$");
        return std::regex_match(userId, pattern);
    }

    static inline bool isValidPassword(const char* password) {
        if (!password || strlen(password) < 6) {
            return false;
        }
        // 简单的密码验证：至少6位，包含字母和数字
        const static std::regex pattern("^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{6,}$");
        return std::regex_match(password, pattern);
    }

    static inline bool isValidEmail(const char* email) {
        if (!email || strlen(email) == 0) {
            return false;
        }
        // 简单的邮箱验证
        const static std::regex pattern("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
        return std::regex_match(email, pattern);
    }

    static inline void validateUserId(const char* userId) {
        if (!isValidUserId(userId)) {
            throw std::invalid_argument("Invalid user ID");
        }
    }

    static inline void validatePassword(const char* password) {
        if (!isValidPassword(password)) {
            throw std::invalid_argument("Invalid password");
        }
    }

    static inline void validateEmail(const char* email) {
        if (!isValidEmail(email)) {
            throw std::invalid_argument("Invalid email address");
        }
    }
};

}
