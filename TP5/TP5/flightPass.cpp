/********************************************
* Titre: Travail pratique #5 - flightPass.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/
#include "flightPass.h"
//Constructeur par paramètres
FlightPass::FlightPass(const string& pnr, double prix, const string& od, TarifBillet tarif) : 
	Billet(pnr, prix, od, tarif), nbUtilisationsRestante_(NB_UTILISATIONS_INITIALE)
{
}
//Getters
int FlightPass::getNbUtilisationsRestante() const
{
	return nbUtilisationsRestante_;
}
//Diminue le nombre d'utilisation restante
void FlightPass::decrementeNbUtilisations()
{
	--nbUtilisationsRestante_;
}
//Retourne une copie de l'objet
FlightPass* FlightPass::clone() const
{
	return new FlightPass(*this);
}
//Fonction d'affichage
void FlightPass::afficher(ostream& o) const
{
	Billet::afficher(o);
	o << "\t\t\t" << setw(11) << "- Utilisation restantes" << ": " << nbUtilisationsRestante_ << endl;
}