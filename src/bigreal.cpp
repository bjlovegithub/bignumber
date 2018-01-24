#include "bigreal.h"
#include "func.h"
#include <sstream>

using namespace std ;
using billjeff::BigReal ;
using billjeff::BigInt ;

#define debug

BigReal::BigReal() : mem_(1), pre_(10) 
{
  try
  {
    num_ = new char[INITIAL] ;
  }
  catch(...)
  {
    cerr << "Memory Allocation Error!" << endl ;
    exit(1) ;
  }
  len_ = 1 ;
  num_[0] = '0' ;
  dp_ = 0 ;
  s_ = true ;
}


BigReal::BigReal( double n ) : mem_(1), pre_(10)
{
  ostringstream oss ;
  oss << n ;
  construct(oss.str()) ;
}


/**********************************
 * Int parameter for ctr
 *********************************/
BigReal::BigReal( int n ) : mem_(1), pre_(10)
{
  ostringstream oss ;
  oss << n ;
  construct(oss.str()) ;
}


BigReal::BigReal( const string& n ) : mem_(1), pre_(10)
{
  construct(n) ;
}

BigReal::BigReal( const char * n ) : mem_(1), pre_(10)
{
  string sn = n ;
  construct(sn) ;
}


/****************************************
 * Copy ctors
 ***************************************/
BigReal::BigReal( const BigReal &v )
{
  const char *ptr = v.getNumPtr() ;
  len_ = v.getLen() ;
  mem_ = 1 ;
  pre_ = v.getPrecision() ;
  // allocate memory
  while ( mem_*INITIAL <= len_ )
    mem_ <<= 1 ;
  try
  {
    num_ = new char[mem_*INITIAL] ;
  }
  catch(...)
  {
    cerr << "Memory Allocation Error!" << endl ;
    exit(1) ;
  }

  // copy the content
  for ( int i = 0 ; i < len_ ; ++i )
    num_[i] = ptr[i] ;

  // sign and dp
  s_ = v.getSign() ;
  dp_ = v.getDP() ;
}

/********************************
 * Ctor for BigInt
 *******************************/
BigReal::BigReal( const BigInt &v ) : mem_(1)
{
  len_ = v.getLen() ;
  s_ = v.getSign() ;
  pre_ = 10 ; // default

  while ( mem_*INITIAL <= len_ )
    mem_ <<= 1 ;
  try
  {
    num_ = new char[mem_*INITIAL] ;
  }
  catch(...)
  {
    cerr << "Memory Allocation Error!" << endl ;
    exit(1) ;
  }

  dp_ = NODP ;
  for ( int i = 0 ; i < len_ ; ++i )
    num_[i] = v.getCharP(i) ;

  return ;  
}


 
BigReal::~BigReal()
{
  delete[] num_ ;
}

