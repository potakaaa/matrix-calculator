#include "matrixcalcu.h"
#include "ui_matrixcalcu.h"
#include "exceptions.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMessageBox>

#include <vector>

std::vector<QLineEdit*> lineEdit_matrixA;
std::vector<QLineEdit*> lineEdit_matrixB;
std::vector<QLineEdit*> lineEdit_matrixA_2;

matrixCalcu::matrixCalcu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::matrixCalcu)
    , buttonGroup(new QButtonGroup(this))
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
    connect(ui->pushButton_clear_matrixA, SIGNAL(clicked()), this, SLOT(clear_matrixA_entries()));
    connect(ui->pushButton_clear_matrixB_2, SIGNAL(clicked()), this, SLOT(clear_matrixB_entries()));
    connect(ui->pushButton_clear_matrixA_advanced, SIGNAL(clicked()), this, SLOT(clear_matrixA_2_entries()));

    buttonGroup->addButton(ui->button_addition);
    buttonGroup->addButton(ui->button_subtraction);
    buttonGroup->addButton(ui->button_multiplication);
    buttonGroup->addButton(ui->button_transpose);
    buttonGroup->addButton(ui->button_determinant);
    buttonGroup->addButton(ui->button_inverse);
    buttonGroup->addButton(ui->button_ref);
    buttonGroup->addButton(ui->button_rref);

    // Set buttons as checkable
    foreach(QAbstractButton *button, buttonGroup->buttons()) {
        connect(button, &QPushButton::toggled, this, &matrixCalcu::updateButtonStyles);
    }

    updateButtonStyles();

}

matrixCalcu::~matrixCalcu()
{
    delete ui;
}

void matrixCalcu::updateButtonStyles()
{
    QString checkedStyle = "color: black; background-color: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 #F6A5CC, stop:1 #B02E6D);";
    QString uncheckedStyle = "";

    foreach(QAbstractButton *button, buttonGroup->buttons()) {
        button->setStyleSheet(button->isChecked() ? checkedStyle : uncheckedStyle);
    }
}

