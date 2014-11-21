/********************************************************************************
** Form generated from reading UI file 'GUI.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QTextEdit *output;
    QLineEdit *input;
    QPushButton *botonEnviar;
    QPushButton *limpiarOutput;
    QTableView *vistaTabla;
    QPushButton *copyClipboard;
    QWidget *page_2;
    QTextEdit *textEdit_2;
    QPushButton *pushButton_2;
    QTableWidget *tableWidget;
    QWidget *arbolWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *arbolLayout;
    QTreeView *vistaArbol;
    QFrame *line;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GUI)
    {
        if (GUI->objectName().isEmpty())
            GUI->setObjectName(QStringLiteral("GUI"));
        GUI->resize(1016, 677);
        centralwidget = new QWidget(GUI);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(280, 10, 721, 611));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        output = new QTextEdit(page);
        output->setObjectName(QStringLiteral("output"));
        output->setGeometry(QRect(0, 350, 721, 201));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(11);
        font.setBold(false);
        font.setWeight(50);
        output->setFont(font);
        input = new QLineEdit(page);
        input->setObjectName(QStringLiteral("input"));
        input->setGeometry(QRect(0, 560, 641, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Calibri"));
        font1.setPointSize(12);
        input->setFont(font1);
        botonEnviar = new QPushButton(page);
        botonEnviar->setObjectName(QStringLiteral("botonEnviar"));
        botonEnviar->setGeometry(QRect(650, 560, 71, 31));
        limpiarOutput = new QPushButton(page);
        limpiarOutput->setObjectName(QStringLiteral("limpiarOutput"));
        limpiarOutput->setGeometry(QRect(0, 320, 75, 23));
        vistaTabla = new QTableView(page);
        vistaTabla->setObjectName(QStringLiteral("vistaTabla"));
        vistaTabla->setGeometry(QRect(0, 0, 721, 281));
        vistaTabla->setStyleSheet(QStringLiteral("gridline-color: rgb(85, 170, 255);"));
        copyClipboard = new QPushButton(page);
        copyClipboard->setObjectName(QStringLiteral("copyClipboard"));
        copyClipboard->setGeometry(QRect(80, 320, 75, 23));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        textEdit_2 = new QTextEdit(page_2);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(0, 30, 721, 231));
        textEdit_2->setStyleSheet(QStringLiteral("border-color: rgb(215, 248, 255);"));
        pushButton_2 = new QPushButton(page_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(0, 0, 101, 21));
        tableWidget = new QTableWidget(page_2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(0, 400, 721, 192));
        stackedWidget->addWidget(page_2);
        arbolWidget = new QWidget(centralwidget);
        arbolWidget->setObjectName(QStringLiteral("arbolWidget"));
        arbolWidget->setGeometry(QRect(10, 10, 231, 591));
        verticalLayoutWidget = new QWidget(arbolWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 231, 591));
        arbolLayout = new QVBoxLayout(verticalLayoutWidget);
        arbolLayout->setSpacing(6);
        arbolLayout->setContentsMargins(11, 11, 11, 11);
        arbolLayout->setObjectName(QStringLiteral("arbolLayout"));
        arbolLayout->setContentsMargins(0, 0, 0, 0);
        vistaArbol = new QTreeView(verticalLayoutWidget);
        vistaArbol->setObjectName(QStringLiteral("vistaArbol"));

        arbolLayout->addWidget(vistaArbol);

        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(250, -10, 20, 651));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        GUI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GUI);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1016, 21));
        GUI->setMenuBar(menubar);
        statusbar = new QStatusBar(GUI);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        GUI->setStatusBar(statusbar);

        retranslateUi(GUI);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GUI);
    } // setupUi

    void retranslateUi(QMainWindow *GUI)
    {
        GUI->setWindowTitle(QApplication::translate("GUI", "FSQL", 0));
        botonEnviar->setText(QApplication::translate("GUI", "Enviar", 0));
        limpiarOutput->setText(QApplication::translate("GUI", "Limpiar", 0));
        copyClipboard->setText(QApplication::translate("GUI", "Copiar-Texto", 0));
        pushButton_2->setText(QApplication::translate("GUI", "Ejecutar", 0));
    } // retranslateUi

};

namespace Ui {
    class GUI: public Ui_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
