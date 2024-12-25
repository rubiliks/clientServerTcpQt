#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sentToServer(QByteArray str);
    void sendlerMessageFromTimer();
    void on_connectButton_clicked();
    void on_sendButton_clicked();
    void sendlerMessageDisconnect();



    void on_lineEdit_textChanged(const QString &arg1);

    void on_spinBoxPort_valueChanged(int arg1);

    void on_disconectedButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray Data;
    QTimer *sendTimer;
    QByteArray *testArray;
    void sendMessageToBox(QString messageToBox);
    QString serverIP = "192.168.2.92";
    qint16 serverPort = 2323;

public slots:


};
#endif // MAINWINDOW_H
