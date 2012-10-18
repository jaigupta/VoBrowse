#include "VoiceBase.h"

#ifdef WIN32

VoiceBase::VoiceBase(std::string gFile)
{
    // Convert and store grammar File name
    widen(gFile, grammarFile);
    
    std::wcout << "Speak phrases defined in the grammar being tested" << std::endl;
    std::wcout << "Press ctrl/c to quit" << std::endl;
    
    CoInitialize(0);
    hr = cpEngine.CoCreateInstance(CLSID_SpInprocRecognizer);
    // Get the default audio input token. 
    
    if (SUCCEEDED(hr))
    {
        // Set the audio input to our token.
        hr = SpGetDefaultTokenFromCategoryId(SPCAT_AUDIOIN, &cpObjectToken);
        hr = cpEngine->SetInput(cpObjectToken, TRUE);
        std::cout<<"Using Dedicated Recogniser"<<std::endl;
    }else {
        hr = cpEngine.CoCreateInstance(CLSID_SpSharedRecognizer);
        std::cout<<"Using Shared recogniser"<<std::endl;
    }
    
    hr = cpEngine->CreateRecoContext(&cpRecoCtx);

    hr = cpRecoCtx->SetNotifyWin32Event();
    hEvent = cpRecoCtx->GetNotifyEventHandle();
    ullEvents = SPFEI(SPEI_RECOGNITION) | SPFEI(SPEI_FALSE_RECOGNITION);
    hr = cpRecoCtx->SetInterest(ullEvents, ullEvents);
    hr = cpRecoCtx->CreateGrammar(1, &cpGram);

    // deactivate the grammar to prevent premature recognitions to an "under-construction" grammar
    hr = cpGram->SetGrammarState(SPGS_DISABLED);

    // Setup Grammar File
    hr = cpGram->LoadCmdFromFile(grammarFile.c_str(), SPLO_DYNAMIC);

    this->clearFileList();

}

void VoiceBase::recognize()
{
    WaitForSingleObject(hEvent, 10000);

    while ( evt.GetFrom(cpRecoCtx) == S_OK )
    {
        if ( evt.eEventId == SPEI_FALSE_RECOGNITION )
            std::wcout << "No recognition" << std::endl;

        else
        {
            pPhrase = evt.RecoResult();
            hr = pPhrase->GetPhrase(&pParts);

            hr = pPhrase->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, FALSE, &pwszText, 0);

            std::wcout << pwszText << " (" << pParts->Rule.Confidence << ") " << std::endl;

            CoTaskMemFree(pParts);
            CoTaskMemFree(pwszText);
        }
    }
}

void VoiceBase::addFile(std::string word)
{
    hr = cpGram->SetGrammarState(SPGS_DISABLED);

    SPSTATEHANDLE hRule;

    // first retrieve the dynamic rule ADDRESS_BOOK
    hr = cpGram->GetRule(L"FILENAME", NULL, SPRAF_Dynamic, FALSE, &hRule);
    // Check hr
    
    std::wstring wordlong;
    widen(word, wordlong);
    hr = cpGram->AddWordTransition(hRule, NULL, wordlong.c_str(), NULL, SPWT_LEXICAL, 1, NULL);
    
    // commit the grammar changes, which updates the grammar inside SAPI,
    //    and notifies the SR Engine about the rule change (i.e. "ADDRESS_BOOK"
    hr = cpGram->Commit(NULL);
    // Check hr
    
    // activate the grammar since "construction" is finished,
    //    and ready for receiving recognitions
    hr = cpGram->SetGrammarState(SPGS_ENABLED);


    hr = cpGram->SetRuleState(0, 0, SPRS_ACTIVE);
}

void VoiceBase::clearFileList()
{
    hr = cpGram->SetGrammarState(SPGS_DISABLED);

    SPSTATEHANDLE hRule;

    // first retrieve the dynamic rule ADDRESS_BOOK
    hr = cpGram->GetRule(L"FILENAME", NULL, SPRAF_Dynamic, FALSE, &hRule);
    // Check hr

    // clear the placeholder text, and everything else in the dynamic ADDRESS_BOOK rule
    hr = cpGram->ClearRule(hRule);

    // commit the grammar changes, which updates the grammar inside SAPI,
    //    and notifies the SR Engine about the rule change (i.e. "ADDRESS_BOOK"
    hr = cpGram->Commit(NULL);
    // Check hr
    
    // activate the grammar since "construction" is finished,
    //    and ready for receiving recognitions
    hr = cpGram->SetGrammarState(SPGS_ENABLED);


    hr = cpGram->SetRuleState(0, 0, SPRS_ACTIVE);

}

VoiceBase::~VoiceBase(void)
{
    cpGram.Release();
    cpRecoCtx.Release();
    cpEngine.Release();
    CoUninitialize();  
}

