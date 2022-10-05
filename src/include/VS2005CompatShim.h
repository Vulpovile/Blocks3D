#ifndef COMPAT_SHIM
#define COMPAT_SHIM
#include <sstream>
#include <string>

template<class T>
std::string toString(const T &value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

namespace std
{
	std::string to_string( int value ) {return toString(value);}
	std::string to_string( long value ) {return toString(value);}
	std::string to_string( long long value ) {return toString(value);}
	std::string to_string( unsigned value ) {return toString(value);}
	std::string to_string( unsigned long value ) {return toString(value);}
	std::string to_string( unsigned long long value ) {return toString(value);}
	std::string to_string( float value ) {return toString(value);}
	std::string to_string( double value ) {return toString(value);}
	std::string to_string( long double value ) {return toString(value);}
}
#endif