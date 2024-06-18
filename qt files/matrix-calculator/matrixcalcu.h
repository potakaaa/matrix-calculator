#ifndef MATRIXCALCU_H
#define MATRIXCALCU_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class matrixCalcu;
}
QT_END_NAMESPACE

class matrixCalcu : public QMainWindow
{
    Q_OBJECT

public:
    matrixCalcu(QWidget *parent = nullptr);
    ~matrixCalcu();

private:
    Ui::matrixCalcu *ui;
};
#endif // MATRIXCALCU_H
