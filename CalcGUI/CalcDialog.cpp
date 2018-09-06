/**
  * @brief Assignment 9 Part B
  * @author Aaron Day
  */

#include "CalcDialog.h"
#include <QGridLayout>
#include <QPushButton>
#include <QValidator>
#include <stdexcept>

using namespace std;

CalcDialog::CalcDialog(QWidget *parent) : QDialog(parent) {

    //Initialize screen and button styles
    screenStyle = "font-size: 18pt";
    memStyle = "QPushButton {"
               "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 white, stop: 1 #FFFF8F);"
               "border-radius: 15px;"
               "border-width: 2px;"
               "border-style: outset;"
               "border-color: yellow;}"
               "QPushButton::pressed {"
               "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 white, stop: 1 yellow);"
               "border-radius: 10px;"
               "border-style: inset;}";
    numStyle = "QPushButton {"
               "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 white, stop: 1 #66CCFF);"
               "border-radius: 15px;"
               "border-width: 2px;"
               "border-style: outset;"
               "border-color: blue;}"
               "QPushButton::pressed {"
               "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 white, stop: 1 blue);"
               "border-radius: 10px;"
               "border-style: inset;}";
    opStyle = "QPushButton {"
               "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 white, stop: 1 #99FF66);"
               "border-radius: 15px;"
               "border-width: 2px;"
               "border-style: outset;"
               "border-color: green;}"
               "QPushButton::pressed {"
               "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 white, stop: 1 green);"
               "border-radius: 10px;"
               "border-style: inset;}";
    activeOpStyle = "QPushButton {"
               "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 white, stop: 1 #FF6666);"
               "border-radius: 15px;"
               "border-width: 2px;"
               "border-style: outset;"
               "border-color: red;}"
               "QPushButton::pressed {"
               "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 white, stop: 1 red);"
               "border-radius: 10px;"
               "border-style: inset;}";
    clearStyle = "QPushButton {"
               "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 white, stop: 1 gray);"
               "border-radius: 15px;"
               "border-width: 2px;"
               "border-style: outset;"
               "border-color: gray;}"
               "QPushButton::pressed {"
               "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 white, stop: 1 dark-gray);"
               "border-radius: 10px;"
               "border-style: inset;}";

    //Initialize and format the screen to display the results
    screen = new QLineEdit;
    screen->setMinimumHeight(BTN_SIZE);
    screen->setStyleSheet(screenStyle);
    QDoubleValidator* validDouble = new QDoubleValidator; //Ensure screen only contains a double
    screen->setValidator(validDouble);
    screen->setAlignment(Qt::AlignRight); //Align screen text to the right
    connect(screen, SIGNAL(textChanged(QString)), this, SLOT(clearScreen(QString)));
    connect(screen, SIGNAL(returnPressed()), this, SLOT(equalPressed()));

    //Create a grid of buttons
    QGridLayout* buttonGrid = new QGridLayout;

    //Initialize memory buttons, add them to grid, format them, and connect them to memOperations
    for(int i = 0; i < MEM; i++) {
        btnMemory[i] = new QPushButton(memoryText[i]);
        buttonGrid->addWidget(btnMemory[i],0,i);
        btnMemory[i]->setStyleSheet(memStyle); //light yellow
        btnMemory[i]->setFixedSize(BTN_SIZE, BTN_SIZE); //set button size
        connect(btnMemory[i], SIGNAL(clicked()), this, SLOT(memOperation()));
        if(i < 2) { btnMemory[i]->setEnabled(false); } //disable MC and MR when created
    }

    //Initialize clear buttons, add them to grid, format them, and connect them to clearPressed
    for(int i = 0; i < CLEAR; i++) {
        btnClear[i] = new QPushButton(clearText[i]);
        buttonGrid->addWidget(btnClear[i], 1, i);
        btnClear[i]->setStyleSheet(clearStyle);
        btnClear[i]->setFixedSize(BTN_SIZE, BTN_SIZE);
        btnClear[i]->setEnabled(false); //disable clear buttons when created
        connect(btnClear[i], SIGNAL(clicked()), this, SLOT(clearPressed()));
    }

    //Initialize number buttons, format them, and connect them to numPressed
    for(int i = 0; i < NUM; i++) {
        btnNumber[i] = new QPushButton(QString::number(i));
        btnNumber[i]->setStyleSheet(numStyle);
        connect(btnNumber[i], SIGNAL(clicked()), this, SLOT(numberPressed()));
        if(i == 0) {
            btnNumber[i]->setMinimumHeight(BTN_SIZE);
            btnNumber[i]->setMinimumWidth(BTN_SIZE * 2);
        }
        else { btnNumber[i]->setFixedSize(BTN_SIZE, BTN_SIZE); }
    }

    //Add number buttons to grid
    buttonGrid->addWidget(btnNumber[0], 5, 0, 1, 2); //0
    for(int i = 1; i <= 3; i++) { buttonGrid->addWidget(btnNumber[i], 4, i-1); } //1-3
    for(int i = 4; i <= 6; i++) { buttonGrid->addWidget(btnNumber[i], 3, i-4); } //4-6
    for(int i = 7; i <= 9; i++) { buttonGrid->addWidget(btnNumber[i], 2, i-7); } //7-9

    //Initialize decimal button, add it to grid, format it, and connect it to numberPressed
    btnDecimal = new QPushButton(".");
    buttonGrid->addWidget(btnDecimal, 5, 2);
    btnDecimal->setStyleSheet(numStyle);
    btnDecimal->setFixedSize(BTN_SIZE, BTN_SIZE);
    connect(btnDecimal, SIGNAL(clicked()), this, SLOT(numberPressed()));

    //Initialize operation buttons, format them, and connect them to operationPressed
    for(int i = 0; i < OPER; i++) {
        btnOperator[i] = new QPushButton(operatorText[i]);
        btnOperator[i]->setStyleSheet(opStyle);
        btnOperator[i]->setFixedSize(BTN_SIZE, BTN_SIZE);
        connect(btnOperator[i], SIGNAL(clicked()), this, SLOT(operatorPressed()));
        connect(btnOperator[i], SIGNAL(clicked()), this, SLOT(effectOn()));
    }
    //Add operator buttons to grid
    for(int i = 0; i < 4; i++) { buttonGrid->addWidget(btnOperator[i], 5 - i, 3); } //+ - x ÷
    for(int i = 4; i < 7; i++) { buttonGrid->addWidget(btnOperator[i], -3 + i, 4); } //√ % 1/x
    buttonGrid->addWidget(btnOperator[7], 1, 3); //±

    //Initialize equal button, add it to grid, format it, and connect it to equalPressed
    btnEqual = new QPushButton("=");
    buttonGrid->addWidget(btnEqual, 4, 4, 2, 1);
    btnEqual->setStyleSheet(opStyle);
    btnEqual->setMaximumWidth(BTN_SIZE);
    btnEqual->setMinimumHeight(BTN_SIZE * 2);
    connect(btnEqual, SIGNAL(clicked()), this, SLOT(equalPressed()));

    //Create the main layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(screen);
    mainLayout->addLayout(buttonGrid);

    setWindowTitle("Aaron's Calc");

    setLayout(mainLayout);
    show();
}

