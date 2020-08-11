#include "cmdinputdlg.h"
#include "ui_cmdinputdlg.h"

cmdInputDlg::cmdInputDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cmdInputDlg)
{
    ui->setupUi(this);
    ui->asciiRd->setChecked(true);
}

void cmdInputDlg::setText(QString str) {
    ui->cmdTxt->setPlainText(str);
}

cmdInputDlg::~cmdInputDlg()
{
    delete ui;
}

void cmdInputDlg::on_exitBtn_clicked()
{
    this->close();
}

void cmdInputDlg::on_okBtn_clicked()
{
    QString str;
    if (ui->hexRd->isChecked()) {
        str = QString::fromLocal8Bit(QByteArray::fromHex(ui->cmdTxt->toPlainText().toLatin1()));
    } else if (ui->asciiRd->isChecked()) {
        str = ui->cmdTxt->toPlainText();
    }
    emit sendData(str);
    this->close();
}

void cmdInputDlg::on_asciiRd_toggled(bool checked)
{
    if (checked) {
        ui->hexRd->setChecked(false);
        ui->cmdTxt->setPlainText(QString::fromLocal8Bit(QByteArray::fromHex(ui->cmdTxt->toPlainText().toLatin1())));
    }
}

void cmdInputDlg::on_hexRd_toggled(bool checked)
{
    if (checked) {
        ui->asciiRd->setChecked(false);
        QByteArray ar(ui->cmdTxt->toPlainText().toStdString().c_str());
        ui->cmdTxt->setPlainText(QString::fromUtf8(ar.toHex()));
    }
}
