#ifndef INSERIRPROFESSOR_H
#define INSERIRPROFESSOR_H

#include <QWidget>
#include <QtSql>
#include <QStringList>
#include <QMessageBox>

#include <inserirdados.h>

namespace Ui {
class DialogInserirProfessor;
}

class DialogInserirProfessor : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogInserirProfessor(QWidget *parent = 0);
    ~DialogInserirProfessor();
    
private:
    Ui::DialogInserirProfessor *ui;

    QSqlQueryModel *model_sit;
    QSqlQueryModel *model_sede;
    QSqlQueryModel *model_cat;
    QSqlQueryModel *model_reg_jur;
    QSqlQueryModel *model_disc;
    void popularComboBox();
    bool verificaCampos();

private slots:
    void insereProfessor();
    void habilitaBotaoInserir();

signals:
    void dadosInseridos();
};

#endif // INSERIRPROFESSOR_H
