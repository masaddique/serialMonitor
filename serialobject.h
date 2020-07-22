#ifndef SERIALOBJECT_H
#define SERIALOBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <QThread>
#include <QMessageBox>
#include <QTextEdit>
#include <QString>

class serialObject:public QThread
{
    Q_OBJECT
    void run() override;
private:
    int serialNum; // save serial port number
    QTextEdit* editBox;
public:
    serialObject();
    serialObject(const char*, int, int, int);
    void serialOpen();
    void serialClose();
    void serialSend();

public slots:
    //void doWork();
signals:
    void dataReady(const char* data);
};

#endif // SERIALOBJECT_H
