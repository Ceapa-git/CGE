#include "pch.h"
#include "logger.h"

namespace cge::log
{
    Logger::Logger(const char *filename, bool timestamp, int min_level, bool clear)
    {
        this->filename = std::make_unique<char[]>(strlen(filename) + 1);
        this->min_level = min_level;
        this->timestamp = timestamp;
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

        char time_srting[100] = {};
        if (this->timestamp)
        {
            std::time_t now = std::time(nullptr);
            std::tm *time = std::localtime(&now);
            snprintf(time_srting, sizeof(time_srting), "[ %02d:%02d:%02d ] ", time->tm_hour, time->tm_min, time->tm_sec);
        }

        if (strcmp(this->filename.get(), "console") == 0)
        {
            bool ok;
            switch (log_level)
            {
            case LOG_INFO:
                std::cout << time_srting << "[ INFO ] ";
                ok = true;
                break;
            case LOG_WARNING:
                std::cout << time_srting << "[ WARNING ] ";
                ok = true;
                break;
            case LOG_ERROR:
                std::cout << time_srting << "[ ERROR ] ";
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
                file << time_srting << "[ INFO ] ";
                ok = true;
                break;
            case LOG_WARNING:
                file << time_srting << "[ WARNING ] ";
                ok = true;
                break;
            case LOG_ERROR:
                file << time_srting << "[ ERROR ] ";
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