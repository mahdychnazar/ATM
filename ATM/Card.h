#pragma once
#include <QtCore/qstring.h>

class Card {
private:

	QString id;
	QString pin;
	long  sum;
	bool isActive;
	int user;

public:
	Card() {};
	Card(const QString& id, const QString& pin, const long  sum, const bool is_active, const int user_id) :
		id(id), pin(pin),sum(sum),isActive(is_active),user(user_id)
	{};
	Card(const char* id, const char* pin, const long  sum, const bool is_active, const int user_id):
		id(QString(id)), pin(QString(pin)), sum(sum), isActive(is_active), user(user_id)
	{};
	Card(const Card& toCopy):
		id(toCopy.getId()), pin(toCopy.getPin()), sum(toCopy.getSum()), isActive(toCopy.getIsActive()),user(toCopy.getUser())
	{
			
	};
	~Card() {};

	QString getId() const { return id; };
	QString getPin() const { return pin; };
	long getSum() const { return sum; };
	bool getIsActive() const { return isActive; };
	int getUser() const { return user; };

	void setPin(QString newPin) { pin = newPin; };
	void setSum(long newSum) { sum = newSum; };
	void setIsActive(bool newIsActive) { isActive = newIsActive; };


};
