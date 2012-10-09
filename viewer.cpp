#include "viewer.h"

Viewer::Viewer(QWidget *parent) :
    QWidget(parent)
{ }

void Viewer::setaTabelaAtiva(GSMESAP::tabelasDoBancoDeDados tb)
{
    tabela = tb;
    switch(tabela)
    {
    case GSMESAP::professor:
        exibeTabelaProfessor();
        setWindowTitle("Professores");
        break;
    case GSMESAP::regime_juridico:
        exibeTabelaRegJuridico();
        setWindowTitle("Regime Jurí­dico");
        break;
    case GSMESAP::categoria:
        exibeTabelaCategoria();
        setWindowTitle("Categoria");
        break;
    case GSMESAP::sede:
        exibeTabelaSede();
        setWindowTitle("Sede");
        break;
    case GSMESAP::situacao:
        exibeTabelaSituacao();
        setWindowTitle("Situacão");
        break;
    }
}

GSMESAP::tabelasDoBancoDeDados Viewer::tabelaAtiva()
{
    return tabela;
}

void Viewer::exibeTabelaProfessor()
{
    if (!QSqlDatabase::database("default").isOpen())
        return;

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this, QSqlDatabase::database("default"));

    model->setTable("professor");
    model->setSort(1, Qt::AscendingOrder);
    model->setEditStrategy(QSqlTableModel::OnRowChange);

    model->setRelation(3, QSqlRelation("regime_juridico", "reg_jur_id", "regime_juridico"));
    model->setRelation(4, QSqlRelation("situacao", "situacao_id", "situacao"));
    model->setRelation(5, QSqlRelation("sede", "sede_id", "sede"));
    model->setRelation(6, QSqlRelation("categoria", "categoria_id", "categoria"));
    model->setRelation(7, QSqlRelation("disciplina", "disciplina_id", "disciplina"));

    if (!model->select())
    {
        QMessageBox::critical(this, "Erro ao selecionar tabela",
                              QString("editaTabelaProfessores(): %1").arg(model->lastError().text()));
        return;
    }

    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Nome do Professor"));
    model->setHeaderData(2, Qt::Horizontal, tr("DN"));
    model->setHeaderData(3, Qt::Horizontal, tr("Regime Jurí­dico"));
    model->setHeaderData(4, Qt::Horizontal, tr("Situação"));
    model->setHeaderData(5, Qt::Horizontal, tr("Sede"));
    model->setHeaderData(6, Qt::Horizontal, tr("Categoria"));
    model->setHeaderData(7, Qt::Horizontal, tr("Disciplinas"));

    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    setaModeloDaVisao(model, true);
}

void Viewer::exibeTabelaRegJuridico()
{
    if (!QSqlDatabase::database("default").isOpen())
        return;

    QSqlTableModel *model = new QSqlTableModel(this, QSqlDatabase::database("default"));

    model->setTable("regime_juridico");
    model->setEditStrategy(QSqlTableModel::OnRowChange);

    if(!model->select())
    {
        QMessageBox::critical(this, "Erro ao selecionar tabela",
                              QString("editaTabelaRegimeJuridico(): %1").arg(model->lastError().text()));
        return;
    }

    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, "Regime Jurídico");

    setaModeloDaVisao(model, false);
}

void Viewer::exibeTabelaCategoria()
{
    if (!QSqlDatabase::database("default").isOpen())
        return;

    QSqlTableModel *model = new QSqlTableModel(this, QSqlDatabase::database("default"));

    model->setTable("categoria");
    model->setEditStrategy(QSqlTableModel::OnRowChange);

    if(!model->select())
    {
        QMessageBox::critical(this, "Erro ao selecionar tabela",
                              QString("editaTabelaCategria(): %1").arg(model->lastError().text()));
        return;
    }

    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, "Categoria");

    setaModeloDaVisao(model, false);
}

void Viewer::exibeTabelaSede()
{
    if (!QSqlDatabase::database("default").isOpen())
        return;

    QSqlTableModel *model = new QSqlTableModel(this, QSqlDatabase::database("default"));

    model->setTable("sede");
    model->setEditStrategy(QSqlTableModel::OnRowChange);

    if(!model->select())
    {
        QMessageBox::critical(this, "Erro ao selecionar tabela",
                              QString("editaTabelaSde(): %1").arg(model->lastError().text()));
        return;
    }

    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, "Sede");

    setaModeloDaVisao(model, false);
}

void Viewer::exibeTabelaSituacao()
{
    if (!QSqlDatabase::database("default").isOpen())
        return;

    QSqlTableModel *model = new QSqlTableModel(this, QSqlDatabase::database("default"));

    model->setTable("situacao");
    model->setEditStrategy(QSqlTableModel::OnRowChange);

    if(!model->select())
    {
        QMessageBox::critical(this, "Erro ao selecionar tabela",
                              QString("editaTabelaSituacao(): %1").arg(model->lastError().text()));
        return;
    }

    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Situação"));

    setaModeloDaVisao(model, false);
}

void Viewer::setaModeloDaVisao(QAbstractItemModel *model, bool relationalDelegate)
{
    QVBoxLayout *v_layout = new QVBoxLayout;
    QLineEdit *campoDePesquisa = new QLineEdit;
    QTableView *tableView = new QTableView;

    v_layout->addWidget(campoDePesquisa);
    v_layout->addWidget(tableView);

    setLayout(v_layout);

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setDynamicSortFilter(true);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterKeyColumn(-1);

    // Filtro
    connect(campoDePesquisa, SIGNAL(textChanged(QString)),
            this, SLOT(filtraConteudo(QString)));

    tableView->setModel(proxyModel);
    tableView->resizeColumnsToContents();
    tableView->setSortingEnabled(true);
    tableView->sortByColumn(1, Qt::AscendingOrder);
    tableView->setCornerButtonEnabled(false);
    tableView->setAlternatingRowColors(true);

    if (relationalDelegate)
        tableView->setItemDelegate(new mySqlRelationalDelegate(tableView));

    campoDePesquisa->setFocus();
}

void Viewer::filtraConteudo(QString filtro)
{
    proxyModel->setFilterRegExp(QRegExp(filtro, Qt::CaseInsensitive,
                                        QRegExp::FixedString));
    proxyModel->setFilterKeyColumn(1);
}
