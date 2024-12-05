#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    
    QApplication::setStyle("Fusion");  // Use Fusion style which is more stable
    a.setAttribute(Qt::AA_UseDesktopOpenGL);  // Prefer desktop OpenGL

    MainWindow w;
    w.show();
    return a.exec();
}
