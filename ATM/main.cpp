#include<QCoreApplication>
#include <QDebug>
#include <iostream>
#include "Card.h"
using namespace std;
int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);
	
	
	Card c1("0000000000000000", "0000", 0, true, 0);
	Card c2("0000000000000001", "0001", 0, true, 1);
	qDebug() << "Hello Atm";
	return a.exec();

}