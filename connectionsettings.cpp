#include "connectionsettings.h"
#include "ui_connectionsettings.h"

ConnectionSettings::ConnectionSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionSettings)
{
    ui->setupUi(this);

    ui->button_clear->setEnabled(verificaCamposSujos());
    ui->manter_conectado->setEnabled(verificaCamposPreenchidos());

    if (QSqlDatabase::database("default").isOpen())
    {
        ui->button_conn->setEnabled(false);
        ui->button_disconn->setEnabled(true);
    }
    else
    {
        ui->button_conn->setEnabled(verificaCamposPreenchidos());
        ui->button_disconn->setEnabled(false);

    }

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

    // Preenche os input_texts com algum conteudo salvo anteriormente
    ui->input_host->setText(settings->value("Host").toString());
    ui->input_port->setText(settings->value("Port").toString());
    ui->input_database->setText(settings->value("Database").toString());
    ui->input_username->setText(settings->value("Username").toString());
    ui->input_password->setText(settings->value("Password").toString());
    ui->manter_conectado->setChecked(settings->value("Conectar").toBool());

    connect(ui->input_host, SIGNAL(textChanged(QString)), // Host
            this, SLOT(tentaHabilitarBotaoConectar()));
    connect(ui->input_host, SIGNAL(textChanged(QString)), // Host
            this, SLOT(tentaHabilitarBotaoLimpar()));
    connect(ui->input_port, SIGNAL(textChanged(QString)), // Porta
            this, SLOT(tentaHabilitarBotaoConectar()));
    connect(ui->input_port, SIGNAL(textChanged(QString)), // Porta
            this, SLOT(tentaHabilitarBotaoLimpar()));
    connect(ui->input_database, SIGNAL(textChanged(QString)), // Base de dados
            this, SLOT(tentaHabilitarBotaoConectar()));
    connect(ui->input_database, SIGNAL(textChanged(QString)), // Base de dados
            this, SLOT(tentaHabilitarBotaoLimpar()));
    connect(ui->input_username, SIGNAL(textChanged(QString)), // Nome de usuário
            this, SLOT(tentaHabilitarBotaoConectar()));
    connect(ui->input_username, SIGNAL(textChanged(QString)), // Nome de usuário
            this, SLOT(tentaHabilitarBotaoLimpar()));
    connect(ui->input_password, SIGNAL(textChanged(QString)), // Senha
            this, SLOT(tentaHabilitarBotaoConectar()));
    connect(ui->input_password, SIGNAL(textChanged(QString)), // Senha
            this, SLOT(tentaHabilitarBotaoLimpar()));

    connect(ui->button_conn, SIGNAL(released()), this, // Botão conectar pressionado
            SLOT(buttonConnectPressed()));
    connect(ui->button_disconn, SIGNAL(released()), this, // Botão desconectar pressionado
            SLOT(buttonDisconnectPressed()));
    connect(ui->button_clear, SIGNAL(released()), this, // Botão limpar pressionado
            SLOT(buttonClearPressed()));
    connect(ui->manter_conectado, SIGNAL(toggled(bool)), // Manter Conectado
            this, SLOT(manterConectado(bool)));
}

ConnectionSettings::~ConnectionSettings()
{
    delete ui;
}

bool ConnectionSettings::verificaCamposPreenchidos()
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

bool ConnectionSettings::verificaCamposSujos()
{
    if (!ui->input_host->text().isEmpty())
        return true;
    if (!ui->input_port->text().isEmpty())
        return true;
    if (!ui->input_database->text().isEmpty())
        return true;
    if (!ui->input_username->text().isEmpty())
        return true;
    if (!ui->input_password->text().isEmpty())
        return true;

    return false;
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

void ConnectionSettings::saveDbName(QString text)
{
    settings->setValue("Database", text);
}

void ConnectionSettings::savePassword(QString text)
{
    settings->setValue("Password", text);
}

void ConnectionSettings::manterConectado(bool value)
{
    settings->setValue("Conectar", value);
}

void ConnectionSettings::tentaHabilitarBotaoConectar()
{
    ui->button_conn->setEnabled(verificaCamposPreenchidos());
}

void ConnectionSettings::tentaHabilitarBotaoLimpar()
{
    ui->button_clear->setEnabled(verificaCamposSujos());
}

void ConnectionSettings::buttonConnectPressed()
{
    if (tentaConectar())
    {
        emit conectadoABaseDeDados();
        ui->button_conn->setEnabled(false); // Desabilita botão conectar
        ui->button_disconn->setEnabled(true); // Habilita botao Desconectar
        ui->manter_conectado->setEnabled(true); // Habilita botao Manter Conectado
    }
}

void ConnectionSettings::buttonDisconnectPressed()
{
    QSqlDatabase::database("default").close();
    QSqlDatabase::removeDatabase("default");
    emit desconectadoDaBaseDeDados();

    ui->button_disconn->setEnabled(false);
    ui->button_conn->setEnabled(true);
    ui->manter_conectado->setEnabled(false);
    ui->manter_conectado->setChecked(false);
}

void ConnectionSettings::buttonClearPressed()
{
    buttonDisconnectPressed();

    ui->input_host->clear();
    ui->input_port->clear();
    ui->input_username->clear();
    ui->input_password->clear();
    ui->input_database->clear();

    settings->clear();
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
