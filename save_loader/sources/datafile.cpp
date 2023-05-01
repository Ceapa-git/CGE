#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include "datafile.h"

namespace data
{
    Data_file::Data_file()
    {
        this->auto_save = false;
        this->header.total_size = 0;
        this->header.chunk_count = 0;
        this->auto_save_stop = false;
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

    int Data_file::add(const int size, const char *content)
    {
        std::unique_lock<std::mutex> lock(this->data_mutex);
        this->chunks.emplace_back(std::make_unique<Data_chunk>())->set_content(size, content);
        this->header.chunk_count++;
        this->header.total_size += (size + sizeof(int));
        return this->chunks.size() - 1;
    }
    void Data_file::get(int index, int &size, const char *&content)
    {
        std::unique_lock<std::mutex> lock(this->data_mutex);
        this->chunks.at(index)->get_content(size, content);
    }
    void Data_file::set(int index, int size, const char *content)
    {
        std::unique_lock<std::mutex> lock(this->data_mutex);
        int old_size;
        const char *ignored;
        this->chunks.at(index)->get_content(old_size, ignored);
        this->header.total_size -= old_size;
        this->chunks.at(index)->set_content(size, content);
        this->header.total_size += size;
    }

    void Data_file::save(const char *filename)
    {
        std::unique_lock<std::mutex> lock(this->data_mutex);
        std::ofstream save_file(filename, std::ios::binary);
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
        save_file.read(reinterpret_cast<char *>(&(this->header.total_size)), sizeof(int));
        save_file.read(reinterpret_cast<char *>(&(this->header.chunk_count)), sizeof(int));
        for (int i = 0; i < this->header.chunk_count; i++)
            this->chunks.emplace_back(std::make_unique<Data_chunk>())->load(save_file);
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
        }
        else
            this->auto_save_filename.reset();
    }

    void Data_file::auto_save_fun()
    {
        std::unique_lock<std::mutex> lock(this->auto_save_mutex);
        this->auto_save_cond.notify_all();
        do
        {
            this->auto_save_cond.wait_for(lock, std::chrono::seconds(10));
            if (this->auto_save)
            {
                if (!this->auto_save_stop)
                    std::cout << "AUTO SAVING\n";
                this->save(this->auto_save_filename.get());
            }
        } while (!this->auto_save_stop);
    }
}