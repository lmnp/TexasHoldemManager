#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent, int blind, int players, QString* names, int* amounts) :
    QWidget(parent)
{
    m_sblind                    = blind;
    m_bblind                    = m_sblind*2;
    m_numberOfPlayers           = players;
    m_playersStillIn            = m_numberOfPlayers;
    m_pot                       = 0;
    m_currentBet                = 0;
    m_player0                   = new PlayerWidget(this, names[0], amounts[0], true);
    m_player1                   = new PlayerWidget(this, names[1], amounts[1]);
    m_player0->setNextPlayer(m_player1);
    m_currentPlayer             = m_player0;
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
    vbox->addWidget(makeTabWidget());
    setLayout(vbox);
}

void        TableWidget::on_pb_call_released()
{
    int diff    =   m_currentBet    -   m_currentPlayer->getLastBet();
    m_currentPlayer->changeAmount(diff);
    if(m_playersStillIn > 1)
    {
        if(m_currentPlayer->getNextPlayer()->getGameStatus())
            m_currentPlayer = m_currentPlayer->getNextPlayer();
        else
        {
            PlayerWidget* m_temp = m_currentPlayer->getNextPlayer();
            while(!m_temp->getGameStatus())
            {
                m_temp = m_temp->getNextPlayer();
            }
            m_currentPlayer = m_temp;
            emit playerChanged(m_currentPlayer->getName());
        }
    }
}

void        TableWidget::on_pb_fold_released()
{
    m_currentPlayer->setGameStatus(false);
    m_playersStillIn--;
    if(m_playersStillIn > 1)
    {
        if(m_currentPlayer->getNextPlayer()->getGameStatus())
            m_currentPlayer = m_currentPlayer->getNextPlayer();
        else
        {
            PlayerWidget* m_temp = m_currentPlayer->getNextPlayer();
            while(!m_temp->getGameStatus())
            {
                m_temp = m_temp->getNextPlayer();
            }
            m_currentPlayer = m_temp;
            emit playerChanged(m_currentPlayer->getName());
        }
    }
}

