
// Generated from Expr.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  ExprLexer : public antlr4::Lexer {
public:
  enum {
    WS = 1, INT = 2, ADD = 3, SUB = 4, MUL = 5, DIV = 6, LPAREN = 7, RPAREN = 8
  };

  explicit ExprLexer(antlr4::CharStream *input);

  ~ExprLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

