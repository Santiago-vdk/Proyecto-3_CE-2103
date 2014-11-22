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






    if(dataString == "001\n"){
        qDebug() << "Caso 001, Autenticacion";

        QString usuario(socket->readLine()) ;
        QString contrasenia(socket->readLine());

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

        QString usuario(socket->readLine()) ;
        QString contrasenia(socket->readLine());

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

    if(dataString == "003\n"){

        QString usuario(socket->readLine()) ;


        //Elimino el \n
        string usuarioTmp = usuario.toStdString();
        usuarioTmp.erase(std::remove(usuarioTmp.begin(),usuarioTmp.end(), '\n'));
        //Convierto las entradas de nuevo a QString
        QString usuarioListo = QString::fromStdString(usuarioTmp);
        //Llamo al Slot de registro
        eliminarUsuario(usuarioListo);
    }

    if(dataString == "004\n"){


        QString usuario(socket->readLine()) ;
        QString permiso(socket->readLine());
        QString archivo(socket->readLine());

        qDebug() << "En thread " << usuario << permiso << archivo;

        //Elimino el \n
        string usuarioTmp = usuario.toStdString();
        usuarioTmp.erase(std::remove(usuarioTmp.begin(),usuarioTmp.end(), '\n'));

        string permisoTmp = permiso.toStdString();
        permisoTmp.erase(std::remove(permisoTmp.begin(),permisoTmp.end(), '\n'));

        string archivoTmp = archivo.toStdString();
        archivoTmp.erase(std::remove(archivoTmp.begin(),archivoTmp.end(), '\n'));

        //Convierto las entradas de nuevo a QString
        QString usuarioListo = QString::fromStdString(usuarioTmp);
        QString permisoListo = QString::fromStdString(permisoTmp);
        QString archivoListo = QString::fromStdString(archivoTmp);

        //Llamo al Slot de registro
        cambiarPermisos(usuarioListo,permisoListo,archivoListo);
    }


    if(dataString == "005\n"){


        QString usuario(socket->readLine()) ;
        QString permiso(socket->readLine());
        QString archivo(socket->readLine());

        qDebug() << "En thread " << usuario << permiso << archivo;

        //Elimino el \n
        string usuarioTmp = usuario.toStdString();
        usuarioTmp.erase(std::remove(usuarioTmp.begin(),usuarioTmp.end(), '\n'));

        string permisoTmp = permiso.toStdString();
        permisoTmp.erase(std::remove(permisoTmp.begin(),permisoTmp.end(), '\n'));

        string archivoTmp = archivo.toStdString();
        archivoTmp.erase(std::remove(archivoTmp.begin(),archivoTmp.end(), '\n'));

        //Convierto las entradas de nuevo a QString
        QString usuarioListo = QString::fromStdString(usuarioTmp);
        QString permisoListo = QString::fromStdString(permisoTmp);
        QString archivoListo = QString::fromStdString(archivoTmp);

        //Llamo al Slot de registro
        removerPermiso(usuarioListo,permisoListo,archivoListo);
    }




    if(dataString == "006\n"){


        QString sentencia(socket->readLine()) ;




        //Elimino el \n
        string sentenciaTmp = sentencia.toStdString();
        sentenciaTmp.erase(std::remove(sentenciaTmp.begin(),sentenciaTmp.end(), '\n'));



        //Convierto las entradas de nuevo a QString
        QString sentenciaListo = QString::fromStdString(sentenciaTmp);


        //Llamo al Slot de registro
        sentenciaDeUsuario(sentenciaListo);
    }

        socket->flush();

    // will write on server side window
    //qDebug() << socketDescriptor << " Data in: " << Data;
    //socket->write(Data);

//    qDebug() << "escribo";
//    test();



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
