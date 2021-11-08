#pragma once


#include"Card.h"
class Transaction {
private:
	QString from;
	QString to;
	long double sum;
	QString dateTime;


public:
	Transaction() {};
	Transaction(const QString& from, const QString& to, const long double sum, const QString& dateTime) :
		from(from), to(to), sum(sum), dateTime(dateTime)
	{};
	Transaction(const char* from, const char* to, const long double sum, const char* dateTime) :
		from(QString(from)), to(QString(to)), sum(sum), dateTime(QString(dateTime))
	{};
	~Transaction() {};

};