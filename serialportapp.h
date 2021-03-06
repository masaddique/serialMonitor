#ifndef SERIALPORTAPP_H
#define SERIALPORTAPP_H

#include <QMainWindow>
#include <QDir>
#include <QMessageBox>
#include <QThread>
#include <QSerialPort>
#include <QWindow>
#include <QTableWidgetItem>
#include <QTimer>
#include <QTime>
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
    void resizeEvent(QResizeEvent *);

private slots:
    void on_exitBtn_clicked();
    void on_portOpenBtn_clicked();
    void printResults();
    void on_mainData_destroyed();
    void buttonClicked();
    //void on_input1_returnPressed();

    void on_inputTable_itemClicked(QTableWidgetItem *item);

    void on_addInput_clicked();

    void on_removeInput_clicked();

    void on_inputTable_cellClicked(int row, int column);

    void on_serialPortApp_destroyed();

    void on_dispASCII_toggled(bool checked);

    void on_dispHEX_toggled(bool checked);

    void on_addOutput_clicked();

    void on_outputTable_cellClicked(int row, int column);

    void on_removeOutput_clicked();

    void datafromDlg(QString);

    void on_inputTable_cellDoubleClicked(int row, int column);

    void on_outputTable_cellDoubleClicked(int row, int column);

private:
    Ui::serialPortApp *ui;
    QSerialPort* port;
    QString dispData; // this will store all the data to be displayed
    QString hexData; // this will store all the data to be displayed in hex
    int selectedX;
    int selectedY;
    int in_out_dlg;
    bool tohex;
    QTimer* timer;
};

#endif // SERIALPORTAPP_H
