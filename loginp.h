#ifndef LOGINP_H
#define LOGINP_H

#include <QMainWindow>

namespace Ui {
class loginp;
}

class loginp : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginp(QWidget *parent = nullptr);
    ~loginp();

private:
    Ui::loginp *ui;
};

#endif // LOGINP_H
