/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface, which is an excellent model for
 * the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include <string>
#include <sstream>
#include "evalstate.hpp"
#include "exp.hpp"
#include "Utils/tokenScanner.hpp"
#include "program.hpp"
#include "parser.hpp"
#include "Utils/error.hpp"
#include "Utils/strlib.hpp"

class Program;

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

    Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

    virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

    virtual void execute(EvalState &state, Program &program) = 0;

};


/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */
class PRINT : public Statement {
private:
 Expression *expression;

public:
 PRINT(TokenScanner &scanner) ;
  //expression = parseExp(scanner);

  ~PRINT() ;
  //delete expression;
 void execute(EvalState &state, Program &program) override ;
  //int value = expression->eval(state);
  //std::cout << value << std::endl;
};




class LET: public Statement {
private:
 std::string variable;
 Expression *expression;

public:
 LET(TokenScanner &scanner);
  /*variable = scanner.nextToken();
  scanner.nextToken();
  expression = parseExp(scanner);
 }*/

 virtual ~LET() ;
  //delete expression;
 //}
  void execute(EvalState &state, Program &program) override;
  //int value = expression->eval(state);
  //state.setValue(variable, value);
 //}
};




class REM : public Statement {
public:
    REM(TokenScanner &scanner) ;
        //while (scanner.hasMoreTokens()) {
        //    scanner.nextToken();
      //  }
    //}
    void execute(EvalState &state, Program &program)  override;
};



class INPUT : public Statement {
private:
 std::string variable;

public:
 // 构造函数
 INPUT(TokenScanner &scanner) ;
  //variable = scanner.nextToken();
 //}
  void execute(EvalState &state, Program &program) override ;
  //int inputValue;
 // std::cin >> inputValue;
  //state.setValue(variable, inputValue);
 //}
};


class END : public Statement {
public:
 END(TokenScanner &scanner) ;
  //while (scanner.hasMoreTokens()) {
   //scanner.nextToken();
 // }

 void execute(EvalState &state, Program &program) override ;
  //std::exit(0);
 //}
};


class GOTO : public Statement {
private:
 int targetLineNumber;

public:
 // 构造函数，从TokenScanner解析出目标行号
 GOTO(TokenScanner &scanner) ;
 /* std::string lineNumberStr = scanner.nextToken();
  try {
   targetLineNumber = std::stoi(lineNumberStr);
  } catch (...) {
   error("Invalid line number in GOTO statement");
  }
 }*/

  void execute(EvalState &state, Program &program)  override;
  /*if (program.getSourceLine(targetLineNumber) == "") {
   error("Line " + std::to_string(targetLineNumber) + " does not exist in the program");
  }
  program.setCurrentLineNumber(targetLineNumber);
 }*/
};


class IF : public Statement {
private:
 Expression *leftExp;
 std::string comparisonOperator;
 Expression *rightExp;
 int targetLineNumber;

public:
 // 构造函数，从TokenScanner解析出IF语句的各个部分
 IF(TokenScanner &scanner) ;
  /*leftExp = parseExp(scanner);
  comparisonOperator = scanner.nextToken();
  rightExp = parseExp(scanner);
  std::string lineNumberStr = scanner.nextToken();
  lineNumberStr = scanner.nextToken();
  try {
   targetLineNumber = std::stoi(lineNumberStr);
  } catch (...) {
   error("Invalid line number in IF statement");
  }
 }*/

 virtual ~IF() ;
 //delete leftExp;
 //delete rightExp;
 //}

 void execute(EvalState &state, Program &program) override ;
 /*int leftValue = leftExp->eval(state);
 int rightValue = rightExp->eval(state);

 bool conditionMet = false;
 if (comparisonOperator == "=") {
  conditionMet = (leftValue == rightValue);
 } else if (comparisonOperator == "<") {
  conditionMet = (leftValue < rightValue);
 } else if (comparisonOperator == ">") {
  conditionMet = (leftValue > rightValue);
 } else if (comparisonOperator == "<=") {
  conditionMet = (leftValue <= rightValue);
 } else if (comparisonOperator == ">=") {
  conditionMet = (leftValue >= rightValue);
 } else {
  error("Invalid comparison operator in IF statement");
 }

 if (conditionMet) {
  if (program.getSourceLine(targetLineNumber) == "") {
   error("Line " + std::to_string(targetLineNumber) + " does not exist in the program");
  }
  program.setCurrentLineNumber(targetLineNumber);
 }
}
};*/
};
#endif
