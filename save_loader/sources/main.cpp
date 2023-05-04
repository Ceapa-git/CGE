#include "pch.h"
#include "datafile.h"

int main()
{
    {
        cge::data::Data_file data;
        char data_bytes[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        data.add(10, data_bytes);
        data.save("save.bin");
    }
    {
        cge::data::Data_file data;
        data.load("save.bin");
        std::cout << data.get_count() << ' ' << data.is_valid() << ' ' << data.get_major() << '.' << data.get_minor() << '\n';
        for (int i = 0; i < data.get_count(); i++)
        {
            int sz;
            const char *cont;
            data.get(i, sz, cont);
            for (int j = 0; j < sz; j++)
                std::cout << (int)cont[j] << ' ';
            std::cout << '\n';
        }
    }
    return 0;
}
