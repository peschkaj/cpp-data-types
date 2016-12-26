/* Jeremiah Peschka
   <jpeschka@pdx.edu>

   Implements a string-like class with convenient functions for working
   with strings of characters, rather than using char arrays.

   Strings are initialized with a capacity. When a string is about to
   grow beyond its initial capacity, the capacity is double. While
   large capacities waste memory, they prevent potentially expensive
   growth and reallocation. Conversely, small capacities save memory
   but cause additional re-allocations as the string grows.

   **N.B.** Throughout the documentation for this class, `string` is
   substituted for `jpstring` for two reasons.
   1) it's easier to type
   2) it doesn't upset the spellchecker in emacs
*/

#include "jpstring.h"

/* Creates a jpstring using.

   `initial_size` sets the value of `capacity`.
   `chars` is initialized with a size of `capacity`
 */
jpstring::jpstring(int initial_size)
    : capacity(initial_size) {
  char_length = 0;
  chars = new char[capacity];
}



/* Copies another jpstring into this one.

   This string's `char_length` and `capacity` are set with values from rhs.
   `chars` is initialized using `capacity` and then the contents of rhs
   are copied into this string using `strncpy` to perform a secure,
   length-bounded copy that zeroes out trailing bytes in `chars.`
 */
jpstring::jpstring(const jpstring& rhs) {
  char_length = rhs.char_length;
  capacity = rhs.capacity;
  chars = new char[capacity];
  strncpy(chars, rhs.chars, capacity);
}



/* Creates an initialized string from the contents of rhs.

   This string's capacity is set to `initial_size`.

   The new characters are added to this string using the `append` method.
 */
jpstring::jpstring(const char* rhs, int initial_size)
    : capacity(initial_size) {
  char_length = 0;
  this->chars = NULL;

  append(rhs);
}



/* Destroys this string and all managed resources */
jpstring::~jpstring() {
  if (chars != NULL) {
    delete[] chars;
  }

  chars = NULL;
}



/* Converts this string to a `char*` */
jpstring::operator char* () {
  return to_cstring();
}

/* Converts this string to a `const char*` */
jpstring::operator const char* () {
  return to_cstring();
}



/* Compares this string to rhs, returns true if they are equal,
   false otherwise.
 */
bool jpstring::equals(const char* rhs) const {
  return (strcmp(chars, rhs) == 0);
}



/* Compares this string to rhs, returns true if they are equal,
   false otherwise.
*/
bool jpstring::operator==(const jpstring& rhs) const {
  return (*(this) == rhs.chars);
}



/* Compares this string to rhs, returns true if they are equal,
   false otherwise.
*/
bool jpstring::operator==(const char* rhs) const {
  return equals(rhs);
}



/* Compares this string to rhs.

   Returns true if they are not equal, false otherwise.
*/
bool jpstring::operator!=(const jpstring& rhs) const {
  return (*(this) != rhs.chars);
}



/* Compares this string to rhs.

   Returns true if they are not equal, false otherwise.
*/
bool jpstring::operator!=(const char* rhs) const {
  return !equals(rhs);
}



/* Less than operator overload.

   Returns true if this string is less than rhs, false otherwise.

   Internally, this uses `strcmp` to determine if this string is less
   than rhs.
 */
bool jpstring::operator<(const jpstring& rhs) const {
  return (*(this) < rhs.chars);
}



/* Less than operator overload.

   Returns true if this string is less than rhs, false otherwise.

   Internally, this uses `strcmp` to determine if this string is less
   than rhs.
 */
bool jpstring::operator<(const char* rhs) const {
  return (strcmp(chars, rhs) < 0);
}



/* Less than or equal operator overload.

   Returns true if this string is less than or equal to rhs.
   Returns false otherwise.

   Internally, this uses `strcmp` to determine if this string is less
   than rhs.
 */
bool jpstring::operator<=(const jpstring& rhs) const {
  return (*(this) <= rhs.chars);
}



/* Less than or equal operator overload.

   Returns true if this string is less than or equal to rhs.
   Returns false otherwise.

   Internally, this uses `strcmp` to determine if this string is less
   than rhs.
*/
bool jpstring::operator<=(const char* rhs) const {
  return (strcmp(chars, rhs) <= 0);
}



/* Greater than operator overload.

   Returns true if this string is greater than rhs.
   Returns false otherwise.

   Internally, this uses `strcmp` to determine if this string is greater
   than rhs.
*/
bool jpstring::operator>(const jpstring& rhs) const {
  return (*(this) > rhs.chars);
}



/* Greater than operator overload.

   Returns true if this string is greater than rhs.
   Returns false otherwise.

   Internally, this uses `strcmp` to determine if this string is greater
   than rhs.
*/
bool jpstring::operator>(const char* rhs) const {
  return (strcmp(chars, rhs) > 0);
}



