#include "llstring.h"
#include <cstring>

llstring::llstring() {
  chars = new clist();
  length = 0;
}

llstring::llstring(const char* str) {
  chars = new clist();
  length = strlen(str);
  chars->insert(str);
}

llstring::~llstring() {
  delete chars;
}

bool llstring::operator==(llstring& rhs) {
  bool equals = false;

  if (length != rhs.length) {
    return false;
  }

  const char* rhs_str = rhs.to_cstring();

  equals = (*(this) == rhs_str);

  delete[] rhs_str;

  return equals;
}

bool llstring::operator==(const char* rhs) {
  bool equals = false;

  const char* lhs = to_cstring();

  equals = (strcmp(lhs, rhs) == 0);

  delete[] lhs;

  return equals;
}

bool llstring::operator!=(llstring& rhs) {
  return !(*(this) == rhs);
}

bool llstring::operator!=(const char* rhs) {
  return !(*(this) == rhs);
}

bool llstring::operator<(llstring& rhs) {
  bool less = false;

  const char* rhs_str = rhs.to_cstring();

  less = (*(this) < rhs_str);

  delete[] rhs_str;

  return less;
}

bool llstring::operator<(const char* rhs) {
  bool less = false;

  const char* lhs = to_cstring();

  less = (strcmp(lhs, rhs) < 0);

  delete[] lhs;

  return less;
}

bool llstring::operator<=(llstring& rhs) {
  return (*(this) == rhs) | (*(this) < rhs);
}

bool llstring::operator<=(const char* rhs) {
  return (*(this) == rhs) | (*(this) < rhs);
}

bool llstring::operator>(llstring& rhs) {
  bool greater = false;

  const char* rhs_str = rhs.to_cstring();

  greater = (*(this) < rhs_str);

  delete[] rhs_str;

  return greater;
}

bool llstring::operator>(const char* rhs) {
  bool greater = false;

  const char* lhs = to_cstring();

  greater = (strcmp(lhs, rhs) > 0);

  delete[] lhs;

  return greater;
}

bool llstring::operator>=(llstring& rhs) {
  return (*(this) == rhs) | (*(this) > rhs);
}

bool llstring::operator>=(const char* rhs) {
  return (*(this) == rhs) | (*(this) > rhs);
}




llstring::operator char* () {
  char* buffer = new char[length + 1];

  // FIXME implement array create in clist

  return buffer;
}

llstring::operator const char* () {
  char* buffer = new char[length + 1];

  // FIXME implement the char* array creation in clist

  return buffer;
}

const char* llstring::to_cstring() const {
  return (const char*)this;
}



llstring& llstring::operator+=(const llstring& rhs) {


  return *this;
}
