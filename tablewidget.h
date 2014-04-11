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
    void        on_pb_call_released();
    void        on_pb_fold_released();
    void        on_pb_check_released();

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
    QLabel      * m_amount0;
    QLabel      * m_amount1;
    QLabel      * m_amount2;
    QLabel      * m_amount3;
    QLabel      * m_amount4;
    QLabel      * m_amount5;
    QLabel      * m_amount6;
    QLabel      * m_amount7;
    QLabel      * m_amount8;
    QLabel      * m_amount9;

    PlayerWidget* m_currentPlayer;


    QTabWidget  * makeTabWidget();
    QGroupBox   * makeCurrentGroupBox();
    QGroupBox   * makeOtherGroupBox();

    QGroupBox   * makePlayerPushButtons();
    QPushButton * m_pb_0;
    QPushButton * m_pb_1;
    QPushButton * m_pb_2;
    QPushButton * m_pb_3;
    QPushButton * m_pb_4;
    QPushButton * m_pb_5;
    QPushButton * m_pb_6;
    QPushButton * m_pb_7;
    QPushButton * m_pb_8;
    QPushButton * m_pb_9;

    int           m_status[10]; //2-bet placed, 1-yet to go,0-current turn,-1-out(folded),-2-not playing


    int           m_pot;
    int           m_currentBet;
    int           m_sblind;
    int           m_bblind;
    int           m_numberOfPlayers;
};

#endif // TABLEWIDGET_H
