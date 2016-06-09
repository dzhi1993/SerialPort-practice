#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    void signalReceived();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::Widget *ui;
    void update(QString command);

    QSerialPort *serial;
    static const quint16 vendor = 9025;
    static const quint16 product = 66;
    QString portName;
    bool serialIsAvailable;
};

#endif // WIDGET_H
