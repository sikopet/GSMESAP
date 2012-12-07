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
    connect(ui->input_codigo, SIGNAL(returnPressed()),
            this, SLOT(procuraRegistro()));

    connect(ui->button_ir, SIGNAL(clicked()),
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
    ui->button_ir->setDisabled(ui->input_codigo->text().isEmpty());
}

void DialogExcluirRegistro::procuraRegistro()
{
    QString q;

    switch (tabela)
    {
    case regime_juridico:
        q = QString("SELECT reg_jur_id as Id, regime_juridico as \"Regime Jurídico\" FROM regime_juridico "
                "WHERE regime_juridico ILIKE '%%1%'").arg(ui->input_codigo->text());
        break;
    case categoria:
        q = QString("SELECT categoria_id as Id, categoria as Categoria FROM categoria "
                "WHERE categoria ILIKE '%%1%'").arg(ui->input_codigo->text());
        break;
    case sede:
        q = QString("SELECT sede_id as Id, sede as Sede FROM sede "
                "WHERE sede ILIKE '%%1%'").arg(ui->input_codigo->text());
        break;
    case situacao:
        q = QString("SELECT situacao_id as Id, situacao as \"Situação\" FROM situacao "
                "WHERE situacao ILIKE '%%1%'").arg(ui->input_codigo->text());
        break;
    case disciplina:
        q = QString("SELECT disciplina_id as Id, disciplina as Disciplina FROM disciplina "
                    "WHERE disciplina ILIKE '%%1%'").arg(ui->input_codigo->text());
        break;
    case professor:
        q = QString("SELECT professor_id as Id, nome as Nome, dn as DN FROM professor "
                "WHERE nome ILIKE '%%1%'").arg(ui->input_codigo->text());
        break;
    }

    model->setQuery(q, QSqlDatabase::database("default"));

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->resizeColumnsToContents();


    connect(ui->tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(itensSelecionados(const QItemSelection,const QItemSelection)));
}

void DialogExcluirRegistro::itensSelecionados(const QItemSelection selecionado, const QItemSelection naoSelecionado)
{
    if (selecionado.count() > 0)
    {
        QModelIndexList list = selecionado.indexes();
        QModelIndex index =  list.at(0);
        codParaExcluir << index.data(0).toString();
    }
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
        case disciplina:
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

        QMessageBox msgbox(this);
        msgbox.setText("Registros excluídos com sucesso.");
        msgbox.setInformativeText("Para mais detalhes, clique no botão abaixo.");
        msgbox.setDetailedText(codParaExcluir.takeLast());
        msgbox.setStandardButtons(QMessageBox::Ok);
        msgbox.exec();

        model->setQuery(model->query().lastQuery(), QSqlDatabase::database("default"));
        emit registroExcluido(tabela);
    }
    else
        QMessageBox::information(this, "Alguns erros ocorreram", QString("Veja a mensagem de log, o último erro foi: %1").
                                 arg(outputList.takeLast()));

    qDebug() << "void DialogExcluirRegistro::excluiItensSelecionados(): " << outputList;
}
