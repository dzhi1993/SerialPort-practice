#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QLabel>
//#include <QFont>
#include <QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mSerialPort = new QSerialPort;
    mSerialPortInfo = new QSerialPortInfo;

    connect(mSerialPort,SIGNAL(readyRead()),this,SLOT(ReadMyCom()));
    connect(ui->comboBox,SIGNAL(currentIndexChanged()),this,SLOT(reset_serialPort()));

    QList<QSerialPortInfo> comInfoList = mSerialPortInfo->availablePorts();//get serial port list information

    if(comInfoList.isEmpty())//no serial port can be used
    {
        QMessageBox::warning(this,"Waring!","There's no avalible COM to use, plese check your serialport!");
    }
    else//show available port
    {
        for(int i = 0; i < comInfoList.size(); i ++)
        {
            ui->comboBox->addItem(comInfoList[i].portName());
        }
    }

    try{

        //mSerialPort->setPort(comInfoList.first());
        //mSerialPort->open(QIODevice::ReadWrite);
        mSerialPort->setPortName(ui->comboBox->currentText());//set serial port
        mSerialPort->open(QIODevice::ReadOnly);// open this serial port
        //mSerialPort->open(QIODevice::readLine());
        mSerialPort->setBaudRate(19200);
        mSerialPort->setDataBits(QSerialPort::Data8);
        mSerialPort->setFlowControl(QSerialPort::NoFlowControl);
        mSerialPort->setStopBits(QSerialPort::OneStop);
        mSerialPort->setParity(QSerialPort::NoParity);

        //data_received = mSerialPort->readLine();//read data from serial port
       // QString str = tc->toUnicode(data_received);//change format of received data
        //double a = str.toDouble();
        //double b = -29.456;
        //QString c = "-29.0";
        /*QwtText qText = str;
        QFont qfont = qText.font();
        qfont.setBold(true);
        qfont.setPointSize(40);
        qText.setFont(qfont);*/

        //ui->textBrowser->insertPlainText(str);//show received data
       // ui->lcdNumber->setDigitCount(7);
        //ui->lcdNumber->display(str.trimmed());//double number
    }
    catch(...){

        QMessageBox::warning(this,"ERROR!","Cannot open the serialport!");

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset_serialPort()
{
    mSerialPort->close();
}

void MainWindow::ReadMyCom()
{
    data_received = mSerialPort->QIODevice::readLine();//read data from serial port
    QString str = tc->toUnicode(data_received);//change format of received data
    //double a = -12.456;
    QString c = "-29.333";

    ui->lcdNumber->setDigitCount(7);
    ui->lcdNumber->display(c);//double number

    //QLabel label(str);
    //label.setFont(QFont("Timers",28,QFont::Bold));

    ui->textBrowser->insertPlainText(str);//show received data
    ui->textBrowser->moveCursor(QTextCursor::End);

    ui->label->setText(str);
}
