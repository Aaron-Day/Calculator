/**
  * @brief Assignment 9 Part A
  * @author Aaron Day
  */

#include "catch.hpp"
#include "Calculator.h"
using namespace std;


TEST_CASE( "Calculator/opsplus", "Basic operations + " ) {
    Calculator c;
    c.store(3);
    double result1 = c.handleOperation(Calculator::ADD);
    REQUIRE( result1 == Approx(3) );
    c.store(2);
    double result2 = c.equalsPressed();
    REQUIRE( result2 == Approx(5) );
}

TEST_CASE( "Calculator/opsminus", "Basic operations - " ) {
    Calculator c;
    c.store(3);
    double result1 = c.handleOperation(Calculator::SUBTRACT);
    REQUIRE( result1 == Approx(3) );
    c.store(2);
    double result2 = c.equalsPressed();
    REQUIRE( result2 == Approx(1) );
}

TEST_CASE( "Calculator/opstimes", "Basic operations * " ) {
    Calculator c;
    c.store(3);
    double result1 = c.handleOperation(Calculator::MULTIPLY);
    REQUIRE( result1 == Approx(3) );
    c.store(2);
    double result2 = c.equalsPressed();
    REQUIRE( result2 == Approx(6) );
}

TEST_CASE( "Calculator/opsdivide", "Basic operations / " ) {
    Calculator c;
    c.store(3);
    double result1 = c.handleOperation(Calculator::DIVIDE);
    REQUIRE( result1 == Approx(3) );
    c.store(2);
    double result2 = c.equalsPressed();
    REQUIRE( result2 == Approx(1.5) );
}

TEST_CASE( "Calculator/chain", "Basic operations chain " ) {
    Calculator c;
    c.store(3);
    double result1 = c.handleOperation(Calculator::ADD);
    REQUIRE( result1 == Approx(3) );
    c.store(5);
    double result2 = c.handleOperation(Calculator::SUBTRACT);
    REQUIRE( result2 == Approx(8) );
    c.store(2);
    double result3 = c.equalsPressed();
    REQUIRE( result3 == Approx(6) );
}

TEST_CASE( "Calculator/equalsChain", "Tests hitting equals multiple times" ) {
    //" 3 + 2 = = " should make 7
    Calculator c;
    c.store(3);
    double result1 = c.handleOperation(Calculator::ADD);
    REQUIRE( result1 == Approx(3) );
    c.store(2);
    double result2 = c.equalsPressed();
    REQUIRE( result2 == Approx(5) );
    double result3 = c.equalsPressed();
    REQUIRE( result3 == Approx(7) );
    double result4 = c.equalsPressed();
    REQUIRE( result4 == Approx(9) );
}

TEST_CASE( "Calculator/sqrRoot", "Test square root" ) {
    //" 9 - 16√ " should make 5
    Calculator c;
    c.store(9);
    double result1 = c.handleOperation(Calculator::SUBTRACT);
    REQUIRE( result1 == Approx(9) );
    c.store(16);
    double result2 = c.handleOperation(Calculator::SQRT);
    REQUIRE( result2 == Approx(4) );
    double result3 = c.equalsPressed();
    REQUIRE( result3 == Approx(5) );
}

TEST_CASE( "Calculator/percent", "Test percent") {
    //" 5 - 20% = = " should make 3
    Calculator c;
    c.store(5);
    double result1 = c.handleOperation(Calculator::SUBTRACT);
    REQUIRE( result1 == Approx(5) );
    c.store(20);
    double result2 = c.handleOperation(Calculator::PERCENT);
    REQUIRE( result2 == Approx(1) );
    double result3 = c.equalsPressed();
    REQUIRE( result3 == Approx(4) );
    double result4 = c.equalsPressed();
    REQUIRE( result4 == Approx(3) );
}

TEST_CASE( "Calculator/percentEqual", "Test equal after percent (no other operator)") {
    //" 20% = = " should make 0.2
    Calculator c;
    c.store(20);
    double result1 = c.handleOperation(Calculator::PERCENT);
    REQUIRE( result1 == Approx(0.2) );
    double result2 = c.equalsPressed();
    REQUIRE( result2 == Approx(0.2) );
}

TEST_CASE( "Calculator/inverse", "Test inverse") {
    //" 10 - 10 1/x " should make 9.9
    Calculator c;
    c.store(10);
    double result1 = c.handleOperation(Calculator::SUBTRACT);
    REQUIRE( result1 == Approx(10) );
    c.store(10);
    double result2 = c.handleOperation(Calculator::INVERSE);
    REQUIRE( result2 == Approx(.1) );
    double result3 = c.equalsPressed();
    REQUIRE( result3 == Approx(9.9) );
}

