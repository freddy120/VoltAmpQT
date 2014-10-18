#ifndef VIEWLOG_H
#define VIEWLOG_H

#include <QWidget>

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE

namespace Ui {
class ViewLog;
}

QT_END_NAMESPACE

class ViewLog : public QWidget
{
    Q_OBJECT
signals:
    void getData(const QByteArray &data);

public:
    explicit ViewLog(QWidget *parent = 0);
    void putData(const QByteArray &data);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void contextMenuEvent(QContextMenuEvent *e);

private:
    Ui::ViewLog *ui;  //gui

};


#endif // VIEWLOG_H
