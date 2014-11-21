#-------------------------------------------------
#
# Project created by QtCreator 2014-10-21T02:14:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport network

TARGET = Proyecto-3_CE-2103
TEMPLATE = app


SOURCES += main.cpp\
    facade.cpp \
    interprete.cpp \
    GUI.cpp \
    ObjectTreeModel.cpp \
    tabla.cpp \
    nodoTabla.cpp \
    listaTabla.cpp \
    compress.cpp \
    metaDato.cpp \
    NodoMetaDato.cpp \
    ListaMetaDato.cpp \
    ArchivoAleatorio.cpp \
    Registro.cpp \
    sistemaArchivos.cpp \
    NodoDato.cpp \
    MatrizDato.cpp \
    ListaDato.cpp \
    com.cpp \
    crearServidor.cpp \
    mainwindow.cpp \
    myserver.cpp \
    mythread.cpp \
    simplecrypt.cpp

HEADERS  += \
    facade.h \
    interprete.h \
    GUI.h \
    ObjectTreeModel.h \
    tabla.h \
    nodoTabla.h \
    listaTabla.h \
    ../../../../../Users/David/Desktop/compress.h \
    compress.h \
    metaDato.h \
    NodoMetaDato.h \
    ListaMetaDato.h \
    ArchivoAleatorio.h \
    Registro.h \
    sistemaArchivos.h \
    NodoDato.h \
    MatrizDato.h \
    ListaDato.h \
    com.h \
    crearServidor.h \
    mainwindow.h \
    myserver.h \
    mythread.h \
    simplecrypt.h

FORMS    += \
    GUI.ui \
    crearServidor.ui \
    mainwindow.ui

RESOURCES += \
    recursos.qrc
