#ifndef FASTINPUT_H
#define FASTINPUT_H


#include <streambuf>
#ifndef WIN32
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif
#include <cstdio>
#include <fstream>

class ImportInBuf: 
#ifdef WIN32
    public std::ifstream {
#else
    public std::streambuf {
#endif
public:
    ImportInBuf(const char* filename);
    // you don;t have to do it like this if your streams are 64 bit
#ifndef WIN32
    void seekg(uint64_t pos);
    uint64_t tellg()const { return pos_; }
    uint64_t size()const { return fsize_; }
#endif
    ~ImportInBuf(){ 
#ifdef WIN32
        close();
#else
        close(fd_); 
#endif
    }
private:
    ImportInBuf(const ImportInBuf&);
#ifndef WIN32
    ImportInBuf& operator=(const ImportInBuf&);
    virtual int underflow()
    {
        if(gptr()<egptr())
        {
            return *gptr();
        }
        int size = read(fd_,buffer_,4096);
        if(size)
        {
            pos_+=size;
            setg(buffer_,buffer_,buffer_+size);
            return *gptr();
        }
        pos_=fsize_;
        return EOF;
    }
    char buffer_[4096];
    int fd_;
    uint64_t fsize_,pos_;
#else
    char ifile[1024];
#endif
};


#endif // FASTINPUT_H

