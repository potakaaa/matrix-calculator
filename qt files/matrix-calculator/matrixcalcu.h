#ifndef MATRIXCALCU_H
#define MATRIXCALCU_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>

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
    QButtonGroup *buttonGroup;
    int to_int(QString text);
    bool int_validator(QString text);
    bool size_validator(int num);
    void showError(const QString message);
    bool checkMatrixEntries_ifNumeric(std::vector<QLineEdit*> lineEdit_vector);
    std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>>& matrix);
    void populateMatrixA();
    std::vector<std::vector<double>> extractLineEditText(std::vector<QLineEdit*> lineEdits, int rows, int cols);

public slots:
    void switch_page_simpleOperation_1();
    void switch_page_advancedOperation_1();
    void clear_matrixA_size();
    void clear_matrixA_size_2();
    void clear_matrixA_entries();
    void clear_matrixB_entries();
    void enter_simpleOperation_1();
    void enter_simpleOperation_2();
    void enter_advancedOperation_1();
    void updateButtonStyles();
    void clear_matrixA_2_entries();
    void remove_existingMatrix(QGridLayout* gridLayout);
    bool check_emptyMatrix(std::vector<QLineEdit*> lineEdit_vector);
    void resultMatrix();
    void resultMatrix_2();




};
#endif // MATRIXCALCU_H
