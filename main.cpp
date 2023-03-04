#include "bank.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <qsplashscreen.h>
#include <qwidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *splash=new QSplashScreen;
    splash->setPixmap(QPixmap("D:/study/work/c++/login3.png"));
    splash->show();

    bank w;
    QTimer::singleShot(2500,splash,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));

//    w.show();
    return a.exec();
}
