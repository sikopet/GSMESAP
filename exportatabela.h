#ifndef EXPORTATABELA_H
#define EXPORTATABELA_H

#include <QtSql>
#include <QTextDocument>
#include <QTextDocumentWriter>
#include <QTextCursor>
#include <QStringList>
#include <QFileDialog>

class ExportaTabela
{
public:
    ExportaTabela(QSqlQuery *q, QString output);
    bool exporta();

private:
    QSqlQuery * query;
    QString outputfilename;
};

#endif // EXPORTATABELA_H
