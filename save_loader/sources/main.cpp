#include <iostream>
#include <chrono>
#include "datafile.h"

int main()
{
    data::Data_file data;
    data.set_auto_save(true, "save.bin");
    data.set_auto_save_interval(std::chrono::seconds(1));
    char data_bytes[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    data.add(10, data_bytes);
    while (false != true && true == true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        data.add(10, data_bytes);
    }
    std::cin.get();
    return 0;
}
