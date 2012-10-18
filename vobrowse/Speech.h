#ifndef _SPEECH_H
#define _SPEECH_H

#pragma once
#include <QThread>
#ifdef WIN32
#include <windows.h>
#include <atlbase.h>
#include <sapi.h>
#include <sphelper.h>
#else

#include <festival/festival.h>

#endif

#include <string>
#include <vector>

class Speech : public QThread
{
    Q_OBJECT
public:
    Speech(void);
    ~Speech(void);
    static void msleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
    void stop();
    enum SayMode{Single, FullList};
    static Speech* instance();
    std::string next;
#ifdef WIN32
    ULONG n;
    HRESULT hr;
    CComPtr<ISpObjectToken> token;
    CComPtr<ISpVoice> tts;
#else

    int heap_size;  // default scheme heap size
    int load_init_files; // we want the festival init files loaded

    //Set Voice

#endif
    std::wstring args;
    SayMode mode;
    SayMode nextMode;
    std::vector<std::string> names;
    void say(std::string, int type);
    void sayList(std::vector<std::string> &nameList, int type);
    bool listRunning;
    static bool visually_disabled;
    static Speech* ins;
protected:
    void run();
};

#endif
