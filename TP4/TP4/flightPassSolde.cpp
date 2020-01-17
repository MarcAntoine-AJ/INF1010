/*
* Titre : flightPassSolde.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "flightPassSolde.h"

// TODO
//Constructeur par paramètres
FlightPassSolde::FlightPassSolde(const string& pnr, double prix, const string& od, TarifBillet tarif, double pourcentageSolde)
	: FlightPass(pnr, prix, od, tarif), Solde(pourcentageSolde)
{
}

// TODO
//Getters
double FlightPassSolde::getPrix() const
{
	return (prix_ * (1 - pourcentageSolde_));
}

// TODO
double FlightPassSolde::getPrixBase()
{
	return prix_;
}

// TODO
//Méthode de copie de l'objet actuel
FlightPassSolde* FlightPassSolde::clone() const
{
	FlightPassSolde* flightClone = new FlightPassSolde(*this);
	return flightClone;
}

// TODO
//Méthode d'Affichage
void FlightPassSolde::afficher(ostream& o) const
{
	FlightPass::afficher(o);
	o << "\t\t\t" << setw(11) << " Pourcentage Solde : " << pourcentageSolde_ << endl;
}