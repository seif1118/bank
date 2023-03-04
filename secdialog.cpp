#include "secdialog.h"
#include "ui_secdialog.h"
#include <QMessageBox>
#include "loginp.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlError>
#include <string>

secDialog::secDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secDialog)
{
    ui->setupUi(this);
    bank conn;


    if(!conn.connopen())
        ui->label_2->setText("failed to connect to the database");
    else
        ui->label_2->setText("connected....");
}

secDialog::~secDialog()
{
    delete ui;
}

void secDialog::on_pushButton_add_clicked()
{
    bank conn;
    QString clid,username,password,transactions;
    clid = ui->lineEdit_id->text();
    username = ui->lineEdit_user->text();
    password = ui->lineEdit_pass->text();
    transactions = ui->lineEdit_trans->text();
    if(!conn.connopen()){
        hide();
        qDebug()<<"failed to open database";
    }

    conn.connopen();
    QSqlQuery qry;
    qry.prepare("INSERT INTO client(clid,username,passowrd,transactions) values ('"+clid+"','"+username+"','"+password+"','"+transactions+"')");
    if(qry.exec())
    {
        QMessageBox::critical(this,tr("save"),tr("saved"));
        conn.connclose();
    }
    else
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void secDialog::on_pushButton_edit_clicked()
{
    bank conn;
    QString clid,username,password,transactions;
    clid = ui->lineEdit_id->text();
    username = ui->lineEdit_user->text();
    password = ui->lineEdit_pass->text();
    transactions = ui->lineEdit_trans->text();
    if(!conn.connopen()){
        hide();
        qDebug()<<"failed to open database";
    }

    conn.connopen();
    QSqlQuery qry;
    qry.prepare("update client set username='"+username+"',transactions='"+transactions+"',passowrd='"+password+"' where clid = "+clid);
    qry.exec();
    if(qry.exec())
    {
        QMessageBox::critical(this,tr("update"),tr("Updated"));
        conn.connclose();
    }
    else
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void secDialog::on_pushButton_delete_clicked()
{
    bank conn;
    QString clid;
    clid = ui->lineEdit_id->text();
    if(!conn.connopen()){
        hide();
        qDebug()<<"failed to open database";
    }

    conn.connopen();
    QSqlQuery qry;
    qry.prepare("Delete from client where clid='"+clid+"'");
    if(qry.exec())
    {
        QMessageBox::critical(this,tr("Delete"),tr("Deleted"));
        conn.connclose();
    }
    else
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}


void secDialog::on_pushButton_viewcl_clicked()//button to view database in the table view
{
    bank conn;
    QSqlQueryModel * modal=new QSqlQueryModel();

    conn.connopen();
    QSqlQuery * qry=new QSqlQuery(conn.mydb);

    qry->prepare("select clid,username,transactions from client");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

    conn.connclose();
    qDebug() <<(modal->rowCount());
}

void secDialog::on_pushButton_print_clicked()
{
    QPrinter printer;
    printer.setPrinterName("desired printer name");
    QPrintDialog dialog(&printer,this);
    if(dialog.exec() == QDialog::Rejected) return;
    ui->textEdit_print->print(&printer);
}

void secDialog::on_pushButton_edittrans_clicked() //add transaction not edit
{
    bank conn;
    QString transactions,clid;
    clid=ui->lineEdit_id->text();
    transactions = ui->lineEdit_trans->text();
    if(!conn.connopen()){
        hide();
        qDebug()<<"failed to open database";
    }

    conn.connopen();
    QSqlQuery qry;
    qry.prepare("update client set transactions='"+transactions+"' where clid = "+clid);
    if(qry.exec())
    {
        QMessageBox::critical(this,tr("save"),tr("saved"));
        conn.connclose();
    }
    else
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void secDialog::on_pushButton_edittrans_2_clicked()
{
    bank conn;
    QString clid,transactions;
    clid = ui->lineEdit_id->text();
    transactions = ui->lineEdit_trans->text();
    if(!conn.connopen()){
        hide();
        qDebug()<<"failed to open database";
    }

    conn.connopen();
    QSqlQuery qry;
    qry.prepare("update client set transactions='"+transactions+"' where clid = "+clid);
    qry.exec();
    if(qry.exec())
    {
        QMessageBox::critical(this,tr("update"),tr("Updated"));
        conn.connclose();
    }
    else
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void secDialog::on_pushButton_deltrans_clicked()
{
    bank conn;
    QString clid,transactions;
    clid = ui->lineEdit_id->text();
    transactions = ui->lineEdit_trans->text();
    if(!conn.connopen()){
        hide();
        qDebug()<<"failed to open database";
    }

    conn.connopen();
    QSqlQuery qry;
    qry.prepare("update client set transactions=NULL where clid = "+clid);
    qry.exec();
    if(qry.exec())
    {
        QMessageBox::critical(this,tr("Delete"),tr("Deleted"));
        conn.connclose();
    }
    else
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}

void secDialog::on_tableView_activated(const QModelIndex &index)//fetch from database
{
    QString val=ui->tableView->model()->data(index).toString();
    QString clid,username,password,transactions;
    clid = ui->lineEdit_id->text();
    username = ui->lineEdit_user->text();
    password = ui->lineEdit_pass->text();
    transactions = ui->lineEdit_trans->text();
    bank conn;
    if(!conn.connopen()){
        hide();
        qDebug()<<"failed to open database";
        return;
    }

    conn.connopen();
    QSqlQuery qry;
    qry.prepare("select * from client where clid='"+val+"' or username='"+val+"' or passowrd='"+val+"' or transactions='"+val+"'");

    if(qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit_id->setText(qry.value(0).toString());//take from the coloumn of tha database
            ui->lineEdit_user->setText(qry.value(1).toString());
            ui->lineEdit_pass->setText(qry.value(3).toString());
        }
        conn.connclose();
    }
    else
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}
