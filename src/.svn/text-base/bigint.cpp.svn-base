#include "bigint.h"
#include "func.h"


using billjeff::BigInt ;

#define debug

BigInt::BigInt() : mem_(1) 
{
  try
  {
    num_ = new char[INITIAL] ;
  }
  catch( ... )
  {  
    cerr << "Memory Allocation Error!" << endl ;
    exit(1) ;
  }
  num_[0] = '0' ;
  len_ = 1 ;
  s_ = true ; // positive
}


BigInt::BigInt(int n) : mem_(1) 
{
  try
  {
    num_ = new char[INITIAL] ;
  }
  catch( ... )
  {
    cerr << "Memory Allocation Error!" << endl ;
    exit(1) ;
  }
  len_ = 0 ;
  if ( n == 0 )
  {
    len_ = 1 ;
    s_ = true ;
    num_[0] = '0' ;
    return ;
  }
  if ( n > 0 )
    s_ = true ;
  else
  {
    s_ = false ;
    n = -n ;
  }
  // convert n to char[]
  while ( n )
  {
    if ( len_ >= mem_*INITIAL )
    {
      mem_ <<= 1 ;
      if ( !expand() )
      {
	cerr << "Memory expands error!" << endl ;
	exit(1) ;
      }
    }
    num_[len_++] = dToC(n%10) ;
    n /= 10 ;
  }
}

void BigInt::construct( const string &s )
{
  int sSize = s.length() ;
  /* We should not calculate memory size by s' length for there
   * are leading useless zeroes. In class BigReal's contructor function,
   * I conqure this problem.
   */
  while ( mem_*INITIAL <= sSize )
    mem_ <<= 1 ;
#ifdef debug1
  cout << "In construct func, mem_ = " << mem_ << endl ;
#endif
  try
  {
    num_ = new char[mem_*INITIAL] ;
  }
  catch( ... )
  {
    cerr << "Memory Allocation Error!" << endl ;
    exit(1) ;
  }
  if ( sSize == 0 )
  {
    /*
      num_ = new char[INITIAL*mem_] ;
      if ( !num_ ){
      cerr << "Memory Allocation Error!" << endl ;
      return ;
      }
    */
    s_ = true ;
    num_[0] = '0' ;
    len_ = 1 ;
    return ;
  }
  for ( int i = 1 ; i < sSize ; ++i )
    if ( !isdigit( s[i] ) )
    {
      cerr << "Invalid number: " << s << ", initialize BigInt as 0!" << endl ;
      //strcpy( num_, "!rebmun dilavnI" ) ;
      len_ = 1 ;
      num_[0] = '0' ;
      s_ = true ;
      return ;
    }
  if ( !isdigit( s[0] ) )
  {
    if ( s[0] == '-' )
      s_ = false ;
    else if ( s[0] == '+' )
      s_ = true ;
    else
    {
      cerr << "Invalid number: " << s << endl ;
      //strcpy( num_, "!rebmun dilavnI" ) ;
      //delete[] num_ ;
      len_ = 1 ;
      num_[0] = '0' ;
      s_ = true ;

      return ;
    }
    /*    
    num_ = new char[mem_*INITIAL] ;
    if ( !num_ ){
      cerr << "Memory Allocation Error!" << endl ;
      return ;
    }
    */
    int ps = 1 ;
    while ( s[ps] == '0' && ps < sSize ) 
      ++ps ;
    if ( ps == sSize )// all digits are zero
    {       
      len_ = 1 ;
      s_ = true ;
      num_[0] = '0' ;
      return ;
    }
    len_ = sSize-ps ;
    int ptr = 0 ;
    for ( int i = sSize-1 ; i >= ps ; --i )
      num_[ptr++] = s[i] ;
  }
  else 
  {
    //num_ = new char[mem_*INITIAL] ;
    s_ = true ;
    //if ( !num_ ){
    //  cerr << "Memory Allocation Error!" << endl ;
    //  return ;
    //}
    int ps = 0 ;
    while ( s[ps] == '0' && ps < sSize )
      ++ps ;
    if ( ps == sSize ){ // all digits are zero
      len_ = 1 ;
      s_ = true ;
      num_[0] = '0' ;
      return ;
    }
    len_ = sSize-ps ;
    int ptr = 0 ;
    for ( int i = sSize-1 ; i >= ps ; --i )
      num_[ptr++] = s[i] ;
  }
}

