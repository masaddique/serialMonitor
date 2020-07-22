#ifndef SERIALPORTAPP_H
#define SERIALPORTAPP_H

#include <QMainWindow>
#include <QDir>
#include <QMessageBox>
#include "serialobject.h"


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

private slots:
    void on_exitBtn_clicked();

    void on_portOpenBtn_clicked();

private:
    Ui::serialPortApp *ui;

    int serialPortObject;
};

#endif // SERIALPORTAPP_H
