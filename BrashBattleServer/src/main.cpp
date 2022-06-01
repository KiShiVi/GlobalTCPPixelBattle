#include "brashbattleserver.h"

#include <QApplication>
#include <QGridLayout>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BrashBattleServer * wgt = new BrashBattleServer();
    wgt->show();
    return a.exec();
}
