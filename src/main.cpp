#include "qpdfunify.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPdfUnify w;
    //w.setFixedSize(width, heigth);

    w.show();

    return a.exec();
}
