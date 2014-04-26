#include "tablewidget.h"
#include <iostream>
#include <QDebug>

TableWidget::TableWidget(QWidget *parent, int blind, int players, QString* names, int* amounts) :
    QWidget(parent)
{
    m_sblind                    = blind;
    m_bblind                    = m_sblind*2;
    m_numberOfPlayers           = players;
    m_playersStillIn            = m_numberOfPlayers;
    m_pot                       = 0;
    m_currentBet                = 0;
    m_round                     = 0;
    m_player0                   = new PlayerWidget(this, names[0], amounts[0]);
    m_player1                   = new PlayerWidget(this, names[1], amounts[1]);
    m_player0->setNextPlayer(m_player1);
    m_currentPlayer             = m_player0;
    m_roundStartPlayer          = m_player0;
    m_sBlindPlayer              = m_player0;
    m_bBlindPlayer              = m_player1;
    m_sBlindPlayer->minusAmount(m_sblind);
    m_pot                      += m_sblind;
    m_bBlindPlayer->minusAmount(m_bblind);
    m_pot                      += m_bblind;
    m_pickWinner                = false;
    if(m_numberOfPlayers >= 3)
    {
        m_player2                   = new PlayerWidget(this, names[2], amounts[2]);
        m_player1->setNextPlayer(m_player2);
        if(m_numberOfPlayers >= 4)
        {
            m_player3                   = new PlayerWidget(this, names[3], amounts[3]);
            m_player2->setNextPlayer(m_player3);
            if(m_numberOfPlayers >= 5)
            {
                m_player4                   = new PlayerWidget(this, names[4], amounts[4]);
                m_player3->setNextPlayer(m_player4);
                if(m_numberOfPlayers >= 6)
                {
                    m_player5                   = new PlayerWidget(this, names[5], amounts[5]);
                    m_player4->setNextPlayer(m_player5);
                    if(m_numberOfPlayers >= 7)
                    {
                        m_player6                   = new PlayerWidget(this, names[6], amounts[6]);
                        m_player5->setNextPlayer(m_player6);
                        if(m_numberOfPlayers >= 8)
                        {
                            m_player7                   = new PlayerWidget(this, names[7], amounts[7]);
                            m_player6->setNextPlayer(m_player7);
                            if(m_numberOfPlayers >= 9)
                            {
                                m_player8                   = new PlayerWidget(this, names[8], amounts[8]);
                                m_player7->setNextPlayer(m_player8);
                                if(m_numberOfPlayers == 10)
                                {
                                    m_player9                   = new PlayerWidget(this, names[9], amounts[9]);
                                    m_player8->setNextPlayer(m_player9);
                                    m_player9->setNextPlayer(m_player0);
                                }
                                else
                                    m_player8->setNextPlayer(m_player0);
                            }
                            else
                                m_player7->setNextPlayer(m_player0);
                        }
                        else
                            m_player6->setNextPlayer(m_player0);
                    }
                    else
                        m_player5->setNextPlayer(m_player0);
                }
                else
                    m_player4->setNextPlayer(m_player0);
            }
            else
                m_player3->setNextPlayer(m_player0);
        }
        else
            m_player2->setNextPlayer(m_player0);
    }
    else
        m_player1->setNextPlayer(m_player0);
    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(makePlayerPushButtons());
    vbox->addWidget(makeOptionsGroupBox());
    setLayout(vbox);
}

void        TableWidget::on_pb_call_released()
{
    int diff    =   m_currentBet    -   m_currentPlayer->getLastBet();
    if(diff > 0)
    {
        if(m_currentPlayer->getAmount() > diff)
        {
            m_currentPlayer->minusAmount(diff);
            m_currentPlayer->changeLastBet(m_currentBet);
            m_pot   +=  diff;
        }
        else
        {
            int c_amount    =   m_currentPlayer->getAmount();
            m_currentPlayer->minusAmount(c_amount);
            m_currentPlayer->changeLastBet(c_amount);
            m_pot   +=  c_amount;
        }
    }
    emit    potChanged(m_pot);
    if(m_round < 4)
    {
        if(m_currentPlayer->getNextPlayer() == m_roundStartPlayer)
        {
            if(!m_roundStartPlayer->getGameStatus())
            {
                PlayerWidget* temp = m_roundStartPlayer->getNextPlayer();
                while(!temp->getGameStatus())
                {
                    temp = temp->getNextPlayer();
                }
                if(temp->getLastBet() == m_currentBet)
                {
                    m_round++;
                    emit roundChanged(m_round);
                    PlayerWidget* temp1 =   m_currentPlayer->getNextPlayer();
                    int i = 0;
                    while(i < m_numberOfPlayers)
                    {
                        temp1->changeLastBet(0);
                        temp1   =   temp1->getNextPlayer();
                        i++;
                    }
                    m_currentBet = 0;
                }
                m_currentPlayer = temp;
                emit playerChanged(m_currentPlayer->getName());
                emit amountChanged(m_currentPlayer->getAmount());
            }
            else
            {
                if(m_roundStartPlayer->getLastBet() == m_currentBet)
                {
                    m_round++;
                    emit roundChanged(m_round);
                    PlayerWidget* temp1 =   m_currentPlayer->getNextPlayer();
                    int i = 0;
                    while(i < m_numberOfPlayers)
                    {
                        temp1->changeLastBet(0);
                        temp1   =   temp1->getNextPlayer();
                        i++;
                    }
                    m_currentBet = 0;
                }
                m_currentPlayer = m_roundStartPlayer;
                emit playerChanged(m_currentPlayer->getName());
                emit amountChanged(m_currentPlayer->getAmount());
            }
        }
        else if(m_currentPlayer->getNextPlayer()->getGameStatus())
        {
            m_currentPlayer = m_currentPlayer->getNextPlayer();
            emit playerChanged(m_currentPlayer->getName());
            emit amountChanged(m_currentPlayer->getAmount());
        }
        else
        {
            PlayerWidget* m_temp = m_currentPlayer->getNextPlayer();
            while(!m_temp->getGameStatus())
            {
                m_temp = m_temp->getNextPlayer();
            }
            m_currentPlayer = m_temp;
            emit playerChanged(m_currentPlayer->getName());
            emit amountChanged(m_currentPlayer->getAmount());
        }
    }
    else
    {
        m_pickWinner    =   true;
    }
}

