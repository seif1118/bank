#include "loginp.h"
#include "ui_loginp.h"

loginp::loginp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginp)
{
    ui->setupUi(this);
}

loginp::~loginp()
{
    delete ui;
}
