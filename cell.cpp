#include "cell.h"

#include <QDebug>

Cell::Cell( const quint8 x, const quint8 y, QWidget * parent ) : QLabel( parent )
{
    m_xPosition = x;
    m_yPosition = y;
    m_color = WHITE;
    setFixedSize(24, 24);
    setStyleSheet( "QLabel{ border: 1px solid black; }" );
}

Cell::~Cell()
{
}

void Cell::setColor( const quint8 color )
{
    m_color = color;
    switch ( m_color )
    {
    case BLACK:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(0, 0, 0); }" );
        break;
    case GRAY:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(128, 128, 128); }" );
        break;
    case SILVER:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(192, 192, 192); }" );
        break;
    case WHITE:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(255, 255, 255); }" );
        break;
    case FUCHSIA:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(255, 0, 255); }" );
        break;
    case PURPLE:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(128, 0, 128); }" );
        break;
    case RED:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(255, 0, 0); }" );
        break;
    case MAROON:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(128, 0, 0); }" );
        break;
    case YELLOW:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(255, 255, 0); }" );
        break;
    case OLIVE:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(128, 128, 0); }" );
        break;
    case LIME:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(0, 255, 0); }" );
        break;
    case GREEN:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(0, 128, 0); }" );
        break;
    case AQUA:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(0, 255 , 255); }" );
        break;
    case TEAL:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(0, 128, 128); }" );
        break;
    case BLUE:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(0, 0, 255); }" );
        break;
    case NAVY:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(0, 0, 128); }" );
        break;
    default:
        qDebug() << "$$$ Incorrect color $$$";
        break;
    }
}

quint8 Cell::getColor()
{
    return m_color;
}

quint8 Cell::getX()
{
    return m_xPosition;
}

quint8 Cell::getY()
{
    return m_yPosition;
}

void Cell::mouseReleaseEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton )
        emit clicked( this );
}