void        TableWidget::on_pb_fold_released()
{
    m_currentPlayer->setGameStatus(false);
    m_playersStillIn--;
    if(m_playersStillIn > 1 && m_round < 4)
    {
        if(m_currentPlayer->getNextPlayer() == m_roundStartPlayer)
        {
            if(!m_roundStartPlayer->getGameStatus())
            {
                PlayerWidget* temp = m_roundStartPlayer->getNextPlayer();
                while(!temp->getGameStatus())
                {
                    temp = temp->getNextPlayer();
                }
                if(temp->getLastBet() == m_currentBet)
                {
                    m_round++;
                    emit roundChanged(m_round);
                    PlayerWidget* temp1 =   m_currentPlayer->getNextPlayer();
                    int i = 0;
                    while(i < m_numberOfPlayers)
                    {
                        temp1->changeLastBet(0);
                        temp1   =   temp1->getNextPlayer();
                        i++;
                    }
                    m_currentBet = 0;
                }
                m_currentPlayer = temp;
                emit playerChanged(m_currentPlayer->getName());
                emit amountChanged(m_currentPlayer->getAmount());
            }
            else
            {
                if(m_roundStartPlayer->getLastBet() == m_currentBet)
                {
                    m_round++;
                    emit roundChanged(m_round);
                    PlayerWidget* temp1 =   m_currentPlayer->getNextPlayer();
                    int i = 0;
                    while(i < m_numberOfPlayers)
                    {
                        temp1->changeLastBet(0);
                        temp1   =   temp1->getNextPlayer();
                        i++;
                    }
                    m_currentBet = 0;
                }
                m_currentPlayer = m_roundStartPlayer;
                emit playerChanged(m_currentPlayer->getName());
                emit amountChanged(m_currentPlayer->getAmount());
            }
        }
        else if(m_currentPlayer->getNextPlayer()->getGameStatus())
        {
            m_currentPlayer = m_currentPlayer->getNextPlayer();
            emit playerChanged(m_currentPlayer->getName());
            emit amountChanged(m_currentPlayer->getAmount());
        }
        else
        {
            PlayerWidget* m_temp = m_currentPlayer->getNextPlayer();
            while(!m_temp->getGameStatus())
            {
                m_temp = m_temp->getNextPlayer();
            }
            m_currentPlayer = m_temp;
            emit playerChanged(m_currentPlayer->getName());
            emit amountChanged(m_currentPlayer->getAmount());
        }
    }
    else if(m_playersStillIn == 1)
    {
        PlayerWidget* temp  =   m_currentPlayer->getNextPlayer();
        while(!temp->getGameStatus())
        {
            temp    =   temp->getNextPlayer();
        }
        temp->plusAmount(m_pot);
        m_pot   =   0;
        m_roundStartPlayer  =   m_roundStartPlayer->getNextPlayer();
        m_currentPlayer =   m_roundStartPlayer;
        emit    playerChanged(m_currentPlayer->getName());
        emit    amountChanged(m_currentPlayer->getAmount());
        m_round =   0;
        emit roundChanged(m_round);
        m_currentBet = 0;
        temp    =   m_currentPlayer->getNextPlayer();
        while(temp != m_currentPlayer)
        {
            temp->changeLastBet(0);
            temp->setGameStatus(true);
            m_playersStillIn++;
            temp    =   temp->getNextPlayer();
        }
        m_sblind       +=   5;
        emit sblindChanged(m_sblind);
        m_bblind        =   2*m_sblind;
        m_pot          +=   m_sblind;
        m_pot          +=   m_bblind;
        m_sBlindPlayer  =   m_sBlindPlayer->getNextPlayer();
        m_sBlindPlayer->minusAmount(m_sblind);
        m_sBlindPlayer->changeLastBet(0);
        m_bBlindPlayer  =   m_bBlindPlayer->getNextPlayer();
        m_bBlindPlayer->minusAmount(m_bblind);
        m_bBlindPlayer->changeLastBet(0);
        emit    potChanged(m_pot);
    }
    else
    {
        m_pickWinner    =   true;
    }
}

