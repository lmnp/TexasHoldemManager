#ifndef RAISEDIALOG_H
#define RAISEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QGroupBox>
#include <QValidator>

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
    void    on_m_plus_released();
    void    on_m_minus_released();
    void    on_slider_changed(int x);
    void    on_line_edit_changed(QString x);

private:
    int m_min;
    int m_max;
    int m_lastBet;
    int m_bet;

    QSlider*    m_slider;
    QLineEdit*  m_lineEdit;
    QPushButton*    m_plus;
    QPushButton*    m_minus;
};

#endif // RAISEDIALOG_H
