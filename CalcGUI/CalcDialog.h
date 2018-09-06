/**
  * @brief Assignment 9 Part B
  * @author Aaron Day
  */

#ifndef CALCDIALOG_H
#define CALCDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "Calculator.h"

class CalcDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CalcDialog(QWidget *parent = 0);

signals:

public slots:
    /**
     * @brief memOperation Processes memory button operations
     */
    void memOperation();

    /**
     * @brief clearPressed Processes clear button operations
     */
    void clearPressed();

    /**
     * @brief operatorPressed Processes operator buttons
     */
    void operatorPressed();

    /**
     * @brief equalPressed Processes equal button
     */
    void equalPressed();

    /**
     * @brief numberPressed Processes number buttons
     */
    void numberPressed();

    /**
     * @brief clearScreen Clears the screen when screen changes with resetScreen flag enabled
     */
    void clearScreen(QString);

    /**
     * @brief effectOn Changes color of active operation button; applies only to + - x ÷
     */
    void effectOn();

    /**
     * @brief effectsOff Resets color of operation buttons to origional color
     */
    void effectsOff();

private:
    //Create the screen
    QLineEdit* screen;

    //resetScreen flag - used to signal when to reset the screen after changes
    bool resetScreen = false;

    //Standard button size
    static const int BTN_SIZE = 30;

    //Create number buttons
    static const int NUM = 10;
    QPushButton* btnNumber[NUM]; //0-9
    QPushButton* btnDecimal;

    //Create operator buttons
    static const int OPER = 8;
    QString operatorText[OPER] = {"+","-","x","÷","√","%","1/x","±"};
    QPushButton* btnOperator[OPER]; //+, -, x, ÷, √, %, 1/x, ±
    QPushButton* btnEqual;
        //equal flag - used to signal when the equal button was just processed
    bool equal = false;
        //lock flag - used to signal when an operation was just processed
    bool lock = false;

    //Create memory buttons
    static const int MEM = 5;
    QString memoryText[MEM] = {"MC","MR","MS","M+","M-"};
    QPushButton* btnMemory[MEM]; //MC, MR, MS, M+, M-

    //Create clear buttons
    static const int CLEAR = 3;
    QString clearText[CLEAR] = {"←","CE","C"};
    QPushButton* btnClear[CLEAR]; //←, CE, C

    //Create calculator object to process logic
    Calculator calcLogic;

    //Create screen and button styles string variables
    QString screenStyle;
    QString memStyle;
    QString numStyle;
    QString opStyle;
    QString activeOpStyle;
    QString clearStyle;
};

#endif // CALCDIALOG_H
