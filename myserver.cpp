// myserver.cpp

#include "myserver.h"
#include "mythread.h"
#include "fstream"
#include <iostream>
#include "string"

#include "simplecrypt.h"
#include "interprete.h"

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

    _interprete = new Interprete(NULL);

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
    ofstream archivoPermisos(nombreArchivoPermisos, fstream::app);
    archivo.seekp(0);  //Fragil
    archivoPermisos.seekp(0);

    //Escribo encriptadamente sobre usuarios
    QString STREAM = pUsuario + "," + pContrasenia;
    QString streamENCRIPTADO = crypto.encryptToString(STREAM);
    archivo << streamENCRIPTADO.toStdString() << endl;
    archivo.close();

    //Escribo sobre los permisos al usuario
    QString STREAMPERMISOS = pUsuario;

    archivoPermisos << STREAMPERMISOS.toStdString() << endl;
    archivoPermisos.close();

    archivoPermisos.close();
}

void MyServer::dropUser(QString pUsuario)
{
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));
    ifstream archivo(nombreArchivoUsuarios);
    ofstream out("outfile.txt");
    string lineRead;
    string comparaUser = pUsuario.toStdString();
    while(getline(archivo, lineRead)){
        QString lineTmp = QString::fromStdString(lineRead);
        QString lineDesencriptado = crypto.decryptToString(lineTmp);
        string line = lineDesencriptado.toStdString();

        if (!line.substr(0,line.find(",")).compare(comparaUser) == 0 ){
            qDebug("Existe usuario");
            out << lineRead << "\n";
        }
    }
    archivo.close();
    out.close();
    // delete the original file
    remove(nombreArchivoUsuarios);
    // rename old to new
    rename("outfile.txt",nombreArchivoUsuarios);
}

void MyServer::actualizarPermisos(QString pUsuario, QString pPermisos, QString pArchivo)
{

        SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));
    ifstream archivo(nombreArchivoUsuarios);

    ifstream archivoPermisos(nombreArchivoPermisos);

    ofstream archivoPermisosTmp("temporal.txt");


    string lineRead;
    string comparaUser = pUsuario.toStdString();
    string comparaPermisos = pPermisos.toStdString();
    string comparaArchivo = pArchivo.toStdString();




    while(getline(archivo, lineRead)){
        QString lineTmp = QString::fromStdString(lineRead);
        QString lineDesencriptado = crypto.decryptToString(lineTmp);
        string line = lineDesencriptado.toStdString();

        if (line.substr(0,line.find(",")).compare(comparaUser) == 0 ){ //Usuario Correcto
            qDebug("Existe usuario");
            string lineReadPermisos;
                archivoPermisos.seekg(0);
            while(getline(archivoPermisos, lineReadPermisos)){
                 if (lineReadPermisos.substr(0,lineReadPermisos.find(",")).compare(comparaUser) == 0 ){
                     qDebug("Existe en permisos");


                        cout << lineReadPermisos << endl;
                     if (lineReadPermisos.find(comparaArchivo) != string::npos ){



                         qDebug("habia archivo");

                         string STREAMPERMISOS = lineReadPermisos.substr(lineReadPermisos.find("(",lineReadPermisos.find(comparaArchivo)) + 1,lineReadPermisos.find(")",lineReadPermisos.find(comparaArchivo)) - lineReadPermisos.find("(",lineReadPermisos.find(comparaArchivo)) - 1);
                         string antesFound = lineReadPermisos.substr(0,lineReadPermisos.find("(",lineReadPermisos.find(comparaArchivo)) + 1);
                         string despuesFound = lineReadPermisos.substr(lineReadPermisos.find(")",lineReadPermisos.find(comparaArchivo)),lineRead.length());

                         string permisoSelect = STREAMPERMISOS.substr(0,1);
                         string permisoInsert = STREAMPERMISOS.substr(2,1);
                         string permisoDelete = STREAMPERMISOS.substr(4,1);
                         string permisoUpdate = STREAMPERMISOS.substr(6,1);

                         if(comparaPermisos.compare("select") == 0){
                             permisoSelect = "1";
                         }
                         if(comparaPermisos.compare("insert") == 0){
                             permisoInsert = "1";
                         }
                         if(comparaPermisos.compare("delete") == 0){
                             permisoDelete = "1";
                         }
                         if(comparaPermisos.compare("update") == 0){
                             permisoUpdate = "1";
                         }
                         STREAMPERMISOS = permisoSelect + "," + permisoInsert + "," + permisoDelete + "," + permisoUpdate;
                         cout << STREAMPERMISOS << endl;
                         archivoPermisos.seekg(0);
                         string itera;
                         while(getline(archivoPermisos, itera)){

                             if (itera.substr(0,itera.find(",")).compare(comparaUser) == 0 ){
                                 archivoPermisosTmp <<antesFound <<  STREAMPERMISOS << despuesFound << "\n";
                             }
                             else{
                                 archivoPermisosTmp << itera << "\n";
                             }
                         }
                     }
                     else{
                         string STREAMNUEVO;
                         string permisoSelect;
                         string permisoInsert;
                         string permisoDelete;
                         string permisoUpdate;

                         if(comparaPermisos.compare("select") == 0){

                             permisoSelect = "1";
                             permisoInsert = "0";
                             permisoDelete = "0";
                             permisoUpdate = "0";
                         }
                         if(comparaPermisos.compare("insert") == 0){
                             permisoSelect = "0";
                             permisoInsert = "1";
                             permisoDelete = "0";
                             permisoUpdate = "0";
                         }
                         if(comparaPermisos.compare("delete") == 0){
                             permisoSelect = "0";
                             permisoInsert = "0";
                             permisoDelete = "1";
                             permisoUpdate = "0";
                         }
                         if(comparaPermisos.compare("update") == 0){
                             permisoSelect = "0";
                             permisoInsert = "0";
                             permisoDelete = "0";
                             permisoUpdate = "1";
                         }

                         STREAMNUEVO = lineReadPermisos+","+ comparaArchivo + "(" + permisoSelect + ","+ permisoInsert + ","+ permisoDelete + ","+ permisoUpdate + ")";
                         cout << STREAMNUEVO << endl;
                         string itera;
                         archivoPermisos.seekg(0);
                         while(getline(archivoPermisos, itera)){
                             if (itera.substr(0,itera.find(",")).compare(comparaUser) == 0 ){

                                 archivoPermisosTmp << STREAMNUEVO << "\n";
                             }
                             else{
                                 archivoPermisosTmp << itera << "\n";
                             }
                         }

                     }
                 }
            }
        }
    }
    archivoPermisosTmp.close();
    archivo.close();
    archivoPermisos.close();

    remove(nombreArchivoPermisos);

    rename("temporal.txt",nombreArchivoPermisos);






}

void MyServer::quitarPermisos(QString pUsuario, QString pPermisos, QString pArchivo)
{






}

void MyServer::sentenciaNuevaUsuario(QString sentencia)
{

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
    connect(thread, SIGNAL(eliminarUsuario(QString)), this, SLOT(dropUser(QString))); //Slot registrar
    connect(thread,SIGNAL(cambiarPermisos(QString,QString,QString)),this,SLOT(actualizarPermisos(QString,QString,QString)));

    connect(thread,SIGNAL(removerPermisos(QString,QString,QString)),this,SLOT(quitarPermisos(QString,QString,QString)));
    connect(thread,SIGNAL(sentenciaDeUsuario(QString)),this,SLOT(sentenciaNuevaUsuario(QString)));


    thread->start();
}