void BigReal::construct( const string &s )
{
  int E ;
  string numPart ;
  bool sign ;

  if ( analyzeDouble( numPart, E, sign, s ) ) // input s is valid double
  {

#ifdef debug1
    cout << numPart << ", " << E << endl ;
#endif

    if ( numPart == "0" || numPart == "" )
    {
      try
      {
	num_ = new char[mem_*INITIAL] ;
      }
      catch(...)
      {
	cerr << "Memory Allocation Error!" << endl ;
	exit(1) ;
      }
      // Initialize BigReal as 0
      num_[0] = '0' ;
      len_ = 1 ;
      s_ = true ;
      dp_ = NODP ;
      return ;
    }

    s_ = sign ;
    // get the memory space needed to store this double number
    int dpPos = -1 ;
    int len = numPart.length() ;
    // get the position of decimal point in numPart.
    for ( int i = 0 ; i < len ; ++i )
      if ( numPart[i] == '.' )
      {
	dpPos = i ;
	break ;
      }
    // erase "."
    if ( dpPos != -1 )
    {
      for ( int i = dpPos ; i < len-1 ; ++i )
	numPart[i] = numPart[i+1] ;
      --len ;
    }
    else
      dpPos = len ;
    //dpPos = dpPos == -1 ? 0 : dpPos ;
    if ( E > len-dpPos )
    {
      len_ = E+2*dpPos-len ;
      dp_ = NODP ;
    }
    else if ( E == len-dpPos )
    {
      len_ = len ;
      dp_ = NODP ;
    }
    else
    {
      len_ = len ; 
      dp_ = dpPos + E ;
      /*
      if ( dpPos > 0 )
	--dp_ ;
      */
    }

#ifdef debug1
    printf( "len_ = %d,\tdp_ = %d,\tlen = %d\n", len_, dp_, len ) ;
#endif

    // Memory allocation
    while ( mem_*INITIAL <= len_ )
      mem_ <<= 1 ;
    try
    {
      num_ = new char[mem_*INITIAL] ;
    }
    catch(...)
    {
      cerr << "Memroy Allocation Error!" << endl ;
      exit(1) ;
    }

    /* copy content from numPart
     * construct num_ array from high position to low position
     */
    int ptr = 0 ;
    for ( int i = len_-1 ; i >= 0 ; --i )
    {
      if ( ptr < len )
      {
	//if ( numPart[ptr] != '.' )
	num_[i] = numPart[ptr] ;
	//else 
	//++i ;
	++ptr ;
	//num_[i] = numPart[ptr--] ;
      }
      else
	num_[i] = '0' ;
    }
  }
  else // invalid
  {
    cerr << "Invalid Input Double Number!" << endl ;
    try
    {
      num_ = new char[mem_*INITIAL] ;
    }
    catch(...)
    {
      cerr << "Memory Allocation Error!" << endl ;
      exit(1) ;
    }
    // Initialize BigReal as 0
    num_[0] = '0' ;
    len_ = 1 ;
    s_ = true ;
    dp_ = NODP ;
  }
}

/************************************************
 * Assitant function for add and minus.
 * It convert this, val to new this, val suitable
 * for add and minus.
 * e.g. *this = 1.001, val = 0.009, then 
 * new *this = 1001, new val = 9.
 * return value is newDP(see codes comment)
 ************************************************/
