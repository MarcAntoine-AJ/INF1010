/********************************************
* Titre: Travail pratique #5 - solde.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "solde.h"
//Constructeur par paramètres
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