BigInt::BigInt( const char *s ) : mem_(1) 
{
  string ts(s) ;
#ifdef debug1
  cout << "ts size = " << ts.length() << endl ;
#endif
  construct(ts) ;
}

BigInt::BigInt( const string &s ) : mem_(1) 
{
  // check s ;
#ifdef debug1
  cout << s << endl ;
#endif

  construct(s) ;
}

BigInt::BigInt( const BigInt &v ) : mem_(1) 
{
  try
  {
    num_ = new char[INITIAL] ;
  }
  catch( ... )
  {
    cerr << "Memory Allocation Error!" << endl ;
    exit(1) ;
  }
  s_ = v.getSign() ;
  //pre_ = v.getPrecision() ;
#ifdef debug1
  cout << "In copy ctr, mem_ = " << mem_ << endl ;
#endif
  contentCopy(v) ;
}

BigInt::BigInt( const BigReal &v ) : mem_(1)
{
  len_ = v.getLen() ;
  // get the decimal position of v ;
  int dp = v.getDP() ;
  if ( dp != NODP )
    len_ = dp ;
  while ( mem_*INITIAL <= len_ )
    mem_ <<= 1 ;

  try
  {
    num_ = new char[mem_*INITIAL] ;
  }
  catch( ... )
  {
    cerr << "Memory Allocation Error!" << endl ;
    exit(1) ;
  }

  s_ = v.getSign() ;
  for ( int i = 0 ; i < len_ ; ++i )
    num_[i] = v.getCharP(i) ;

  return ;
}
 
BigInt & BigInt::operator = ( const BigInt &val )
{
#ifdef debug1
  cout << "here, val's len = " << val.getLen() << endl ;
#endif
  s_ = val.getSign() ;
  contentCopy(val) ;
  return *this ;
}

BigInt & BigInt::operator += ( const BigInt &val )
{
  add(val) ;
  return *this ;
}

BigInt & BigInt::operator -= ( const BigInt &val )
{
  minus(val) ;
  return *this ;
}

BigInt& BigInt::operator *= ( const BigInt &val ) 
{
  multiply(val) ;
  return *this ;
}

BigInt& BigInt::operator /= ( const BigInt &val ) 
{
  if ( val == 0 )
    throw DivideZero() ;
  divide(val) ;
  return *this ;
}

BigInt::~BigInt()
{
  delete[] num_ ;
}

BigInt& BigInt::padd( const BigInt &val )
{
#ifdef debug1
  cout << "mem_ = " << mem_ << endl ;
#endif
  int l = val.getLen() ;
  if ( l >= len_ )
  {
    //int minL = min( l, len_ ) ;
    bool f = false ;
    while ( mem_*INITIAL <= l ){
      mem_ <<= 1 ;
      f = true ;
    }
    if (f)
    {
      if (!expand())
      {
#ifdef debug1
	cout << "Before expands, val = " << *this << endl ;
#endif
	cerr << "Memory expands error!" << endl ;
	exit(1) ;
      }
#ifdef debug1
	cout << "after expand, value is: " << *this << endl ;
#endif

    } 
    int jin = 0 ;
    for ( int i = 0 ; i < l ; ++i )
    {
      int t = jin+getNumP(i)+val.getNumP(i) ;
      num_[i] = dToC(t%10) ;
      jin = t/10 ;
    }
    /*
    for ( int i = minL ; i < l ; ++i )
    {
      int t = jin+val.getNumP(i) ;
      num_[i] = static_cast<char>((t%10)+'0') ;
      jin = t/10 ;
    }
    */
    if ( jin != 0 )
    {
      num_[l] = dToC(jin) ;
      len_ = l+1 ;
    }
    else
      len_ = l ;
  }
  else 
  {
    int jin = 0 ;
    for ( int i = 0 ; i < len_ ; ++i )
    {
      int t = jin+getNumP(i)+val.getNumP(i) ;
      num_[i] = dToC(t%10) ;
      jin = t/10 ;
    }
    if ( jin != 0 )
    {
      if ( len_ == mem_*INITIAL ){
	mem_ <<= 1;
	if ( !expand() ){
	  cerr << "Memory expand error!" << endl ;
	  exit(1) ;
	}
#ifdef debug1
	cout << "after expand, value is: " << *this << endl ;
#endif
      }
      num_[len_] = dToC(jin) ;
      ++len_ ;
    }
  }
  return *this ;
}


