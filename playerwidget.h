#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>

class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerWidget(QWidget *parent = 0, QString name = "", int amount = 1000);
    QString getName() const      {return m_name;}
    int     getAmount() const    {return m_amount;}

signals:

public slots:

private:
    QString m_name;
    int     m_amount;
};

#endif // PLAYERWIDGET_H
