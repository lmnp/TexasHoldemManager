#include "playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent, QString name, int amount) :
    QWidget(parent)
{
    m_name      =   name;
    m_amount    =   amount;
}
