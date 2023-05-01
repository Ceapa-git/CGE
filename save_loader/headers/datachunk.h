#ifndef __DATACHUNK__H__
#define __DATACHUNK__H__
#include <memory>
#include <iostream>
#include <fstream>

namespace data
{
    typedef struct
    {
    public:
        int size;
    } data_chunk_header;
    class Data_chunk
    {
    public:
        Data_chunk();
        ~Data_chunk(){};

        void set_content(int size, const char *content);
        void get_content(int &size, const char *&content) const;

        void save(std::ofstream &save_file);
        void load(std::ifstream &save_file);

    private:
        data_chunk_header header;
        std::unique_ptr<char[]> content;
    };
}

#endif //__DATACHUNK__H__