/*
* Titre : solde.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe C�T�-MORNEAULT
*/

#include "solde.h"
//Constructeur par param�tres
Solde::Solde(double pourcentageSolde)
{
	pourcentageSolde_ = pourcentageSolde;
}
//Destructeur
Solde::~Solde()
{
}
//Getters
double Solde::getPourcentageSolde() const
{
	return pourcentageSolde_;
}
//Setters
void Solde::setPourcentageSolde(double pourcentageSolde)
{
	pourcentageSolde_ = pourcentageSolde;
}
