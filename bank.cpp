#include "bank.h"
#include "ui_bank.h"
#include<QMessageBox>
#include "loginp.h"


bank::bank(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::bank)
{
    ui->setupUi(this);

    QPixmap pix("D:/study/work/c++/login2.jpg");
    ui->label_pic->setPixmap(pix);

    if(!connopen())
        ui->label_stat->setText("failed to connect to the server");
    else
        ui->label_stat->setText("connected....");

}

bank::~bank()
{
    delete ui;
}


void bank::on_pushButton_clicked()//login
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_passowrd->text();
    if(!connopen()){
        hide();
        qDebug()<<"failed to open database";
    }

    connopen();
    QSqlQuery qry;
    qry.prepare("select * from client where username='"+username+"'and passowrd='"+password+"'");
    if(qry.exec())
    {
        int count=0;
        while(qry.next())
        {
            count++;
        }
        if(count==1)
        {
            ui->label_stat->setText("username and passowrd are correct");
            connclose();
            this->hide();
            secDialog bankc;
            bankc.setModal(true);
            bankc.exec();
        }
        if(count>1)
        {
            ui->label_stat->setText("username or passowrd are duplicated");
        }
        if(count<1)
        {
            ui->label_stat->setText("username or passowrd are incorrect");
        }
    }
}

void bank::on_pushButton_signup_clicked()//signup
{
    bank conn;
    QString clid,username,password;
    clid = ui->lineEdit_clid2->text();
    username = ui->lineEdit_username2->text();
    password = ui->lineEdit_passsword2->text();
    if(!conn.connopen()){
        hide();
        qDebug()<<"failed to open database";
    }

    conn.connopen();
    QSqlQuery qry;
    qry.prepare("INSERT INTO client(clid,username,passowrd) values ('"+clid+"','"+username+"','"+password+"')");
    if(qry.exec())
    {
        QMessageBox::critical(this,tr("save"),tr("saved"));
        conn.connclose();
    }
    else
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}
