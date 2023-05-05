#include "pch.h"
#include "logger.h"

int main()
{
    {
        cge::log::Logger logger("console");
        int level;
        char message[] = "level 0";
        std::cin >> level;
        message[6] += level;
        logger.log(message, level);
    }
    {
        cge::log::Logger logger("console", false);
        int level;
        char message[] = "level 0";
        std::cin >> level;
        message[6] += level;
        logger.log(message, level);
    }
    {
        cge::log::Logger logger("console", false);
        int level;
        std::cin >> level;
        cge::log::log_arg args;
        args.v_int = level;
        logger.log_f("level %d", &args, LOG_ERROR);
    }
    return 0;
}