/* Greater than or equal to operator overload.

   Returns true if this string is greater than or equal to rhs.
   Returns false otherwise.

   Internally, this uses `strcmp` to determine if this string is greater
   than or equal to rhs.
*/
bool jpstring::operator>=(const jpstring& rhs) const {
  return (*(this) >= rhs.chars);
}



/* Greater than or equal to operator overload.

   Returns true if this string is greater than or equal to rhs.
   Returns false otherwise.

   Internally, this uses `strcmp` to determine if this string is greater
   than or equal to rhs.
*/
bool jpstring::operator>=(const char* rhs) const {
  return (strcmp(chars, rhs) >= 0);
}



/* Overloading the assignment operator

   The initial check ensures we're not assigning to our self.

   Once we know we're not assigning to our self, operator=(const char*)
   is for assignment.
 */
jpstring& jpstring::operator=(const jpstring& rhs) {
  if (this == &rhs) {
    return *this;
  }

  *this = rhs.chars;

  return *this;
}



/* Assignment operator overload for const char*

   Creates a temporary pointer to hold `chars`. If the memory allocation
   for the new `chars` fails, we still have the original characters in the
   string.
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



/* Overloads the += operator.

   Appends `rhs` to this string.

   If this string is too short, the capacity is expanded by doubling it
   until it's large enough to accommodate both this string and rhs.
 */
jpstring& jpstring::operator+=(const jpstring& rhs) {
  return (*(this) += rhs.chars);
}



/* Overloads the += operator.

   Appends `rhs` to this string.

   If this string is too short, the capacity is expanded by doubling it
   until it's large enough to accommodate both this string and rhs.
*/
jpstring& jpstring::operator+=(const char* rhs) {
  append(rhs);

  return *this;
}



/* Adds this string to rhs and returns a new string. */
jpstring jpstring::operator+(const jpstring& rhs) {
  jpstring new_string(chars);
  new_string += rhs.chars;
  return new_string;
}



/* Adds this string to rhs and returns a new string. */
jpstring jpstring::operator+(const char* rhs) {
  jpstring new_string(chars);
  new_string += rhs;
  return new_string;
}



/* Appends rhs to this string.

   If this string's capacity is too small to contain the new string,
   the capacity is repeatedly doubled until it is large enough to hold
   both this string and rhs.

   Once the capacity is large enough, `strncat` is used to concatenate
   rhs and this string. `strncat` is used to prevent buffer overruns
   and to ensure that the resulting new string is always null terminated.
 */
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



/* Creates a C style string (char array) from this string.

   `chars` is copied into a new buffer and a pointer to the buffer is
   returned to the caller.

   The returned string will be sized to char_length + 1 and `strncpy`
   will ensure that the buffer is null terminated.
 */
char* jpstring::to_cstring() const {
  char* buffer = new char[char_length + 1]();
  strncpy(buffer, chars, char_length + 1);

  return buffer;
}



/* Grows the internal character array.

   The capacity will be doubled until it is larger than the desired
   string. Once the capacity is at the right size, a temporary pointer
   to `chars` is created. `chars` is initialized to the new size
   (capacity) and then strncpy is used to place the contents back in
   `chars`. This pattern is used to stop a failure to allocate memory
   from destroying the contents of this string.
 */
void jpstring::grow_chars(int minimum_length) {
  int growth_factor = (minimum_length / capacity);

  for (int i = 0; i < growth_factor; ++i) {
    capacity *= 2;
  }

  char* temp = chars;
  chars = new char[capacity]();

  if (temp) {
    strncpy(chars, temp, capacity);
  }

  delete[] temp;
}



/* Returns the length of this string.

   This is tracked through all assignment operations.
 */
int jpstring::length() const {
  return char_length;
}



/* Returns this string's capacity.

   Capacity only changes when an operation would grow this string to be
   larger than the current capacity. This value can only be set during
   initialization and inside `grow_chars`.
 */
int jpstring::size() const {
  return capacity;
}



/* Provides an overload for the ostream operator << */
std::ostream& operator<<(std::ostream& out, const jpstring& rhs) {
  out << rhs.chars;
  return out;
}



/* Provides an overload for the istream operator >>

   This uses the += operator overload internally, and only data types
   supported by += can be streamed into this string.
 */
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



/* Splits this string on the delimiter (space by default) until the end
   of line character (`eol` defaults to '\0') is reached.

   Characters are read in using using a buffer that is `BUFFER_SIZE`
   characters long. `BUFFER_SIZE` is set to 140 characters at compile
   time. This should be sufficient for the vast majority of use cases.

   A stringstream is used to stream characters out of `chars` and into
   the buffer.
 */
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
