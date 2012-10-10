#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QTableView>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>
#include <QtSql>

#include <QMessageBox>
#include <QVBoxLayout>
#include <QLineEdit>

#include <gsmesap_enums.h>
#include <mysqlrelationaldelegate.h>

class Viewer : public QWidget
{
    Q_OBJECT
public:
    explicit Viewer(QWidget *parent = 0);

    void setaTabelaAtiva(GSMESAP::tabelasDoBancoDeDados tb);
    GSMESAP::tabelasDoBancoDeDados tabelaAtiva();

private slots:
    void filtraConteudo(QString filtro);

private:
    void exibeTabelaProfessor();
    void exibeTabelaSemRelacao(QString nomeTabela, QStringList colunas);
    void setaModeloDaVisao(QAbstractItemModel *model, bool relationalDelegate);

    QSortFilterProxyModel *proxyModel;
    GSMESAP::tabelasDoBancoDeDados tabela;
};

#endif // VIEWER_H
