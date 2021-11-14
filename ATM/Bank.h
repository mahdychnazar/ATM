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
		accounts++;

        return  res;
	};

	bool addCard(const char* card_id, const char* pin, long sum, bool isActive, int user_id) {
		QSqlQuery a_query;
		QString str_insert = "INSERT INTO CARDS (card_id, pin, summ, isActive, user_id) "
			"VALUES (%1, '%2', %3, %4, %5);";
		QString str = str_insert.arg(card_id)
			.arg(pin)
			.arg(QString::number(sum))
			.arg(isActive)
			.arg(QString::number(user_id));
		bool res = a_query.exec(str);
		a_query.clear();
		cards++;
		return res;
	};
	
	bool doTransaction(const char* sender, const char* reciever, const int sum)
	{
		bool isOk = false;

		QSqlDatabase::database().transaction();
		QSqlQuery a_query;
		QString str_insert = "INSERT INTO TRANSACTIONS (sender, reciever, summ, dateTime, transaction_id) "
			"VALUES ('%1', '%2', %3, '%4', %5);";
		QString str = str_insert.arg(sender)
			.arg(reciever)
			.arg(sum)
			.arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
			.arg(transactions + 1);
		isOk = a_query.exec(str);
		QString str_from = "UPDATE CARDS SET summ = summ+%1 WHERE card_id = '%2'";
		 str = str_from.arg(-sum)
			.arg(sender);
		 isOk = isOk && a_query.exec(str);

		QString str_to = "UPDATE CARDS SET summ = summ+%1 WHERE card_id = '%2'";
		 str = str_to.arg(sum)
			.arg(reciever);
		 isOk = isOk && a_query.exec(str);
		 if(isOk)
		 {
			  QSqlDatabase::database().commit();
		 }
		 else
		 {
			 QSqlDatabase::database().rollback();
		 }
		 qDebug() << a_query.lastError();
		 transactions++;
		 return isOk;
	};	


	bool getCard(const char* id, const char* pin, Card& target) {
		QSqlQuery a_query;
		QString str_select = "SELECT * FROM CARDS WHERE card_id = '%1' AND pin = '%2';";
		QString str = str_select.arg(id)
			.arg(pin);
		bool isOk = a_query.exec(str);
		qDebug() << a_query.lastError();
		if (isOk && a_query.next())
		{
			QString cardId = a_query.value(0).toString();
			qDebug() << cardId << '\n';
			QString pin = a_query.value(1).toString();
			long sum = a_query.value(2).toInt();
			bool isActive = a_query.value(3).toBool();
			int userId = a_query.value(4).toInt();
			Card res = Card(cardId, pin, sum, isActive, userId);
			target = res;
			return true;
		}
		else
		{
			return false;
		}	
	};
	bool isCard(const char* id)
	{
		QSqlQuery a_query;
		QString str_select = "SELECT * FROM CARDS WHERE card_id = '%1';";
		QString str = str_select.arg(id);
		bool isOk = a_query.exec(str);
		isOk = isOk && a_query.next();
		return isOk;
	}


	bool updateSum(const char* id, int sum)
	{
		if (isCard(id))
		{
			QSqlQuery a_query;
			QString str_update = "UPDATE CARDS SET summ = summ+%1 WHERE card_id = '%2'";
			QString str = str_update.arg(sum)
				.arg(id);
			return a_query.exec(str);
		}
		else { return false; }
	}

	bool activateCard(const char* id, bool activate)
	{
		if (isCard(id))
		{
			QSqlQuery a_query;
			QString str_update = "UPDATE CARDS SET isActive = %1 WHERE card_id = '%2'";
			QString str = str_update.arg(activate)
			.arg(id);
			return a_query.exec(str);
		}
		else { return false; }
	}

};