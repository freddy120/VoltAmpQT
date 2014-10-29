#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QtSerialPort>

//! [0]


class SettingsDialog;

class serialThread : public QThread
{
    Q_OBJECT

public:
    serialThread (QObject *parent = 0);
    ~serialThread ();

    void transaction(const QString &portName, int waitTimeout, const QString &request);
    void run();

signals:
    void response(const QString &s);
    void error(const QString &s);
    void timeout(const QString &s);


private slots:
    //void openSerialPort();
    //void closeSerialPort();
    //void writeData(const QByteArray &data);
    //void readData();

private:
    QString portName;
    QString request;
    int waitTimeout;
    QMutex mutex;
    QWaitCondition cond;
    bool quit;
    QSerialPort *serialcom;
    SettingsDialog *settings;
};
//! [0]


#endif // SERIALTHREAD_H
