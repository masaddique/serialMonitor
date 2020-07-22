#include "serialobject.h"


serialObject::serialObject()
{
    //QThread::QThread();
    //QMessageBox::information(this,"Info","Never use this again", QMessageBox::Ok);
}

serialObject::serialObject(const char *port,int baud, int parity, int stopbits)
{
    //QThread::QThread();
    //editBox = edit;
    serialNum = open(port, O_RDWR|O_NOCTTY|O_NDELAY);
    if (serialNum == -1) {
        QMessageBox::warning(NULL, "Info",QString("Unable to open port") + QString(port), QMessageBox::Ok);
    }
    struct termios config;
    tcgetattr(serialNum, &config);
    config.c_cflag &= ~CBAUD;
    switch(baud)
    {
    case 1200:
        cfsetispeed(&config,B1200);
        cfsetospeed(&config,B1200);
        break;
    case 2400:
        cfsetispeed(&config,B2400);
        cfsetospeed(&config,B2400);
        break;
    case 4800:
        cfsetispeed(&config,B4800);
        cfsetospeed(&config,B4800);
        break;
    case 9600:
        cfsetispeed(&config,B9600);
        cfsetospeed(&config,B9600);
        break;
    case 19200:
        cfsetispeed(&config,B19200);
        cfsetospeed(&config,B19200);
        break;
    case 38400:
        cfsetispeed(&config,B38400);
        cfsetospeed(&config,B38400);
        break;
        break;
    case 115200:
        cfsetispeed(&config,B115200);
        cfsetospeed(&config,B115200);
        break;
    case 230400:
        cfsetispeed(&config,B230400);
        cfsetospeed(&config,B230400);
        break;
    }
    switch(parity) {
    case 0:
        config.c_cflag &= ~PARENB;
        break;
    case 1:
        config.c_cflag |= PARODD;
        break;
    case 2:
        config.c_cflag |= ~PARODD;
        break;
    }
    switch(stopbits) {
    case 1:
        config.c_cflag &= ~CSTOPB;
        break;
    case 2:
        config.c_cflag |= CSTOPB;
        break;
    }
    // find size
    config.c_cflag &= ~CSIZE;
    config.c_cflag |= CS8;

    // no hardware flow control
    config.c_cflag &= ~CRTSCTS;
    config.c_cflag |= CREAD|CLOCAL;

    // no XON/XOFF flow control
    config.c_iflag &= ~(IXON|IXOFF|IXANY);
    config.c_iflag &= ~(ICANON|ECHO|ECHOE|ISIG);
    config.c_oflag &= ~OPOST;

    //config.c_cc[VMIN] = 10;
    //config.c_cc[VTIME] = 0;

    if ((tcsetattr(serialNum,TCSANOW,&config)) != 0) {
        QMessageBox::warning(NULL,"Info", "Cannot open port with desired configurations",QMessageBox::Ok);
    }
    tcflush(serialNum,TCIFLUSH);
    printf("Port is open %s",port);
    //close(serialNum);
}

void serialObject::serialOpen()
{

}

void serialObject::serialClose()
{
    close(serialNum);
}

void serialObject::serialSend() {
    // do something
}
void serialObject::run() {
    //QMessageBox::information(NULL,"info","Reached here",QMessageBox::Ok);
    //QThread::run();
    //QMessageBox::information(NULL,"info","This is running",QMessageBox::Ok);
    while (1) {
        char data[32];
        int dataready = read(serialNum,&data,32);
        if (dataready!=-1) {
            emit(dataReady(data));
        }
    }
}
