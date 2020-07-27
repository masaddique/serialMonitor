#include "serialportapp.h"
#include "ui_serialportapp.h"
#include <QByteArray>
#include <QScrollBar>
#include <QSize>
#include <string>
#include <cstdio>
#include <QTableWidgetItem>

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
    //QMessageBox::information(this,"None",QString::number(this->size().width())+"," + QString::number(this->size().height()),QMessageBox::Ok);
    if (ui->portOpenBtn->text()=="Open") {
        port = new QSerialPort(this);
        QString serial = ui->portCombo->currentText();
        serial = "/dev/" + serial;
        int baud = ui->baudCombo->currentText().toInt();
        switch (baud) {
        case 1200:
            port->setBaudRate(QSerialPort::Baud1200);
            break;
        case 2400:
            port->setBaudRate(QSerialPort::Baud2400);
            break;
        case 4800:
            port->setBaudRate(QSerialPort::Baud4800);
            break;
        case 9600:
            port->setBaudRate(QSerialPort::Baud9600);
            break;
        case 19200:
            port->setBaudRate(QSerialPort::Baud19200);
            break;
        case 38400:
            port->setBaudRate(QSerialPort::Baud38400);
            break;
        case 115200:
            port->setBaudRate(QSerialPort::Baud115200);
            break;
        default:
            port->setBaudRate(QSerialPort::Baud1200);
        }
        int stop = ui->stopCombo->currentText().toInt();
        switch(stop) {
        case 1:
            port->setStopBits(QSerialPort::OneStop);
            break;
        case 2:
            port->setStopBits(QSerialPort::TwoStop);
            break;
        }
        int parity = ui->parityCombo->currentIndex();
        switch(parity) {
            case 0:
            port->setParity(QSerialPort::NoParity);
            break;
        case 1:
            port->setParity(QSerialPort::OddParity);
            break;
        case 2:
            port->setParity(QSerialPort::EvenParity);
        }
        port->setFlowControl(QSerialPort::NoFlowControl);
        port->setPortName(serial);
        port->open(QIODevice::ReadWrite);
        if (port->isOpen()) {
            //QMessageBox::information(this,"Info", "Port opened",QMessageBox::Ok);
            ui->baudCombo->setEnabled(false);
            ui->portCombo->setEnabled(false);
            ui->parityCombo->setEnabled(false);
            ui->stopCombo->setEnabled(false);
            ui->portOpenBtn->setText("Close");
            connect(port,&QSerialPort::readyRead,this,&serialPortApp::printResults);
            ui->statusBar->showMessage(serial + QString(" opened on ") + QTime::currentTime().toString("hh:mm:ss"));
        }
        else {
            ui->statusBar->showMessage(serial + QString(" unavailable last try") + QTime::currentTime().toString("hh:mm:ss"));
        }
    }
    else if (ui->portOpenBtn->text()=="Close") {
        port->close();
        if (!port->isOpen()) {
            ui->baudCombo->setEnabled(true);
            ui->portCombo->setEnabled(true);
            ui->parityCombo->setEnabled(true);
            ui->stopCombo->setEnabled(true);
            ui->portOpenBtn->setText("Open");
            disconnect(port,&QSerialPort::readyRead,this,&serialPortApp::printResults);
            ui->statusBar->showMessage(port->portName() + QString(" closed on ") + QTime::currentTime().toString("hh:mm:ss"));
        }
    }
}

void serialPortApp::showEvent(QShowEvent *) {

    //QMessageBox::information(this,"QT Version",QT_VERSION_STR);
    QDir devDir("/dev/");
    QStringList filter("tty*");
    ui->dispASCII->setChecked(true);
    ui->dispHEX->setChecked(false);
    QStringList serialsItems = devDir.entryList(filter,QDir::AllEntries|QDir::System);
    foreach (QString ser,serialsItems)
    {
        ui->portCombo->addItem(ser);
    }
    ui->mainData->clear();
    this->showMaximized();
    tohex = false;
    dispData.clear();
}

void serialPortApp::closeEvent(QCloseEvent *) {
    if(port->isOpen()) {
        port->close();
    }
}