int BigReal::convertAB( const BigReal &val, BigInt &ia, BigInt &ib ) 
{
  string sa, sb ;
  sa = sb = "" ;
  int vDP = val.getDP(), vLen = val.getLen() ;
  // Decimal point position from tail.
  // e.g. 12.4, newDP = 1 ;
  // When newDP is NODP, it represents no decimal point
  int newDP ; 
  // Both of them do not have float point part
  if ( vDP == NODP && dp_ == NODP )
  {
    for ( int i = len_-1 ; i >= 0 ; --i )
      sa += num_[i] ;
    for ( int i = vLen-1 ; i >= 0 ; --i )
      sb += val.getCharP(i) ;
    newDP = NODP ;
  }
  // val does not have float point part
  // It will add several zeroes to val
  if ( vDP == NODP && dp_ != NODP )
  {
    for ( int i = vLen-1 ; i >= 0 ; --i )
      sb += val.getCharP(i) ;
    for ( int i = len_-1 ; i >= 0 ; --i )
      sa += num_[i] ;
    
    // TODO - Improve this code.
    int temp = 0 ;    
    if ( dp_ > 0 )
    {
      // case: val = 123, *this = 1.23
      // 123 => 12300, 1.23 => 123
      temp = (len_ - dp_) ;
    }
    else
    {
      // case: val = 123, *this = 0.0123
      // 123 => 1230000, 0.0123 => 123
      temp = (len_-dp_) ;
    }
    newDP = temp ;

    // add zero to sb ;
    while ( temp-- )
      sb += '0' ;       
  }

  if ( vDP != NODP && dp_ == NODP )
  {
    for ( int i = vLen-1 ; i >= 0 ; --i )
      sb += val.getCharP(i) ;
    for ( int i = len_-1 ; i >= 0 ; --i )
      sa += num_[i] ;

    // debug
    //cout << "Flag: " << sa << " " << sb << endl ;

    int temp = 0 ;    
    // TODO - Improve this codes
    if ( vDP > 0 )
    {
      // case: *this = 123, val = 1.23
      // 123 => 12300, 1.23 => 123
      temp = (vLen - vDP) ;
    }
    else
    {
      // case: *this = 123, val = 0.0123
      // 123 => 1230000, 0.0123 => 123
      temp = (vLen-vDP) ;
    }

    newDP = temp ;
    // add zero to sb ;
    while ( temp-- )
      sa += '0' ;    
  }
  // Both of them have float point part
  if ( vDP != NODP && dp_ != NODP )
  {
    for ( int i = vLen-1 ; i >= 0 ; --i )
      sb += val.getCharP(i) ;
    for ( int i = len_-1 ; i >= 0 ; --i )
      sa += num_[i] ;

    if ( dp_ > 0 && vDP > 0 )
    {
      // *this = 12.34, val = 12.3
      // 12.34 => 1234, 12.3 => 1230
      if ( len_-dp_ >= vLen-vDP )
      {
	int temp = (len_-dp_) - (vLen-vDP) ;
	for ( int i = 0 ; i < temp ; ++i )
	  sb += '0' ;
	
	newDP = (len_ - dp_) ;
      }
      else
      {
	// *this = 12.3, val = 12.34
	// 12.3 => 1230, 12.34 => 1234
	int temp = (vLen-vDP) - (len_-dp_) ;
	for ( int i = 0 ; i < temp ; ++i )
	  sa += '0' ;

	newDP = (vLen-vDP) ;
      }
    }
    else if ( dp_ > 0 && vDP <= 0 )
    {
      // *this = 12.3, val = 0.012
      // 12.3 => 12300, 0.012 => 12
      if ( (vLen-vDP) > (len_-dp_) )
      {
	int temp = (vLen-vDP) - (len_-dp_) ;
	for ( int i = 0 ; i < temp ; ++i )
	  sa += '0' ;

	newDP = vLen-vDP ;
      }
      else
      {
	// *this = 12.345, val = 0.01
	// 12.345 => 12345, 0.01 => 10
	int temp = (len_-dp_) - (vLen-vDP) ;
	for ( int i = 0 ; i < temp ; ++i )
	  sb += '0' ;

	newDP = (len_ - dp_) ;
      }
    }
    else if ( dp_ <= 0 && vDP > 0 )
    {
      // *this = 0.01, val = 1.234
      // 0.01 => 10, 1.234 => 1234	
      if ( (vLen-vDP) > (len_-dp_) )
      {
	int temp = (vLen-vDP) - (len_-dp_) ;
	for ( int i = 0 ; i < temp ; ++i )
	  sa += '0' ;

	newDP = (vLen-vDP) ;
      }
      else
      {
	// *this = 0.012, val = 1.23
	// 0.012 => 12, 1.23 => 1230
	int temp = (len_-dp_) - (vLen-vDP) ;
	for ( int i = 0 ; i < temp ; ++i )
	  sb += '0' ;

	newDP = (len_-dp_) ;
      }
    }
    else  // dp_ < 0 && vDP < 0       
    {

#ifdef debug1
      cout << "Flag1: sa = " << sa << ", sb = " << sb << endl ;
      cout << *this << " " << val << endl ;
      //debug
      cout << -dp_+len_ << " " << vLen-vDP << endl ;	
#endif
      /*
      for ( int i = vLen-1 ; i >= 0 ; --i )
	sb += val.getCharP(i) ;
      for ( int i = len_ ; i >= 0 ; --i )
	sa += num_[i] ;
      */
      // *this = 0.01, val = 0.0123
      // 0.01 => 100, 0.0123 => 123
      if ( (len_-dp_) < (vLen-vDP) )
      {
	int temp = (vLen-vDP) - (len_-dp_) ;
	for ( int i = 0 ; i < temp ; ++i )
	  sa += '0' ;

	newDP = vLen-vDP ;	
      } 
      else
      {
	// *this = 0.0123, val = 0.01
	// 0.0123 => 123, 0.01 => 100
	int temp = (len_-dp_) - (vLen-vDP) ;
	for ( int i = 0 ; i < temp ; ++i )
	  sb += '0' ;

	newDP = len_-dp_ ;
      }
    }
  }

  // Assign converted result to BigInt a and b.
#ifdef debug1
  cout << "sa = " << sa << ", sb = " << sb << endl ;
#endif

  ia = sa ;
  ib = sb ;

  return newDP ;

}


/******************************************
 * This is assitant function for add and
 * minus, multiply operation.
 * Its input "a" is the result of function
 * convertAB's third parameter, and newDP
 * is the resutn value of convertAB().
 * Adjusted result assign to *this
 *****************************************/
