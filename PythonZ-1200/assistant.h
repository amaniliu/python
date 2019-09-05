#ifndef ASSISTANT_H
#define ASSISTANT_H

#include <QObject>

class Assistant : public QObject
{
    Q_OBJECT
public:
    explicit Assistant(QObject *parent = nullptr);

    void sendPicInfo(unsigned char* buffer, long length);

    void sendMessage(int msg);

signals:
    void sendpic(unsigned char* buffer, long length);

    void sendmsg(int msg);
};

#endif // ASSISTANT_H
