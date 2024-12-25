#include <QCoreApplication>
#include <iostream>
#include <ostream>
#include "server.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout<<"run"<<std::endl;
    server s;
    return a.exec();
}
