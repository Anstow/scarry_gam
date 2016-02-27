#include "graphviewer.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphViewer w;
    w.show();

    return a.exec();
}
