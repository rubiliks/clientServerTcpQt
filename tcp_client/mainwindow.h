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
    void on_connectButton_clicked();
    void on_sendButton_clicked();
    void sendlerMessageDisconnect();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_spinBoxPort_valueChanged(int arg1);
    void on_disconectedButton_clicked();
    void on_int16_size_array_valueChanged(int arg1);
    void on_spinBox_Array_0_valueChanged(int arg1);
    void on_spinBox_Array_1_valueChanged(int arg1);
    void on_spinBox_Array_2_valueChanged(int arg1);
    void on_spinBox_Array_3_valueChanged(int arg1);

private:
    void sendMessageToBox(QString messageToBox);
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray Data;
    QByteArray *sendArray;
    int16_t zeroInArray = 0;
    int16_t firstInArray = 111;
    int16_t secondInArray = 222;
    int16_t thirdInArray = 333;
    QString serverIP = "192.168.2.92";
    qint16 serverPort = 2323;
    int16_t sizeInt16Array= 4;

public slots:
};
#endif // MAINWINDOW_H
