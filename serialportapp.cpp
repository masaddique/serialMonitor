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
    QString serial = ui->portCombo->currentText();
    serial = "/dev/" + serial;
    serialPortObject = open((serial.toStdString().c_str(),O_RDWR|O_NOCTTY|O_NDELAY);
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
}

void serialPortApp::closeEvent(QCloseEvent *) {
    close(serialPortObject);
}
