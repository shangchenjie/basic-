/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include "program.hpp"



Program::Program() = default;

Program::~Program() = default;

void Program::clear() {
    sourceLines.clear();
   /* for (auto& pair : parsedStatements) {
        if (pair.second!= nullptr) {
            delete pair.second;
        }
    }
    parsedStatements.clear();*/
    // Replace this stub with your own code
    //todo
}

void Program::addSourceLine(int lineNumber, const std::string &line) {
    if (sourceLines.find(lineNumber)!= sourceLines.end()) {
        sourceLines[lineNumber] = line;
       /* if (parsedStatements.find(lineNumber)!= parsedStatements.end()) {
            if (parsedStatements[lineNumber]!= nullptr) {
                delete parsedStatements[lineNumber];
            }
            parsedStatements.erase(lineNumber);
        }*/
    } else {
        sourceLines[lineNumber] = line;
    }
    // Replace this stub with your own code
    //todo
}

void Program::removeSourceLine(int lineNumber) {
    sourceLines.erase(lineNumber);
   /* if (parsedStatements.find(lineNumber)!= parsedStatements.end()) {
        if (parsedStatements[lineNumber]!= nullptr) {
            delete parsedStatements[lineNumber];
        }
        parsedStatements.erase(lineNumber);
    }*/
    // Replace this stub with your own code
    //todo
}

std::string Program::getSourceLine(int lineNumber) {
    if (sourceLines.find(lineNumber)!= sourceLines.end()) {
        return sourceLines[lineNumber];
    }
    return "";
    // Replace this stub with your own code
    //todo
}
/*
void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    if (sourceLines.find(lineNumber) == sourceLines.end()) {
        throw std::runtime_error("error");
    }
    if (parsedStatements.find(lineNumber)!= parsedStatements.end()) {
        if (parsedStatements[lineNumber]!= nullptr) {
            delete parsedStatements[lineNumber];
        }
    }
    parsedStatements[lineNumber] = stmt;
    // Replace this stub with your own code
    //todo
}

//void Program::removeSourceLine(int lineNumber) {



Statement *Program::getParsedStatement(int lineNumber) {
    if (parsedStatements.find(lineNumber)!= parsedStatements.end()) {
        return parsedStatements[lineNumber];
    }
    return nullptr;
   // Replace this stub with your own code
   //todo
}*/

int Program::getFirstLineNumber() {
    if (sourceLines.empty()) {
        return -1;
    }

    int firstLineNumber = -1;
    for (const auto& pair : sourceLines) {
        if (firstLineNumber == -1 || pair.first < firstLineNumber) {
            firstLineNumber = pair.first;
        }
    }

    return firstLineNumber;
    // Replace this stub with your own code
    //todo
}

int Program::getNextLineNumber(int lineNumber){

    bool foundNext = false;
    int nextLineNumber = -1;
    for (const auto& pair : sourceLines) {
        if (foundNext && pair.first>lineNumber &&pair.first<nextLineNumber) {
            nextLineNumber = pair.first;
        }
        if (pair.first > lineNumber&&!foundNext) {
            nextLineNumber = pair.first;
            foundNext = true;
        }
    }

    return nextLineNumber;
    // Replace this stub with your own code
    //todo
}
int Program::getCurrentLineNumber() const {
    return currentLineNumber;
}

void Program::setCurrentLineNumber(int lineNumber) {
    currentLineNumber = lineNumber;
}
//more func to add
//todo


