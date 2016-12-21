#include <iostream>
#include <cstring>
#include <sstream>
#include "list.h"

#ifndef JPSTRING
#define JPSTRING

class jpstring {
 public:
  jpstring(int initial_size = DEFAULT_CAPACITY);
  jpstring(const jpstring& rhs);
  jpstring(const char* chars, int initial_size = DEFAULT_CAPACITY);
  //jpstring(const jpstring& rhs, int initial_size = DEFAULT_CAPACITY);
  ~jpstring();

  operator char* ();
  operator const char* ();

  bool operator==(const jpstring& rhs) const;
  bool operator==(const char* rhs) const;
  bool operator!=(const jpstring& rhs) const;
  bool operator!=(const char* rhs) const;
  bool operator<(const jpstring& rhs) const;
  bool operator<(const char* rhs) const;
  bool operator<=(const jpstring& rhs) const;
  bool operator<=(const char* rhs) const;
  bool operator>(const jpstring& rhs) const;
  bool operator>(const char* rhs) const;
  bool operator>=(const jpstring& rhs) const;
  bool operator>=(const char* rhs) const;

  jpstring& operator=(const jpstring& rhs);

  jpstring& operator+=(const jpstring& rhs);
  jpstring& operator+=(const char* rhs);

  jpstring operator+(const jpstring& rhs);
  jpstring operator+(const char* rhs);
  jpstring operator+(const int rhs);
  jpstring operator+(const double rhs);

  // jpstring* split( char delimiter = ' ', char eol = '\0');
  list<jpstring>* split(char delimiter= ' ', char eol = '\0');

  friend std::ostream& operator<<(std::ostream& out, const jpstring& rhs);
  friend std::istream& operator>>(std::istream& in,  jpstring& rhs);

  int length() const;
  int size() const;
 private:
  bool equals(const char* rhs) const;

  char* to_cstring() const;
  void grow_chars(int minimum_lenghth);
  void append(const char* chars);

  int capacity;
  int char_length;
  char* chars;

  const static int DEFAULT_CAPACITY = 16;
  const static int BUFFER_SIZE = 140;
};

#endif
