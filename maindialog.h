#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "settingsdialog.h"
#include "helpdialog.h"
#include "pregameonedialog.h"


namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

private slots:
    void on_pb_settings_released();

    void on_pb_help_released();

    void on_pb_play_released();

private:
    Ui::MainDialog   *ui;
    SettingsDialog   *m_settingsDialog;
    HelpDialog       *m_helpDialog;
    PreGameOneDialog *m_pregameonedialog;
};

#endif // MAINDIALOG_H
