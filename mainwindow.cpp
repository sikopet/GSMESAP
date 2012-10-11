#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tabwidget = new QTabWidget;
    tabwidget->setTabsClosable(true);
    tabwidget->setDocumentMode(true);

    // Menu Editar
    connect(ui->menu_editar, SIGNAL(triggered(QAction*)), this,
            SLOT(abre_visoes(QAction*)));

    // Menu Inserir
    connect(ui->menu_inserir, SIGNAL(triggered(QAction*)), this,
            SLOT(abre_formulario_para_inserir_registro(QAction*)));

    // Menu Inserir -> Excluir
    connect(ui->menu_excluir, SIGNAL(triggered(QAction*)), this,
            SLOT(abre_formulario_para_excluir_registro(QAction*)));

    // Menu Ferramentas
    connect(ui->action_ferramentas_documentos, SIGNAL(triggered()), this,
            SLOT(abre_forumulario_ferramentas_documentos()));

    // Configurar conexão
    connect(ui->action_configurar_conexao, SIGNAL(triggered()), this,
            SLOT(abre_formulario_para_configurar_conexao()));

    // Exporta para CSV
    connect(ui->action_exportar_para_csv, SIGNAL(triggered()), this,
            SLOT(exporta_para_csv()));

    // Fecha uma aba
    connect(tabwidget, SIGNAL(tabCloseRequested(int)), this,
            SLOT(fecha_tab(int)));

    //Tenta Conectar automaticamente
    QSettings set;
    if (set.value("Conectar").toBool())
    {
        ConnectionSettings conn;
        conn.tentaConectar();
    }

    setCentralWidget(tabwidget);
}

void MainWindow::abre_formulario_para_configurar_conexao()
{
    ConnectionSettings *f = new ConnectionSettings(this);
    f->setWindowFlags(Qt::Dialog);
    f->show();
}

void MainWindow::abre_formulario_para_inserir_registro(QAction *act)
{

    if (act == ui->action_inserir_professor)
    {
        DialogInserirProfessor *p = new DialogInserirProfessor(this);
        p->setWindowFlags(Qt::Dialog);
        p->show();
    }
    else
    {
        DialogInserirDados *s;

        if (act == ui->action_inserir_categoria)
            s = new DialogInserirDados(categoria, this);
        else if (act == ui->action_inserir_disciplinas)
            s = new DialogInserirDados(disciplina, this);
        else if (act == ui->action_inserir_reg_juridico)
            s = new DialogInserirDados(regime_juridico, this);
        else if (act == ui->action_inserir_sede)
            s = new DialogInserirDados(sede, this);
        else if (act == ui->action_inserir_situacao)
            s = new DialogInserirDados(situacao, this);

        s->show();
    }
}

void MainWindow::abre_formulario_para_excluir_registro(QAction *act)
{
    DialogExcluirRegistro *exc;
    if (ui->action_excluir_professores == act)
        exc = new DialogExcluirRegistro(professor);
    if (ui->action_excluir_situacoes == act)
        exc = new DialogExcluirRegistro(situacao);
    if (ui->action_excluir_categorias == act)
        exc = new DialogExcluirRegistro(categoria);
    if (ui->action_excluir_reg_jur == act)
        exc = new DialogExcluirRegistro(regime_juridico);
    if (ui->action_excluir_sedes == act)
        exc = new DialogExcluirRegistro(sede);
    if (ui->action_excluir_disciplinas == act)
        exc = new DialogExcluirRegistro(disciplina);

    exc->show();
}

void MainWindow::abre_forumulario_ferramentas_documentos()
{
    DialogDocumentos *docs = new DialogDocumentos(this);
    docs->setWindowFlags(Qt::Dialog);
    docs->show();
}

void MainWindow::abre_visoes(QAction *act)
{
    Viewer *v = new Viewer(this);

    if (act == ui->action_editar_professores)
        adiciona_tab(v, "Professores", GSMESAP::professor);
    if (act == ui->action_editar_situacao)
        adiciona_tab(v, "Situacao", GSMESAP::situacao);
    if (act == ui->action_editar_categoria)
        adiciona_tab(v, "Categoria", GSMESAP::categoria);
    if (act == ui->action_editar_reg_juridico)
        adiciona_tab(v, "RegimeJuridico", GSMESAP::regime_juridico);
    if (act == ui->action_editar_sede)
        adiciona_tab(v, "Sede", GSMESAP::sede);
    if (act == ui->action_editar_disciplinas)
        adiciona_tab(v, "Disciplina", GSMESAP::disciplina);
}

void MainWindow::adiciona_tab(Viewer *view, QString tabName, GSMESAP::tabelasDoBancoDeDados tb)
{
    if (listaDasAbas.contains(tabName))
        tabwidget->setCurrentIndex(listaDasAbas.indexOf(tabName));
    else
    {
        view->setaTabelaAtiva(tb);
        tabwidget->setCurrentIndex(tabwidget->addTab(view, tabName));
        listaDasAbas << tabName;
    }
}

void MainWindow::fecha_tab(int index)
{
    tabwidget->removeTab(index);
    listaDasAbas.removeAt(index);
}

void MainWindow::exporta_para_csv()
{
    if (tabwidget->currentIndex() == -1)
        return;

    QString abaAtiva = listaDasAbas.at(tabwidget->currentIndex());
    QString q;

    if (abaAtiva == "Professores")
        q = "SELECT * FROM lista_professores";
    if (abaAtiva == "Situacao")
        q = "SELECT * FROM situacao";
    if (abaAtiva == "Categoria")
        q = "SELECT * FROM categoria";
    if (abaAtiva == "RejimeJuridico")
        q = "SELECT * FROM categoria";
    if (abaAtiva == "Sede")
        q = "SELECT * FROM sede";
    if (abaAtiva == "Disciplina")
        q = "SELECT * FROM disciplina";

    QString filename = QFileDialog::getSaveFileName(this, "Save", QDir::homePath(), tr("CSV Files (*.csv)"));
    if (filename.isEmpty())
        return;

    QSqlQuery *query = new QSqlQuery(q, QSqlDatabase::database("default"));
    ExportaTabela *exporta = new ExportaTabela(query, filename);

    if (exporta->exporta())
        QMessageBox::information(this, "Documento exportado", filename);
}

MainWindow::~MainWindow()
{
    delete ui;
}
