/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include "statement.hpp"


/* Implementation of the Statement class */

int stringToInt(std::string str);

Statement::Statement() = default;

Statement::~Statement() = default;

PRINT::PRINT(TokenScanner &scanner){
 expression = parseExp(scanner);
};
PRINT::~PRINT() {
 delete expression;
}
void PRINT::execute(EvalState &state, Program &program) {
 int value = expression->eval(state);
 std::cout << value << std::endl;
};


LET::LET(TokenScanner &scanner) {
 variable = scanner.nextToken();
 if(variable=="LET"){
  error("SYNTAX ERROR");
 }
 scanner.nextToken();
 expression = parseExp(scanner);
};
LET::~LET() {
 delete expression;
}
void LET::execute(EvalState &state, Program &program) {
 int value = expression->eval(state);
 state.setValue(variable, value);
};


REM::REM(TokenScanner &scanner) {
 while (scanner.hasMoreTokens()) {
  scanner.nextToken();
 }
};
void REM::execute(EvalState &state, Program &program)  {};


INPUT::INPUT (TokenScanner &scanner) {
 variable = scanner.nextToken();
};
void INPUT::execute(EvalState &state, Program &program)  {
 std::string inputValue;
 int Value;

 while(true) {
  bool flag=true;
  std::cout<<" ? ";
  getline(std::cin,inputValue);
  if(!(inputValue[0]=='-'||inputValue[0]<='9'&&inputValue[0]>='0')) {
   flag=false;
  }
  for(int i=1;i<inputValue.size();i++) {
   if(inputValue[i]<'0'||inputValue[i]>'9') {
    std::cout<<"INVALID NUMBER"<<std::endl;
    flag=false;
    break;
   }
  }
if(flag) {
 Value = std::stoi(inputValue);
 state.setValue(variable, Value);
 break;
}
 }
};

END::END(TokenScanner &scanner) {
 while (scanner.hasMoreTokens()) {
  scanner.nextToken();
 }
};
void END::execute(EvalState &state, Program &program)  {
 program.setCurrentLineNumber(-1);
};

GOTO::GOTO(TokenScanner &scanner) {
 std::string lineNumberStr = scanner.nextToken();
 try {
  targetLineNumber = std::stoi(lineNumberStr);
 } catch (...) {
  error("Invalid line number in GOTO statement");
 }
};
void GOTO::execute(EvalState &state, Program &program) {
 if (program.getSourceLine(targetLineNumber) == "") {
  error("LINE NUMBER ERROR");
 }
 program.setCurrentLineNumber(targetLineNumber);
 //Statement* stmt = program.getParsedStatement(targetLineNumber);
 //if (stmt!= nullptr) {
  //stmt->execute(state, program);
 //}
}


IF::IF(TokenScanner &scanner) {
 leftExp = readE(scanner);
 comparisonOperator = scanner.nextToken();
 rightExp = readE(scanner);
 std::string lineNumberStr = scanner.nextToken();
 lineNumberStr = scanner.nextToken();
 try {
  targetLineNumber = std::stoi(lineNumberStr);
 } catch (...) {
  error("LINE NUMBER ERROR");
 }
};
IF::~IF() {
 delete leftExp;
 delete rightExp;
}
void IF::execute(EvalState &state, Program &program) {
 int leftValue = leftExp->eval(state);
 int rightValue = rightExp->eval(state);
 program.setCurrentLineNumber(0);
 bool conditionMet = false;
 if (comparisonOperator == "=") {
  conditionMet = (leftValue == rightValue);
 } else if (comparisonOperator == "<") {
  conditionMet = (leftValue < rightValue);
 } else if (comparisonOperator == ">") {
  conditionMet = (leftValue > rightValue);
 } else {
  error("Invalid comparison operator in IF statement");
 }

 if (conditionMet) {
  if (program.getSourceLine(targetLineNumber) == "") {
   error("Line " + std::to_string(targetLineNumber) + " does not exist in the program");
  }
  program.setCurrentLineNumber(targetLineNumber);
  /*Statement* stmt = program.getParsedStatement(targetLineNumber);
  if (stmt!= nullptr) {
   stmt->execute(state, program);
  }*/
 }
}
//todo
