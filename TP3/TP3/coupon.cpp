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
//Opérateur plus grand
bool Coupon::operator>(const Coupon& coupon) const
{
	return rabais_ > coupon.rabais_;
}
//Opérateur plus petit
bool Coupon::operator<(const Coupon& coupon) const
{
	return rabais_ < coupon.rabais_;
}
//Opérateur d'affichage
ostream& operator<<(ostream& o, const Coupon& coupon)
{
	return o << "\t\t- Coupon " << coupon.code_ << ". Rabais : " << coupon.rabais_ << "." << endl;
}