void        TableWidget::on_pb_check_released()
{
    m_pot   +=  0;
    emit    potChanged(m_pot);
    if(m_currentBet == 0)
    {
        m_currentPlayer->minusAmount(0);
        m_currentBet    =   0;
        if(m_round  <   4)
        {
            if(m_currentPlayer->getNextPlayer() == m_roundStartPlayer)
            {
                if(!m_roundStartPlayer->getGameStatus())
                {
                    PlayerWidget* temp = m_roundStartPlayer->getNextPlayer();
                    while(!temp->getGameStatus())
                    {
                        temp = temp->getNextPlayer();
                    }
                    if(temp->getLastBet() == m_currentBet)
                    {
                        m_round++;
                        emit roundChanged(m_round);
                        PlayerWidget* temp1 =   m_currentPlayer->getNextPlayer();
                        int i = 0;
                        while(i < m_numberOfPlayers)
                        {
                            temp1->changeLastBet(0);
                            temp1   =   temp1->getNextPlayer();
                            i++;
                        }
                        m_currentBet = 0;
                    }
                    m_currentPlayer = temp;
                    emit playerChanged(m_currentPlayer->getName());
                    emit amountChanged(m_currentPlayer->getAmount());
                }
                else
                {
                    if(m_roundStartPlayer->getLastBet() == m_currentBet)
                    {
                        m_round++;
                        emit roundChanged(m_round);
                        PlayerWidget* temp1 =   m_currentPlayer->getNextPlayer();
                        int i = 0;
                        while(i < m_numberOfPlayers)
                        {
                            temp1->changeLastBet(0);
                            temp1   =   temp1->getNextPlayer();
                            i++;
                        }
                        m_currentBet = 0;
                    }
                    m_currentPlayer = m_roundStartPlayer;
                    emit playerChanged(m_currentPlayer->getName());
                    emit amountChanged(m_currentPlayer->getAmount());
                }
            }
            else if(m_currentPlayer->getNextPlayer()->getGameStatus())
            {
                m_currentPlayer = m_currentPlayer->getNextPlayer();
                emit playerChanged(m_currentPlayer->getName());
                emit amountChanged(m_currentPlayer->getAmount());
            }
            else
            {
                PlayerWidget* m_temp = m_currentPlayer->getNextPlayer();
                while(!m_temp->getGameStatus())
                {
                    m_temp = m_temp->getNextPlayer();
                }
                m_currentPlayer = m_temp;
                emit playerChanged(m_currentPlayer->getName());
                emit amountChanged(m_currentPlayer->getAmount());
            }
        }
        else
        {
            m_pickWinner    =   true;
        }
    }
}

void         TableWidget::on_pb_raise_released()
{
    m_raise   =   new RaiseDialog(this, m_currentBet+1, m_currentPlayer->getAmount(),m_currentPlayer->getLastBet());
    connect(m_raise,  SIGNAL(bet_confirmed(int)), this, SLOT(on_raised_confirmed(int)));
    m_raise->setModal(true);
    m_raise->exec();
}

void    TableWidget::on_raised_confirmed(int x)
{
    if(x != 0)
    {
        m_currentPlayer->minusAmount(x);
        m_currentBet    =   x;
        m_pot   +=  x;
        emit    potChanged(m_pot);
        if(m_round  <   4)
        {
            if(m_currentPlayer->getNextPlayer() == m_roundStartPlayer)
            {
                if(!m_roundStartPlayer->getGameStatus())
                {
                    PlayerWidget* temp = m_roundStartPlayer->getNextPlayer();
                    while(!temp->getGameStatus())
                    {
                        temp = temp->getNextPlayer();
                    }
                    if(temp->getLastBet() == m_currentBet)
                    {
                        m_round++;
                        emit roundChanged(m_round);
                        PlayerWidget* temp1 =   m_currentPlayer->getNextPlayer();
                        int i = 0;
                        while(i < m_numberOfPlayers)
                        {
                            temp1->changeLastBet(0);
                            temp1   =   temp1->getNextPlayer();
                            i++;
                        }
                        m_currentBet = 0;
                    }
                    m_currentPlayer = temp;
                    emit playerChanged(m_currentPlayer->getName());
                    emit amountChanged(m_currentPlayer->getAmount());
                }
                else
                {
                    if(m_roundStartPlayer->getLastBet() == m_currentBet)
                    {
                        m_round++;
                        emit roundChanged(m_round);
                        PlayerWidget* temp1 =   m_currentPlayer->getNextPlayer();
                        int i = 0;
                        while(i < m_numberOfPlayers)
                        {
                            temp1->changeLastBet(0);
                            temp1   =   temp1->getNextPlayer();
                            i++;
                        }
                        m_currentBet = 0;
                    }
                    m_currentPlayer = m_roundStartPlayer;
                    emit playerChanged(m_currentPlayer->getName());
                    emit amountChanged(m_currentPlayer->getAmount());
                }
            }
            else if(m_currentPlayer->getNextPlayer()->getGameStatus())
            {
                m_currentPlayer = m_currentPlayer->getNextPlayer();
                emit playerChanged(m_currentPlayer->getName());
                emit amountChanged(m_currentPlayer->getAmount());
            }
            else
            {
                PlayerWidget* m_temp = m_currentPlayer->getNextPlayer();
                while(!m_temp->getGameStatus())
                {
                    m_temp = m_temp->getNextPlayer();
                }
                m_currentPlayer = m_temp;
                emit playerChanged(m_currentPlayer->getName());
                emit amountChanged(m_currentPlayer->getAmount());
            }
        }
        else
        {
            m_pickWinner    =   true;
        }
    }
    else
    {
            return;
    }
}

