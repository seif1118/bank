#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include "bank.h"

namespace Ui {
class secDialog;
}

class secDialog : public QDialog
{
    Q_OBJECT

public:
    explicit secDialog(QWidget *parent = nullptr);
    ~secDialog();
    void show();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_viewcl_clicked();

    void on_pushButton_print_clicked();

    void on_pushButton_edittrans_clicked();

    void on_pushButton_edittrans_2_clicked();

    void on_pushButton_deltrans_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::secDialog *ui;
    void updateUI();
};

#endif // SECDIALOG_H
