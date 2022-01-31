#ifndef IHMGESTIONBALANCES_H
#define IHMGESTIONBALANCES_H

#include <QWidget>

namespace Ui {
class IhmGestionBalances;
}

class IhmGestionBalances : public QWidget
{
    Q_OBJECT

public:
    //explicit IhmGestionBalances(QWidget *parent = nullptr);
    //~IhmGestionBalances();

private:
    Ui::IhmGestionBalances *ui;
};

#endif // IHMGESTIONBALANCES_H
