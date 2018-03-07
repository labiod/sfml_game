#ifndef LOG_HPP
#define LOG_HPP

//Class using for loggin debug or error message in terminal
//Works only in debug mode, in release methods are empty
class Log {
    public:
        static void d(const char* tag, const char* msg, ...);

        static void e(const char* tag, const char* msg, ...);
};

#endif //LOG_HPP