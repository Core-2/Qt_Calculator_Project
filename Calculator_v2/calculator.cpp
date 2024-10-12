#include "calculator.h"

void Calculator::createWidgets() {
    QGridLayout *calcLayout = new QGridLayout();
    setLayout(calcLayout);

    MainDisplay = new QLineEdit();
    SecondDisplay = new QLineEdit();

    for(int i{0}; i < 10; i++) {
        DigitButtons.append(new QPushButton(QString::number(i)));
    }

    PlusButton = new QPushButton("+");
    MinusButton = new QPushButton("-");
    MultButton = new QPushButton("\303\227");
    DivisionButton = new QPushButton("\303\267");
    ClearButton = new QPushButton("Clear");
    ClearAllButton = new QPushButton("Clear All");
    BackspaceButton = new QPushButton("Backspace");
    PointButton = new QPushButton(".");
    ChangeSignButton = new QPushButton("\302\261");
    EqualButton = new QPushButton("=");

    historyLabel = new QLabel("History");
    historyDeleteButton = new QPushButton("Del");
    historyList = new QListWidget();

    calcLayout->addWidget(SecondDisplay, 0, 0, 1, 4);
    calcLayout->addWidget(MainDisplay, 1, 0, 1, 4);

    calcLayout->addWidget(ClearButton, 2, 0);
    calcLayout->addWidget(ClearAllButton, 2, 1);
    calcLayout->addWidget(BackspaceButton, 2, 2);

    calcLayout->addWidget(DigitButtons[7], 3, 0);
    calcLayout->addWidget(DigitButtons[8], 3, 1);
    calcLayout->addWidget(DigitButtons[9], 3, 2);

    calcLayout->addWidget(DigitButtons[4], 4, 0);
    calcLayout->addWidget(DigitButtons[5], 4, 1);
    calcLayout->addWidget(DigitButtons[6], 4, 2);

    calcLayout->addWidget(DigitButtons[1], 5, 0);
    calcLayout->addWidget(DigitButtons[2], 5, 1);
    calcLayout->addWidget(DigitButtons[3], 5, 2);

    calcLayout->addWidget(ChangeSignButton, 6, 0);
    calcLayout->addWidget(DigitButtons[0], 6, 1);
    calcLayout->addWidget(PointButton, 6, 2);

    calcLayout->addWidget(DivisionButton, 2, 3);
    calcLayout->addWidget(MultButton, 3, 3);
    calcLayout->addWidget(MinusButton, 4, 3);
    calcLayout->addWidget(PlusButton, 5, 3);
    calcLayout->addWidget(EqualButton, 6, 3);

    calcLayout->addWidget(historyLabel, 0, 4);
    calcLayout->addWidget(historyDeleteButton, 0, 5);
    calcLayout->addWidget(historyList, 1, 4, 6, 2);

    QFont *mainDisplayFont = new QFont();
    mainDisplayFont->setPointSize(36);
    mainDisplayFont->setFamily(QString::fromUtf8("Arial"));
    mainDisplayFont->setWeight(QFont::Bold);

    QFont *secondDisplayFont = new QFont();
    secondDisplayFont->setPointSize(12);
    secondDisplayFont->setFamily(QString::fromUtf8("Arial"));

    MainDisplay->setText("0");
    MainDisplay->setFixedHeight(75);
    MainDisplay->setAlignment(Qt::AlignRight);
    MainDisplay->setReadOnly(true);
    MainDisplay->setFont(*mainDisplayFont);
    MainDisplay->setTextMargins(10, 0, 10, 0);

    SecondDisplay->setText("");
    SecondDisplay->setFixedHeight(25);
    SecondDisplay->setAlignment(Qt::AlignRight);
    SecondDisplay->setReadOnly(true);
    SecondDisplay->setFont(*secondDisplayFont);
    SecondDisplay->setTextMargins(10, 0, 10, 0);

    historyDeleteButton->setFixedWidth(100);
    historyDeleteButton->setEnabled(false);
    historyLabel->setFixedSize(200, 50);

    ClearButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ClearAllButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    BackspaceButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    for(QPushButton *digit : DigitButtons) {
        digit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    }

    PlusButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    MinusButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    MultButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    DivisionButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    PointButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ChangeSignButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    EqualButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    historyDeleteButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    clearOperands();
}


