#include "matrixcalcu.h"
#include "ui_matrixcalcu.h"

matrixCalcu::matrixCalcu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::matrixCalcu)
{
    ui->setupUi(this);

    setWindowTitle("Matrix Calculator");




    // For Matrix A Entries
    // Placeholder for matrix A size
    int matrixA_rows = 2; int matrixA_cols = 2; int matrixA_size = matrixA_rows*matrixA_cols;
    int rowNum = 0; int colNum = 0; int i = 0;
    QLineEdit* lineEdit_matrixA[matrixA_size];
    for (int x = 0; x < matrixA_size; x++) {
        lineEdit_matrixA[x] = new QLineEdit();
    }

    ui->gridLayout->addWidget(ui->label_enterMatrixA_entry, 0, 0, 1, matrixA_cols);
    ui->gridLayout->addWidget(ui->label_matrixA_size_entry, matrixA_rows+1, 0, 1, matrixA_cols);

    for (rowNum = 1; rowNum < matrixA_rows+1; rowNum++) {
        for(colNum = 0; colNum < matrixA_cols; colNum++) {
            ui->gridLayout->addWidget(lineEdit_matrixA[i], rowNum, colNum);
            i++;
        }

    }

    ui->frame_6->setStyleSheet("#frame_6 QLineEdit { border-radius: 7px; "
                               "max-width: 300px; min-height: 50px; "
                               "font: bold 25px \"DM Sans\" ;qproperty-alignment: AlignCenter; "
                               "margin: 5px 2px;}");

}

matrixCalcu::~matrixCalcu()
{
    delete ui;
}
