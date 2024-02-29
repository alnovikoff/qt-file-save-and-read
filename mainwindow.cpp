#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file = new File();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    file->write(ui->lineEdit->text());

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(file->read());
}


void MainWindow::on_pushButton_3_clicked()
{
    if(ui->lineEdit_2->text() != "")
    {
        file->changeFileName(ui->lineEdit_2->text());
    }
}

