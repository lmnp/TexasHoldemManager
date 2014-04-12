#include "raisedialog.h"

RaiseDialog::RaiseDialog(QWidget *parent, int min, int max, int lastBet) :
    QDialog(parent)
{
    m_min       =   min;
    m_max       =   max;
    m_lastBet   =   lastBet;
    m_lineEdit  =   new QLineEdit(this);
    QIntValidator* i_val    =   new QIntValidator(m_min,m_max,this);
    m_lineEdit->setValidator(i_val);
    m_lineEdit->setText(QString::number(m_min));
    m_slider  =   new QSlider(Qt::Horizontal,this);
    m_slider->setRange(m_min, m_max);
    m_slider->setValue(m_min);
    connect(m_slider,   SIGNAL(valueChanged(int)),      this,   SLOT(on_slider_changed(int)));
    connect(m_lineEdit, SIGNAL(textChanged(QString)),   this,  SLOT(on_line_edit_changed(QString)));
    m_plus      =   new QPushButton("+",this);
    m_minus     =   new QPushButton("-",this);
    m_plus->setMaximumSize(m_plus->parentWidget()->width()/4,m_lineEdit->height());
    m_minus->setMaximumSize(m_minus->parentWidget()->width()/4,m_lineEdit->height());
    connect(m_plus,     SIGNAL(released()), this,    SLOT(on_m_plus_released()));
    connect(m_minus,    SIGNAL(released()), this,   SLOT(on_m_minus_released()));
    QPushButton*    cancel  =   new QPushButton("Cancel", this);
    cancel->setMinimumWidth(this->parentWidget()->parentWidget()->width()/2-10);
    QPushButton*    confirm =   new QPushButton("Place Bet", this);
    confirm->setMinimumWidth(this->parentWidget()->parentWidget()->width()/2-10);
    connect(cancel, SIGNAL(released()), this, SLOT(on_cancel_released()));
    connect(confirm, SIGNAL(released()), this, SLOT(on_confirm_released()));
    QGridLayout*    grid    =   new QGridLayout(this);
    grid->addWidget(m_slider,0,0);
    grid->addWidget(m_lineEdit,0,1);
    grid->addWidget(m_plus,0,2);
    grid->addWidget(m_minus,0,3);
    grid->addWidget(cancel,1,0,1,1,Qt::AlignCenter);
    grid->addWidget(confirm,1,1,1,2,Qt::AlignCenter);
    setLayout(grid);
    setWindowTitle("Raise");
    move(0, this->parentWidget()->parentWidget()->height()/3);
    setMinimumHeight(this->parentWidget()->parentWidget()->height()/3);
    setMinimumWidth(this->parentWidget()->parentWidget()->width());

}

void    RaiseDialog::on_cancel_released()
{
    delete this;
}

void    RaiseDialog::on_confirm_released()
{
    m_bet   =   m_lineEdit->text().toInt();
    emit bet_confirmed(m_bet);
    delete this;
}

void    RaiseDialog::on_m_plus_released()
{
    int x   =   m_lineEdit->text().toInt();
    if(x+10     <   m_max)
        m_lineEdit->setText(QString::number(m_lineEdit->text().toInt()+10));
    else
        m_lineEdit->setText(QString::number(m_max));
}

void    RaiseDialog::on_m_minus_released()
{
    int x   =   m_lineEdit->text().toInt();
    if(x-10     <   m_min)
        m_lineEdit->setText(QString::number(m_min));
    else
        m_lineEdit->setText(QString::number(m_lineEdit->text().toInt()-10));
}

void    RaiseDialog::on_slider_changed(int x)
{
    m_lineEdit->setText(QString::number(x));
}

void    RaiseDialog::on_line_edit_changed(QString x)
{
    m_slider->setValue(x.toInt());
}
