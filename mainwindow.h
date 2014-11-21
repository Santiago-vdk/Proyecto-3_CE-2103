#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "myserver.h"
#include "string"
#include "crearServidor.h"
#include <QTcpSocket>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   // bool usuarioExiste(string pUsuario);

private slots:
    void on_startServer_clicked();
    void on_connectServer_clicked();
    void on_botonRegistrar_clicked();
    void crearServer();
    void clienteAceptado();
    void clienteDenegado();

public slots:
    void recibirMensajeServidor(QString pMensaje);

private:
    Ui::MainWindow *ui;
    MyServer server;
    crearServidor *vistaServer;
    QTcpSocket  *socket;
    bool banderaKicked;

protected:
    void keyPressEvent(QKeyEvent *event); // declaration



};

#endif // MAINWINDOW_H
