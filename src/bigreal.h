#ifndef _BIGREAL_H_
#define _BIGREAL_H_

#include "utility.h"
#include "bigint.h"
#include <string>
#include <iostream>

using namespace std ;

namespace billjeff
{
  // Fordward Declaration
  class BigInt ;

  // BigReal class declaration
  class BigReal
  {
    friend ostream & operator << ( ostream &os, const BigReal &o ) ;
    friend void swap( BigReal &s1, BigReal &s2 ) ;
  private:
    // num_ stores every digit of bigreal
    char *num_ ; 
    // length of bigreal
    int len_ ;
    // sign for bigreal, s_ is true when bigreal is positive
    bool s_ ;
    // used for memory management	  
    int mem_ ;
    /* used for decimal point
     * if dp_ > 0, then put decimal point after dp_ digits which are from num_;
     * if dp_ <= 0, then put dp_ zeroes before num_ ;
     * if dp_ = NODP, there are no decimal point.
     */
    int dp_ ;
    // used for divide result precision control.
    // e.g. pre_ = 3, then there will be at most 3 digits after decimal points.
    int pre_ ;

  protected:
    void construct( const string &s ) ;
    // add another positive bigreal    
    BigReal& padd( const BigReal &val ) ;
    // minus operator, assume operands are positive and the result is 
    // large or equal to zero.
    BigReal& pminus( const BigReal &val ) ;
    // ignore the sign, multiply operation
    BigReal& pmultiply( const BigReal &val ) ;
    // ignore the sign, divide operation
    BigReal& pdivide( const BigReal &val ) ;    
    // ignore sign, get the string representation of content
    string toPString() const ;
    // copy num_[] from val to current object
    void contentCopy( const BigReal &val ) ;
    // expand memory for num_
    bool expand() ;
    // construct new this, val suitable for add and minus operation
    int convertAB( const BigReal &val, BigInt &ia, BigInt &ib ) ;
    // adjust the result of convertAB()
    void resultAdjust( BigInt &a, int newDP ) ;
  public:
    // default ctr
    BigReal() ;
    // double as parameter ctr 
    explicit BigReal( double n ) ;
    // int as parameter for ctr
    explicit BigReal( int n ) ;
    // string as parameter ctr 
    explicit BigReal( const string &s ) ;
    // C-string ctr
    explicit BigReal( const char * s ) ;
    // copy ctr 
    BigReal( const BigReal &v ) ;
    // ctor for BigInt
    explicit BigReal( const BigInt &v ) ;
    // dtr
    ~BigReal() ;
    // add operator
    BigReal& add( const BigReal &val ) ;    
    // minus operator
    BigReal& minus( const BigReal &val ) ;
    // multiply operator
    BigReal& multiply( const BigReal &val ) ;
    // divide operator
    BigReal& divide( const BigReal &val ) ;
    // assignment operator
    BigReal& operator = ( const BigReal &val ) ;
    template <class T>
      BigReal operator=( const T &a )
      {
	BigReal tmp(a) ;
	*this = tmp ;
	return *this ;
      }

    BigReal& operator += ( const BigReal &val ) ;
    template <class T>
      BigReal operator+=( const T &a )
      {
	BigReal tmp(a) ;
	*this += tmp ;
	return *this ;
      }


    BigReal& operator -= ( const BigReal &val ) ;
    template <class T>
      BigReal operator-=( const T &a )
      {
	BigReal tmp(a) ;
	*this -= tmp ;
	return *this ;
      }


    BigReal& operator *= ( const BigReal &val ) ;
    template <class T>
      BigReal operator*=( const T &a )
      {
	BigReal tmp(a) ;
	*this *= tmp ;
	return *this ;
      }


    BigReal& operator /= ( const BigReal &val ) ;
    template <class T>
      BigReal operator/=( const T &a )
      {
	BigReal tmp(a) ;
	*this /= tmp ;
	return *this ;
      }


    // compare operator
    bool operator == ( const BigReal &val ) const ;
    bool operator != ( const BigReal &val ) const ;
    bool operator > ( const BigReal &val ) const ;
    bool operator < ( const BigReal &val ) const ;
    bool operator >= ( const BigReal &val ) const ;
    bool operator <= ( const BigReal &val ) const ;
    // increasement and decreasement operator
    BigReal& operator ++ () ;
    BigReal operator ++ (int) ;
    BigReal& operator -- () ;
    BigReal operator -- (int) ;
    // change sign
    BigReal operator - () ;
    // ignore the sign, just compare two numbers absolute value ;
    // >0 for greator, 0 for equal, <0 for smaller
    int pcomp( const BigReal &val ) const ;

    // sign operator
    void changeSign() 
    {
      if ( len_ == 1 && num_[0] == '0' )
	return ;
      s_ ^= 1 ;
    }

    // set new dp_ value
    void setDP( int newdp )
    {
      dp_ = newdp ;
    }

    // set precision for divide result
    void setPrecision( int pre )
    {
      if ( pre < 0 )
      {
	cerr << "Precision must set to be non-negative value!" ;
	return ;
      }
      pre_ = pre ;
    }
    
    // get number at position p
    int getNumP( int p ) const
    {
      if ( p >= 0 && p < len_ )
        return cToD(num_[p]) ;
      //else
      //cerr << "Invalid index: " << p << " to get the char at P!" << endl ;
      return 0 ;
    }

    // get precision value
    int getPrecision() const
    {
      return pre_ ;
    }

    /************************
     * Get character at 
     * position p
     ***********************/
    char getCharP( int p ) const 
    {
      //cout << "Flag: " << *this << endl ;
      if ( p >= 0 && p < len_ )
	return num_[p] ;
      //else
      //cerr << "Invalid index: " << p << " to get the char at P!" << endl ;
      return '0' ;
    }

    /************************
     * Get the num_
     ***********************/
    const char * getNumPtr() const
    {
      return num_ ;
    }

    // get length of number
    int getLen() const
    {
      return len_ ;
    }

    /************************
     * Get the value of dp_
     ***********************/
    int getDP() const 
    {
      return dp_ ;
    }

    /************************
     * Get the mem_
     ***********************/
    int getMemVal() const
    {
      return mem_ ;
    }

    // get number sign
    bool getSign() const 
    {
      return s_ ;
    }
    // get string representation
    string toString() const ;

  } ;

  // overloaded operator << ;
  ostream & operator << ( ostream &os, const BigReal &o ) ;
  // overloaded operator >> ;
  istream & operator >> ( istream &is, BigReal &in ) ;
  // add operation for BigReal ;
  BigReal operator + ( const BigReal &op1, const BigReal &op2 ) ;
  // minus operation for BigReal ;
  BigReal operator - ( const BigReal &op1, const BigReal &op2 ) ;
  // multiply operation ;
  BigReal operator * ( const BigReal &op1, const BigReal &op2 ) ;
  // divide operation ;
  BigReal operator / ( const BigReal &op1, const BigReal &op2 ) ;
  // mode operation ;
  // BigReal operator % ( const BigReal &op1, const BigReal &op2 ) ;
}

#endif