void BigReal::resultAdjust( BigInt &a, int newDP )
{
  // TODO - No string object is needed here. Just return a point of char*.
  string temp = a.toString() ;
  size_t it = temp.find('-') ;
  if ( it != string::npos )
    temp.erase(temp.begin()+it) ;
  // copy the result to *this.
  if ( newDP == NODP ) // No decimal point
  {
    dp_ = newDP ;
    len_ = temp.length() ;
    // expand memory if current num_ is not big enough
    while ( mem_*INITIAL <= len_ )
      mem_ << 1 ;
    delete[] num_ ;
    try 
    {
      num_ = new char[mem_*INITIAL] ;
    }
    catch( ... )
    {
      cerr << "Memory Allocation Error!" << endl ;
      exit(1) ;
    }
    
    for ( int i = 0 ; i < len_ ; ++i )
      num_[i] = temp[len_-1-i] ;
  }
  else // Decimal point may exist
  {
    // delete trailing zero
    // e.g. 12300, newDP = 1, and then it converts to 1230, newDP = 0.
    // 12300, newDP = 3, then it converts to 123, newDP = 1 .
    int len = temp.length()-1 ;
    while ( newDP > 0 )
    {
      if ( temp[len] != '0' )
	break ;
      --len ;
      --newDP ;
    }

    len_ = len+1 ;
    // expand memory if current num_ is not big enough.
    while ( mem_*INITIAL <= len_ )
      mem_ <<= 1 ;

    delete[] num_ ;
    try
    {
      num_ = new char[mem_*INITIAL] ;
    }
    catch( ... )
    {
      cerr << "Memory Allocation Error!" << endl ;
      exit(1) ;
    }
    
    // copy content
    int ptr = 0 ;
    for ( int i = len ; i >= 0 ; --i )
      num_[ptr++] = temp[i] ;

    // assign new dp_ value.
    // see the example above
    if ( newDP == 0 )
      dp_ = NODP ;
    else 
    {
      // e.g. 123, newDP = 1, then dp_ = 2
      if ( len_ - newDP > 0 )
	dp_ = (len_-newDP) ;
      else if ( len_ - newDP < 0 )
      {
	// e.g. 123, newDP = 4, the value is 0.0123
	dp_ = len_-newDP ;
      }
      else // e.g. 123, newDP = 3, the value is 0.123.
	dp_ = 0 ;
      // debug
      //cout << newDP << " " << dp_ << endl ;
    }
  }
}

/*******************************************
 * Add val to current BigReal where ignoring
 * their symbols.
 ******************************************/
BigReal& BigReal::padd( const BigReal &val )
{    
  
  BigInt a, b ;  
  int newDP = convertAB(val, a, b) ;
  a += b ;
  
  resultAdjust(a, newDP) ;  

  return *this ;
} 


/********************************************
 * *this minus val, where it is kept that 
 * pcomp(*this, val) is 1(*this is greator
 * than val ignoring sign.
 *******************************************/
BigReal& BigReal::pminus( const BigReal &val ) 
{
  BigInt a, b ;
  int newDP = convertAB(val, a, b) ;
  a -= b ;

  resultAdjust(a, newDP) ;

  return *this ;
}


/******************************************
 * Add val to this.
 * It checks whether this and val is
 * zero first.
 *****************************************/
BigReal& BigReal::add( const BigReal &val )
{
  // Any one is zero
  if ( val == 0 )
    return *this ;
  if ( *this == 0 )
  {
    *this = val ;
    return *this ;
  }

  // They are all non-zero
  bool vSign = val.getSign() ;
  if ( (s_ == true && vSign == true ) ||  // all positive
       (s_ == false && vSign == false ) ) // negative vs. negative
  {
    padd(val) ;
  }
  else if ( (s_ == true && vSign == false) || // positive vs. negative
	    (s_ == false && vSign == true ) ) // negative vs. positive
  {
    int comp = pcomp(val) ;
    if ( comp == 0 ) // equal
    {
      s_ = true ;
      dp_ = NODP ;
      len_ = 1 ;
      num_[0] = '0' ;
    }
    else if ( comp == 1 ) // *this is larger(ignore their sign)
    {
      //TODO - Implement pminus
      pminus(val) ;
    }
    else // *this is less than val(ignore their sign)
    {
      //TODO 
      // swap their content first
      BigReal temp = val ;
      billjeff::swap( *this, temp ) ;
      pminus(temp) ;
    }
  }
  /*
  else //negative vs. negative
  {
    s_ = false ;
    padd(val) ;
  }
  */

  return *this ;
}

