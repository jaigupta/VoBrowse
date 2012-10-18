#include "ControlThread.h"
using namespace std;

// control thread constructor
ControlThread::ControlThread(MainWindow *window):w(window)
{
#ifdef WIN32
    string gFile = "meeting2.xml";
    vBase = new VoiceBase(gFile);
#else
    char **ar;
    ar = (char**)malloc(sizeof(char*)*2);
    ar[0] = (char*)malloc(sizeof(char)*100);
    strcpy(ar[0], "voiceBase");
    vBase = new VoiceBase(1, ar);
#endif

    // connect to slots
    connect(this, SIGNAL(notifySaid(QString)), w, SLOT(notifySaid(QString)));
    connect(this, SIGNAL(openFile(QString)), w, SLOT(openByName(QString)));
    connect(w,    SIGNAL(pathChanged()),     this, SLOT(pathChanged()));
    connect(this, SIGNAL(forwardDir()),   w   , SLOT(forwardDir()));
    connect(this, SIGNAL(backDir()),      w   , SLOT(backDir()));
    connect(this, SIGNAL(searchSpoken(bool)), w->controlPanel, SLOT(searchButtonClicked(bool)));
    connect(this, SIGNAL(spokeSearchAlpha(char)), w->leftPanel, SLOT(addSearchAlpha(char)));
    connect(this, SIGNAL(setActiveTab(int)), w->leftPanel, SLOT(setActiveTab(int)));
    connect(this, SIGNAL(openNotepad(QString)), w->mypad, SLOT(readFromFile(QString)));
    connect(this, SIGNAL(notepadIncreaseFont()), w->mypad, SLOT(fontUp()));
    connect(this, SIGNAL(notepadDecreaseFont()), w->mypad, SLOT(fontDown()));
    connect(this, SIGNAL(notepadScrollUp()), w->mypad, SLOT(moveCursorUp()));
    connect(this, SIGNAL(notepadScrollDown()), w->mypad, SLOT(moveCursorDown()));
    connect(this, SIGNAL(notepadClose()), w->mypad, SLOT(hide()));
    connect(this, SIGNAL(changeDrive(const QString&)), w->leftPanel, SLOT(driveOpened(const QString&)));
    connect(this, SIGNAL(bookmarkthis(const QString &)), w->leftPanel, SLOT(addBookmark(const QString&)));
    sp.start();
}

// control thread destructor
ControlThread::~ControlThread(void)
{
}

// handler for file change event
void ControlThread::pathChanged()
{
    printf("going to regenerate files\n");
    //reload files in the new path
    reloadFiles();
    printf("going to regenerate grammar\n");
    // regenerate grammer for new path
    vBase->regenerateGrammar();
    printf("setting working as false");
    // control thread stops processing the event
    w->setWorking(false);
}

// return a single recognized alphabet
static char getAlpha(string &s)
{
    static string w[][2] = {    
        {"aaa","a"} ,
        {"aea","a"} ,
        {"bee", "b"},
        {"cee", "c"},   
        {"dee", "d"},
        {"ee", "e"} ,
        {"ef", "f"} ,
        {"gee", "g"},
        {"eh", "h"} ,
        {"aai", "i"},
        {"jay", "j"},
        {"kay", "k"},
        {"el", "l"} ,
        {"em", "m"} ,
        {"en", "n"} ,
        {"ao", "o"} ,
        {"pee", "p"},
        {"que", "q"},
        {"aar", "r"},
        {"aes", "s"},
        {"tee", "t"},
        {"you", "u"},
        {"we", "v"} ,
        {"double oo", "w"},
        {"double you", "w"},
        {"axe", "x"},
        {"why", "y"},
        {"zed", "z"},
        {"zee", "z"}
    };
    for(int i = 0; i<29; i++)
    {
        if(w[i][0] == s)
        {
            return w[i][1][0];
        }
    }
#ifndef WIN32
    // return a single recognized digit
    static string digits[10][2] = {
        {"zero", "0"},
        {"one",  "1"},
        {"two",  "2"},
        {"three","3"},
        {"four", "4"},
        {"five", "5"},
        {"six",  "6"},
        {"seven","7"},
        {"eight","8"},
        {"nine", "9"}};

    for(int i = 0; i<10; i++)
    {
        if(digits[i][0] == s)
        {
            return digits[i][1][0];
        }
    }
#endif
    return s[0];
}


