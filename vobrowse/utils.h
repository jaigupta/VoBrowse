#ifndef _UTILS_H
#define _UTILS_H

#include <iostream>
#include <string>
#include <sstream>

#ifdef WIN32

#include <locale>

void widen( const std::string& str, std::wstring& incomingString);

#endif


enum EditMode{ None, Search };

#endif
