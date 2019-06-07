#ifndef JSONQTNOTES_H
#define JSONQTNOTES_H

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
    void ConnectOrthoJsonByAllOtrhos(QString email, QString password);

private slots:
    void on_connection_clicked();

private:
    Ui::jsonQtNotes *ui;

};

#endif // JSONQTNOTES_H
