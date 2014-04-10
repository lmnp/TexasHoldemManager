#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent, int blind, int players, QString* names, int* amounts) :
    QWidget(parent)
{
    m_sblind                    = blind;
    m_bblind                    = m_sblind*2;
    m_numberOfPlayers           = players;
    m_pot                       = 0;
    for(int i = m_numberOfPlayers; i < 10; i++)
    {
        m_status[i] = -2;
    }
    for(int i = 0; i < m_numberOfPlayers; i++)
    {
        m_status[i] = 1;
    }
    m_status[0] = 0;
    m_player0                   = new PlayerWidget(this, names[0], amounts[0]);
    m_player1                   = new PlayerWidget(this, names[1], amounts[1]);
    m_currentPlayer = m_player0;
    if(m_numberOfPlayers >= 3)
    {
        m_player2                   = new PlayerWidget(this, names[2], amounts[2]);
        if(m_numberOfPlayers >= 4)
        {
            m_player3                   = new PlayerWidget(this, names[3], amounts[3]);
            if(m_numberOfPlayers >= 5)
            {
                m_player4                   = new PlayerWidget(this, names[4], amounts[4]);
                if(m_numberOfPlayers >= 6)
                {
                    m_player5                   = new PlayerWidget(this, names[5], amounts[5]);
                    if(m_numberOfPlayers >= 7)
                    {
                        m_player6                   = new PlayerWidget(this, names[6], amounts[6]);
                        if(m_numberOfPlayers >= 8)
                        {
                            m_player7                   = new PlayerWidget(this, names[7], amounts[7]);
                            if(m_numberOfPlayers >= 9)
                            {
                                m_player8                   = new PlayerWidget(this, names[8], amounts[8]);
                                if(m_numberOfPlayers == 10)
                                {
                                    m_player9                   = new PlayerWidget(this, names[9], amounts[9]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(makeTabWidget());
    setLayout(vbox);
}

QGroupBox*  TableWidget::makeCurrentGroupBox()
{
    QGridLayout* grid      =   new QGridLayout(this);
    QLabel*      name      =   new QLabel(tr("Name "));
    QLabel*      amount    =   new QLabel(tr("Amount "));
    QGroupBox*   options   =   new QGroupBox(tr("Options"));
    QGridLayout* o_grid    =   new QGridLayout(this);
    QPushButton* raise     =   new QPushButton(tr("Raise"));
    QPushButton* fold      =   new QPushButton(tr("Fold"));
    QPushButton* call      =   new QPushButton(tr("Call"));
    QPushButton* check     =   new QPushButton(tr("Check"));
    grid->addWidget(name,0,0);
    grid->addWidget(amount,1,0);
    o_grid->addWidget(raise, 0, 0);
    o_grid->addWidget(fold, 0, 1);
    o_grid->addWidget(call, 1, 0);
    o_grid->addWidget(check, 1, 1);
    options->setLayout(o_grid);
    grid->addWidget(options, 1, 1);
    QGroupBox*  groupbox    =    new QGroupBox(this);
    groupbox->setLayout(grid);
    return groupbox;
}

QGroupBox* TableWidget::makeOtherGroupBox()
{
    QGridLayout* grid   =   new QGridLayout(this);
    QLabel* name = new QLabel(m_player0->getName(),this);
    grid->addWidget(name,0,0);
    name = new QLabel(m_player1->getName(),this);
    grid->addWidget(name,1,0);
    if(m_numberOfPlayers >= 3)
    {
        name    =   new QLabel(m_player2->getName(),this);
        grid->addWidget(name,2,0);
        if(m_numberOfPlayers >= 4)
        {
            name    =   new QLabel(m_player3->getName(),this);
            grid->addWidget(name,3,0);
            if(m_numberOfPlayers >= 5)
            {
                name    =   new QLabel(m_player4->getName(),this);
                grid->addWidget(name,4,0);
                if(m_numberOfPlayers >= 6)
                {
                    name    =   new QLabel(m_player5->getName(),this);
                    grid->addWidget(name,5,0);
                    if(m_numberOfPlayers >= 7)
                    {
                        name    =   new QLabel(m_player6->getName(),this);
                        grid->addWidget(name,6,0);
                        if(m_numberOfPlayers >= 8)
                        {
                            name    =   new QLabel(m_player7->getName(),this);
                            grid->addWidget(name,7,0);
                            if(m_numberOfPlayers >= 9)
                            {
                                name    =   new QLabel(m_player8->getName(),this);
                                grid->addWidget(name,8,0);
                                if(m_numberOfPlayers == 10)
                                {
                                    name    =   new QLabel(m_player9->getName(),this);
                                    grid->addWidget(name,9,0);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    QLabel* amount0 = new QLabel(QString::number(m_player0->getAmount()),this);
    grid->addWidget(amount0,0,1);
    QLabel* amount1 = new QLabel(QString::number(m_player1->getAmount()),this);
    grid->addWidget(amount1,1,1);
    if(m_numberOfPlayers >= 3)
    {
        QLabel* amount2    =   new QLabel(QString::number(m_player2->getAmount()),this);
        grid->addWidget(amount2,2,1);
        if(m_numberOfPlayers >= 4)
        {
            QLabel* amount3    =   new QLabel(QString::number(m_player3->getAmount()),this);
            grid->addWidget(amount3,3,1);
            if(m_numberOfPlayers >= 5)
            {
                QLabel* amount4    =   new QLabel(QString::number(m_player4->getAmount()),this);
                grid->addWidget(amount4,4,1);
                if(m_numberOfPlayers >= 6)
                {
                    QLabel* amount5    =   new QLabel(QString::number(m_player5->getAmount()),this);
                    grid->addWidget(amount5,5,1);
                    if(m_numberOfPlayers >= 7)
                    {
                        QLabel* amount6    =   new QLabel(QString::number(m_player6->getAmount()),this);
                        grid->addWidget(amount6,6,1);
                        if(m_numberOfPlayers >= 8)
                        {
                            QLabel* amount7    =   new QLabel(QString::number(m_player7->getAmount()),this);
                            grid->addWidget(amount7,7,1);
                            if(m_numberOfPlayers >= 9)
                            {
                                QLabel* amount8    =   new QLabel(QString::number(m_player8->getAmount()),this);
                                grid->addWidget(amount8,8,1);
                                if(m_numberOfPlayers == 10)
                                {
                                    QLabel* amount9    =   new QLabel(QString::number(m_player9->getAmount()),this);
                                    grid->addWidget(amount9,9,1);
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
    maketable->setMinimumHeight(this->parentWidget()->parentWidget()->height()/4);
    return maketable;
}
