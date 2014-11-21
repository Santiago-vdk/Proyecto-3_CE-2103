// mythread.cpp

#include "mythread.h"
#include "string"

using namespace std;

MyThread::MyThread(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
}

void MyThread::run()
{
    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    // set the ID
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));



    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies
    exec();
}

void MyThread::readyRead()
{
    QByteArray Data;
    Data = socket->readLine();

    QString dataString(Data);
    QString usuario(socket->readLine()) ;
    QString contrasenia(socket->readLine());



    socket->flush();

    if(dataString == "001\n"){
        qDebug() << "Caso 001, Autenticacion";

        //Elimino el \n
        string usuarioTmp = usuario.toStdString();
        usuarioTmp.erase(std::remove(usuarioTmp.begin(),usuarioTmp.end(), '\n'));

        string contraTmp = contrasenia.toStdString();
        contraTmp.erase(std::remove(contraTmp.begin(),contraTmp.end(), '\n'));

        //Convierto las entradas de nuevo a QString
        QString usuarioListo = QString::fromStdString(usuarioTmp);
        QString contraListo = QString::fromStdString(contraTmp);

        //Llamo al Slot de autenticacion
        auth(usuarioListo,contraListo);

    }


    if(dataString == "002\n"){
        qDebug() << "Caso 002, Registro";

//        QString usuario(socket->readLine()) ;
//        QString contrasenia(socket->readLine());

        //Elimino el \n
        string usuarioTmp = usuario.toStdString();
        usuarioTmp.erase(std::remove(usuarioTmp.begin(),usuarioTmp.end(), '\n'));

        string contraTmp = contrasenia.toStdString();
        contraTmp.erase(std::remove(contraTmp.begin(),contraTmp.end(), '\n'));

        //Convierto las entradas de nuevo a QString
        QString usuarioListo = QString::fromStdString(usuarioTmp);
        QString contraListo = QString::fromStdString(contraTmp);

        //Llamo al Slot de registro
        registrar(usuarioListo,contraListo);

    }


    // will write on server side window
    //qDebug() << socketDescriptor << " Data in: " << Data;
    //socket->write(Data);

    qDebug() << "escribo";
    test();



}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    exit(0);
}

void MyThread::expulsarCliente()
{
    qDebug() << "Cerrando Conexion...";
    socket->deleteLater();
    //exit(0);
}

void MyThread::llegadaNotificacion(QString pCodigo)
{
    qDebug() << pCodigo;
}

void MyThread::test()
{
    socket->write("Test");
}