void    TableWidget::on_pb_0_released()
{
    if(m_pickWinner)
    {
        m_player0->plusAmount(m_pot);
        m_pot   =   0;
        m_round =   0;
        emit    roundChanged(m_round);
        m_sBlindPlayer  =   m_sBlindPlayer->getNextPlayer();
        m_sblind       +=   5;
        emit sblindChanged(m_sblind);
        m_sBlindPlayer->minusAmount(m_sblind);
        m_sBlindPlayer->changeLastBet(0);
        m_bBlindPlayer  =   m_bBlindPlayer->getNextPlayer();
        m_bblind        =   2*m_sblind;
        m_bBlindPlayer->minusAmount(m_bblind);
        m_bBlindPlayer->changeLastBet(0);
        m_pot          +=   m_sblind + m_bblind;
        emit    potChanged(m_pot);
        m_roundStartPlayer  =   m_roundStartPlayer->getNextPlayer();
        m_currentPlayer =   m_roundStartPlayer;
        emit    playerChanged(m_currentPlayer->getName());
        emit    amountChanged(m_currentPlayer->getAmount());
        m_currentBet    =   0;
        int i = 0;
        while(i < m_numberOfPlayers)
        {
            PlayerWidget*   temp    =   m_currentPlayer->getNextPlayer();
            if(!temp->getNextPlayer()->getGameStatus())
            {
                temp->getNextPlayer()->changeLastBet(0);
                temp->getNextPlayer()->setGameStatus(true);
                m_playersStillIn++;
            }
            else
                temp    =   temp->getNextPlayer();
            i++;
        }
        m_pickWinner    =   false;
    }
}

void    TableWidget::on_pb_1_released()
{
    if(m_pickWinner)
    {
        m_player1->plusAmount(m_pot);
        m_pot   =   0;
        m_round =   0;
        emit    roundChanged(m_round);
        m_sBlindPlayer  =   m_sBlindPlayer->getNextPlayer();
        m_sblind       +=   5;
        emit sblindChanged(m_sblind);
        m_sBlindPlayer->minusAmount(m_sblind);
        m_sBlindPlayer->changeLastBet(0);
        m_bBlindPlayer  =   m_bBlindPlayer->getNextPlayer();
        m_bblind        =   2*m_sblind;
        m_bBlindPlayer->minusAmount(m_bblind);
        m_bBlindPlayer->changeLastBet(0);
        m_pot          +=   m_sblind + m_bblind;
        emit    potChanged(m_pot);
        m_roundStartPlayer  =   m_roundStartPlayer->getNextPlayer();
        m_currentPlayer =   m_roundStartPlayer;
        emit    playerChanged(m_currentPlayer->getName());
        emit    amountChanged(m_currentPlayer->getAmount());
        m_currentBet    =   0;
        int i = 0;
        while(i < m_numberOfPlayers)
        {
            PlayerWidget*   temp    =   m_currentPlayer->getNextPlayer();
            if(!temp->getNextPlayer()->getGameStatus())
            {
                temp->getNextPlayer()->changeLastBet(0);
                temp->getNextPlayer()->setGameStatus(true);
                m_playersStillIn++;
            }
            else
                temp    =   temp->getNextPlayer();
            i++;
        }
        m_pickWinner    =   false;
    }
}

void    TableWidget::on_pb_2_released()
{
    if(m_pickWinner)
    {
        m_player2->plusAmount(m_pot);
        m_pot   =   0;
        m_round =   0;
        emit    roundChanged(m_round);
        m_sBlindPlayer  =   m_sBlindPlayer->getNextPlayer();
        m_sblind       +=   5;
        emit sblindChanged(m_sblind);
        m_sBlindPlayer->minusAmount(m_sblind);
        m_sBlindPlayer->changeLastBet(0);
        m_bBlindPlayer  =   m_bBlindPlayer->getNextPlayer();
        m_bblind        =   2*m_sblind;
        m_bBlindPlayer->minusAmount(m_bblind);
        m_bBlindPlayer->changeLastBet(0);
        m_pot          +=   m_sblind + m_bblind;
        emit    potChanged(m_pot);
        m_roundStartPlayer  =   m_roundStartPlayer->getNextPlayer();
        m_currentPlayer =   m_roundStartPlayer;
        emit    playerChanged(m_currentPlayer->getName());
        emit    amountChanged(m_currentPlayer->getAmount());
        m_currentBet    =   0;
        int i = 0;
        while(i < m_numberOfPlayers)
        {
            PlayerWidget*   temp    =   m_currentPlayer->getNextPlayer();
            if(!temp->getNextPlayer()->getGameStatus())
            {
                temp->getNextPlayer()->changeLastBet(0);
                temp->getNextPlayer()->setGameStatus(true);
                m_playersStillIn++;
            }
            else
                temp    =   temp->getNextPlayer();
            i++;
        }
        m_pickWinner    =   false;
    }
}

void    TableWidget::on_pb_3_released()
{
    if(m_pickWinner)
    {
        m_player3->plusAmount(m_pot);
        m_pot   =   0;
        m_round =   0;
        emit    roundChanged(m_round);
        m_sBlindPlayer  =   m_sBlindPlayer->getNextPlayer();
        m_sblind       +=   5;
        emit sblindChanged(m_sblind);
        m_sBlindPlayer->minusAmount(m_sblind);
        m_sBlindPlayer->changeLastBet(0);
        m_bBlindPlayer  =   m_bBlindPlayer->getNextPlayer();
        m_bblind        =   2*m_sblind;
        m_bBlindPlayer->minusAmount(m_bblind);
        m_bBlindPlayer->changeLastBet(0);
        m_pot          +=   m_sblind + m_bblind;
        emit    potChanged(m_pot);
        m_roundStartPlayer  =   m_roundStartPlayer->getNextPlayer();
        m_currentPlayer =   m_roundStartPlayer;
        emit    playerChanged(m_currentPlayer->getName());
        emit    amountChanged(m_currentPlayer->getAmount());
        m_currentBet    =   0;
        int i = 0;
        while(i < m_numberOfPlayers)
        {
            PlayerWidget*   temp    =   m_currentPlayer->getNextPlayer();
            if(!temp->getNextPlayer()->getGameStatus())
            {
                temp->getNextPlayer()->changeLastBet(0);
                temp->getNextPlayer()->setGameStatus(true);
                m_playersStillIn++;
            }
            else
                temp    =   temp->getNextPlayer();
            i++;
        }
        m_pickWinner    =   false;
    }
}

