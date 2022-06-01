#pragma once

#include <QObject>
#include <QByteArray>

class QTcpSocket;
class QHostAddress;

namespace TCPManager
{
    //!
    //! \brief The TCPClient class Класс TCP клиента
    //!
    class TCPClient : public QObject
    {
        Q_OBJECT
    public:
        //!
        //! \brief TCPClient Конструктор
        //! \param host Хост
        //! \param port Порт
        //! \param parent Родительский объект
        //!
        TCPClient( const QHostAddress & host, const quint16 port, QObject * parent = nullptr );
        ~TCPClient();

    public slots:
        //!
        //! \brief sendMessage Отправить данные
        //! \param data Данные
        //!
        void sendMessage( const QByteArray & data );

    signals:
        //!
        //! \brief newData Сигнал, испускающийся при получении новых данных об игровом поле
        //! \param data Данные
        //!
        void newData( QByteArray & data );
        //!
        //! \brief newTimer Сигнал, испускающийся при получении новых данных о времени задержки
        //! \param data
        //!
        void newTimer( QByteArray & data );

    private slots:
        //!
        //! \brief onReadyRead Реакция на получение TCP пакета
        //!
        void onReadyRead();
        //!
        //! \brief onDisconnected Реакция на отключение от сервера
        //!
        void onDisconnected();
        //!
        //! \brief onConnected Реакция на подключение к серверу
        //!
        void onConnected();

    private:
        //!
        //! \brief p_socket Указатель на TCP сокет
        //!
        QTcpSocket  * p_socket;
    };
}
