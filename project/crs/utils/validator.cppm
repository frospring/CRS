
// utils/validator.cppm
export module crs.utils.validator ;

import <regex>;
import <stdexcept>;
import <iostream>;

export namespace crs utils {


class Validator{


static inline bool isValidUserId(const char *userId ){


if(!userId ||strlen(userId )==0 ){
return false ;
}

// 简单的用户ID验证：只允许字母、数字、下划线，长度1-20
const static re2 ::RE2 pattern("^[a-zA-Z0-9_]{1,20}$");
return re2 ::RE2 ::FullMatch(userId ,pattern );

}

static inline bool isValidPassword(const char *password ){


if(!password ||strlen(password )<6 ){
return false ;
}

// 简单的密码验证：至少6位，包含字母和数字
const static re2 ::RE2 pattern("^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{6,}$");
return re2 ::RE2 ::FullMatch(password ,pattern );

}

static inline bool isValidEmail(const char *email ){


if(!email ||strlen(email )==0 ){
return false ;
}

// 简单的邮箱验证
const static re2 ::RE2 pattern("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
return re2 ::RE2 ::FullMatch(email ,pattern );

}

static inline void validateUserId(const char *userId ){
if(!isValidUserId(userId )){
throw new ("Invalid user ID");
}
}

static inline void validatePassword(const char *password ){
if(!isValidPassword(password )){
throw new ("Invalid password");
}
}

static inline void validateEmail(const char *email ){
if(!isValidEmail(email )){
throw new ("Invalid email address");
}
}


};

}//namespace