void    TableWidget::on_pb_4_released()
{
    if(m_pickWinner)
    {
        m_player4->plusAmount(m_pot);
        m_pot   =   0;
        m_round =   0;
        emit    roundChanged(m_round);
        m_sBlindPlayer  =   m_sBlindPlayer->getNextPlayer();
        m_sblind       +=   5;
        emit sblindChanged(m_sblind);
        m_sBlindPlayer->minusAmount(m_sblind);
        m_sBlindPlayer->changeLastBet(0);
        m_bBlindPlayer  =   m_bBlindPlayer->getNextPlayer();
        m_bblind        =   2*m_sblind;
        m_bBlindPlayer->minusAmount(m_bblind);
        m_bBlindPlayer->changeLastBet(0);
        m_pot          +=   m_sblind + m_bblind;
        emit    potChanged(m_pot);
        m_roundStartPlayer  =   m_roundStartPlayer->getNextPlayer();
        m_currentPlayer =   m_roundStartPlayer;
        emit    playerChanged(m_currentPlayer->getName());
        emit    amountChanged(m_currentPlayer->getAmount());
        m_currentBet    =   0;
        int i = 0;
        while(i < m_numberOfPlayers)
        {
            PlayerWidget*   temp    =   m_currentPlayer->getNextPlayer();
            if(!temp->getNextPlayer()->getGameStatus())
            {
                temp->getNextPlayer()->changeLastBet(0);
                temp->getNextPlayer()->setGameStatus(true);
                m_playersStillIn++;
            }
            else
                temp    =   temp->getNextPlayer();
            i++;
        }
        m_pickWinner    =   false;
    }
}

void    TableWidget::on_pb_5_released()
{
    if(m_pickWinner)
    {
        m_player5->plusAmount(m_pot);
        m_pot   =   0;
        m_round =   0;
        emit    roundChanged(m_round);
        m_sBlindPlayer  =   m_sBlindPlayer->getNextPlayer();
        m_sblind       +=   5;
        emit sblindChanged(m_sblind);
        m_sBlindPlayer->minusAmount(m_sblind);
        m_sBlindPlayer->changeLastBet(0);
        m_bBlindPlayer  =   m_bBlindPlayer->getNextPlayer();
        m_bblind        =   2*m_sblind;
        m_bBlindPlayer->minusAmount(m_bblind);
        m_bBlindPlayer->changeLastBet(0);
        m_pot          +=   m_sblind + m_bblind;
        emit    potChanged(m_pot);
        m_roundStartPlayer  =   m_roundStartPlayer->getNextPlayer();
        m_currentPlayer =   m_roundStartPlayer;
        emit    playerChanged(m_currentPlayer->getName());
        emit    amountChanged(m_currentPlayer->getAmount());
        m_currentBet    =   0;
        int i = 0;
        while(i < m_numberOfPlayers)
        {
            PlayerWidget*   temp    =   m_currentPlayer->getNextPlayer();
            if(!temp->getNextPlayer()->getGameStatus())
            {
                temp->getNextPlayer()->changeLastBet(0);
                temp->getNextPlayer()->setGameStatus(true);
                m_playersStillIn++;
            }
            else
                temp    =   temp->getNextPlayer();
            i++;
        }
        m_pickWinner    =   false;
    }
}

void    TableWidget::on_pb_6_released()
{
    if(m_pickWinner)
    {
        m_player6->plusAmount(m_pot);
        m_pot   =   0;
        m_round =   0;
        emit    roundChanged(m_round);
        m_sBlindPlayer  =   m_sBlindPlayer->getNextPlayer();
        m_sblind       +=   5;
        emit sblindChanged(m_sblind);
        m_sBlindPlayer->minusAmount(m_sblind);
        m_sBlindPlayer->changeLastBet(0);
        m_bBlindPlayer  =   m_bBlindPlayer->getNextPlayer();
        m_bblind        =   2*m_sblind;
        m_bBlindPlayer->minusAmount(m_bblind);
        m_bBlindPlayer->changeLastBet(0);
        m_pot          +=   m_sblind + m_bblind;
        emit    potChanged(m_pot);
        m_roundStartPlayer  =   m_roundStartPlayer->getNextPlayer();
        m_currentPlayer =   m_roundStartPlayer;
        emit    playerChanged(m_currentPlayer->getName());
        emit    amountChanged(m_currentPlayer->getAmount());
        m_currentBet    =   0;
        int i = 0;
        while(i < m_numberOfPlayers)
        {
            PlayerWidget*   temp    =   m_currentPlayer->getNextPlayer();
            if(!temp->getNextPlayer()->getGameStatus())
            {
                temp->getNextPlayer()->changeLastBet(0);
                temp->getNextPlayer()->setGameStatus(true);
                m_playersStillIn++;
            }
            else
                temp    =   temp->getNextPlayer();
            i++;
        }
        m_pickWinner    =   false;
    }
}

