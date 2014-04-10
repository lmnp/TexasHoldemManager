#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent, int sblind, int players, QString* names, int* amounts) :
    QMainWindow(parent)
{
    m_tableWidget = new TableWidget(this, sblind, players, names, amounts);
    setCentralWidget(m_tableWidget);
}
