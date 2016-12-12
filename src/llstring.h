#include <cstring>
#include "clist.h"

#ifndef LLSTRING
#define LLSTRING

class llstring {
 public:
  // Create an empty llstring
  llstring();

  // Create a llstring from a char array
  llstring(const char* str);

  // Destroy this llstring and all associated resources
  ~llstring();

  // Comparison operator overloads
  bool operator==(llstring& rhs);
  bool operator==(const char* rhs);
  bool operator!=(llstring& rhs);
  bool operator!=(const char* rhs);
  bool operator<(llstring& rhs);
  bool operator<(const char* rhs);
  bool operator<=(llstring& rhs);
  bool operator<=(const char* rhs);
  bool operator>(llstring& rhs);
  bool operator>(const char* rhs);
  bool operator>=(llstring& rhs);
  bool operator>=(const char* rhs);


  // Overloading the += operator to add either another llstring or
  // a char array
  llstring& operator+=(const llstring& rhs);
  llstring& operator+=(const char* rhs);

  // Overloading the + operator to combine two llstrings or one llstring
  // and a char array
  llstring& operator+(const llstring& rhs);
  llstring& operator+(const char* rhs);

  // Turns an llstring into a char array
  const char* to_cstring() const;

  // Operator overloading to allow an llstring to be used directly in
  // place of a char* without using `to_cstring()`.
  operator char* ();
  operator const char* ();


 private:
  // Appends a single clist node to the llstring


  int length;
  clist* chars;
};

#endif