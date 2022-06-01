#pragma once

#define TIME_DELAY 15   //!< Задержка между вохможной сменой цвета одним пользователем

#include <QWidget>
#include <QLabel>
#include <QColor>
#include <QObject>
#include <QMouseEvent>
#include <QByteArray>
#include <QDataStream>


//!
//! \brief The PACKET_TYPE enum Тип отправляемого TCP пакета
//!
enum PACKET_TYPE
{
    DATA,   //!< Данные о пикселях
    TIME,   //!< Время
    CMD     //!< Резерв
};

//!
//! \brief The Cell class Класс одного пикселя
//!
class Cell : public QLabel
{
    Q_OBJECT
public:
    //!
    //! \brief Cell Конструктор
    //! \param x Координата по X
    //! \param y Координата по Y
    //! \param parent Родительский виджет
    //!
    Cell( const quint8 x, const quint8 y, QWidget * parent = nullptr );
    //!
    //! \brief ~Cell Деструктор
    //!
    virtual ~Cell();
    //!
    //! \brief setColor Устанавливает цвет пикселя
    //! \param color Цвет
    //!
    void setColor( const quint8 color );
    //!
    //! \brief getColor Возвращает цвет пикселя
    //! \return Цвет пикселя
    //!
    quint8 getColor();
    //!
    //! \brief getX Возвращает координату X
    //! \return Координата X
    //!
    quint8 getX();
    //!
    //! \brief getY Возвращает координату Y
    //! \return Координата Y
    //!
    quint8 getY();

signals:
    //!
    //! \brief clicked Сигнал, испускающийся при клике на пиксель
    //! \param sender Собственный объект
    //!
    void clicked( Cell * sender );

protected:
    //!
    //! \brief mouseReleaseEvent Событие клика. Реализован для сигнала
    //! \param e Событие
    //!
    void mouseReleaseEvent( QMouseEvent * e );

private:
    quint8 m_color;         //!< Цвет
    quint8 m_xPosition;     //!< Координата по X
    quint8 m_yPosition;     //!< Координата по Y
};

