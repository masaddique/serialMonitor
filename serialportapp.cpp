#include "serialportapp.h"
#include "ui_serialportapp.h"

serialPortApp::serialPortApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::serialPortApp)
{
    ui->setupUi(this);
}

serialPortApp::~serialPortApp()
{
    delete ui;
}

void serialPortApp::on_exitBtn_clicked()
{
    this->close();
}

void serialPortApp::on_portOpenBtn_clicked()
{
    if (ui->portOpenBtn->text()=="Open") {
        QString serial = ui->portCombo->currentText();
        serial = "/dev/" + serial;
        int baud = ui->baudCombo->currentText().toInt();
        int stop = ui->stopCombo->currentText().toInt();
        int parity = ui->parityCombo->currentText().toInt();
        //QString final = "Opening Serial port \n" + serial + "\n" + parity + "\n" + stop;
        QMessageBox::information(this,"Info", "Port opened",QMessageBox::Ok);
        ui->baudCombo->setEnabled(false);
        ui->portCombo->setEnabled(false);
        ui->parityCombo->setEnabled(false);
        ui->stopCombo->setEnabled(false);
        ui->portOpenBtn->setText("Close");
        serialObject* ser = new serialObject(serial.toStdString().c_str(),baud,parity,stop);

    }
    else if (ui->portOpenBtn->text()=="Close") {
        ui->baudCombo->setEnabled(true);
        ui->portCombo->setEnabled(true);
        ui->parityCombo->setEnabled(true);
        ui->stopCombo->setEnabled(true);
        ui->portOpenBtn->setText("Open");
    }

}

void serialPortApp::showEvent(QShowEvent *) {
    QDir devDir("/dev/");
    QStringList filter("tty*");
    QStringList serialsItems = devDir.entryList(filter,QDir::AllEntries|QDir::System);
    //QMessageBox::information(this,"None",QString::number(serialsItems.length()),QMessageBox::Ok);
    foreach (QString ser,serialsItems)
    {
        ui->portCombo->addItem(ser);
    }
    ui->mainData->clear();
}

void serialPortApp::closeEvent(QCloseEvent *) {
    //close(serialPortObject);
}
