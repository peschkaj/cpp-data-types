#include <cstring>
#include <iostream>
#include "clist.h"

#ifndef LLSTRING
#define LLSTRING

class llstring {
 public:
  // Create an empty llstring
  llstring();

  // Create a llstring from a char array
  llstring(const char* str);

  // Create an llstring from another llstring
  llstring(const llstring& rhs);

  // Destroy this llstring and all associated resources
  ~llstring();

  bool equals(const llstring& rhs) const;
  bool equals(const char* rhs) const;

  // Comparison operator overloads
  bool operator==(const llstring& rhs) const;
  bool operator==(const char* rhs) const;
  bool operator!=(llstring& rhs) const;
  bool operator!=(const char* rhs) const;
  bool operator<(llstring& rhs) const;
  bool operator<(const char* rhs) const;
  bool operator<=(llstring& rhs) const;
  bool operator<=(const char* rhs) const;
  bool operator>(llstring& rhs) const;
  bool operator>(const char* rhs) const;
  bool operator>=(llstring& rhs) const;
  bool operator>=(const char* rhs) const;

  // Operator overloading to allow an llstring to be used directly in
  // place of a char* without using `to_cstring()`.
  operator char* ();
  operator const char* ();

  // Turns an llstring into a char array
  const char* to_cstring() const;

  llstring& operator=(const llstring& rhs);

  // Overloading the += operator to add either another llstring or
  // a char array
  llstring& operator+=(const llstring& rhs);
  llstring& operator+=(const char* rhs);

  // Overloading the + operator to combine two llstrings or one llstring
  // and a char array
  llstring operator+(const llstring& rhs);
  llstring operator+(const char* rhs);
  llstring operator+(const int rhs);
  llstring operator+(const double rhs);


  /* Return the length of the string in the container */
  int length() const;

  /* append characters to the string */
  int append(const char* to_add);

  friend std::ostream& operator<<(std::ostream& out, const llstring& str);

 private:


  int data_length;
  clist* chars;
};

#endif
