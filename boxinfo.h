#ifndef BOXINFO_H
#define BOXINFO_H

#include <QDialog>

namespace Ui {
class boxInfo;
}

class boxInfo : public QDialog
{
    Q_OBJECT

public:
    explicit boxInfo(QWidget *parent = nullptr);
    ~boxInfo();

private:
    Ui::boxInfo *ui;
};

#endif // BOXINFO_H
