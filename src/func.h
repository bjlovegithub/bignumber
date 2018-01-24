// math related function definitions
// billjeff 
// Feb/9/2008


#ifndef _FUNC_H_
#define _FUNC_H_

#include "bigint.h"
#include "bigreal.h"
#include <algorithm>


namespace billjeff {
  BigInt power( const BigInt &p, const BigInt &e ) ;
  BigInt factorial( const BigInt &p ) ;
  BigInt sqr( const BigInt &p ) ;
  BigReal sqr( const BigReal &p ) ;
  
  template <class T>
  inline T billjeff::abs( const T &p ) 
  {
    T tmp(p) ;
    if ( tmp < 0 )
    {
      tmp.changeSign() ;
      return tmp ;
    }
    return tmp ;
  }

    
  BigReal sqrt( const BigInt&, int precision = 10 ) ;
  BigReal sqrt( const BigReal&, int precision = 10 ) ;

  bool isPrime( BigInt ) ;

  // TODO
  BigReal log() ; // Maybe I will add several functions to support other base log operation.
  BigReal getPI( BigInt precision ) ;  
  BigInt nextPrime() ;

  BigInt fib( const BigInt & ) ; 
  BigInt fib( int ) ;
  //BigInt abs() ;
  
  // swap function for BigInt and BigReal;
  void swap( BigInt &v1, BigInt &v2 ) ;
  void swap( BigReal &v1, BigReal &v2 ) ;
   
  // BigInt vs. BigReal operations
  BigReal operator* ( const BigInt&, const BigReal& ) ;
  BigReal operator* ( const BigReal&, const BigInt& ) ;
  BigReal operator/ ( const BigInt&, const BigReal& ) ;
  BigReal operator/ ( const BigReal&, const BigInt& ) ;
  BigReal operator+ ( const BigInt&, const BigReal& ) ;
  BigReal operator+ ( const BigReal&, const BigInt& ) ;
  BigReal operator- ( const BigInt&, const BigReal& ) ;
  BigReal operator- ( const BigReal&, const BigInt& ) ;
  bool operator< ( const BigInt&, const BigReal& ) ;
  bool operator< ( const BigReal&, const BigInt& ) ;
  bool operator> ( const BigInt&, const BigReal& ) ;
  bool operator> ( const BigReal&, const BigInt& ) ;
  bool operator<= ( const BigInt&, const BigReal& ) ;
  bool operator<= ( const BigReal&, const BigInt& ) ;
  bool operator>= ( const BigInt&, const BigReal& ) ;
  bool operator>= ( const BigReal&, const BigInt& ) ;
  bool operator== ( const BigInt&, const BigReal& ) ;
  bool operator== ( const BigReal&, const BigInt& ) ;
  bool operator!= ( const BigInt&, const BigReal& ) ;
  bool operator!= ( const BigReal&, const BigInt& ) ;

  /****************************************************
   * Template overloaded operator for T op BigNumber, 
   * T includes int, short, float, char*, etc,
   * BigNumber includes BigInt and BigReal.
   * op includes: >, >=, <, <=, ==, !=.
   ***************************************************/
  template <class T>
    bool operator<( const T &a, const BigInt &b )
  {
    BigInt tmp(a) ;
    return tmp < b ;
  }

  template <class T>
    bool operator<( const T &a, const BigReal &b )
  {
    BigReal tmp(a) ;
    return tmp < b ;
  }

  template <class T>
    bool operator<=( const T &a, const BigInt &b )
  {
    BigInt tmp(a) ;
    return tmp <= b ;
  }

  template <class T>
    bool operator<=( const T &a, const BigReal &b )
  {
    BigReal tmp(a) ;
    return tmp <= b ;
  }

  template <class T>
    bool operator>( const T &a, const BigInt &b )
  {
    BigInt tmp(a) ;
    return tmp > b ;
  }

  template <class T>
    bool operator>( const T &a, const BigReal &b )
  {
    BigReal tmp(a) ;
    return tmp > b ;
  }

  template <class T>
    bool operator>=( const T &a, const BigInt &b )
  {
    BigInt tmp(a) ;
    return tmp >= b ;
  }

  template <class T>
    bool operator>=( const T &a, const BigReal &b )
  {
    BigReal tmp(a) ;
    return tmp >= b ;
  }

  template <class T>
    bool operator==( const T &a, const BigInt &b )
  {
    BigInt tmp(a) ;
    return tmp == b ;
  }

  template <class T>
    bool operator==( const T &a, const BigReal &b )
  {
    BigReal tmp(a) ;
    return tmp == b ;
  }

  template <class T>
    bool operator!=( const T &a, const BigInt &b )
  {
    BigInt tmp(a) ;
    return tmp != b ;
  }

