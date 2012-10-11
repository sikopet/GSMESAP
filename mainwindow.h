#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QStringList>

#include "gsmesap_enums.h"
#include "connectionsettings.h"
#include "viewer.h"
#include "dialoginserirdados.h"
#include "dialoginserirprofessor.h"
#include "dialogexcluirregistro.h"
#include "exportatabela.h"
#include "dialogdocumentos.h"

using namespace GSMESAP;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void abre_formulario_para_configurar_conexao();
    void abre_forumulario_ferramentas_documentos();
    void abre_formulario_para_inserir_registro(QAction *act);
    void abre_formulario_para_excluir_registro(QAction *act);
    void abre_visoes(QAction *act);
    void fecha_tab(int index);
    void exporta_para_csv();

private:
    Ui::MainWindow *ui;
    QTabWidget *tabwidget;
    QStringList listaDasAbas;
    void adiciona_tab(Viewer *view, QString tabName, GSMESAP::tabelasDoBancoDeDados tb);
};

#endif // MAINWINDOW_H
