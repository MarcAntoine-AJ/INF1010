/********************************************
* Titre: Travail pratique #5 - billetRegulier.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/
#include "billetRegulier.h"
//Constructeur par paramètres
BilletRegulier::BilletRegulier(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol) :
	Billet(pnr, prix, od, tarif), dateVol_(dateVol)
{
}
//Getter
string BilletRegulier::getDateVol() const
{
	return dateVol_;
}

void BilletRegulier::setDateVol(string dateVol)
{
	dateVol_ = dateVol;
}
//Fonction qui retourne une copie de l'objet
BilletRegulier* BilletRegulier::clone() const
{
	return new BilletRegulier(*this);
}
//Fonction d'affichage
void BilletRegulier::afficher(ostream& o) const
{
	Billet::afficher(o);
	o << "\t\t\t" << setw(11) << "- Vol le" << ": " << dateVol_ << endl;
}