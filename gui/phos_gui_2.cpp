#include <QtGui/QApplication>
#include "phosgui.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    phosGui theGui(0, Qt::Window);
    //theGui.showMaximized();
    theGui.show();
    return app.exec();
}
