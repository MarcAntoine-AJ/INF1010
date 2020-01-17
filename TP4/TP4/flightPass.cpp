/*
* Titre : flightPass.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/
#include "flightPass.h"

//Constructeur par paramètres
FlightPass::FlightPass(const string& pnr, double prix, const string& od, TarifBillet tarif) :
	Billet(pnr, prix, od, tarif), nbUtilisationsRestante_(NB_UTILISATIONS_INITIALE)
{
}

//Get le nombre d'utilisations
int FlightPass::getNbUtilisationsRestante() const
{
	return nbUtilisationsRestante_;
}
//Diminue le nombre d'utilisations
void FlightPass::decrementeNbUtilisations()
{
	--nbUtilisationsRestante_;
}

// TODO
//Méthode de copie de l'objet actuel
FlightPass* FlightPass::clone() const
{
	FlightPass* flightClone = new FlightPass(*this);
	return flightClone;
}



// TODO
//Méthode d'Affichage
void FlightPass::afficher(ostream& o) const
{
	Billet::afficher(o);
	o << "\t\t\t" << setw(11) << "- Utilisation restantes" << ": " << nbUtilisationsRestante_ << endl;

}