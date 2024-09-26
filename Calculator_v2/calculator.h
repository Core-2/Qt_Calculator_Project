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
    void slotOperatorPressed();
    void slotChangeSign();
    void slotClearEntry();
    void slotClearAll();
    void slotBackspace();
//    void slotPlus();
//    void slotMinus();
//    void slotMultiply();
//    void slotDivide();
    void slotPoint();
//    void slotEqual();
//    void slotDeleteHistory();

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    double currentSum;
    double currentFactor;
    double currentOperand;
    bool isOperatorPressed;
    bool isEqualPressed;

    enum class Operation {
        no_op,
        plus,
        minus,
        multiply,
        divide,
        equal,
    };

    Operation currentOperation;
    Operation previousOperation;
    Operation pendingOperation;

    QLineEdit *MainDisplay;
    QLineEdit *SecondDisplay;

    const QString divisionByZeroMsg{"Cannot divide by zero"};

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

    void clearOperands();

    void operationExec(Operation, double);
};
#endif // CALCULATOR_H