/******************************************
 * Minus val to this.
 * First, It checks whether this and val is
 * zero.
 *****************************************/
BigReal& BigReal::minus( const BigReal &val )
{
  // Any one is zero
  if ( val == 0 )
    return *this ;
  if ( *this == 0 )
  {
    *this = val ;
    s_ = 1^(val.getSign()) ;
    return *this ;
  }

  // They are all non-zero
  bool vSign = val.getSign() ;

  if ( (s_ == true && vSign == false) ||   // positive - negative => positive + positive
       (s_ == false && vSign == true)    ) // negative - positive => negative + negative
  {
    padd(val) ;
  }
  else if ( (s_ == true && vSign == true) ||   // positive vs. positive 
	    (s_ == false && vSign == false) )  // negative vs. negative 
  {
    int comp = pcomp(val) ;
    if ( comp == 0 ) // equal
    {
      s_ = true ;
      dp_ = NODP ;
      len_ = 1 ;
      num_[0] = '0' ;
    }
    else if ( comp == 1 ) // *this is larger(ignore their sign)
    {
      //TODO - Implement pminus
      pminus(val) ;
    }
    else // *this is less than val(ignore their sign)
    {
      //TODO 
      // swap their content first
      BigReal temp = val ;
      billjeff::swap( *this, temp ) ;
      pminus(temp) ;
      s_ = (1^s_) ;
    }
  }
  /*
  else //negative vs. negative
  {
    s_ = false ;
    padd(val) ;
  }
  */

  return *this ;
}

/******************************************
 * Member function multiply
 * a.multiply(b) then a is (a*b)
 *****************************************/
BigReal& BigReal::multiply( const BigReal &val )
{  
  // zero , quick test and return.
  if ( *this == 0 )
    return *this ;
  if ( val == 0 )
  {
    *this = 0 ;
    return *this ;
  }

  // convert a(*this), b(val) to BigInt objects, and get newDP
  // newDP has the same meaning as it in convertAB()
  BigReal ta = *this, tb = val ;
  ta.setDP(NODP) ;
  tb.setDP(NODP) ;
  BigInt ia(ta), ib(tb) ;
#ifdef debug1
  cout << ia << " " << ib << endl ;
#endif

  // get the value of newDP. e.g. a = 1.23, b = 2.3, then newDP = 2+1 = 3
  int newDP = 0;
  int valDP = val.getDP(), valLen = val.getLen() ;
  if ( dp_ == NODP && valDP == NODP ) // e.g. a = 123, b = 3
    newDP = NODP ; // No decimal point
  //else if ( dp_ == NODP && valDP != NODP )
  else
  {
    if ( valDP != NODP )
    {
      // TODO - Maybe I should remove if statement here. But it is clear I put it here.
      if ( valDP > 0 ) // e.g. b = 12.3
	newDP = valLen-valDP ;
      else             // e.g. b = 0.12
	newDP = valLen-valDP ;
    }
    if ( dp_ != NODP )
    {
      // TODO
      if ( dp_ > 0 )
	newDP += len_-dp_ ;
      else if ( dp_ <= 0 )
	newDP += len_-dp_ ;
    }
  }    

  BigInt ic = ia*ib ;
#ifdef debug1
  cout << "a*b = " << ic << endl ;
  cout << "newDP = " << newDP << endl ;
#endif
  // Adjust sign for the result.
  if ( ic >= 0 )
    s_ = true ;
  else
    s_ = false ;
  
  if ( ic < 0 )
    ic = (-ic) ;
  resultAdjust(ic, newDP) ;

  
  return *this ;
}


/**********************************************
 * Member function divide
 * a.divide(b) then a is (a/b)
 * This function may throw DivideZero exception
 **********************************************/
