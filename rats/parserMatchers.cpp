#include "declarations.h"
#include "grammarStorage.h"
#include "parseTreeNode.h"
#include "parser.h"
#include "ratterns/ratterns.h"
#include <utility>

namespace rats {
shared_ptr<ParseTreeNode> Parser::match(Pattern &pattern) {
  ERR_IF(true, NoPatternMatcherDefined);
}

shared_ptr<ParseTreeNode> Parser::match(LiteralPattern &pattern) {
  // TAG("matching " << pattern._PId << " at " << _streamPosition);
  if (pattern._literal.size() > (_stream.size() - _streamPosition)) {
    return nullptr;
  }

  for (position i = 0; i < pattern._literal.size(); ++i) {
    if (_stream[i + _streamPosition] != pattern._literal[i]) {
      return nullptr;
    }
  }

  _streamPosition += pattern._literal.size();

  return create_shared<ParseTreeNode>(pattern._literal);
}

shared_ptr<ParseTreeNode> Parser::match(VariablePattern &pattern) {
  //  TAG("matching " << pattern._PId);
  auto restorepos = _streamPosition;
  auto ans = applyRule(_grammar->get(pattern._varId), _streamPosition);
  if (ans) {
    return ans;
  }
  _streamPosition = restorepos;
  return nullptr;
}

shared_ptr<ParseTreeNode> Parser::match(SequencePattern &pattern) {
  // TAG("matching " << pattern._PId);
  auto restorepos = _streamPosition;
  auto ans = create_shared<ParseTreeNode>();

  for (auto &elem : pattern._patterns) {
    auto child = applyRule(elem, _streamPosition);
    if (child) {
      ans->_children.push_back(std::move(child));
    } else {
      _streamPosition = restorepos;
      return nullptr;
    }
  }

  return ans;
}

shared_ptr<ParseTreeNode> Parser::match(RankedChoicePattern &pattern) {
  // TAG("matching " << pattern._PId);
  auto restorepos = _streamPosition;
  for (auto &elem : pattern._patterns) {
    auto child = applyRule(elem, _streamPosition);
    if (child) {
      auto ans = create_shared<ParseTreeNode>();
      ans->_children.push_back(child);
      return ans;
    }
    _streamPosition = restorepos;
  }

  return nullptr;
}

shared_ptr<ParseTreeNode> Parser::match(NumberPattern &pattern) {
  // TAG("matching " << pattern._PId);
  auto originalPosition = _streamPosition;
  auto nrDigits = [&]() {
    size_t i = 0;
    for (; (i + _streamPosition) < _stream.size(); ++i) {
      char c = _stream[i + _streamPosition];
      if (!('0' <= c && c <= '9')) {
        break;
      }
    }
    return i;
  };

  _streamPosition += nrDigits();

  if (_streamPosition < _stream.size()) {
    if (_stream[_streamPosition] == '.') {
      ++_streamPosition;
      _streamPosition += nrDigits();
    }
  }

  if (_streamPosition == originalPosition) {
    return nullptr;
  }

  return create_shared<ParseTreeNode>(
      _stream.substr(originalPosition, _streamPosition - originalPosition));
}

shared_ptr<ParseTreeNode> Parser::match(RepeaterPattern &pattern) {
  // TAG("matching " << pattern._PId);
  auto attempt = create_shared<ParseTreeNode>();

  auto restorepos = _streamPosition;

  size_t nrOfMatches = 0;

  for (; nrOfMatches < pattern._min; ++nrOfMatches) {
    auto ans = applyRule(pattern._pattern, _streamPosition);
    if (ans) {
      attempt->_children.push_back(std::move(ans));
    } else {
      _streamPosition = restorepos;
      return nullptr;
    }
  }

  auto max = (pattern._max == Reps::INF ? (unsigned long)-1 : pattern._max);

  while (nrOfMatches < max) {
    restorepos = _streamPosition;
    auto ans = applyRule(pattern._pattern, _streamPosition);
    if (ans && _streamPosition != restorepos) {
      attempt->_children.push_back(std::move(ans));
    } else {
      _streamPosition = restorepos;
      break;
    }
  }

  return attempt;
}

shared_ptr<ParseTreeNode> Parser::match(NamedPattern &pattern) {
  // TAG("matching " << pattern._PId);
  auto restorepos = _streamPosition;

  auto child = applyRule(pattern._pattern, _streamPosition);

  if (child) {
    auto ans = create_shared<ParseTreeNode>(pattern._name);
    ans->_children.push_back(std::move(child));
    return ans;
  }

  _streamPosition = restorepos;
  return nullptr;
}
} // namespace rats
