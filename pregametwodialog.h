#ifndef PREGAMETWODIALOG_H
#define PREGAMETWODIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QGridLayout>
#include <QBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class PreGameTwoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PreGameTwoDialog(QWidget *parent = 0);
    PreGameTwoDialog(QWidget *parent = 0, int players = 8, int blinds = 15);

signals:

public slots:
    void    on_pb_back_released();

private:
    QGroupBox   *mainGroupBox();
    QLabel      *playerLabels();
    QLineEdit   *playerNames();
    QLineEdit   *playerAmounts();
    QPushButton *backButton();
    QPushButton *nextButton();
    int          m_numberOfPlayers;
    int          m_sblind;

};

#endif // PREGAMETWODIALOG_H