//Memory functions
void CalcDialog::memOperation() {
    //Create variables
    int index;
    QString oldString = screen->text();;
    double num = oldString.toDouble();;
    //Identify which button was pressed
    QObject* sender = QObject::sender();
    QPushButton* operPressed = dynamic_cast<QPushButton*>(sender);
    for(int i = 0;; i++) {
        if(operPressed->text() == memoryText[i]) { index = i; break; }
    }
    //Enable MC and MR buttons
    for(int i = 0; i < 2; i++) {
        btnMemory[i]->setEnabled(true);
    }
    //Process appropriate memory opperation
    resetScreen = false;
    switch(index) {
    case 0: //MC - Disable MC and MR buttons, clear memory
        for(int i = 0; i < 2; i++) {
            btnMemory[i]->setEnabled(false);
        }
        calcLogic.clearMem();
        break;
    case 1: //MR - Set screen to memory value
        screen->setText(QString::number(calcLogic.recallMem()));
        break;
    case 2: //MS - Store screen value into memory, overwrite current memory value
        calcLogic.storeMem(num);
        break;
    case 3: //M+ - Add screen value to memory, if memory is empty, value is added to 0 and stored as the new memory value
        calcLogic.handleMem(Calculator::ADD, num);
        break;
    case 4: //M- - Subtract screen value from memory, if memory is empty, value is subtracted from 0 and stored as the new memory value
        calcLogic.handleMem(Calculator::SUBTRACT, num);
        break;
    }
    resetScreen = true;
}

//Clear functions
void CalcDialog::clearPressed() {
    //reset flags and effects
    lock = false;
    equal = false;
    effectsOff();
    //Create variables
    int index;
    QString oldString = screen->text();;
    //Identify which button was pressed
    QObject* sender = QObject::sender();
    QPushButton* operPressed = dynamic_cast<QPushButton*>(sender);
    for(int i = 0;; i++) {
        if(operPressed->text() == clearText[i]) { index = i; break; }
    }
    //Process appropriate clear function
    switch(index) {
    case 0: //Backspace, disable if screen is empty
        screen->backspace();
        if(oldString.isEmpty()) { btnClear[0]->setEnabled(false); }
        break;
    case 1: //Clear line, if already clear then clear calc (not memory), disable backspace
        if(oldString.isEmpty()) {
            calcLogic.clear();
            for(int i = 0; i < CLEAR; i++) { btnClear[i]->setEnabled(false); } //disable all clear buttons if calc is cleared
        }
        btnClear[0]->setEnabled(false);
        screen->clear();
        break;
    case 2: //Clear calc (not memory), disable all clear buttons
        calcLogic.clear();
        screen->clear();
        for(int i = 0; i < CLEAR; i++) { btnClear[i]->setEnabled(false); }
        break;
    }
}

