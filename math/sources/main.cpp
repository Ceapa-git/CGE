#include "pch.h"
#include "logger.h"

int main()
{
    cge::log::Logger logger("console", LOG_WARNING);
    for (int i = 0; i < 10; i++)
    {
        int level;
        char message[] = "level 0";
        std::cin >> level;
        message[6] += level;
        logger.log(message, level);
    }
    return 0;
}
