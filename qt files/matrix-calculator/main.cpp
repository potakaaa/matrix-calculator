#include "matrixcalcu.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    matrixCalcu w;
    w.setWindowIcon(QIcon("D:/Documents/SCHOOL WORKS/1ST YEAR BS CS1A/2ND SEM/CS121 - Computer Programming 2/Matrix Calculator/logo/CS CALC.png"));

    w.show();
    return a.exec();
}
