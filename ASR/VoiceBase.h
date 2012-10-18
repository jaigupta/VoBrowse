#ifndef _VOICE_BASE_H
#define _VOICE_BASE_H

#ifdef WIN32

#pragma once
#include <windows.h>
#include <sphelper.h>
#include "utils.h"

#pragma warning(disable:4995)

#include <iostream>

#define MAX_FILE_NAME_LEN 255

class VoiceBase
{
    LPWSTR pwszText;
    HANDLE hEvent;
    HRESULT hr;
    CSpEvent evt;
    SPPHRASE *pParts;
    ISpPhrase *pPhrase;
    ULONGLONG ullEvents;
    CComPtr<ISpRecognizer> cpEngine;
    CComPtr<ISpRecoContext> cpRecoCtx;
    CComPtr<ISpRecoGrammar> cpGram;
    CComPtr<ISpObjectToken>      cpObjectToken;
    std::wstring grammarFile;

public:
    VoiceBase(std::string gFile);
    void recognize();
    void addFile(std::string word);
    void clearFileList();
    ~VoiceBase(void);
};

#else

#include <stdio.h>
#include <string.h>

#if !defined(_WIN32_WCE)
#include <signal.h>
#include <setjmp.h>
#endif
#if defined(WIN32) && !defined(GNUWINCE)
#include <time.h>
#else
#include <sys/types.h>
#include <sys/time.h>
#endif

#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/cont_ad.h>

#include "pocketsphinx.h"
#include <string>
#include <vector>
#include <set>
#include <iostream>

class VoiceBase
{
public:
    static const arg_t cont_args_def[] ;
    ps_decoder_t *ps;
    cmd_ln_t *config;
    FILE* rawfd;
    jmp_buf jbuf;
private:
    // Variables from recognise from microphone
    ad_rec_t *ad;
    int16 adbuf[4096];
    int32 k, ts, rem;
    char const *hyp;
    char const *uttid;
    cont_ad_t *cont;
    char word[256];
    std::set<std::string> dic_words;
    std::vector<std::string> flist;
public:
    VoiceBase(int argc, char* argv[]);
    int32 ad_file_read(ad_rec_t * ad, 
		       int16 * buf, 
		       int32 max);
    void print_word_times(int32 start);
    void recognize_from_file();
    void sleep_msec(int32 ms);
    std::string recognize_from_microphone();
    void sighandler(int signo);
    void resumeRecording();
    void addFile(std::string filename);
    void clearFileList();
    void regenerateGrammar();
    std::string breakit(std::string fname);
    ~VoiceBase();
};
#endif

#endif

