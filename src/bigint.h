#ifndef _BIGINT_H_
#define _BIGINT_H_

#include "utility.h"
#include "bigreal.h"
#include <string>
#include <iostream>

using namespace std ;

namespace billjeff{
  // Forward Declaration
  class BigReal ;

  // BigInt class declaration
  class BigInt
  {
    friend ostream & operator << ( ostream & os, const BigInt &o ) ;
    friend void swap( BigInt &s1, BigInt &s2 ) ;
  private:
    // num_ stores every digit of bigint
    char *num_ ; 
    // length of bigint
    int len_ ;
    // sign for bigint, s_ is true when bigint is positive
    bool s_ ;
    // used for memory management
    int mem_ ;
    // used for divide precision control, the same as in BigReal
    // default value of pre_ is set to 0
    //int pre_ ;

  protected:
    void construct( const string & ) ;
    // add another positive bigint
    // TODO - pay attention to positive and negative numbers operation.
    BigInt& padd( const BigInt &val ) ;
    // minus operator, assume operands are positive and the result is 
    // large or equal to zero.
    BigInt& pminus( const BigInt &val ) ;
    // ignore the sign, multiply operation
    BigInt& pmultiply( const BigInt &val ) ;
    // ignore the sign, divide operation
    BigInt& pdivide( const BigInt &val ) ;    
    // ignore sign, get the string representation of content
    string toPString() const ;
    // copy num_[] from val to current object
    void contentCopy( const BigInt &val ) ;
    // expand memory for num_
    bool expand() ;
  public:
    // default ctr
    BigInt() ;
    // int as parameter ctr 
    explicit BigInt( int n ) ;
    // string as parameter ctr 
    explicit BigInt( const string &s ) ;
    // C-string ctr
    explicit BigInt( const char * s ) ;
    // copy ctr 
    BigInt( const BigInt &v ) ;
    // ctor for BigReal ;
    explicit BigInt ( const BigReal &v ) ;
    // dtr
    ~BigInt() ;
    // add operator
    BigInt& add( const BigInt &val ) ;    
    // minus operator
    BigInt& minus( const BigInt &val ) ;
    // multiply operator
    BigInt& multiply( const BigInt &val ) ;
    // divide operator
    BigInt& divide( const BigInt &val ) ;
    // assignment operator
    BigInt& operator = ( const BigInt &val ) ;    
    template <class T>
      BigInt operator=( const T &b )
      {
	BigInt tmp(b) ;
	*this = tmp ;
	return *this ;
      }
    
    BigInt& operator += ( const BigInt &val ) ;
    template <class T>
      BigInt operator+=( const T &b )
      {
	BigInt tmp(b) ;
	*this += tmp ;
	return *this ;
      }
    

    BigInt& operator -= ( const BigInt &val ) ;
    template <class T>
      BigInt operator-=( const T &b )
      {
	BigInt tmp(b) ;
	*this -= tmp ;
	return *this ;
      }
    

    BigInt& operator *= ( const BigInt &val ) ;
    template <class T>
      BigInt operator*=( const T &b )
      {
	BigInt tmp(b) ;
	*this *= tmp ;
	return *this ;
      }
    

    BigInt& operator /= ( const BigInt &val ) ;
    template <class T>
      BigInt operator/=( const T &b )
      {
	BigInt tmp(b) ;
	*this /= tmp ;
	return *this ;
      }
    

    // compare operator
    bool operator == ( const BigInt &val ) const ;
    bool operator != ( const BigInt &val ) const ;
    bool operator > ( const BigInt &val ) const ;
    bool operator < ( const BigInt &val ) const ;
    bool operator >= ( const BigInt &val ) const ;
    bool operator <= ( const BigInt &val ) const ;
    // increasement and decreasement operator
    BigInt& operator ++ () ;
    BigInt operator ++ (int) ;
    BigInt& operator -- () ;
    BigInt operator -- (int) ;
    // change sign
    BigInt operator - () ;
    // ignore the sign, just compare two numbers absolute value ;
    // >0 for greator, 0 for equal, <0 for smaller
    int pcomp( const BigInt &val ) const ;

    // sign operator
    void changeSign() 
    {
      if ( len_ == 1 && num_[0] == '0' )
	return ;
      s_ ^= 1 ;
    }

    // bool operator
    /*
    operator bool()
    {
      if ( *this == 0 )
	return false ;
      return true ;
    }
    */

    // set precision for divide result
    /*
    void setPrecision( int pre )
    {
      if ( pre < 0 )
      {
	cerr << "Precision value must be non-negative!" << endl ;
	return ;
      }
      pre_ = pre ;
    }
    */
    // add( const

    // get number at position p
    // When the p is not the correct index, it will return 0. 
    int getNumP( int p ) const
    {
      // debug
      // cout << "Flag: " << *this << endl ;

      if ( p >= 0 && p < len_ )
        return cToD(num_[p]) ;
      //else
      //cerr << "Invalid index: " << p << " to get the char at P!" << endl ;
      return 0 ;
    }

    // get character at position p
    char getCharP( int p ) const 
    {
      //cout << "Flag2 : " << *this << endl ;
      if ( p >= 0 && p < len_ )
	return num_[p] ;
      //else
      //cerr << "Invalid index: " << p << " to get the char at P!" << endl ;
      return '0' ;
    }

    // get length of number
    int getLen() const
    {
      return len_ ;
    }

    // get precision
    /*
    int getPrecision() const
    {
      return pre_ ;
    }
    */
    // get number sign
    bool getSign() const 
    {
      return s_ ;
    }
    // get string representation
    string toString() const ;

  } ;

  // overloaded operator << ;
  ostream & operator << ( ostream &os, const BigInt &o ) ;
  // overloaded operator >> ;
  istream & operator >> ( istream &is, BigInt &in ) ;
  // add operation for BigInt ;
  BigInt operator + ( const BigInt &op1, const BigInt &op2 ) ;
  // minus operation for BigInt ;
  BigInt operator - ( const BigInt &op1, const BigInt &op2 ) ;
  // multiply operation ;
  BigInt operator * ( const BigInt &op1, const BigInt &op2 ) ;
  // divide operation ;
  BigInt operator / ( const BigInt &op1, const BigInt &op2 ) ;
  // mode operation ;
  BigInt operator % ( const BigInt &op1, const BigInt &op2 ) ;
}

#endif 

