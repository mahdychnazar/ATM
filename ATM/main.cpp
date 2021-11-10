#include<QCoreApplication>
#include <QDebug>
#include <iostream>
#include "Card.h"
#include "Bank.h"
using namespace std;
int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);
	
	
	Card c1("0000000000000000", "0000", 0, true, 0);
	Card c2("0000000000000001", "0001", 0, true, 1);

	Bank bank = Bank();
	Card c3 = bank.findCard("1000000000000002");
	
	qDebug()<<	bank.doTransaction("1000000000000002", "1000000000000003", 50, QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")) << '\n';
	//qDebug() << c3.getId();
	//qDebug() << bank.addAccount("Nazar") << '\n';
	//qDebug() << bank.addCard("1000000000000003", "0000", 0, true, 0) << '\n';
	//qDebug() << "Hello Atm";
	return a.exec();

}