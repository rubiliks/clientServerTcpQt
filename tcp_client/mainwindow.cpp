#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("TCP client");
    socket = new QTcpSocket(this);
    sendArray = new QByteArray ;
    connect(socket,&QTcpSocket::disconnected,this,&MainWindow::sendlerMessageDisconnect);
}

MainWindow::~MainWindow()
{
    disconnect(socket,&QTcpSocket::disconnected,this,&MainWindow::sendlerMessageDisconnect);
    socket->disconnectFromHost();
    delete ui;
    delete socket;
    delete sendArray;
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
            sendMessageToBox("TCP Connected in " + QString::number(timerConnect.elapsed()) + " ms ");
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
    int16_t array[sizeIntArray] ;
    array[0] = zeroInArray ;
    array[1] = firstInArray ;
    array[2] = secondInArray ;
    array[3] = thirdInArray ;
    sendArray->resize(sizeof(array));
    memcpy(sendArray->data(), array, sizeof(array));
    sentToServer(*sendArray);
}

void MainWindow::sendlerMessageDisconnect()
{
    sendMessageToBox(" Server close TCP socket! ");
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

void MainWindow::on_int16_size_array_valueChanged(int arg1)
{
    sizeIntArray = arg1;
}

void MainWindow::on_spinBox_Array_0_valueChanged(int arg1)
{
    zeroInArray = arg1;
}

void MainWindow::on_spinBox_Array_1_valueChanged(int arg1)
{
    firstInArray = arg1;
}

void MainWindow::on_spinBox_Array_2_valueChanged(int arg1)
{
    secondInArray = arg1;
}

void MainWindow::on_spinBox_Array_3_valueChanged(int arg1)
{
    thirdInArray = arg1;
}
