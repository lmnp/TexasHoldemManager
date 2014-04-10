#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tablewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0, int sblind = 15, int players = 8, QString* names = NULL, int* amounts = NULL);

signals:

public slots:

private:
    TableWidget*    m_tableWidget;

};

#endif // MAINWINDOW_H
