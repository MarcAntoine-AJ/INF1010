/*
 * Date : 1 Septembre 2019
 * Auteur : Marc-Antoine Abou Jaoude
 */

#include <string>
#include <iostream>
#include <vector>
#include "coupon.h"
using namespace std;
//Constructeur par defaut
Coupon::Coupon() 
	: code_(""),rabais_(0),cout_(0)
{
}
//Constructeur par parametre
Coupon::Coupon(const string& code, double rabais, int cout)
	: code_(code), rabais_(rabais), cout_(cout)
{
}

// Getters
string Coupon:: getCode() const 
{
	return code_;
}
double Coupon::getRabais()const
{
	return rabais_;
}
int Coupon:: getCout() const
{
	return cout_;
}

// Setters
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
//Méthode d'affichage de coupon
void Coupon::afficherCoupon() const {
	cout << "		Coupon : " << code_ << " . " << "Rabais : " << rabais_ << "." <<endl;

}
//Destructeur de coupon
Coupon::~Coupon() {


}






