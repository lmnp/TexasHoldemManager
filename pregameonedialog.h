#ifndef PREGAMEONEDIALOG_H
#define PREGAMEONEDIALOG_H

#include <QDialog>
#include "pregametwodialog.h"

namespace Ui {
class PreGameOneDialog;
}

class PreGameOneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreGameOneDialog(QWidget *parent = 0);
    ~PreGameOneDialog();

private slots:
    void on_pb_back_released();

    void on_pb_next_released();

    void on_le_players_editingFinished();

    void on_le_blinds_editingFinished();

private:
    Ui::PreGameOneDialog *ui;
    PreGameTwoDialog     *m_pregametwodialog;
    int                   m_numberOfPlayers;
    int                   m_sblind;
};

#endif // PREGAMEONEDIALOG_H
