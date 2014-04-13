#include "playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent, QString name, int amount, bool in) :
    QWidget(parent)
{
    m_name      =   name;
    m_amount    =   amount;
    m_inGame    =   in;
    m_lastBet   =   0;
}
