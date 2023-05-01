#include <cstring>
#include "datachunk.h"

namespace data
{
    Data_chunk::Data_chunk()
    {
        this->header.size = 0;
    }

    void Data_chunk::set_content(int size, const char *content)
    {
        this->header.size = size;
        this->content = std::make_unique<char[]>(size);
        memcpy(this->content.get(), content, size);
    }
    void Data_chunk::get_content(int &size, const char *&content) const
    {
        size = this->header.size;
        content = this->content.get();
    }

    void Data_chunk::save(std::ofstream &save_file)
    {
        save_file.write(reinterpret_cast<const char *>(&(this->header.size)), sizeof(int));
        save_file.write(this->content.get(), this->header.size);
    }
    void Data_chunk::load(std::ifstream &save_file)
    {
        save_file.read(reinterpret_cast<char *>(&(this->header.size)), sizeof(int));
        content = std::make_unique<char[]>(this->header.size);
        save_file.read(this->content.get(), this->header.size);
    }
}