BigReal& BigReal::divide( const BigReal &val )
{
  // Note: val cannot be zero. In overloaed function operator / and /=,
  // there will be an exception when val is zero.


  // Assume *this is ra, val is rb.
  // convert ra and rb to ia and ib. 
  // e.g. 1.23 => 123, 0.0123 => 123.
  int valLen = val.getLen(), valDP = val.getDP() ;

  // Fisrt, get the newDP for ra and rb. newDP has the same meaning
  // in multiply member function in BigReal.
  int newDPa, newDPb ;
  if ( dp_ == NODP )  // ra = 123
    newDPa = 0 ;
  else if ( dp_ > 0 ) // ra = 1.23
    newDPa = len_-dp_ ;
  else                // ra = 0.123
    newDPa = len_-dp_ ; // They have the same expression for dp_>0
                        // I write them out for clarity.

  if ( valDP == NODP )
    newDPb = 0 ;
  else
    newDPb = valLen-valDP ;

  BigInt A, B ;
  string ta = "", tb = "" ;

  for ( int i = len_-1 ; i >= 0 ; --i )
    ta += num_[i] ;
  for ( int i = valLen-1 ; i >= 0 ; --i )
    tb += val.getCharP(i) ;
  // Different condition. e.g. 1.23/0.001, 1.23/100 etc.
  if ( newDPa >= newDPb ) // e.g. 1.23/100 => 123/10000 or 123.23/100.1 => 12323/10010
  {   
    // Add zero to tb.
    int flag = newDPa-newDPb ;
    while ( flag-- )
      tb += '0' ;
  }
  else // e.g. 123/0.01 => 12300/1
  {
    int flag = newDPb-newDPa ;
    while ( flag-- )
      ta += '0' ;
  }
  
  //cout << "pre_ = " << pre_ << endl ; // debug
  // precision control.
  {
    int flag = pre_ ;
    while ( flag-- )
      ta += '0' ;
  }

  //cout << "here" << endl ; // debug

  A = ta ;
  B = tb ;

  //cout << "here2" << endl ; // debug

  if ( !s_ )
    A.changeSign() ;
  if ( !val.getSign() )
    B.changeSign() ;

  //cout << A << " " << B << endl ;

  BigInt C = A/B ;

#ifdef debug1
  cout << "A = " << A << "\nB = " << B << "\nC = " << C << "C len = " << C.getLen() << endl ;
#endif

  // Assign the result C to this.
  // *this = C ;

  // Get new dp_ value.
  /*
  if ( len_ - pre_ <= 0 ) // e.g. 0.12
    dp_ = len_-pre_ ;
  else                    // e.g. 1.2
    dp_ = len_-pre_ ;
  */

  //dp_ = C.getLen()-pre_ ;
  // TODO - Delete this codes.
  //cout << "dp = " << dp_ << endl ;

  // Set the symbol.
  if ( C >= 0 )
    s_ = true ;
  else
    s_ = false ;
  // Adjust final result.
  if ( C == 0 )
    resultAdjust( C, NODP ) ;
  else
    resultAdjust( C, pre_ ) ;

  return *this ;
}

/*************************************
 * Compare two BigReal number where
 * ignore their symbol.
 * Return Value: 1 for big, 0 for 
 * equal, -1 for small.
 ************************************/
