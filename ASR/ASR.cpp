#if 0
#include <windows.h>
#include <sphelper.h>

#pragma warning(disable:4995)
#include <iostream>

bool done = false;

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)
{
 std::wcout << "Exiting . . ." << std::endl;
 done = true;

 return TRUE;
}

int wmain(int argc, wchar_t **argv)
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

 if ( argc != 2 )
  std::wcout << "Enter the name of a grammar file to test." << std::endl;

 else
 {
  SetConsoleCtrlHandler(HandlerRoutine, TRUE);

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
    std::cout<<"Using shared recogniser"<<std::endl;
  }

  
  hr = cpEngine->CreateRecoContext(&cpRecoCtx);

  hr = cpRecoCtx->SetNotifyWin32Event();
  hEvent = cpRecoCtx->GetNotifyEventHandle();
  ullEvents = SPFEI(SPEI_RECOGNITION) | SPFEI(SPEI_FALSE_RECOGNITION);
  hr = cpRecoCtx->SetInterest(ullEvents, ullEvents);

  hr = cpRecoCtx->CreateGrammar(1, &cpGram);
  hr = cpGram->LoadCmdFromFile(argv[1], SPLO_STATIC);

  hr = cpGram->SetRuleState(0, 0, SPRS_ACTIVE);

  while ( !done )
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
  

  cpGram.Release();
  cpRecoCtx.Release();
  cpEngine.Release();

  CoUninitialize();  
 }

 return 0;
}

#endif