  template <class T>
    bool operator!=( const T &a, const BigReal &b )
  {
    BigReal tmp(a) ;
    return tmp != b ;
  }

  /****************************************************
   * Template overloaded operator for BigNumber op T, 
   * T includes int, short, float, char*, etc,
   * BigNumber includes BigInt and BigReal.
   * op includes: >, >=, <, <=, ==, !=.
   ***************************************************/
  template <class T>
    bool operator>( const BigInt &a, const T &b )
  {
    BigInt tmp(b) ;
    return a > tmp ;
  }

  template <class T>
    bool operator>( const BigReal &a, const T &b )
  {
    BigReal tmp(b) ;
    return a > tmp ;
  }

  template <class T>
    bool operator>=( const BigInt &a, const T &b )
  {
    BigInt tmp(b) ;
    return a >= tmp ;
  }

  template <class T>
    bool operator>=( const BigReal &a, const T &b )
  {
    BigReal tmp(b) ;
    return a >= tmp ;
  }

  template <class T>
    bool operator<( const BigInt &a, const T &b )
  {
    BigInt tmp(b) ;
    return a < tmp ;
  }

  template <class T>
    bool operator<( const BigReal &a, const T &b )
  {
    BigReal tmp(b) ;
    return a < tmp ;
  }

  template <class T>
    bool operator<=( const BigInt &a, const T &b )
  {
    BigInt tmp(b) ;
    return a <= tmp ;
  }

  template <class T>
    bool operator<=( const BigReal &a, const T &b )
  {
    BigReal tmp(b) ;
    return a <= tmp ;
  }

  template <class T>
    bool operator==( const BigInt &a, const T &b )
  {
    BigInt tmp(b) ;
    return a == tmp ;
  }

  template <class T>
    bool operator==( const BigReal &a, const T &b )
  {
    BigReal tmp(b) ;
    return a == tmp ;
  }

  template <class T>
    bool operator!=( const BigInt &a, const T &b )
  {
    BigInt tmp(b) ;
    return a != tmp ;
  }

  template <class T>
    bool operator!=( const BigReal &a, const T &b )
  {
    BigReal tmp(b) ;
    return a != tmp ;
  }

  /****************************************************
   * Template overloaded operator for T op BigNumber, 
   * T includes int, short, float, char*, etc,
   * BigNumber includes BigInt and BigReal.
   * op includes: +, -, *, /, =.
   ***************************************************/
  template <class T>
    BigInt operator+( const T &a, const BigInt &b )
  {
    BigInt tmp(a) ;
    return tmp + b ;
  }

  template <class T>
    BigReal operator+( const T &a, const BigReal &b )
  {
    BigReal tmp(a) ;
    return tmp + b ;
  }

  template <class T>
    BigInt operator-( const T &a, const BigInt &b )
  {
    BigInt tmp(a) ;
    return tmp - b ;
  }

  template <class T>
    BigReal operator-( const T &a, const BigReal &b )
  {
    BigReal tmp(a) ;
    return tmp - b ;
  }

  template <class T>
    BigInt operator*( const T &a, const BigInt &b )
  {
    BigInt tmp(a) ;
    return tmp * b ;
  }

  template <class T>
    BigReal operator*( const T &a, const BigReal &b )
  {
    BigReal tmp(a) ;
    return tmp * b ;
  }

  template <class T>
    BigInt operator/( const T &a, const BigInt &b )
  {
    BigInt tmp(a) ;
    return tmp / b ;
  }

  template <class T>
    BigReal operator/( const T &a, const BigReal &b )
  {
    BigReal tmp(a) ;
    return tmp / b ;
  }

  /*
  template <class T>
    BigInt operator=( const T &a, const BigInt &b )
  {
    BigInt tmp(a) ;
    return tmp = b ;
  }

  template <class T>
    BigReal operator=( const T &a, const BigReal &b )
  {
    BigReal tmp(a) ;
    return tmp = b ;
  }
  */

  /****************************************************
   * Template overloaded operator for BigNumber op T, 
   * T includes int, short, float, char*, etc,
   * BigNumber includes BigInt and BigReal.
   * op includes: +, -, *, /, =.
   ***************************************************/
  template <class T>
    BigInt operator+( const BigInt &a, const T &b )
  {
    BigInt tmp(b) ;
    return a + tmp ;
  }

  template <class T>
    BigReal operator+( const BigReal &a, const T &b )
  {
    BigReal tmp(b) ;
    return a + tmp ;
  }

  template <class T>
    BigInt operator-( const BigInt &a, const T &b )
  {
    BigInt tmp(b) ;
    return a - tmp ;
  }