TEST_CASE( "Calculator/sign", "Test sign") {
    //" 10 - 5± " should make 15
    Calculator c;
    c.store(10);
    double result1 = c.handleOperation(Calculator::SUBTRACT);
    REQUIRE( result1 == Approx(10) );
    c.store(5);
    double result2 = c.handleOperation(Calculator::SIGN);
    REQUIRE( result2 == Approx(-5) );
    double result3 = c.equalsPressed();
    REQUIRE( result3 == Approx(15) );
}

TEST_CASE( "Calculator/clear", "Test clear") {
    //" 3 + 2 = C = = " should make 0
    Calculator c;
    c.store(3);
    double result1 = c.handleOperation(Calculator::ADD);
    REQUIRE( result1 == Approx(3) );
    c.store(2);
    double result2 = c.equalsPressed();
    REQUIRE( result2 == Approx(5) );
    c.clear();
    double result3 = c.equalsPressed();
    REQUIRE( result3 == Approx(0) );
    double result4 = c.equalsPressed();
    REQUIRE( result4 == Approx(0) );
}

TEST_CASE( "Calculator/MS_MR", "Test memory store and recall") {
    //" 5 MS = " should make 0, " MR " should make 5
    Calculator c;
    c.storeMem(5);
    double result1 = c.equalsPressed();
    REQUIRE( result1 == Approx(0) );
    double result2 = c.recallMem();
    REQUIRE( result2 == Approx(5) );
}

TEST_CASE( "Calculator/M±", "Test memory addition and subtraction") {
    //" 5 M+ M+ M+ MR " should make 15, " 5 M- MR " should make 10
    Calculator c;
    c.handleMem(Calculator::ADD, 5);
    c.handleMem(Calculator::ADD, 5);
    c.handleMem(Calculator::ADD, 5);
    double result1 = c.recallMem();
    REQUIRE( result1 == Approx(15) );
    c.handleMem(Calculator::SUBTRACT, 5);
    double result2 = c.recallMem();
    REQUIRE( result2 == Approx(10) );
}

TEST_CASE( "Calculator/MC", "Test memory clear") {
    //" 5 MS M+ MR " should make 10, " MC MR " should make 0
    Calculator c;
    c.storeMem(5);
    c.handleMem(Calculator::ADD, 5);
    double result1 = c.recallMem();
    REQUIRE( result1 == Approx(10) );
    c.clearMem();
    double result2 = c.recallMem();
    REQUIRE( result2 == Approx(0) );
}

TEST_CASE( "Calculator/sqrtBetweenEquals", "process √ between equals") {
    //" 61 + 20 = √ √ = " should make 3√ or about 1.7
    Calculator c;
    c.store(61);
    c.handleOperation(Calculator::ADD);
    c.store(20);
    double result1 = c.equalsPressed();
    REQUIRE( result1 == Approx(81) );
    c.store(result1);
    double result2 = c.handleOperation(Calculator::SQRT);
    REQUIRE( result2 == Approx(9) );
    double result3 = c.handleOperation(Calculator::SQRT);
    REQUIRE( result3 == Approx(3) );
    double result4 = c.equalsPressed();
    REQUIRE( result4 == Approx(sqrt(3)));
}

TEST_CASE( "Calculator/opSqrtEqual", "process √ between op and equals") {
    //" 81 + √ √ = " should make 84
    Calculator c;
    c.store(81);
    double result1 = c.handleOperation(Calculator::ADD);
    REQUIRE( result1 == Approx(81) );
    c.store(result1);
    double result2 = c.handleOperation(Calculator::SQRT);
    REQUIRE( result2 == Approx(9) );
    double result3 = c.handleOperation(Calculator::SQRT);
    REQUIRE( result3 == Approx(3) );
    double result4 = c.equalsPressed();
    REQUIRE( result4 == Approx(84) );
}

TEST_CASE( "Calculator/complexChain", "process √s ops nums and equals") {
    //" 61 + 20 = √ √ + 4 = " should make 7
    Calculator c;
    c.store(61);
    c.handleOperation(Calculator::ADD);
    c.store(20);
    double result1 = c.equalsPressed();
    REQUIRE( result1 == Approx(81) );
    c.store(result1);
    c.setEqual(false); //pressing anything other than = disables the equal bool
    double result2 = c.handleOperation(Calculator::SQRT);
    REQUIRE( result2 == Approx(9) );
    double result3 = c.handleOperation(Calculator::SQRT);
    REQUIRE( result3 == Approx(3) );
    c.store(result3);
    double result4 = c.handleOperation(Calculator::ADD);
    REQUIRE( result4 == Approx(3) );
    c.store(4);
    double result5 = c.equalsPressed();
    REQUIRE( result5 == Approx(7) );
}

TEST_CASE( "Calculator/multipleNowOps", "process √ then %") {
    //" 81 √ % = " should make 0.09
    Calculator c;
    c.store(81);
    double result1 = c.handleOperation(Calculator::SQRT);
    REQUIRE( result1 == Approx(9) );
    double result2 = c.handleOperation(Calculator::PERCENT);
    REQUIRE( result2 == Approx(0.09) );
    double result3 = c.equalsPressed();
    REQUIRE( result3 == Approx(0.09) );

}

