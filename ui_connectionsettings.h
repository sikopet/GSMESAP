/********************************************************************************
** Form generated from reading UI file 'connectionsettings.ui'
**
** Created: Wed 22. Aug 00:02:16 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONSETTINGS_H
#define UI_CONNECTIONSETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectionSettings
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_1;
    QLineEdit *input_host;
    QLabel *label_2;
    QLineEdit *input_port;
    QLabel *label_5;
    QLineEdit *input_database;
    QLabel *label_3;
    QLineEdit *input_username;
    QLabel *label_4;
    QLineEdit *input_password;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *button_disconn;
    QPushButton *button_conn;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *button_clear;
    QPushButton *button_quit;
    QCheckBox *manter_conectado;

    void setupUi(QDialog *ConnectionSettings)
    {
        if (ConnectionSettings->objectName().isEmpty())
            ConnectionSettings->setObjectName(QString::fromUtf8("ConnectionSettings"));
        ConnectionSettings->resize(475, 244);
        formLayoutWidget = new QWidget(ConnectionSettings);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 10, 453, 221));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_1 = new QLabel(formLayoutWidget);
        label_1->setObjectName(QString::fromUtf8("label_1"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_1);

        input_host = new QLineEdit(formLayoutWidget);
        input_host->setObjectName(QString::fromUtf8("input_host"));

        formLayout->setWidget(0, QFormLayout::FieldRole, input_host);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        input_port = new QLineEdit(formLayoutWidget);
        input_port->setObjectName(QString::fromUtf8("input_port"));

        formLayout->setWidget(1, QFormLayout::FieldRole, input_port);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_5);

        input_database = new QLineEdit(formLayoutWidget);
        input_database->setObjectName(QString::fromUtf8("input_database"));

        formLayout->setWidget(2, QFormLayout::FieldRole, input_database);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        input_username = new QLineEdit(formLayoutWidget);
        input_username->setObjectName(QString::fromUtf8("input_username"));

        formLayout->setWidget(3, QFormLayout::FieldRole, input_username);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        input_password = new QLineEdit(formLayoutWidget);
        input_password->setObjectName(QString::fromUtf8("input_password"));
        input_password->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(4, QFormLayout::FieldRole, input_password);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        button_disconn = new QPushButton(formLayoutWidget);
        button_disconn->setObjectName(QString::fromUtf8("button_disconn"));
        button_disconn->setEnabled(false);

        horizontalLayout_5->addWidget(button_disconn);

        button_conn = new QPushButton(formLayoutWidget);
        button_conn->setObjectName(QString::fromUtf8("button_conn"));
        button_conn->setEnabled(false);

        horizontalLayout_5->addWidget(button_conn);


        formLayout->setLayout(5, QFormLayout::FieldRole, horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        button_clear = new QPushButton(formLayoutWidget);
        button_clear->setObjectName(QString::fromUtf8("button_clear"));
        button_clear->setEnabled(true);

        horizontalLayout_6->addWidget(button_clear);

        button_quit = new QPushButton(formLayoutWidget);
        button_quit->setObjectName(QString::fromUtf8("button_quit"));

        horizontalLayout_6->addWidget(button_quit);


        formLayout->setLayout(6, QFormLayout::FieldRole, horizontalLayout_6);

        manter_conectado = new QCheckBox(formLayoutWidget);
        manter_conectado->setObjectName(QString::fromUtf8("manter_conectado"));
        manter_conectado->setEnabled(false);

        formLayout->setWidget(7, QFormLayout::FieldRole, manter_conectado);

        QWidget::setTabOrder(input_port, input_database);
        QWidget::setTabOrder(input_database, input_username);
        QWidget::setTabOrder(input_username, input_password);
        QWidget::setTabOrder(input_password, button_conn);
        QWidget::setTabOrder(button_conn, button_disconn);
        QWidget::setTabOrder(button_disconn, button_clear);
        QWidget::setTabOrder(button_clear, button_quit);

        retranslateUi(ConnectionSettings);
        QObject::connect(button_quit, SIGNAL(released()), ConnectionSettings, SLOT(close()));

        QMetaObject::connectSlotsByName(ConnectionSettings);
    } // setupUi

    void retranslateUi(QDialog *ConnectionSettings)
    {
        ConnectionSettings->setWindowTitle(QApplication::translate("ConnectionSettings", "Configurar Conex\303\243o", 0, QApplication::UnicodeUTF8));
        label_1->setText(QApplication::translate("ConnectionSettings", "Host:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ConnectionSettings", "Porta:", 0, QApplication::UnicodeUTF8));
        input_port->setText(QString());
        label_5->setText(QApplication::translate("ConnectionSettings", "Database:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ConnectionSettings", "Username:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ConnectionSettings", "Senha:", 0, QApplication::UnicodeUTF8));
        button_disconn->setText(QApplication::translate("ConnectionSettings", "&Desconectar", 0, QApplication::UnicodeUTF8));
        button_conn->setText(QApplication::translate("ConnectionSettings", "Co&nectar", 0, QApplication::UnicodeUTF8));
        button_clear->setText(QApplication::translate("ConnectionSettings", "&Limpar", 0, QApplication::UnicodeUTF8));
        button_quit->setText(QApplication::translate("ConnectionSettings", "&Fechar", 0, QApplication::UnicodeUTF8));
        manter_conectado->setText(QApplication::translate("ConnectionSettings", "Mantenha-me conectado", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConnectionSettings: public Ui_ConnectionSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONSETTINGS_H
