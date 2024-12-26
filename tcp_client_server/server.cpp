#include "server.h"
#include <QTimer>
#include <QTime>

server::server()
{
    if(this->listen(QHostAddress::Any,2323))
    {
        qDebug()<<QDateTime::currentDateTime().toString("HH:mm:ss::zzz") <<" Start TCP server";
    } else
    {
        qDebug()<<QDateTime::currentDateTime().toString("HH:mm:ss::zzz")<<" Error start TCP server";
    }
}

void server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket,&QTcpSocket::readyRead,this,&server::slotReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);
    qDebug()<<QDateTime::currentDateTime().toString("HH:mm:ss::zzz")<<"Client connected"<< " descriptor " <<socketDescriptor;
}

void server::slotReadyRead()
{
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_8);
    if(in.status()==QDataStream::Ok)
    {
        in.startTransaction();
        QString startTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
        qDebug()<<startTime<<" Transaction start time ";
        QByteArray Array;
        in >> Array;
        if(!in.commitTransaction())
        {
          return;
        }
        int16_t array[Array.size()];
        if (Array.size() % sizeof(int16_t) == 0) {
            memcpy(array, Array.data(), Array.size());
            qDebug()<<"Value array[0] = " <<array [0] ;
            qDebug()<<"Value array[1] = " <<array [1] ;
            qDebug()<<"Value array[2] = " <<array [2] ;
            qDebug()<<"Value array[3] = " <<array [3] ;
            int sizeOfArray = Array.size();
            qDebug()<<"Size array in byte = "<<sizeOfArray;
            QString endTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss::zzz");
            qDebug()<<endTime<<"end time ";
            qDebug()<<"---------------------------------------";
        }
        else {
            qDebug() << "QDataStream error";
        }
    }
}

