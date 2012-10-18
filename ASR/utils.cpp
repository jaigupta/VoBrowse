#include "utils.h"

using namespace std;

void widen( const string& str, wstring& incomingString)
{
    wostringstream wstm;
    const ctype<wchar_t>& ctfacet =
    use_facet< ctype<wchar_t> >( wstm.getloc() );
     
    for( size_t i=0; i<str.size(); ++i )
    wstm << ctfacet.widen( str[i] );
     
    wstm << L"\n";
    incomingString = wstm.str();
}
