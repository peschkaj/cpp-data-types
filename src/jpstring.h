/* Jeremiah Peschka
   <jpeschka@pdx.edu>

   Implements a string-like class with convenient functions for working
   with strings of characters, rather than using char arrays.

   Strings are initialized with a capacity. When a string is about to
   grow beyond its initial capacity, the capacity is double. While
   large capacities waste memory, they prevent potentially expensive
   growth and reallocation. Conversely, small capacities save memory
   but cause additional re-allocations as the string grows.

   **N.B.** Throughout the documentation for this class, `string` is
            substituted for `jpstring` for two reasons.
            1) it's easier to type
            2) it doesn't upset the spellchecker in emacs
 */

#include <cstring>
#include <iostream>
#include <sstream>
#include "slist.h"

#ifndef JPSTRING
#define JPSTRING

class jpstring {
 public:
  /* Creates a string with the specified initial capacity. */
  jpstring(int initial_size = DEFAULT_CAPACITY);



  /* Copy constructor */
  jpstring(const jpstring& rhs, int initial_size = DEFAULT_CAPACITY);



  /* Creates a string from a char array.

     Even if initial_size is smaller than chars, the process of appending
     chars into the current string will grow the capacity.
   */
  jpstring(const char* chars, int initial_size = DEFAULT_CAPACITY);



  /* Tears down this string and all associated resources. */
  ~jpstring();



  /* Converts this string to a char* */
  operator char*();
  operator const char*();



  /* Equality operator overloads.

     These require both sides of the comparison to contain the same
     characters.
   */
  bool operator==(const jpstring& rhs) const;
  bool operator==(const char* rhs) const;



  /* Inequality overloads.

     These require the strings to be not ==.
     Internally, they implement this through using a !(a == b).
   */
  bool operator!=(const jpstring& rhs) const;
  bool operator!=(const char* rhs) const;



  /* Less than overload

     Returns true if rhs sorts after this string lexicographically.
     Behavior-wise, this is the same as `RCMP(a, b) < 0`.
   */
  bool operator<(const jpstring& rhs) const;
  bool operator<(const char* rhs) const;



  /* Less than or equal overload

     Returns true if rhs sorts after or equivalent to this string,
     lexicographically. Behavior-wise, this is the same as
     `strcmp(a, b) <= 0`.
   */
  bool operator<=(const jpstring& rhs) const;
  bool operator<=(const char* rhs) const;



  /* Greater than operator overload

     Returns true if rhs sorts before this string.
     Behavior-wise, this is the same as `strcmp(a, b) > 0`.
   */
  bool operator>(const jpstring& rhs) const;
  bool operator>(const char* rhs) const;



  /* Greater than or equal operator overload.

     Returns true if rhs sorts before or equal to this string.
     Behavior-wise, this is the same as `strmcp(a, b) >= 0`.
   */
  bool operator>=(const jpstring& rhs) const;
  bool operator>=(const char* rhs) const;



  /* Assignment operator overload.

     Allows the user to either set this string equal to another string
     or equal to a char*.
   */
  jpstring& operator=(const jpstring& rhs);
  jpstring& operator=(const char* rhs);



  /* += operator overload

     This allows the user to append other strings to this one.

     If a larger number of strings are being appended, consider using
     the `stringbuilder` instead.
   */
  jpstring& operator+=(const jpstring& rhs);
  jpstring& operator+=(const char* rhs);
  jpstring& operator+=(const jpstring* rhs);



  /* Addition operator overloading

     Each explicit overload allows the user to append additional data
     to this string.
   */
  jpstring operator+(const jpstring& rhs);
  jpstring operator+(const char* rhs);
  jpstring operator+(const int rhs);
  jpstring operator+(const double rhs);



  /* Splits this string into a list of strings.

     The default split will split on a space and takes the null
     terminator to be the end of string for split purposes.

     The `eol` parameter is necessary because this string uses a
     c-string as the representation of the string.
   */
  slist<jpstring>* split(char delimiter = ' ', char eol = '\0');



  /* Overloads allowing the stream operator to be used with a string */
  friend std::ostream& operator<<(std::ostream& out, const jpstring& rhs);
  friend std::istream& operator>>(std::istream& in, jpstring& rhs);

  /* Returns the current length of the string. */
  int length() const;



  /* Returns the capacity of this string. */
  int size() const;

 private:
  /* A convenience method provided for comparison operations. */
  bool equals(const char* rhs) const;



  /* Converts this string into a c-string */
  char* to_cstring() const;



  /* Grows this string's capacity to the minimum length

     Contents are preserved as the string is grown. Any resources that
     need to be released will be released and destroyed as a result of
     the grow operation.
   */
  void grow_chars(int minimum_lenghth);



  /* Appends characters to the end of the string.

     If the string is not long enough to contain the new characters,
     `capacity` is doubled and then `grow_chars` is called with the
     new string.
   */
  void append(const char* chars);



  /* capacity contains the maximum size of chars.

     chars is allocated as `new char[capacity]`
   */
  int capacity;


  /* char_length holds the current number of characters in `chars` */
  int char_length;



  /* The characters contained in this string */
  char* chars;



  /* The default capacity of a string */
  const static int DEFAULT_CAPACITY = 16;



  /* Sizing for internal buffers used in >> and split */
  const static int BUFFER_SIZE = 140;
};

#endif