void    TableWidget::on_pb_7_released()
{
    if(m_pickWinner)
    {
        m_player7->plusAmount(m_pot);
        m_pot   =   0;
        m_round =   0;
        emit    roundChanged(m_round);
        m_sBlindPlayer  =   m_sBlindPlayer->getNextPlayer();
        m_sblind       +=   5;
        emit sblindChanged(m_sblind);
        m_sBlindPlayer->minusAmount(m_sblind);
        m_sBlindPlayer->changeLastBet(0);
        m_bBlindPlayer  =   m_bBlindPlayer->getNextPlayer();
        m_bblind        =   2*m_sblind;
        m_bBlindPlayer->minusAmount(m_bblind);
        m_bBlindPlayer->changeLastBet(0);
        m_pot          +=   m_sblind + m_bblind;
        emit    potChanged(m_pot);
        m_roundStartPlayer  =   m_roundStartPlayer->getNextPlayer();
        m_currentPlayer =   m_roundStartPlayer;
        emit    playerChanged(m_currentPlayer->getName());
        emit    amountChanged(m_currentPlayer->getAmount());
        m_currentBet    =   0;
        int i = 0;
        while(i < m_numberOfPlayers)
        {
            PlayerWidget*   temp    =   m_currentPlayer->getNextPlayer();
            if(!temp->getNextPlayer()->getGameStatus())
            {
                temp->getNextPlayer()->changeLastBet(0);
                temp->getNextPlayer()->setGameStatus(true);
                m_playersStillIn++;
            }
            else
                temp    =   temp->getNextPlayer();
            i++;
        }
        m_pickWinner    =   false;
    }
}

void    TableWidget::on_pb_8_released()
{
    if(m_pickWinner)
    {
        m_player8->plusAmount(m_pot);
        m_pot   =   0;
        m_round =   0;
        emit    roundChanged(m_round);
        m_sBlindPlayer  =   m_sBlindPlayer->getNextPlayer();
        m_sblind       +=   5;
        emit sblindChanged(m_sblind);
        m_sBlindPlayer->minusAmount(m_sblind);
        m_sBlindPlayer->changeLastBet(0);
        m_bBlindPlayer  =   m_bBlindPlayer->getNextPlayer();
        m_bblind        =   2*m_sblind;
        m_bBlindPlayer->minusAmount(m_bblind);
        m_bBlindPlayer->changeLastBet(0);
        m_pot          +=   m_sblind + m_bblind;
        emit    potChanged(m_pot);
        m_roundStartPlayer  =   m_roundStartPlayer->getNextPlayer();
        m_currentPlayer =   m_roundStartPlayer;
        emit    playerChanged(m_currentPlayer->getName());
        emit    amountChanged(m_currentPlayer->getAmount());
        m_currentBet    =   0;
        int i = 0;
        while(i < m_numberOfPlayers)
        {
            PlayerWidget*   temp    =   m_currentPlayer->getNextPlayer();
            if(!temp->getNextPlayer()->getGameStatus())
            {
                temp->getNextPlayer()->changeLastBet(0);
                temp->getNextPlayer()->setGameStatus(true);
                m_playersStillIn++;
            }
            else
                temp    =   temp->getNextPlayer();
            i++;
        }
        m_pickWinner    =   false;
    }
}

void    TableWidget::on_pb_9_released()
{
    if(m_pickWinner)
    {
        m_player9->plusAmount(m_pot);
        m_pot   =   0;
        m_round =   0;
        emit    roundChanged(m_round);
        m_sBlindPlayer  =   m_sBlindPlayer->getNextPlayer();
        m_sblind       +=   5;
        emit sblindChanged(m_sblind);
        m_sBlindPlayer->minusAmount(m_sblind);
        m_sBlindPlayer->changeLastBet(0);
        m_bBlindPlayer  =   m_bBlindPlayer->getNextPlayer();
        m_bblind        =   2*m_sblind;
        m_bBlindPlayer->minusAmount(m_bblind);
        m_bBlindPlayer->changeLastBet(0);
        m_pot          +=   m_sblind + m_bblind;
        emit    potChanged(m_pot);
        m_roundStartPlayer  =   m_roundStartPlayer->getNextPlayer();
        m_currentPlayer =   m_roundStartPlayer;
        emit    playerChanged(m_currentPlayer->getName());
        emit    amountChanged(m_currentPlayer->getAmount());
        m_currentBet    =   0;
        int i = 0;
        while(i < m_numberOfPlayers)
        {
            PlayerWidget*   temp    =   m_currentPlayer->getNextPlayer();
            if(!temp->getNextPlayer()->getGameStatus())
            {
                temp->getNextPlayer()->changeLastBet(0);
                temp->getNextPlayer()->setGameStatus(true);
                m_playersStillIn++;
            }
            else
                temp    =   temp->getNextPlayer();
            i++;
        }
        m_pickWinner    =   false;
    }
}

void        TableWidget::on_round_changed(int x)
{
    if(x == 0)
    {
        m_lround->setText("Please Place Initial Bets");
    }
    else if(x == 1)
    {
        m_lround->setText("FLOP");
    }
    else if(x == 2)
    {
        m_lround->setText("TURN");
    }
    else if(x == 3)
    {
        m_lround->setText("RIVER");
    }
    else
    {
        m_lround->setText("Please Select The Winner");
    }
}

