// Implementation of self-written string class
// written by Aleksei Klopkov v1.1 14/07/2016

#include <iostream>
#include "string.h"

// default constructor
string::string( void )
{
	str = nullptr;
}

// constructor
string::string( const char* s )
{
	int length = strlen( s ) + 1;
	str = new char[ length ];
	strcpy( str, s );
}

// copy constructor 
string::string( const string & s )
{
	str = nullptr;
	CopyDataFrom( s );
}

// move constructor
string::string( string && s )
{
	str = s.str;
	s.str = nullptr;
}

// destructor
string::~string( void )
{
	delete [ ] str;
}

/*
// inside overloaded operator + which has a self-written string as a right operand
string string::operator + ( const string & s ) const
{
	int length  = Length( ) + strlen( s.str ) + 1;

	string temp;
	
	temp.str = new char [ length ];

	strcpy( temp.str, str );

	strcat( temp.str, s.str );

	return s;
}*/

// inside overloaded operator + which has an old-style string as a right operand
string string::operator + ( const char* s ) const
{
	int length  = Length( ) + strlen( s )  + 1;
	
	string temp;
	
	temp.str = new char [ length ];

	strcpy( temp.str, str );
	
	strcat( temp.str, s );

	return temp;
}

// assignment operator
string& string::operator = ( const string & s )
{
	if ( this != &s )
	{
		CopyDataFrom( s );
	}
	return *this;
}

// move assignment operator
string& string::operator = ( string && s )
{
	if ( &s != this )
	{
		char* new_str = s.str;

		s.str = str;

		str = new_str;
	}
	return *this;
}

// overloaded comparsion operator <
bool string::operator < ( const string& s ) const
{
	return StrCmp( str, s.str ) < 0;
}

// overloaded comparsion operator >
bool string::operator > ( const string& s ) const
{
	// return StrCmp( str, s.str ) > 0
	return s < *this;
}

// overloaded comparison operator ==
bool string::operator == ( const string& s ) const
{
	// return StrCmp( str, s.str ) == 0
	return !( *this < s ) && !( *this > s );
}

// overloaded comparison operator !=
bool string::operator != (const string& s) const
{
	return ( *this > s ) || ( s > *this );
}

// overloaded comparsion operator >= 
bool string::operator >= ( const string& s ) const
{
	return *this > s || *this == s;
}

// overloaded comparsion operator <=
bool string::operator <= ( const string& s ) const
{
	return *this < s || *this == s;
}

// additional function, which is used in a copy-constructor or in an assignment operator
void string::CopyDataFrom( const string & s )
{
	delete [ ] str;

	int length = strlen( s.str ) + 1;
	
	str = new char[ length ];

	strcpy( str, s.str );
}

// overloaded operator += which has a self-written string as a right operand
string& string::operator += ( const string& s ) 
{
	/*int length = Length( ) + s.Length( ) + 1;
	char* temp = new char [ length ];
	strcpy( temp, str );
	delete [ ] str;
	strcat( temp, s.str );
	str = temp;
	return *this;*/

	string& temp = *this + s;

	*this = temp;

	return *this;
}

// overloaded operator += which has an old-style char string as a right operand
string& string::operator += ( const char* s )
{
	/*int length = Length( ) + strlen( s ) + 1;
	char* temp = new char [ length ];
	strcpy( temp, str );
	delete [ ] str;
	strcat( temp, s );
	str = temp;
	return *this;*/

	string& temp = *this + s;

	*this = temp;

	return *this;
}

// self written version of strcmp which ignores case of letters
int string::StrCmp( const char* str1, const char* str2 ) const
{
	while( *str1 && *str2 && tolower( *str1 ) == tolower ( *str2 ) )
	{
		str1++; str2++;
	}
	return tolower( *str1 ) - tolower( *str2 );
}

// overloaded << output operator
std::ostream& operator << ( std::ostream& o, const string& str )
{
	o << str.GetString( ); 
	return o;
}

// overloaded >> input operator
std::istream& operator >> ( std::istream& i, string& str )
{
	int buf_size = 16;
	char* s = new char[ buf_size ];
	char c;
	char* start = s;

	while( ( c = getchar( ) ) != '\n' )
	{	
		
		if( s - start == buf_size )
		{
			buf_size *= 2;
			char* temp = new char[ buf_size ];
			memcpy( temp, start, buf_size );
			delete [ ] start; 
			start = temp;
			s = start + buf_size / 2;
		}
		*( s++ ) = c;
	}

	*s = '\0';
	str = string( start );
	delete [ ] start;
	return i;
}

// overloaded operator + as a global function, which has an old-style char string as a left operand
string operator + ( const char* str, const string& s )
{
	int length  = s.Length( ) + strlen( str ) + 1;

	char* temp =  new char [ length ];

	strcpy( temp, str );

	strcat( temp, s.GetString( ) );

	string st( temp );

	delete [ ] temp;

	return st;
}

// overloaded operator + as a global function which has self-written strings as left and right operands
string operator + ( const string& str1, const string& str2 )
{
	int length  = str1.Length( ) + str2.Length( ) + 1;

	char* temp = new char[ length ];

	strcpy( temp, str1.GetString( ) );

	strcat( temp, str2.GetString( ) );
	
	string s( temp );

	delete [] temp;

	return s;
}