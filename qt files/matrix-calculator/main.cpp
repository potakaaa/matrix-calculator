#include "matrixcalcu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    matrixCalcu w;
    w.show();
    return a.exec();
}
