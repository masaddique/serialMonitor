#ifndef SERIALPORTAPP_H
#define SERIALPORTAPP_H

#include <QMainWindow>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <fstream>
#include <QDir>
#include <QMessageBox>
#include <termios.h>
#include <fcntl.h>

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
