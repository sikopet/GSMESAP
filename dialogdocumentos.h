#ifndef DIALOGDOCUMENTOS_H
#define DIALOGDOCUMENTOS_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>
#include <QDebug>

namespace Ui {
class DialogDocumentos;
}

class DialogDocumentos : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogDocumentos(QWidget *parent = 0);
    ~DialogDocumentos();

private slots:
    void insereDocumento();
    
private:
    Ui::DialogDocumentos *ui;
    QSqlQueryModel *model;
    QSqlQueryModel *modelTipoDoc;
};

#endif // DIALOGDOCUMENTOS_H