#else

#include "VoiceBase.h"

using namespace std;
const arg_t VoiceBase::cont_args_def [] = {
	POCKETSPHINX_OPTIONS,
	/* Argument file. */
	{ "-argfile",
	  ARG_STRING,
	  NULL,
	  "Argument file giving extra arguments." },
	{ "-adcdev", 
	  ARG_STRING, 
	  NULL, 
	  "Name of audio device to use for input." },
	{ "-infile", 
	  ARG_STRING, 
	  NULL, 
	  "Audio file to transcribe." },
	{ "-time", 
	  ARG_BOOLEAN, 
	  "no", 
	  "Print word times in file transcription." },
	CMDLN_EMPTY_OPTION
    };

void
VoiceBase::sighandler(int signo)
{
    longjmp(jbuf, 1);
}

VoiceBase::VoiceBase(int argc, char* argv[])
{
    char const *cfg;

    if (argc == 2) {
        // If there is a input configuration file name, load from there.
        config = cmd_ln_parse_file_r(NULL, cont_args_def, argv[1], TRUE);
    }
    else {
        // If no input configuration file name, load from default settings.
        config = cmd_ln_parse_r(NULL, cont_args_def, argc, argv, FALSE);
    }
    
    /* Handle argument file as -argfile. */
    if (config && (cfg = cmd_ln_str_r(config, "-argfile")) != NULL) {
        config = cmd_ln_parse_file_r(config, cont_args_def, cfg, FALSE);
    }
    
    printf("CFG %s\n", cfg);
    
    if (config == NULL)
        E_FATAL("Failed top open audio device\n");

    ps = ps_init(config);
    if (ps == NULL)
        E_FATAL("Failed top open audio device\n");
    
    E_INFO("%s COMPILED ON: %s, AT: %s\n\n", argv[0], __DATE__, __TIME__);
    
    if (cmd_ln_str_r(config, "-infile") != NULL) {
        printf("\n\n\nRecognising from file\n\n\n");
	recognize_from_file();
    } else {
        
        /* Make sure we exit cleanly (needed for profiling among other things) */
/*
#if !defined(GNUWINCE) && !defined(_WIN32_WCE) && !defined(__SYMBIAN32__)
	signal(SIGINT, &sighandler);
#endif
  */      
    }
    
    if ((ad = ad_open_dev(cmd_ln_str_r(config, "-adcdev"),
                          (int)cmd_ln_float32_r(config, "-samprate"))) == NULL)
        E_FATAL("Failed top open audio device\n");
    printf("Sample rate is : %d, %s\n", (int)cmd_ln_float32_r(config, "-samprate"), cmd_ln_str_r(config, "-adcdev"));
    /* Initialize continuous listening module */
    if ((cont = cont_ad_init(ad, ad_read)) == NULL)
        E_FATAL("Failed to initialize voice activity detection\n");
    printf("Signal level :%d %d\n", ad->sps, ad->bps);
    if (ad_start_rec(ad) < 0)
        E_FATAL("Failed to start recording\n");
    if (cont_ad_calib(cont) < 0)
        E_FATAL("Failed to calibrate voice activity detection\n");
    ad_stop_rec(ad);
/*
    FILE *f = fopen("cmu07a.dic", "r");
    char s[1000];
    if(!f)
	cout<<"failes"<<endl;
    while(fscanf(f, "%s", s))
    {
	string s1 = s;
	dic_words.insert(s1);
//	cout<<"inseting"<<endl;
	fgets(s, 1000, f);
    }
    fclose(f); 
    set<std::string>::iterator it = dic_words.begin();
    for(int i=0; i<10; i++)
    {
	cout<<*it<<endl;
	it++;
	}*/
}
int32
VoiceBase::ad_file_read(ad_rec_t * ad, int16 * buf, int32 max)
{
    size_t nread;
    
    nread = fread(buf, sizeof(int16), max, rawfd);
    
    return (nread > 0 ? nread : -1);
}

void
VoiceBase::print_word_times(int32 start)
{
	ps_seg_t *iter = ps_seg_iter(ps, NULL);
	while (iter != NULL) {
		int32 sf, ef, pprob;
		float conf;
		
		ps_seg_frames (iter, &sf, &ef);
		pprob = ps_seg_prob (iter, NULL, NULL, NULL);
		conf = logmath_exp(ps_get_logmath(ps), pprob);
		printf ("%s %f %f %f\n", ps_seg_word (iter), (sf + start) / 100.0, (ef + start) / 100.0, conf);
		iter = ps_seg_next (iter);
	}
}

/*
 * Continuous recognition from a file
 */