void Calculator::addResultToHistory() {
    historyList->insertItem(0, (new QListWidgetItem(SecondDisplay->text() + MainDisplay->text())));

    if(!historyDeleteButton->isEnabled())
        historyDeleteButton->setEnabled(true);
}


void Calculator::clearOperands() {
    currentOperand = 0.0;
    currentSum = 0.0;
    currentFactor = 0.0;
    isEqualPressed = false;
    isOperatorPressed = false;
    currentOperation = Operation::no_op;
    previousOperation = Operation::no_op;
    pendingOperation = Operation::no_op;
}


Calculator::Operation Calculator::recognizeOperator(QString text) {
    Operation operation;
    if(text == "+")
        operation = Operation::plus;
    else if(text == "-")
        operation = Operation::minus;
    else if(text == "\303\227")
        operation = Operation::multiply;
    else if(text == "\303\267")
        operation = Operation::divide;
    else if(text == "=")
        operation = Operation::equal;
    else
        operation = Operation::no_op;

    return operation;
}


void Calculator::operatorPressedAgain(Operation operation, double operand) {
    if(isEqualPressed) {
        SecondDisplay->setText(MainDisplay->text());
        isEqualPressed = false;
    }
    else {
    QString text{SecondDisplay->text()};
    text.chop(1);
    SecondDisplay->setText(text);
    }

    if(operation == Operation::multiply ||
            operation == Operation::divide)
    {
        currentFactor = operand;
        currentSum = 0.0;
    }
    else {
        currentSum = operand;
        currentFactor = 0.0;
    }


    previousOperation = operation;
}


void Calculator::operatorPressedFirstTime(Operation operation, double operand) {
    if(operation == Operation::multiply ||
            operation == Operation::divide)
        currentFactor = operand;
    else
        currentSum = operand;
}


void Calculator::additiveOperatorPressed(Operation operation, double operand) {
    if(operation == Operation::multiply ||
            operation == Operation::divide)
    {
        currentFactor = operand;
        pendingOperation = previousOperation;
    }
    else {
        if(previousOperation == Operation::plus)
            currentSum += operand;
        else if(previousOperation == Operation::minus)
            currentSum -= operand;
    }
}


void Calculator::multiplicativeOperatorPressed(Operation operation, double operand) {
    if(previousOperation == Operation::multiply)
        currentFactor *= operand;
    else if(previousOperation == Operation::divide)
        currentFactor /= operand;

    if(operation != Operation::multiply &&
            operation != Operation::divide)
    {
        if(pendingOperation == Operation::plus || pendingOperation == Operation::no_op)
            currentSum += currentFactor;
        else if(pendingOperation == Operation::minus)
            currentSum -= currentFactor;

        currentFactor = 0.0;
        pendingOperation = Operation::no_op;
    }
}


void Calculator::operationExec(Operation operation, double operand) {
    if(isOperatorPressed) {
        operatorPressedAgain(operation, operand);
        return;
    }

    SecondDisplay->setText(SecondDisplay->text() + MainDisplay->text());

    switch(previousOperation) {
    case Operation::no_op:
        operatorPressedFirstTime(operation, operand);
        break;

    case Operation::plus:
    case Operation::minus:
        additiveOperatorPressed(operation, operand);
        break;

    case Operation::multiply:
    case Operation::divide:
        if(previousOperation == Operation::divide && operand == 0.0) {
            MainDisplay->setText(divisionByZeroMsg);
            isEqualPressed = true;
            return;
        }
        multiplicativeOperatorPressed(operation, operand);
        break;

    case Operation::equal:
        break;
    }

    if(operation == Operation::equal) {
        MainDisplay->setText(QString::number(currentSum, 'g', 16));
        isEqualPressed = true;
    }

    previousOperation = operation;
}


