#include "facade.h"
#include "sistemaArchivos.h"

Facade::Facade(QTcpSocket *socket)
{


    _interprete = new Interprete(socket);

}

bool Facade::revizarSintaxis(string sentencia)
{
    return _interprete->revisarSintaxis(sentencia);
}

bool Facade::ejecutar(string sentencia)
{
    return _interprete->ejecutar(sentencia);
}

tabla *Facade::getTablaTmp()
{
    return _interprete->getTablaTmp();
}