void
VoiceBase::recognize_from_file() {
    /*
      cont_ad_t *cont;
    ad_rec_t file_ad = {0};
    int16 adbuf[4096];
    const char* hyp;
    const char* uttid;
    int32 k, ts, start;

    char waveheader[44];
    rawfd = fopen(cmd_ln_str_r(config, "-infile"), "rb");
    fread(waveheader, 1, 44, rawfd);

    file_ad.sps = (int32)cmd_ln_float32_r(config, "-samprate");
    file_ad.bps = sizeof(int16);

    if ((cont = cont_ad_init(&file_ad, ad_file_read)) == NULL) {
        E_FATAL("Failed to initialize voice activity detection");
    }
    if (cont_ad_calib(cont) < 0)
        E_FATAL("Failed to calibrate voice activity detection\n");
    rewind (rawfd);

    for (;;) {

	while ((k = cont_ad_read(cont, adbuf, 4096)) == 0);
	
        if (k < 0) {
    	    break;
    	}

        if (ps_start_utt(ps, NULL) < 0)
            E_FATAL("ps_start_utt() failed\n");

        ps_process_raw(ps, adbuf, k, FALSE, FALSE);
        
        ts = cont->read_ts;
        start = (ts - k) / file_ad.sps * 100;
        
        for (;;) {
            if ((k = cont_ad_read(cont, adbuf, 4096)) < 0)
            	break;

            if (k == 0) {
                ///*
                // * No speech data available; check current timestamp with most recent
                // * speech to see if more than 1 sec elapsed.  If so, end of utterance.
                 //* /
                if ((cont->read_ts - ts) > DEFAULT_SAMPLES_PER_SEC)
                    break;
            }
            else {
                /* New speech data received; note current timestamp * /
                ts = cont->read_ts;
            }


            ps_process_raw(ps, adbuf, k, FALSE, FALSE);
        }

        ps_end_utt(ps);
        
        if (cmd_ln_boolean_r(config, "-time")) {
	    print_word_times(start);
	} else {
	    hyp = ps_get_hyp(ps, NULL, &uttid);
            printf("%s: %s\n", uttid, hyp);
        }
        fflush(stdout);	
    }

    cont_ad_close(cont);
    fclose(rawfd);*/
}

/* Sleep for specified msec */
void VoiceBase::sleep_msec(int32 ms)
{
#if (defined(WIN32) && !defined(GNUWINCE)) || defined(_WIN32_WCE)
    Sleep(ms);
#else
    /* ------------------- Unix ------------------ */
    struct timeval tmo;

    tmo.tv_sec = 0;
    tmo.tv_usec = ms * 1000;

    select(0, NULL, NULL, NULL, &tmo);
#endif
}

/*
 * Main utterance processing loop:
 *     for (;;) {
 * 	   wait for start of next utterance;
 * 	   decode utterance until silence of at least 1 sec observed;
 * 	   print utterance result;
 *     }
 */
std::string VoiceBase::recognize_from_microphone()
{
    resumeRecording();
    /* Indicate listening for next utterance */
    printf("READY....\n");
    fflush(stdout);
    fflush(stderr);
    
    /* Wait data for next utterance */
    while ((k = cont_ad_read(cont, adbuf, 4096)) == 0)
	sleep_msec(100);
    
    if (k < 0)
	E_FATAL("Failed to read audio\n");
    
    /*
     * Non-zero amount of data received; start recognition of new utterance.
     * NULL argument to uttproc_begin_utt => automatic generation of utterance-id.
     */
    if (ps_start_utt(ps, NULL) < 0)
	E_FATAL("Failed to start utterance\n");
    ps_process_raw(ps, adbuf, k, FALSE, FALSE);
    printf("Listening...\n");
    fflush(stdout);
    
    /* Note timestamp for this first block of data */
    ts = cont->read_ts;
    
    /* Decode utterance until end (marked by a "long" silence, >1sec) */
    for (;;) {
	/* Read non-silence audio data, if any, from continuous listening module */
	if ((k = cont_ad_read(cont, adbuf, 4096)) < 0)
	    E_FATAL("Failed to read audio\n");
	if (k == 0) {
	    /*
	     * No speech data available; check current timestamp with most recent
	     * speech to see if more than 1 sec elapsed.  If so, end of utterance.
	     */
	    if ((cont->read_ts - ts) > DEFAULT_SAMPLES_PER_SEC)
		break;
	}
	else {
	    /* New speech data received; note current timestamp */
	    ts = cont->read_ts;
	}
	
	/*
	 * Decode whatever data was read above.
	 */
	rem = ps_process_raw(ps, adbuf, k, FALSE, FALSE);
	
	/* If no work to be done, sleep a bit */
	if ((rem == 0) && (k == 0))
	    sleep_msec(20);
    }
    
    /*
     * Utterance ended; flush any accumulated, unprocessed A/D data and stop
     * listening until current utterance completely decoded
     */
    ad_stop_rec(ad);
    while (ad_read(ad, adbuf, 4096) >= 0);
    cont_ad_reset(cont);
    
    printf("Stopped listening, please wait...\n");
    fflush(stdout);
    /* Finish decoding, obtain and print result */
    ps_end_utt(ps);
    hyp = ps_get_hyp(ps, NULL, &uttid);
    if(hyp)
    {
        printf("%s: %s\n", uttid, hyp);
        fflush(stdout);
        return std::string(hyp);
    }
    return std::string("");
}

