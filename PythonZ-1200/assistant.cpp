#include "assistant.h"

Assistant::Assistant(QObject *parent) : QObject(parent)
{

}

void Assistant::sendMessage(int msg)
{
    emit sendmsg(msg);
}

void Assistant::sendPicInfo(unsigned char* buffer, long length)
{
    emit sendpic(buffer, length);
}
