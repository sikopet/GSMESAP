#include "inserirdados.h"

InserirDados::InserirDados(QString nomeProfessor, QDate data, int categoria, int disciplinas, int reg_jur, int sede, int situacao)
{
    QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("default"));

    query->prepare("INSERT INTO professor (nome, dn, reg_jur_id, situacao_id, "
                   "sede_id, categoria_id, disciplina_id) VALUES(?, ?, ?, ?, ?, ?, ?)");

    query->addBindValue(nomeProfessor.toUpper());
    query->addBindValue(data.toString("yyyy-MM-dd"));
    query->addBindValue(reg_jur);
    query->addBindValue(situacao);
    query->addBindValue(sede);
    query->addBindValue(categoria);
    query->addBindValue(disciplinas);

    if (query->exec())
        ok = true;
    else
    {
        erro = query->lastError();
        ok = false;
    }
}

InserirDados::InserirDados(QString tabela, QString campo, QString dado)
{
    QString q = QString("INSERT INTO %1(%2) VALUES(\'%3\')").arg(tabela, campo, dado.toUpper());
    QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("default"));
    if (query->exec(q))
        ok = true;
    else
    {
        ok = false;
        erro = query->lastError();
    }
}

bool InserirDados::dadosInseridos()
{
    if (ok)
        return true;
    else
        return false;
}

QSqlError InserirDados::ultimoErro()
{
    return erro;
}