QGroupBox*  TableWidget::makeOptionsGroupBox()
{
    QGridLayout* grid           =   new QGridLayout(this);
    QGroupBox*   options        =   new QGroupBox(tr("Options"),this);
    QPushButton* pb_raise       =   new QPushButton(tr("Raise"));
    QPushButton* pb_fold        =   new QPushButton(tr("Fold"));
    QPushButton* pb_call        =   new QPushButton(tr("Call"));
    QPushButton* pb_check       =   new QPushButton(tr("Check"));
    connect(pb_call,    SIGNAL(released()), this,   SLOT(on_pb_call_released()));
    connect(pb_fold,    SIGNAL(released()), this,   SLOT(on_pb_fold_released()));
    connect(pb_check,   SIGNAL(released()), this,   SLOT(on_pb_check_released()));
    connect(pb_raise,   SIGNAL(released()), this,   SLOT(on_pb_raise_released()));
    grid->addWidget(pb_raise, 0, 0);
    grid->addWidget(pb_fold, 0, 1);
    grid->addWidget(pb_call, 0, 2);
    grid->addWidget(pb_check, 0, 3);
    options->setMaximumHeight(options->parentWidget()->parentWidget()->parentWidget()->height()/8);
    options->setMinimumHeight(options->parentWidget()->parentWidget()->parentWidget()->height()/8);
    options->setLayout(grid);
    return options;
}

