#ifndef MORTGAGEWINDOW_H
#define MORTGAGEWINDOW_H

#include <QDialog>
#include "player.h"
#include "buildableproperty.h"
#include "restaurant.h"

enum Mod
{
    Apply,
    Pay
};

namespace Ui
{
class MortgageWindow;
}

class MortgageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MortgageWindow(const vector<Player *> &, const vector<Box *> &, QWidget *parent = nullptr);
    ~MortgageWindow();
    void init(Player *);

signals:
    void doMortgage(Property *, const Mod &);

private slots:
    void on_applyBtn_clicked();

    void on_payBtn_clicked();

    void on_mortgageList_activated(const QString &);

    void on_confirmBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::MortgageWindow *ui;
    vector<Player *> playerList;
    vector<Box *> gameField;
    Player *currentPlayer;
    Property *targetProperty;
};

#endif // MORTGAGEWINDOW_H
