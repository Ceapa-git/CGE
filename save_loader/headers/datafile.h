#ifndef __DATAFILE__H__
#define __DATAFILE__H__

#include "pch.h"
#include "datachunk.h"

namespace cge::data
{
    typedef struct
    {
    public:
        int total_size;
        int chunk_count;
    } data_file_header;
    class Data_file
    {
    public:
        Data_file();
        ~Data_file();

        int add(const int size, const char *content); // index of the newly added content
        void get(int index, int &size, const char *&content);
        void set(int index, int size, const char *content);

        void save(const char *filename);
        void load(const char *filename);

        bool get_auto_save();
        void set_auto_save(bool state, const char *filename);

        void set_auto_save_interval(std::chrono::seconds interval);

    private:
        void auto_save_fun();

    private:
        data_file_header header;
        std::mutex data_mutex;
        std::vector<std::unique_ptr<Data_chunk>> chunks;
        std::thread auto_save_thread;
        std::mutex auto_save_mutex;
        std::condition_variable auto_save_cond;
        bool auto_save;
        std::unique_ptr<char[]> auto_save_filename;
        bool auto_save_stop;
        std::chrono::seconds auto_save_interval;
        bool auto_save_modified;
    };
}

#endif //__DATAFILE__H__