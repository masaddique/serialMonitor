#ifndef SERIALOBJECT_H
#define SERIALOBJECT_H

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
class serialObject
{
private:
    int serialNum;
public:
    serialObject();
    serialObject(const char*, const char*, const char*, const char*);
    serialOpen();
    serialClose();
    serialSend();
};

#endif // SERIALOBJECT_H
