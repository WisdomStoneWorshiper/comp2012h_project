#ifndef TRADEWINDOW_H
#define TRADEWINDOW_H

#include <QDialog>
#include <QIntValidator>
#include "player.h"
#include "buildableproperty.h"
#include "restaurant.h"

namespace Ui
{
class TradeWindow;
}

class TradeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TradeWindow(const vector<Player *> &, const vector<Box *> &, QWidget *parent = nullptr);
    ~TradeWindow();

    void init(Player *);
signals:
    void doTrade(Player *, Property *, unsigned);
private slots:
    void on_sellerBox_activated(const QString &arg1);

    void on_cancelBtn_clicked();

    void on_propertyBox_activated(const QString &arg1);

    void on_priceField_textChanged(const QString &arg1);

    void on_comfirmBtn_clicked();

    void on_buyerBox_activated(const QString &arg1);

private:
    Ui::TradeWindow *ui;
    vector<Player *> playerList;
    vector<Box *> gameField;
    Player *buyer;
    QIntValidator *valider;
    Player *seller;
    Property *targetProperty;
};

#endif // TRADEWINDOW_H
