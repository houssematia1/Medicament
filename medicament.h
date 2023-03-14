#ifndef MEDICAMENT_H
#define MEDICAMENT_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include<QTableView>
class medicament
{
private:
 QString nom,dispo;
 int qtm,id;
public:
 medicament();
 medicament(int,QString,int,QString);


        //getters
        int getId(){return id;}
        QString getNom(){return nom;}
        int getQtm(){return qtm;}
        QString getDispo(){return dispo;}

        //setters
       void setIdh(int id){this->id=id;}
       void setNom(QString n){nom=n;}
       void setQtm(int q){this->qtm=q;}
       void setDispo(QString d){dispo=d;}

        //CRUD
        bool ajouter ();
        QSqlQueryModel* afficher();
        bool supprimer(int);
        bool modifier (int,QString,int,QString);
        //fonctionnalités avancés
        void rechercher(QTableView*, QString);


};

#endif // MEDICAMENT_H
