#include <QtGui/QApplication>
#include "displaywidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DisplayWidget w;

    w.show();
    return a.exec();
}
