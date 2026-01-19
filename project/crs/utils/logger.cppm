// utils/logger.cppm
export module crs.utils.logger;

import <iostream>;
import <chrono>;
import <iomanip>;

export namespace crs :: utils {

enum class LogLevel { DEBUG , INFO , WARN , ERROR };

class Logger{
private :
static inline LogLevel currentLevel =LogLevel :: INFO ;

static inline bool isEnabled(LogLevel level ){
return level >=currentLevel ;
}

static inline void log(LogLevel level ,const char *levelStr ,
                       const char *msg ,const char *file ,int line ){
if(isEnabled(level )){

auto now =std ::chrono ::system_clock ::now ();
auto time_t =std ::chrono ::system_clock ::to_time_t(now );

std ::ctime(&time_t );
std ::cerr <<"["<<levelStr <<" "<<std ::ctime (&time_t )<<" "<<file <<" :"<<" "<<line <<" ]"<<msg <<" "<<std ::endl ;

}


}


public :

static inline void setLogLevel(LogLevel level ){currentLevel =level ;}


static inline void debug(const char *msg ,const char *file ="unknown ",int line =0 ){
log(LogLevel :: DEBUG ,"DEBUG ",msg ,file ,line );
}


static inline void info(const char *msg ,const char *file ="unknown ",int line =0 ){
log(LogLevel :: INFO ,"INFO ",msg ,file ,line );
}

static inline void warn(const char *msg ,const char *file ="unknown ",int line =0 ){
log(LogLevel :: WARN ,"WARN ",msg ,file ,line );
}

static inline void error(const char *msg ,const char *file ="unknown ",int line =0 ){
log(LogLevel :: ERROR ,"ERROR ",msg ,file ,line );
}

};


#define LOG_DEBUG(msg )crs :: utils :: Logger ::debug(msg,__FILE__,__LINE__)
#define LOG_INFO(msg )crs :: utils :: Logger ::info(msg,__FILE__,__LINE__)
#define LOG_WARN(msg )crs :: utils :: Logger ::warn(msg,__FILE__,__LINE__)
#define LOG_ERROR(msg )crs :: utils :: Logger ::error(msg,__FILE__,__LINE__)


}//namespace
