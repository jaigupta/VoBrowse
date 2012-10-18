#ifndef _VOICE_BASE_H
#define _VOICE_BASE_H
#include <QString>

#ifdef WIN32

#pragma once
#include <windows.h>
#include <sphelper.h>
#include "utils.h"
#include <QMessageBox>
#include <map>

#pragma warning(disable:4995)

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "jdktrie.h"
#include "importinbuf.h"
typedef jdk_fasttree<int,128,char> my_tree;

#define MAX_FILE_NAME_LEN 255

enum VoiceBaseState{MAIN_MENU, GENERAL_WORDS};

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
    my_tree tree;
    std::multimap<std::string, std::string> fileMap;

public:
    VoiceBase(std::string gFile);
    std::string recognize();
    void addFileList(std::vector<std::string> word);
    void clearFileList();
    void loadDictionary();
    std::string VoiceBase::breakit(std::string fname);
    std::string VoiceBase::furtherBreak(std::string in);
    std::set<std::string> VoiceBase::getFileList(std::string recog);
    void loadSearchGrammar();
    void loadNotepadGrammar();
    void loadCommandGrammar();
    void regenerateGrammar() {};
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
#include <map>
#include <QDebug>

#include "jdktrie.h"
#include "importinbuf.h"
typedef jdk_fasttree<int,128,char> my_tree;

class VoiceBase
{
public:
    static const arg_t cont_args_def[] ;
    ps_decoder_t *ps;
    cmd_ln_t *config;
    FILE* rawfd;
    jmp_buf jbuf;
private:
    my_tree tree;
    std::multimap<std::string, std::string> fileMap;
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
    std::string recognize();
    void sighandler(int signo);
    void resumeRecording();
    void addFile(std::string filename);
    void clearFileList();
    void regenerateGrammar();
    void loadDictionary();
    void loadSearchGrammar();
    void loadCommandGrammar();
    void loadNotepadGrammar();
    std::set<std::string> getFileList(std::string);
    std::string breakit(std::string fname);
    std::string furtherBreak(std::string);
    ~VoiceBase();
};
#endif

#endif

