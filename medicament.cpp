#include "medicament.h"
#include "mainwindow.h"

medicament::medicament()
{

}
medicament::medicament(int id,QString nom,int qtm ,QString dispo)
{
    this ->id =id;
    this ->nom =nom;
    this ->qtm =qtm;
    this ->dispo =dispo;


}
bool medicament::ajouter()
{QSqlQuery query;
    QString res = QString::number(id);

    //prend la requête en paramètre pour préparer son execution
    query.prepare("insert into MEDICAMENT(IDM, NOMM, QTEM, DISPOMED)" "values(:id, :nom, :qtm, :dispo)");
    //creation des variables liées
    query.bindValue(0,res);
    query.bindValue(1,nom);
    query.bindValue(2,qtm);
    query.bindValue(3,dispo);
    return query.exec(); //envoie la requete pour l'executer

}
QSqlQueryModel * medicament::afficher()
{
QSqlQueryModel* model= new QSqlQueryModel();
model->setQuery("SELECT * FROM MEDICAMENT");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom medicament "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("disponibilité"));
return model;
}
bool medicament::supprimer(int id)
{
    QSqlQuery query;

    query.prepare("Delete from MEDICAMENT where IDM= :id");
    query.bindValue(0,id);

    return query.exec();
}
bool medicament::modifier(int id,QString nom,int qtm ,QString dispo)
{
    QSqlQuery query;
    //prend la requête en paramètre pour préparer son execution
    query.prepare("update MEDICAMENT set  NOMM= :nom , QTEM= :qtm, DISPOMED= :dispo where IDM= :id");

    //creation des variables liées
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":qtm", qtm);
    query.bindValue(":dispo", dispo);
    return query.exec(); //envoie la requete pour l'executer
}
void medicament::rechercher(QTableView *table, QString nom)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from MEDICAMENT where regexp_like(NOMM,:nom);");
   query->bindValue(":nom",nom);

   if(nom==0)
   {
       query->prepare("select * from MEDICAMENT");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
