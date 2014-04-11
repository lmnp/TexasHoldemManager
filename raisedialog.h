#ifndef RAISEDIALOG_H
#define RAISEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QSpinBox>
#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QGroupBox>

class RaiseDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RaiseDialog(QWidget *parent = 0, int min = 0, int max = 0, int lastBet = 0);

signals:
    void    bet_confirmed(int);

public slots:
    void    on_cancel_released();
    void    on_confirm_released();

private:
    int m_min;
    int m_max;
    int m_lastBet;
    int m_bet;
    QSpinBox*   m_spinbox;
};

#endif // RAISEDIALOG_H
