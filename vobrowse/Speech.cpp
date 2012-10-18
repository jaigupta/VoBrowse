#include "Speech.h"
#include "utils.h"
using namespace std;

bool Speech::visually_disabled = true;
Speech* Speech::ins = NULL;
Speech::Speech(void)
{
#ifdef WIN32
    tts.CoCreateInstance(CLSID_SpVoice);
    hr = SpGetDefaultTokenFromCategoryId( SPCAT_VOICES, &token, FALSE);
    hr = tts->SetVoice(token);
#else
    heap_size = 210000;
    load_init_files = 1;
    festival_initialize(load_init_files,heap_size);
    festival_eval_command("(voice_ked_diphone)");
#endif
    next = "";
    mode = Single;
    Speech::ins = this;
}

void Speech::say(std::string line, int type)
{
    if(!visually_disabled && type == 1) 
        return;
    next = line;
    listRunning = false;
    nextMode = Single;
}

void Speech::sayList(vector<string> &sayList, int type)
{
    if(!visually_disabled && type == 1)
        return;
    names = sayList;
    listRunning = false;
    nextMode = FullList;
}

void Speech::run()
{
    while(1)
    {
        if(next == "" && names.size() == 0)
        {
            Speech::msleep(100);
            continue;
        }
        if(nextMode == Single)
        {
#ifdef WIN32
            std::wstring ms;
            widen(next, ms);
            next = "";
            tts->Speak(ms.c_str(),SPF_IS_XML | SPF_ASYNC, &n);
            tts->WaitUntilDone(-1);
#else
        string tmp = next;
        next = "";
        festival_say_text(tmp.c_str());
#endif
        }
        else {
            int i = 0;
            listRunning = true;
            while(listRunning && i < names.size())
            {
#ifdef WIN32
                std::wstring ms;
                widen(names[i], ms);
                tts->Speak(ms.c_str(),SPF_IS_XML | SPF_ASYNC, &n);
                tts->WaitUntilDone(-1);
#else
                string temp = names[i];
                festival_say_text(temp.c_str());
#endif
                i++;
            }
            listRunning = false;
            names.clear();
        }
    }
}

void Speech::stop()
{
    listRunning = false;
}

Speech::~Speech(void)
{
#if 0
    tts.Release();
    token.Release();
#endif
}

Speech* Speech::instance()
{
    return ins;
}