// handler for running main thread
void ControlThread::run()
{
    w->setWorking(false);
    // load dictionary for current directory
    vBase->loadDictionary();
    reloadFiles();
    // generate grammer for current directory
    vBase->regenerateGrammar();
    qDebug()<<"loaded Grammar";
    string s;

    while(w && w->isVisible())
    {
        // waiting for processing to finish
        int i = 10;
        while(i-- && w->isWorking()){
            ControlThread::msleep(1000);
        }

        // recognise speech command
        s = vBase->recognize();
        //if command recognised
        if(s.size() > 0)
        {
            // handle 'open' command to open file/folder
            if(s.find("open")==0)
            {
                if(s.size() <=5) continue;
                string file_name = s.substr(5, s.size()-5);
                //emit notifySaid(QString(string("opening " + file_name).c_str()));
                std::set<string> files = vBase->getFileList(file_name);
                if(files.size() > 0) {
                    w->setWorking(true);
                    string filename = *(files.begin());
                    QString path = QDir(w->leftPanel->getCurrentDir()).absoluteFilePath(QString(filename.c_str()));
                    QFileInfo f(path);
                    if(f.isDir())
                        emit openFile(QString(files.begin()->c_str()));
                    else if(f.isFile()) {
                        // if file, open with text browser
                        emit openNotepad(path);
                        // load grammar for textpad commands
                        vBase->loadNotepadGrammar();
                        // recognise textpad commands
                        s = vBase->recognize();
                        while(1)
                        {
                            // increasing font
                            if(s.find("font up")==0)
                            {
                                emit notepadIncreaseFont();
                            }
                            // decreasing  font
                            else if(s.find("font down") == 0)
                            {
                                emit notepadDecreaseFont();
                            }
                            // scroll up
                            else if(s.find("navigate up") == 0)
                            {
                                emit notepadScrollUp();
                            }
                            // scroll down
                            else if(s.find("navigate down") == 0)
                            {
                                emit notepadScrollDown();
                            }
                            // close textpad
                            else if(s.find("close") == 0)
                            {
                                emit notepadClose();
                                break;
                            // stop reading text
                            }else if(s.find("turn silent"))
                            {
                                sp.stop();
                            }
                            // speak text again
                            else if(s.find("speak again"))
                            {
                                emit openNotepad(path);
                            }
                            s = vBase->recognize();
                        }
                        vBase->loadCommandGrammar();
                        reloadFiles();
                        vBase->regenerateGrammar();
                        w->setWorking(false);
                    }
                }else
                {
                    sp.say("empty file list returned\n", 1);
                }
            }
            // handle list file command to list all files
            else if(s.find("list files") == 0)
            {
                reloadFiles();
            }
            // moving up to the previous directory
            else if(s.find("move up") == 0)
            {
                w->setWorking(true);
                emit openFile(QString(".."));
            }

            else if(s.find("move back") == 0)
            {
                emit forwardDir();
            } 
            else if(s.find("move forward") == 0)
            {
                emit backDir();
            }
            else if(s.find("bookmark this") == 0)
            {
                QString path = w->leftPanel->getCurrentDir();
                emit bookmarkthis(path);
            }
            // handler for showing bookmarks
            else if(s.find("show bookmark") == 0)
            { 
                emit setActiveTab(2);
            }
            else if(s.find("show history") == 0)
            {
                emit setActiveTab(1);
            }else if(s.find("show find result") == 0)
            {
                emit setActiveTab(3);
            }else if(s.find("show browser") == 0)
            {
                emit setActiveTab(0);
            }
#ifdef WIN32
            else if(s.find("browse drive ") == 0)
            {
                emit changeDrive(QString(string(s.substr(13, s.size() - 13)+":\\").c_str()));
            }
            else if(s.find("show drives") == 0)
            {
                emit setActiveTab(4);
            }
#endif
            else if(s.find("close") == 0)
            {
                qApp->quit();
                return;
            }else if(s.find("find files") == 0)
            {
                emit searchSpoken(true);
                vBase->loadSearchGrammar();
                s = vBase->recognize();
                sp.say("Search Started", 1);
                while(1)
                {
                    if(s.find("done")==0)
                    {
                        emit spokeSearchAlpha(2);
                        break;
                    }
                    else if(s.find("cancel") == 0)
                    {
                        emit searchSpoken(false);
                        break;
                    }
                    else if(s.find("question") == 0)
                    {
                        emit spokeSearchAlpha('?');
                    }
                    else if(s.find("star") == 0)
                    {
                        emit spokeSearchAlpha('*');
                    }
                    else if(s.find("period") == 0)
                    {
                        emit spokeSearchAlpha('.');
                    }
                    else if(s.find("delete all") == 0)
                    {
                        emit spokeSearchAlpha(1);
                    }
                    else if(s.find("delete") == 0)
                    {
                        emit spokeSearchAlpha(0);
                    }
                    else{
                        emit spokeSearchAlpha(getAlpha(s));
                    }
                    s = vBase->recognize();
                }
                vBase->loadCommandGrammar();
                reloadFiles();
                vBase->regenerateGrammar();
            }else if(s.find("go silent") == 0)
            {
                sp.stop();
            }
            //emit notifySaid(QString(s.c_str()));
        }
    }
}

void ControlThread::reloadFiles()
{
    static string lastPath = "";
    string pathnew = w->leftPanel->getCurrentDir().toLocal8Bit().data();
    if(pathnew == lastPath) return;
    sp.say("Path changed to " + pathnew, 1);
    pathnew = lastPath;
    
    sp.say("Listing Files", 1);
    vBase->clearFileList();
    QStringList fList = w->getFileList();
    //fList = w->getFileList();
#ifdef WIN32
    vector<string> fnames;
#endif
    for(int i=0; i<fList.size(); i++)
    {
        if(fList.at(i).trimmed().size() > 0)
        {
#ifdef WIN32
            fnames.push_back(string(fList.at(i).toLocal8Bit().constData()));
#else
            vBase->addFile(string(fList.at(i).toLocal8Bit().constData()));
#endif
        }
    }
#ifdef WIN32
    sp.sayList(fnames, 1);
    vBase->addFileList(fnames);
#endif
    //emit notifySaid(QString("reset to %1 files").arg(QString::number(p)));
}
