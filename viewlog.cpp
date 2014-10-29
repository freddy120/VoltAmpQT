#include "viewlog.h"
#include "ui_viewlog.h"


QT_USE_NAMESPACE

ViewLog::ViewLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewLog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());  //no resize

    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);

    //ui->VoltLogplainTextEdit->setPlainText("Hello World");
}


void ViewLog::putData(const QByteArray &data)
{

    QString textlog;
    //textlog = ui->VoltLogplainTextEdit->toPlainText();
   // textlog = textlog + QString(data).trimmed();
   //  ui->VoltLogplainTextEdit->clear();

    ui->VoltLogplainTextEdit->textCursor().insertText(QString(data));
    //ui->VoltLogplainTextEdit->setPlainText(QString(data).trimmed());
    // insertPlainText(QString(data));
}
