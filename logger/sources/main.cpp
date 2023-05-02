#include "pch.h"
#include "logger.h"

int main()
{
    cge::data::Logger logger;
    logger.log("info");
    logger.log("info2",LOG_INFO);
    logger.log("warning",LOG_WARNING);
    logger.log("error",LOG_ERROR);
    logger.log("invalid level",3);
    return 0;
}