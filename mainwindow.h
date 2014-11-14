#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include "qcustomplot.h"
#include <QtSerialPort>
#include <QInputDialog>

#include <fstream>
#include "voltagrama.h"

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

   //!------Plot-------!
   void setupSimpleDemo(QCustomPlot *customPlot);
   void addplot(const QVector<double>& xVoltaje,const QVector<double>& yAmplitudep, const QVector<double>& yAmplituden);
   void addplotD(const QVector<double>& xVoltaje,const QVector<double>& yAmplitude);



   void getDatafromSerial();
   void getDatafromFile(std::string filename);



   //!------Calculate x values for technique-------!
   void setx_strippingVoltammetry(int scanmode);//stripping voltammetry
   void setx_normalVoltammetry (int scanmode);// normalVoltammetry
   void setx_cyclicVoltammetry (int scanmode);//cyclicVoltammetry

private slots:

   //!------Serial communication-------!
    void openSerialPort();
    void closeSerialPort();

    void writeData(const QByteArray &data);
    void readData();

    void handleError(QSerialPort::SerialPortError error);

    //!------Init Process-------!
    void startProceso();


    void setAllconfigurations();
    void LoadFile();

    void showBothSignals();
    void showDifferential();


    void titleDoubleClick(QMouseEvent *event, QCPPlotTitle *title);
    void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
    void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void removeSelectedGraph();
    void removeAllGraphs();
    void contextMenuRequest(QPoint pos);
    void moveLegend();
    void graphClicked(QCPAbstractPlottable *plottable);


private:
    int currentNumberVolt; // Numero actual de voltagramas!
    Voltagrama::Voltamm voltamm_data;

 // functions

    void initActionsConnections();
    void getAllconfigurations();


    // objects

    std::ofstream fileoutput;
    std::ifstream fileinput;
    Ui::MainWindow *ui;
    SettingsDialog *settings;
    ViewLog *logfile;
    QSerialPort *serialPort;
    QString portName;

    std::vector<Voltagrama> voltagramas;// array of voltagramas
};
#endif // MAINWINDOW_H

