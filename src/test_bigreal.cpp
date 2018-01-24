#include "bignumber.h"

using billjeff::BigReal ;
using billjeff::BigInt ;

#define debug3
#define file_io1

int main( void )
{
#ifdef file_io
  freopen( "test_data_sqrt_bigint.txt", "r", stdin ) ;
  //freopen( "test_data_sqrt_bigint.txt_out.txt", "w", stdout ) ;
#endif

#ifdef debug1
  cout << "Test for output function and default ctor" << endl ;
  BigReal a ;
  cout << a << endl ;
#endif

#ifdef debug2
  cout << "Test for construct function and BigReal(double n)" << endl ;
  BigReal a(0.001) ;
  cout << "0.001: " << a << endl ;
  BigReal b(100000) ;
  cout << "100000: " << b << endl ;
  BigReal c(100.001E50) ;
  cout << "100.001E50: " << c << endl ;
  BigReal d(-0.0000001) ;
  cout << d << endl ;
  BigReal e(+0.00000) ;
  cout << e << endl ;
  BigReal f(1000e1000) ;
  cout << f << endl ;
  BigReal g(+12345.123213213e100) ;
  cout << g << endl ;
  BigReal h(-.123E-3) ;
  cout << h << endl ;
  BigReal i(+.123E-4) ;
  cout << i << endl ;
  BigReal j(-0.0000E199) ;
  cout << j << endl ;
  /**********************************************************************************
   * Test cases: +0.000, -0.000, +0.000E10000, -0E50000, 1.01E1000, +1.01, -1.01e1000
   * -1e3, 1e4, -1e-1, -1.00e-3
   * TODO - Test 143.1e-2
   *********************************************************************************/
  string st ;
  while ( cin >> st )
    cout << BigReal(st) << endl ;
  //BigReal h(+0.000.123123) ;
  //cout << h << endl ;
#endif

#ifdef debug3

 START:
  goto T21 ;

 T1:
  puts( "Test ctor BigReal( const char * )" ) ;
  char buf[1024] ;
  while ( scanf( "%s", buf ) == 1 )
  {
    cout << BigReal(buf) << endl ;
  }
  goto END ;

 T2:
  {
    puts( "Test copy ctor" ) ;
    string s ;  
    //BigReal a("123e10") ;
    while ( cin >> s )
    {
      BigReal b(s) ;
      BigReal c(b) ;
      cout << b << "\n" << c << endl ;
    }
  }
  goto END ;

 T3:
  {
    puts( "Test ctor for BigReal(BigInt)" ) ;
    /*************************************
     * Test cases: 1234, 0000, +000, -000,
     * -1, +1, -99999999999999999999, i
     ************************************/
    BigInt t(1234) ;
    while ( cin >> t )
      cout << BigReal(t) << endl ;
  }

 T4:
  {
    puts( "Test for BigInt's ctor for BigReal" ) ;
    /*********************************************
     * Test cases: 0.001, 1e10, -1e10, 3.2132131, 
     * +00.000, -0.000, .321321e1, hello
     ********************************************/
    BigReal t ;
    while ( cin >> t )
      cout << BigInt(t) << endl ;
  }

 T5:
  {
    puts( "Test for swap function" ) ;
    BigInt a, b ;
    while ( cin >> a >> b )
    {
      billjeff::swap(a, b) ;
      cout << a << " " << b << endl ;
      if ( a == b )
	break ;
    }

    BigReal c, d ;
    while ( cin >> c >> d )
    {
      swap(c, d) ;
      cout << c << " " << d << endl ;
      //if ( c == d )
      //break ;
    }
  }
  goto END ;

 T6:
  {
    puts( "Test for comparing functions" ) ;
    // Test: ==, !=, >, >=, <, <=
    BigReal a, b ;
    while ( cin >> a >> b )
    {
      cout << "a==b: " << (a == b) << endl ;
      cout << "a!=b: " << (a != b) << endl ;
      cout << "a>b: " << (a > b) << endl ;
      cout << "a>=b: " << (a >= b) << endl ;
      cout << "a<b: " << (a < b) << endl ;
      cout << "a<=b: " << (a <= b) << endl ;

    }
  }
  goto END ;

 T7:
  {
    BigReal a ;
    a = 0 ;
    cout << (a==0) << endl ;
  } 
  goto END ;

 T8:
  {
    /****************************************
     * Test for add() function.
     * Test cases: 
     * P vs. P: 1, 1; 1, 0.1; 1, 0.001; 1e-3, 1; 1e-3, 1e-4.
     * P vs. N: 1, -1; 1, -0.1, 1, -0.001, 1e-3, -1; 1e-3, -1e-4.
     * N vs. P: -1, 1; -1, 0.1, -1, 0.001, -1e-3, 1; -1e-3, 1e-4.
     * N vs. N: -1, -1; -1, -0.1; -1, -0.001; -1e-3, -1; -1e-3, -1e-4.
     * Complicated Input:
     ****************************************/ 
    BigReal a, b ;
    while ( cin >> a >> b )
    {
      //cout << a+b << endl ;
      //cout << a-b << endl ;
      try
      {
	cout << a/b << endl ;
      }
      catch( const billjeff::DivideZero &exp )
      {
	cout << exp.what() ;
      }
      cout << "---" << endl ;
    }
  }
  goto END ;

 T9:
  {
    cout << "Test BigInt Divide Function" << endl ;
    BigInt A, B ;
    while ( cin >> A >> B )
    {
      try
      {
	cout << "A = " << A << "\nB = " << B << endl ;
	cout << "A/B = " << A/B << endl ;    
      }
      catch (const billjeff::DivideZero& exp)
      {
	cout << exp.what() << endl ;
      }      
    }
  }
  goto END ;

 T10:
  {
    cout << "Test BigReal Divide Function" << endl ;
    BigReal A, B ;
    while ( cin >> A >> B )
    {
      try
      {
	A.setPrecision(10) ;
	cout << "A = " << A << "\nB = " << B << endl ;
	cout << "A/B = " << A/B << endl ;
      }
      catch( const billjeff::DivideZero &exp )
      {
	cout << exp.what() << endl ;
      }
    }
  }
  goto END ;

 T11:
  {
    cout << "Test operator[+-/*]( const BigInt&, const BigReal& )" << endl ;
    BigInt ia ;
    BigReal rb ;
    while ( cin >> ia >> rb )
    {
      cout << "A = " << ia << ", B = " << rb << endl ;
      cout << "A+B = " << ia+rb << endl ;
      cout << "A-B = " << ia-rb << endl ;
      cout << "A*B = " << ia*rb << endl ;
      //cout << "here" << endl ; // debug
      try{
	cout << "A/B = " << ia/rb << endl ;
      }
      catch( const billjeff::DivideZero& exp )
      {
	cout << exp.what() ;
      }
    }
  }
  goto END ;

 T12:
  {
    cout << "Test sqrt(BigInt)" << endl ;
    BigInt ia ;
    
    while ( cin >> ia )
    {
      cout << ia << endl ;
      //cout << billjeff::sqrt(ia) << endl ;
      cout << billjeff::sqrt(ia, 10) << endl ;
    }
  }
  goto END ;

 T13:
  {
    BigReal a, b ;
    while ( cin >> a >> b )
    {
      cout << (a > b) << endl ;
    }

  }
  goto END ;

 T14:
  {
    cout << "Test sqrt(BigReal)" << endl ;
    BigReal ra ;
    
    while ( cin >> ra )
    {
      cout << ra << endl ;
      //cout << billjeff::sqrt(ra) << endl ;
      cout << billjeff::sqrt(ra, 3) << endl ;
    }
  }
  goto END ;

 T15:
  {
    cout << "Test abs function" << endl ;
    // Test cases: -1, -0.1, -0, 0, -0.1e10
    //             1, 1.1 1e-10, 1e-1, 0.1e-1
    BigInt ia ;
    BigReal ra ;

    int n = 10 ;
    while ( n-- )
    {
      cin >> ia ;
      cout << billjeff::abs(ia) << endl ;
    }

    n = 10 ;
    while ( n-- )
    {
      cin >> ra ;
      cout << billjeff::abs(ra) << endl ;
    }

  }
  goto END ;

 T16:
  {
    cout << "Test for operator% for BigInt" << endl ;
    BigInt a, b ;
    while ( cin >> a >> b )
    {
      try
      {
	cout << a%b << endl ;
      }
      catch( ... )
      {

      }
    }
    goto END ;
  }

 T17:
  {
    cout << "Test for isPrime" << endl ;
    BigInt a ;
    while ( cin >> a )
    {
      bool b = billjeff::isPrime(a) ;
      if ( b )
	cout << a << " is Prime" << endl ;
      else
	cout << a << "is Not Prime" << endl ;
    }
    goto END ;
  }

  /*
 T18:
  {
    cout << "Test BigInt bool operator" << endl ;
    BigInt a ;
    while ( cin >> a )
    {
      if ( a )
	cout << "True" << endl ;
      else
	cout << "False" << endl ;
    }
    goto END ;
  }
  */
 T18:
  {
    cout << "Test comparison operator for BigInt and BigReal" << endl ;
    BigInt ia(1), ib("111111111111111111111111111") ;
    BigReal ra("1e-10"), rb("1e100") ;
    cout << "BigInt op BigInt" << endl ;
    cout << (ia > ib) << endl ;
    cout << (ia < ib) << endl ;
    cout << (ia <= ib) << endl ;
    cout << (ia >= ib) << endl ;
    cout << (ia == ib) << endl ;
    cout << (ia != ib) << endl ;
    cout << "BigInt op int" << endl ;
    cout << (ia < 1) << endl ;
    cout << (ia > 1) << endl ;
    cout << (ia <= 1) << endl ;
    cout << (ia >= 1) << endl ;
    cout << (ia != 1) << endl ;
    cout << (ia == 1) << endl ;
    cout << "int op BigInt" << endl ;
    cout << (1 > ib) << endl ;
    cout << (1 < ib) << endl ;
    cout << (1 <= ib) << endl ;
    cout << (1 >= ib) << endl ;
    cout << (1 == ib) << endl ;
    cout << (1 != ib) << endl ;
    cout << "BigReal op BigReal" << endl ;
    cout << (ra <= rb) << endl ;
    cout << (ra >= rb) << endl ;
    cout << (ra != rb) << endl ;
    cout << (ra == rb) << endl ;
    cout << (ra > rb) << endl ;
    cout << (ra < rb) << endl ;
    cout << "BigReal op BigInt" << endl ; 
    cout << (ra <= ib) << endl ;
    cout << (ra >= ib) << endl ;
    cout << (ra != ib) << endl ;
    cout << (ra == ib) << endl ;
    cout << (ra > ib) << endl ;
    cout << (ra < ib) << endl ;
    cout << "BigInt op BigReal" << endl ;
    cout << (ia <= rb) << endl ;
    cout << (ia >= rb) << endl ;
    cout << (ia != rb) << endl ;
    cout << (ia == rb) << endl ;
    cout << (ia > rb) << endl ;
    cout << (ia < rb) << endl ;
    cout << "int op BigReal" << endl ;
    //cout << "int op BigInt" << endl ;
    cout << (1 > rb) << endl ;
    cout << (1 < rb) << endl ;
    cout << (1 <= rb) << endl ;
    cout << (1 >= rb) << endl ;
    cout << (1 == rb) << endl ;
    cout << (1 != rb) << endl ;
    cout << "float op BigReal" << endl ;
    //cout << "int op BigInt" << endl ;
    cout << (1.0 > rb) << endl ;
    cout << (1.0 < rb) << endl ;
    cout << (1.0 <= rb) << endl ;
    cout << (1.0 >= rb) << endl ;
    cout << (1.0 == rb) << endl ;
    cout << (1.0 != rb) << endl ;
  }
  goto END ;

 T19:
  {
    cout << "Test for fib() func" << endl ;
    // Test cases: 0, 1, 2, 100, 3, 4, -1.
    int p ;
    while ( cin >> p )
    {
      BigInt tmp(p) ;
      cout << billjeff::fib(p) << endl ;
      cout << billjeff::fib(tmp) << endl ;
      cout << "------------------" << endl ;
    }
    goto END ;
  }

 T20:
  {
    cout << "Test for gcd" << endl ;
    using billjeff::gcd ;
    try{
      cout << "gcd(1, 2) = " << gcd(1, 2) << endl ;
      cout << "gcd(10, 2) = " << gcd(10, 2) << endl ;
      //cout << "gcd(10, 0) = " << gcd(10, 0) << endl ;
      cout << "gcd(BigInt(10000), 100) = " << gcd(BigInt(10000), 100) << endl ;
      cout << "gcd(BigInt(10000), -3) = " << gcd(BigInt(10000), -3) << endl ;
      cout << "gcd(BigInt(10000), BigInt(100)) = " << gcd(BigInt(10000), BigInt(100)) << endl ;
      cout << "gcd(BigInt(100), BigInt(1000)) = " << gcd(BigInt(100), BigInt(1000)) << endl ;
      cout << "gcd(BigInt(10000), BigInt(0)) = " << gcd(BigInt(10000), BigInt(0)) << endl ;
    }
    catch(const billjeff::DivideZero& e )
    {
      cout << e.what() << endl ;
    }

    goto END ;
  }

 T21:
  {
    cout << "Test for lcm" << endl ;
    using billjeff::lcm ;
    try{
      cout << "lcm(1, 2) = " << lcm(1, 2) << endl ;
      cout << "lcm(10, 2) = " << lcm(10, 2) << endl ;
      //cout << "lcm(10, 0) = " << lcm(10, 0) << endl ;
      cout << "lcm(BigInt(10000), 100) = " << lcm(BigInt(10000), 100) << endl ;
      cout << "lcm(BigInt(10000), -3) = " << lcm(BigInt(10000), -3) << endl ;
      cout << "lcm(BigInt(10000), BigInt(100)) = " << lcm(BigInt(10000), BigInt(100)) << endl ;
      cout << "lcm(BigInt(100), BigInt(1000)) = " << lcm(BigInt(100), BigInt(1000)) << endl ;
      cout << "lcm(BigInt(10000), BigInt(0)) = " << lcm(BigInt(10000), BigInt(0)) << endl ;
    }
    catch(const billjeff::DivideZero& e )
    {
      cout << e.what() << endl ;
    }

    goto END ;
  }


 END:
  puts("End of Test") ;
#endif



#ifdef debug

#endif


  return 0 ;
}
