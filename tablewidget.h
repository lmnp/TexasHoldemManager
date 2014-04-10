#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QGroupBox>
#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "playerwidget.h"

class TableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TableWidget(QWidget *parent = 0,int blind = 15, int players = 8, QString* names = NULL, int* amounts = NULL);

signals:

public slots:

private:
    PlayerWidget* m_player0;
    PlayerWidget* m_player1;
    PlayerWidget* m_player2;
    PlayerWidget* m_player3;
    PlayerWidget* m_player4;
    PlayerWidget* m_player5;
    PlayerWidget* m_player6;
    PlayerWidget* m_player7;
    PlayerWidget* m_player8;
    PlayerWidget* m_player9;
    QTabWidget  * makeTabWidget();
    QGroupBox   * makeCurrentGroupBox();
    QGroupBox   * makeOtherGroupBox();
    int           m_pot;
    int           m_currentBet;
    int           m_sblind;
    int           m_bblind;
    int           m_numberOfPlayers;
};

#endif // TABLEWIDGET_H
