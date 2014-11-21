// myserver.cpp

#include "myserver.h"
#include "mythread.h"
#include "fstream"
#include <iostream>
#include "string"

#include "simplecrypt.h"

using namespace std;

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{

}

void MyServer::startServer(QString ip, QString puerto, bool archivoUsers, bool archivoPermisos) //Se deberia instanciar el archivo con los usuarios
{
    //Configuracion del servidor
    int port = puerto.toInt();
    QHostAddress a;
    a = QHostAddress("192.168.1.140"); //ip

    //Nombre default del archivo que contiene los usuarios
    nombreArchivoUsuarios = "usuarios.txt";

    //Nombre default del archivo que contiene los permisos
    nombreArchivoPermisos = "permisos.txt";


    qDebug() << archivoUsers << archivoPermisos  ;
    //Creo los archivos de usuarios y permisos si la opcion fue seleccionada
    if(archivoUsers){
        ofstream outputFile("usuarios.txt");
        if( ! outputFile )	{
            qDebug() << "Error al crear archivo de usuarios..." ;
        }
        outputFile.close();
        crearSuperUsuario();
    }

    if(archivoPermisos){
        ofstream outputFile("permisos.txt");
        if( ! outputFile )	{
            qDebug() << "Error al crear archivo de permisos..." ;
        }
        outputFile.close();
        crearPermisosSuperUsuario();
    }

    if(!this->listen(a,port))
    {
        this->listen();
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Direccion IP " << a << endl;
        qDebug() << "Escuchando Puerto  " << port << "...";
        qDebug() << "Comprobando existencia de archivos";
        revisarArchivos();
    }

}

void MyServer::authUsuario(QString pUsuario, QString pContrasenia)
{
    qDebug() << "Autenticando";
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));

    ifstream archivo(nombreArchivoUsuarios);

    bool flag = false;


    while(!archivo.eof() && flag != true){
        string lineRead;
        getline(archivo, lineRead);
        string comparaUser = pUsuario.toStdString();
        string comparaContra = pContrasenia.toStdString();

        //Convierto el line de nuevo a un QString para desencriptar
        QString lineTmp = QString::fromStdString(lineRead);
        QString lineDesencriptado = crypto.decryptToString(lineTmp);
        string line = lineDesencriptado.toStdString();
        if (line.substr(0,line.find(",")).compare(comparaUser) == 0 && line.substr(line.find(",")+1,line.length()).compare(comparaContra) == 0){
            qDebug() << "Cliente Autenticado Correctamente!";
            flag = true;
            notifaciones("001");

            return;
        }
    }
    if(!flag){
        qDebug() << "Cliente Denegado!";
        clienteDenegado();
        return;

    }
    archivo.close();
}

void MyServer::regisUsuario(QString pUsuario, QString pContrasenia)
{
    qDebug() << "Agregando nuevo usuario";
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));
    ofstream archivo(nombreArchivoUsuarios, fstream::app);
    archivo.seekp(0);
    QString STREAM = pUsuario + "," + pContrasenia;
    QString streamENCRIPTADO = crypto.encryptToString(STREAM);
    archivo << streamENCRIPTADO.toStdString() << endl;
    archivo.close();
}



void MyServer::revisarArchivos()
{
    //Revisamos si el archivo de usuarios en realidad existe
    ifstream ofs(nombreArchivoUsuarios);
    if( ! ofs )	{
        qDebug() << "El archivo de usuarios no existe, cerrando conexion..." ;
        this->close();

    }
    ofs.close();

    //Revisamos si el archivo de usuarios en realidad existe
    ifstream ofs2(nombreArchivoPermisos);
    if( ! ofs2 )	{
        qDebug() << "El archivo de permisos no existe, cerrando conexion..." ;
        this->close();
    }
    ofs2.close();



}

void MyServer::crearSuperUsuario()
{
    qDebug() << "Agregando super usuario";
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));
    ofstream archivo(nombreArchivoUsuarios, fstream::app);
    archivo.seekp(0);
    QString STREAM = "system,manager";
    QString streamENCRIPTADO = crypto.encryptToString(STREAM);
    archivo << streamENCRIPTADO.toStdString() << endl;
    archivo.close();
}

void MyServer::crearPermisosSuperUsuario()
{
    qDebug() << "Agregando permisos super usuario";
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));
    ofstream archivo(nombreArchivoPermisos, fstream::app);
    archivo.seekp(0);
    QString STREAM = "master";
    QString streamENCRIPTADO = crypto.encryptToString(STREAM);
    archivo << streamENCRIPTADO.toStdString() << endl;
    archivo.close();
}






void MyServer::incomingConnection(qintptr socketDescriptor)
{
    // We have a new connection
    qDebug() << socketDescriptor << " Connecting...";

    MyThread *thread = new MyThread(socketDescriptor, this);
    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(auth(QString , QString )), this, SLOT(authUsuario(QString , QString ))); //Slot autenticacion
    connect(this, SIGNAL(clienteDenegado()),thread, SLOT(expulsarCliente()));   //Slot expulsarCliente
    connect(thread, SIGNAL(registrar(QString , QString )), this, SLOT(regisUsuario(QString , QString ))); //Slot registrar

    connect(this, SIGNAL(notifaciones(QString)), thread, SLOT(llegadaNotificacion(QString))); //Comunicacion textual servidor-cliente

    thread->start();
}
