#include "matrixcalcu.h"
#include "ui_matrixcalcu.h"

matrixCalcu::matrixCalcu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::matrixCalcu)
{
    ui->setupUi(this);
}

matrixCalcu::~matrixCalcu()
{
    delete ui;
}
