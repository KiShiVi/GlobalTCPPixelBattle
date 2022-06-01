#include "tcpserver.h"

#include <QApplication>

#define PORT 2673

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TCPManager::TCPServer * server = new TCPManager::TCPServer( PORT );
    return a.exec();
}
