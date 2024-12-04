/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BASIC interpreter.
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.hpp"
#include "parser.hpp"
#include "program.hpp"
#include "Utils/error.hpp"
#include "Utils/tokenScanner.hpp"
#include "Utils/strlib.hpp"


/* Function prototypes */

void processLine(std::string line, Program &program, EvalState &state);

/* Main program */

int main() {
    EvalState state;
    Program program;
    //cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            std::string input;
            getline(std::cin, input);
            if (input.empty())
                return 0;
            processLine(input, program, state);
        } catch (ErrorException &ex) {
            std::cout << ex.getMessage() << std::endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version of
 * implementation, the program reads a line, parses it as an expression,
 * and then prints the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(std::string line, Program &program, EvalState &state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    if (isdigit(line[0])) {
        int lineNumber = std::stoi(line.substr(0, line.find(' ')));
        scanner.nextToken();
        if(!scanner.hasMoreTokens()) {
            program.removeSourceLine(lineNumber);
        }else {
            scanner.nextToken();
            std::string m=scanner.nextToken();
            if(m=="LET"){
                error("SYNTAX ERROR");
            }
            std::string statementText = line.substr(line.find(' ') + 1);
            program.addSourceLine(lineNumber, statementText);

            /*if (statementText.find("GOTO") == 0) {
                GOTO gotoStmt(scanner);
                program.setParsedStatement(lineNumber, &gotoStmt);
            } else if (statementText.find("PRINT") == 0) {
                PRINT printStmt(scanner);
                program.setParsedStatement(lineNumber, &printStmt);
            } else if (statementText.find("LET") == 0) {
                LET letStmt(scanner);
                program.setParsedStatement(lineNumber, &letStmt);
            } else if (statementText.find("REM") == 0) {
                REM remStmt(scanner);
                program.setParsedStatement(lineNumber, &remStmt);
            } else if (statementText.find("INPUT") == 0) {
                INPUT inputStmt(scanner);
                program.setParsedStatement(lineNumber, &inputStmt);
            } else if (statementText.find("END") == 0) {
                END endStmt(scanner);
                program.setParsedStatement(lineNumber, &endStmt);
            } else if (statementText.find("IF") == 0) {
                IF ifStmt(scanner);
                program.setParsedStatement(lineNumber, &ifStmt);
            } else {
                throw ErrorException("Unrecognized statement starting with a number: " + line);
            }*/
        }
    } else {
        std::string upperLine = scanner.nextToken();
        if (upperLine == "LIST") {
            int firstLineNumber = program.getFirstLineNumber();
            while (firstLineNumber != -1) {
                std::string sourceLine = program.getSourceLine(firstLineNumber);
                std::cout << firstLineNumber << " " << sourceLine << std::endl;
                firstLineNumber = program.getNextLineNumber(firstLineNumber);
            }
        } else if (upperLine == "RUN") {
            int currentLineNumber = program.getFirstLineNumber();
            //int originalLineNumber = currentLineNumber;
            while (currentLineNumber != -1) {
                //Statement *stmt = program.getParsedStatement(currentLineNumber);
                //if (stmt != nullptr) {
                //    stmt->execute(state, program);
                //}
                std::string line = program.getSourceLine(currentLineNumber);
                int originalLineNumber = currentLineNumber;
                TokenScanner scanner;
                scanner.ignoreWhitespace();
                scanner.scanNumbers();
                scanner.setInput(line);
                std::string s=scanner.nextToken();
                //scanner.nextToken();
                if (s == "GOTO") {
                    GOTO gotoStmt(scanner);
                    gotoStmt.execute( state, program);
                    if(program.getCurrentLineNumber() > 0) {
                        currentLineNumber= program.getCurrentLineNumber();
                    }
                } else if (s == "PRINT") {
                    PRINT printStmt(scanner);
                    printStmt.execute( state, program);
                } else if (s == "LET") {
                    LET letStmt(scanner);
                    letStmt.execute( state, program);
                } else if (s == "REM") {
                    REM remStmt(scanner);
                    remStmt.execute( state, program);
                } else if (s == "INPUT") {
                    INPUT inputStmt(scanner);
                    inputStmt.execute( state, program);
                    scanner.nextToken();
                } else if (s == "END") {
                    END endStmt(scanner);
                    endStmt.execute( state, program);
                    currentLineNumber= program.getCurrentLineNumber();
                } else if (s == "IF") {
                    IF ifStmt(scanner);
                    ifStmt.execute( state, program);
                    if(program.getCurrentLineNumber() > 0) {
                        currentLineNumber= program.getCurrentLineNumber();
                    }
                } else {
                    throw ErrorException("Unrecognized statement starting with a number: " + line);
                }
                if(originalLineNumber == currentLineNumber) {
                    currentLineNumber = program.getNextLineNumber(currentLineNumber);
                }
            }
        } else if (upperLine == "QUIT") {
            std::exit(0);
        } else if (upperLine == "CLEAR") {
            program.clear();
            state.Clear();
        } else if (upperLine == "HELP") {
            std::cout << "This is a simple BASIC interpreter." << std::endl;
            std::cout << "Available commands are:" << std::endl;
            std::cout << " - LIST: Displays all the program lines." << std::endl;
            std::cout << " - RUN: Executes the program from the beginning." << std::endl;
            std::cout << " - CLEAR: Deletes all program and variables." << std::endl;
            std::cout << " - HELP: Displays this help message." << std::endl;
            std::cout << " - QUIT: Exits the interpreter." << std::endl;
            std::cout << "Program lines start with a line number followed by a BASIC statement (e.g., 10 PRINT 1)." <<
                    std::endl;
        } else {
            TokenScanner scannerForStmt;
            scannerForStmt.ignoreWhitespace();
            scannerForStmt.scanNumbers();
            scannerForStmt.setInput(line);
            scannerForStmt.nextToken();

            if (upperLine == "REM") {
                REM remStmt(scannerForStmt);
                remStmt.execute(state, program);
            } else if (upperLine == "INPUT") {
                INPUT inputStmt(scannerForStmt);
                inputStmt.execute(state, program);
            } else if (upperLine == "END") {
                END endStmt(scannerForStmt);
                endStmt.execute(state, program);
            } else if (upperLine == "GOTO") {
                GOTO gotoStmt(scannerForStmt);
                gotoStmt.execute(state, program);
            } else if (upperLine == "IF") {
                IF ifStmt(scannerForStmt);
                ifStmt.execute(state, program);
            } else if (upperLine == "PRINT") {
                PRINT printStmt(scannerForStmt);
                printStmt.execute(state, program);
            } else if (upperLine == "LET") {
                LET letStmt(scanner);
                letStmt.execute(state, program);
            } else {
                throw ErrorException("Invalid BASIC command: " + line);
            }
        }
    }
    //todo
}
