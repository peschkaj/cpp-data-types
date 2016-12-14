#include "llstring.h"
#include <cstring>

llstring::llstring() {
  chars = new clist();
  data_length = 0;
}

llstring::llstring(const char* str) {
  chars = new clist();
  data_length = strlen(str);
  chars->insert(str);
}

llstring::~llstring() {
  delete chars;
  chars = NULL;
}

bool llstring::equals(const llstring& rhs) const {
  bool equals = false;

  if (data_length != rhs.data_length) {
    return false;
  }

  const char* rhs_str = rhs.to_cstring();
  const char* lhs_str = to_cstring();

  equals = (strcmp(lhs_str, rhs_str) == 0);

  delete[] rhs_str;
  delete[] lhs_str;
  rhs_str = NULL;
  lhs_str = NULL;

  return equals;
}

bool llstring::equals(const char* rhs) const {
  bool equals = false;

  const char* lhs = to_cstring();

  equals = (strcmp(lhs, rhs) == 0);

  delete[] lhs;
  lhs = NULL;

  return equals;
}

bool llstring::operator==(llstring& rhs) const {
  return equals(rhs);
}

bool llstring::operator==(const char* rhs) const {
  return equals(rhs);
}

bool llstring::operator!=(llstring& rhs) const {
  return !(*(this) == rhs);
}

bool llstring::operator!=(const char* rhs) const {
  return !(*(this) == rhs);
}

bool llstring::operator<(llstring& rhs) const {
  bool less = false;

  const char* rhs_str = rhs.to_cstring();
  const char* lhs_str = to_cstring();

  less = (strcmp(lhs_str, rhs_str) < 0);

  delete[] rhs_str;
  delete[] lhs_str;
  rhs_str = NULL;
  lhs_str = NULL;

  return less;
}

bool llstring::operator<(const char* rhs) const {
  bool less = false;

  const char* lhs = to_cstring();

  less = (strcmp(lhs, rhs) < 0);

  delete[] lhs;
  lhs = NULL;

  return less;
}

bool llstring::operator<=(llstring& rhs) const {
  return (*(this) == rhs) | (*(this) < rhs);
}

bool llstring::operator<=(const char* rhs) const {
  return (*(this) == rhs) | (*(this) < rhs);
}

bool llstring::operator>(llstring& rhs) const {
  bool greater = false;

  const char* rhs_str = rhs.to_cstring();
  const char* lhs_str = to_cstring();

  greater = (strcmp(lhs_str, rhs_str) > 0);

  delete[] rhs_str;
  delete[] lhs_str;
  rhs_str = NULL;
  lhs_str = NULL;

  return greater;
}

bool llstring::operator>(const char* rhs) const {
  bool greater = false;

  const char* lhs = to_cstring();

  greater = (strcmp(lhs, rhs) > 0);

  delete[] lhs;
  lhs = NULL;

  return greater;
}

bool llstring::operator>=(llstring& rhs) const {
  return (*(this) == rhs) | (*(this) > rhs);
}

bool llstring::operator>=(const char* rhs) const {
  return (*(this) == rhs) | (*(this) > rhs);
}




/* Converts the llstring into some kind of char* or const char* by using
   the appropriate method in the clist container
 */
llstring::operator char* () {
  return chars->to_cstring();
}

llstring::operator const char* () {
  return chars->to_cstring();
}

const char* llstring::to_cstring() const {
  return chars->to_cstring();
}



int llstring::length() const {
  return data_length;
}



int llstring::append(const char* to_add) {
  int added = 0;

  added = chars->append(to_add);
  data_length += added;

  return added;
}




llstring& llstring::operator+=(const llstring& rhs) {
  char* buffer;

  buffer = new char[rhs.length() + 1];
  strcpy(buffer, rhs.to_cstring());
  append(buffer);
  delete[] buffer;

  return *this;
}

llstring& llstring::operator+=(const char* rhs) {
  append(rhs);

  return *this;
}
