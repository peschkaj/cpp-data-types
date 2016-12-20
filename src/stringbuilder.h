#include <cstring>
#include <iostream>
#include "clist.h"

#ifndef STRINGBUILDER
#define STRINGBUILDER

class stringbuilder {
 public:
  // Create an empty stringbuilder
  stringbuilder();

  // Create a stringbuilder from a char array
  stringbuilder(const char* str);

  // Create an stringbuilder from another stringbuilder
  stringbuilder(const stringbuilder& rhs);

  // Destroy this stringbuilder and all associated resources
  ~stringbuilder();

  bool equals(const stringbuilder& rhs) const;
  bool equals(const char* rhs) const;

  // Comparison operator overloads
  bool operator==(const stringbuilder& rhs) const;
  bool operator==(const char* rhs) const;
  bool operator!=(stringbuilder& rhs) const;
  bool operator!=(const char* rhs) const;
  bool operator<(stringbuilder& rhs) const;
  bool operator<(const char* rhs) const;
  bool operator<=(stringbuilder& rhs) const;
  bool operator<=(const char* rhs) const;
  bool operator>(stringbuilder& rhs) const;
  bool operator>(const char* rhs) const;
  bool operator>=(stringbuilder& rhs) const;
  bool operator>=(const char* rhs) const;

  // Operator overloading to allow an stringbuilder to be used directly in
  // place of a char* without using `to_cstring()`.
  operator char* ();
  operator const char* ();

  // Turns an stringbuilder into a char array
  const char* to_cstring() const;

  stringbuilder& operator=(const stringbuilder& rhs);

  // Overloading the += operator to add either another stringbuilder or
  // a char array
  stringbuilder& operator+=(const stringbuilder& rhs);
  stringbuilder& operator+=(const char* rhs);

  // Overloading the + operator to combine two stringbuilders or one stringbuilder
  // and a char array
  stringbuilder operator+(const stringbuilder& rhs);
  stringbuilder operator+(const char* rhs);
  stringbuilder operator+(const int rhs);
  stringbuilder operator+(const double rhs);


  /* Return the length of the string in the container */
  int length() const;

  /* append characters to the string */
  int append(const char* to_add);

  friend std::ostream& operator<<(std::ostream& out, const stringbuilder& str);

 private:


  int data_length;
  clist* chars;
};

#endif
