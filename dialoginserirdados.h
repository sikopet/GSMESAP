#ifndef DialogInserirDados_H
#define DialogInserirDados_H

#include <QtSql>
#include <QDialog>
#include <QMessageBox>

#include "gsmesap_enums.h"
#include "inserirdados.h"

using namespace GSMESAP;

namespace Ui {
class DialogInserirDados;
}

class DialogInserirDados : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogInserirDados(tabelasDoBancoDeDados tb, QWidget *parent = 0);
    ~DialogInserirDados();
    
private:
    Ui::DialogInserirDados *ui;
    QSqlQueryModel *model;
    tabelasDoBancoDeDados tabelaAtiva;
    QString geraConsulta();

private slots:
    void acaoDeInserirOsDados();
};

#endif // DialogInserirDados_H
