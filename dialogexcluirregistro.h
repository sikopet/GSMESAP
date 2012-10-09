#ifndef EXCLUIRREGISTRO_H
#define EXCLUIRREGISTRO_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>

#include "gsmesap_enums.h"

using namespace GSMESAP;

namespace Ui {
class DialogExcluirRegistro;
}

class DialogExcluirRegistro : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogExcluirRegistro(tabelasDoBancoDeDados tb, QWidget *parent = 0);
    ~DialogExcluirRegistro();
    
private:
    Ui::DialogExcluirRegistro *ui;
    tabelasDoBancoDeDados tabela;
    QStringList codParaExcluir;
    QSqlQueryModel *model;

private slots:
    void verificaCampo();
    void procuraRegistro();
    void itensSelecionados(const QItemSelection &, const QItemSelection &);
    void excluiItensSelecionados();

signals:
    void registroExcluido(tabelasDoBancoDeDados tb);
};

#endif // EXCLUIRREGISTRO_H
