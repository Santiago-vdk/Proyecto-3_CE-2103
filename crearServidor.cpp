#include "crearServidor.h"
#include "ui_crearServidor.h"
#include <QTcpSocket>
#include "ostream"
#include "iostream"
#include "fstream"
#include <QHostAddress>

using namespace std;

crearServidor::crearServidor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::crearServidor)
{
    ui->setupUi(this);

    QTcpSocket socket;
    QString ipLocal;
    socket.connectToHost("8.8.8.8", 53); // google DNS, or something else reliable
    if (socket.waitForConnected()) {
        ipLocal =  socket.localAddress().toString();

    } else {
        qWarning()
                << "error al detectar IP del servidor:"
                << socket.errorString();
    }

    ui->direccionIP->setText(ipLocal);
    ui->puerto->setText("6666");
    ui->ipAccesoLabel->setText(ipLocal);
}

crearServidor::~crearServidor()
{
    delete ui;
}

QString crearServidor::getIP()
{
    return ui->direccionIP->text();
}

QString crearServidor::getPuerto()
{
    return ui->puerto->text();
}

bool crearServidor::getNuevoUsuarios()
{
    return ui->nuevoUsuarios->isChecked();
}

bool crearServidor::getNuevoPermisos()
{
    return ui->nuevoPermisos->isChecked();
}

void crearServidor::on_pushButton_clicked()
{
    iniciarServidor();
}
