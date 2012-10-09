#ifndef CONNECTIONSETTINGS_H
#define CONNECTIONSETTINGS_H

#include <QDialog>
#include <QDebug>
#include <QSettings>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
    class ConnectionSettings;
}

/**
 * @brief The ConnectionSettings class
 */
class ConnectionSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionSettings(QWidget *parent = 0);
    ~ConnectionSettings();
    bool tentaConectar();

private slots:
    void saveHost(const QString text);
    void savePort(const QString text);
    void saveUsername(const QString text);
    void savePassword(const QString text);
    void saveDbName(const QString text);
    void buttonConnectPressed();
    void buttonDisconnectPressed();
    void buttonClearPressed();
    void habilitaBotaoConectar();
    void manterConectado(bool value);

signals:
    void conectadoABaseDeDados();
    void desconectadoDaBaseDeDados();
    
private:
    Ui::ConnectionSettings *ui;
    QSettings *settings;
    bool verificaCampos();
};

#endif // CONNECTIONSETTINGS_H
