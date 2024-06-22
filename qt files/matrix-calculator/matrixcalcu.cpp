#include "matrixcalcu.h"
#include "ui_matrixcalcu.h"
#include <iostream>

matrixCalcu::matrixCalcu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::matrixCalcu)
{
    ui->setupUi(this);

    setWindowTitle("Matrix Calculator");

    /**

    **/

    // Sidebar button functionalities
    connect(ui->button_addition, SIGNAL(clicked()), this, SLOT(switch_page_simpleOperation_1()));
    connect(ui->button_subtraction, SIGNAL(clicked()), this, SLOT(switch_page_simpleOperation_1()));
    connect(ui->button_multiplication, SIGNAL(clicked()), this, SLOT(switch_page_simpleOperation_1()));
    connect(ui->button_transpose, SIGNAL(clicked()), this, SLOT(switch_page_advancedOperation_1()));
    connect(ui->button_determinant, SIGNAL(clicked()), this, SLOT(switch_page_advancedOperation_1()));
    connect(ui->button_inverse, SIGNAL(clicked()), this, SLOT(switch_page_advancedOperation_1()));
    connect(ui->button_ref, SIGNAL(clicked()), this, SLOT(switch_page_advancedOperation_1()));
    connect(ui->button_rref, SIGNAL(clicked()), this, SLOT(switch_page_advancedOperation_1()));
    connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(clear_matrixA_size()));
    connect(ui->pushButton_clear_2, SIGNAL(clicked()), this, SLOT(clear_matrixA_size_2()));
    connect(ui->pushButton_enter_size, SIGNAL(clicked()), this, SLOT(enter_simpleOperation_1()));
    connect(ui->pushButton_enter_size_2, SIGNAL(clicked()), this, SLOT(enter_advancedOperation_1()));
    connect(ui->pushButton_enter_matrixA, SIGNAL(clicked()), this, SLOT(enter_simpleOperation_2()));


}

matrixCalcu::~matrixCalcu()
{
    delete ui;
}

void matrixCalcu::switch_page_simpleOperation_1()
{
    clear_matrixA_size();
    ui->stackedWidget->setCurrentWidget(ui->page_simpleOperation_1);
}

void matrixCalcu::switch_page_advancedOperation_1()
{
    clear_matrixA_size_2();
    ui->stackedWidget->setCurrentWidget(ui->page_advancedOperation_1);
}

void matrixCalcu::clear_matrixA_size()
{
    ui->lineEdit_matrixA_rows->clear();
    ui->lineEdit_matrixA_cols->clear();
    ui->lineEdit_matrixB_rows->clear();
    ui->lineEdit_matrixB_cols->clear();
}

void matrixCalcu::clear_matrixA_size_2()
{
    ui->lineEdit_matrixA_rows_2->clear();
    ui->lineEdit_matrixA_cols_2->clear();
}

void matrixCalcu::enter_simpleOperation_1()
{
    // For Matrix A Entries
    // Placeholder for matrix A size
    int matrixA_rows = to_int(ui->lineEdit_matrixA_rows->text()); int matrixA_cols = to_int(ui->lineEdit_matrixA_cols->text());
    int matrixA_size = matrixA_rows*matrixA_cols;
    int rowNumA = 0; int colNumA = 0; int iA = 0;
    QLineEdit* lineEdit_matrixA[matrixA_size];
    for (int x = 0; x < matrixA_size; x++) {
        lineEdit_matrixA[x] = new QLineEdit();
    }

    ui->gridLayout->addWidget(ui->label_enterMatrixA_entry, 0, 0, 1, matrixA_cols);
    ui->gridLayout->addWidget(ui->label_matrixA_size_entry, matrixA_rows+1, 0, 1, matrixA_cols);

    for (rowNumA = 1; rowNumA < matrixA_rows+1; rowNumA++) {
        for(colNumA = 0; colNumA < matrixA_cols; colNumA++) {
            ui->gridLayout->addWidget(lineEdit_matrixA[iA], rowNumA, colNumA);
            iA++;
        }

    }

    ui->frame_6->setStyleSheet("#frame_6 QLineEdit { border-radius: 7px; "
                               "max-width: 300px; min-height: 50px; "
                               "font: bold 25px \"DM Sans\" ;qproperty-alignment: AlignCenter; "
                               "margin: 5px 2px;}");

    ui->stackedWidget->setCurrentWidget(ui->page_enterMatrixA);
}

