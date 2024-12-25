#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    sendTimer = new QTimer(this);
    testArray = new QByteArray ;
    connect(sendTimer,SIGNAL(timeout()),this,SLOT(sendlerMessageFromTimer()));
    connect(socket,&QTcpSocket::disconnected,this,&MainWindow::sendlerMessageDisconnect);
    sendTimer->start(1);
}

MainWindow::~MainWindow()
{
    disconnect(socket,&QTcpSocket::disconnected,this,&MainWindow::sendlerMessageDisconnect);
    socket->disconnectFromHost();
    delete ui;
    delete socket;
    delete sendTimer;
    delete testArray;
}

void MainWindow::sentToServer(QByteArray dataArray)
{
        Data.clear();
        QDataStream out (&Data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_8);
        out <<dataArray;
        if (socket->state() == QTcpSocket::ConnectedState) {
            socket->write(Data);
            sendMessageToBox("TCP Data send " + QString::number(dataArray.size())  +" byte ");
        } else {
            sendMessageToBox("Socket is not connected!Error data send");
        }
}

void MainWindow::sendMessageToBox(QString messageToBox)
{
    messageToBox = QDateTime::currentDateTime().toString("HH:mm:ss::zzz") + " " + messageToBox;
    QString messageToBox1 = messageToBox ;
    ui->textBrowser->append(messageToBox1);
    qDebug()<<messageToBox;
}


void MainWindow::on_connectButton_clicked()
{
    if(socket->state() != QTcpSocket::ConnectedState)
    {
        QElapsedTimer timerConnect;
        timerConnect.start();
        socket->connectToHost(serverIP,serverPort);
        if(socket->waitForConnected(500)) {
            sendMessageToBox("TCP Connected in "+ "QString::number(timerConnect.elapsed())" + " ms ");
        } else {
            sendMessageToBox("Error TCP connection,time out "+ QString::number(timerConnect.elapsed()) + " ms ");
        }
    }
    else
    {
        sendMessageToBox("TCP Connection already on ");
    }
}

void MainWindow::on_sendButton_clicked()
{
    int16_t array[197120] ;
    array[0] = 000 ;
    array[1] = 111 ;
    array[2] = 222 ;
    array[3] = 333 ;
    array[4] = 1488 ;

    testArray->resize(sizeof(array));
    memcpy(testArray->data(), array, sizeof(array));
    sentToServer(*testArray);
}

void MainWindow::sendlerMessageDisconnect()
{
    sendMessageToBox(" Server close TCP socket! ");
}

void MainWindow::sendlerMessageFromTimer()
{

}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    serverIP = arg1;
}


void MainWindow::on_spinBoxPort_valueChanged(int arg1)
{
    serverPort = arg1;
}

void MainWindow::on_disconectedButton_clicked()
{
    if(socket->state() == QTcpSocket::ConnectedState) {
        socket->disconnectFromHost();
    }
    else
    {
        sendMessageToBox(" Server not connected! ");
    }
}

