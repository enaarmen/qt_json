#include "jsonqtnotes.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    jsonQtNotes w;
    w.show();

    return a.exec();
}
