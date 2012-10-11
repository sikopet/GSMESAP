#include "dialogdocumentos.h"
#include "ui_dialogdocumentos.h"

DialogDocumentos::DialogDocumentos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDocumentos)
{
    ui->setupUi(this);

    connect(ui->pushButton_inserir, SIGNAL(clicked()), this,
            SLOT(insereDocumento()));

    // Populando ComboBox_doc_tipo
    modelTipoDoc = new QSqlQueryModel(this);
    modelTipoDoc->setQuery("SELECT doc_tipo_id, doc_tipo FROM documento_tipo", QSqlDatabase::database("default"));
    ui->comboBox_doc_tipo->setModel(modelTipoDoc);
    ui->comboBox_doc_tipo->setModelColumn(1);

    // Popula o tableView
    model = new QSqlQueryModel;
    model->setQuery("SELECT documento.documento_numero, documento.descricao,"
                    "documento_tipo.doc_tipo FROM public.documento, public.documento_tipo "
                    "WHERE documento_tipo.doc_tipo_id = documento.doc_tipo_id", QSqlDatabase::database("default"));
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->resizeColumnsToContents();

    model->setHeaderData(0, Qt::Horizontal, "Número");
    model->setHeaderData(1, Qt::Horizontal, "Descrição");
    model->setHeaderData(2, Qt::Horizontal, "Tipo do Documento");
}

void DialogDocumentos::insereDocumento()
{
    QString q;

    q = QString("INSERT INTO documento(doc_tipo_id, documento_numero, descricao) VALUES('%1', '%2', '%3')").
            arg(modelTipoDoc->record(ui->comboBox_doc_tipo->currentIndex()).value("doc_tipo_id").toString(),
                ui->lineEdit_doc_num->text(), ui->lineEdit_doc_descricao->text());

    QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("default"));
    if (query->exec(q))
        QMessageBox::information(this, "Dados inseridos com sucesso", "Os dados foram inseridos com sucesso na base de dados");
    else
        QMessageBox::critical(this, "Dados não inseridos", query->lastError().text());

    model->setQuery(model->query().lastQuery(), QSqlDatabase::database("default"));
}

DialogDocumentos::~DialogDocumentos()
{
    delete ui;
}
