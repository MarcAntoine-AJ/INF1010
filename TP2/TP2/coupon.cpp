/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "coupon.h"
 //Constructeur par défaut
Coupon::Coupon() :
	code_(""),
	rabais_(0),
	cout_(0)
{
}
//Constructeur par paramètres
Coupon::Coupon(const string& code, double rabais, int cout) :
	code_(code),
	rabais_(rabais),
	cout_(cout)
{
}
//Destructeur
Coupon::~Coupon()
{
}
//Getters
string Coupon::getCode() const
{
	return code_;
}

double Coupon::getRabais() const
{
	return rabais_;
}

int Coupon::getCout() const
{
	return cout_;
}
//Setters
void Coupon::setCode(const string& code)
{
	code_ = code;
}

void Coupon::setRabais(double rabais)
{
	rabais_ = rabais;
}

void Coupon::setCout(int cout)
{
	cout_ = cout;
}

// TODO: Remplacer cette methode par l'operateur <<
//Surcharge de l'opérateur >
bool Coupon :: operator>(const Coupon& coupon) const
{
	if (rabais_ > coupon.rabais_)
	{
		return true;
	}
	else {
		return false;
	}
}
//Surcharge de l'opérateur <
bool Coupon :: operator<(const Coupon& coupon) const
{
	if (rabais_ < coupon.rabais_)
	{
		return true;
	}
	else {
		return false;
	}
}

//Surcharge de l'opérateur << pour afficher infos
ostream& operator<< (ostream& os, const Coupon& coupon)
{
	return os << "\t\t- Coupon " << coupon.code_ << ". Rabais : " << coupon.rabais_ << "." << endl;
}

