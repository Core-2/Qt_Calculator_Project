#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QLabel>
#include <QList>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QString>
#include <QLineEdit>


class Calculator : public QWidget
{
    Q_OBJECT
private slots:
    void slotDigitPressed(int);
//    void slotClearEntry();
//    void slotClear();
    void slotBackspace();
    void slotPlus();
//    void slotMinus();
//    void slotMultiply();
//    void slotDivide();
    void slotPoint();
    void slotEqual();
//    void slotDeleteHistory();

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    double result{0};
    double currentSum{0};
    double currentFactor{0};
    double currentOperand{0};
    bool isFirstOp{true};
    bool isNextNumEmpty{true};
    bool isPointPressed{false};
    bool isOperatorPressed{false};
    bool isEqualPressed{false};
    int decimalCount{0};
    const int DIGIT_COUNT{11};
    int currentDigitCount{0};

    enum class Operation {
        plus,
        minus,
        multiply,
        divide,
        equal,
    };

    Operation op;

    QLineEdit *MainDisplay;
    QLineEdit *SecondDisplay;

    QList<QPushButton*> DigitButtons;

    QPushButton *PlusButton;
    QPushButton *MinusButton;
    QPushButton *MultButton;
    QPushButton *DivisionButton;

    QPushButton *PointButton;
    QPushButton *ChangeSignButton;

    QPushButton *EqualButton;

    QPushButton *ClearButton;
    QPushButton *ClearAllButton;
    QPushButton *BackspaceButton;

    QSignalMapper *mapper;

    QVBoxLayout *historyLayout;
    QList<QLabel*> historyList;
    QScrollArea *historyArea;
    QWidget *historyWindow;
    QLabel* historyLabel;
    QPushButton *historyDeleteButton;

    void createWidgets();

    void operationExec();
};
#endif // CALCULATOR_H
