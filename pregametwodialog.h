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

};

#endif // PREGAMETWODIALOG_H