void Calculator::slotDigitPressed(int digit) {
    if(isOperatorPressed) {
        MainDisplay->setText("0");
        isOperatorPressed = false;
    }

    if(isEqualPressed) {
        slotClearAll();
    }

    if(MainDisplay->text() == "0") {

        if(digit == 0)
            return;

        MainDisplay->setText(QString::number(digit));
        return;
    }

    MainDisplay->setText(MainDisplay->text() + QString::number(digit));
}


void Calculator::slotOperatorPressed() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    currentOperation = recognizeOperator(clickedButton->text());
    currentOperand = MainDisplay->text().toDouble();
    operationExec(currentOperation, currentOperand);
    SecondDisplay->setText(SecondDisplay->text() + clickedButton->text());
    isOperatorPressed = true;

    if(isEqualPressed && MainDisplay->text() != divisionByZeroMsg)
        addResultToHistory();
}


void Calculator::slotPoint() {
    if(isOperatorPressed) {
        MainDisplay->setText("0");
        isOperatorPressed = false;
    }

    if(isEqualPressed) {
        slotClearAll();
    }

    if(!MainDisplay->text().contains('.')) {
        MainDisplay->setText(MainDisplay->text() + ".");
    }
}


void Calculator::slotChangeSign() {
    QString text = MainDisplay->text();
    double operand = text.toDouble();

    if(operand > 0.0) {
        text.prepend("-");
    }
    else if(operand < 0.0) {
        text.remove(0, 1);
    }

    MainDisplay->setText(text);
}


void Calculator::slotClearEntry() {
    MainDisplay->setText("0");
}


void Calculator::slotClearAll() {
    slotClearEntry();
    SecondDisplay->setText("");
    clearOperands();
}


void Calculator::slotBackspace() {
    if(isEqualPressed) {
        SecondDisplay->setText("");
        return;
    }

    if(MainDisplay->text() == "0") return;

    QString text{MainDisplay->text()};
    text.chop(1);
    if(text.isEmpty()) {
        text = "0";
    }

    MainDisplay->setText(text);
}


void Calculator::slotDeleteHistory() {
    historyList->clear();
    historyDeleteButton->setEnabled(false);
}


Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    resize(950, 500);
    setWindowTitle("Calculator");
    createWidgets();

    mapper = new QSignalMapper(this);

    for(int i{0}; i < 10; i++) {
        connect(DigitButtons[i], SIGNAL(clicked()), mapper, SLOT(map()), Qt::UniqueConnection);
        mapper->setMapping(DigitButtons[i], i);
    }

    connect(mapper, SIGNAL(mappedInt(int)), this, SLOT(slotDigitPressed(int)), Qt::UniqueConnection);

    connect(BackspaceButton, SIGNAL(clicked()), this, SLOT(slotBackspace()), Qt::UniqueConnection);
    connect(PointButton, SIGNAL(clicked()), this, SLOT(slotPoint()), Qt::UniqueConnection);
    connect(ChangeSignButton, SIGNAL(clicked()), this, SLOT(slotChangeSign()), Qt::UniqueConnection);
    connect(ClearButton, SIGNAL(clicked()), this, SLOT(slotClearEntry()), Qt::UniqueConnection);
    connect(ClearAllButton, SIGNAL(clicked()), this, SLOT(slotClearAll()), Qt::UniqueConnection);
    connect(historyDeleteButton, SIGNAL(clicked()), this, SLOT(slotDeleteHistory()), Qt::UniqueConnection);

    connect(PlusButton, SIGNAL(clicked()), this, SLOT(slotOperatorPressed()), Qt::UniqueConnection);
    connect(MinusButton, SIGNAL(clicked()), this, SLOT(slotOperatorPressed()), Qt::UniqueConnection);
    connect(MultButton, SIGNAL(clicked()), this, SLOT(slotOperatorPressed()), Qt::UniqueConnection);
    connect(DivisionButton, SIGNAL(clicked()), this, SLOT(slotOperatorPressed()), Qt::UniqueConnection);
    connect(EqualButton, SIGNAL(clicked()), this, SLOT(slotOperatorPressed()), Qt::UniqueConnection);

}


Calculator::~Calculator()
{
}
