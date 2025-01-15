#ifndef INC_RATS_DECLARATIONS
#define INC_RATS_DECLARATIONS

#include <cstddef>
#include <functional>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace rats {

using string = std::string;
using position = std::size_t;
using patternId = unsigned short;
using variableId = unsigned short;

template <typename T> using vector = std::vector<T>;
template <typename T> using set = std::set<T>;
template <typename T, typename U> using pair = std::pair<T, U>;
template <typename T> using shared_ptr = std::shared_ptr<T>;
template <typename T> using unique_ptr = std::unique_ptr<T>;
template <typename T, typename U, typename H = std::hash<T>>
using hashmap = std::unordered_map<T, U, H>;

template <typename T, typename... ARGS>
shared_ptr<T> create_shared(ARGS &&...args) {
  return shared_ptr<T>{new T(std::forward<ARGS>(args)...)};
}

template <typename T, typename... ARGS>
unique_ptr<T> create_unique(ARGS &&...args) {
  return unique_ptr<T>{new T(std::forward<ARGS>(args)...)};
}

class Parser;
class GrammarStorage;

struct ParseTreeNode;

struct Pattern;
struct LiteralPattern;
struct VariablePattern;
struct SequencePattern;
struct RankedChoicePattern;
struct RepeaterPattern;
struct NamedPattern;
struct NumberPattern;
struct VarNamePattern;

} // namespace rats

#endif
