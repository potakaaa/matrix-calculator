#include "matrixcalcu.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    matrixCalcu w;
    w.setWindowIcon(QIcon(":/logo/resource/CS CALC.png"));

    w.show();
    return a.exec();
}
