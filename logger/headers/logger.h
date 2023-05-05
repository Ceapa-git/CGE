#ifndef __LOGGER__H__
#define __LOGGER__H__

#include "pch.h"

#define LOG_INFO (0)
#define LOG_WARNING (1)
#define LOG_ERROR (2)

#define LOG_MAXLEVEL LOG_ERROR

namespace cge::log
{
    typedef struct
    {
        union{
            int v_int;
            unsigned int v_uint;
            char* v_charp;
            unsigned char* v_ucharp;
        };
    } log_arg;
    class Logger
    {
    public:
        Logger(const char *filename, bool timestamp = true, int min_level = LOG_INFO, bool clear = false);
        Logger() : Logger("console"){};
        ~Logger(){};

        void log(const char *message, int log_level = LOG_INFO);
        void log_f(const char *format, const log_arg *args, int log_level = LOG_INFO);

        void set_min_level(int min_level);

    private:
        std::unique_ptr<char[]> filename;
        int min_level;
        bool timestamp;
    };
}

#endif //__LOGGER__H__