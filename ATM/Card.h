#pragma once
#include <QtCore/qstring.h>

class Card {
private:

	QString id;
	QString pin;
	long double sum;
	bool isActive;
	int user;

public:
	Card();
	Card(const QString& id, const QString& pin, const long double sum, const bool is_active, const int user_id) :
		id(id), pin(pin),sum(sum),isActive(is_active),user(user_id)
	{};
	Card(const char* id, const char* pin, const long double sum, const bool is_active, const int user_id):
		id(QString(id)), pin(QString(pin)), sum(sum), isActive(is_active), user(user_id)
	{};
	Card(const Card&);
	~Card() {};

	QString getId() const { return id; };
	QString getPin() const { return pin; };
	long double getSum() const { return sum; };
	bool getIsActive() const { return isActive; };
	int getUser() const { return user; };

	void setPin(QString newPin) { pin = newPin; };
	void setSum(long double newSum) { sum = newSum; };
	void setIsActive(bool newIsActive) { isActive = newIsActive; };

};
