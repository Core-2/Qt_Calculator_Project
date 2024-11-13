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
    historyList->insertItem(0, (new QListWidgetItem(SecondDisplay->text() + MainDisplay->text() + '=' + QString::number(result))));

    if(!historyDeleteButton->isEnabled())
        historyDeleteButton->setEnabled(true);
}


void Calculator::clearOperands() {
    rightOperand = 0.0;
    result = 0.0;
    isEqualPressed = false;
    isOperatorPressed = false;
    isFirstOperation = true;
    storedOperation = Operation::no_op;
    currentOperation = Operation::no_op;
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


void Calculator::lockOperationButtons() {
    PlusButton->setEnabled(false);
    MinusButton->setEnabled(false);
    MultButton->setEnabled(false);
    DivisionButton->setEnabled(false);
    PointButton->setEnabled(false);
    ChangeSignButton->setEnabled(false);
    ClearButton->setEnabled(false);
    ClearAllButton->setEnabled(false);
    BackspaceButton->setEnabled(false);
}


void Calculator::unlockOperationButtons() {
    slotClearAll();

    PlusButton->setEnabled(true);
    MinusButton->setEnabled(true);
    MultButton->setEnabled(true);
    DivisionButton->setEnabled(true);
    PointButton->setEnabled(true);
    ChangeSignButton->setEnabled(true);
    ClearButton->setEnabled(true);
    ClearAllButton->setEnabled(true);
    BackspaceButton->setEnabled(true);
}

//---------------------------------------------------------------------------------------------------------------------------------
void Calculator::slotDigitPressed(int digit) {
    if(MainDisplay->text() == divisionByZeroMsg) {
        unlockOperationButtons();
    }

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
    rightOperand = MainDisplay->text().toDouble();

    if(isFirstOperation) {
        result = rightOperand;
        isFirstOperation = false;
    }
    else {
        if(isOperatorPressed) {
            QString text{SecondDisplay->text()};
            text.chop(1);
        }
        else {
            calculate(rightOperand, storedOperation);

            if(MainDisplay->text() != divisionByZeroMsg) {
                addResultToHistory();
            }
            else {
                lockOperationButtons();
                return;
            }
        }
    }

    isOperatorPressed = true;

    MainDisplay->setText(QString::number(result));

    if(currentOperation == Operation::equal) {
        isEqualPressed = true;
        if(storedOperation != Operation::equal)
            SecondDisplay->setText(SecondDisplay->text() + QString::number(rightOperand) + clickedButton->text());
    }
    else {
        isEqualPressed = false;
        SecondDisplay->setText(MainDisplay->text() + clickedButton->text());
    }

    storedOperation = currentOperation;
}


void Calculator::calculate(double operand, Operation operation) {
    switch (operation) {
    case Operation::no_op:
        result = operand;
        break;
    case Operation::plus:
        result += operand;
        break;
    case Operation::minus:
        result -= operand;
        break;
    case Operation::multiply:
        result *= operand;
        break;
    case Operation::divide:
        if(operand == 0.0) {
            MainDisplay->setText(divisionByZeroMsg);
            return;
        }
        result /= operand;
        break;
    case Operation::equal:
        break;
    }
}
//---------------------------------------------------------------------------------------------------------------------------------


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
