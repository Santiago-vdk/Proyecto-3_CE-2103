#include "GUI.h"
#include "ui_GUI.h"
#include <QStandardItemModel>
#include <QSplitter>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QFormLayout>
#include <QMessageBox>
#include "string"
#include <QDebug>
#include <QToolBar>
#include <QPropertyAnimation>
#include <QInputDialog>
#include <QDir>
#include <QModelIndex>
#include "objecttreemodel.h"

#include "listaTabla.h"
#include "tabla.h"
#include <facade.h>

using namespace std;

GUI::GUI(QWidget *parent, QTcpSocket *socket) :
    QMainWindow(parent),
    ui(new Ui::GUI)
{
    ui->setupUi(this);
    this->hide();
    this->setWindowFlags( (windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);

    _socket = socket;
    facade = new Facade(_socket);





    //Barra de Menu
    QPixmap nuevaBasePix(":/recursos/database.png");
    QPixmap cmdPix(":/recursos/cmd.png");
    QPixmap sqlPix(":/recursos/sql.png");

    QToolBar *toolbar = addToolBar("ToolBar");
    setIconSize(QSize(40,40));

    QAction *fsql = toolbar->addAction("FSQL");
    QAction *ventananuevaBase = toolbar->addAction(QIcon(nuevaBasePix),"Nueva Base de Datos");
    QAction *ventanacmd = toolbar->addAction(QIcon(cmdPix),"Cambiar a Modo CMD");
    QAction *ventanasql = toolbar->addAction(QIcon(sqlPix),"Ejecutar Busqueda");

    toolbar->addSeparator();

    connect(ventananuevaBase,SIGNAL(triggered()), this, SLOT(crearBaseDeDatos()));
    connect(ventanacmd,SIGNAL(triggered()), this, SLOT(cambiarModoCMD()));
    connect(ventanasql,SIGNAL(triggered()), this, SLOT(cambiarModoSQL()));

    this->addToolBar(toolbar);
    //Fin barra menu

    //Propiedades de las ventanas, botones y iconos
    ui->output->setReadOnly(true);
    ui->vistaArbol->setDisabled(true);
    ui->input->setDisabled(true);
    ui->output->setReadOnly(true);
    cursorOutput = ui->output->textCursor();

    //Set' arbol
    root= new QObject();
    root->setObjectName( "root" );
    ui->arbolLayout->addWidget( ui->vistaArbol );
    ui->arbolWidget->setLayout(ui->arbolLayout);
    vistaArbol();
    //Fin de propiedades de las ventanas


    crearPalabrasReservadas();


}

void GUI::autenticacion()
{

}

void GUI::crearBaseDeDatos()
{
    qDebug() << "Creo una nueva base de datos";

    bool ok;
    QInputDialog* inputDialog = new QInputDialog();
    inputDialog->setOptions(QInputDialog::NoButtons);

    QString text =  inputDialog->getText(NULL ,"QInputDialog::getText() Example",
                                         "Nombre Base de Datos:", QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
    {
        qDebug() << text;
        QObject *base = new QObject(root);
        base->setObjectName(text);
        vistaArbol();
        //Insertar en lista con bases
    }
    ui->vistaArbol->setDisabled(false);
    ui->input->setDisabled(false);
}

void GUI::cambiarModoCMD()
{
    qDebug() << "Modo CMD";
    ui->stackedWidget->setCurrentIndex(0);

}

void GUI::cambiarModoSQL()
{
    qDebug() << "Modo SQL";
    ui->stackedWidget->setCurrentIndex(1);
}

void GUI::on_botonEnviar_clicked()
{
    if(!(ui->input->text().isEmpty())){
        std::string comando = ui->input->text().toStdString();
        /*Se llama al parser con el comando ingresado
            * if (parser(comando))
            * Luego implementar el comando grafico
           */
        qDebug() << "aqui";
        qDebug() << ui->input->text();
        if(facade->revizarSintaxis(comando)){
            qDebug() << "Funko";
            if(facade->ejecutar(comando)){
                tablaVisual = facade->getTablaTmp();
                refrescaTabla();

            }

        }

        ui->output->append(ui->input->text());
        ui->input->clear();
    }
    else{
        QMessageBox *empty =  new QMessageBox();
        empty->setText("Error, por favor ingrese un comando.");
        empty->show();
    }
}

void GUI::on_limpiarOutput_clicked()
{
    ui->output->clear();
}



void GUI::on_input_textChanged(const QString &arg1)
{

}

void GUI::on_output_textChanged()
{
    selectionsOutput.clear();
    ui->output->extraSelections().clear();


    //Formato para tipos de datos
    QTextCharFormat fmt3;
    fmt3.setForeground(QColor("#808BED"));
    fmt3.setFontWeight(QFont::Bold);


    //Formato palabras reservadas
    QTextCharFormat fmt;
    fmt.setForeground(QColor("#028885"));
    fmt.setFontWeight(QFont::Bold);


    //Formato Texto Entre Parentesis
    QTextCharFormat fmt2;
    fmt2.setForeground(QColor("Black"));
    fmt2.setFontWeight(QFont::Bold);

    //Texto entre parentesis
    while( !(cursorOutput = ui->output->document()->find(QRegExp("("), cursorOutput)).isNull()) {
        QTextEdit::ExtraSelection sel = { cursorOutput, fmt2 };
        selectionsOutput.append(sel);
    }

    //Palabras reservadas
    for(int i = 0; i < listaPalabrasReservadas.size(); i++){
        while( !(cursorOutput = ui->output->document()->find(QRegExp(listaPalabrasReservadas.at(i)), cursorOutput)).isNull()) {
            QTextEdit::ExtraSelection sel = { cursorOutput, fmt };
            selectionsOutput.append(sel);
        }
    }

    //Tipos reservadas
    for(int i = 0; i < listaTiposReservados.size(); i++){

        while( !(cursorOutput = ui->output->document()->find(QRegExp(listaTiposReservados.at(i)), cursorOutput)).isNull()) {
            QTextEdit::ExtraSelection sel = { cursorOutput, fmt3 };
            selectionsOutput.append(sel);
        }
    }



    ui->output->setExtraSelections(selectionsOutput);
    ui->output->extraSelections().clear();
}

void GUI::on_input_returnPressed()
{
    if(!(ui->input->text().isEmpty())){
        std::string comando = ui->input->text().toStdString();
        /*Se llama al parser con el comando ingresado
            * if (parser(comando))
            * Luego implementar el comando grafico
           */
        qDebug() << "aqui";
        qDebug() << ui->input->text();
        if(facade->revizarSintaxis(comando)){
            qDebug() << "Funko";
            facade->ejecutar(comando);
            refrescaTabla();


             QByteArray Data = "006\n" ;
              QByteArray Data1(comando.c_str());
            _socket->write(Data);
            _socket->write(Data1);




        }

        ui->output->append(ui->input->text());
        ui->input->clear();
    }
    else{
        QMessageBox *empty =  new QMessageBox();
        empty->setText("Error, por favor ingrese un comando.");
        empty->show();
    }
}

void GUI::refrescaTabla()
{

    model.clear();
    horizontalHeader.clear();
    ui->vistaTabla->reset();


    _header = facade->getTablaTmp()->getMetaDato();
    _infoTabla = facade->getTablaTmp()->getMatrizDato();

    //Insertamos los headers
    for(int i = 0; i < _header->getTamanio(); i++){
        horizontalHeader.append(QString::fromStdString(_header->buscarPosicion(i)->getmetaDato()));
    }

    for(int i = 0; i <_infoTabla->getTamanio(); i++){
        for(int j = 0; j < _infoTabla->getHead()->getTamanio(); j++){
            QStandardItem *item = new QStandardItem(QString::fromStdString(_infoTabla->buscarDatoEnPos(i,j)));
            model.setItem(i, j, item);
        }
    }


    model.index(1,1,model.index(0,0));
    model.setHorizontalHeaderLabels(horizontalHeader);

    ui->vistaTabla->setModel(&model);
    ui->vistaTabla->resizeRowsToContents();
    ui->vistaTabla->resizeColumnsToContents();
}

void GUI::on_copyClipboard_clicked()
{
    ui->output->selectAll();
    ui->output->copy();

}

void GUI::vistaArbol()
{


    ObjectTreeModel *model = new ObjectTreeModel(root);
    ui->vistaArbol->setModel( model );


}

//void GUI::on_pushButton_clicked()
//{

//    //    child = new QObject( tabla1 );
//    //    child->setObjectName( "Mark" );
//    //    child = new QObject( tabla1 );
//    //    child->setObjectName( "Bob" );
//    //    child = new QObject( tabla1 );
//    //    child->setObjectName( "Kent" );

//    ui->vistaArbol->expandAll();

//}

void GUI::crearPalabrasReservadas()
{
    //Palabras reservadas del FSQL
    listaPalabrasReservadas.append("CREATE TABLE");
    listaPalabrasReservadas.append("SELECT");
    listaPalabrasReservadas.append("INSERT INTO");
    listaPalabrasReservadas.append("UPDATE");
    listaPalabrasReservadas.append("DELETE FROM");
    listaPalabrasReservadas.append("CREATE INDEX");
    listaPalabrasReservadas.append("COMPRESS TABLE");
    listaPalabrasReservadas.append("BACKUP TABLE");
    listaPalabrasReservadas.append("RESTORE TABLE");
    listaPalabrasReservadas.append("VALUES");
    listaPalabrasReservadas.append("WHERE");
    listaPalabrasReservadas.append("FROM");

    //Tipos de datos reservados
    listaTiposReservados.append("String");
    listaTiposReservados.append("Integer");
    listaTiposReservados.append("Decimal");

}




GUI::~GUI()
{
    delete ui;
}
