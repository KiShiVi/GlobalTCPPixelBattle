#pragma once

#include <QObject>
#include <QByteArray>
#include <QHostAddress>

class QTcpServer;
class QTcpSocket;

namespace TCPManager
{
    //!
    //! \brief The TCPServer class Класс TCP сервера
    //!
    class TCPServer : public QObject
    {
        Q_OBJECT
    public:
        //!
        //! \brief TCPServer Конструктор
        //! \param port Порт подключения
        //! \param parent Родительский объект
        //!
        TCPServer( const quint16 port, QObject * parent = nullptr );
        ~TCPServer();

    public slots:
        //!
        //! \brief sendEveryoneData Отправить данные всем подключенным сокетам
        //! \param data Данные
        //!
        void sendEveryoneData( const QByteArray & data );
        //!
        //! \brief sendDataToHost Отправить данные только по одному IP
        //! \param host IP
        //! \param data Данные
        //!
        void sendDataToHost( const QHostAddress & host, const QByteArray & data );

    signals:
        //!
        //! \brief cellChanged Сигнал об изменении состояния пикселя
        //! \param address Хост
        //! \param data Данные
        //!
        void cellChanged( const QHostAddress & address, QByteArray * data );

    private slots:
        //!
        //! \brief onNewConnection Реакция на подключение нового пользователя
        //!
        void onNewConnection();
        //!
        //! \brief onReadyRead Реакция на получение данных
        //!
        void onReadyRead();
        //!
        //! \brief onDisconnected Реакция на отключение
        //!
        void onDisconnected();

    private:
        QTcpServer            * p_server;       //!< Указатель на TCP сервер
        QList<QTcpSocket *>     m_socketList;   //!< Список клиентских сокетов
    };
}