BigInt& BigInt::pminus( const BigInt &val )
{
  bool bor = false ;
  int newLen = 0 ;
  for ( int i = 0 ; i < len_ ; ++i ){
    if ( bor ){
      if ( num_[i] != '0' )
      {
	bor = false ;
	num_[i] = dToC(cToD(num_[i])-1) ;
      }
      else
	num_[i] = '9' ;
    }
    int temp = getNumP(i)-val.getNumP(i) ;
    if ( temp < 0 )
    {
      bor = true ;
      temp = 10+temp ;      
    }
    num_[i] = dToC(temp) ;
    if ( temp != 0 )
      newLen = i ;
  }
  len_ = newLen+1 ;
  return *this ;
}


BigInt& BigInt::pmultiply( const BigInt &val )
{
  if ( operator==(BigInt("0")) || val == BigInt("0") )
  {
    *this = "0" ;
    return *this ;
  }
  else 
  {
    int len = val.getLen() ;
    BigInt re("0") ;
    //*this = "0" ;
    for ( int i = 0 ; i < len ; ++i )
    {
      int jin = 0 ;
      string ts = "" ;
      int v = val.getNumP(i) ;
      if ( v == 0 )
	continue ;
      for ( int j = 0 ; j < len_ ; ++j ){
	int temp = getNumP(j)*v+jin ;
#ifdef debug1
	cout << "temp = " << temp << endl ;
#endif
	ts.insert(ts.begin(), dToC(temp%10)) ;
	jin = temp/10 ;
      }
      if ( jin != 0 )
	ts.insert(ts.begin(), dToC(jin)) ;
      for ( int j = 0 ; j < i ; ++j )
	ts += "0" ;
      BigInt tempVal(ts) ;
      re.add(tempVal) ;
#ifdef debug1
      cout << ts << endl ;
      cout << re << endl ;
#endif
    }
    contentCopy(re) ;
  }

  return *this ;
}

BigInt& BigInt::pdivide( const BigInt &val )
{
  int f = pcomp(val) ;
  if ( f == -1 ) {// less than val ;
    s_ = true ;
    len_ = 1 ;
    num_[0] = '0' ;
    return *this ;
  }
  int pos = len_-1 ;
  string remain = "" ;
  remain += num_[pos] ;
  string re = "" ;
  BigInt pdivisor(val) ;
  if ( !val.getSign() )
    pdivisor.changeSign() ;
  --pos ;
#ifdef debug1
  cout << "Enter divide func" << endl ;
  int flag = 0 ;
#endif
  while (1)
  {
    BigInt temp(remain) ;    
#ifdef debug1
    cout << "remian = " << temp << ", pos = " << pos << endl ;
    //if (flag++ > 10)
    // break ;
#endif
    //int tempFlag = 0 ;
    while ( pos >= 0 )
    {
      if ( temp >= pdivisor )
	break ;
      //remain.insert(remain.begin(), num_[pos--]) ;
      remain += num_[pos--] ;
      //cout << "debug - " << remain << endl ;
      temp = BigInt(remain) ;
      //++tempFlag ;
      //if ( tempFlag > 1 )      
      if ( temp < pdivisor )
	re += "0" ;
      else
	break ;
    }
    //cout << "here" << endl ;    
    if ( temp < pdivisor )
      break ;
    int div ;
    //cout << "here" << endl ;
    for ( div = 1 ; div < 10 ; ++div ){
      if ( div*pdivisor > temp )
	break ;
    }
    --div ;
    remain = (temp-div*pdivisor).toString() ;
    if ( remain == "0" )
      remain = "" ;
#ifdef debug1
    cout << "pos = " << pos << endl ;
    cout << "remain = " << remain << endl ;
#endif
    re += dToC(div) ;
  }
  contentCopy(BigInt(re)) ;
  return *this ;
}

