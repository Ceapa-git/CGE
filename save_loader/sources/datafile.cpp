#include "pch.h"
#include "datafile.h"

namespace cge::data
{
    Data_file::Data_file()
    {
        this->auto_save = false;
        this->header.magic = 0xDf;
        this->header.padding = 0;
        this->header.v_major = 1;
        this->header.v_minor = 0;
        this->header.total_size = 0;
        this->header.chunk_count = 0;
        this->auto_save_stop = false;
        this->auto_save_interval = std::chrono::seconds(10);
        this->auto_save_modified = false;
        this->auto_save_thread = std::thread(&Data_file::auto_save_fun, this);
        std::unique_lock<std::mutex> lock(this->auto_save_mutex);
        this->auto_save_cond.wait(lock);
    }
    Data_file::~Data_file()
    {
        std::unique_lock<std::mutex> lock(this->auto_save_mutex);
        this->auto_save_stop = true;
        lock.unlock();
        this->auto_save_cond.notify_all();
        this->auto_save_thread.join();
    }

    bool Data_file::is_valid() const
    {
        return (this->header.magic == 0xDf && this->header.padding == 0);
    }
    int Data_file::get_count() const
    {
        return this->header.chunk_count;
    }
    int Data_file::get_major() const
    {
        return this->header.v_major;
    }
    int Data_file::get_minor() const
    {
        return this->header.v_minor;
    }

    int Data_file::add(const int size, const unsigned char *content)
    {
        std::unique_lock<std::mutex> lock(this->data_mutex);
        this->chunks.emplace_back(std::make_unique<Data_chunk>())->set_content(size, content);
        this->header.chunk_count++;
        this->header.total_size += (size + sizeof(int));
        std::unique_lock<std::mutex> lock_auto_save(this->auto_save_mutex);
        this->auto_save_modified = true;
        return this->chunks.size() - 1;
    }
    void Data_file::get(int index, int &size, const unsigned char *&content)
    {
        std::unique_lock<std::mutex> lock(this->data_mutex);
        this->chunks.at(index)->get_content(size, content);
    }
    void Data_file::set(int index, int size, const unsigned char *content)
    {
        std::unique_lock<std::mutex> lock(this->data_mutex);
        int old_size;
        const unsigned char *ignored;
        this->chunks.at(index)->get_content(old_size, ignored);
        this->header.total_size -= old_size;
        this->chunks.at(index)->set_content(size, content);
        this->header.total_size += size;
        std::unique_lock<std::mutex> lock_auto_save(this->auto_save_mutex);
        this->auto_save_modified = true;
    }

    void Data_file::save(const char *filename)
    {
        std::unique_lock<std::mutex> lock(this->data_mutex);
        std::ofstream save_file(filename, std::ios::binary | std::ios::trunc);
        save_file.write(reinterpret_cast<const char *>(&(this->header.magic)), 1);
        save_file.write(reinterpret_cast<const char *>(&(this->header.padding)), 1);
        save_file.write(reinterpret_cast<const char *>(&(this->header.v_major)), 1);
        save_file.write(reinterpret_cast<const char *>(&(this->header.v_minor)), 1);

        save_file.write(reinterpret_cast<const char *>(&(this->header.total_size)), sizeof(int));
        save_file.write(reinterpret_cast<const char *>(&(this->header.chunk_count)), sizeof(int));
        for (auto &chunk : this->chunks)
            chunk->save(save_file);
        save_file.close();
    }
    void Data_file::load(const char *filename)
    {
        std::unique_lock<std::mutex> lock(this->data_mutex);
        std::ifstream save_file(filename, std::ios::binary);

        this->header.total_size = 0;
        this->header.chunk_count = 0;
        if (!save_file)
            return;
        if (save_file.peek() == std::ifstream::traits_type::eof())
            return;

        save_file.read(reinterpret_cast<char *>(&(this->header.magic)), 1);
        save_file.read(reinterpret_cast<char *>(&(this->header.padding)), 1);
        save_file.read(reinterpret_cast<char *>(&(this->header.v_major)), 1);
        save_file.read(reinterpret_cast<char *>(&(this->header.v_minor)), 1);
        if (this->header.magic != 0xDf || this->header.padding != 0)
        {
            this->header.magic = 0;
            this->header.padding = 0;
            this->header.v_major = 0;
            this->header.v_minor = 0;
            save_file.close();
            return;
        }

        save_file.read(reinterpret_cast<char *>(&(this->header.total_size)), sizeof(int));
        save_file.read(reinterpret_cast<char *>(&(this->header.chunk_count)), sizeof(int));
        for (int i = 0; i < this->header.chunk_count; i++)
        {
            if (save_file.eof())
            {
                this->header.magic = 0;
                this->header.padding = 0;
                this->header.v_major = 0;
                this->header.v_minor = 0;
                this->header.total_size = 0;
                this->header.chunk_count = 0;

                while (!this->chunks.empty())
                    this->chunks.pop_back();
                save_file.close();
                return;
            }
            this->chunks.emplace_back(std::make_unique<Data_chunk>())->load(save_file);
        }
        save_file.close();
    }

    bool Data_file::get_auto_save()
    {
        return this->auto_save;
    }
    void Data_file::set_auto_save(bool state, const char *filename)
    {
        std::unique_lock<std::mutex> lock(this->auto_save_mutex);
        this->auto_save = state;
        if (this->auto_save)
        {
            this->auto_save_filename = std::make_unique<char[]>(strlen(filename) + 1);
            strcpy(this->auto_save_filename.get(), filename);
            this->auto_save_modified = true;
        }
        else
            this->auto_save_filename.reset();
    }
    void Data_file::set_auto_save_interval(std::chrono::seconds interval)
    {
        std::unique_lock<std::mutex> lock(this->auto_save_mutex);
        this->auto_save_interval = interval;
        this->auto_save_modified = true;
        this->auto_save_cond.notify_all();
    }

    void Data_file::auto_save_fun()
    {
        std::unique_lock<std::mutex> lock(this->auto_save_mutex);
        this->auto_save_cond.notify_all();
        do
        {
            this->auto_save_cond.wait_for(lock, this->auto_save_interval);
            if (this->auto_save && this->auto_save_modified)
            {
                this->save(this->auto_save_filename.get());
                this->auto_save_modified = false;
            }
        } while (!this->auto_save_stop);
    }
}