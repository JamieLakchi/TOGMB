#include "assert.h"
#include "declarations.h"
#include "grammarStorage.h"
#include "parseTreeNode.h"
#include "parser.h"
#include <algorithm>
#include <limits>
#include <string>
#include <utility>

namespace rats {

MemoEntry::MemoEntry(const position next, shared_ptr<ParseTreeNode> tree)
    : _nextpos{next}, _ans{std::move(tree)}, _active{node} {}

MemoEntry::MemoEntry(const position next, shared_ptr<LR> lr)
    : _nextpos{next}, _lr{std::move(lr)}, _active{recursion} {}

MemoEntry::~MemoEntry() {
  _nextpos = 0;
  if (_active == node) {
    _ans = nullptr;
  } else {
    _lr = nullptr;
  }
}

Head::Head(shared_ptr<Pattern> pattern) : _rule(std::move(pattern)) {}

LR::LR(shared_ptr<ParseTreeNode> seed, shared_ptr<Pattern> rule,
       shared_ptr<Head> head, shared_ptr<LR> next)
    : _seed{std::move(seed)}, _rule{std::move(rule)}, _head{std::move(head)},
      _next{std::move(next)} {}

Parser::ParseResult Parser::parse(const string &input) {
  clearMemory();
  _stream = input;

  auto ans = applyRule(_grammar->get(_grammar->getStartId()), 0);

  ParseResult result = {false, ans, _lastPatternStart, _lastFailName};

  if (!ans) {
    return result;
  }

  (void)preen(ans);

  result._success = (_streamPosition >= _stream.size());

  clearMemory();

  return result;
}

void Parser::clearMemory() {
  _stream.clear();
  _streamPosition = 0;
  _memotable.clear();
  _lrstack = nullptr;
  _heads.clear();
  _lastPatternStart = 0;
  _lastFailName.clear();
}

shared_ptr<ParseTreeNode> Parser::applyRule(shared_ptr<Pattern> &pattern,
                                            const position p) {
  //  TAG("applying rule " << pattern->_PId << " at " << p);
  // printAll();
  auto m = recall(pattern, p);
  if (!m) {
    auto lr = create_shared<LR>(nullptr, pattern, nullptr, _lrstack);
    _lrstack = lr;
    m = create_shared<MemoEntry>(p, lr);
    memo(pattern->_PId, p) = m;
    auto ans = pattern->eval(*this);
    _lrstack = _lrstack->_next;
    m->_nextpos = _streamPosition;
    if (lr->_head) {
      lr->_seed = ans;
      return LRAnswer(pattern, p, m);
    } else {
      m->_active = MemoEntry::node;
      m->_ans = ans;
      return ans;
    }
  } else {
    _streamPosition = m->_nextpos;
    if (m->_active == MemoEntry::recursion) {
      setupLR(pattern, m->_lr);
      return m->_lr->_seed;
    } else {
      // TODO: add error logging upon memory retrieval
      return m->_ans;
    }
  }
}

shared_ptr<MemoEntry> &Parser::memo(const patternId id, const position p) {
  pair<patternId, position> key{id, p};
  auto found = _memotable.find(key);

  if (found == _memotable.end()) {
    _memotable[key] = nullptr;
  } else {
    return found->second;
  }

  return _memotable[key];
}

shared_ptr<Head> &Parser::head(const position p) {
  auto found = _heads.find(p);

  if (found == _heads.end()) {
    _heads[p] = nullptr;
  } else {
    return found->second;
  }

  return _heads[p];
}

shared_ptr<MemoEntry> Parser::recall(shared_ptr<Pattern> &pattern,
                                     const position p) {
  // TAG("recalling rule " << pattern->_PId << " at " << p);
  // printAll();
  auto &h = head(_streamPosition);
  auto &m = memo(pattern->_PId, p);
  if (!h) {
    return m;
  }
  if (!m && h->_rule->_PId != pattern->_PId &&
      (h->_involved.find(pattern) == h->_involved.end())) {
    shared_ptr<ParseTreeNode> fail = nullptr;
    return create_shared<MemoEntry>(p, fail);
  }

  auto found = h->_eval.find(pattern);
  if (found != h->_eval.end()) {
    h->_eval.erase(found);
    auto ans = pattern->eval(*this);
    m->_active = MemoEntry::node;
    m->_ans = ans;
    m->_nextpos = _streamPosition;
  }
  return m;
}

void Parser::setupLR(shared_ptr<Pattern> &pattern, shared_ptr<LR> &lr) {
  // TAG("setupLR" << pattern->_PId);
  // printAll();

  if (!lr->_head) {
    lr->_head = create_shared<Head>(pattern);
  }

  auto s = _lrstack;
  while (s->_head != lr->_head) {
    s->_head = lr->_head;
    lr->_head->_involved.insert(s->_rule);
    s = s->_next;
  }
}

shared_ptr<ParseTreeNode> Parser::LRAnswer(shared_ptr<Pattern> &pattern,
                                           const position p,
                                           shared_ptr<MemoEntry> &memory) {
  // TAG("LRAnswer " << pattern->_PId << " at: " << p);
  // printAll();

  auto &h = memory->_lr->_head;
  if (h->_rule != pattern) {
    return memory->_lr->_seed;
  } else {
    memory->_active = MemoEntry::node;
    memory->_ans = memory->_lr->_seed;
    if (memory->_ans) {
      return growLR(pattern, p, memory, h);
    } else {
      return nullptr;
    }
  }
}

shared_ptr<ParseTreeNode> Parser::growLR(shared_ptr<Pattern> &pattern,
                                         const position p,
                                         shared_ptr<MemoEntry> &memory,
                                         shared_ptr<Head> &h) {
  // TAG("growing LR " << pattern->_PId << " pos=" << p);
  // printAll();
  head(p) = h;
  while (true) {
    _streamPosition = p;
    h->_eval = h->_involved;
    auto ans = pattern->eval(*this);
    if (!ans || _streamPosition <= memory->_nextpos) {
      break;
    }
    memory->_ans = ans;
    memory->_nextpos = _streamPosition;
  }
  head(p) = nullptr;
  _streamPosition = memory->_nextpos;
  return memory->_ans;
}

void Parser::setGrammar(unique_ptr<GrammarStorage> &&grammar) {
  _grammar = std::move(grammar);
}

vector<shared_ptr<ParseTreeNode>>
Parser::preen(shared_ptr<ParseTreeNode> &root) {
  vector<shared_ptr<ParseTreeNode>> newChildren;

  for (auto &child : root->_children) {
    auto preened = preen(child);
    newChildren.insert(newChildren.end(), preened.begin(), preened.end());
  }

  if (root->_value.empty()) {
    return newChildren;
  } else {
    root->_children = newChildren;
    return {root};
  }
}

position Parser::updateLastPatternStart(position p) {
  _lastPatternStart = std::max(p, _lastPatternStart);
  return p;
}

void Parser::printStack() {
  auto cur = _lrstack;
  while (cur != nullptr) {
    std::cout << (cur->_head ? std::to_string(cur->_head->_rule->_PId)
                             : "headless")
              << " " << cur->_rule->_PId << " "
              << (cur->_seed ? cur->_seed->_value : "fail") << "; ";
    cur = cur->_next;
  }
  std::cout << "end" << std::endl;
}

void Parser::printMemo() {
  for (auto &elem : _memotable) {
    std::cout << "(" << elem.first.first << ", " << elem.first.second << ") = ";
    if (elem.second) {
      std::cout << elem.second->_nextpos << " ";
      if (elem.second->_active == MemoEntry::node) {
        std::cout << "node ";
        if (elem.second->_ans) {
          elem.second->_ans->print();
        } else {
          std::cout << "failure";
        }
      } else {
        std::cout << "lr ";
        if (elem.second->_lr->_seed) {
          elem.second->_lr->_seed->print();
        } else {
          std::cout << "no seed";
        }
      }
    } else {
      std::cout << "nullptr";
    }
    std::cout << std::endl;
  }
}

void Parser::printHeads() {
  for (auto &elem : _heads) {
    std::cout << elem.first << " ";
    if (elem.second) {
      std::cout << (elem.second->_rule->_PId);
      std::cout << " involved:{ ";
      for (auto &inv : elem.second->_involved) {
        std::cout << inv->_PId << " ";
      }
      std::cout << "} eval:{ ";
      for (auto &inv : elem.second->_eval) {
        std::cout << inv->_PId << " ";
      }
      std::cout << "}";
    } else {
      std::cout << "nullptr";
    }
    std::cout << std::endl;
  }
}

void Parser::printAll() {
  std::cout << "streampos: " << _streamPosition
            << " char: " << _stream[_streamPosition] << std::endl;

  std::cout << "stack: " << std::endl;
  printStack();
  std::cout << "memory: " << std::endl;
  printMemo();
  std::cout << "heads: " << std::endl;
  printHeads();
  std::cout << "--------------------------------" << std::endl;
}

} // namespace rats