QGroupBox*  TableWidget::makePlayerPushButtons()
{
    QGridLayout*    grid    =   new QGridLayout(this);
    QLabel*         pot     =   new QLabel("Pot: ", this);
    pot->setAlignment(Qt::AlignCenter);
    m_lpot                  =   new QLabel(QString::number(m_pot),this);
    m_lpot->setAlignment(Qt::AlignCenter);
    connect(this,   SIGNAL(potChanged(int)),    m_lpot, SLOT(setNum(int)));
    QLabel*         round   =   new QLabel("Round: ", this);
    round->setAlignment(Qt::AlignCenter);
    m_lround                =   new QLabel("Please Place Initial Bets", this);
    m_lround->setAlignment(Qt::AlignCenter);
    connect(this,   SIGNAL(roundChanged(int)),  this,       SLOT(on_round_changed(int)));
    QLabel*         sblind  =   new QLabel("Small Blind: ", this);
    sblind->setAlignment(Qt::AlignCenter);
    m_lsblind               =   new QLabel(QString::number(m_sblind),   this);
    m_lsblind->setAlignment(Qt::AlignCenter);
    connect(this,   SIGNAL(sblindChanged(int)), m_lsblind,  SLOT(setNum(int)));
    m_pb_0  =   new QPushButton(m_player0->getName(),this);
    connect(m_pb_0, SIGNAL(released()), this,   SLOT(on_pb_0_released()));
    m_pb_1  =   new QPushButton(m_player1->getName(),this);
    connect(m_pb_1, SIGNAL(released()), this,   SLOT(on_pb_1_released()));
    if(m_numberOfPlayers >= 3)
    {
        m_pb_2  =   new QPushButton(m_player2->getName(),this);
        connect(m_pb_2, SIGNAL(released()), this,   SLOT(on_pb_2_released()));
        if(m_numberOfPlayers >= 4)
        {
            m_pb_3  =   new QPushButton(m_player3->getName(),this);
            connect(m_pb_3, SIGNAL(released()), this,   SLOT(on_pb_3_released()));
            if(m_numberOfPlayers >= 5)
            {
                m_pb_4  =   new QPushButton(m_player4->getName(),this);
                connect(m_pb_4, SIGNAL(released()), this,   SLOT(on_pb_4_released()));
                if(m_numberOfPlayers >= 6)
                {
                    m_pb_5  =   new QPushButton(m_player5->getName(),this);
                    connect(m_pb_5, SIGNAL(released()), this,   SLOT(on_pb_5_released()));
                    if(m_numberOfPlayers >= 7)
                    {
                        m_pb_6  =   new QPushButton(m_player6->getName(),this);
                        connect(m_pb_6, SIGNAL(released()), this,   SLOT(on_pb_6_released()));
                        if(m_numberOfPlayers >= 8)
                        {
                            m_pb_7  =   new QPushButton(m_player7->getName(),this);
                            connect(m_pb_7, SIGNAL(released()), this,   SLOT(on_pb_7_released()));
                            if(m_numberOfPlayers >= 9)
                            {
                                m_pb_8  =   new QPushButton(m_player8->getName(),this);
                                connect(m_pb_8, SIGNAL(released()), this,   SLOT(on_pb_8_released()));
                                if(m_numberOfPlayers == 10)
                                {
                                    m_pb_9  =   new QPushButton(m_player9->getName(),this);
                                    connect(m_pb_9, SIGNAL(released()), this,   SLOT(on_pb_9_released()));
                                    grid->addWidget(m_pb_0,1,0);
                                    grid->addWidget(m_pb_1,0,1);
                                    grid->addWidget(m_pb_2,0,2);
                                    grid->addWidget(m_pb_3,1,3);
                                    grid->addWidget(m_pb_4,2,3);
                                    grid->addWidget(m_pb_5,3,3);
                                    grid->addWidget(m_pb_6,4,2);
                                    grid->addWidget(m_pb_7,4,1);
                                    grid->addWidget(m_pb_8,3,0);
                                    grid->addWidget(m_pb_9,2,0);
                                    grid->addWidget(pot,1,1);
                                    grid->addWidget(m_lpot,1,2);
                                    grid->addWidget(sblind,2,1);
                                    grid->addWidget(m_lsblind,2,2);
                                    grid->addWidget(round,3,1);
                                    grid->addWidget(m_lround,3,2);

                                }
                                else
                                {
                                    grid->addWidget(m_pb_0,1,0);
                                    grid->addWidget(m_pb_1,0,1);
                                    grid->addWidget(m_pb_2,0,2);
                                    grid->addWidget(m_pb_3,1,3);
                                    grid->addWidget(m_pb_4,2,3);
                                    grid->addWidget(m_pb_5,3,3);
                                    grid->addWidget(m_pb_6,4,2);
                                    grid->addWidget(m_pb_7,4,1);
                                    grid->addWidget(m_pb_8,3,0);
                                    grid->addWidget(pot,1,1);
                                    grid->addWidget(m_lpot,1,2);
                                    grid->addWidget(sblind,2,1);
                                    grid->addWidget(m_lsblind,2,2);
                                    grid->addWidget(round,3,1);
                                    grid->addWidget(m_lround,3,2);
                                }
                            }
                            else
                            {
                                grid->addWidget(m_pb_0,1,0);
                                grid->addWidget(m_pb_1,0,2);
                                grid->addWidget(m_pb_2,1,4);
                                grid->addWidget(m_pb_3,2,4);
                                grid->addWidget(m_pb_4,3,4);
                                grid->addWidget(m_pb_5,4,2);
                                grid->addWidget(m_pb_6,3,0);
                                grid->addWidget(m_pb_7,2,0);
                                grid->addWidget(pot,1,1);
                                grid->addWidget(m_lpot,1,3);
                                grid->addWidget(sblind,2,1);
                                grid->addWidget(m_lsblind,2,2);
                                grid->addWidget(round,3,1);
                                grid->addWidget(m_lround,3,3);
                            }
                        }
                        else
                        {
                            grid->addWidget(m_pb_0,1,0);
                            grid->addWidget(m_pb_1,0,2);
                            grid->addWidget(m_pb_2,1,4);
                            grid->addWidget(m_pb_3,2,4);
                            grid->addWidget(m_pb_4,3,4);
                            grid->addWidget(m_pb_5,4,2);
                            grid->addWidget(m_pb_6,3,0);
                            grid->addWidget(pot,1,1);
                            grid->addWidget(m_lpot,1,3);
                            grid->addWidget(sblind,2,1);
                            grid->addWidget(m_lsblind,2,2);
                            grid->addWidget(round,3,1);
                            grid->addWidget(m_lround,3,3);
                        }
                    }
                    else
                    {
                        grid->addWidget(m_pb_0,1,0);
                        grid->addWidget(m_pb_1,1,3);
                        grid->addWidget(m_pb_2,2,3);
                        grid->addWidget(m_pb_3,3,3);
                        grid->addWidget(m_pb_4,3,0);
                        grid->addWidget(m_pb_5,2,0);
                        grid->addWidget(pot,1,1);
                        grid->addWidget(m_lpot,1,2);
                        grid->addWidget(sblind,2,1);
                        grid->addWidget(m_lsblind,2,2);
                        grid->addWidget(round,3,1);
                        grid->addWidget(m_lround,3,2);
                    }
                }
                else
                {
                    grid->addWidget(m_pb_0,1,0);
                    grid->addWidget(m_pb_1,1,3);
                    grid->addWidget(m_pb_2,2,3);
                    grid->addWidget(m_pb_3,3,3);
                    grid->addWidget(m_pb_4,3,0);
                    grid->addWidget(pot,1,1);
                    grid->addWidget(m_lpot,1,2);
                    grid->addWidget(sblind,2,1);
                    grid->addWidget(m_lsblind,2,2);
                    grid->addWidget(round,3,1);
                    grid->addWidget(m_lround,3,2);
                }
            }
            else
            {
                grid->addWidget(m_pb_0,1,0);
                grid->addWidget(m_pb_1,1,3);
                grid->addWidget(m_pb_2,3,3);
                grid->addWidget(m_pb_3,3,0);
                grid->addWidget(pot,1,1);
                grid->addWidget(m_lpot,1,2);
                grid->addWidget(sblind,2,1);
                grid->addWidget(m_lsblind,2,2);
                grid->addWidget(round,3,1);
                grid->addWidget(m_lround,3,2);
            }
        }
        else
        {
            grid->addWidget(m_pb_0,1,0);
            grid->addWidget(m_pb_1,1,3);
            grid->addWidget(m_pb_2,3,3);
            grid->addWidget(pot,1,1);
            grid->addWidget(m_lpot,1,2);
            grid->addWidget(sblind,2,1);
            grid->addWidget(m_lsblind,2,2);
            grid->addWidget(round,3,1);
            grid->addWidget(m_lround,3,2);
        }
    }
    else
    {
        grid->addWidget(m_pb_0,2,0);
        grid->addWidget(m_pb_1,2,3);
        grid->addWidget(pot,1,1);
        grid->addWidget(m_lpot,1,2);
        grid->addWidget(sblind,2,1);
        grid->addWidget(m_lsblind,2,2);
        grid->addWidget(round,3,1);
        grid->addWidget(m_lround,3,2);
    }
    QGroupBox*      groupbox    =   new QGroupBox("Table", this);
    groupbox->setLayout(grid);
    return groupbox;
}
