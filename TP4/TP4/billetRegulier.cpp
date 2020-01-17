/*
* Titre : billetRegulier.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "billetRegulier.h"

//Constructeur par paramètres
BilletRegulier::BilletRegulier(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol) :
	Billet(pnr, prix, od, tarif), dateVol_(dateVol)
{
}
//Getters
string BilletRegulier::getDateVol() const
{
	return dateVol_;
}

//Setters
void BilletRegulier::setDateVol(string dateVol)
{
	dateVol_ = dateVol;
}

// TODO
// Méthode pour donner une copie de l'objet courant
BilletRegulier* BilletRegulier::clone() const
{
	BilletRegulier* billetClone = new BilletRegulier(*this); // Esque jai le droit utiliser this
	return billetClone;
}



// TODO
//Méthode d'Affichage
void BilletRegulier::afficher(ostream& o) const
{
	Billet::afficher(o);
	o << "\t\t\t" << setw(11) << "- Vol le" << ": " << dateVol_ << endl;


}