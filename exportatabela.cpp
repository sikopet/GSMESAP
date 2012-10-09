#include "exportatabela.h"

ExportaTabela::ExportaTabela(QSqlQuery *q, QString output)
{
    query = q;
    query->setForwardOnly(true);
    outputfilename = output;
}

bool ExportaTabela::exporta()
{
    if (outputfilename.isEmpty())
        return false;

    QTextDocument *document = new QTextDocument;
    QTextDocumentWriter *writer = new QTextDocumentWriter(outputfilename);
    writer->setFormat("plaintext");
    QTextCodec *codec = QTextCodec::codecForName("ISO 8859-1");
    writer->setCodec(codec);

    QStringList csv;

    // Cabeçalho
    for (int i = 0; i < query->record().count(); ++i)
        csv << QString(query->record().fieldName(i)).append(";");

    // Conteúdo
    while(query->next())
    {
        csv << "\n";
        for (int i = 0; i < query->record().count(); ++i)
            csv << query->value(i).toString().append(";");
    }

    QTextCursor cursor(document);
    for (int i = 0; i < csv.count(); ++i)
        cursor.insertText(csv.at(i));

    if (!writer->write(document))
        return false;
    else
        return true;
}
