#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    QFont *calculatorFont = new QFont();
    calculatorFont->setPointSize(18);
    calculatorFont->setFamily(QString::fromUtf8("Arial"));
    w.setFont(*calculatorFont);
    w.show();
    return a.exec();
}
