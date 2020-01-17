/********************************************
* Titre: Travail pratique #5 - flightPassSolde.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "flightPassSolde.h"
//Constructeur par paramètres
FlightPassSolde::FlightPassSolde(const string& pnr, double prix, const string& od, TarifBillet tarif, double pourcentageSolde) :
	FlightPass(pnr, prix, od, tarif), Solde(pourcentageSolde)
{
}
//Getters
double FlightPassSolde::getPrix() const
{
	return prix_ * (1 - pourcentageSolde_);
}

double FlightPassSolde::getPrixBase() const
{
	return prix_;
}
//Retourne une copie de l'objet
FlightPassSolde* FlightPassSolde::clone() const
{
	return new FlightPassSolde(*this);
}
//Fonction d'affichage
void FlightPassSolde::afficher(ostream& o) const
{
	FlightPass::afficher(o);
	o << "\t\t\t" << setw(11) << "- Pourcentage solde" << ": " << pourcentageSolde_ << "%" << endl;
}