#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include "qcustomplot.h"
#include <QtSerialPort>


QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE



class SettingsDialog;
class ViewLog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   void setupSimpleDemo(QCustomPlot *customPlot);
   // void getallSerialPort();
   // void connectSerialPort(const QSerialPortInfo &info);

private slots:
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void readData();
    void handleError(QSerialPort::SerialPortError error);

private:
    void initActionsConnections();

private:
    Ui::MainWindow *ui;
    SettingsDialog *settings;
    ViewLog *logfile;
    QSerialPort *serialPort;
};
#endif // MAINWINDOW_H

