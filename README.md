## Demand Analysis and Function Design
  * Support "+"(operator and sign operator) "-" "multiply" "/" "++" "--" ">" "<" ">=" "<=" "==" "!=" "bit operations" "power" "log" "sqrt" "%" etc operations;
  * All numbers are stored in class as char[], which the dimension is 1000( const int LEN = 1000);
  * "+" "-" "multiply" "/" and "%"( I donot know whether mod is a operator ) are member functions( overloaded ).
  * function "power" "log" and "sqrt" are provied as undepended functions which take several class objects as their parameters. "power" "log" and "sqrt" are also member functions in class. The relationship between member "power" and non-member "power"(for example) is like this:  
    ```
      namespace billjeff {
        class BigNumbers {
        public:
          void power( const BigNumbers& n ) { ... }
        }
        ...
        void power( BigNumbers& base, const BigNumber& pow ) {
          base.power(pow) ;
        }
      }
    ```
  * class ctr: Accept string/char[] based parameter for ctr, the default number base is 10, user can spicify the base by providing another parameter for ctr; provides default ctr to support array;
  * useful functions: class provides a function to convert the "big number" to string or char[]; 

## Memory Model
  * On demand memory allocation model. First 2exp10, then 2exp11, then 2exp12 and so on. ( Maybe I should choose a better memory model for my application ).

## Decimal
  * BigNumber class just supports decimal format number and calculation. If you have no-decimal number, there are also tools available in the "BigNumber.h" header file.

## Detailed Issues
  * About 0: the sign for 0 is true(sign is true), and length is 1, so num array's content is '0'.
  * About float number add and minus: e.g. a = 0.001, b = 10.9993, for a+b, convertAB() function will convert a to 10, and b to 10993, then we construct two BigInt object IA = a, IB = b, and get IC = IA+IB. Then we adjust IC and copy its content to this. for a-b, we first swap(a, b), so a is 10.9993, b is 0.001, and after using convertAB(), a is 109993, b is 10, construct two BigInt object, and IC = 109983, and using adjust function to copy the content back to this.
  * BigInt/BigInt(divide operation), the result is BigInt. And the result of divide operation between BigReal and BigInt is always BigReal.
  * BigReal::setPrecision can set the divide precision of divide result. e.g. BigReal r, c, r.setPrecision(10), then the result of r/c has at most 10 none zero digits after decimal point. Note if the divide result is 1.11111111119, then it will return 1.1111111111, not 1.1111111112.
  * I add keyword "explicit" before BigInt and BigReal's cotrs. And add several functions to support comparison and math operators. For BigInt, added functions are - template operator(add,sub,mul,div,%,>,<,>=,<=,==,!=,=); for BigReal, added functions are - template operator(add,sub,mul,div,>,<,>=,<=,==,!=,=). Many codes are added. Why do I have to add explicit keyword before ctors, there are two reasons: Fisrt, it is for prohibiting implicit conversions, second, when I want to do such as 1 < BigInt or 1 < BigReal comparison, implicit conversion leads to ambitious function calls, for 
  ```
  bool operator( BigInt&, BigInt& );
  ```
  and
  ```
  bool operator( BigReal&, BigInt& );
  ```
  are candidate functions. All these operators are class specific fucntions, it means that BigInt and BigReal should have their own overloaded operators. It can use BigReal as all operators' parameter, but it is not good. For example, if we implement just one function
  ```
  template <class T, class V> 
    BigReal operator+( const T &a, const V &b );
  ```
  when we do add operations for two BigInt objects, we have to convert the result back to BigInt! It makes no sence.

## Class List
  * BigInt
  * BigReal
  * Number


## About Exception
  * DivideZero: operator/, operator% will throw DivideZero exception if divisor is zero.

## Function List
  * operator add/multiply/divide/minus: overloaded functions for BigInt and BigReal.
    * BigReal add: First, member function add makes a decision about the symbol for the add operation result. Then it calls padd(), which calculates two positive real number's sum. In padd() function, we construct two BigInt number which ignore the decimal point, when we get the sum, we add decimal point back to the result when it is necessary.
  * Input and Output(including parameters for ctors)
    * Input for BigReal: For class constructor, double, float, int(including BigInt), NUMeNUM format are accepted. We recommend that if you want to process double type numbers preciously, then you can consider about using BigReal. Otherwise, it is not recommended to use BigReal. For example, we want to construct BigReal for 12345.123213213e100, system will use 1.23451e+104 instead. If you want to keep precision, use char[] or string.
    * Input for BigInt:
    * Invalid Input: When the input is invalid, both BigInt and BigReal will initialize their object to zero.
  * sqrt function
    * sqrt for BigInt: This function take a BigInt object as its first argument, and precision as its second argument. precision is int type, and it is used to specify the precision for the result. e.g. if we call sqrt as sqrt( ia, 10 ), and the result will have 11 non-zero digits after decimal point. precision's default value is 10.

## Experience
  * Organize head file( for class/function declaration and template function implementation ) well, or, it is hard to debug. Sometimes we put all function 	   declaration in other header files B.h, and class declaration in current header file A.h, functions use classes, so it is necessary include B.h at the last in A.h or include B.h just after A.h in A.cpp files.
  * Put the most specilist overloaded functions before any overloadedtemplate function.
  