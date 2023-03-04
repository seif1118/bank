#ifndef BANK_H
#define BANK_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "secdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class bank; }
QT_END_NAMESPACE

class bank : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    void connclose()
    {
        mydb.close();
        mydb.setDatabaseName(QSqlDatabase::defaultConnection);//handle the connection to the database
    }
    bool connopen()
    {
        mydb=QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/sqlite2/bank.db");

        if(!mydb.open()){
            qDebug()<<("failed to connect to the server");
            return false;
        }
        else
            qDebug()<<("connected....");
        return true;
    }



public:
    bank(QWidget *parent = nullptr);
    ~bank();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_signup_clicked();

private:
    Ui::bank *ui;

};
#endif // BANK_H
