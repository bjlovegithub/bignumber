#include "bignumber.h"
#include <string>

using billjeff::BigInt ;

#define debug7

int main( void ){
#ifdef debug1
  BigInt a ;
  cout << a << endl ;
  BigInt b(123) ;
  cout << b << endl ;
  BigInt d( -123 ) ;
  cout << d << endl ;
  string s = "123" ;
  BigInt c(s) ;
  cout << c << endl ;
  s = "-123" ;
  BigInt e(s) ;
  cout << e << endl ;
  BigInt f("345") ;
  cout << f << endl ;
  BigInt g("-345") ;
  cout << g << endl ;
#endif

#ifdef debug1
  cout << "Test for Add operation for BigInt" << endl ;
  cout << a << endl ;
  cout << a+b << endl ;
  cout << a << " " << b << endl ;
  cout << b+d << endl ;
  cout << s+g << endl ;
  cout << s+f << endl ;
  BigInt temp = f+g+e+e ;
  cout << temp << endl ;
#endif

#ifdef debug2
  cout << "Test for minus operation" << endl ;
  cout << a-b << endl ;
  BigInt temp = a-b-c+c+e-f ;
  cout << temp << endl ;
  temp = 2-1 ;
  temp = temp+10001 ;
  temp = temp + "111111111111111111111111132133333333333333333333333321321312" ;
  temp = temp + "999999999999999999999999999999999999999999999" ;
  temp = "0"-temp ;
  temp = temp-temp ;
  temp += temp ;
  temp += "123" ;  
  //temp -= temp ;
  temp.changeSign() ;
  cout << (a == "0") << endl ;
  cout << temp << endl ;
#endif

  // 
#ifdef debug3
  cout << "Test for multiply operation" << endl ;
  BigInt a, b, c, d ;
  a = "123" ;
  b = "-123" ;
  c = "0" ;
  d = "-2" ;
  cout << "a = " << a << endl ;
  cout << "here" << endl ;
  cout << a*b << endl ;
  cout << c*a << endl ;
  cout << b*d << endl ;
  cout << ++a << " " << a << endl ;
  cout << a++ << " " << a << endl ;
  cout << --a << " " << a << endl ;
  cout << a-- << " " << a << endl ;
  cout << "Test for divide operation" << endl ;
  cout << a/b << endl ;
  cout << a/d << endl ;
  cout << c/a << endl ;
  cout << a/c << endl ;
  cout << 1/a << endl ;
  cout << a/3 << endl ;
  //cout << a.toString() << endl ;
#endif

  // TODO - Debug
#ifdef debug4
  cout << "Test for power and fractorial function" << endl ;
  BigInt a ;
  a = "-1234" ;
  //cout << power(a, 0) << endl ;
  
  cout << "a = " << a << endl ;
  /*
  a = "+001234000" ;
  cout << "a = " << a << endl ;
  a = " +00000000000" ;
  cout << "a = " << a << endl ;
  a = "-000000000000" ;
  cout << "a = " << a << endl ;
  */
  //BigInt b = "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999" ;
  /*BigInt c ="8" ;
  cout << c << endl ;
  cout << c+"1" << endl ;
  */
  //cout << billjeff::power(a, b) << endl ;
  cout << a*(-1) << endl ;
  cout << "a = " << a << endl ;
  cout << a/(-40) << endl ;
  cout << a/(-100) << endl ;
  cout << a/12000 << endl ;
  
#endif

#ifdef debug5
  cout << "Test for factorial & operaotr >> & operator % " << endl ;
  BigInt a = 0 ;
  cout << a << endl ;
  a = "0" ;
  cout << a << endl ;
  while ( cin >> a ){
    cout << billjeff::power(a, 3) << endl ;
    cout << billjeff::factorial(a) << endl ;
    cout << a%3 << endl ;
  }
#endif


#ifdef debug6
  cout << "Test for minus operation" << endl ;
  BigInt a, b ;
  while ( cin >> a >> b )
  {
    cout << "========" << endl ;
    cout << a-b << endl ;
    cout << b-a << endl ;
    cout << (-a) << endl ;
    cout << a*b << endl ;
    cout << "========" << endl ;
  }
#endif

#ifdef debug7
  cout << "Test for square operation" << endl ;
  BigInt a ;
  while ( cin >> a )
  {
    cout << sqr(a) << endl ;
  }
#endif

  /*************************************************
   * Several Test Cases for BigInt is in 
   * test_bigreal.cpp file
   ************************************************/

#ifdef debug
  cout << "Test for multiply operation" << endl ;

#endif

#ifdef debug
  cout << "Test for multiply operation" << endl ;

#endif

#ifdef debug
  cout << "Test for multiply operation" << endl ;

#endif


  return 0 ;
}
