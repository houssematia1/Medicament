#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "medicament.h"
#include <QMessageBox>
#define file_ex "^[0-9]+$"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(MD.afficher());
    ui->lineEdit_idm->setValidator(new QRegExpValidator( QRegExp(file_ex),this));

}

MainWindow::~MainWindow()
{
    delete ui;

}



void MainWindow::on_pushButton_ajouter_clicked()
{
    int id=ui->lineEdit_idm->text().toInt();
        QString nom=ui->lineEdit_nom->text();
        int qtm=ui->spinBox_quantite->text().toInt();
        QString dispo=ui->comboBox->currentText();
        medicament m(id,nom,qtm,dispo);
        bool test=m.ajouter();
        if(test)
           {
               //REFRESH
               ui->tableView->setModel(m.afficher());
               ui->lineEdit_idm->clear();
               ui->lineEdit_nom->clear();
               ui->spinBox_quantite->clear();

               QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("Ajout effectué.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("Failed"),
                           QObject::tr("Ajout non effectué.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);

           }
}

void MainWindow::on_pushButton_supprimer_clicked()
{

        int id=ui->lineEdit_supprimer->text().toInt();
         bool test=MD.supprimer(id);
         if(test)
         {
             //REFRESH
              ui->tableView->setModel(MD.afficher());
              ui->lineEdit_supprimer->clear();

             QMessageBox::information(nullptr, QObject::tr("OK"),
                         QObject::tr("Suppression effectuée.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         }
         else
         {
             QMessageBox::critical(nullptr, QObject::tr("Failed"),
                         QObject::tr("Suppression non effectuée.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

         }
}

void MainWindow::on_pushButton_modifier_clicked()
{
    int id=ui->lineEdit_idm->text().toInt();
        QString nom=ui->lineEdit_nom->text();
        int qtm=ui->spinBox_quantite->text().toInt();
        QString dispo= ui->comboBox->currentText();
        medicament m(id,nom,qtm,dispo);
        bool test=m.modifier(id,nom,qtm,dispo);
            if(test)
            {
                //REFRESH
                ui->tableView->setModel(m.afficher());
                ui->lineEdit_idm->clear();
                ui->lineEdit_nom->clear();
   ui->spinBox_quantite->clear();
                QMessageBox::information(nullptr, QObject::tr("OK"),
                            QObject::tr("Modification effectuée.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Failed"),
                            QObject::tr("Modification non effectuée.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }

}

void MainWindow::on_pushButton_rechercher_clicked()
{
    ui->tableView->setModel(MD.afficher());
    QString nomh=ui->lineEdit_rechercher->text();
    MD.rechercher(ui->tableView,nomh);
}



void MainWindow::on_tableView_activated(const QModelIndex &index)
{

        QString val=ui->tableView->model()->data(index).toString();// recupere l'id selectionné
        QSqlQuery qry;
        qry.prepare("select * from MEDICAMENT where IDM='"+val+"'");
        if(qry.exec())
        {
         while(qry.next())
         {
          ui->lineEdit_idm->setText(qry.value(0).toString());
          ui->lineEdit_nom->setText(qry.value(1).toString());
          ui->spinBox_quantite->setValue(qry.value(2).toInt());
          ui->comboBox->setCurrentText(qry.value(3).toString());






         }
        }


}
