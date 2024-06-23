#include "matrixcalcu.h"

#include <QApplication>
#include <QIcon>
#include <QStyleFactory>
#include <QPalette>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    matrixCalcu w;
    w.setWindowIcon(QIcon(":/logo/resource/CS CALC.png"));

    a.setStyle(QStyleFactory::create("Fusion"));

    // Create a custom palette
    QPalette customPalette;

    // Window and widget colors
    customPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    customPalette.setColor(QPalette::WindowText, Qt::white);
    customPalette.setColor(QPalette::Base, QColor(42, 42, 42));
    customPalette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
    customPalette.setColor(QPalette::ToolTipBase, Qt::white);
    customPalette.setColor(QPalette::ToolTipText, Qt::white);
    customPalette.setColor(QPalette::Text, Qt::white);
    customPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    customPalette.setColor(QPalette::ButtonText, Qt::white);
    customPalette.setColor(QPalette::BrightText, Qt::red);
    customPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    customPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    customPalette.setColor(QPalette::HighlightedText, Qt::black);

    // Optionally remove border colors or set them to match the background
    customPalette.setColor(QPalette::Shadow, QColor(53, 53, 53));
    customPalette.setColor(QPalette::Mid, QColor(53, 53, 53));

    a.setPalette(customPalette);


    w.show();
    return a.exec();
}
