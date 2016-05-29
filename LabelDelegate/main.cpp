#include "homepage.h"
#include <QApplication>
//完成得差不多了才发现需要的是listwidget+delegate，泪崩。
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HomePage w;
    w.show();

    return a.exec();
}
