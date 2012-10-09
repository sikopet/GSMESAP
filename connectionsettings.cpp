#include "connectionsettings.h"
#include "ui_connectionsettings.h"

ConnectionSettings::ConnectionSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionSettings)
{
    ui->setupUi(this);

    settings = new QSettings;

    // Conecta os Slots para salvar o conteudo dos input_text
    connect(ui->input_host, SIGNAL(textChanged(QString)),
            this, SLOT(saveHost(QString)));
    connect(ui->input_port, SIGNAL(textChanged(QString)),
            this, SLOT(savePort(QString)));
    connect(ui->input_database, SIGNAL(textChanged(QString)),
            this, SLOT(saveDbName(QString)));
    connect(ui->input_username, SIGNAL(textChanged(QString)),
            this, SLOT(saveUsername(QString)));
    connect(ui->input_password, SIGNAL(textChanged(QString)),
            this, SLOT(savePassword(QString)));
    connect(ui->manter_conectado, SIGNAL(toggled(bool)),
            this, SLOT(manterConectado(bool)));

    // Seta os input_texts com algum conteudo salvo anteriormente
    ui->input_host->setText(settings->value("Host").toString());
    ui->input_port->setText(settings->value("Port").toString());
    ui->input_database->setText(settings->value("Database").toString());
    ui->input_username->setText(settings->value("Username").toString());
    ui->input_password->setText(settings->value("Password").toString());
    ui->manter_conectado->setChecked(settings->value("Conectar").toBool());

    // Conectar e Desconectar a base de dados
    connect(ui->button_conn, SIGNAL(released()), this,
            SLOT(buttonConnectPressed()));
    connect(ui->button_disconn, SIGNAL(released()), this,
            SLOT(buttonDisconnectPressed()));
    connect(ui->button_clear, SIGNAL(released()), this,
            SLOT(buttonClearPressed()));

    connect(ui->input_host, SIGNAL(textChanged(QString)),
            this, SLOT(habilitaBotaoConectar()));
    connect(ui->input_port, SIGNAL(textChanged(QString)),
            this, SLOT(habilitaBotaoConectar()));
    connect(ui->input_database, SIGNAL(textChanged(QString)),
            this, SLOT(habilitaBotaoConectar()));
    connect(ui->input_username, SIGNAL(textChanged(QString)),
            this, SLOT(habilitaBotaoConectar()));
    connect(ui->input_password, SIGNAL(textChanged(QString)),
            this, SLOT(habilitaBotaoConectar()));

    if (verificaCampos())
        if (QSqlDatabase::database("default").isOpen())
        {
            ui->button_disconn->setEnabled(true);
            ui->manter_conectado->setEnabled(true);
        }
        else
            ui->button_conn->setEnabled(true);
}

ConnectionSettings::~ConnectionSettings()
{
    delete ui;
}

void ConnectionSettings::saveHost(QString text)
{
    settings->setValue("Host", text);
}

void ConnectionSettings::savePort(QString text)
{
    settings->setValue("Port", text);
}

void ConnectionSettings::saveUsername(QString text)
{
    settings->setValue("Username", text);
}

void ConnectionSettings::savePassword(QString text)
{
    settings->setValue("Password", text);
}

void ConnectionSettings::saveDbName(QString text)
{
    settings->setValue("Database", text);
}

void ConnectionSettings::manterConectado(bool value)
{
    settings->setValue("Conectar", value);
}

void ConnectionSettings::habilitaBotaoConectar()
{
    if (verificaCampos())
        ui->button_conn->setEnabled(true);
    else
        ui->button_conn->setEnabled(false);
}

void ConnectionSettings::buttonConnectPressed()
{
    ui->button_conn->setEnabled(false);
    if (tentaConectar())
    {
        emit conectadoABaseDeDados();
        ui->button_disconn->setEnabled(true); // Habilita botao Desconectar
        ui->manter_conectado->setEnabled(true); // Habilita botao Manter Conectado
    }
    else
        ui->button_conn->setEnabled(true); // Habilita botao Conectar
}

void ConnectionSettings::buttonDisconnectPressed()
{
    QSqlDatabase::database("default").close();
    QSqlDatabase::removeDatabase("default");
    emit desconectadoDaBaseDeDados();

    ui->button_disconn->setEnabled(false);
    ui->button_conn->setEnabled(true);
    ui->manter_conectado->setChecked(false);
    ui->manter_conectado->setEnabled(false);
}

void ConnectionSettings::buttonClearPressed()
{
    buttonDisconnectPressed();

    settings->clear();

    ui->input_host->clear();
    ui->input_port->clear();
    ui->input_username->clear();
    ui->input_password->clear();
    ui->input_database->clear();
}

bool ConnectionSettings::verificaCampos()
{
    if (ui->input_host->text().isEmpty())
        return false;
    if (ui->input_port->text().isEmpty())
        return false;
    if (ui->input_database->text().isEmpty())
        return false;
    if (ui->input_username->text().isEmpty())
        return false;
    if (ui->input_password->text().isEmpty())
        return false;

        return true;
}

bool ConnectionSettings::tentaConectar()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "default");

    db.setHostName(settings->value("Host").toString());
    db.setPort(settings->value("Port").toInt());
    db.setDatabaseName(settings->value("Database").toString());
    db.setUserName(settings->value("Username").toString());
    db.setPassword(settings->value("Password").toString());

    if (db.open())
        return true;

    QMessageBox::information(this, "Erro na conexão", db.lastError().text());

    return false;
}
