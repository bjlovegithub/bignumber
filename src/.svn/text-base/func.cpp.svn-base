#include "func.h"

#define debug

using billjeff::BigInt ;
using billjeff::BigReal ;

BigInt billjeff::power( const BigInt &p, const BigInt &e ) {
  //cout << "e = " << e << endl ;
  if ( e < 0 ){
    // TODO - handle exponent is less than zero
    return BigInt(0) ;
  }
  if ( e == 0 )
    return BigInt(1) ;
  BigInt tp = p ;
  for( BigInt i(1) ; i < e ; ++i ){
#ifdef debug1
    cout << "e = " << i << ", val = " ;
    cout << tp << endl ;
#endif
    tp *= p ;
  }
  return tp ;
}

BigInt billjeff::factorial( const BigInt &p ) {
  if ( p < 0 )
    return BigInt(0) ;
  if ( p == 0 )
    return BigInt(1) ;
  BigInt re(1) ;
  for ( BigInt it(2) ; it <= p ; ++it )
    re *= it ;
  return re ; 
}

BigInt billjeff::sqr( const BigInt &p )
{
  return p*p ;
}

BigReal billjeff::sqr( const BigReal &p )
{
  return p*p ;
}


/**********************************************
 * Get the square root of parameter p(BigInt)
 * Parameter precision are used to set the 
 * precision of result, default value is 10
 * Note: Big numbers need to set precision to
 *       be big enough to get precious result.
 *********************************************/
BigReal billjeff::sqrt( const BigInt &p, int precision )
{
  if ( p < 0 )
  {
    cerr << "Input cannot be less than zero!" << endl ;
    return BigReal(0) ;
  }

  if ( precision < 0 )
  {
    cerr << "Parameter precision for sqrt cannot be less than zero!" << endl ;
    return BigReal(0) ;
  }

  BigReal rp(p) ;

  // Use binary search method to find the answer.

  BigReal E ;
  {
    string tmp = "0." ;
    for ( int i = 1 ; i < precision ; ++i )
      tmp += '0' ;
    tmp += '1' ;
    E = tmp ;
  }

#ifdef debug1
  cout << "E = " << E << endl ;
#endif 

  BigReal s(0), e(rp), mid, sqr_mid ;
  precision += 1 ;
  s.setPrecision(precision) ;
  e.setPrecision(precision) ;
  mid.setPrecision(precision) ;
  sqr_mid.setPrecision(precision) ;

  mid = (s+e)/BigReal(2) ;
  sqr_mid = sqr(mid) ;  

  // tmpMid is used to exit infinite loop.
  BigReal tmpMid = mid ;
  while ( abs(sqr_mid-rp) >= E )
  {    
    //cout << sqr_mid << " A " << rp << endl ; // debug
    //cout << (sqr_mid > rp) << endl ; // debug
    if ( sqr_mid > rp )
      e = mid ;
    else
      s = mid ;
    mid = (s+e)/BigReal(2) ;
    if ( tmpMid == mid )
    {
      cerr << "Please set precision to be larger to get the precious result!" << endl ;
      break ;
    }
    else
      tmpMid = mid ;
#ifdef debug1
    cout << "S = " << s << ", E = " << e << endl ;
    cout << mid << endl ;
    cout << abs(sqr_mid-rp) << endl ;
#endif
    sqr_mid = sqr(mid) ;
  }

  return mid ;
}


/**********************************************
 * Get the square root of parameter p(BigReal)
 * Parameter precision are used to set the 
 * precision of result, default value is 10
 * Note: Big numbers need to set precision to
 *       be big enough to get precious result.
 *********************************************/