TEST_CASE( "Calculator/multipleOps1", "pressing operation multiple times, process only once") {
    //" 5 + + + + + + = " should make 10
    Calculator c;
    c.store(5);
    c.handleOperation(Calculator::ADD);
    c.handleOperation(Calculator::ADD);
    c.handleOperation(Calculator::ADD);
    c.handleOperation(Calculator::ADD);
    c.handleOperation(Calculator::ADD);
    c.handleOperation(Calculator::ADD);
    double result1 = c.equalsPressed();
    REQUIRE( result1 == Approx(10) );
}

TEST_CASE( "Calculator/multipleOps2", "pressing multiple operations, first and last same, process only last") {
    //" 5 + - + - + - + = " should make 10
    Calculator c;
    c.store(5);
    c.handleOperation(Calculator::ADD);
    c.handleOperation(Calculator::SUBTRACT);
    c.handleOperation(Calculator::ADD);
    c.handleOperation(Calculator::SUBTRACT);
    c.handleOperation(Calculator::ADD);
    c.handleOperation(Calculator::SUBTRACT);
    c.handleOperation(Calculator::ADD);
    double result1 = c.equalsPressed();
    REQUIRE( result1 == Approx(10) );
}

TEST_CASE( "Calculator/multipleOps3", "pressing multiple operations, first and last different, process only last one") {
    //" 5 + - + - + - + - = " should make 0
    Calculator c;
    c.store(5);
    c.handleOperation(Calculator::ADD);
    c.handleOperation(Calculator::SUBTRACT);
    c.handleOperation(Calculator::ADD);
    c.handleOperation(Calculator::SUBTRACT);
    c.handleOperation(Calculator::ADD);
    c.handleOperation(Calculator::SUBTRACT);
    c.handleOperation(Calculator::ADD);
    c.handleOperation(Calculator::SUBTRACT);
    double result1 = c.equalsPressed();
    REQUIRE( result1 == Approx(0) );
}

TEST_CASE( "Calculator/equalStore", "test reset when store is used after equal") {
    //" 5 + = 5 = " should make 5
    Calculator c;
    c.store(5);
    double result1 = c.handleOperation(Calculator::ADD);
    REQUIRE( result1 == Approx(5) );
    c.store(5);
    double result2 = c.equalsPressed();
    REQUIRE( result2 == Approx(10) );
    c.store(5);
    double result3 = c.equalsPressed();
    REQUIRE( result3 == Approx(5) );
}

TEST_CASE( "Calculator/opNowAndLater", "process immediate and delayed operators") {
    //" 61 + 81 √ √ + 3 " should make 67
    Calculator c;
    c.store(61);
    c.handleOperation(Calculator::ADD);
    c.store(81);
    double result1 = c.handleOperation(Calculator::SQRT);
    REQUIRE( result1 == Approx(9) );
    double result2 = c.handleOperation(Calculator::SQRT);
    REQUIRE( result2 == Approx(3) );
    c.store(result2);
    double result3 = c.handleOperation(Calculator::ADD);
    REQUIRE( result3 == Approx(64) );
    c.store(3);
    double result4 = c.equalsPressed();
    REQUIRE( result4 == Approx(67) );
}

TEST_CASE( "Calculator/opEquals", "pressing an operator followed by equals") {
    //" 5 + = = " should make 15
    Calculator c;
    c.store(5);
    double result1 = c.handleOperation(Calculator::ADD);
    REQUIRE( result1 == Approx(5) );
    double result2 = c.equalsPressed();
    REQUIRE( result2 == Approx(10) );
    double result3 = c.equalsPressed();
    REQUIRE( result3 == Approx(15) );
}

TEST_CASE( "Calculator/sqrtPercentEqual", "test equal after sqrt and percent") {
    //" 81 √ % = " should make 0.09
    Calculator c;
    c.store(81);
    double result1 = c.handleOperation(Calculator::SQRT);
    REQUIRE( result1 == Approx(9) );
    double result2 = c.handleOperation(Calculator::PERCENT);
    REQUIRE( result2 == Approx(0.09) );
    double result3 = c.equalsPressed();
    REQUIRE( result3 == Approx(0.09) );
}

TEST_CASE( "Calculator/sqrtNumberEqual", "test number after sqrt") {
    //" 81 √ 6 = " should make 6
    Calculator c;
    c.store(81);
    double result1 = c.handleOperation(Calculator::SQRT);
    REQUIRE( result1 == Approx(9) );
    if(c.getOper() == Calculator::SQRT) {
        c.setOper(Calculator::NONE);
    }
    c.store(6);
    double result2 = c.equalsPressed();
    REQUIRE( result2 == Approx(6) );
}
