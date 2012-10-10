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
        break;
    case GSMESAP::regime_juridico:
        exibeTabelaSemRelacao("regime_juridico", QStringList() << "ID" << "Regime Jurídico");
        break;
    case GSMESAP::categoria:
        exibeTabelaSemRelacao("categoria", QStringList() << "ID" << "Categoria");
        break;
    case GSMESAP::sede:
        exibeTabelaSemRelacao("sede", QStringList() << "ID" << "Sede");
        break;
    case GSMESAP::situacao:
        exibeTabelaSemRelacao("situacao", QStringList() << "ID" << "Situação");
        break;
    case GSMESAP::disciplina:
        exibeTabelaSemRelacao("disciplina", QStringList() << "ID" << "Disciplina");
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

void Viewer::exibeTabelaSemRelacao(QString nomeTabela, QStringList colunas)
{
    if (!QSqlDatabase::database("default").isOpen())
        return;

    QSqlTableModel *model = new QSqlTableModel(this, QSqlDatabase::database("default"));

    model->setTable(nomeTabela);
    model->setEditStrategy(QSqlTableModel::OnRowChange);

    if(!model->select())
    {
        QMessageBox::critical(this, "Erro ao selecionar tabela",
                              QString("editaTabelaRegimeJuridico(): %1").arg(model->lastError().text()));
        return;
    }

    for (int i = 0; i < colunas.count(); ++i)
        model->setHeaderData(i, Qt::Horizontal, colunas.at(i));

    setaModeloDaVisao(model, false);
}


void Viewer::setaModeloDaVisao(QAbstractItemModel *model, bool relationalDelegate)
{
    QVBoxLayout *v_layout = new QVBoxLayout;
    QLineEdit *campoDePesquisa = new QLineEdit;
    campoDePesquisa->setPlaceholderText("Filtrar...");
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
