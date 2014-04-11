#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <iostream>

class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerWidget(QWidget *parent = 0, QString name = "", int amount = 1000, bool start = false, bool in = true);
    QString         getName() const      {return m_name;}
    int             getAmount() const    {return m_amount;}
    PlayerWidget*   getNextPlayer() const{return m_nextPlayer;}
    bool            getGameStatus() const{return m_inGame;}
    void            changeAmount(int amount) {m_amount -= amount; m_lastBet = amount; emit amountChanged(m_amount);}
    void            setNextPlayer(PlayerWidget* np){m_nextPlayer = np;}
    void            setGameStatus(bool in)  {m_inGame = in;}

signals:
    void amountChanged(int);

public slots:

private:
    QString         m_name;
    int             m_amount;
    int             m_lastBet;
    bool            m_startRound;
    bool            m_inGame;
    PlayerWidget*   m_nextPlayer;
};

#endif // PLAYERWIDGET_H
