#include "jpstring.h"

jpstring::jpstring(int initial_size)
    : capacity(initial_size) {
  char_length = 0;
  chars = new char[initial_size];
}

jpstring::jpstring(const jpstring& rhs) {
  char_length = rhs.char_length;
  capacity = rhs.capacity;
  chars = new char[capacity];
  strcpy(chars, rhs.chars);
}

jpstring::jpstring(const char* rhs, int initial_size)
    : capacity(initial_size) {
  char_length = 0;
  this->chars = NULL;

  append(rhs);
}

jpstring::~jpstring() {
  if (chars != NULL) {
    delete[] chars;
  }

  chars = NULL;
}



jpstring::operator char* () {
  return to_cstring();
}

jpstring::operator const char* () {
  return to_cstring();
}



bool jpstring::equals(const char* rhs) const {
  return (strcmp(chars, rhs) == 0);
}

bool jpstring::operator==(const jpstring& rhs) const {
  return (*(this) == rhs.chars);
}

bool jpstring::operator==(const char* rhs) const {
  return equals(rhs);
}

bool jpstring::operator!=(const jpstring& rhs) const {
  return (*(this) != rhs.chars);
}

bool jpstring::operator!=(const char* rhs) const {
  return !equals(rhs);
}

bool jpstring::operator<(const jpstring& rhs) const {
  return (*(this) < rhs.chars);
}

bool jpstring::operator<(const char* rhs) const {
  return (strcmp(chars, rhs) < 0);
}

bool jpstring::operator<=(const jpstring& rhs) const {
  return (*(this) <= rhs.chars);
}

bool jpstring::operator<=(const char* rhs) const {
  return (strcmp(chars, rhs) <= 0);
}

bool jpstring::operator>(const jpstring& rhs) const {
  return (*(this) > rhs.chars);
}

bool jpstring::operator>(const char* rhs) const {
  return (strcmp(chars, rhs) > 0);
}

bool jpstring::operator>=(const jpstring& rhs) const {
  return (*(this) >= rhs.chars);
}

bool jpstring::operator>=(const char* rhs) const {
  return (strcmp(chars, rhs) >= 0);
}



/* Overloading the assignment operator

   The initial check ensures we're not assigning to our self.

   Once we know that we're not assigning to our self, we create another
   pointer to `chars`. If memory allocation fails, we'll still have the
   original characters in this string.
 */
jpstring& jpstring::operator=(const jpstring& rhs) {
  if (this == &rhs) {
    return *this;
  }

  char* temp = chars;
  capacity = rhs.capacity;
  append(rhs.chars);
  delete[] temp;

  return *this;
}



/* Assignment operator overload for const char*


 */
jpstring& jpstring::operator=(const char* rhs) {
  char* temp = chars;
  int len = strlen(rhs) + 1;

  chars = new char[len]();
  append(rhs);

  if (temp) {
    delete[] temp;
    temp = NULL;
  }

  return *this;
}



jpstring& jpstring::operator+=(const jpstring& rhs) {
  return (*(this) += rhs.chars);
}

jpstring& jpstring::operator+=(const char* rhs) {
  append(rhs);

  return *this;
}

jpstring jpstring::operator+(const jpstring& rhs) {
  jpstring new_string(chars);
  new_string += rhs.chars;
  return new_string;
}

jpstring jpstring::operator+(const char* rhs) {
  jpstring new_string(chars);
  new_string += rhs;
  return new_string;
}



void jpstring::append(const char* rhs) {
  int rhs_length = strlen(rhs);
  int minimum_length = char_length + rhs_length;

  if (minimum_length >= capacity) {
    grow_chars(minimum_length);
  }

  if (this->chars) {
    strncat(chars, rhs, rhs_length);
  } else {
    chars = new char[capacity]();
    strncpy(chars, rhs, rhs_length);
  }

  char_length = minimum_length;
}



char* jpstring::to_cstring() const {
  char* buffer = new char[char_length + 1]();
  strcpy(buffer, chars);

  return buffer;
}

void jpstring::grow_chars(int minimum_length) {
  int growth_factor = (minimum_length / capacity);

  for (int i = 0; i < growth_factor; ++i) {
    capacity *= 2;
  }

  char* temp = chars;
  chars = new char[capacity]();

  if (temp) {
    strcpy(chars, temp);
  }

  delete[] temp;
}



int jpstring::length() const {
  return char_length;
}

int jpstring::size() const {
  return capacity;
}



std::ostream& operator<<(std::ostream& out, const jpstring& rhs) {
  out << rhs.chars;
  return out;
}

std::istream& operator>>(std::istream& in, jpstring& rhs) {
  char* buffer = new char[jpstring::BUFFER_SIZE]();

  if (in) {
    while (in >> buffer) {
      rhs += buffer;
      buffer = new char[jpstring::BUFFER_SIZE]();
    }

    delete[] buffer;
  } else {
    in.setstate(std::ios::failbit);
  }

  return in;
}




list<jpstring>* jpstring::split(char delimiter, char eol) {
  list<jpstring>* words = new list<jpstring>;
  int word_count = 0;

  std::stringstream ss;
  char* buffer = new char[BUFFER_SIZE]();

  ss << chars;

  for (int i = 0; i < char_length; ++i) {
    if (*(chars + i) == delimiter) {
      ++word_count;
    }
  }

  for (int i = 0; i < word_count; ++i) {
    ss.get(buffer, BUFFER_SIZE, delimiter);
    ss.ignore(BUFFER_SIZE, delimiter);
    jpstring t(buffer);
    words->append(t);
  }

  ss.get(buffer, BUFFER_SIZE, eol);
  jpstring t(buffer);
  words->append(t);

  delete[] buffer;

  return words;
}
