#include "matrixcalcu.h"
#include "ui_matrixcalcu.h"
#include "exceptions.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMessageBox>
#include <QString>

#include <vector>

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
    connect(ui->pushButton_enter_matrixB_2, SIGNAL(clicked()), this, SLOT(resultMatrix()));
    connect(ui->pushButton_enter_matrixA_advanced, SIGNAL(clicked()), this, SLOT(resultMatrix_2()));

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
    qDebug() << "what";
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
                 if (ui->button_transpose->isChecked()) {
                     int row_num = 0; int col_num = 0; int counter = 0;
                     remove_existingMatrix(ui->gridLayout_3);

                     int answer_rows = to_int(ui->lineEdit_matrixA_rows_2->text()); int answer_cols = to_int(ui->lineEdit_matrixA_cols_2->text());
                     answer = extractLineEditText(lineEdit_matrixA_2, answer_rows, answer_cols);

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

                     qDebug() << "Transposed Matrix:";
                     for (const auto& row : matrix_Transposed) {
                         qDebug() << row;
                     }

                     ui->gridLayout_3->addWidget(ui->label_matrixResult, 0, 0, 1, answer_rows);
                     ui->gridLayout_3->addWidget(ui->label_matrixResult_size, answer_cols + 1, 0, 1, answer_rows);
                     ui->label_matrixResult_size->setText(ui->lineEdit_matrixA_cols_2->text() + " x " + ui->lineEdit_matrixA_rows_2->text());

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
                 }

                 ui->frame_11->setStyleSheet("#frame_11 QLineEdit { border-radius: 7px; "
                                             "max-width: 300px; min-height: 50px; "
                                             "font: bold 25px \"DM Sans\" ;qproperty-alignment: AlignCenter; "
                                             "margin: 5px 2px;}");

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
    ui->label_matrixResult_size->setText("Determinant: " + QString::number(det));
    ui->gridLayout_3->addWidget(ui->label_matrixResult, 0, 0, 1, to_int(ui->lineEdit_matrixA_cols_2->text()));
    ui->gridLayout_3->addWidget(ui->label_matrixResult_size, to_int(ui->lineEdit_matrixA_rows_2->text()) + 1, 0, 1, to_int(ui->lineEdit_matrixA_cols_2->text()));

    lineEdit_matrixResult.resize(matrixA_rows*matrixA_cols);

    for (int x = 0; x < matrixA_rows * matrixA_cols; x++) {
        lineEdit_matrixResult[x] = new QLineEdit();
    }


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

    ui->frame_11->setStyleSheet("#frame_11 QLineEdit { border-radius: 7px; "
                                "max-width: 300px; min-height: 50px; "
                                "font: bold 25px \"DM Sans\" ;qproperty-alignment: AlignCenter; "
                                "margin: 5px 2px;}");

}














