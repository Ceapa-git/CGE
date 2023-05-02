#include "pch.h"
#include "datafile.h"

int main()
{
    data::Data_file data;
    char data_bytes[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    data.add(10, data_bytes);
    data.save("save.bin");
    return 0;
}
