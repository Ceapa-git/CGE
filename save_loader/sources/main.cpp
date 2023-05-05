#include "pch.h"
#include "datafile.h"

int main()
{
    {
        cge::data::Data_file data;
        unsigned char data_bytes[4] = {10, 0, 0, 0};
        data.add(4, data_bytes);
        data.save("save.bin");
    }
    {
        cge::data::Data_file data;
        data.load("save.bin");
        std::cout << data.get_count() << ' ' << data.is_valid() << ' ' << data.get_major() << '.' << data.get_minor() << '\n';
        for (int i = 0; i < data.get_count(); i++)
        {
            int sz;
            const unsigned char *cont;
            data.get(i, sz, cont);
            int value = *(int *)(cont);
            std::cout << value << '\n';
            for (int j = 0; j < sz; j++)
                std::cout << (int)cont[j] << ' ';
            std::cout << '\n';
            unsigned char v_data[4] = {
                (unsigned char)((value >> 8 * 0) & 0xff),
                (unsigned char)((value >> 8 * 1) & 0xff),
                (unsigned char)((value >> 8 * 2) & 0xff),
                (unsigned char)((value >> 8 * 3) & 0xff)};
            data.set(0, 4, v_data);
        }
        data.save("save.bin");
    }
    std::cout << "aA" << '\n';
    {
        cge::data::Data_file data;
        data.load("save.bin");
        std::cout << data.get_count() << ' ' << data.is_valid() << ' ' << data.get_major() << '.' << data.get_minor() << '\n';
        for (int i = 0; i < data.get_count(); i++)
        {
            int sz;
            const unsigned char *cont;
            data.get(i, sz, cont);
            int value = *(int *)(cont);
            std::cout << value << '\n';
            for (int j = 0; j < sz; j++)
                std::cout << (int)cont[j] << ' ';
            std::cout << '\n';
        }
    }
    return 0;
}