BigReal billjeff::sqrt( const BigReal &p, int precision )
{
  if ( p < 0 )
  {
    cerr << "Input cannot be less than zero!" << endl ;
    return BigReal(0) ;
  }

  if ( precision < 0 )
  {
    cerr << "Parameter precision for sqrt cannot be less than zero!" << endl ;
    return BigReal(0) ;
  }

  // Use binary search method to find the answer.

  BigReal E ;
  {
    string tmp = "0." ;
    for ( int i = 1 ; i < precision ; ++i )
      tmp += '0' ;
    tmp += '1' ;
    E = tmp ;
  }

#ifdef debug1
  cout << "E = " << E << endl ;
#endif 

  BigReal s, e, mid, sqr_mid ;
  if ( p < 1 )
  {
    s = p ;
    e = 1 ;
  }
  else
  {
    s = 1 ;
    e = p ;
  }
  precision += 1 ;
  s.setPrecision(precision) ;
  e.setPrecision(precision) ;
  mid.setPrecision(precision) ;
  sqr_mid.setPrecision(precision) ;

  mid = (s+e)/BigReal(2) ;
  sqr_mid = sqr(mid) ;  
  
  // tmpMid is used to exit infinite loop.
  BigReal tmpMid = mid ;
  while ( abs(sqr_mid-p) >= E )
  {    
    //cout << sqr_mid << " A " << rp << endl ; // debug
    //cout << (sqr_mid > rp) << endl ; // debug
    if ( sqr_mid > p )
      e = mid ;
    else
      s = mid ;
    mid = (s+e)/BigReal(2) ;
    if ( tmpMid == mid )
    {
      cerr << "Please set precision to be larger to get the precious result!" << endl ;
      break ;
    }
    else
      tmpMid = mid ;
#ifdef debug1
    cout << "S = " << s << ", E = " << e << endl ;
    cout << mid << endl ;
    cout << abs(sqr_mid-p) << endl ;
#endif
    sqr_mid = sqr(mid) ;
  }

  return mid ;

}


/****************************************
 * Function: If p is prime, return true,
 *           else, return false.
 ***************************************/
bool billjeff::isPrime( BigInt p ) 
{

  if ( p == 1 )
    return false ; 

  p = abs(p) ;

  // Generate all primes within 1000.
  bool Prime[1000] ;
  {
    memset( Prime, 1, 1000 ) ;
    //Prime[2] = true ;
    Prime[0] = Prime[1] = false ;
    int ptr = 2 ;
    while ( ptr < 501 )
    {
      // Remove non-Prime numbers
      int tp = ptr*2 ;
      while ( tp < 1000 )
      {
	Prime[tp] = false ;
	tp += ptr ;
      }
      // for the first prime after p including p.
      for ( ++ptr; p < 501 ; ++ptr )
	if ( Prime[ptr] )
	  break ;      
    }

#ifdef debug
    class OP
    {
    public:
      void operator() ( bool b ) ;
    } ;
    //for_each( Prime, Prime+sizeof(bool)*1000, 
    for ( int i = 0 ; i < 1000 ; ++i )
      if ( Prime[i] )
	cout << i << " " ;
    cout << endl ;
#endif
  }

  // Pre-test to exclude non-Prime number.
  for ( int i = 0 ; i < 1000 ; ++i )
  {
    if ( p <= i )
      break ;
    if ( Prime[i] )
    {
      if ( p % i == 0 )
	return false ;
    }
  }

  if ( p < 1000 )
    return true ;

  // Prime Test.
  {
    BigInt end(sqrt(p)), pos(1001) ;
    for ( ; pos <= end ; ++pos )
    {
      if ( p % pos == 0 )
	return false ;
    }
  }

  return true ;
}

// TODO - Add TODO function's code here.

/**********************************************
 * Get pth fibonacci number, where p starts
 * at 0. f(0) = 0, f(1) = 1, f(n)=f(n-1)+f(n-2)
 *********************************************/
BigInt billjeff::fib( const BigInt & p )
{
  if ( p < 0 )
  {
    cerr << "There is no " << p << "th fibonacci number! Please use non-zero para"
         << "meter!" << endl ;
    return BigInt(0) ;
  }

  if ( p == 0 )
    return BigInt(0) ;
  else if ( p == 1 )
    return BigInt(1) ;

  BigInt fn, fn_1(1), fn_2(0) ;
  for ( BigInt i(2) ; i <= p ; ++i )
  {    
    //cout << "i = " << i << endl ; // debug
    fn = fn_1+fn_2 ;
    fn_2 = fn_1 ;
    fn_1 = fn ;
  }

  return fn ;
}


/**********************************************
 * Fib() for the parameter is int.
 *********************************************/
BigInt billjeff::fib( int p )
{
  return billjeff::fib(BigInt(p)) ;
}


/**********************************************
 * Swap function for BigInt and BigReal
 * Swap the content of two big numbers
 *********************************************/
