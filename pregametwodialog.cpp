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

QGroupBox* PreGameTwoDialog::mainGroupBox()
{
    QGridLayout* grid = new QGridLayout(this);
    for(int i = 0; i < m_numberOfPlayers; i++)
    {
        grid->addWidget(playerLabels(),     i,    0);
        grid->addWidget(playerNames(),      i,    1);
        grid->addWidget(makeDollars(),      i,    2);
        grid->addWidget(playerAmounts(),    i,    3);
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
    return lineEdit;
}

QLineEdit* PreGameTwoDialog::playerAmounts()
{
    QLineEdit*  lineEdit = new QLineEdit(this);
    QValidator* vdouble  = new QIntValidator(1, 999999999, this);
    lineEdit->setValidator(vdouble);
    lineEdit->setMaximumWidth(200);
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
    return pushButton;
}
