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

class serialObject:public QThread
{
private:
    int serialNum; // save serial port number
public:
    serialObject();
    serialObject(const char*, int, int, int);
    void serialOpen();
    void serialClose();
    void serialSend();
};

#endif // SERIALOBJECT_H
