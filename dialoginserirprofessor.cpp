#include "dialoginserirprofessor.h"
#include "ui_dialoginserirprofessor.h"

DialogInserirProfessor::DialogInserirProfessor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInserirProfessor)
{
    ui->setupUi(this);

    ui->buttom_inserir->setEnabled(false);

    connect(ui->buttom_inserir, SIGNAL(pressed()),
            this, SLOT(insereProfessor()));
    connect(ui->input_nome_prof, SIGNAL(textChanged(QString)),
            this, SLOT(habilitaBotaoInserir()));
    popularComboBox();
}

void DialogInserirProfessor::popularComboBox()
{
    ui->input_nome_prof->clear();
    ui->input_nome_prof->setFocus();
    ui->input_dn_prof->setDate(QDate::currentDate());

    model_cat = new QSqlQueryModel;
    model_cat->setQuery("SELECT * FROM  categoria", QSqlDatabase::database("default"));
    ui->combo_cat_prof->setModel(model_cat);
    ui->combo_cat_prof->setModelColumn(1);

    model_disc = new QSqlQueryModel;
    model_disc->setQuery("SELECT* FROM disciplina", QSqlDatabase::database("default"));
    ui->combo_disciplina->setModel(model_disc);
    ui->combo_disciplina->setModelColumn(1);

    model_reg_jur = new QSqlQueryModel;
    model_reg_jur->setQuery("SELECT * FROM regime_juridico", QSqlDatabase::database("default"));
    ui->combo_reg_jur_prof->setModel(model_reg_jur);
    ui->combo_reg_jur_prof->setModelColumn(1);

    model_sede = new QSqlQueryModel;
    model_sede->setQuery("SELECT * FROM sede", QSqlDatabase::database("default"));
    ui->combo_sede_prof->setModel(model_sede);
    ui->combo_sede_prof->setModelColumn(1);

    model_sit = new QSqlQueryModel;
    model_sit->setQuery("SELECT * FROM situacao", QSqlDatabase::database("default"));
    ui->combo_sit_prof->setModel(model_sit);
    ui->combo_sit_prof->setModelColumn(1);
}

void DialogInserirProfessor::habilitaBotaoInserir()
{
    if (verificaCampos())
        ui->buttom_inserir->setEnabled(true);
    else
        ui->buttom_inserir->setEnabled(false);
}

void DialogInserirProfessor::insereProfessor()
{
    InserirDados *insere = new InserirDados(ui->input_nome_prof->text(),
                                            ui->input_dn_prof->date(),
                                            model_cat->record(ui->combo_cat_prof->currentIndex()).value("categoria_id").toInt(),
                                            model_disc->record(ui->combo_disciplina->currentIndex()).value("disciplina_id").toInt(),
                                            model_reg_jur->record(ui->combo_reg_jur_prof->currentIndex()).value("reg_jur_id").toInt(),
                                            model_sede->record(ui->combo_sede_prof->currentIndex()).value("sede_id").toInt(),
                                            model_sit->record(ui->combo_sit_prof->currentIndex()).value("situacao_id").toInt());

    if (insere->dadosInseridos())
    {
        QMessageBox::information(this, "Confirmação", "Dados Inseridos com sucesso");
        popularComboBox();
        emit dadosInseridos();
    }
    else
        QMessageBox::critical(this, "Não foi possí­vel inserir", insere->ultimoErro().text(), QMessageBox::Cancel);
}

bool DialogInserirProfessor::verificaCampos()
{
    if (ui->input_nome_prof->text().isEmpty())
        return false;
    if (ui->input_dn_prof->text().isEmpty())
        return false;
    if (ui->combo_cat_prof->count() <= 0)
        return false;
    if (ui->combo_reg_jur_prof->count() <= 0)
        return false;
    if (ui->combo_sede_prof->count() <= 0)
        return false;
    if (ui->combo_sit_prof->count() <= 0)
        return false;
    return true;
}

DialogInserirProfessor::~DialogInserirProfessor()
{
    delete ui;
}
