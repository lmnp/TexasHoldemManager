#include "pregametwodialog.h"

PreGameTwoDialog::PreGameTwoDialog(QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(mainGroupBox());
    vbox->addWidget(backButton());
    vbox->addWidget(nextButton());
    setLayout(vbox);
}

void PreGameTwoDialog::on_pb_back_released()
{
    delete this;
}

QGroupBox* PreGameTwoDialog::mainGroupBox()
{
    QGridLayout* grid = new QGridLayout(this);
    for(int i = 0; i < 10; i++)
    {
        grid->addWidget(playerLabels(), i , 0);
        grid->addWidget(playerNames(), i , 1);
        grid->addWidget(playerAmounts(), i , 2);
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
    QLineEdit* lineEdit = new QLineEdit(this);
    return lineEdit;
}

QPushButton* PreGameTwoDialog::backButton()
{
    QPushButton* pushButton = new QPushButton(tr("Back"), this);
    connect(pushButton, SIGNAL(released()),this,SLOT(on_pb_back_released()));
    return pushButton;
}

QPushButton* PreGameTwoDialog::nextButton()
{
    QPushButton* pushButton = new QPushButton(tr("Next"), this);
    return pushButton;
}
