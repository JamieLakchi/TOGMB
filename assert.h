#ifndef INC_ASSERT_H
#define INC_ASSERT_H

#include <iostream>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifndef NDEBUG
#define ASSERT(condition, message)                                             \
  do {                                                                         \
    if (!(condition)) {                                                        \
      std::cerr << "\nAssertion failed at " << __FILE__ << ": line "           \
                << __LINE__ << "\n"                                            \
                << "Condition: (" << TOSTRING(condition) << ")\n"              \
                << "Message: \"" << message << "\"\n\n";                       \
      std::abort();                                                            \
    }                                                                          \
  } while (false)
#else
#define ASSERT(condition, message)
#endif

#define ERR_CREATE(name, _what)                                                \
  class name : public std::exception {                                         \
  public:                                                                      \
    const char *what() const throw() { return _what; };                        \
  };

#define ERR_IF(condition, error)                                               \
  if (condition) {                                                             \
    throw error{};                                                             \
  }

#define DUMPVAR(_var) std::cout << #_var << ": " << _var << std::endl

#define TAG(tag) std::cout << tag << std::endl

#endif
