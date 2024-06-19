#include "matrixcalcu.h"
#include "ui_matrixcalcu.h"

matrixCalcu::matrixCalcu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::matrixCalcu)
{
    ui->setupUi(this);

    setWindowTitle("Matrix Calculator");

    QGridLayout *layout = new QGridLayout(ui->frame_6);

    // Placeholder for matrix A size
    int matrixA_rows = 3; int matrixA_cols = 3; int matrixA_size = matrixA_rows*matrixA_cols;

    int rowNum = 0; int colNum = 0; int i = 0;
    std::string name;

    QLineEdit* lineEdit_matrixA[matrixA_size];

    QLineEdit* sample = new QLineEdit(ui->frame_6);
    /**
    for (rowNum = 0; rowNum <= matrixA_rows; rowNum++) {
        for(colNum = 0; colNum <= matrixA_cols; colNum++) {
            layout->addWidget(lineEdit_matrixA[i], rowNum, colNum);
            i++;
        }

    }
    **/

}

matrixCalcu::~matrixCalcu()
{
    delete ui;
}
