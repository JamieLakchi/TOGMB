#ifndef INC_RATS_PARSER
#define INC_RATS_PARSER

#include "assert.h"
#include "declarations.h"

namespace rats {

struct Head {
  Head(shared_ptr<Pattern> pattern);

  shared_ptr<Pattern> _rule;
  set<shared_ptr<Pattern>> _involved;
  set<shared_ptr<Pattern>> _eval;
};

struct LR {
  LR(shared_ptr<ParseTreeNode> seed, shared_ptr<Pattern> rule,
     shared_ptr<Head> head, shared_ptr<LR> next);

  shared_ptr<ParseTreeNode> _seed;
  shared_ptr<Pattern> _rule;
  shared_ptr<Head> _head;
  shared_ptr<LR> _next;
};

struct MemoEntry {
  enum ActiveMemberType { node, recursion };

  MemoEntry(const position next, shared_ptr<ParseTreeNode> tree);
  MemoEntry(const position next, shared_ptr<LR> lr);
  ~MemoEntry();

  position _nextpos;
  ActiveMemberType _active;
  union {
    shared_ptr<ParseTreeNode> _ans;
    shared_ptr<LR> _lr;
  };
};

ERR_CREATE(NoPatternMatcherDefined,
           "No pattern matching function has been defined in the parser.");

class Parser {
public:
  void setGrammar(unique_ptr<GrammarStorage> &&grammar);

  struct ParseResult {
    bool _success = false;
    shared_ptr<ParseTreeNode> _ans = nullptr;
    position _lastPatternStart = 0;
    vector<string> _lastFailName;
  };

  ParseResult parse(const string &input);

  void clearMemory();

  /**
   * The match functions implement a visitor pattern for Pattern derivatives.
   * A nullptr means a match has failed
   */
  // will throw an error
  shared_ptr<ParseTreeNode> match(Pattern &pattern);
#define MATCH(patternname) shared_ptr<ParseTreeNode> match(patternname &pattern)
  // visitor method implementations
  MATCH(LiteralPattern);
  MATCH(VariablePattern);
  MATCH(SequencePattern);
  MATCH(RankedChoicePattern);
  MATCH(NumberPattern);
  MATCH(RepeaterPattern);
  MATCH(NamedPattern);
  MATCH(VarNamePattern);

private:
  string _stream;
  position _streamPosition;
  unique_ptr<GrammarStorage> _grammar;

  shared_ptr<ParseTreeNode> applyRule(shared_ptr<Pattern> &pattern, position p);

  shared_ptr<MemoEntry> &memo(const patternId id, const position p);
  shared_ptr<Head> &head(const position p);

  shared_ptr<MemoEntry> recall(shared_ptr<Pattern> &pattern, const position p);

  void setupLR(shared_ptr<Pattern> &pattern, shared_ptr<LR> &lr);

  shared_ptr<ParseTreeNode> LRAnswer(shared_ptr<Pattern> &pattern,
                                     const position p,
                                     shared_ptr<MemoEntry> &memory);

  shared_ptr<ParseTreeNode> growLR(shared_ptr<Pattern> &pattern,
                                   const position p,
                                   shared_ptr<MemoEntry> &memory,
                                   shared_ptr<Head> &head);

  class MemoHash {
  public:
    size_t operator()(const pair<patternId, position> &p) const {
      return (p.first << sizeof(patternId)) ^ p.second;
    }
  };

  hashmap<pair<patternId, position>, shared_ptr<MemoEntry>, MemoHash>
      _memotable;

  shared_ptr<LR> _lrstack = nullptr;
  hashmap<position, shared_ptr<Head>> _heads;

  // error
  position updateLastPatternStart(position p);
  position _lastPatternStart = 0;
  vector<string> _lastFailName;
  patternId _lastFailId = 0;

  // cleanup
  vector<shared_ptr<ParseTreeNode>> preen(shared_ptr<ParseTreeNode> &root);

  // logging
  void printStack();
  void printMemo();
  void printHeads();
  void printAll();
};

} // namespace rats

#endif
