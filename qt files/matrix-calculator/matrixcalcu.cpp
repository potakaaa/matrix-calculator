#include "matrixcalcu.h"
#include "ui_matrixcalcu.h"
#include "exceptions.h"
#include "gauss.h"
#include "inverse.h"
#include "add_text.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMessageBox>
#include <QString>
#include <QPixmap>
#include <QSettings>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QTextCursor>
#include <QDebug>
#include <QFileDialog>
#include <QRandomGenerator>
#include <vector>
#include <QStyle>

std::vector<QLineEdit*> lineEdit_matrixA;
std::vector<QLineEdit*> lineEdit_matrixB;
std::vector<QLineEdit*> lineEdit_matrixA_2;

std::vector<QLineEdit*> lineEdit_matrixResult;
std::vector<std::vector<double>> matrixA;
std::vector<std::vector<double>> matrixB;
std::vector<std::vector<double>> answer;
int matrixA_rows;
int matrixA_cols;
int matrixB_rows;
int matrixB_cols;
bool inverse_flag;
double det;


matrixCalcu::matrixCalcu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::matrixCalcu)
    , buttonGroup(new QButtonGroup(this))
{
    ui->setupUi(this);
    QPixmap pix(":/logo/resource/CS CALC.png");
    const int sideLength = ui->label_logo->width();
    QPixmap scaled = pix.scaled(sideLength, sideLength, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_logo->setPixmap(scaled);

    QString s1 = "Matrix"; QString s2 = "Calculator"; QString sp = " ";

    spec_string txt1(s1); spec_string txt2(s2); spec_string txt_result;
    txt_result = s1 + sp + s2;
    ui->label_welcome->setText(txt_result.to_qstring(txt_result));


    setWindowTitle("Matrix Calculator");

    ui->frame_2->setStyleSheet("border: none;");
    ui->frame->setStyleSheet("border: none;");

    /**



    **/

    ui->stackedWidget->setCurrentWidget(ui->page_home);

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
    connect(ui->pushButton_enter_matrixB_2, SIGNAL(clicked()), this, SLOT(resultMatrix()));
    connect(ui->pushButton_enter_matrixA_advanced, SIGNAL(clicked()), this, SLOT(resultMatrix_2()));
    connect(ui->pushButton_print_matrixResult, SIGNAL(clicked()), this, SLOT(on_printButton_clicked()));
    connect(ui->pushButton_clear_matrixResult, SIGNAL(clicked()), this, SLOT(home_button()));


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

void matrixCalcu::resetButtons() {
    foreach(QAbstractButton *button, buttonGroup->buttons()) {
        button->setChecked(false);
        button->setStyleSheet("");
        button->repaint();

    }
}

void matrixCalcu::switch_page_simpleOperation_1()
{
    clear_matrixA_size();
    remove_existingMatrix(ui->gridLayout);
    remove_existingMatrix(ui->gridLayout_2);
    remove_existingMatrix(ui->gridLayout_5);
    remove_existingMatrix(ui->gridLayout_3);

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



void matrixCalcu::enter_simpleOperation_1()
{
    // For Matrix A Entries
    // Placeholder for matrix A size
    remove_existingMatrix(ui->gridLayout);
    try {
        QString a_rows = ui->lineEdit_matrixA_rows->text(); QString a_cols = ui->lineEdit_matrixA_cols->text();
        QString b_rows = ui->lineEdit_matrixB_rows->text(); QString b_cols = ui->lineEdit_matrixB_cols->text();
        matrixA_rows = to_int(ui->lineEdit_matrixA_rows->text()); matrixA_cols = to_int(ui->lineEdit_matrixA_cols->text());
        matrixB_rows = to_int(ui->lineEdit_matrixB_rows->text()); matrixB_cols = to_int(ui->lineEdit_matrixB_cols->text());
        int matrixA_size = matrixA_rows*matrixA_cols;
        ui->label_matrixA_size_entry->setText(a_rows + " x " + a_cols);
        ui->label_matrixB_size_entry->setText(b_rows + " x " + b_cols);

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
    matrixA = extractLineEditText(lineEdit_matrixA, matrixA_rows, matrixA_cols);
    // For Matrix B Entries
    // Placeholder for matrix B size
    remove_existingMatrix(ui->gridLayout_2);
    try {
        if (check_emptyMatrix(lineEdit_matrixA)) {
            throw InputIsEmpty("Matrix input is empty!");
            showError("Matrix input is empty!");
        }

        matrixB_rows = to_int(ui->lineEdit_matrixB_rows->text()); matrixB_cols = to_int(ui->lineEdit_matrixB_cols->text());
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
    } catch(const InputIsEmpty e) {
        qDebug() << "Caught InputIsEmpty:" << e.message();
        showError(e.message());
    }
}

void matrixCalcu::enter_advancedOperation_1()
{
    // For Matrix A advanced operation Entries
    // Placeholder for matrix A size
    remove_existingMatrix(ui->gridLayout_5);
    try {
        QString a_rows = ui->lineEdit_matrixA_rows_2->text(); QString a_cols = ui->lineEdit_matrixA_cols_2->text();
        matrixA_rows = to_int(ui->lineEdit_matrixA_rows_2->text()); matrixA_cols = to_int(ui->lineEdit_matrixA_cols_2->text());
        int matrixA_size = matrixA_rows*matrixA_cols;
        ui->label_matrixA_size_entry_advanced->setText(a_rows + " x " + a_cols);

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
    QRegularExpression re("[0-9]");
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
    msgBox.setWindowIcon(QIcon(":/logo/resource/CS CALC.png"));
    msgBox.exec();
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

bool matrixCalcu::check_emptyMatrix(std::vector<QLineEdit*> lineEdit_vector)
{
    bool flag = false;
    for (int i = 0; i < lineEdit_vector.size(); i++) {
        if (lineEdit_vector[i]->text().isEmpty()) {
            flag = true;
            break;
        }
    }
    return flag;
}

void matrixCalcu::resultMatrix()
{
    try {
        if (check_emptyMatrix(lineEdit_matrixB)) {
            qDebug() << "Empty matrix error here";
            throw InputIsEmpty("Matrix input is empty!");
            showError("Matrix input is empty!");

        } else {
            bool validator = checkMatrixEntries_ifNumeric(lineEdit_matrixB);
            if (validator) {
                ui->stackedWidget->setCurrentWidget(ui->page_matrixResult);
            }
        }
    } catch(const InputIsEmpty e) {
        qDebug() << "Caught InputIsEmpty:" << e.message();
        showError(e.message());
    } catch(const NonNumericException e) {
        qDebug() << "Caught NonNumericException:" << e.message();
        showError(e.message());

    }

    if (ui->button_addition->isChecked()){
        addition();
    }
    if (ui->button_subtraction->isChecked()){
        subtraction();
    }
    if (ui->button_multiplication->isChecked()){
        multiplication();
    }

}

void matrixCalcu::resultMatrix_2()
{
    try {
        if (check_emptyMatrix(lineEdit_matrixA_2)) {
            qDebug() << "Empty matrix error here";
            throw InputIsEmpty("Matrix input is empty!");
            showError("Matrix input is empty!");

        } else {
            qDebug() << "0.7";
            bool validator = checkMatrixEntries_ifNumeric(lineEdit_matrixA_2);
             if (validator) {
                qDebug() << "0.8";
                 if (ui->button_ref->isChecked() || ui->button_rref->isChecked()){
                    ui->label_matrixResult_size->setText(ui->lineEdit_matrixA_rows_2->text() + " x " + ui->lineEdit_matrixA_cols_2->text());
                    remove_existingMatrix(ui->gridLayout_3);
                    RowEchelon();

                 }
                 if (ui->button_inverse->isChecked()){
                     inverse_flag = false;
                     ui->label_matrixResult_size->setText(ui->lineEdit_matrixA_rows_2->text() + " x " + ui->lineEdit_matrixA_cols_2->text());
                     remove_existingMatrix(ui->gridLayout_3);
                     inverse();

                 }
                 if (ui->button_transpose->isChecked()) {
                     int row_num = 0; int col_num = 0; int counter = 0;
                     remove_existingMatrix(ui->gridLayout_3);

                     int answer_rows = to_int(ui->lineEdit_matrixA_rows_2->text()); int answer_cols = to_int(ui->lineEdit_matrixA_cols_2->text());
                     answer = extractLineEditText(lineEdit_matrixA_2, answer_rows, answer_cols);
                     matrixA = extractLineEditText(lineEdit_matrixA_2, answer_rows, answer_cols);

                     qDebug() << "0.9";

                     // Print matrixA details to debug its initialization
                     qDebug() << "Matrix A:";
                     for (const auto& row : answer) {
                         qDebug() << row;
                     }

                     qDebug() << "Matrix A Rows: " << ui->lineEdit_matrixA_rows_2->text() << " Matrix A Cols: " << ui->lineEdit_matrixA_cols_2->text();

                     std::vector<std::vector<double>> matrix_Transposed;
                     qDebug() << "0.88";

                     // Check if matrixA is empty
                     if (answer.empty() || answer[0].empty()) {
                         qDebug() << "Matrix A is empty or not initialized properly.";
                         return;
                     }

                     matrix_Transposed = transpose(answer);
                     qDebug() << "0.89";

                     // Ensure the transposed matrix is correctly formed
                     if (matrix_Transposed.empty() || matrix_Transposed[0].empty()) {
                         qDebug() << "Transposed matrix is empty or not initialized properly.";
                         return;
                     }
                     answer = matrix_Transposed;

                     qDebug() << "Transposed Matrix:";
                     for (const auto& row : matrix_Transposed) {
                         qDebug() << row;
                     }

                     ui->gridLayout_3->addWidget(ui->label_matrixResult, 0, 0, 1, answer_rows);
                     ui->gridLayout_3->addWidget(ui->label_matrixResult_size, answer_cols + 1, 0, 1, answer_rows);
                     QString txt = ui->lineEdit_matrixA_rows_2->text() + " x " + ui->lineEdit_matrixA_cols_2->text();
                     QString rev = ""; int txt_size = txt.length(); QString f = reverseString(txt, txt_size, rev);
                     ui->label_matrixResult_size->setText(f);

                     qDebug() << "0.99";
                     qDebug() << "Matrix A Rows: " << answer_cols << " Matrix A Cols: " << answer_rows;
                     int size = answer_rows * answer_cols;

                     lineEdit_matrixResult.resize(size);
                     for (int x = 0; x < size; x++) {
                         lineEdit_matrixResult[x] = new QLineEdit();
                         lineEdit_matrixResult[x]->setReadOnly(true);
                     }

                     qDebug() << "1";
                     int layout_row;
                     for (int row_num = 0, layout_row = 1; row_num < matrix_Transposed.size(); row_num++, layout_row++) {
                         for (int col_num = 0; col_num < matrix_Transposed[0].size(); col_num++) {
                             if (counter >= size) {
                                 qDebug() << "Counter out of bounds: " << counter << " Size: " << size;
                                 return; // Exiting the function since counter is out of bounds
                             }

                             // Add QLineEdit to the layout
                             ui->gridLayout_3->addWidget(lineEdit_matrixResult[counter], layout_row, col_num);

                             // Set text to the QLineEdit
                             lineEdit_matrixResult[counter]->setText(QString::number(matrix_Transposed[row_num][col_num]));

                             counter++;
                         }
                     }

                     qDebug() << "2";
                 } if (ui->button_determinant->isChecked()) {
                     int row_temp = matrixA_rows; int col_temp = matrixA_cols;
                     std::vector<std::vector<double>> temp = extractLineEditText(lineEdit_matrixA_2, row_temp, col_temp);
                     double determinant_temp = determinant(temp);
                     determinant_output(determinant_temp);
                     matrixA = temp;
                     det = determinant_temp;
                 }

                 ui->frame_11->setStyleSheet("#frame_11 QLineEdit { border-radius: 7px; "
                                             "max-width: 300px; min-height: 50px; "
                                             "font: bold 25px \"DM Sans\" ;qproperty-alignment: AlignCenter; "
                                             "margin: 5px 2px;}");

                 qDebug() << inverse_flag;
                 if (inverse_flag) {
                     ui->stackedWidget->setCurrentWidget(ui->page_matrixResult);
                 } else {

                 }

             }

        }
    } catch(const InputIsEmpty e) {
        qDebug() << "Caught InputIsEmpty:" << e.message();
        showError(e.message());
    } catch(const NonNumericException e) {
        qDebug() << "Caught NonNumericException:" << e.message();
        showError(e.message());

    }
}

bool matrixCalcu::checkMatrixEntries_ifNumeric(std::vector<QLineEdit *> lineEdit_vector)
{
    bool flag = true;
    for (int i = 0; i < lineEdit_vector.size(); i++) {
        if (!int_validator(lineEdit_vector[i]->text())) {
            QString message = "Matrix entry is not a number!";
            throw NonNumericException(message);
            showError(message);
            flag = false;
            break;
        }
    }
    return flag;
}

#include <QDebug>
#include <vector>

std::vector<std::vector<double>> matrixCalcu::transpose(const std::vector<std::vector<double>> &matrix)
{
    qDebug() << "4";
    inverse_flag = true;
    // Check if the matrix is empty
    if (matrix.empty()) {
        qDebug() << "Matrix is empty";
        return {};  // Return an empty matrix
    }

    int rows = matrix.size();

    // Check if the first row is empty
    if (matrix[0].empty()) {
        qDebug() << "First row is empty";
        return {};  // Return an empty matrix
    }

    int cols = matrix[0].size();
    std::vector<std::vector<double>> transposed(cols, std::vector<double>(rows));
    qDebug() << "5";

    // Print the original matrix
    qDebug() << "Original Matrix:";
    for (int i = 0; i < rows; i++) {
        QString rowString;
        for (int j = 0; j < cols; j++) {
            rowString += QString::number(matrix[i][j]) + " ";
        }
        qDebug() << rowString;
    }

    // Transpose the matrix // j=1
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }

    qDebug() << "6";

    // Print the transposed matrix
    qDebug() << "Transposed Matrix:";
    for (int i = 0; i < cols; i++) {
        QString rowString;
        for (int j = 0; j < rows; j++) {
            rowString += QString::number(transposed[i][j]) + " ";
        }
        qDebug() << rowString;
    }

    return transposed;
}


std::vector<std::vector<double>> matrixCalcu::extractLineEditText(std::vector<QLineEdit *> lineEdits, int rows, int cols)
{
    std::vector<std::vector<double>> result(rows, std::vector<double>(cols));

    if (rows * cols != lineEdits.size()) {
        qDebug() << "Mismatch between matrix dimensions and number of QLineEdit widgets.";
        return {}; // Return an empty matrix or handle the error as needed
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int index = i * cols + j;
            QString text = lineEdits[index]->text();
            bool conversionOk = false;
            double number = text.toDouble(&conversionOk);

            if (conversionOk) {
                result[i][j] = number;
            } else {
                // Handle conversion failure if needed
                result[i][j] = 0.0; // Default value
            }
        }
    }

    return result;
}

double matrixCalcu::determinant(const std::vector<std::vector<double> > &matrix)
{
    int n = matrix.size();

    if (n == 1) {
        return matrix[0][0];
    }

    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    double det = 0;
    for (int i = 0; i < n; ++i) {
        std::vector<std::vector<double>> submatrix(n - 1, std::vector<double>(n - 1));
        for (int j = 1; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (k < i) {
                    submatrix[j - 1][k] = matrix[j][k];
                } else if (k > i) {
                    submatrix[j - 1][k - 1] = matrix[j][k];
                }
            }
        }
        det += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * determinant(submatrix);
    }

    return det;
}

void matrixCalcu::addition()
{
    matrixB = extractLineEditText(lineEdit_matrixB, matrixB_rows, matrixB_cols);
    qDebug() << "1";
    std::vector<std::vector<double>> result;
    result.resize(matrixA.size());
    for (size_t i = 0; i < result.size(); ++i) {
        result[i].resize(matrixA[0].size());
    }
    qDebug() << "2";
    for (size_t i = 0; i < matrixA.size(); i++) {
        for (size_t j = 0; j < matrixA[0].size(); j++) {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
    qDebug() << "2.2";
    int rowNumA = 0; int colNumA = 0; int iA = 0;

    answer = result;

    lineEdit_matrixResult.resize(matrixA_rows*matrixA_cols);
    qDebug() << "2.4";
    qDebug() << "matrix size: " << matrixA_rows*matrixA_cols;
    for (int x = 0; x < lineEdit_matrixResult.size(); x++) {
        lineEdit_matrixResult[x] = new QLineEdit();
    }
    ui->gridLayout_3->addWidget(ui->label_matrixResult, 0, 0, 1, matrixA_cols);
    ui->gridLayout_3->addWidget(ui->label_matrixResult_size, matrixA_rows+1, 0, 1, matrixA_cols);
    ui->label_matrixResult_size->setText(ui->lineEdit_matrixA_rows->text() + " x " + ui->lineEdit_matrixA_cols->text());
    qDebug() << matrixA.size();
    int layout_row = 1;
    for (rowNumA = 0, layout_row = 1; rowNumA < matrixA_rows; rowNumA++, layout_row++) {
        qDebug() << "2.8";
        for(colNumA = 0; colNumA < matrixA_cols; colNumA++) {
            ui->gridLayout_3->addWidget(lineEdit_matrixResult[iA], layout_row, colNumA);
            lineEdit_matrixResult[iA]->setText(QString::number(result[rowNumA][colNumA]));
            lineEdit_matrixResult[iA]->setReadOnly(true);
            lineEdit_matrixResult[iA]->setAlignment(Qt::AlignHCenter);
            iA++;
        }

    }
    ui->frame_11->setStyleSheet("#frame_11 QLineEdit { border-radius: 7px; "
                                "max-width: 300px; min-height: 50px; "
                                "font: bold 25px \"DM Sans\" ;qproperty-alignment: AlignCenter; "
                                "margin: 5px 2px;}");
    qDebug() << "4";
}

void matrixCalcu::subtraction()
{
    matrixB = extractLineEditText(lineEdit_matrixB, matrixB_rows, matrixB_cols);
    std::vector<std::vector<double>> result;
    result.resize(matrixA.size());
    for (size_t i = 0; i < result.size(); ++i) {
        result[i].resize(matrixA[0].size());
    }

    for (size_t i = 0; i < matrixA.size(); i++) {
        for (size_t j = 0; j < matrixA[0].size(); j++) {
            result[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }

    answer = result;
    int rowNumA = 0; int colNumA = 0; int iA = 0;
    lineEdit_matrixResult.resize(matrixA_rows*matrixA_cols);

    for (int x = 0; x < matrixA_rows * matrixA_cols; x++) {
        lineEdit_matrixResult[x] = new QLineEdit();
    }
    ui->gridLayout_3->addWidget(ui->label_matrixResult, 0, 0, 1, matrixA_cols);
    ui->gridLayout_3->addWidget(ui->label_matrixResult_size, matrixA_rows+1, 0, 1, matrixA_cols);
    ui->label_matrixResult_size->setText(ui->lineEdit_matrixA_rows->text() + " x " + ui->lineEdit_matrixA_cols->text());
    qDebug() << matrixA.size();
    int layout_row = 1;
    for (rowNumA = 0, layout_row = 1; rowNumA < matrixA_rows; rowNumA++, layout_row++) {
        for(colNumA = 0; colNumA < matrixA_cols; colNumA++) {
            ui->gridLayout_3->addWidget(lineEdit_matrixResult[iA], layout_row, colNumA);
            lineEdit_matrixResult[iA]->setText(QString::number(result[rowNumA][colNumA]));
            lineEdit_matrixResult[iA]->setReadOnly(true);
            lineEdit_matrixResult[iA]->setAlignment(Qt::AlignHCenter);
            iA++;
        }

    }

    ui->frame_11->setStyleSheet("#frame_11 QLineEdit { border-radius: 7px; "
                                "max-width: 300px; min-height: 50px; "
                                "font: bold 25px \"DM Sans\" ;qproperty-alignment: AlignCenter; "
                                "margin: 5px 2px;}");
}

void matrixCalcu::multiplication() {
    // Ensure matrix dimensions are compatible for multiplication
    if (matrixA_cols != matrixB_rows) {
        qDebug() << "Matrix dimensions are not compatible for multiplication!";
        return;
    }

    std::vector<std::vector<double>> result(matrixA_rows, std::vector<double>(matrixB_cols, 0.0));

    // Fill matrixB with values
    matrixB = extractLineEditText(lineEdit_matrixB, matrixB_rows, matrixB_cols);
    qDebug() << "Matrix B extracted";

    // Matrix multiplication
    for (int i = 0; i < matrixA_rows; i++) {
        for (int j = 0; j < matrixB_cols; j++) {
            for (int k = 0; k < matrixA_cols; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    answer = result;
    qDebug() << "Matrix multiplication completed";

    // Resize lineEdit_matrixResult to match result matrix dimensions
    int totalElements = matrixA_rows * matrixB_cols;
    lineEdit_matrixResult.resize(totalElements);
    qDebug() << "lineEdit_matrixResult resized to " << totalElements;

    // Create QLineEdit objects for the result matrix
    for (int x = 0; x < totalElements; x++) {
        lineEdit_matrixResult[x] = new QLineEdit();
    }

    qDebug() << "QLineEdit objects created";

    // Display result matrix
    int row_new = matrixA_rows;
    int col_new = matrixB_cols;
    ui->gridLayout_3->addWidget(ui->label_matrixResult, 0, 0, 1, col_new);
    ui->gridLayout_3->addWidget(ui->label_matrixResult_size, row_new + 1, 0, 1, col_new);
    ui->label_matrixResult_size->setText(ui->lineEdit_matrixA_rows->text() + " x " + ui->lineEdit_matrixB_cols->text());

    int iA = 0;
    for (int rowNumA = 0, layout_row = 1; rowNumA < row_new; rowNumA++, layout_row++) {
        for (int colNumA = 0; colNumA < col_new; colNumA++) {
            ui->gridLayout_3->addWidget(lineEdit_matrixResult[iA], layout_row, colNumA);
            lineEdit_matrixResult[iA]->setText(QString::number(result[rowNumA][colNumA]));
            lineEdit_matrixResult[iA]->setReadOnly(true);
            lineEdit_matrixResult[iA]->setAlignment(Qt::AlignHCenter);
            iA++;
        }
    }

    ui->frame_11->setStyleSheet("#frame_11 QLineEdit { border-radius: 7px; "
                                "max-width: 300px; min-height: 50px; "
                                "font: bold 25px \"DM Sans\" ;qproperty-alignment: AlignCenter; "
                                "margin: 5px 2px;}");

    qDebug() << "Result matrix displayed";
}

void matrixCalcu::determinant_output(double det)
{
    inverse_flag = true;
    qDebug() << "b1";
    ui->label_matrixResult_size->setText("Determinant: " + QString::number(det));
    ui->gridLayout_3->addWidget(ui->label_matrixResult, 0, 0, 1, to_int(ui->lineEdit_matrixA_cols_2->text()));
    ui->gridLayout_3->addWidget(ui->label_matrixResult_size, to_int(ui->lineEdit_matrixA_rows_2->text()) + 1, 0, 1, to_int(ui->lineEdit_matrixA_cols_2->text()));

    lineEdit_matrixResult.resize(matrixA_rows*matrixA_cols);
    qDebug() << "b2";
    for (int x = 0; x < matrixA_rows * matrixA_cols; x++) {
        lineEdit_matrixResult[x] = new QLineEdit();
    }

    qDebug() << "b3";
    answer = extractLineEditText(lineEdit_matrixA_2, matrixA_rows, matrixA_cols);
    int layout_row = 0; int iA = 0;
    for (int rowNumA = 0, layout_row = 1; rowNumA < matrixA_rows; rowNumA++, layout_row++) {
        for(int colNumA = 0; colNumA < matrixA_cols; colNumA++) {
            ui->gridLayout_3->addWidget(lineEdit_matrixResult[iA], layout_row, colNumA);
            lineEdit_matrixResult[iA]->setText(QString::number(answer[rowNumA][colNumA]));
            lineEdit_matrixResult[iA]->setReadOnly(true);
            lineEdit_matrixResult[iA]->setAlignment(Qt::AlignHCenter);
            iA++;
        }

    }
    qDebug() << "b4";

    ui->frame_11->setStyleSheet("#frame_11 QLineEdit { border-radius: 7px; "
                                "max-width: 300px; min-height: 50px; "
                                "font: bold 25px \"DM Sans\" ;qproperty-alignment: AlignCenter; "
                                "margin: 5px 2px;}");

}

void matrixCalcu::inverse()
{
    matrixA = extractLineEditText(lineEdit_matrixA_2, matrixA_rows, matrixA_cols);
    std::vector<std::vector<double>> result;

    try {

        if (determinant(matrixA) == 0){
            throw runtime_error("Inverse does not exist (determinant is zero).");
            showError("Determinant is Zero");
            inverse_flag = false;
        }
        else{
            inverse_flag = true;
            result = inverseMatrix(matrixA);

            int rowNumA = 0; int colNumA = 0; int iA = 0;
            int row_n = matrixA_rows; int col_n = matrixA_cols;
            lineEdit_matrixResult.resize(matrixA_rows*matrixA_cols);

            for (int x = 0; x < lineEdit_matrixResult.size(); x++) {
                lineEdit_matrixResult[x] = new QLineEdit();
            }
            ui->gridLayout_3->addWidget(ui->label_matrixResult, 0, 0, 1, matrixA_cols);
            ui->gridLayout_3->addWidget(ui->label_matrixResult_size, matrixA_rows+1, 0, 1, matrixA_cols);
            qDebug() << matrixA.size();
            int layout_row = 1;
            for (rowNumA = 0, layout_row = 1; rowNumA < matrixA_rows; rowNumA++, layout_row++) {
                qDebug() << "2.8";
                for(colNumA = 0; colNumA < matrixA_cols; colNumA++) {
                    ui->gridLayout_3->addWidget(lineEdit_matrixResult[iA], layout_row, colNumA);
                    lineEdit_matrixResult[iA]->setText(QString::number(result[rowNumA][colNumA]));
                    lineEdit_matrixResult[iA]->setReadOnly(true);
                    lineEdit_matrixResult[iA]->setAlignment(Qt::AlignHCenter);
                    iA++;
                }

            } answer = result;
        }

    }
    catch (runtime_error){
        qDebug() << "No Determinant";
        showError("Determinant is Zero!\nInverse Does Not Exist!");
    }
}

void matrixCalcu::RowEchelon()
{
    inverse_flag = true;
    matrixA = extractLineEditText(lineEdit_matrixA_2, matrixA_rows, matrixA_cols);
    std::vector<std::vector<double>> original;
    original = matrixA;
    std::vector<std::vector<double>> result;
    int next_row_id = 0;
    vector<Position> pivot_positions;
    for (int col = 0; col < matrixA_cols; col++)
    {
        int nonzero_row_id = is_nonzero_column(matrixA, col, matrixA_rows, next_row_id);
        if (nonzero_row_id >= 0)
        {
            qDebug() << "discovered leftmost nonzero column " << col
                     << ", and topmost nonzero row " << nonzero_row_id << Qt::endl;
            if (nonzero_row_id != next_row_id)
            {
                qDebug() << "exchanged row " << next_row_id << " and row " << nonzero_row_id << Qt::endl;
                row_exchange(matrixA.begin() + next_row_id, matrixA.begin() + nonzero_row_id);
                nonzero_row_id = next_row_id;
            }
            qDebug() << "selected pivot at position (row=" << nonzero_row_id << ",col=" << col << ") with value "
                     << matrixA[nonzero_row_id][col] << Qt::endl;
            pivot_positions.push_back(Position(nonzero_row_id, col));
            for (int row = next_row_id; row < matrixA_rows; row++)
            {
                if (matrixA[row][col] == 0)
                    continue;
                if (row == nonzero_row_id)
                    continue;
                qDebug() << "adding " << -matrixA[row][col] / matrixA[nonzero_row_id][col]
                         << " times of row " << nonzero_row_id << " onto row " << row << Qt::endl;
                row_replace(matrixA.begin() + row,
                            matrixA.begin() + nonzero_row_id,
                            -matrixA[row][col] / matrixA[nonzero_row_id][col]);
            }
            next_row_id++;
        }
        else
        {
            continue;
        }
    }

    for (vector<Position>::iterator pos = pivot_positions.begin(); pos != pivot_positions.end(); pos++) {
        if (pos->col == matrixA_cols - 1) {
            break; // Kani ra and na-add, ga check if last column na ba and mag stop siya meaning inconsistent
        }
        if (matrixA[pos->row][pos->col] != 1.0) {
            qDebug() << "scaling row " << pos->row << " by " << 1.0 / matrixA[pos->row][pos->col] << Qt::endl;
            row_scale(matrixA.begin() + pos->row, 1.0 / matrixA[pos->row][pos->col]);
        }

        if (ui->button_rref->isChecked()){
            for (int row = 0; row < matrixA_rows; row++) {
                if (matrixA[row][pos->col] != 0 && row != pos->row) {
                    qDebug() << "adding " << -matrixA[row][pos->col] / matrixA[pos->row][pos->col]
                             << " times of row " << pos->row << " onto row " << row << Qt::endl;
                    row_replace(matrixA.begin() + row, matrixA.begin() + pos->row,
                                -matrixA[row][pos->col] / matrixA[pos->row][pos->col]);
                }
            }
        }
    }
    result = matrixA;
    answer = result; // NEW
    matrixA = original;
    int rowNumA = 0; int colNumA = 0; int iA = 0;
    int row_n = matrixA_rows; int col_n = matrixA_cols;
    lineEdit_matrixResult.resize(matrixA_rows*matrixA_cols);
    qDebug() << "2.4";
    qDebug() << "matrix size: " << matrixA_rows*matrixA_cols;
    for (int x = 0; x < lineEdit_matrixResult.size(); x++) {
        lineEdit_matrixResult[x] = new QLineEdit();
    }
    ui->gridLayout_3->addWidget(ui->label_matrixResult, 0, 0, 1, matrixA_cols);
    ui->gridLayout_3->addWidget(ui->label_matrixResult_size, matrixA_rows+1, 0, 1, matrixA_cols);
    qDebug() << matrixA.size();
    int layout_row = 1;
    for (rowNumA = 0, layout_row = 1; rowNumA < matrixA_rows; rowNumA++, layout_row++) {
        qDebug() << "2.8";
        for(colNumA = 0; colNumA < matrixA_cols; colNumA++) {
            ui->gridLayout_3->addWidget(lineEdit_matrixResult[iA], layout_row, colNumA);
            lineEdit_matrixResult[iA]->setText(QString::number(result[rowNumA][colNumA]));
            lineEdit_matrixResult[iA]->setReadOnly(true);
            lineEdit_matrixResult[iA]->setAlignment(Qt::AlignHCenter);
            iA++;
        }

    }

    qDebug() << "4";
}


QString matrixCalcu::reverseString(QString txt, int size, QString& rev)
{
    qDebug() << "a";
    if (size == 0) {
        return rev;
    }
    qDebug() << "a1";
    rev += txt[size-1];
    qDebug() << "a2";
    return reverseString(txt, size-1, rev);

}

bool matrixCalcu::isDarkMode()
{
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", QSettings::NativeFormat);
    return settings.value("AppsUseLightTheme").toInt() == 0;
}

void matrixCalcu::printMatrix(const QString &fileName) {
    qDebug() << "Printing matrices to PDF";

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QPainter painter;
    painter.begin(&printer);

    int margin = 100;
    int spacing = 70;
    int startX = margin;
    int startY = margin;

    // Get the page size in points (1 inch = 72 points)
    QRectF pageRect = printer.pageLayout().paintRectPixels(printer.resolution());

    // Title of the document
    painter.setFont(QFont("DM Sans", 27, QFont::Bold));
    QString title = "Matrix Calculation Results";
    int titleWidth = painter.fontMetrics().horizontalAdvance(title);
    int titleX = (pageRect.width() - titleWidth) / 2;
    painter.drawText(QPointF(titleX, startY-20), title);
    startY += spacing;

    painter.setFont(QFont("DM Sans", 16, QFont::Bold));
    if(ui->button_addition->isChecked()){
        QString txt_operation = "Operation: Addition";
        int text_oper = (pageRect.width() - (painter.fontMetrics().horizontalAdvance(txt_operation))) / 2;
        painter.drawText(QPointF(text_oper, startY-40), txt_operation);
    }
    if(ui->button_subtraction->isChecked()){
        QString txt_operation = "Operation: Subtraction";
        int text_oper = (pageRect.width() - (painter.fontMetrics().horizontalAdvance(txt_operation))) / 2;
        painter.drawText(QPointF(text_oper, startY-40), txt_operation);
    }
    if(ui->button_multiplication->isChecked()){
        QString txt_operation = "Operation: Multiplication";
        int text_oper = (pageRect.width() - (painter.fontMetrics().horizontalAdvance(txt_operation))) / 2;
        painter.drawText(QPointF(text_oper, startY-40), txt_operation);
    }
    if(ui->button_transpose->isChecked()){
        QString txt_operation = "Operation: Transpose";
        int text_oper = (pageRect.width() - (painter.fontMetrics().horizontalAdvance(txt_operation))) / 2;
        painter.drawText(QPointF(text_oper, startY-40), txt_operation);
    }
    if(ui->button_inverse->isChecked()){
        QString txt_operation = "Operation: Inverse";
        int text_oper = (pageRect.width() - (painter.fontMetrics().horizontalAdvance(txt_operation))) / 2;
        painter.drawText(QPointF(text_oper, startY-40), txt_operation);
    }
    if(ui->button_determinant->isChecked()){
        QString txt_operation = "Operation: Determinant";
        int text_oper = (pageRect.width() - (painter.fontMetrics().horizontalAdvance(txt_operation))) / 2;
        painter.drawText(QPointF(text_oper, startY-40), txt_operation);
    }
    if(ui->button_ref->isChecked()){
        QString txt_operation = "Operation: Row Echelon Form";
        int text_oper = (pageRect.width() - (painter.fontMetrics().horizontalAdvance(txt_operation))) / 2;
        painter.drawText(QPointF(text_oper, startY-40), txt_operation);
    }
    if(ui->button_rref->isChecked()){
        QString txt_operation = "Operation: Reduced Row Echelon Form";
        int text_oper = (pageRect.width() - (painter.fontMetrics().horizontalAdvance(txt_operation))) / 2;
        painter.drawText(QPointF(text_oper, startY-40), txt_operation);
    }

    // Display Matrix A
    if (!matrixA.empty() && !matrixA[0].empty()) {
        painter.setFont(QFont("DM Sans", 15, QFont::Bold));
        QString matrixA_title = "Matrix A";
        int matrixA_x = (pageRect.width() - (painter.fontMetrics().horizontalAdvance(matrixA_title))) / 2;
        painter.drawText(QPointF(matrixA_x, startY+25), matrixA_title);
        startY += spacing;
        drawMatrix(painter, matrixA, pageRect.width(), startY);

        // Update startY to the next position
        startY += (matrixA.size() * 50) + spacing;
    } else {
        QMessageBox::warning(this, "Warning", "Matrix A is empty or uninitialized.");
    }

    if (ui->button_addition->isChecked() || ui->button_subtraction->isChecked() || ui->button_multiplication->isChecked())
    {
        // Display Matrix B
        if (!matrixB.empty() && !matrixB[0].empty()) {
            if (startY + (matrixB.size() * 50) + spacing > pageRect.height()) {
                printer.newPage();
                startY = margin;
            }

            painter.setFont(QFont("DM Sans", 15, QFont::Bold));
            QString matrixB_title = "Matrix B";
            int matrixB_x = (pageRect.width() - (painter.fontMetrics().horizontalAdvance(matrixB_title))) / 2;
            painter.drawText(QPointF(matrixB_x, startY+20), matrixB_title);
            startY += spacing;
            drawMatrix(painter, matrixB, pageRect.width(), startY);

            // Update startY to the next position
            startY += (matrixB.size() * 50) + spacing;
        } else {
            QMessageBox::warning(this, "Warning", "Matrix B is empty or uninitialized.");
        }
    }
    if (!ui->button_determinant->isChecked()) {
        // Display Result Matrix (answer)
        if (!answer.empty() && !answer[0].empty()) {
            if (startY + (answer.size() * 20) + spacing+100 > pageRect.height()) {
                printer.newPage();
                startY = margin;
            }

            QString matrixAns_title = "Result Matrix";
            int matrixAns_x = (pageRect.width() - (painter.fontMetrics().horizontalAdvance(matrixAns_title))) / 2;
            painter.setFont(QFont("DM Sans", 15, QFont::Bold));
            painter.drawText(QPointF(matrixAns_x, startY+30), matrixAns_title);
            startY += spacing;
            drawMatrix(painter, answer, pageRect.width(), startY);
        } else {
            QMessageBox::warning(this, "Warning", "Result Matrix is empty or uninitialized.");
        }
    }
    else{
        startY += spacing;
        QString determ_label = "Determinant: " + QString::number(det);
        int det_label_width = (pageRect.width() - (painter.fontMetrics().horizontalAdvance(determ_label))) / 2;
        painter.setFont(QFont("DM Sans", 15, QFont::Bold));
        painter.drawText(QPointF(det_label_width, startY), determ_label);

        startY += spacing;
    }
    startY = margin-45;
    startY += spacing;


    QMessageBox::information(this, "PDF Created", "PDF file saved as " + fileName);
    painter.end();
}







void matrixCalcu::drawMatrix(QPainter &painter, const std::vector<std::vector<double>> &matrix, int pageWidth, int startY) {
    if (matrix.empty() || matrix[0].empty()) {
        return;
    }

    int rows = matrix.size();
    int cols = matrix[0].size();

    QFont font("DM Sans", 14, QFont::Bold);
    painter.setFont(font);

    int rectWidth = 110;
    int rectHeight = 60;

    int totalMatrixWidth = cols * rectWidth;
    int startX = (pageWidth - totalMatrixWidth) / 2;

    // Draw matrix content
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QString text = QString::number(matrix[i][j]);
            int x = startX + j * rectWidth;
            int y = startY + i * rectHeight;
            QRect rect(x, y, rectWidth, rectHeight);
            painter.drawRect(rect);
            painter.drawText(rect, Qt::AlignCenter, text);
        }
    }
}

void matrixCalcu::on_printButton_clicked() {
    QString initialPath = QDir::homePath(); // Start in the user's home directory
    QString filter = "PDF Files (*.pdf);;All Files (*)";

    // Generate a random 10-digit string
    QString randomString = generateRandomString();

    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", initialPath, filter);
    if (fileName.isEmpty()) {
        return;
    }

    // Append the random string to the base name
    QFileInfo fileInfo(fileName);
    QString baseName = fileInfo.baseName();
    QString suffix = fileInfo.suffix();
    QString path = fileInfo.path();

    // Construct the new file name with the random string
    QString newFileName = path + "/" + baseName + "_" + randomString;
    if (!suffix.isEmpty()) {
        newFileName += "." + suffix;
    } else {
        newFileName += ".pdf";
    }

    // Save the PDF using the modified file name
    printMatrix(newFileName);

}

void matrixCalcu::home_button()
{
    remove_existingMatrix(ui->gridLayout);
    remove_existingMatrix(ui->gridLayout_2);
    remove_existingMatrix(ui->gridLayout_5);
    remove_existingMatrix(ui->gridLayout_3);
    resetButtons();

    ui->stackedWidget->setCurrentWidget(ui->page_home);
}


QString matrixCalcu::generateRandomString()
{
    QString randomString;
    for (int i = 0; i < 10; ++i) {
        int randomDigit = QRandomGenerator::global()->bounded(10); // generates a number between 0 and 9
        randomString.append(QString::number(randomDigit));
    }
    return randomString;
}










