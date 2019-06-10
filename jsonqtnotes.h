#ifndef JSONQTNOTES_H
#define JSONQTNOTES_H

#include <QJsonDocument>
#include <QString>
#include <QtCore>
#include <QWidget>

#define BASE_URL "http://localhost:8000"

namespace Ui {
class jsonQtNotes;
}

class jsonQtNotes : public QWidget
{
    Q_OBJECT

public:
    explicit jsonQtNotes(QWidget *parent = nullptr);
    ~jsonQtNotes();
    bool ConnectOrthoJsonByAllOtrhos(QString email, QString password); //deprecated before email
    bool CheckLogin(QJsonDocument & json, QString & email, QString & password);
    bool PrintPatients();

private slots:
    void on_connection_clicked();

    void on_deconnection_clicked();

private:
    Ui::jsonQtNotes *ui;
    QString         *id;
    QString         *email;
};

#endif // JSONQTNOTES_H
