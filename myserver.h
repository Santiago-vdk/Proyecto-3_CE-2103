// myserver.h

#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include "mythread.h"
#include "fstream"
#include "interprete.h"


using namespace std;

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void startServer(QString ip, QString puerto, bool archivoUsers, bool archivoPermisos);
signals:

    void clienteDenegado();
    void notifaciones(QString pCodigo);

public slots:
    void authUsuario(QString pUsuario, QString pContrasenia);
    void regisUsuario(QString pUsuario, QString pContrasenia);
    void dropUser(QString pUsuario);
        void actualizarPermisos(QString pUsuario,QString pPermisos, QString pArchivo);
        void quitarPermisos(QString pUsuario,QString pPermisos, QString pArchivo);
        void sentenciaNuevaUsuario(QString sentencia);


private:
    void revisarArchivos();
    void crearSuperUsuario();
    void crearPermisosSuperUsuario();
    char * nombreArchivoUsuarios;
    char * nombreArchivoPermisos;
    Interprete *_interprete;



protected:
    void incomingConnection(qintptr socketDescriptor);

};

#endif // MYSERVER_H
