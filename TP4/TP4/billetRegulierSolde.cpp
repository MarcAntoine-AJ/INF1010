/*
* Titre : billetRegulierSolde.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe C�T�-MORNEAULT
*/

#include "billetRegulierSolde.h"

// TODO
//Constructeur par param�tres
BilletRegulierSolde::BilletRegulierSolde(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol, double pourcentageSolde) :
	BilletRegulier(pnr, prix, od, tarif, dateVol), Solde(pourcentageSolde)
{
}

// TODO
//Getters
double BilletRegulierSolde::getPrix() const
{
	return (prix_ * (1 - pourcentageSolde_));
}

// TODO
double BilletRegulierSolde::getPrixBase()
{
	return prix_;
}

// TODO
//M�thode pour cr�er une copie
BilletRegulierSolde* BilletRegulierSolde::clone() const
{
	BilletRegulierSolde* billetClone = new BilletRegulierSolde(*this);
	return billetClone;
}

// TODO
//M�thode d'Affichage
void BilletRegulierSolde::afficher(ostream& o) const
{
	BilletRegulier::afficher(o);
	o << "\t\t\t" << setw(11) << "Pourcentage du solde : " << pourcentageSolde_ << " % " << endl;

}