/**
  * @brief Assignment 9 Part A
  * @author Aaron Day
  */

#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
public:
    /**
     * @brief Calculator Default calculator constructor
     */
    Calculator();

    /**
     * @brief The opType enum Enumerated values for operation types
     */
    enum opType { ADD, SUBTRACT, MULTIPLY, DIVIDE, SQRT, PERCENT, INVERSE, SIGN, NONE };

    /**
     * @brief EPSILON Close enough to 0 to equal 0
     */
    const double EPSILON = 0.0000001;

    /**
     * @brief setOper Sets oper to a new operator
     * @param newOperator New operaton
     */
    void setOper(opType newOperaton);

    /**
     * @brief getOper Return the current oper
     * @return oper
     */
    opType getOper() const;

    /**
     * @brief store Stores a value to num2
     * @param value Value to store
     */
    void store(double value);

    /**
     * @brief handleOperation Processes any existing operation, stores new operation
     * @param newOperation New operation to store
     * @return result of existing operation (num1)
     */
    double handleOperation(opType newOperation);

    /**
     * @brief setOpLock Set the operation lock flag
     * @param lock Set flag to this
     */
    void setOpLock(bool lock);

    /**
     * @brief equalsPressed Processes existing operation, stores result to num1 and returns it
     * @return num1
     */
    double equalsPressed();

    /**
     * @brief setEqual Set the equal flag
     * @param newEqual Set flag to this
     */
    void setEqual(bool newEqual);

    /**
     * @brief clear Reset calculator to default except memory
     */
    void clear();

    /**
     * @brief clearMem Reset memory to 0
     */
    void clearMem();

    /**
     * @brief recallMem Return value stored in memory
     * @return Memory value
     */
    double recallMem();

    /**
     * @brief storeMem Store value to memory
     * @param value Value to store
     */
    void storeMem(double value);

    /**
     * @brief handleMem Process memory operations
     * @param memOper Operation to use
     * @param value Value to process
     */
    void handleMem(opType memOper, double value);

private:
    double num1;
    double num2;
    double memory;
    opType oper;

    bool equal;
    bool opLock;
};

#endif // CALCULATOR_H
