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

    historyWindow = new QWidget();
    historyLayout = new QVBoxLayout(historyWindow);
    historyLabel = new QLabel("History");
    historyArea = new QScrollArea();
    historyDeleteButton = new QPushButton("Del");

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
    calcLayout->addWidget(historyArea, 1, 4, 6, 2);

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

    historyArea->setWidget(historyWindow);
    historyArea->setFixedWidth(300);
    historyArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    historyArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    historyDeleteButton->setFixedWidth(100);
    historyDeleteButton->setEnabled(false);

    historyLayout->setAlignment(Qt::AlignTop);
    historyLayout->setContentsMargins(0, 0, 0, 0);

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
}

void Calculator::slotDigitPressed(int digit) {
    if(isEqualPressed) {
        SecondDisplay->setText("");
        currentSum = 0;
        currentOperand = 0;
        isEqualPressed = false;
    }
    if(isOperatorPressed) {
        MainDisplay->setText("0");
        isOperatorPressed = false;
    }

    if(MainDisplay->text() == "0") {
        if(digit == 0) return;
        MainDisplay->setText(QString::number(digit));

        //qDebug() << "Display's length: " << MainDisplay->text().length();

        return;
    }

    MainDisplay->setText(MainDisplay->text() + QString::number(digit));

    //qDebug() << "Display's length: " << MainDisplay->text().length();
}

void Calculator::slotPoint() {
    if(!MainDisplay->text().contains('.')) {
        MainDisplay->setText(MainDisplay->text() + ".");
    }
}

void Calculator::slotPlus() {
    if(isEqualPressed) {
        SecondDisplay->setText(MainDisplay->text() + "+");
        currentSum = 0;
        currentOperand = 0;
        isEqualPressed = false;
    }
    else {
        SecondDisplay->setText(SecondDisplay->text() + MainDisplay->text() + "+");
    }

    currentOperand = MainDisplay->text().toDouble();
    currentSum += currentOperand;
    currentOperand = 0;
    isOperatorPressed = true;
}

void Calculator::slotEqual() {
    if(isEqualPressed) {
        SecondDisplay->setText(QString::number(currentSum) + "+" + QString::number(currentOperand) + "=");

        currentSum += currentOperand;

        MainDisplay->setText(QString::number(currentSum));

        return;
    }

    SecondDisplay->setText(SecondDisplay->text() + MainDisplay->text() + "=");

    currentOperand = MainDisplay->text().toDouble();
    currentSum += currentOperand;

    MainDisplay->setText(QString::number(currentSum));

    isEqualPressed = true;
    isOperatorPressed = true;
}

void Calculator::slotBackspace() {
    if(MainDisplay->text() == "0") return;

    QString text{MainDisplay->text()};
    text.chop(1);
    if(text.isEmpty()) {
        text = "0";
    }

    MainDisplay->setText(text);
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

    connect(PlusButton, SIGNAL(clicked()), this, SLOT(slotPlus()), Qt::UniqueConnection);
    connect(EqualButton, SIGNAL(clicked()), this, SLOT(slotEqual()), Qt::UniqueConnection);

}

Calculator::~Calculator()
{
}

