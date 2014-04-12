#include "pregametwodialog.h"

PreGameTwoDialog::PreGameTwoDialog(QWidget *parent, int players, int blinds) :
    QDialog(parent)
{
    m_numberOfPlayers = players;
    m_sblind          = blinds;
    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(mainGroupBox());
    QGridLayout* grid = new QGridLayout();
    grid->addWidget(backButton(), 0, 0);
    grid->addWidget(nextButton(), 0, 1);
    vbox->addLayout(grid);
    setLayout(vbox);
}

void PreGameTwoDialog::on_pb_back_released()
{
    delete this;
}

void PreGameTwoDialog::on_pb_next_released()
{
    QString names[10];
    names[0] = m_player0name->text();
    names[1] = m_player1name->text();
    if(m_numberOfPlayers >= 3)
    {
        names[2] = m_player2name->text();
        if(m_numberOfPlayers >= 4)
        {
            names[3] = m_player3name->text();
            if(m_numberOfPlayers >= 5)
            {
                names[4] = m_player4name->text();
                if(m_numberOfPlayers >= 6)
                {
                    names[5] = m_player5name->text();
                    if(m_numberOfPlayers >= 7)
                    {
                        names[6] = m_player6name->text();
                        if(m_numberOfPlayers >= 8)
                        {
                            names[7] = m_player7name->text();
                            if(m_numberOfPlayers >= 9)
                            {
                                names[8] = m_player8name->text();
                                if(m_numberOfPlayers == 10)
                                {
                                    names[9] = m_player9name->text();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int amounts[10];
    amounts[0] = m_player0amount->text().toInt();
    amounts[1] = m_player1amount->text().toInt();
    if(m_numberOfPlayers >= 3)
    {
        amounts[2] = m_player2amount->text().toInt();
        if(m_numberOfPlayers >= 4)
        {
            amounts[3] = m_player3amount->text().toInt();
            if(m_numberOfPlayers >= 5)
            {
                amounts[4] = m_player4amount->text().toInt();
                if(m_numberOfPlayers >= 6)
                {
                    amounts[5] = m_player5amount->text().toInt();
                    if(m_numberOfPlayers >= 7)
                    {
                        amounts[6] = m_player6amount->text().toInt();
                        if(m_numberOfPlayers >= 8)
                        {
                            amounts[7] = m_player7amount->text().toInt();
                            if(m_numberOfPlayers >= 9)
                            {
                                amounts[8] = m_player8amount->text().toInt();
                                if(m_numberOfPlayers == 10)
                                {
                                    amounts[9] = m_player9amount->text().toInt();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    m_mainwindow = new MainWindow(this,m_sblind, m_numberOfPlayers,names, amounts);
    m_mainwindow->showMaximized();
}

QGroupBox* PreGameTwoDialog::mainGroupBox()
{
    QGridLayout* grid = new QGridLayout(this);
    m_player0name   = playerNames();
    m_player0amount = playerAmounts();
    m_player1name   = playerNames();
    m_player1amount = playerAmounts();
    grid->addWidget(playerLabels(),  0,  0);
    grid->addWidget(m_player0name,   0,  1);
    grid->addWidget(makeDollars(),   0,  2);
    grid->addWidget(m_player0amount, 0,  3);

    grid->addWidget(playerLabels(),  1,  0);
    grid->addWidget(m_player1name,   1,  1);
    grid->addWidget(makeDollars(),   1,  2);
    grid->addWidget(m_player1amount, 1,  3);
    if(m_numberOfPlayers >= 3)
    {
        m_player2amount = playerAmounts();
        m_player2name   = playerNames();
        grid->addWidget(playerLabels(),  2,  0);
        grid->addWidget(m_player2name,   2,  1);
        grid->addWidget(makeDollars(),   2,  2);
        grid->addWidget(m_player2amount, 2,  3);

        if(m_numberOfPlayers >= 4)
        {
            m_player3amount = playerAmounts();
            m_player3name   = playerNames();
            grid->addWidget(playerLabels(),  3,  0);
            grid->addWidget(m_player3name,   3,  1);
            grid->addWidget(makeDollars(),   3,  2);
            grid->addWidget(m_player3amount, 3,  3);

            if(m_numberOfPlayers >= 5)
            {
                m_player4amount = playerAmounts();
                m_player4name   = playerNames();
                grid->addWidget(playerLabels(),  4,  0);
                grid->addWidget(m_player4name,   4,  1);
                grid->addWidget(makeDollars(),   4,  2);
                grid->addWidget(m_player4amount, 4,  3);

                if(m_numberOfPlayers >= 6)
                {
                    m_player5amount = playerAmounts();
                    m_player5name   = playerNames();
                    grid->addWidget(playerLabels(),  5,  0);
                    grid->addWidget(m_player5name,   5,  1);
                    grid->addWidget(makeDollars(),   5,  2);
                    grid->addWidget(m_player5amount, 5,  3);

                    if(m_numberOfPlayers >= 7)
                    {
                        m_player6amount = playerAmounts();
                        m_player6name   = playerNames();
                        grid->addWidget(playerLabels(),  6,  0);
                        grid->addWidget(m_player6name,   6,  1);
                        grid->addWidget(makeDollars(),   6,  2);
                        grid->addWidget(m_player6amount, 6,  3);

                        if(m_numberOfPlayers >= 8)
                        {
                            m_player7amount = playerAmounts();
                            m_player7name   = playerNames();
                            grid->addWidget(playerLabels(),  7,  0);
                            grid->addWidget(m_player7name,   7,  1);
                            grid->addWidget(makeDollars(),   7,  2);
                            grid->addWidget(m_player7amount, 7,  3);

                            if(m_numberOfPlayers >= 9)
                            {
                                m_player8amount = playerAmounts();
                                m_player8name   = playerNames();
                                grid->addWidget(playerLabels(),  8,  0);
                                grid->addWidget(m_player8name,   8,  1);
                                grid->addWidget(makeDollars(),   8,  2);
                                grid->addWidget(m_player8amount, 8,  3);

                                if(m_numberOfPlayers == 10)
                                {
                                    m_player9amount = playerAmounts();
                                    m_player9name   = playerNames();
                                    grid->addWidget(playerLabels(),  9,  0);
                                    grid->addWidget(m_player9name,   9,  1);
                                    grid->addWidget(makeDollars(),   9,  2);
                                    grid->addWidget(m_player9amount, 9,  3);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    QGroupBox* groupbox = new QGroupBox(tr("Game Configuration Cont."), this);
    groupbox->setLayout(grid);
    return groupbox;
}

QLabel*    PreGameTwoDialog::playerLabels()
{
    QLabel* label = new QLabel(tr("Player "), this);
    return label;
}

QLineEdit* PreGameTwoDialog::playerNames()
{
    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setAlignment(Qt::AlignCenter);
    return lineEdit;
}

QLineEdit* PreGameTwoDialog::playerAmounts()
{
    QLineEdit*  lineEdit = new QLineEdit(this);
    QValidator* vdouble  = new QIntValidator(1, 999999999, this);
    lineEdit->setValidator(vdouble);
    lineEdit->setMaximumWidth(200);
    lineEdit->setAlignment(Qt::AlignRight);
    lineEdit->setText("1000");
    return lineEdit;
}

QLabel*   PreGameTwoDialog::makeDollars()
{
    QLabel* label = new QLabel(tr("$"), this);
    label->setMaximumWidth(50);
    return label;
}

QPushButton* PreGameTwoDialog::backButton()
{
    QPushButton* pushButton = new QPushButton(tr("Back"), this);
    pushButton->setMinimumSize(150,100);
    connect(pushButton, SIGNAL(released()), this, SLOT(on_pb_back_released()));
    return pushButton;
}

QPushButton* PreGameTwoDialog::nextButton()
{
    QPushButton* pushButton = new QPushButton(tr("Next"), this);
    pushButton->setMinimumSize(150,100);
    pushButton->setDefault(true);
    connect(pushButton, SIGNAL(released()), this, SLOT(on_pb_next_released()));
    return pushButton;
}