BigInt& BigInt::add( const BigInt &val ) 
{
  if ( s_ && val.getSign() ){ // positive add positive
    padd( val ) ;
  }
  else if ( !s_ && !val.getSign() ){
    padd( val ) ;
  }
  else if ( s_ && !val.getSign() ){ // positive add negative
    int f = pcomp(val) ;
#ifdef debug1
    cout << len_ << " " << val.getLen() << endl ;
    cout << f << endl ;
#endif
    if ( f > 0 ){ // positive greater than val's absolute value
      pminus( val ) ;
    }
    else if ( f < 0 ){
      BigInt temp(*this) ;
      contentCopy(val) ;
      pminus(temp) ;
      s_ = false ;
    }
    else { // equal
      len_ = 1 ;
      s_ = true ;
      num_[0] = '0' ;
    }
  }
  else { // negative add positive
    int f = pcomp(val) ;
    if ( f > 0 ){
      pminus(val) ;
    }
    else if ( f < 0 )
    {
      BigInt temp(*this) ;
      contentCopy(val) ;
      pminus(temp) ;
      s_ = true ;
    }
    else 
    {
      len_ = 1 ;
      s_ = true ;
      num_[0] = '0' ;
    }
  }
  return *this ;
}

BigInt& BigInt::minus( const BigInt &val )
{
  if ( s_ && !val.getSign() ){ // positive minus negative
    padd( val ) ;
  }
  else if ( !s_ && val.getSign() ){
    padd( val ) ;
  }
  else if ( s_ && val.getSign() ){ // positive minus positive
    int f = pcomp(val) ;
#ifdef debug1
    cout << len_ << " " << val.getLen() << endl ;
    cout << f << endl ;
#endif
    if ( f > 0 ){ // positive greater than val's absolute value
      pminus( val ) ;
    }
    else if ( f < 0 ){
      BigInt temp(*this) ;
      contentCopy(val) ;
      pminus(temp) ;
      s_ = false ;
    }
    else { // equal
      len_ = 1 ;
      s_ = true ;
      num_[0] = '0' ;
    }
  }
  else { // negative minus negative
    int f = pcomp(val) ;
    if ( f > 0 ){
      pminus(val) ;
    }
    else if ( f < 0 ){
      BigInt temp(*this) ;
      contentCopy(val) ;
      pminus(temp) ;
      s_ = true ;
    }
    else {
      len_ = 1 ;
      s_ = true ;
      num_[0] = '0' ;
    }
  }
  return *this ;
}


BigInt& BigInt::multiply( const BigInt &val )
{
  pmultiply(val) ;
  if ( operator==(BigInt("0")) )
  {
    s_ = true ;
    return *this ;
  }
  if ( s_ && val.getSign() || !s_ && !val.getSign() )
    s_ = true ;
  else
    s_ = false ;
  return *this ;
}


BigInt& BigInt::divide( const BigInt &val )
{
  if ( val == "0" ){
    //cerr << "Error! Divisor cannot be zero!" << endl ;
    //return *this ;
    throw billjeff::DivideZero() ;
  }
  pdivide(val) ;
  // Result is zero, set the symbol is true(+).
  if ( pcomp(BigInt(0)) == 0 )
  {
    s_ = true ;
    return *this ;
  }
  // Condition for none zero result.
  if ( s_ && val.getSign() || !s_ && !val.getSign() ){
    s_ = true ;
  } 
  else
    s_ = false ;
  return *this ;
}


BigInt& BigInt::operator ++ () 
{
  add(BigInt("1")) ;
  return *this ;
}


BigInt BigInt::operator ++ (int s) 
{
  BigInt temp(*this) ;
  operator++() ;
  return temp ;
}


BigInt& BigInt::operator -- () 
{
  minus(BigInt("1")) ;
  return *this ;
}


BigInt BigInt::operator -- (int s) 
{
  BigInt temp(*this) ;
  operator--() ;
  return temp ;
}


int BigInt::pcomp( const BigInt &val ) const 
{
  if ( len_ > val.getLen() ) // current number is absolute bigger
    return 1 ;
  else if ( len_ < val.getLen() )
    return -1 ;
  //int i ;
  for ( int i = len_-1 ; i >= 0 ; --i )
    if ( num_[i] > dToC(val.getNumP(i)) )
      return 1 ;
    else if ( num_[i] < dToC(val.getNumP(i)) )
      return -1 ;
  return 0 ;
}

string BigInt::toPString() const 
{
  string re = "" ;
  for ( int i = len_-1 ; i >= 0 ; --i )
    re += num_[i] ;
  return re ;
}

bool BigInt::operator == ( const BigInt &val ) const 
{
  if ( (s_ == val.getSign()) && (len_ == val.getLen()) && (pcomp(val) == 0) )
    return true ;
  return false ;
}

bool BigInt::operator != ( const BigInt &val ) const 
{
  if ( operator==(val) )
    return false ;
  return true ;
}

