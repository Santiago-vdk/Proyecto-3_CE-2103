#ifndef CREARSERVIDOR_H
#define CREARSERVIDOR_H

#include <QDialog>

namespace Ui {
class crearServidor;
}

class crearServidor : public QDialog
{
    Q_OBJECT

public:
    explicit crearServidor(QWidget *parent = 0);
    ~crearServidor();
   QString getIP();
    QString getPuerto();
    bool getNuevoUsuarios();
    bool getNuevoPermisos();


private slots:
    void on_pushButton_clicked();

signals:
    void iniciarServidor();

private:
    Ui::crearServidor *ui;
};

#endif // CREARSERVIDOR_H
