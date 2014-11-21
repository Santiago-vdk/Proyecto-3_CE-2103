#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myserver.h"
#include "string"
#include "ostream"
#include "iostream"
#include "fstream"
#include "crearServidor.h"
#include <QKeyEvent>
#include  <GUI.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet("background:transparent;");
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->contraseniaUsuario->setEchoMode(QLineEdit::Password);
    banderaKicked = false;




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startServer_clicked()
{

    vistaServer = new crearServidor();
    vistaServer->show();

    connect(vistaServer,SIGNAL(iniciarServidor()),this,SLOT(crearServer()));

}

void MainWindow::on_connectServer_clicked()
{


    socket = new QTcpSocket();

    string username = ui->nombreUsuario->text().toStdString().append("\n");
    string contrasenia = ui->contraseniaUsuario->text().toStdString().append("\n");

    socket->connectToHost("192.168.1.140",6666);
    QByteArray Data = "001\n" ;
    QByteArray Data1(username.c_str(), username.length());
    QByteArray Data2(contrasenia.c_str(), contrasenia.length());
    socket->write(Data);
    socket->write(Data1);
    socket->write(Data2);



    connect(socket, SIGNAL(disconnected()),
                this, SLOT(clienteDenegado()));






    if(!banderaKicked){
        clienteAceptado();
    }




}

void MainWindow::on_botonRegistrar_clicked()
{
    string username = ui->nombreUsuario->text().toStdString().append("\n");
    string contrasenia = ui->contraseniaUsuario->text().toStdString().append("\n");
    QTcpSocket  *socket = new QTcpSocket();
    socket->connectToHost("192.168.1.140",6666);
    QByteArray Data = "002\n" ;
    QByteArray Data1(username.c_str(), username.length());
    QByteArray Data2(contrasenia.c_str(), contrasenia.length());
    socket->write(Data);
    socket->write(Data1);
    socket->write(Data2);




}

void MainWindow::crearServer()
{
    vistaServer->close();

    //Iniciar Servidor
    qDebug() << vistaServer->getIP() ;
    server.startServer(vistaServer->getIP(),vistaServer->getPuerto(),vistaServer->getNuevoUsuarios(),vistaServer->getNuevoPermisos());
    ui->startServer->setDisabled(true);



}

void MainWindow::clienteAceptado()
{
    qDebug("Nice");
    this->close();
    GUI *gui = new GUI(NULL,socket);
    gui->show();
}

void MainWindow::clienteDenegado()
{
    qDebug("Auch");
    //socket->close();
    banderaKicked = true;
    this->close();
}

void MainWindow::recibirMensajeServidor(QString pMensaje)
{
    qDebug() << pMensaje;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Escape) // Your key here.
           {
                  this->close();
            }
}










