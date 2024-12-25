#include "server.h"
#include <QTimer>
#include <QTime>


server::server()
{
    if(this->listen(QHostAddress::Any,2323))
    {

        qDebug()<<"start server";
    } else
    {
        qDebug()<<"error start server";
    }
}

void server::incomingConnection(qintptr socketDescriptor)
{
     qDebug()<<"client connected";
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket,&QTcpSocket::readyRead,this,&server::slotReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);
    Sockets.push_back(socket);
    qDebug()<<"client connected"<<socketDescriptor;
}

void server::slotReadyRead()
{
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_8);
    if(in.status()==QDataStream::Ok)
    {
        in.startTransaction();
        qDebug()<<"QDataStream read";
        QString startTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
        qDebug()<<"start time "<<startTime;
        QByteArray testArray;
        in >> testArray;

        if(!in.commitTransaction())
        {
          return;
        }

        int16_t array[testArray.size()];
        if (testArray.size() % sizeof(int16_t) == 0) {
            // Используем memcpy для копирования данных из QByteArray в массив int16_t
            memcpy(array, testArray.data(), testArray.size());

            // Выводим результат
            qDebug() << "Данные в массиве int16_t:";
            for (int i = 0; i < 4; ++i) {
               // qDebug() << "array[" << i << "]:" << array[i];
            }
        } else {
            qDebug() << "Размер QByteArray не кратен размеру int16_t.";
        }

        qDebug() <<array [0];
        qDebug() <<array [1];
        qDebug() <<array [2];
        qDebug() <<array [3];
        qDebug() <<array [4];

        // qDebug()<<testArray;
        int dsd = testArray.size();
        qDebug()<<"size array"<<dsd;

        QString endTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss::zzz");
        qDebug()<<"end time "<<endTime;
    }
    else {
        qDebug() << "QDataStream error";
    }
}

void server::SendToClient(QString str)
{
    str = "server send";
    Data.clear();
    QDataStream out (&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_8);
    out <<str;
    auto size = Sockets.length();
    for (auto i=0;i<size;i++){
        Sockets[i]->write(Data);
    }
}
