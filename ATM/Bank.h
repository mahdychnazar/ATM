#pragma once
#include<QtSql>


#include <QDateTime>
#include <QDebug>
#include "Card.h"

class Bank {
private:

	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

	int accounts = 0;
	int cards = 0;
	int transactions = 0;
	bool isOk;



public:

	Bank()
	{
		QSqlQuery a_query;
		db.setDatabaseName("db.db");
		db.open();

		isOk = a_query.exec("SELECT COUNT (*) FROM ACCOUNTS");
		a_query.next();
		accounts = a_query.value(0).toInt();
		isOk = a_query.exec("SELECT COUNT(*) FROM CARDS");
		a_query.next();
		cards = a_query.value(0).toInt();
		isOk = a_query.exec("SELECT COUNT(*) FROM TRANSACTIONS");
		a_query.next();
		transactions = a_query.value(0).toInt();
		a_query.finish();

		qDebug() << accounts << '\n';
		qDebug() << cards << '\n';
		qDebug() << transactions << '\n';

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
		a_query.clear();

        return  res;
	};

	bool addCard(const char* card_id, const char* pin, double sum, bool isActive, int user_id) {
		QSqlQuery a_query;
		QString str_insert = "INSERT INTO CARDS (card_id, pin, sum, isActive, user_id) "
			"VALUES (%1, '%2', %3, %4, %5);";
		QString str = str_insert.arg(card_id)
			.arg(pin)
			.arg(sum)
			.arg(isActive)
			.arg(user_id);
		bool res = a_query.exec(str);
		a_query.clear();
		return res;
	};
	
	bool doTransaction(const char* from, const char* to, const int sum,  const QString &dateTime)
	{
		QSqlQuery a_query;
		QString str_insert = "INSERT INTO TRANSACTIONS (from, to, sum, dateTime, transaction_id) "
			"VALUES (%1, %2, %3, %4, %5);";
		QString str = str_insert.arg(from)
			.arg(to)
			.arg(sum)
			.arg(dateTime)
			.arg(transactions + 1);
		bool isOk = a_query.exec(str);
		/*QString str_from = "UPDATE CARDS SET sum = sum+%1 WHERE card_id = '%2'";
		 str = str_from.arg(-sum)
			.arg(from);
		 isOk = isOk && a_query.exec(str);

		QString str_to = "UPDATE CARDS SET sum = sum+%1 WHERE card_id = '%2'";
		 str = str_from.arg(sum)
			.arg(to);
		 isOk = isOk && a_query.exec(str);*/
		 return isOk;
	};	

	Card findCard(const char* id) {
		QSqlQuery a_query;
		QString str_select = "SELECT * FROM CARDS WHERE card_id = '%1';";
		QString str = str_select.arg(id);
		bool isOk = a_query.exec(str);
		qDebug() << a_query.lastError();
		if (isOk)
		{
			a_query.next();
			QString cardId = a_query.value(0).toString();
			qDebug() << cardId << '\n';
			QString pin = a_query.value(1).toString();
			double sum = a_query.value(2).toInt();
			bool isActive = a_query.value(3).toBool();
			int userId = a_query.value(4).toInt();
			Card res = Card(cardId, pin, sum, isActive, userId);
			return res;
		}
		else
		{
			return Card();
		}
		

	};


};