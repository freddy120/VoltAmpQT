#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QtSerialPort>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupSimpleDemo(QCustomPlot *customPlot);
    void getallSerialPort();
    void connectSerialPort(const QSerialPortInfo &info);

private slots:
    void on_comboBoxSerial_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPortInfo pinfo;
    QSerialPort *serialPort;
};


#endif // MAINWINDOW_H

