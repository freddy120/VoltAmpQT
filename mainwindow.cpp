#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupSimpleDemo(ui->customPlot);


    getallSerialPort();



}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::getallSerialPort(){

    //Example use QSerialPortInfo

      int i=0;
     foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();

        i++;
        ui->comboBoxSerial->insertItem(i,info.portName()); // insert al combobox.

    }
}
void MainWindow::connectSerialPort(const QSerialPortInfo &info){



    //conectar al puerto serial elegido.
    // Example use QSerialPort

    serialPort->setPort(info);
    if (serialPort->open(QIODevice::ReadWrite))
    serialPort->close();
    else
        qDebug() << "no se puede abrir"<<endl;


}


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




