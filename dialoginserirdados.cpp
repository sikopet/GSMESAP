#include "DialogInserirDados.h"
#include "ui_dialoginserirdados.h"

DialogInserirDados::DialogInserirDados(tabelasDoBancoDeDados tb, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInserirDados)
{
    ui->setupUi(this);

    tabelaAtiva = tb;

    model = new QSqlQueryModel;
    model->setQuery(geraConsulta(), QSqlDatabase::database("default"));

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->resizeColumnsToContents();

    connect(ui->lineEdit_Inserir, SIGNAL(returnPressed()), this,
            SLOT(acaoDeInserirOsDados()));
}

void DialogInserirDados::acaoDeInserirOsDados()
{
    if (ui->lineEdit_Inserir->text().isNull())
        return;

    InserirDados *inserir;

    switch(tabelaAtiva)
    {
    case disciplinas:
        inserir = new InserirDados("disciplina",
                                   "disciplina",
                                   ui->lineEdit_Inserir->text());
        break;
    case categoria:
        inserir = new InserirDados("categoria",
                                   "categoria",
                                   ui->lineEdit_Inserir->text());
        break;
    case regime_juridico:
        inserir = new InserirDados("regime_juridico",
                                   "regime_juridico",
                                   ui->lineEdit_Inserir->text());
        break;
    case sede:
        inserir = new InserirDados("sede",
                                   "sede",
                                   ui->lineEdit_Inserir->text());
        break;
    case situacao:
        inserir = new InserirDados("situacao",
                                   "situacao",
                                   ui->lineEdit_Inserir->text());
        break;
    }

    if (inserir->dadosInseridos())
    {
        // Atualiza o tableView
        model->setQuery(model->query().lastQuery(), QSqlDatabase::database("default"));
        // Limpa o campo lineEdit_Inserir
        ui->lineEdit_Inserir->clear();

        QMessageBox::information(this, "Dados Inseridos", "Dados inseridos com sucesso");
    }
    else
        QMessageBox::information(this, "Dados Não Inseridos", inserir->ultimoErro().text());
}

QString DialogInserirDados::geraConsulta()
{
    QString q;
    switch(tabelaAtiva)
    {
    case categoria:
        q = "SELECT categoria_id AS Id, categoria AS Categoria FROM categoria";
        break;
    case disciplinas:
        q = "SELECT disciplina_id AS Id, disciplina AS Disciplina FROM disciplina";
        break;
    case regime_juridico:
        q = "SELECT reg_jur_id AS Id, regime_juridico AS \"Regime Jurídico\" FROM regime_juridico";
        break;
    case sede:
        q = "SELECT sede_id AS Id, sede AS Sede FROM sede";
        break;
    case situacao:
        q = "SELECT situacao_id AS Id, situacao AS \"Situação\" FROM situacao";
        break;
    default:
        q = "";
    }

    return q;
}

DialogInserirDados::~DialogInserirDados()
{
    delete ui;
}
