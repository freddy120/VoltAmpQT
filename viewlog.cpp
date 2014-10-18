#include "viewlog.h"
#include "ui_viewlog.h"


QT_USE_NAMESPACE

ViewLog::ViewLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewLog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    ui->VoltLogplainTextEdit->setPlainText("Hello World");
}


void ViewLog::putData(const QByteArray &data)
{
   ui->VoltLogplainTextEdit->setPlainText(QString(data));
  // insertPlainText(QString(data));
}

void ViewLog::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Backspace:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        break;
    default:
        emit getData(e->text().toLocal8Bit());
    }
}

void ViewLog::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    setFocus();
}

void ViewLog::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void  ViewLog::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}

