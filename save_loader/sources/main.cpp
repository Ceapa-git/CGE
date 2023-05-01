#include <iostream>
#include <chrono>
#include "datafile.h"

int main()
{
    {
        data::Data_file data;
        char data_bytes[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        data.set_auto_save(true, "save.bin");
        data.add(10, data_bytes);
        data.add(10, "0123456789");
    }
    {
        data::Data_file data;
        data.load("save.bin");
        int size;
        const char *data_bytes;
        data.get(0, size, data_bytes);
        for (int i = 0; i < size; i++)
        {
            std::cout << (int)data_bytes[i] << ' ';
        }
        std::cout << '\n';
        data.get(1, size, data_bytes);
        for (int i = 0; i < size; i++)
        {
            std::cout << (int)data_bytes[i] << ' ';
        }
    }
    std::cout << std::endl;
    return 0;
}
