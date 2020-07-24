#ifndef SERIALPORTAPP_H
#define SERIALPORTAPP_H

#include <QMainWindow>
#include <QDir>
#include <QMessageBox>
#include <QThread>
#include <QSerialPort>
#include <QWindow>
#include <QTableWidgetItem>
#include <QVector>
//#include <QListWidget>


namespace Ui {
class serialPortApp;
}

class serialPortApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit serialPortApp(QWidget *parent = 0);
    ~serialPortApp();

protected:
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);
    void changeEvent(QEvent *);

private slots:
    void on_exitBtn_clicked();
    void on_portOpenBtn_clicked();
    void printResults();
    void on_mainData_destroyed();
    void buttonClicked();
    void on_input1_returnPressed();

    void on_inputTable_itemClicked(QTableWidgetItem *item);

    void on_addInput_clicked();

    void on_removeInput_clicked();

    void on_inputTable_cellClicked(int row, int column);

    void on_serialPortApp_destroyed();

private:
    Ui::serialPortApp *ui;
    QSerialPort* port;
    int selectedX;
    int selectedY;
};

#endif // SERIALPORTAPP_H