//Operator functions
void CalcDialog::operatorPressed() {
    //reset flags and effects
    effectsOff();
    resetScreen = false;
    calcLogic.setEqual(false);
    //enable C button
    btnClear[2]->setEnabled(true);
    //Create variables
    int index;
    double result;
    bool errorFound = false;
    //Identify which button was pressed
    QObject* sender = QObject::sender();
    QPushButton* operPressed = dynamic_cast<QPushButton*>(sender);
    for(int i = 0;; i++) {
        if(operPressed->text() == operatorText[i]) { index = i; break; }
    }
    //If an operation has not already been done or this is an immediate operation then store number and lock operators
    if(!lock || index >= 4) {
        QString oldString = screen->text();
        double num = oldString.toDouble();
        calcLogic.store(num);
        lock = true;
    }
    //If equal was the last process then set the calculator's operator to NONE
    if(equal) {
        calcLogic.setOper(Calculator::NONE);
        equal = false;
    }
    //Try to process the operation, if unable, display error
    try {
        result = calcLogic.handleOperation(static_cast<Calculator::opType>(index));
    }
    catch(runtime_error& err) {
        screen->setText(err.what());
        errorFound = true;
    }
    //If process had no errors then set the screen to display result
    if(!errorFound) {
        QString newString = QString::number(result);
        screen->setText(newString);
        resetScreen = true;
    }
}

void CalcDialog::equalPressed() {
    //reset flags and effects
    effectsOff();
    lock = false;
    resetScreen = false;
    //Create variables
    double result;
    bool errorFound= false;
    //If equal has not already been processed then store the screen value
    if(!equal) {
        QString oldString = screen->text();
        double num = oldString.toDouble();
        calcLogic.store(num);
        equal = true;
    }
    calcLogic.setEqual(true);
    //Try to process the last operation, if unable, display error
    try {
        result = calcLogic.equalsPressed();
    }
    catch(runtime_error& err) {
        screen->setText(err.what());
        errorFound = true;
    }
    //If process had no errors then set the screen to display result
    if(!errorFound) {
        QString newString = QString::number(result);
        screen->setText(newString);
        resetScreen = true;
    }
}

//Number buttons
void CalcDialog::numberPressed() {
    //reset flags and effects
    effectsOff();
    lock = false;
    calcLogic.setEqual(false);
    //If equal was the last process then set the calculator's operator to NONE
    if(equal) {
        calcLogic.setOper(Calculator::NONE);
        equal = false;
    }
    if(calcLogic.getOper() == Calculator::SQRT) {
        calcLogic.setOper(Calculator::NONE);
    }
    //Identify which button was pressed and insert that number into the screen
    QObject* sender = QObject::sender();
    QPushButton* numPressed = dynamic_cast<QPushButton*>(sender);
    if(resetScreen && numPressed->text() == ".") { screen->clear(); } //clears the screen if resetScreen flag is on and decimal is pressed
    screen->insert(numPressed->text());
}

//Checks
void CalcDialog::clearScreen(QString) {
    //reset effects
    effectsOff();
    //Create variables
    QString oldString = screen->text();
    //enable or disable clear buttons
    if(!oldString.isEmpty()) {
        btnClear[0]->setEnabled(true);
        btnClear[1]->setEnabled(true);
    } else {
        btnClear[0]->setEnabled(false);
        if(!btnClear[2]->isEnabled()) {
            btnClear[1]->setEnabled(false);
        }
    }
    //reset the screen when new input is added
    if(resetScreen) {
        screen->cursorBackward(false, 1);
        for(int i = 0; i < oldString.size() - 1; i++) {
            screen->cursorBackward(true);
        }
        screen->backspace();
        screen->cursorForward(false, 1);
        resetScreen = false;
    }
}

//Operator button effects
void CalcDialog::effectOn() {
    //Identify which button was pressed, if it was a main operator ( + - x ÷ ) then turn on effects
    QObject* sender = QObject::sender();
    QPushButton* operPressed = dynamic_cast<QPushButton*>(sender);
    for(int i = 0; i < 4; i++) {
        if(operPressed->text() == operatorText[i]) {
            operPressed->setStyleSheet(activeOpStyle);
            break;
        }
    }
}

void CalcDialog::effectsOff() {
    //Turn off all operator button effects
    for(int i = 0; i < 4; i++) {
        btnOperator[i]->setStyleSheet(opStyle);
    }
}
