#include "pch.h"
#include "logger.h"

namespace cge::log
{
    Logger::Logger(const char *filename, int min_level, bool clear)
    {
        this->filename = std::make_unique<char[]>(strlen(filename) + 1);
        this->min_level = min_level;
        strcpy(this->filename.get(), filename);
        if (strcmp(this->filename.get(), "console") != 0 && clear)
        {
            std::ofstream clear_file;
            clear_file.open(this->filename.get(), std::ios::trunc);
            clear_file.close();
        }
    }

    void Logger::log(const char *message, int log_level)
    {
        if (log_level < this->min_level && log_level >= 0)
            return;
        if (strcmp(this->filename.get(), "console") == 0)
        {
            bool ok;
            switch (log_level)
            {
            case LOG_INFO:
                std::cout << "[ INFO ] ";
                ok = true;
                break;
            case LOG_WARNING:
                std::cout << "[ WARNING ] ";
                ok = true;
                break;
            case LOG_ERROR:
                std::cout << "[ ERROR ] ";
                ok = true;
                break;
            default:
                ok = false;
                break;
            }
            if (!ok)
            {
                Logger console_logger("console");
                console_logger.log("INVLAID LOG LEVEL!", LOG_ERROR);
                console_logger.log(this->filename.get(), LOG_ERROR);
                return;
            }
            std::cout << message << std::endl;
        }
        else
        {
            std::ofstream file = std::ofstream(this->filename.get(), std::ios::app);
            bool ok;
            switch (log_level)
            {
            case LOG_INFO:
                file << "[ INFO ] ";
                ok = true;
                break;
            case LOG_WARNING:
                file << "[ WARNING ] ";
                ok = true;
                break;
            case LOG_ERROR:
                file << "[ ERROR ] ";
                ok = true;
                break;
            default:
                ok = false;
                break;
            }
            if (!ok)
            {
                Logger console_logger("console");
                console_logger.log("INVLAID LOG LEVEL!", LOG_ERROR);
                console_logger.log(this->filename.get(), LOG_ERROR);
                return;
            }
            file << message << std::endl;
            file.close();
        }
    }
}