void VoiceBase::resumeRecording()
{
    /* Resume A/D recording for next utterance */
    int f;
    if ((f = ad_start_rec(ad)) < 0)
	E_FATAL("Failed to start recording\n");
    printf("\n----\n\n %d \n\n---\n", f);
}

void VoiceBase::addFile(string file_name)
{
    flist.push_back(file_name);
}

void VoiceBase::clearFileList()
{
    flist.clear();
}

string VoiceBase::breakit(string fname)
{
    string s = string(1, fname[0]);
    int i = 1;
    while(i < fname.size())
    {

	if(isdigit(fname[i]))
	{
	    switch(fname[i])
	    {
	    case '1':
		s = s + " one";
		break;
	    case '2':
		s = s + " two";
		break;
	    case '3':
		s = s + " three";
		break;
	    case '4':
		s = s + " four";
		break;
	    case '5':
		s = s + " five";
		break;
	    case '6':
		s = s + " six";
		break;
	    case '7':
		s = s + " seven";
		break;
	    case '8':
		s = s + " eight";
		break;
	    case '9':
		s = s + " nine";
		break;
	    case '0':
		s = s + " zero";
		break;
	    }
	}else if( isalpha(fname[i]) && (islower(fname[i-1]) ^ islower(fname[i])) )
	{
	    s = s + " " + string(1, tolower(fname[i]));
	}else if(isalpha(fname[i])){
	    s = s + string(1, tolower(fname[i]));
	}else {
	    s = s + " ";
	}
	i++;
    }
    return s;
}

void VoiceBase::regenerateGrammar()
{
    /*
    FILE *f = fopen("mygram.txt", "w");
    fprintf(f, "<s> back </s>\n<s> cancel </s>\n<s> up </s>\n<s> forward </s>\n<s> ok </s>\n");
    for(int i=0; i<flist.size(); i++)
    {
	fprintf(f, "<s> open %s </s>\n", breakit(flist[i]).c_str());
    }
    fclose(f);
    system("text2wfreq < mygram.txt | wfreq2vocab > mygram.vocab && text2idngram -vocab mygram.vocab -idngram mygram.idngram < mygram.txt && idngram2lm -vocab_type 0 -idngram mygram.idngram -vocab mygram.vocab -arpa mygram.arpa && sphinx_lm_convert -i mygram.arpa -o mygram.dmp && sphinx_lm_convert -i mygram.dmp -ifmt dmp -o mygram.lm -ofmt arpa");
    config = cmd_ln_init(NULL, ps_args(), TRUE,
			 "-hmm", MODELDIR "/hmm/en_US/hub4wsj_sc_8k",
			 "-lm", "mygram.lm",
			 "-dict", "cmu07a.dic",
			 NULL);
    */
    FILE *f = fopen("mygram.jsgf", "w");
    fprintf(f, "#JSGF V1.0;\n"
	    "grammar com;\n"
	    "public <command> = ( close | back |  up  | forward | <open> | <search> );\n"
	    "<search> = search ( a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | y | z )+; \n"
	    "<open> = open <filename>;\n<filename> = (");
    for(int i=0; i<flist.size(); i++)
    {
	if(i!=0)
	    fprintf(f, "| %s ", breakit(flist[i]).c_str());
	else
	    fprintf(f, " %s ", breakit(flist[i]).c_str());
    }
    fprintf(f, ");\n");
    fclose(f);
    config = cmd_ln_init(NULL, ps_args(), TRUE,
			 "-samprate", "16000",
			 "-jsgf", "mygram.jsgf",
			 NULL);
    
    if (config == NULL)
        E_FATAL("1Failed top open audio device\n");

    ps = ps_init(config);
    if (ps == NULL)
        E_FATAL("2Failed top open audio device\n");
    
    
    /* Initialize continuous listening module */
    if ((cont = cont_ad_init(ad, ad_read)) == NULL)
        E_FATAL("Failed to initialize voice activity detection\n");
    if (ad_start_rec(ad) < 0)
        E_FATAL("Failed to start recording\n");
    if (cont_ad_calib(cont) < 0)
        E_FATAL("Failed to calibrate voice activity detection\n");
    ad_stop_rec(ad);
    cout<<"Grammar reloaded"<<endl;
    
}
VoiceBase::~VoiceBase()
{
    cont_ad_close(cont);
    ad_close(ad);
    ps_free(ps);
}

#endif
