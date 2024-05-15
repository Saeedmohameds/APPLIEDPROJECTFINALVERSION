#include "mainwindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Ultimate Spell-checker");
    QPixmap background(":/imgs/projectnewbackground.png");

    QPixmap scaledBackground = background.scaled(w.size(), Qt::IgnoreAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Window, scaledBackground);
    w.setPalette(palette);
    w.setFixedSize(w.size());


    w.show();

    return a.exec();
}
