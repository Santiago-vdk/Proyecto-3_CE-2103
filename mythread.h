// mythread.h

#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(qintptr ID, QObject *parent = 0);

    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);
    void auth(QString object1, QString object2);
    void registrar(QString object1, QString object2);
    void emitirNotificacionUsuario(QString pMensaje);

public slots:
    void readyRead();
    void disconnected();
    void expulsarCliente();
    void llegadaNotificacion(QString pCodigo);

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    void test();
};

#endif // MYTHREAD_H