void serialPortApp::printResults()
{
    QString timeStr("");
    QString match("");
    QByteArray infromSerial = port->readLine(); // this is by default hex data if convert to hex
    QString str2check(infromSerial);
    if (ui->outputTable->rowCount()>0) {
        int c = ui->outputTable->rowCount();
        for (int i = 0; i < c;i++) {
            QCheckBox* box = qobject_cast<QCheckBox*>(ui->outputTable->cellWidget(i,0));
            if (box->isChecked()) {
                //ui->statusBar->showMessage(QString::number(ui->outputTable->rowCount()) + QString("Checked"));

                QString sstr = ui->outputTable->item(i,1)->text();
                if (str2check.contains(sstr)) {
                    match = match + QString(" (Matching Sequence ") + QString::number(i) + QString(")");
                }
            }
        }
    }
    if (ui->timeTicks->isChecked()) {
        timeStr =  QTime::currentTime().toString("\nhh:mm:ss ->>");
    }
    dispData = dispData + match + timeStr + QString::fromUtf8(infromSerial);
    QString hexStr = QString(infromSerial.toHex().constData());
    hexStr.replace(QString("0a"),QString("0a\n"));
    hexData  = hexData + match + timeStr + hexStr;
    if (tohex) {
        ui->mainData->setPlainText(hexData);
    } else {
        ui->mainData->setPlainText(dispData);
    }
    ui->mainData->verticalScrollBar()->setValue(ui->mainData->verticalScrollBar()->maximum());

}

void serialPortApp::on_mainData_destroyed()
{

}

void serialPortApp::changeEvent(QEvent* event) {
    if (event->type() == QEvent::WindowStateChange) {
            int h = this->height();
            int w = this->width();
            ui->mainData->setGeometry(0.2*w,0.2*h,0.7*w,0.8*h);
            ui->inputTable->setGeometry(0.05*w,0.20*h,0.1*w,0.3*h);
            ui->outputTable->setGeometry(0.05*w,0.65*h,0.1*w,0.3*h);
            ui->mainData->updateGeometry();
            this->updateGeometry();
    }
}

void serialPortApp::buttonClicked() {
    int i;
    for (i = 0; i < ui->inputTable->rowCount();i++) {
        if (sender()==ui->inputTable->cellWidget(i,0)) {
            break;
        }
    }
    QString str = ui->inputTable->item(i,1)->text();
    int len = str.length();
    port->write(QByteArray(str.toStdString().c_str(),len));
}

void serialPortApp::on_inputTable_itemClicked(QTableWidgetItem *item)
{
    if (item->column()==0) {
        QMessageBox::information(this,"info",QString::number(item->row()));
    }

}

void serialPortApp::on_addInput_clicked()
{
    int row = ui->inputTable->rowCount();
    QPushButton* btn = new QPushButton(QString("->"),ui->inputTable);
    btn->setObjectName(QString::number(row));
    connect(btn,&QPushButton::clicked,this,&serialPortApp::buttonClicked);
    ui->inputTable->insertRow(row);
    ui->inputTable->setItem(row,1,new QTableWidgetItem(QString::number(row)));
    ui->inputTable->setCellWidget(row,0,btn);
}

void serialPortApp::on_removeInput_clicked()
{
    if(selectedX) {
        ui->inputTable->removeRow(selectedX);
        selectedX = -1;
    }
}

void serialPortApp::on_inputTable_cellClicked(int row, int column)
{
    selectedX = row;
    selectedY = column;
}

void serialPortApp::on_serialPortApp_destroyed()
{
    if(port->isOpen()) {
        port->close();
    }
}

void serialPortApp::on_dispASCII_toggled(bool checked)
{
    if (checked) {
        tohex = false;
    }
    else {
        tohex = true;
    }
}

void serialPortApp::on_dispHEX_toggled(bool checked)
{
    if (checked) {
        tohex = true;
    }
    else {
        tohex = false;
    }
}

void serialPortApp::on_addOutput_clicked()
{
    int row = ui->outputTable->rowCount();
    QCheckBox* chk = new QCheckBox(QString("Enable"),ui->inputTable);
    chk->setObjectName(QString::number(row));
    //connect(btn,&QPushButton::clicked,this,&serialPortApp::buttonClicked);
    ui->outputTable->insertRow(row);
    ui->outputTable->setItem(row,1,new QTableWidgetItem(QString::number(row)));
    ui->outputTable->setCellWidget(row,0,chk);
}

void serialPortApp::on_outputTable_cellClicked(int row, int column)
{
    selectedX = row;
    selectedY = column;
}

void serialPortApp::on_removeOutput_clicked()
{
    if(selectedX) {
        ui->outputTable->removeRow(selectedX);
        selectedX = -1;
    }
}
