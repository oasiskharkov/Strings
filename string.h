// Class-container which represents string and overloaded operators for it
// written by Aleksei Klopkov v1.1 14/07/2016

#ifndef _STRING_H
#define _STRING_H

class string
{
private:
	char* str;
	void CopyDataFrom( const string& _str );
	int StrCmp( const char* str1, const char* str2 ) const;
public:
	string( );
	string( const char* s );

	string( const string & s );
	string( string && s );

	~string( void );

	//string operator + ( const string & _string ) const;
	string operator + ( const char* s ) const;
	string& operator = ( const string & s );
	string& operator = ( string && s );
	string& operator += ( const string& s );
	string& operator += ( const char* s );
	bool operator < ( const string& s ) const;
	bool operator == ( const string& s ) const;
	bool operator != ( const string& s ) const;
	bool operator > ( const string& s ) const;
	bool operator >= ( const string& s ) const;
	bool operator <= ( const string& s ) const;

	int Length( ) const;
	char* GetString( ) const;
	bool IsNullOrEmpty( ) const;
};

// returns string length
inline int string::Length( ) const
{
	return strlen( str );
}

// checks is string NULL or empty
inline bool string::IsNullOrEmpty( ) const
{
	return str == NULL || strlen( str ) == 0;
}

// returns string
inline char* string::GetString( ) const
{
	return str;
}

string operator + ( const string& str1, const string& str2 );
string operator + ( const char* str, const string& s );
std::ostream& operator << ( std::ostream& o, const string& str );
std::istream& operator >> ( std::istream& i, string& str);

#endif