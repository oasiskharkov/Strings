// code.cpp 
// written by Aleksei Klopkov v1.1 14/07/2016 

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <crtdbg.h>
#include "string.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::sort;

int main()
{
	FILE* pOut( nullptr );
	errno_t err = freopen_s( &pOut, "debug_out.txt", "w", stderr );

	if ( err )
		cout << "Error in freopen" << endl;

	_CrtSetDbgFlag( _CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF );
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
	_CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDERR );

	vector<string> strings;

	try 
	{
		while(true)
		{
			cout << "Input string: ";
			string s;
			cin >> s;
			if( s.IsNullOrEmpty( ) ) break;
			strings.push_back( s );
		}

		sort( strings.begin( ), strings.end( ), [] ( string a, string b ) { return a > b; } );

		typedef vector<string>::const_iterator CI;

		for( CI i = strings.begin( ); i != strings.end( ); i++ )
		{
			cout << *i << endl;
		}
	}
	catch( std::bad_alloc& ba )
	{
		cout << "Error was caught while allocating memory: "  << ba.what( ) << endl;
	}
	catch(...)
	{
		cout << "Something went wrong!" << endl;
	}
	
	return 0;
}
