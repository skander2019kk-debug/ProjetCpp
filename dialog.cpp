#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setClient(Client c)
{
    ui->lineedit_cin2->setText(c.get_cin());
    ui->lineedit_nom2->setText(c.get_nom());
    ui->lineedit_prenom2->setText(c.get_prenom());
}