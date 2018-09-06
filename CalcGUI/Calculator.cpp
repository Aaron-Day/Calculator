/**
  * @brief Assignment 9 Part A
  * @author Aaron Day
  */

#include "Calculator.h"
#include <stdexcept>
#include <cmath>

using namespace std;

Calculator::Calculator() {
    num1 = 0;
    num2 = 0;
    memory = 0;
    oper = NONE;
    equal = false;
    opLock = false;
}

void Calculator::store(double value) {
    num2 = value;
    if(equal) { num1 = 0; }
    opLock = false;
}

double Calculator::handleOperation(Calculator::opType newOperation) {
    //Process newOperation if it is an immediate operation ( √ % 1/x ± )
    if(newOperation > 3 && newOperation < 8) {
        switch(newOperation) {
        case SQRT:
            //throw a runtime error if trying to √ a negative number
            if(num2 < 0) { throw runtime_error("NEG √ ERROR"); }
            num2 = sqrt(num2);
            //if no other operations are stored, then store this one
            if(oper == NONE || equal) { oper = SQRT; }
            break;
        case PERCENT:
            //if SQRT is the current operation, change it to NONE
            if(oper == SQRT) { oper = NONE; }
            num2 = num2 / 100;
            //if there is a value in num1 return the percentage of that value
            if(abs(num1) > EPSILON) { num2 = num1 * num2; }
            break;
        case INVERSE:
            //if SQRT is the current operation, change it to NONE
            if(oper == SQRT) { oper = NONE; }
            if(abs(num2) < EPSILON) { throw runtime_error("DIV 0 ERROR"); }
            num2 = 1 / num2;
            break;
        case SIGN:
            //if SQRT is the current operation, change it to NONE
            if(oper == SQRT) { oper = NONE; }
            num2 = -num2;
            break;
        }
        return num2;
    } else { //newOperation is not an immediate operation
        //if equal was just processed, unlock operations
        if(equal) { opLock = false; }
        if(!opLock) {
            switch(oper) {
            case ADD:
                num1 += num2; break;
            case SUBTRACT:
                num1 -= num2; break;
            case MULTIPLY:
                num1 *= num2; break;
            case DIVIDE:
                //throw a runtime error if trying to divide by 0
                if(abs(num2) < EPSILON) { throw runtime_error("DIV 0 ERROR"); }
                num1 /= num2; break;
            case SQRT:
            case NONE:
                num1 = num2;
            }
        }
        oper = newOperation;
        opLock = true;
        return num1;
    }
}

void Calculator::setOpLock(bool lock) {
    opLock = lock;
}

double Calculator::equalsPressed() {
    equal = true;
    return handleOperation(oper);
}

void Calculator::setEqual(bool newEqual) {
    equal = newEqual;
}

void Calculator::clear() {
    num1 = 0;
    num2 = 0;
    oper = NONE;
    equal = false;
    opLock = false;
}

void Calculator::clearMem() {
    memory = 0;
}

double Calculator::recallMem() {
    return memory;
}

void Calculator::storeMem(double value) {
    memory = value;
}

void Calculator::handleMem(opType memOper, double value) {
    switch(memOper) {
    case ADD:
        memory += value; break;
    case SUBTRACT:
        memory -= value;
    }
}

void Calculator::setOper(opType newOperaton) {
    oper = newOperaton;
}

Calculator::opType Calculator::getOper() const {
    return oper;
}
