#include "maindialog.h"
#include "ui_maindialog.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::on_pb_settings_released()
{
    m_settingsDialog = new SettingsDialog(this);
    m_settingsDialog->showMaximized();
}

void MainDialog::on_pb_help_released()
{
    m_helpDialog = new HelpDialog(this);
    m_helpDialog->showMaximized();
}

void MainDialog::on_pb_play_released()
{
    m_pregameonedialog = new PreGameOneDialog(this);
    m_pregameonedialog->showMaximized();
}
