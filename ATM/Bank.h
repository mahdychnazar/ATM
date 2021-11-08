#pragma once
#include<QtSql>

class Bank {
private:

	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

	int accounts = 0;
	int cards = 0;



public:

	Bank()
	{
		db.setDatabaseName("db.db");
		db.open();
	}

	bool addAccount(const char* name)
	{
	   QSqlQuery a_query;
        QString str_insert = "INSERT INTO ACCOUNTS (account_id, Name) "
            "VALUES (%1, '%2');";
        QString   str = str_insert.arg(QString::number(accounts + 1))
            .arg(name);
        bool res = a_query.exec(str);
       
        qDebug() << a_query.lastError();

        return  res;
	};

	bool addCard();
	
	bool doTransactions();

};