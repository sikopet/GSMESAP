#ifndef INSERIRDADOS_H
#define INSERIRDADOS_H

#include <QtSql>
#include <QStringList>
#include <QDate>

class InserirDados
{
public:
    InserirDados(QString nomeProfessor, QDate data, int categoria, int disciplinas, int reg_jur, int sede, int situacao);
    InserirDados(QString tabela, QString campo, QString dado);

    bool dadosInseridos();
    QSqlError ultimoErro();

private:
    bool ok;
    QSqlError erro;
};

#endif // INSERIRDADOS_H