int BigReal::pcomp( const BigReal &v ) const
{
  int vLen = v.getLen() ;
  int vDP = v.getDP() ;
#ifdef debug1
  cout << "a = " << *this << ", b = " << v << endl ;
  cout << len_ << " " << vLen << endl ;
#endif
  // Exclude the condition when *this or v is zero
  if ( dp_ == NODP && len_ == 1 && num_[0] == '0' )
  {
    // v is zero
    if ( vDP == NODP && vLen == 1 && v.getCharP(0) == '0' )
      return 0 ;
    return -1 ;
  }
  if ( vDP == NODP && vLen == 1 && v.getCharP(0) == '0' )  
    return 1 ;

  // e.g. *this = 2, v = 2.1
  if ( dp_ == NODP && vDP != NODP )
  {
    if ( len_ > vDP ) // *this = 23, v = 2.1
      return 1 ;
    if ( len_ < vDP ) // *this = 2, v = 32.1
      return -1 ;
    int i ;
    int p1 = len_-1 , p2 = vLen-1 ;
    for ( i = 0 ; i < len_ ; ++i )
    {
      char c1 = num_[p1-i], c2 = v.getCharP(p2-i) ;
      if ( c1 > c2 )
	return 1 ;
      else if ( c1 < c2 )
	return -1 ;
    }
    return -1 ; // *this = 2, v = 2.1
  }

  // e.g. *this = 2.1, v = 2
  if ( dp_ != NODP && vDP == NODP )
  {
    if ( dp_ > vLen ) // *this = 23.1, v = 2
      return 1 ;
    if ( dp_ < vLen ) // *this = 2.1, v = 32
      return -1 ;
    int i ;
    int p1 = len_-1 , p2 = vLen-1 ;
    for ( i = 0 ; i < len_ ; ++i )
    {
      char c1 = num_[p1-i], c2 = v.getCharP(p2-i) ;
      if ( c1 > c2 )
	return 1 ;
      else if ( c1 < c2 )
	return -1 ;
    }
    return 1 ; // *this = 2.1, v = 2
  }

  if ( dp_ > vDP )
    return 1 ;
  else if ( dp_ < vDP )
    return -1 ;
  else // dp is equal
  {
    if ( dp_ == NODP )
    {
      if ( len_ > vLen )
	return 1 ;
      else if ( len_ < vLen )
	return -1 ;
      else
      {
	bool f = true ;
	int p1 = len_-1, p2 = vLen-1 ;
	for ( int i = 0 ; i < len_ && f ; ++i )
	{
	  char c1 = num_[p1-i], c2 = v.getCharP(p2-i) ;
	  if ( c1 > c2 )
	  {
	    f = false ;
	    return 1 ;
	  }
	  else if ( c1 < c2 )
	  {
	    f = false ;
	    return -1 ;
	  }
	}
	if ( f ) // equal
	  return 0 ;
      }
    }
    else // condition like: 1.23, 2.321321.
    {
      int len = min( len_, vLen ) ;
      bool f = true ;
      int aPtr = len_-1, bPtr = vLen-1 ;
      for ( int i = 0 ; i < len ; ++i, --aPtr, --bPtr )
	if ( num_[aPtr] > v.getCharP(bPtr) )
	{
	  f = false ;
	  return 1 ;
	}
	else if ( num_[aPtr] < v.getCharP(bPtr) )
	{
	  f = false ;
	  return -1 ;
	}
      if ( f ) // from 0 to len-1, all digits are equal
      {
	// who have more digits win!
	if ( len_ > len )
	  return 1 ;
	if ( vLen > len )
	  return -1 ;
	// They are equal
	return 0 ;
      }
    }
  }
}


/*****************************************
 * Overlaoded operator += for bigreal
 ****************************************/
BigReal& BigReal::operator += ( const BigReal &val )
{
  add(val) ;
  return *this ;
}


/*****************************************
 * Overlaoded operator -= for bigreal
 ****************************************/
BigReal& BigReal::operator -= ( const BigReal &val )
{
  minus(val) ;
  return *this ;
}


/*****************************************
 * Overlaoded operator *= for bigreal
 ****************************************/
BigReal& BigReal::operator *= ( const BigReal &val )
{
  multiply(val) ;
  return *this ;
}


/*****************************************
 * Overlaoded operator /= for bigreal
 * Exception: DivideZero
 * Use default precision 10 for divide.
 ****************************************/
BigReal& BigReal::operator /= ( const BigReal &val )
{
  if ( val == BigReal(0) )
    throw DivideZero() ;
  divide(val) ;
  return *this ;
}


/*****************************************************
 * Overloaded operator> for comparing two BigReal
 * number.
 ****************************************************/
bool BigReal::operator > ( const BigReal &val ) const 
{
  bool valSign = val.getSign() ;

  // This number is positive and val is negative or 
  // vice verse.
  if ( s_ && !valSign )
    return true ;
  else if ( !s_ && valSign )
    return false ;
  else
  {
    //They have the same symbol
    int pComp = pcomp(val) ;
#ifdef debug1
    cout << "pComp = " << pComp << endl ;
#endif
    // Two positive number
    if ( s_ )
    {
      if ( pComp == 1 )
	return true ;
      return false ;
    }
    else
    {
      // Two negative number
      if ( pComp == -1 )
	return true ;
      return false ;
    }
  }
}


/*****************************************************
 * Overloaded operator< for comparing two BigReal
 * number.
 ****************************************************/
bool BigReal::operator< ( const BigReal &val ) const 
{
  if ( val > *this )
    return true ;
  return false ;
}


