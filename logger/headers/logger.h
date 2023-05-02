#ifndef __LOGGER__H__
#define __LOGGER__H__

#include "pch.h"

#define LOG_INFO (0)
#define LOG_WARNING (1)
#define LOG_ERROR (2)

namespace cge::data
{
    class Logger
    {
    public:
        Logger(const char *filename, bool append = false);
        Logger() : Logger("console"){};
        ~Logger(){};
        void log(const char *message, int log_level = LOG_INFO);

    private:
        std::unique_ptr<char[]> filename;
    };
}

#endif //__LOGGER__H__