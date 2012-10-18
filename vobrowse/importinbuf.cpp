#include "importinbuf.h"

#ifdef WIN32

ImportInBuf::ImportInBuf(const char* filename): std::ifstream(filename)
{
    if(is_open())
    {
        int a = 1;
    }else
    {
        int b= 1;
    }
    strcpy(ifile, filename);
}

#else

ImportInBuf::ImportInBuf(const char* filename)
    :fd_(open(filename,O_RDONLY | O_LARGEFILE))
{
    setg(buffer_,buffer_,buffer_);
    struct stat st;
    fstat(fd_,&st);
    fsize_=st.st_size;
}

// you don;t have to do it like this if your streams are 64 bit
void ImportInBuf::seekg(uint64_t pos)
{
    lseek(fd_,pos,SEEK_SET);
    pos_=pos;
    setg(buffer_,buffer_,buffer_);
}

#endif