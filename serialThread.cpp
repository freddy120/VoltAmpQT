
#include "serialThread.h"

#include "settingsdialog.h"


#include <QtSerialPort/QSerialPort>

#include <QTime>




QT_USE_NAMESPACE

serialThread::serialThread(QObject *parent)
    : QThread(parent), waitTimeout(0), quit(false)
{

    settings  = new SettingsDialog;
    serialcom = new QSerialPort(this); //! [4]

}

serialThread::~serialThread()
{
    mutex.lock();
    quit = true;
    cond.wakeOne();
    mutex.unlock();
    wait();
}

//! [5]
//! [0]
//! [4]
void serialThread::run()
{
    ;
}
