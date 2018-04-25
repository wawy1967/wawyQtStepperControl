#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    serial->setPortName("/dev/ttyACM0");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setParity(QSerialPort::NoParity);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setDataBits(QSerialPort::Data8);
}

MainWindow::~MainWindow()
{
    serial->close();
    delete ui;
}

void MainWindow::on_pushButtonRun_clicked()
{
    if (ui->radioButtonForward->isChecked())
        {
            QString s = QString::number(ui->spinBoxStep->value());
            QByteArray command = "f";
            command.append(s);
            qDebug() << command;
            if (serial->isWritable())
                serial->write(command);
            else if (serial->open(QIODevice::ReadWrite))
                serial->write(command);
            else
            {
                QMessageBox::information(0,"Error",
                         "Cannot open port!");
                return;
            }
        }
    if (ui->radioButtonReverse->isChecked())
        {
            QString s = QString::number(ui->spinBoxStep->value());
            QByteArray command = "r";
            command.append(s);
            qDebug() << command;
            if (serial->isWritable())
                serial->write(command);
            else if (serial->open(QIODevice::ReadWrite))
                serial->write(command);
            else
            {
                QMessageBox::information(0,"Error",
                         "Cannot open port!");
                return;
            }
        }
}
