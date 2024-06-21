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

public slots:
    void switch_page_simpleOperation_1();
    void switch_page_advancedOperation_1();
    void clear_matrixA_size();
    void clear_matrixA_size_2();
    void enter_simpleOperation_1();
    void enter_simpleOperation_2();
    void enter_advancedOperation_1();
    int to_int(QString text);
    void clear_matrixA_entries();
    void clear_matrixB_entries();
};
#endif // MATRIXCALCU_H
