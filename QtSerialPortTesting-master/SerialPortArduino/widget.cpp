#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    serial = new QSerialPort;
    serialIsAvailable = false;
    portName = "";

    foreach (const QSerialPortInfo &serialInfo, QSerialPortInfo::availablePorts()) {
        qDebug() << serialInfo.productIdentifier();
        qDebug() << serialInfo.vendorIdentifier();
        qDebug() << serialInfo.portName();
    }

    foreach (const QSerialPortInfo &serialInfo, QSerialPortInfo::availablePorts()) {
        if (serialInfo.hasVendorIdentifier() && serialInfo.hasProductIdentifier()){
            if (serialInfo.vendorIdentifier() == vendor){
                if (serialInfo.productIdentifier() == product){
                    portName = serialInfo.portName();
                    serialIsAvailable = true;
                }
            }
        }
    }
    if (serialIsAvailable){
        serial->setPortName(portName);
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->open(QSerialPort::ReadWrite);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
    }
    connect(serial, SIGNAL(readyRead()), this, SLOT(signalReceived()));
}

Widget::~Widget()
{
    if (serial->isOpen()){
        serial->close();
    }
    delete ui;
}

void Widget::signalReceived()
{
    QByteArray data;
    data = serial->readAll();
    qDebug()<<data;
}

void Widget::update(QString command)
{
    if (serial->isWritable()){
        serial->write(command.toStdString().c_str());
    }
    else {
        qDebug()<<"Tidak Terkirim"<<endl;
    }
}


void Widget::on_horizontalSlider_valueChanged(int value)
{
    this->ui->label->setText(QString("<span style=\" font-size:14pt; font-weight:600;\">%1</span>").arg(value));
    this->update(QString("r%1").arg(value));
}
