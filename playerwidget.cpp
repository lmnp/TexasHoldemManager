#include "playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent, QString name, int amount, bool start, bool in) :
    QWidget(parent)
{
    m_name      =   name;
    m_amount    =   amount;
    m_startRound=   start;
    m_inGame    =   in;
}