/*****************************************************
 * Overloaded operator>= for comparing two BigReal
 * number.
 ****************************************************/
bool BigReal::operator >= ( const BigReal &val ) const 
{
  return (!operator<(val)) ;
}


/*****************************************************
 * Overloaded operator<= for comparing two BigReal
 * number.
 ****************************************************/
bool BigReal::operator <= ( const BigReal &val ) const 
{
  return (!operator>(val)) ;
}


/*****************************************************
 * Overloaded operator== for comparing two BigReal
 * number.
 ****************************************************/
bool BigReal::operator == ( const BigReal &val ) const 
{
  if ( !operator>(val) && !val.operator>(*this) )
    return true ;
  return false ;
}


/*****************************************************
 * Overloaded operator!= for comparing two BigReal
 * number.
 ****************************************************/
bool BigReal::operator != ( const BigReal &val ) const 
{
  return !(operator==(val)) ;
}


/*************************************
 * Assignment Operator=
 ************************************/
BigReal & BigReal::operator= ( const BigReal &v )
{
  s_ = v.getSign() ;
  len_ = v.getLen() ;
  dp_ = v.getDP() ;

  int tm = v.getMemVal() ;
  if ( tm > mem_ )
  {
    delete[] num_ ;
    try
    {
      num_ = new char[tm*INITIAL] ;
    }
    catch(...)
    {
      cerr << "Memory Allocation Error!" << endl ;
      exit(1) ;
    }
  }
  mem_ = tm ;

  // get the content of v's num[]
  for ( int i = 0 ; i < len_ ; ++i )
    num_[i] = v.getCharP(i) ;

  return *this ;
}


/*****************************************
 * operator + for bigreal
 ****************************************/
BigReal billjeff::operator + ( const BigReal &op1, const BigReal &op2 ) 
{
  BigReal temp(op1) ;
  
  temp += op2 ;
  return temp ;
}


/*****************************************
 * operator - for bigreal
 ****************************************/
BigReal billjeff::operator - ( const BigReal &op1, const BigReal &op2 ) 
{
  BigReal temp(op1) ;
  
  temp -= op2 ;
  return temp ;
}

/******************************************
 * operator * for bigreal
 *****************************************/
BigReal billjeff::operator * ( const BigReal &op1, const BigReal &op2 )
{
  BigReal temp(op1) ;
  temp *= op2 ;
  return temp ;
}

/******************************************
 * operator / for bigreal
 * The precision of result is decided by
 * pre_ in class BigReal. e.g. if
 * pre_ = 3, and the precious result
 * is 1.2345, then 1.235 is returned.
 *****************************************/
BigReal billjeff::operator / ( const BigReal &op1, const BigReal &op2 )
{
  if ( op2 == BigReal(0) )
    throw DivideZero() ;

  BigReal temp(op1) ;
 
  temp.divide(op2) ;
  return temp ;
}

/*****************************************
 * Overloaded operator>> for BigReal
 ****************************************/
ostream & billjeff::operator << ( ostream &os, const BigReal &o )
{

#ifdef debug1
  cout << "len=" << o.len_ << "num[0]=" << o.num_[0] << endl ;
#endif

  if ( !(o.len_ == 1 && o.num_[0] == '0') && o.s_ == false )
    os << "-" ;
  if ( o.dp_ <= 0 ) // leading zero
  {
    int t_dp = (-o.dp_) ;
    os << "0." ;    
    for ( int i = 0 ; i < t_dp ; ++i )
      os << "0" ;
    for ( int i = o.len_-1 ; i >= 0 ; --i )
      os << o.num_[i] ;
  }
  else if ( o.dp_ > 0 )
  {
    int c = 1 ;
    for ( int i = o.len_-1 ; i >= 0 ; --i, ++c )
    {
      os << o.num_[i] ;
      if ( o.dp_ == c )
	os << "." ;
    }
  }
  else // NODP
  {
    for ( int i = o.len_-1 ; i >= 0 ; --i )
      os << o.num_[i] ;
  }
  return os ;
}


/*****************************************
 * Overloaded operator>> for BigReal
 ****************************************/
istream & billjeff::operator >> ( istream &is, BigReal &in )
{
  string s ;
  is >> s ;
  BigReal temp(s) ;
  in = temp ;
  return is ;
}
