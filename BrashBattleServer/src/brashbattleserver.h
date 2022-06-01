#pragma once

#include "../cell.h"

#include "tcpserver.h"
#include <QWidget>
#include <QHostAddress>
#include <QDateTime>

#define PORT 2673   //!< Порт подключения к серверу

//!
//! \brief The BrashBattleServer class Класс сервера игры
//!
class BrashBattleServer : public QWidget
{
    Q_OBJECT

public:
    //!
    //! \brief BrashBattleServer Конструктор
    //! \param parent Родительский виджет
    //!
    BrashBattleServer(QWidget *parent = nullptr);
    ~BrashBattleServer();

private slots:
    //!
    //! \brief sendTimers Реакция на отправку времени задержки
    //!
    void sendTimers();
    //!
    //! \brief sendStates Реакция на отправку состояния поля
    //!
    void sendStates();
    //!
    //! \brief onCellChanged Реакция на изменение цвета поля
    //! \param host Хост
    //! \param data Данные
    //!
    void onCellChanged( const QHostAddress & host, QByteArray * data );

private:
    QMap<quint32, quint64>          timeControl;    //!< Мапа для контроля времени хода на каждый IP
    QList<QList<Cell *> >           cells;          //!< Игровое поле
    TCPManager::TCPServer        *  p_server;       //!< Указатель на TCP сервер
};
