#include "raisedialog.h"

RaiseDialog::RaiseDialog(QWidget *parent, int min, int max, int lastBet) :
    QDialog(parent)
{
    m_min       =   min;
    m_max       =   max;
    m_lastBet   =   lastBet;
    m_spinbox   =   new QSpinBox(this);
    m_spinbox->setRange(m_min, m_max);
    m_spinbox->setValue(m_min);
    QSlider*        slider  =   new QSlider(Qt::Horizontal,this);
    slider->setRange(m_min, m_max);
    slider->setValue(m_min);
    connect(slider,     SIGNAL(valueChanged(int)), m_spinbox, SLOT(setValue(int)));
    connect(m_spinbox,    SIGNAL(valueChanged(int)),  slider, SLOT(setValue(int)));
    QLabel*         diff    =   new QLabel(QString::number(m_lastBet+1),this);
    connect(slider, SIGNAL(valueChanged(int)), diff, SLOT(setNum(int)));
    QPushButton*    cancel  =   new QPushButton("Cancel", this);
    QPushButton*    confirm =   new QPushButton("Place Bet", this);
    connect(cancel, SIGNAL(released()), this, SLOT(on_cancel_released()));
    QGridLayout*    grid    =   new QGridLayout(this);
    grid->addWidget(slider,0,0);
    grid->addWidget(m_spinbox,0,1);
    grid->addWidget(diff,0,2);
    grid->addWidget(cancel,1,0);
    grid->addWidget(confirm,1,2);
    setLayout(grid);
    setWindowTitle("Raise");
    move(this->parentWidget()->parentWidget()->width()/4, this->parentWidget()->parentWidget()->height()/3);
    setMinimumHeight(this->parentWidget()->parentWidget()->height()/3);
    setMinimumWidth(this->parentWidget()->parentWidget()->width()/2);

}

void    RaiseDialog::on_cancel_released()
{
    delete this;
}

void    RaiseDialog::on_confirm_released()
{
    m_bet   =   m_spinbox->value();
    emit bet_confirmed(m_bet);
}
