#pragma once

#include "../cell.h"
#include "tcpclient.h"
#include <QWidget>
#include <QByteArray>
#include <QLCDNumber>

#define HOST "IP"               //!< IP сервера
#define PORT 2673               //!< Порт сервера

//!
//! \brief The BrashBattleClient class Класс клиента игры
//!
class BrashBattleClient : public QWidget
{
    Q_OBJECT

public:
    //!
    //! \brief BrashBattleClient Конструктор
    //! \param parent Родительский виджет
    //!
    BrashBattleClient( QWidget * parent = nullptr );
    //!
    //! \brief ~BrashBattleClient Деструктор
    //!
    ~BrashBattleClient();

private slots:
    //!
    //! \brief onNewData Реакция на получение новых данных об игровом поле
    //! \param data Данные
    //!
    void onNewData( QByteArray & data );
    //!
    //! \brief onNewTimer Реакция на получение данных об окончании задержки между ходами
    //! \param data Данные
    //!
    void onNewTimer( QByteArray & data );
    //!
    //! \brief onClicked Реакция на нажатие на один из пикселей
    //! \param sender Указатель на пиксель
    //!
    void onClicked( Cell * sender );
    //!
    //! \brief setCurrentColor Установить текущий цвет для рисования
    //! \param sender Указатель на пиксель с выбранным цветом
    //!
    void setCurrentColor( Cell * sender );
    //!
    //! \brief onConnected Реакция на подключение к серверу
    //!
    void onConnected();
    //!
    //! \brief onDisconnected Реакция на отключение от сервера
    //!
    void onDisconnected();

private:
    quint8                      m_currentColor;     //!< Выбранный цвет;
    Cell                    *   p_currentColorCell; //!< Указатель на пискель с выбранным цветом
    Cell                    *   p_connectionState;  //!< Указатель на индикатор состояния подключения к серверу
    QLCDNumber              *   p_lcd;              //!< Указатель на счетчик времени
    QList<QList<Cell *> >       cells;              //!< Массив пикселей
    TCPManager::TCPClient   *   p_client;           //!< Указатель на TCP клиент
};
