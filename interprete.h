#ifndef INTERPRETE_H
#define INTERPRETE_H
#include <string>
#include "sistemaArchivos.h"
#include "listaTabla.h"
#include <QTcpSocket>
using namespace std;

class Interprete
{
public:

    Interprete(QTcpSocket *socket);
    bool revisarSintaxis(string sentencia);
    bool ejecutar(string sentencia);
    tabla *getTablaTmp();

private:

    bool existeTabla(string ptabla);
    bool existeColumna(tabla *ptabla, string columna);
    bool nombreValido(string nombre);
    bool datoValido(string dato);
    int cumpleWhere(tabla *ptabla, string pcondiciones, int ppos);

    bool revisarCreateTable(string sentencia);
    bool revisarSelect(string sentencia);
    bool revisarInsert(string sentencia);
    bool revisarUpdate(string sentencia);
    bool revisarDelete(string sentencia);
    bool revisarCreateIndex(string sentencia);
    bool revisarCompress(string sentencia);
    bool revisarBackup(string sentencia);
    bool revisarRestore(string sentencia);

    bool revisarCreateUser(string sentencia);
    bool revisarDropUser(string sentencia);
    bool revisarGrant(string sentencia);
    bool revisarRevoke(string sentencia);

    bool ejecutarCreateTable(string sentencia);
    bool ejecutarSelect(string sentencia);
    bool ejecutarInsert(string sentencia);
    bool ejecutarUpdate(string sentencia);
    bool ejecutarDelete(string sentencia);
    bool ejecutarCreateIndex(string sentencia);
    bool ejecutarCompress(string sentencia);
    bool ejecutarBackup(string sentencia);
    bool ejecutarRestore(string sentencia);

    bool ejecutarCreateUser(string sentencia);
    bool ejecutarDropUser(string sentencia);
    bool ejecutarGrant(string sentencia);
    bool ejecutarRevoke(string sentencia);

    int cargaTablas();
    bool has_suffix(const string& s, const string& suffix);
    sistemaArchivos *sis;
    void generarTabla(string pName);

    void crearArchivoTabla();
    void actualizarArchivoTabla();

    listaTabla * _listaTablas;
    bool _revisandoColumna;
    tabla *_tablaTmp;

    QTcpSocket *_socket;

};





#endif // INTERPRETE_H
