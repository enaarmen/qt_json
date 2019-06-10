#include <QString>
#include <QtCore>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QDebug>

#include "jsonqtnotes.h"
#include "ui_jsonqtnotes.h"

jsonQtNotes::jsonQtNotes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jsonQtNotes), id(NULL), email(NULL)
{
    ui->setupUi(this);
}

jsonQtNotes::~jsonQtNotes()
{
    delete ui;
}

bool jsonQtNotes::ConnectOrthoJsonByAllOtrhos(QString email, QString password)
{
    //QJsonObject json;
    if (this->id && this->email)
        return (false);
    QNetworkRequest request(QUrl(QString(BASE_URL) + QString("/get_all_ortho")));
    QNetworkAccessManager *q_network_manager = new QNetworkAccessManager(this);
    QNetworkReply *reply;// = q_network_manager.get(request);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    reply = q_network_manager->get(request);

    while (!reply->isFinished())
        qApp->processEvents();
    QString response_data = reply->readAll();
    QJsonDocument json_document = QJsonDocument::fromJson(response_data.toUtf8());

    //qDebug() << "is empty:" << json_document[0]["_id"].toString();

    //ui->connection_get->setText(json_document.toJson());

    if (CheckLogin(json_document, email, password)) {
        qDebug() << "got:" << email << "connected";
        return (true);
    } else
        qDebug() << "bad connection";
    return (false);
    //reply->deleteLater();
}

bool jsonQtNotes::PrintPatients()
{
    if (this->id && this->email) {
        QNetworkRequest request(QUrl(QString(BASE_URL) + QString("/get_patient_by_ortho/") + *this->id));
        QNetworkAccessManager *q_network_manager = new QNetworkAccessManager(this);
        QNetworkReply *reply;// = q_network_manager.get(request);

        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        reply = q_network_manager->get(request);
        while (!reply->isFinished())
            qApp->processEvents();
        QString response_data = reply->readAll();
        QJsonDocument json_document = QJsonDocument::fromJson(response_data.toUtf8());
        ui->connection_get->setText(json_document.toJson());
        return (true);
    } else
        ui->connection_get->setText("il n'y a pas de patients.");
    return (false);
}

void jsonQtNotes::on_connection_clicked()
{
    qDebug() << "recuperation des infos email: " << ui->email->toPlainText() << "et password:" << ui->password->toPlainText();
    if (ConnectOrthoJsonByAllOtrhos(ui->email->toPlainText(), ui->password->toPlainText()))
        PrintPatients();
}

bool jsonQtNotes::CheckLogin(QJsonDocument & json_document, QString & email, QString & password)
{
    if (json_document.array().begin() == json_document.array().end())
        return (false);
    for (auto it = json_document.array().begin(); it != json_document.array().end(); ++it) {
        qDebug() << "iterateur:" << (*it);
        QJsonObject json = (*it).toObject();
        if (!json.value("email").toString().compare(email) &&
                !json.value("password").toString().compare(password)) {
            this->id = new QString(json.value("_id").toString());
            this->email = new QString(json.value("email").toString());
            qDebug() << "dans le if";
            return (true);
        } else
            qDebug() << "iterator:" << (*it).toObject() << "doesn't match";
    }
    return(false);
}

void jsonQtNotes::on_deconnection_clicked()
{
    qDebug() << "deconnection.";
    delete this->id;
    delete this->email;
    this->id = NULL;
    this->email = NULL;
}
