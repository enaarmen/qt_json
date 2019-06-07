#include <QString>
#include <QtCore>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonValue>

#include <QDebug>

#include "jsonqtnotes.h"
#include "ui_jsonqtnotes.h"

jsonQtNotes::jsonQtNotes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jsonQtNotes)
{
    ui->setupUi(this);
}

jsonQtNotes::~jsonQtNotes()
{
    delete ui;
}

void jsonQtNotes::ConnectOrthoJsonByAllOtrhos(QString email, QString password)
{
    QJsonObject json;
    QNetworkRequest request(QUrl(QString(BASE_URL) + QString("/get_all_ortho")));
    QNetworkAccessManager *q_network_manager = new QNetworkAccessManager(this);
    QNetworkReply *reply;// = q_network_manager.get(request);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    reply = q_network_manager->get(request);
    //connect(manager, &QNetworkAccessManager::finished, this, &QNetworkReply::isFinished);
    //json.insert("email", email);
    //json.insert("password", password);
    //reply = q_network_manager->get(request);
    //reply = q_network_manager.post(request, QJsonDocument(json).toJson());
    while (!reply->isFinished())
        qApp->processEvents();
    QString response_data = reply->readAll();
    QJsonDocument json_document = QJsonDocument::fromJson(response_data.toUtf8());
    json = json_document.object();
    QJsonValue value = json.value(QString("password"));
    qDebug() << "valeur du password :" + value.toString();
    qDebug() << "reply readAll: " << reply->readAll();
    qDebug() << "response_data is:" << response_data;
    qDebug() << "Json got: " << json_document.toJson();
    ui->connection_get->setText(json_document.toJson());
    reply->deleteLater();
}

void jsonQtNotes::on_connection_clicked()
{
    if (!ui->email->find("email") && !ui->email->size().isEmpty()
            && !ui->password->find("password")
            && !ui->password->size().isEmpty()) {
        ConnectOrthoJsonByAllOtrhos(ui->email->toPlainText(), ui->password->toPlainText().toUtf8());
        qDebug() << QString("recuperation des infos email: ") + ui->email->toPlainText().toUtf8();
    } else
        qDebug() <<"bad connection";
}
