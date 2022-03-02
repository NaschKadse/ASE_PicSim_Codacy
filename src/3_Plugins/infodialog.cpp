#include "../../header/infodialog.h"
#include "../../forms/ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint),
                                          ui(new Ui::InfoDialog) {
    ui->setupUi(this);
}
InfoDialog::~InfoDialog() {
    delete ui;
}
void InfoDialog::on_okButton_clicked() {
    position = ui->spinBox->text();
    accept();
}
void InfoDialog::on_cancelButton_clicked() {
    // Reject the dialog
    reject();
}
QString InfoDialog::getPosition() const {
    return position;
}