#ifndef BB_H_INCLUDED
#define BB_H_INCLUDED

#include <iostream>
#include <vector>
using namespace std;

namespace BB {


/*
 *
 * String
 *
 */
    // case insensitive equal
    inline static
    bool IsEqualStrings(const std::string& a, const std::string& b)
    {
        size_t sz = a.size();
        if (b.size() != sz)
            return false;
        for (unsigned int i = 0; i < sz; ++i)
            if (tolower(a[i]) != tolower(b[i]))
                return false;
        return true;
    }



    // https://wiki.kldp.org/HOWTO/html/C++Programming-HOWTO/standard-string.html
    inline static
    void Tokenize(const string& str,
                  std::vector<std::string>& tokens,
                  const string& delimiters)
    {
        // 맨 첫 글자가 구분자인 경우 무시
        string::size_type lastPos = str.find_first_not_of(delimiters, 0);
        // 구분자가 아닌 첫 글자를 찾는다
        string::size_type pos     = str.find_first_of(delimiters, lastPos);

        while (string::npos != pos || string::npos != lastPos)
        {
            // token을 찾았으니 vector에 추가한다
            tokens.push_back(str.substr(lastPos, pos - lastPos));
            // 구분자를 뛰어넘는다.  "not_of"에 주의하라
            lastPos = str.find_first_not_of(delimiters, pos);
            // 다음 구분자가 아닌 글자를 찾는다
            pos = str.find_first_of(delimiters, lastPos);
        }
    }



    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
    // http://stackoverflow.com/a/7430262
    inline void MakeSurePathExists(std::string dir_name, mode_t mode=0755)
    {
        struct stat st = {0};

        if (stat(dir_name.c_str(), &st) == -1)
        {
            mkdir(dir_name.c_str(), mode);
        }
        else
        {
            cout << "Directory " << dir_name << " already exists !" << endl;
        }
    }



#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>

#include <algorithm>
    // Returns a list of files in a directory (except the ones that begin with a dot)
    // http://stackoverflow.com/a/1932861

    inline void GetFilesInDirectory(std::vector<string> &out, const std::string &directory)
    {

        std::cout << directory.c_str() << std::endl;

#ifdef WINDOWS
        HANDLE dir;
        WIN32_FIND_DATA file_data;
        if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
            return; /* No files found */

        do {
            const string file_name = file_data.cFileName;
            const string full_file_name = directory + "/" + file_name;
            const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

            if (file_name[0] == '.')
                continue;

            if (is_directory)
                continue;

            out.push_back(full_file_name);
        } while (FindNextFile(dir, &file_data));

        FindClose(dir);
#else

        DIR *dir;
        class dirent *ent;
        class stat st;

        dir = opendir(directory.c_str());


        while ((ent = readdir(dir)) != NULL) {
            const string file_name = ent->d_name;
            const string full_file_name = directory + "/" + file_name;

            if (file_name[0] == '.')
                continue;

            if (stat(full_file_name.c_str(), &st) == -1)
                continue;

            const bool is_directory = (st.st_mode & S_IFDIR) != 0;

            if (is_directory)
                continue;

            out.push_back(full_file_name);
        }

        closedir(dir);

        std::sort(out.begin(), out.end());
#endif
    } // GetFilesInDirectory

    inline static
    int GetFilesofExtInDirectory(std::vector<std::string> &out, const string &directory, const string &_extension)
    {
        std::vector<std::string> fns;
        BB::GetFilesInDirectory(fns, directory);
        std::vector<std::string> fn1;
        for(std::vector<string>::iterator it= fns.begin(); it!= fns.end(); ++it)
        {
            vector<string> tokens;
            Tokenize(*it, tokens, ".");
            string ext = tokens[tokens.size()-1];

            if(BB::IsEqualStrings(ext, _extension) )
            {
                fn1.push_back(*it);

            }
        }
        out = fn1;

        std::sort(out.begin(), out.end());

        return fn1.size();
    }


    // cross-platform sleep function
    // http://stackoverflow.com/a/28827188
    #ifdef WIN32
    #include <windows.h>
    #elif _POSIX_C_SOURCE >= 199309L
    #include <time.h>   // for nanosleep
    #else
    #include <unistd.h> // for usleep
    #endif

    inline static
    void sleep_ms(int milliseconds)
    {
    #ifdef WIN32
        Sleep(milliseconds);
    #elif _POSIX_C_SOURCE >= 199309L
        struct timespec ts;
        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;
        nanosleep(&ts, NULL);
    #else
        usleep(milliseconds * 1000);
    #endif
    }



#ifdef _WINDOWS
#include <time.h>
#else
#include <sys/time.h>
#endif

inline static std::string GetTimeString()
{

    string str1;
    // only for Windows
    #ifdef _WINDOWS
        SYSTEMTIME st;
        GetSystemTime(&st);
        str1 = string_format("%d%02d%02d_%02d%02d%02d_%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    #else
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        struct timeval ts;
        gettimeofday(&ts,0);
        double tu = ts.tv_usec;

        char buf[255];
        sprintf(buf, "%d%02d%02d_%02d%02d%02d_%.f",    now->tm_year + 1900,
                                                                now->tm_mon + 1,
                                                                now->tm_mday,
                                                                now->tm_hour,
                                                                now->tm_min,
                                                                now->tm_sec,
                                                                    tu);
        str1 = std::string(buf);

    #endif





    return str1;

}


} //namespace



#endif
