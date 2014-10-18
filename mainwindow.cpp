#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settingsdialog.h"
#include "viewlog.h"

#include <QMessageBox>
#include <QtSerialPort>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupSimpleDemo(ui->customPlot);

    this->setFixedSize(this->width(),this->height());


    settings = new SettingsDialog;
    //! [1]
    logfile =  new ViewLog;
    serialPort = new QSerialPort(this);
    //! [1]


    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_disconnect->setEnabled(false);
    ui->pushButton_settings->setEnabled(true);
   // ui->pushButton_viewlog->setEnabled(false);

    initActionsConnections();


    connect(serialPort, SIGNAL(error(QSerialPort::SerialPortError)), this,
                SLOT(handleError(QSerialPort::SerialPortError)));

    //! [2]
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(readData()));
    //! [2]
    connect(logfile, SIGNAL(getData(QByteArray)), this, SLOT(writeData(QByteArray)));
    //! [3]

     //! [3]
    //getallSerialPort();

    //serialPort = new QSerialPort();
    //thread= new QThread();
   // serialPort->moveToThread(thread);
    //thread->start();


}

MainWindow::~MainWindow()
{
    delete settings;
    delete logfile;
    delete ui;

}

void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings(); //estructura de datos

    serialPort->setPortName(p.name);
    serialPort->setBaudRate(p.baudRate);
    serialPort->setDataBits(p.dataBits);
    serialPort->setParity(p.parity);
    serialPort->setStopBits(p.stopBits);
    serialPort->setFlowControl(p.flowControl);

    if (serialPort->open(QIODevice::ReadWrite)) {
            ui->pushButton_viewlog->setEnabled(true);
          //  console->setLocalEchoEnabled(p.localEchoEnabled);
            ui->pushButton_connect->setEnabled(false);
            ui->pushButton_disconnect->setEnabled(true);

            ui->pushButton_settings->setEnabled(false);

            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serialPort->errorString());

        ui->statusBar->showMessage(tr("Open error"));
    }
}


//! [5]
void MainWindow::closeSerialPort()
{
    serialPort->close();
    ui->pushButton_viewlog->setEnabled(false);
    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_disconnect->setEnabled(false);
    ui->pushButton_settings->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
}
//! [5]

//! [6]
void MainWindow::writeData(const QByteArray &data)
{
    serialPort->write(data);
}
//! [6]

//! [7]
void MainWindow::readData()
{
    QByteArray data = serialPort->readAll();
    logfile->putData(data);

    //! mostrar data here

}
//! [7]

//! [8]
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serialPort->errorString());
        closeSerialPort();
    }

}
//! [8]

void MainWindow::initActionsConnections()
{
    connect(ui->pushButton_connect, SIGNAL(clicked()), this, SLOT(openSerialPort()));
    connect(ui->pushButton_disconnect, SIGNAL(clicked()), this, SLOT(closeSerialPort()));
   // connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->pushButton_settings, SIGNAL(clicked()), settings, SLOT(show()));
    connect(ui->pushButton_viewlog,SIGNAL(clicked()), logfile , SLOT(show()));



    // connect(ui->actionClear, SIGNAL(triggered()), console, SLOT(clear()));
   //  connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
   //  connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}


//void MainWindow::getallSerialPort(){

//    //Example use QSerialPortInfo

//      int i=0;
//     foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
//        qDebug() << "Name        : " << info.portName();
//        qDebug() << "Description : " << info.description();
//        qDebug() << "Manufacturer: " << info.manufacturer();

//        i++;
//        ui->comboBoxSerial->insertItem(i,info.portName()); // insert al combobox.

//    }
//}
//void MainWindow::connectSerialPort(const QSerialPortInfo &info){



//    //conectar al puerto serial elegido.
//    // Example use QSerialPort

//    serialPort->setPort(info);
//    if (serialPort->open(QIODevice::ReadWrite))
//    serialPort->close();
//    else
//        qDebug() << "no se puede abrir"<<endl;


//}


void MainWindow::setupSimpleDemo(QCustomPlot *customPlot)
{


  // add two new graphs and set their look:
  customPlot->addGraph();
  customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
  customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
  customPlot->addGraph();
  customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph

  customPlot->addGraph();
  customPlot->graph(2)->setPen(QPen(Qt::green)); // line color red for second graph

  // generate some points of data (y0 for first, y1 for second graph):
  QVector<double> x(250), y0(250), y1(250), y2(250);
  for (int i=0; i<250; ++i)
  {
    x[i] = i;
    y0[i] = exp(-i/150.0)*cos(i/10.0); // exponentially decaying cosine
    y1[i] = exp(-i/150.0);             // exponential envelope
    y2[i] = sin(2*3.1416*i/250);
  }
  // configure right and top axis to show ticks but no labels:
  // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
  customPlot->xAxis2->setVisible(true);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setVisible(true);
  customPlot->yAxis2->setTickLabels(false);
  // make left and bottom axes always transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
  // pass data points to graphs:
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(1)->setData(x, y1);
  customPlot->graph(2)->setData(x, y2);
  // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
  customPlot->graph(0)->rescaleAxes();
  // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
  customPlot->graph(1)->rescaleAxes(true);
  customPlot->graph(2)->rescaleAxes(true);
  // Note: we could have also just called customPlot->rescaleAxes(); instead
  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}




