#include "stringbuilder.h"
#include <cstring>
#include <cstdlib>

stringbuilder::stringbuilder() {
  chars = new clist();
  data_length = 0;
}

stringbuilder::stringbuilder(const char* str) {
  chars = new clist();
  append(str);
}

stringbuilder::stringbuilder(const stringbuilder& rhs) {
  chars = new clist();
  const char* buffer = rhs.to_cstring();
  append(buffer);

  delete[] buffer;
}

stringbuilder::~stringbuilder() {
  delete chars;
  chars = NULL;
}

bool stringbuilder::equals(const stringbuilder& rhs) const {
  bool equals = false;
  const char* rhs_str = rhs.to_cstring();

  equals = this->equals(rhs_str);

  delete[] rhs_str;
  rhs_str = NULL;

  return equals;
}

bool stringbuilder::equals(const char* rhs) const {
  bool equals = false;

  const char* lhs = to_cstring();

  equals = (strcmp(lhs, rhs) == 0);

  delete[] lhs;
  lhs = NULL;

  return equals;
}

bool stringbuilder::operator==(const stringbuilder& rhs) const {
  return equals(rhs);
}

bool stringbuilder::operator==(const char* rhs) const {
  return equals(rhs);
}

bool stringbuilder::operator!=(stringbuilder& rhs) const {
  return !(*(this) == rhs);
}

bool stringbuilder::operator!=(const char* rhs) const {
  return !(*(this) == rhs);
}

bool stringbuilder::operator<(stringbuilder& rhs) const {
  bool less = false;

  const char* rhs_str = rhs.to_cstring();

  less = (*this < rhs_str);

  delete[] rhs_str;
  rhs_str = NULL;

  return less;
}

bool stringbuilder::operator<(const char* rhs) const {
  bool less = false;

  const char* lhs = to_cstring();

  less = (strcmp(lhs, rhs) < 0);

  delete[] lhs;
  lhs = NULL;

  return less;
}

bool stringbuilder::operator<=(stringbuilder& rhs) const {
  return (*(this) == rhs) | (*(this) < rhs);
}

bool stringbuilder::operator<=(const char* rhs) const {
  return (*(this) == rhs) | (*(this) < rhs);
}

bool stringbuilder::operator>(stringbuilder& rhs) const {
  bool greater = false;

  const char* rhs_str = rhs.to_cstring();

  greater = (*this > rhs_str);

  delete[] rhs_str;
  rhs_str = NULL;

  return greater;
}

bool stringbuilder::operator>(const char* rhs) const {
  bool greater = false;

  const char* lhs = to_cstring();

  greater = (strcmp(lhs, rhs) > 0);

  delete[] lhs;
  lhs = NULL;

  return greater;
}

bool stringbuilder::operator>=(stringbuilder& rhs) const {
  return (*(this) == rhs) | (*(this) > rhs);
}

bool stringbuilder::operator>=(const char* rhs) const {
  return (*(this) == rhs) | (*(this) > rhs);
}




/* Converts the stringbuilder into some kind of char* or const char* by using
   the appropriate method in the clist container
 */
const char* stringbuilder::to_cstring() const {
  return chars->to_cstring();
}



/* Overloading the assignment operator.

   This includes a test to make sure we're not assigning to ourself.

   Once we know we're not trying to overwrite ourself, the next step is to
   move the current list of characters into a temporary clist. If the program
   hits an exception while allocating memory, this stringbuilder will still have
   its original characters.
 */
stringbuilder& stringbuilder::operator=(const stringbuilder& rhs) {
  if (this == &rhs) {
    return *this;
  }

  clist *old_chars = chars;
  chars = new clist;
  chars->append(rhs.to_cstring());
  delete old_chars;

  return *this;
}



int stringbuilder::length() const {
  return data_length;
}



int stringbuilder::append(const char* to_add) {
  int added = 0;

  added = chars->append(to_add);
  data_length += added;

  return added;
}



stringbuilder& stringbuilder::operator+=(const stringbuilder& rhs) {
  const char* buffer = rhs.to_cstring();
  append(buffer);
  delete[] buffer;

  return *this;
}

stringbuilder& stringbuilder::operator+=(const char* rhs) {
  append(rhs);

  return *this;
}



stringbuilder stringbuilder::operator+(const stringbuilder& rhs) {
  const char* buffer = to_cstring();
  stringbuilder new_string(buffer);

  const char* rhs_buffer = rhs.to_cstring();
  new_string += rhs_buffer;

  delete[] buffer;
  delete[] rhs_buffer;

  return new_string;
}

stringbuilder stringbuilder::operator+(const char* rhs) {
  const char* buffer = to_cstring();
  stringbuilder new_string(buffer);
  new_string += rhs;

  delete[] buffer;
  return new_string;
}



std::ostream& operator<<(std::ostream& out, const stringbuilder& str) {
  const char* buffer= str.to_cstring();

  out << buffer;

  delete[] buffer;

  return out;
}