void        TableWidget::on_pb_check_released()
{
    if(m_currentBet == 0)
    {
        m_currentPlayer->changeAmount(0);
        m_currentBet    =   0;
        if(m_playersStillIn > 1)
        {
            if(m_currentPlayer->getNextPlayer()->getGameStatus())
                m_currentPlayer = m_currentPlayer->getNextPlayer();
            else
            {
                PlayerWidget* m_temp = m_currentPlayer->getNextPlayer();
                while(!m_temp->getGameStatus())
                {
                    m_temp = m_temp->getNextPlayer();
                }
                m_currentPlayer = m_temp;
                emit playerChanged(m_currentPlayer->getName());
            }
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
        m_currentPlayer->changeAmount(x);
        m_currentBet    =   x;
        if(m_playersStillIn > 1)
        {
            if(m_currentPlayer->getNextPlayer()->getGameStatus())
                m_currentPlayer = m_currentPlayer->getNextPlayer();
            else
            {
                PlayerWidget* m_temp = m_currentPlayer->getNextPlayer();
                while(!m_temp->getGameStatus())
                {
                    m_temp = m_temp->getNextPlayer();
                }
                m_currentPlayer = m_temp;
                emit playerChanged(m_currentPlayer->getName());
            }
        }
    }
    else
    {
            return;
    }
}

QGroupBox*  TableWidget::makeCurrentGroupBox()
{
    QGridLayout* grid           =   new QGridLayout(this);
    QLabel*      l_name         =   new QLabel(tr("Name "));
    QLabel*      l_amount       =   new QLabel(tr("Amount "));
    m_currentPlayerName         =   new QLabel(m_currentPlayer->getName());
    m_currentPlayerAmount       =   new QLabel(QString::number(m_currentPlayer->getAmount()));
    QGroupBox*   options        =   new QGroupBox(tr("Options"));
    QGridLayout* o_grid         =   new QGridLayout(this);
    QPushButton* pb_raise       =   new QPushButton(tr("Raise"));
    QPushButton* pb_fold        =   new QPushButton(tr("Fold"));
    QPushButton* pb_call        =   new QPushButton(tr("Call"));
    QPushButton* pb_check       =   new QPushButton(tr("Check"));
    connect(pb_call,    SIGNAL(released()), this,   SLOT(on_pb_call_released()));
    connect(pb_fold,    SIGNAL(released()), this,   SLOT(on_pb_fold_released()));
    connect(pb_check,   SIGNAL(released()), this,   SLOT(on_pb_check_released()));
    connect(pb_raise,   SIGNAL(released()), this,   SLOT(on_pb_raise_released()));
    connect(m_currentPlayer, SIGNAL(amountChanged(int)),        m_currentPlayerAmount,  SLOT(setNum(int)));
    connect(this,            SIGNAL(playerChanged(QString)),    m_currentPlayerName,    SLOT(setText(QString)));
    grid->addWidget(l_name,0,0);
    grid->addWidget(l_amount,1,0);
    grid->addWidget(m_currentPlayerName,0,1);
    grid->addWidget(m_currentPlayerAmount,1,1);
    o_grid->addWidget(pb_raise, 0, 0);
    o_grid->addWidget(pb_fold, 0, 1);
    o_grid->addWidget(pb_call, 1, 0);
    o_grid->addWidget(pb_check, 1, 1);
    options->setLayout(o_grid);
    grid->addWidget(options, 0, 2, 2, 2);
    QGroupBox*  groupbox    =    new QGroupBox(this);
    groupbox->setLayout(grid);
    return groupbox;
}

QGroupBox*  TableWidget::makeOtherGroupBox()
{
    QGridLayout* grid   =   new QGridLayout(this);
    QLabel* name = new QLabel(m_player0->getName(),this);
    name->setAlignment(Qt::AlignCenter);
    grid->addWidget(name,0,0);
    name = new QLabel(m_player1->getName(),this);
    name->setAlignment(Qt::AlignCenter);
    grid->addWidget(name,1,0);
    if(m_numberOfPlayers >= 3)
    {
        name    =   new QLabel(m_player2->getName(),this);
        name->setAlignment(Qt::AlignCenter);
        grid->addWidget(name,2,0);
        if(m_numberOfPlayers >= 4)
        {
            name    =   new QLabel(m_player3->getName(),this);
            name->setAlignment(Qt::AlignCenter);
            grid->addWidget(name,3,0);
            if(m_numberOfPlayers >= 5)
            {
                name    =   new QLabel(m_player4->getName(),this);
                name->setAlignment(Qt::AlignCenter);
                grid->addWidget(name,4,0);
                if(m_numberOfPlayers >= 6)
                {
                    name    =   new QLabel(m_player5->getName(),this);
                    name->setAlignment(Qt::AlignCenter);
                    grid->addWidget(name,5,0);
                    if(m_numberOfPlayers >= 7)
                    {
                        name    =   new QLabel(m_player6->getName(),this);
                        name->setAlignment(Qt::AlignCenter);
                        grid->addWidget(name,6,0);
                        if(m_numberOfPlayers >= 8)
                        {
                            name    =   new QLabel(m_player7->getName(),this);
                            name->setAlignment(Qt::AlignCenter);
                            grid->addWidget(name,7,0);
                            if(m_numberOfPlayers >= 9)
                            {
                                name    =   new QLabel(m_player8->getName(),this);
                                name->setAlignment(Qt::AlignCenter);
                                grid->addWidget(name,8,0);
                                if(m_numberOfPlayers == 10)
                                {
                                    name    =   new QLabel(m_player9->getName(),this);
                                    name->setAlignment(Qt::AlignCenter);
                                    grid->addWidget(name,9,0);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    m_amount0 = new QLabel(QString::number(m_player0->getAmount()),this);
    connect(m_player0, SIGNAL(amountChanged(int)),m_amount0, SLOT(setNum(int)));
    m_amount0->setAlignment(Qt::AlignCenter);
    grid->addWidget(m_amount0,0,1);
    m_amount1 = new QLabel(QString::number(m_player1->getAmount()),this);
    connect(m_player1, SIGNAL(amountChanged(int)),m_amount1, SLOT(setNum(int)));
    m_amount1->setAlignment(Qt::AlignCenter);
    grid->addWidget(m_amount1,1,1);
    if(m_numberOfPlayers >= 3)
    {
        m_amount2    =   new QLabel(QString::number(m_player2->getAmount()),this);
        connect(m_player2, SIGNAL(amountChanged(int)),m_amount2, SLOT(setNum(int)));
        m_amount2->setAlignment(Qt::AlignCenter);
        grid->addWidget(m_amount2,2,1);
        if(m_numberOfPlayers >= 4)
        {
            m_amount3    =   new QLabel(QString::number(m_player3->getAmount()),this);
            connect(m_player3, SIGNAL(amountChanged(int)),m_amount3, SLOT(setNum(int)));
            m_amount3->setAlignment(Qt::AlignCenter);
            grid->addWidget(m_amount3,3,1);
            if(m_numberOfPlayers >= 5)
            {
                m_amount4    =   new QLabel(QString::number(m_player4->getAmount()),this);
                connect(m_player4, SIGNAL(amountChanged(int)),m_amount4, SLOT(setNum(int)));
                m_amount4->setAlignment(Qt::AlignCenter);
                grid->addWidget(m_amount4,4,1);
                if(m_numberOfPlayers >= 6)
                {
                    m_amount5    =   new QLabel(QString::number(m_player5->getAmount()),this);
                    connect(m_player5, SIGNAL(amountChanged(int)),m_amount5, SLOT(setNum(int)));
                    m_amount5->setAlignment(Qt::AlignCenter);
                    grid->addWidget(m_amount5,5,1);
                    if(m_numberOfPlayers >= 7)
                    {
                        m_amount6    =   new QLabel(QString::number(m_player6->getAmount()),this);
                        connect(m_player6, SIGNAL(amountChanged(int)),m_amount6, SLOT(setNum(int)));
                        m_amount6->setAlignment(Qt::AlignCenter);
                        grid->addWidget(m_amount6,6,1);
                        if(m_numberOfPlayers >= 8)
                        {
                            m_amount7    =   new QLabel(QString::number(m_player7->getAmount()),this);
                            connect(m_player7, SIGNAL(amountChanged(int)),m_amount7, SLOT(setNum(int)));
                            m_amount7->setAlignment(Qt::AlignCenter);
                            grid->addWidget(m_amount7,7,1);
                            if(m_numberOfPlayers >= 9)
                            {
                                m_amount8    =   new QLabel(QString::number(m_player8->getAmount()),this);
                                connect(m_player8, SIGNAL(amountChanged(int)),m_amount8, SLOT(setNum(int)));
                                m_amount8->setAlignment(Qt::AlignCenter);
                                grid->addWidget(m_amount8,8,1);
                                if(m_numberOfPlayers == 10)
                                {
                                    m_amount9    =   new QLabel(QString::number(m_player9->getAmount()),this);
                                    connect(m_player9, SIGNAL(amountChanged(int)),m_amount9, SLOT(setNum(int)));
                                    m_amount9->setAlignment(Qt::AlignCenter);
                                    grid->addWidget(m_amount9,9,1);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    QGroupBox* groupbox = new QGroupBox(this);
    groupbox->setLayout(grid);
    return groupbox;
}


QTabWidget* TableWidget::makeTabWidget()
{
    QTabWidget *maketable = new QTabWidget(this);
    maketable->addTab(makeCurrentGroupBox(),tr("Current Player"));
    maketable->addTab(makeOtherGroupBox(), tr("Other"));
    maketable->setMaximumHeight(this->parentWidget()->parentWidget()->height()/3);
    return maketable;
}

QGroupBox*  TableWidget::makePlayerPushButtons()
{
    QGridLayout*    grid    =   new QGridLayout(this);
    m_pb_0  =   new QPushButton(m_player0->getName(),this);
    m_pb_1  =   new QPushButton(m_player1->getName(),this);
    if(m_numberOfPlayers >= 3)
    {
        m_pb_2  =   new QPushButton(m_player2->getName(),this);
        if(m_numberOfPlayers >= 4)
        {
            m_pb_3  =   new QPushButton(m_player3->getName(),this);
            if(m_numberOfPlayers >= 5)
            {
                m_pb_4  =   new QPushButton(m_player4->getName(),this);
                if(m_numberOfPlayers >= 6)
                {
                    m_pb_5  =   new QPushButton(m_player5->getName(),this);
                    if(m_numberOfPlayers >= 7)
                    {
                        m_pb_6  =   new QPushButton(m_player6->getName(),this);
                        if(m_numberOfPlayers >= 8)
                        {
                            m_pb_7  =   new QPushButton(m_player7->getName(),this);
                            if(m_numberOfPlayers >= 9)
                            {
                                m_pb_8  =   new QPushButton(m_player8->getName(),this);
                                if(m_numberOfPlayers == 10)
                                {
                                    m_pb_9  =   new QPushButton(m_player9->getName(),this);
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
                    }
                }
                else
                {
                    grid->addWidget(m_pb_0,1,0);
                    grid->addWidget(m_pb_1,1,3);
                    grid->addWidget(m_pb_2,2,3);
                    grid->addWidget(m_pb_3,3,3);
                    grid->addWidget(m_pb_4,3,0);
                }
            }
            else
            {
                grid->addWidget(m_pb_0,1,0);
                grid->addWidget(m_pb_1,1,3);
                grid->addWidget(m_pb_2,3,3);
                grid->addWidget(m_pb_3,3,0);
            }
        }
        else
        {
            grid->addWidget(m_pb_0,1,0);
            grid->addWidget(m_pb_1,1,3);
            grid->addWidget(m_pb_2,3,3);
        }
    }
    else
    {
        grid->addWidget(m_pb_0,2,0);
        grid->addWidget(m_pb_1,2,3);
    }
    QGroupBox*      groupbox    =   new QGroupBox("Table", this);
    groupbox->setLayout(grid);
    return groupbox;
}
