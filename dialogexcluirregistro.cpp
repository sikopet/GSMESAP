#include "dialogexcluirregistro.h"
#include "ui_dialogexcluirregistro.h"

DialogExcluirRegistro::DialogExcluirRegistro(tabelasDoBancoDeDados tb, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogExcluirRegistro)
{
    ui->setupUi(this);

    tabela = tb;

    model = new QSqlQueryModel(this);

    connect(ui->input_codigo, SIGNAL(textChanged(QString)),
            this, SLOT(verificaCampo()));
    connect(ui->button_ir, SIGNAL(clicked()),
            this, SLOT(procuraRegistro()));
    connect(ui->input_codigo, SIGNAL(returnPressed()),
            this, SLOT(procuraRegistro()));
    connect(ui->button_excluir, SIGNAL(released()),
            this, SLOT(excluiItensSelecionados()));
}

DialogExcluirRegistro::~DialogExcluirRegistro()
{
    delete ui;
}

void DialogExcluirRegistro::verificaCampo()
{
    if (ui->input_codigo->text().isEmpty())
        ui->button_ir->setEnabled(false);
    else
        ui->button_ir->setEnabled(true);
}

void DialogExcluirRegistro::procuraRegistro()
{
    QString q;

    switch (tabela)
    {
    case regime_juridico:
        q = QString("SELECT reg_jur_id as Id, regime_juridico as \"Regime Jurídico\" FROM regime_juridico "
                "WHERE regime_juridico like '%%1%'").arg(ui->input_codigo->text());
        break;
    case categoria:
        q = QString("SELECT categoria_id as Id, categoria as Categoria FROM categoria "
                "WHERE categoria like '%%1%'").arg(ui->input_codigo->text());
        break;
    case sede:
        q = QString("SELECT sede_id as Id, sede as Sede FROM sede "
                "WHERE sede like '%%1%'").arg(ui->input_codigo->text());
        break;
    case situacao:
        q = QString("SELECT situacao_id as Id, situacao as Situação FROM situacao "
                "WHERE situacao like '%%1%'").arg(ui->input_codigo->text());
        break;
    case disciplinas:
        q = QString("SELECT disciplina_id as Id, disciplina as Disciplina FROM disciplina "
                    "WHERE disciplina LIKE '%%1%'").arg(ui->input_codigo->text());
        break;
    case professor:
        q = QString("SELECT professor_id as Id, nome as Nome, dn as DN FROM professor "
                "WHERE nome like '%%1%'").arg(ui->input_codigo->text());
        break;
    }

    model->setQuery(q, QSqlDatabase::database("default"));

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->resizeColumnsToContents();


    connect(ui->tableView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(itensSelecionados(QItemSelection,QItemSelection)));
}

void DialogExcluirRegistro::itensSelecionados(const QItemSelection &, const QItemSelection &)
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();

    codParaExcluir.clear();

    for (int i = 0; i < indexes.count(); ++i)
        if (indexes.at(i).data(0).type() == QVariant::Int)
            codParaExcluir << indexes.at(i).data(0).toString();

    ui->button_excluir->setEnabled(true);
}

void DialogExcluirRegistro::excluiItensSelecionados()
{
    QStringList outputList;
    outputList.clear();

    QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("default"));

    for (int i = 0; i < codParaExcluir.count(); ++i)
    {
        switch(tabela)
        {
        case regime_juridico:
            if (!query->exec(QString("DELETE FROM regime_juridico WHERE reg_jur_id='%1'").arg(codParaExcluir.at(i))))
                outputList << "Regime Jurídico:" << query->lastError().text();
            break;
        case categoria:
            if (!query->exec(QString("DELETE FROM categoria WHERE categoria_id='%1'").arg(codParaExcluir.at(i))))
                outputList << "Categoria: " << query->lastError().text();
            break;
        case sede:
            if (!query->exec(QString("DELETE FROM sede WHERE sede_id='%1'").arg(codParaExcluir.at(i))))
                outputList << "Sede: " << query->lastError().text();
            break;
        case situacao:
            if (!query->exec(QString("DELETE FROM situacao WHERE situacao_id='%1'").arg(codParaExcluir.at(i))))
                outputList << "Situação: "  << query->lastError().text();
            break;
        case disciplinas:
            if (!query->exec(QString("DELETE FROM disciplina WHERE disciplina_id='%1'").arg(codParaExcluir.at(i))))
                outputList << "Disciplias: " << query->lastError().text();
            break;
        case professor:
            if (!query->exec(QString("DELETE FROM professor WHERE professor_id='%1'").arg(codParaExcluir.at(i))))
                outputList << "Professor: " << query->lastError().text();
            break;
        }
    }

    if (outputList.isEmpty())
    {
        QMessageBox::information(this, "Registro (s) Deletado (s) com Sucesso",
                                 "O (s) registro (s) selecionado (s) foi (ram) apagado (s) do banco de dados",
                                 QMessageBox::Ok);
        model->setQuery(model->query().lastQuery(), QSqlDatabase::database("default"));
        emit registroExcluido(tabela);
    }
    else
        QMessageBox::information(this, "Alguns erros ocorreram", QString("Veja a mensagem de log, o último erro foi: %1").
                                 arg(outputList.takeLast()));

    qDebug() << "void DialogExcluirRegistro::excluiItensSelecionados(): " << outputList;
}
