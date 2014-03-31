#include "pregameonedialog.h"
#include "ui_pregameonedialog.h"

PreGameOneDialog::PreGameOneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreGameOneDialog)
{
    ui->setupUi(this);
    m_numberOfPlayers = 8;
    m_sblind          = 15;

    QValidator *players = new QIntValidator(2,  10,  this);
    QValidator *blinds  = new QIntValidator(15, 100, this);
    ui->le_players->setValidator(players);
    ui->le_blinds->setValidator(blinds);
}

PreGameOneDialog::~PreGameOneDialog()
{
    delete ui;
}

void PreGameOneDialog::on_pb_back_released()
{
    delete this;
}

void PreGameOneDialog::on_pb_next_released()
{
    m_pregametwodialog = new PreGameTwoDialog(this, m_numberOfPlayers, m_sblind);
    m_pregametwodialog->showMaximized();
}

void PreGameOneDialog::on_le_players_editingFinished()
{
    if(m_numberOfPlayers != ui->le_players->text().toInt())
        m_numberOfPlayers = ui->le_players->text().toInt();
}

void PreGameOneDialog::on_le_blinds_editingFinished()
{
    if(m_sblind != ui->le_blinds->text().toInt())
        m_sblind = ui->le_blinds->text().toInt();
}
