/********************************************
* Titre: Travail pratique #5 - coupon.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

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
//Opérateur >
bool Coupon::operator>(const Coupon& coupon) const
{
	return rabais_ > coupon.rabais_;
}
//Operateur <
bool Coupon::operator<(const Coupon& coupon) const
{
	return rabais_ < coupon.rabais_;
}
//Operateur d'affichage
ostream& operator<<(ostream& o, Coupon* c)
{
	c->afficher(o);
	return o;

}
//Fonction d'Affichage
void Coupon::afficher(ostream& o) const
{
	o << "\t\t- Coupon " << code_ << ". Rabais : " << rabais_ << "." << endl;
}

