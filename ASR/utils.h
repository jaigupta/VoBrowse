#ifndef _UTILS_
#define _UTILS_

#ifdef WIN32

#include <locale>
#include <iostream>
#include <string>
#include <sstream>

void widen( const std::string& str, std::wstring& incomingString);

#endif

#endif