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
    return 0;
}
