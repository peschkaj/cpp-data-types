#include "llstring.h"
#include <cstring>

llstring::llstring() {
  chars = new clist();
  data_length = 0;
}

llstring::llstring(const char* str) {
  chars = new clist();
  append(str);
}

llstring::llstring(const llstring& rhs) {
  chars = new clist();
  append(rhs.to_cstring());
}

llstring::~llstring() {
  delete chars;
  chars = NULL;
}

bool llstring::equals(const llstring& rhs) const {
  bool equals = false;
  const char* rhs_str = rhs.to_cstring();

  equals = this->equals(rhs_str);

  delete[] rhs_str;
  rhs_str = NULL;

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

bool llstring::operator==(const llstring& rhs) const {
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

  less = (*this < rhs_str);

  delete[] rhs_str;
  rhs_str = NULL;

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

  greater = (*this > rhs_str);

  delete[] rhs_str;
  rhs_str = NULL;

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



/* Overloading the assignment operator.

   This includes a test to make sure we're not assigning to ourself.

   Once we know we're not trying to overwrite ourself, the next step is to
   move the current list of characters into a temporary clist. If the program
   hits an exception while allocating memory, this llstring will still have
   its original characters.
 */
llstring& llstring::operator=(const llstring& rhs) {
  if (this == &rhs) {
    return *this;
  }

  clist *old_chars = chars;
  chars = new clist;
  chars->append(rhs.to_cstring());
  delete old_chars;

  return *this;
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



llstring llstring::operator+(const llstring& rhs) {
  llstring new_string(to_cstring());
  new_string += rhs.to_cstring();
  return new_string;
}

llstring llstring::operator+(const char* rhs) {
  llstring new_string(to_cstring());
  new_string += rhs;
  return new_string;
}



std::ostream& operator<<(std::ostream& out, const llstring& str) {
  out << str.to_cstring();

  return out;
}