bool BigInt::operator < ( const BigInt &val ) const 
{
  bool vs = val.getSign() ;
  if ( s_ == false && vs == true )
    return true ;
  if ( s_ == true && vs == false )
    return false ;
  int f = pcomp(val) ;
  if ( s_ == true ){
    if ( f == 1 || f == 0 )
      return false ;
    else
      return true ;
  }
  else{
    if ( f == 1 )
      return true ;
    else
      return false ;
  }
}

bool BigInt::operator > ( const BigInt &val ) const 
{
  if ( (operator<(val) == false) && operator!=(val) == true )
    return true ;
  return false ;
}

bool BigInt::operator <= ( const BigInt &val ) const 
{
  if ( operator>(val) == false )
    return true ;
  return false ;
}

bool BigInt::operator >= ( const BigInt &val ) const 
{
  if ( operator<(val) == false )
    return true ;
  return false ;
}


BigInt BigInt::operator - () 
{
  BigInt temp(*this) ;
  temp.changeSign() ;
  return temp ;
}

bool BigInt::expand()
{
#ifdef debug1
  cout << "len_ = " << len_ << endl ;
  cout << "mem_ = " << mem_ << endl ;
#endif
  if ( mem_ > 10000 ){
    cerr << "Number is too large!" << endl ;
    return false ;
  }

  char *newNum ;
  try
  {
    newNum = new char[mem_*INITIAL] ;
  }
#ifdef debug1
  if ( !newNum )
    cout << "Here, Memory allocation error" << endl ;
#endif
  catch( ... )
  {
    cerr << "Memory Allocation Error in BigInt::expand!" << endl ;
    return false ;
  }
  for ( int i = 0 ; i < len_ ; ++i )
    newNum[i] = num_[i] ;
  delete[] num_ ;
  num_ = newNum ;
  return true ;
}


void BigInt::contentCopy( const BigInt &val ) 
{
#ifdef debug1
  cout << "mem_ = " << mem_ << " , and it is in contentCopy func" << endl ;
  cout << "val = " << val << endl ;
#endif
  int newLen = val.getLen() ;
  bool f = false ;
  while ( mem_*INITIAL <= newLen )
  {
    mem_ <<= 1 ;
    f = true ;
  }
  if (f)
  {
    if (!expand())
    {
      cerr << "Memory expanding error!" << endl ;
      exit(1) ;
    }
  }
  len_ = newLen ;
  for ( int i = 0 ; i < len_ ; ++i )
    num_[i] = dToC(val.getNumP(i)) ;
}

string BigInt::toString() const 
{
  string sign = "" ;
  if ( !s_ )
    sign = "-" ;
  return (sign+toPString()) ;
}

ostream & billjeff::operator << ( ostream &os, const BigInt &o ) 
{
  if ( !o.s_ )
    os << "-" ;
  for ( int i = o.len_-1 ; i >= 0 ; --i )
    os << o.num_[i] ;
  return os ;
}

istream & billjeff::operator >> ( istream &is, BigInt &in ) 
{
  string s ;
  is >> s ;
  in = s ;
  return is ;
}

BigInt billjeff::operator + ( const BigInt &op1, const BigInt &op2 )
{  
  BigInt temp(op1) ;
  temp.add(op2) ;
  return temp ;
}

BigInt billjeff::operator - ( const BigInt &op1, const BigInt &op2 ) 
{
  BigInt temp(op1) ;
  temp.minus(op2) ;
  return temp ;
}

BigInt billjeff::operator * ( const BigInt &op1, const BigInt &op2 ) 
{
  BigInt temp(op1) ;
  //cout << "op1 = " << op1 << endl ;
  //cout << "temp = " << temp << endl ;
  temp.multiply(op2) ;
  return temp ;
}

BigInt billjeff::operator / ( const BigInt &op1, const BigInt &op2 )
{
  if ( op2 == 0 )
    throw DivideZero() ;
  BigInt temp(op1) ;
  temp.divide(op2) ;
  return temp ;
}



BigInt billjeff::operator% (const BigInt &p, const BigInt &q ) 
{
  if ( q == 0 )
  {
    cerr << "The second parameter for operator% cannot be zero!" << endl ;
    throw billjeff::DivideZero() ;
  }

  {
    BigInt tmp = p/q ;
    return (p-tmp*q) ;
  }
}
