#include "jpstring.h"

jpstring::jpstring(int initial_size)
    : capacity(initial_size) {
  char_length = 0;
  chars = new char[initial_size];
}

jpstring::jpstring(const char* chars, int initial_size)
    : capacity(initial_size) {
  char_length = strlen(chars) + 1;
  this->chars = new char[char_length]();

  append(chars);
}

jpstring::jpstring(const jpstring& rhs, int initial_size)
    : capacity(initial_size) {
  char_length = strlen(rhs.chars) + 1;
  chars = new char[char_length]();

  append(chars);
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
  chars = new char[rhs.char_length] + 1;
  capacity = rhs.capacity;
  append(rhs.chars);
  delete[] temp;

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



void jpstring::append(const char* chars) {
  int rhs_length = strlen(chars);
  int minimum_length = char_length + rhs_length;

  if (minimum_length >= capacity) {
    grow_chars(minimum_length);
  }

  strcat(this->chars, chars);
  char_length = minimum_length;
}



char* jpstring::to_cstring() const {
  char* buffer = new char[char_length + 1]();
  strcpy(buffer, chars);

  return buffer;
}

void jpstring::grow_chars(int minimum_length) {
  int growth_factor = (minimum_length / capacity) + 1;

  for (int i = 0; i < growth_factor; ++i) {
    capacity *= 2;
  }

  char* temp = chars;
  chars = new char[capacity];
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



jpstring* jpstring::split(char delimiter) {
  int word_count = 0;
  jpstring* words;
  std::stringstream ss;
  char buffer[BUFFER_SIZE];

  if (char_length == 0) {
    return NULL;
  }

  for (int i = 0; i < char_length; ++i) {
    if (*(chars + i) == delimiter) {
      ++word_count;
    }
  }

  words = new jpstring[word_count + 1];

  ss << chars;

  for (int i = 0; i < word_count; ++i) {
    ss.get(buffer, BUFFER_SIZE, delimiter);
    words[i] = buffer;
  }

  ss.get(buffer, BUFFER_SIZE, '\0');
  words[word_count] = buffer;

  return words;
}
