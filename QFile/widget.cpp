#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>
#include <QDataStream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonread_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                         "open", "../", "TXT(*.txt)");

    if(path.isEmpty() == false)
    {
        QFile file(path);

        //openfile
        bool isOK = file.open(QIODevice::ReadOnly);
        if(isOK == true)
        {
            //read
            QByteArray array = file.readAll();

            //put in textedit
            ui->textEdit->setPlainText(array);

            //close file
            file.close();
        }
        QFileInfo info(path);
        qDebug() << "name: " << info.fileName();
        qDebug() << "suffix: " << info.suffix();
        qDebug() << "size: " << info.size();
        qDebug() << "created:" << info.created().toString("yyyy-MM-dd hh:mm:ss");
    }
}


void Widget::on_buttonwrite_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "save", "../", "TXT(*.txt)");

    if(path.isEmpty() == false)
    {
        QFile file(path);

        file.setFileName(path);

        //openfile
        bool isOK = file.open(QIODevice::WriteOnly);
        if(isOK == true)
        {
            //get content
            QString str = ui->textEdit->toPlainText();

            //write
            //QString -> QByteArray
            file.write(str.toUtf8());

            //close file
            file.close();
        }
    }
}

