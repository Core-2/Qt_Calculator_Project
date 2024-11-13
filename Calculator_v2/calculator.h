#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QLabel>
#include <QList>
#include <QGridLayout>
#include <QString>
#include <QLineEdit>
#include <QListWidget>


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
    void slotPoint();
    void slotDeleteHistory();

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    double result;
    double rightOperand;
    bool isOperatorPressed;
    bool isEqualPressed;
    bool isFirstOperation;

    enum class Operation {
        no_op,
        plus,
        minus,
        multiply,
        divide,
        equal,
    };

    Operation storedOperation;
    Operation currentOperation;

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

    QLabel* historyLabel;
    QPushButton *historyDeleteButton;
    QListWidget *historyList;

    void createWidgets();

    void addResultToHistory();

    void clearOperands();

    void calculate(double, Operation);

    void lockOperationButtons();
    void unlockOperationButtons();

    Operation recognizeOperator(QString);
};
#endif // CALCULATOR_H
