#ifndef PREGAMETWODIALOG_H
#define PREGAMETWODIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QGridLayout>
#include <QBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QValidator>
#include "mainwindow.h"

class PreGameTwoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PreGameTwoDialog(QWidget *parent = 0, int players = 8, int blinds = 15);

signals:

public slots:
    void    on_pb_back_released();

    void    on_pb_next_released();

private:
    QGroupBox   *mainGroupBox();
    QLabel      *playerLabels();
    QLineEdit   *playerNames();
    QLineEdit   *playerAmounts();
    QLabel      *makeDollars();
    QPushButton *backButton();
    QPushButton *nextButton();
    QLineEdit   *m_player0name;
    QLineEdit   *m_player1name;
    QLineEdit   *m_player2name;
    QLineEdit   *m_player3name;
    QLineEdit   *m_player4name;
    QLineEdit   *m_player5name;
    QLineEdit   *m_player6name;
    QLineEdit   *m_player7name;
    QLineEdit   *m_player8name;
    QLineEdit   *m_player9name;

    QLineEdit   *m_player0amount;
    QLineEdit   *m_player1amount;
    QLineEdit   *m_player2amount;
    QLineEdit   *m_player3amount;
    QLineEdit   *m_player4amount;
    QLineEdit   *m_player5amount;
    QLineEdit   *m_player6amount;
    QLineEdit   *m_player7amount;
    QLineEdit   *m_player8amount;
    QLineEdit   *m_player9amount;

    MainWindow  *m_mainwindow;
    int          m_numberOfPlayers;
    int          m_sblind;

};

#endif // PREGAMETWODIALOG_H
