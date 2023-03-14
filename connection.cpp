#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("TEST");
db.setUserName("system");
db.setPassword("houssem123");

if (db.open())
test=true;





    return  test;
}
