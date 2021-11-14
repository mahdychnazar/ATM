#include<QCoreApplication>
#include <QDebug>
#include <iostream>
#include "Card.h"
#include "Bank.h"
using namespace std;
int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);
	

	Bank bank = Bank();
	//bank.addCard("1000000000000002", "1111", 10, true, 0);
	Card c;
	//qDebug() << bank.getCard("1000000000000002", "1111", c);
	//qDebug() << c.getId() + " " + c.getPin()+ " ";
	qDebug() << bank.isCard("1000000000000003");
	return a.exec();

}