  template <class T>
    BigReal operator-( const BigReal &a, const T &b )
  {
    BigReal tmp(b) ;
    return a - tmp ;
  }
 
  template <class T>
    BigInt operator*( const BigInt &a, const T &b )
  {
    BigInt tmp(b) ;
    return a * tmp ;
  }

  template <class T>
    BigReal operator*( const BigReal &a, const T &b )
  {
    BigReal tmp(b) ;
    return a * tmp ;
  }

  template <class T>
    BigInt operator/( const BigInt &a, const T &b )
  {
    BigInt tmp(b) ;
    return a / tmp ;
  }

  template <class T>
    BigReal operator/( const BigReal &a, const T &b )
  {
    BigReal tmp(b) ;
    return a / tmp ;
  }

  /****************************************
   * Overloaded operator % to support
   * BigInt % T. where T is
   * int, string, char*, short etc.
   * If T is invalid for BigInt's ctor,
   * error message will be displayed.
   ***************************************/
  template <class T>
    BigInt operator% ( const BigInt &a, const T &b )
  {
    // Construct tmp BigInt from b, if b is invalid, error message
    // will be displayed.
    BigInt tmp(b) ;

    return a%tmp ;
  }
  
  /****************************************
   * Overloaded operator % to support
   * T % BigInt. where T is
   * int, string, char*, short etc.
   * If T is invalid for BigInt's ctor,
   * error message will be displayed.
   ***************************************/
  template <class T>
    BigInt operator% ( const T &a, const BigInt &b )
  {
    // Construct tmp BigInt from a, if a is invalid, error message
    // will be displayed.
    BigInt tmp(a) ;

    return b%tmp ;
  }

  /*********************************************
   * Get the greatest common divisor of a and b
   * Where T and V can be: int, short, char, 
   * BigInt.
   * Note the Divide_Zero exception
   ********************************************/
  template <class T, class V>
    BigInt gcd( const T &a, const V &b ) 
  {
    string type_bigint, type_bigreal, type_real, type_float ;
    type_bigint = typeid(const BigInt&).name() ;
    type_bigreal = typeid(const BigReal&).name() ;
    type_real = typeid(const double&).name() ;
    type_float = typeid(const float&).name() ;

    string type_a, type_b ;
    type_a = typeid(a).name() ;
    type_b = typeid(b).name() ;

#ifdef debug1
    cout << type_bigint << " " << type_a << endl ;
    cout << type_bigreal << " " << type_b << endl ;
#endif

    if ( type_a == type_bigreal || type_b == type_bigreal ||
	 type_a == type_real || type_b == type_real ||
	 type_a == type_float || type_b == type_float )
    {
      cerr << "Parameter a and b for GCD  must be BigInt or int type!" << endl ;
      return BigInt(0) ;
    }

    BigInt tmp_a(a), tmp_b(b) ;
    /*
    if ( type_a != type_bigint )
      tmp_a = a ;
    if ( type_b != type_bigint )
      tmp_b = b ;
    */
    if ( tmp_a < tmp_b )
      swap(tmp_a, tmp_b) ;

    BigInt tmp ;

    while ( true )
    {      
      //cout << tmp_a << " " << tmp_b << endl ; // debug
      tmp = tmp_a%tmp_b ;
      if ( tmp == 0 )
	break ;
      tmp_a = tmp_b ;
      //tmp_a = tmp_b ;
      tmp_b = tmp ; 
    }

    return tmp_b ;

  }


  /*********************************************
   * Get the least common mutiple of a and b
   * Where T and V can be: int, short, char, 
   * BigInt.
   * Note the Divide_Zero exception
   ********************************************/
  template <class T, class V>
    BigInt lcm( const T &a, const V &b ) 
  {

    if ( a == 0 || b == 0 )
      return BigInt(0) ;

    string type_bigint, type_bigreal, type_real, type_float ;
    type_bigint = typeid(const BigInt&).name() ;
    type_bigreal = typeid(const BigReal&).name() ;
    type_real = typeid(const double&).name() ;
    type_float = typeid(const float&).name() ;

    string type_a, type_b ;
    type_a = typeid(a).name() ;
    type_b = typeid(b).name() ;

#ifdef debug1
    cout << type_bigint << " " << type_a << endl ;
    cout << type_bigreal << " " << type_b << endl ;
#endif

    if ( type_a == type_bigreal || type_b == type_bigreal ||
	 type_a == type_real || type_b == type_real ||
	 type_a == type_float || type_b == type_float )
    {
      cerr << "Parameter a and b for LCM  must be BigInt or int type!" << endl ;
      return BigInt(0) ;
    }

    return (a*b)/gcd(a,b) ;

  }  

}

#endif 