void billjeff::swap( BigInt &s1, BigInt &s2 )
{
  std::swap( s1.num_, s2.num_ ) ;
  std::swap( s1.s_, s2.s_ ) ;
  std::swap( s1.mem_, s2.mem_ ) ;
  std::swap( s1.len_, s2.len_ ) ;
}

void billjeff::swap( BigReal &s1, BigReal &s2 ) 
{
  std::swap( s1.num_, s2.num_ ) ;
  std::swap( s1.s_, s2.s_ ) ;
  std::swap( s1.mem_, s2.mem_ ) ;
  std::swap( s1.len_, s2.len_ ) ;
  std::swap( s1.dp_, s2.dp_ ) ;
  std::swap( s1.pre_, s2.pre_ ) ;
}

/******************************************************
 * These bunch of functions are overloaded functions.
 * The reuslts are BigReal, while you can convert these
 * results to BigInt if you want.
 *****************************************************/
BigReal billjeff::operator* ( const BigInt& ia, const BigReal& rb )
{
  BigReal tmp(ia) ;
  return tmp*rb ;
}

BigReal billjeff::operator* ( const BigReal& rb, const BigInt& ia )
{
  return ia*rb ;
}

BigReal billjeff::operator/ ( const BigInt& ia, const BigReal& rb ) 
{
  BigReal tmp(ia) ;
  //cout << "tmp = " << tmp << endl ;
  return tmp/rb ;
}

BigReal billjeff::operator/ ( const BigReal& rb, const BigInt& ia ) 
{
  return ia/rb ;
}

BigReal billjeff::operator+ ( const BigInt& ia, const BigReal& rb )
{
  BigReal tmp(ia) ;
  return tmp+rb ;
}

BigReal billjeff::operator+ ( const BigReal& rb, const BigInt& ia )
{
  return ia+rb ;
}

BigReal billjeff::operator- ( const BigInt& ia, const BigReal& rb ) 
{
  BigReal tmp(ia) ;
  return tmp-rb ;
}


BigReal billjeff::operator- ( const BigReal& rb, const BigInt& ia )
{
  return ia-rb ;
}

/******************************************
 * Overloaded operators are used to support
 * BigInt op BigReal compararison.
 * NOTE: Maybe I can use boost::operator.
 *****************************************/
bool billjeff::operator< ( const BigInt& ia, const BigReal& rb ) 
{
  BigReal tmp(ia) ;
  return tmp < rb ;
}

bool billjeff::operator< ( const BigReal& ra, const BigInt& ib ) 
{
  BigReal tmp(ib) ;
  return ra < tmp ;
}

bool billjeff::operator> ( const BigInt& ia, const BigReal& rb )
{
  BigReal tmp(ia) ;
  return tmp > rb ;
}

bool billjeff::operator> ( const BigReal& rb, const BigInt& ia ) 
{
  BigReal tmp(ia) ;
  return rb > tmp ;
}

bool billjeff::operator<= ( const BigInt& ia, const BigReal& rb ) 
{
  BigReal tmp(ia) ;
  return tmp <= rb ;
}

bool billjeff::operator<= ( const BigReal& rb, const BigInt& ia ) 
{
  BigReal tmp(ia) ;
  return tmp <= rb ;
}

bool billjeff::operator>= ( const BigInt& ia, const BigReal& rb ) 
{
  BigReal tmp(ia) ;
  return tmp >= rb ;
}

bool billjeff::operator>= ( const BigReal& rb, const BigInt& ia ) 
{
  BigReal tmp(ia) ;
  return tmp >= rb ;
}

bool billjeff::operator== ( const BigInt& ia, const BigReal& rb ) 
{
  BigReal tmp(ia) ;
  return tmp == rb ;
}

bool billjeff::operator== ( const BigReal& rb, const BigInt& ia ) 
{
  BigReal tmp(ia) ;
  return tmp == rb ;
}

bool billjeff::operator!= ( const BigInt& ia, const BigReal& rb ) 
{
  BigReal tmp(ia) ;
  return tmp != rb ;
}

bool billjeff::operator!= ( const BigReal& rb, const BigInt& ia ) 
{
  BigReal tmp(ia) ;
  return tmp != rb ;
}

