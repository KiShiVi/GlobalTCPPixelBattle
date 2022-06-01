#include "brashbattleclient.h"

#include <QApplication>

#define PORT 2673

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BrashBattleClient * wgt = new BrashBattleClient();
    wgt->show();

    return a.exec();
}