void matrixCalcu::enter_simpleOperation_2()
{
    // For Matrix B Entries
    // Placeholder for matrix B size
    int matrixB_rows = to_int(ui->lineEdit_matrixB_rows->text()); int matrixB_cols = to_int(ui->lineEdit_matrixB_rows->text());
    int matrixB_size = matrixB_rows*matrixB_cols;
    int rowNumB = 0; int colNumB = 0; int iB = 0;
    QLineEdit* lineEdit_matrixB[matrixB_size];
    for (int x = 0; x < matrixB_size; x++) {
        lineEdit_matrixB[x] = new QLineEdit();
    }

    ui->gridLayout_2->addWidget(ui->label_enterMatrixB_entry, 0, 0, 1, matrixB_cols);
    ui->gridLayout_2->addWidget(ui->label_matrixB_size_entry, matrixB_rows+1, 0, 1, matrixB_cols);

    for (rowNumB = 1; rowNumB < matrixB_rows+1; rowNumB++) {
        for(colNumB = 0; colNumB < matrixB_cols; colNumB++) {
            ui->gridLayout_2->addWidget(lineEdit_matrixB[iB], rowNumB, colNumB);
            iB++;
        }

    }

    ui->frame_9->setStyleSheet("#frame_9 QLineEdit { border-radius: 7px; "
                               "max-width: 300px; min-height: 50px; "
                               "font: bold 25px \"DM Sans\" ;qproperty-alignment: AlignCenter; "
                               "margin: 5px 2px;}");
    ui->stackedWidget->setCurrentWidget(ui->page_enterMatrixB);
}

void matrixCalcu::enter_advancedOperation_1()
{
    // For Matrix A advanced operation Entries
    // Placeholder for matrix A size
    int matrixA_rows = to_int(ui->lineEdit_matrixA_rows_2->text()); int matrixA_cols = to_int(ui->lineEdit_matrixA_cols_2->text());
    int matrixA_size = matrixA_rows*matrixA_cols;
    int rowNumA = 0; int colNumA = 0; int iA = 0;
    QLineEdit* lineEdit_matrixA[matrixA_size];
    for (int x = 0; x < matrixA_size; x++) {
        lineEdit_matrixA[x] = new QLineEdit();
    }

    ui->gridLayout_5->addWidget(ui->label_enterMatrixA_entry_advanced, 0, 0, 1, matrixA_cols);
    ui->gridLayout_5->addWidget(ui->label_matrixA_size_entry_advanced, matrixA_rows+1, 0, 1, matrixA_cols);

    for (rowNumA = 1; rowNumA < matrixA_rows+1; rowNumA++) {
        for(colNumA = 0; colNumA < matrixA_cols; colNumA++) {
            ui->gridLayout_5->addWidget(lineEdit_matrixA[iA], rowNumA, colNumA);
            iA++;
        }

    }

    ui->frame_10->setStyleSheet("#frame_10 QLineEdit { border-radius: 7px; "
                               "max-width: 300px; min-height: 50px; "
                               "font: bold 25px \"DM Sans\" ;qproperty-alignment: AlignCenter; "
                               "margin: 5px 2px;}");

    ui->stackedWidget->setCurrentWidget(ui->page_enterMatrixA_advanced);
}

int matrixCalcu::to_int(QString text)
{
    bool ok;
    int num = text.toInt(&ok);

    // Throw exception here
    if (!ok) {
        std::cout << "Bad Input!";
    }
    return num;
}