void matrixCalcu::switch_page_simpleOperation_1()
{
    clear_matrixA_size();
    remove_existingMatrix(ui->gridLayout);
    remove_existingMatrix(ui->gridLayout_2);
    remove_existingMatrix(ui->gridLayout_5);
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

void matrixCalcu::clear_matrixA_entries()
{
    for (int x = 0; x < lineEdit_matrixA.size(); x++) {
        lineEdit_matrixA[x]->clear();
    }
}

void matrixCalcu::clear_matrixB_entries()
{
    for (int x = 0; x < lineEdit_matrixB.size(); x++) {
        lineEdit_matrixB[x]->clear();
    }
}

void matrixCalcu::clear_matrixA_2_entries()
{
    for (int x = 0; x < lineEdit_matrixA_2.size(); x++) {
        lineEdit_matrixA_2[x]->clear();
    }
}

void matrixCalcu::remove_existingMatrix(QGridLayout* gridLayout)
{

    // Check if the grid layout is not null
    if (!gridLayout)
        return;

    // Iterate over all items in the grid layout
    while (QLayoutItem* item = gridLayout->takeAt(0)) {
        // If the item is a widget, remove it from the layout
        if (QWidget* widget = item->widget()) {
            gridLayout->removeWidget(widget);
            widget->setParent(nullptr); // Remove the widget from the layout without deleting it
        }
        // Delete the layout item
        delete item;
    }
}

void matrixCalcu::enter_simpleOperation_1()
{
    // For Matrix A Entries
    // Placeholder for matrix A size
    remove_existingMatrix(ui->gridLayout);
    try {
        QString a_rows = ui->lineEdit_matrixA_rows->text(); QString a_cols = ui->lineEdit_matrixA_cols->text();
        QString b_rows = ui->lineEdit_matrixB_rows->text(); QString b_cols = ui->lineEdit_matrixB_cols->text();
        int matrixA_rows = to_int(ui->lineEdit_matrixA_rows->text()); int matrixA_cols = to_int(ui->lineEdit_matrixA_cols->text());
        int matrixB_rows = to_int(ui->lineEdit_matrixB_rows->text()); int matrixB_cols = to_int(ui->lineEdit_matrixB_cols->text());
        int matrixA_size = matrixA_rows*matrixA_cols;

        if (matrixA_rows > 6 || matrixA_cols > 6 || matrixB_rows > 6 || matrixB_cols > 6) {
            QString message = "Matrix size is limited to 6x6 only!";
            throw SizeTooLargeException(message);
            showError(message);
        } else if (!int_validator(a_rows) || !int_validator(a_cols) || !int_validator(b_rows) || !int_validator(b_cols)) {
            QString message = "Matrix entry is not a number!";
            throw NonNumericException(message);
            showError(message);
        }

        int rowNumA = 0; int colNumA = 0; int iA = 0;
        lineEdit_matrixA.resize(matrixA_size);

        ui->gridLayout->addWidget(ui->label_enterMatrixA_entry, 0, 0, 1, matrixA_cols);
        ui->gridLayout->addWidget(ui->label_matrixA_size_entry, matrixA_rows+1, 0, 1, matrixA_cols);

        for (int x = 0; x < matrixA_size; x++) {
            lineEdit_matrixA[x] = new QLineEdit();
        }

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

        if (ui->button_addition->isChecked() || ui->button_subtraction->isChecked()) {
            if (a_rows == b_rows && a_cols == b_cols) {

                ui->stackedWidget->setCurrentWidget(ui->page_enterMatrixA);
            } else {
                showError("Matrix should be equivalent");
            }
        } else if (ui->button_multiplication->isChecked()) {
            if (a_cols == b_rows) {

                ui->stackedWidget->setCurrentWidget(ui->page_enterMatrixA);
            } else {
                showError("Matrices are not compatible!");
            }
        }
    } catch (SizeTooLargeException e) {
        qDebug() << "Caught SizeTooLargeException:" << e.message();
        showError(e.message());
        ui->stackedWidget->setCurrentWidget(ui->page_simpleOperation_1);
    } catch(const NonNumericException e) {
        qDebug() << "Caught NonNumericException:" << e.message();
        showError(e.message());
        ui->stackedWidget->setCurrentWidget(ui->page_simpleOperation_1);
    }

}

void matrixCalcu::enter_simpleOperation_2()
{
    // For Matrix B Entries
    // Placeholder for matrix B size
    remove_existingMatrix(ui->gridLayout_2);
    try {
        int matrixB_rows = to_int(ui->lineEdit_matrixB_rows->text()); int matrixB_cols = to_int(ui->lineEdit_matrixB_rows->text());
        int matrixB_size = matrixB_rows*matrixB_cols;

        int rowNumB = 0; int colNumB = 0; int iB = 0;
        lineEdit_matrixB.resize(matrixB_size);
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
    } catch (SizeTooLargeException e) {
        qDebug() << "Caught SizeTooLargeException:" << e.message();
        showError(e.message());
        ui->stackedWidget->setCurrentWidget(ui->page_simpleOperation_1);
    } catch(const NonNumericException e) {
        qDebug() << "Caught NonNumericException:" << e.message();
        showError(e.message());
        ui->stackedWidget->setCurrentWidget(ui->page_simpleOperation_1);
    }
}

void matrixCalcu::enter_advancedOperation_1()
{
    // For Matrix A advanced operation Entries
    // Placeholder for matrix A size
    remove_existingMatrix(ui->gridLayout_5);
    try {
        QString a_rows = ui->lineEdit_matrixA_rows_2->text(); QString a_cols = ui->lineEdit_matrixA_cols_2->text();
        int matrixA_rows = to_int(ui->lineEdit_matrixA_rows_2->text()); int matrixA_cols = to_int(ui->lineEdit_matrixA_cols_2->text());
        int matrixA_size = matrixA_rows*matrixA_cols;

        if (matrixA_rows > 6 || matrixA_cols > 6) {
            QString message = "Matrix size is limited to 6x6 only!";
            throw SizeTooLargeException(message);
            showError(message);
        } else if (!int_validator(a_rows) || !int_validator(a_cols)) {
            QString message = "Matrix entry is not a number!";
            throw NonNumericException(message);
            showError(message);
        }

        int rowNumA = 0; int colNumA = 0; int iA = 0;
        lineEdit_matrixA_2.resize(matrixA_size);
        for (int x = 0; x < matrixA_size; x++) {
            lineEdit_matrixA_2[x] = new QLineEdit();
        }

        ui->gridLayout_5->addWidget(ui->label_enterMatrixA_entry_advanced, 0, 0, 1, matrixA_cols);
        ui->gridLayout_5->addWidget(ui->label_matrixA_size_entry_advanced, matrixA_rows+1, 0, 1, matrixA_cols);

        for (rowNumA = 1; rowNumA < matrixA_rows+1; rowNumA++) {
            for(colNumA = 0; colNumA < matrixA_cols; colNumA++) {
                ui->gridLayout_5->addWidget(lineEdit_matrixA_2[iA], rowNumA, colNumA);
                iA++;
            }

        }

        ui->frame_10->setStyleSheet("#frame_10 QLineEdit { border-radius: 7px; "
                                    "max-width: 300px; min-height: 50px; "
                                    "font: bold 25px \"DM Sans\" ;qproperty-alignment: AlignCenter; "
                                    "margin: 5px 2px;}");


        if (ui->button_determinant->isChecked() || ui->button_inverse->isChecked()) {
            if (a_rows == a_cols) {
                ui->stackedWidget->setCurrentWidget(ui->page_enterMatrixA_advanced);
            } else {
                showError("Matrix is not square!");
            }
        } else {
            ui->stackedWidget->setCurrentWidget(ui->page_enterMatrixA_advanced);
        }

    } catch (SizeTooLargeException e) {
        qDebug() << "Caught SizeTooLargeException:" << e.message();
        showError(e.message());
        ui->stackedWidget->setCurrentWidget(ui->page_advancedOperation_1);
    } catch(const NonNumericException e) {
        qDebug() << "Caught NonNumericException:" << e.message();
        showError(e.message());
        ui->stackedWidget->setCurrentWidget(ui->page_advancedOperation_1);
    }
}


int matrixCalcu::to_int(QString text)
{
    int num;

    bool ok;
    num = text.toInt(&ok);
    return num;

}

bool matrixCalcu::int_validator(QString text)
{
    bool flag = false;
    QRegularExpression re("[0-9]");  // a digit (\d), zero or more times (*)
    QRegularExpressionMatch match = re.match(text);
    if (match.hasMatch()) {
        qDebug() << "all digits";
        flag = true;
    } else {
        throw NonNumericException("Input is not numeric!");
    }
    return flag;
}

bool matrixCalcu::size_validator(int num) {
    bool flag = true;
    if (num > 6) {
        throw SizeTooLargeException("Matrix is limited to 6x6 only!");
    }
    return flag;
}

void matrixCalcu::showError(const QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Matrix Calculator");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText(message);
    msgBox.exec();
}








