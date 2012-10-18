#include "VoiceBase.h"

using namespace std ;
 
int main(int argc, char **argv)
{
#ifdef WIN32
    string gFile = "meeting2.xml";
    VoiceBase v(gFile);
    for(int i = 0; i <= 2; i++)
    {
        v.recognize();
    }
    v.addFile("jai");
    for(int i = 0; i <= 2; i++)
    {
        v.recognize();
    }
    v.clearFileList();
    v.addFile("deepak");
    for(int i = 0; i <= 2; i++)
    {
        v.recognize();
    }
    v.addFile("prakash");
    for(int i = 0; i <= 2; i++)
    {
        v.recognize();
    }
    return 0;
#else
    VoiceBase v(argc, argv);
    v.recognize_from_microphone();
    v.addFile("down");
    v.addFile("copy");
    v.addFile("pen");
    v.regenerateGrammar();
    v.recognize_from_microphone();
    v.recognize_from_microphone();
    v.recognize_from_microphone();
    v.recognize_from_microphone();
#endif
}
