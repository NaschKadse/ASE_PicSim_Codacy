#include "info.h"
#include "../forms/ui_info.h"

Info::Info(QWidget *parent) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint), ui(new Ui::Info) {
    ui->setupUi(this);
    QPixmap pmap = QPixmap("../pic/Qt.png");
    ui->label->setPixmap(pmap);
    QPixmap pmap2 = QPixmap("../pic/CLion.png");
    ui->label_2->setPixmap(pmap2);
    QPixmap pmap3 = QPixmap("../pic/cpp.png");
    ui->label_3->setPixmap(pmap3);
    QPixmap pmap4 = QPixmap("../pic/dhbw.png");
    ui->label_4->setPixmap(pmap4);
}
Info::~Info() {
    delete ui;
}
