#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>
#include <limits>
#include <exception>
using namespace std ;

#define debug
#ifdef debug
#include <iostream>
#endif

const int MAXNUM = 1000000 ;
const int INITIAL = 1024 ;
const int NODP = numeric_limits<int>::max() ;

inline char dToC( int d ){
  return static_cast<char>(d+static_cast<int>('0')) ;
}

inline int cToD( char c ){
  return static_cast<int>(c)-static_cast<int>('0') ;
}

// used for analyze double number
// Return Value: true for OK, false for Error.
bool analyzeDouble( string &numPart, int &E, bool &sign, const string &src ) ;


// Exception for divide zero error.
namespace billjeff
{
  class DivideZero : public exception
  {
  private:
    int lineNumber_ ;
  public:
    DivideZero( int l = -1 ) throw() : lineNumber_(l)
    { }

    const char * what() const throw()
    {
      string s = "Divide Zero Error" ;
      //cerr << "" ;
      if ( lineNumber_ != -1 )
	s += ", at Line: " ;
      s += "!\n" ;
      return s.c_str() ;
    }
  } ;
}


// TODO - Provide tools to convert no-decimal number to 
//        decimal format number.

#endif
