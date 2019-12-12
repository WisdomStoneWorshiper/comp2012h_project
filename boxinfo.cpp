#include "boxinfo.h"
#include "ui_boxinfo.h"

boxInfo::boxInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::boxInfo)
{
    ui->setupUi(this);
}

boxInfo::~boxInfo()
{
    delete ui;
}
