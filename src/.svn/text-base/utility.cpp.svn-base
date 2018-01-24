#include "utility.h"

#define debug


bool analyzeDouble( string &numPart, int &E, bool &sign, const string &src ) 
{
  if ( src == "" )
  {
    numPart = "0" ;
    E = 0 ;
    sign = true ;
    return true ;
  }

  numPart = "" ;
  bool numFlag, eFlag ;
  numFlag = eFlag = false ;

  // E is int type, so the exponent cannot exceed 2^32-1;
  E = 0 ;

  int len = src.length() ;

  int state = 0 ; // 0 - start, 1 - number, 2 - process E part, 3 - end.
  int ptr = 0 ;
  int dpPos = 0 ; 
  while ( state != 3 )
  {
    /*
    if ( ptr >= len )
      break ;
    */
#ifdef debug1
    cout << "state=" << state << endl ;
    cout << "src = " << src << endl ;
    cout << "ptr=" << ptr << ", " << src[ptr] << endl ;
#endif

    switch(state)
    {
    case 0:
      if ( src[ptr] == '.' )
      {
	state = 1 ;
	sign = true ;
	break ;
      }
      if ( src[ptr] == '+' || src[ptr] == '-' || isdigit(src[ptr]) )
      {
	if ( src[ptr] == '+' )
	{
	  sign = true ;
	  ++ptr ;
	}
	else if ( src[ptr] == '-' )
	{
	  sign = false ;
	  ++ptr ;
	}
	else
	  sign = true ;
	// process leading zeroes
	while ( src[ptr] == '0' && ptr < len )
	{
	  ++ptr ;
	} 
	state = 1 ;
      }
      else
	return false ;
      break ;
    

    case 1: // process number before E or e
      {
	if ( ptr >= len )
	{
	  state = 2 ;
	  break ;
	}
	bool decimalPoint = false ;
	bool zeroFlag = false ;
	/* 0.00000123, eg. this flag is to indicate whether there is no-zero
	 * digits before ".".
	 */
	bool dpFlag = false ; 
	if ( isdigit(src[ptr]) )
	  zeroFlag = true ;
	while ( src[ptr] != 'E' && src[ptr] != 'e' && ptr < len )
	{
#ifdef debug1
	  cout << "---\ndpPos = " << dpPos << "\nptr = " << ptr << endl ;
#endif
	  if ( src[ptr] == '.' )
	  {
	    if ( !decimalPoint )
	    {
	      /*
	      if ( numPart == "" )
		numPart = "0" ;
	      numPart += '.' ;
	      */
	      decimalPoint = true ;
	      if ( zeroFlag )
		numPart += '.' ;
	      else
		dpPos = 0 ;
	      ++ptr ;
	    }
	    else
	      return false ; // error, two or more consecutive '.' 
	    continue ;
	  }
	  else if ( isdigit(src[ptr]) )
	  {
	    if ( src[ptr] != '0' )
	    {
	      zeroFlag = true ;
	      numPart += src[ptr] ;
	      if ( !decimalPoint && !dpFlag )
		dpFlag = true ;
	      if ( decimalPoint && !dpFlag ) 
		++dpPos ;
	    }
	    else if ( !zeroFlag )
	      ++dpPos ;
	    else
	      numPart += src[ptr] ;
	    ++ptr ;
	  }
	  else
	    return false ; // invalide number
	  //cout << "src = " << src << endl ;
	  //cout << "here, [ptr] = " << src[ptr] << "\tstate = " << state << endl ;
	}
	state = 2 ;
	break ;
      }
      
    case 2: // process E part
      {
	if ( ptr >= len )
	{
#ifdef debug1
	  cout << "dpPos = " << dpPos << endl ;
#endif
	  E -= dpPos ;
	  state = 3 ;
	  break ;
	}
	if ( src[ptr] != 'E' && src[ptr] != 'e' )
	  return false ;
	++ptr ;
	
	int exp = 1 ;
	int temp = len-1 ;
	while ( temp > ptr )
	{
	  if ( !isdigit(src[temp]) )
	  {
	    E = 0 ;
	    return false ;
	  }
	  E += cToD(src[temp])*exp ;
	  exp *= 10 ;
	  --temp ;
	}
	if ( src[temp] == '-' )
	  E = (-E) ;	
	else if ( isdigit(src[temp]) )
	{
	  E += cToD(src[temp])*exp ;
	}
	else if ( src[temp] != '+' )
	  return false ;
#ifdef debug1
	cout << "State 2,\tdpPos = " << dpPos << ",\tE = " << E << endl ;
#endif
	E -= dpPos ;
	state = 3 ;
	break ;
      }

    case 3:
      return true ;
    }    
  }
  return true ;
}
