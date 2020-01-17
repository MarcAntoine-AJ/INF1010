/*
* Titre : membrePremium.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "membrePremium.h"
//Constructeur par paramètres
MembrePremium::MembrePremium(const string& nom) :
	MembreRegulier(nom), joursRestants_(JOUR_RESTANT_INITIALE), pointsCumulee_(0)
{
}
//Setter
void MembrePremium::setJourRestants(unsigned int joursRestants)
{
	joursRestants_ = joursRestants;
}
//Méthode pour modifier les points cumulées
void MembrePremium::modifierPointsCumulee(unsigned int pointCumulee)
{
	pointsCumulee_ += pointCumulee;
}
//Getter
unsigned int MembrePremium::getJourRestants() const
{
	return joursRestants_;
}

unsigned int MembrePremium::getpointsCumulee() const
{
	return pointsCumulee_;
}
//Méthode pour ajouter un billet
void MembrePremium::ajouterBillet(Billet* billet)
{
	MembreRegulier::ajouterBillet(billet);
	modifierPointsCumulee(calculerPoints(billets_.back()));
}
//Méthode pour calculer le cout des coupons
double MembrePremium::calculerCoutCoupon(Coupon* coupon) const
{
	double rabais = 0.01 * pointsCumulee_ / 1000;

	if (rabais > 0.2)
		rabais = 0.2;

	return coupon->getCout() * (1 - rabais);
}

// TODO
//Méthode pour voir si le membre peut acheter un coupon
bool MembrePremium::peutAcheterCoupon(Coupon* coupon) const
{
	bool valeur = false;
	if (points_ > calculerCoutCoupon(coupon))
	{
		valeur = true;
	}
	return valeur;
}
//Méthode pour achter un coupon
void MembrePremium::acheterCoupon(Coupon* coupon)
{
	if (peutAcheterCoupon(coupon)) {
		*this += coupon;
		modifierPoints(-calculerCoutCoupon(coupon));
	}
}
// TODO
//Méthode d'Affichage
void MembrePremium::afficher(ostream& o) const
{
	MembreRegulier::afficher(o);
	o << "\t- Points cumulee: " << pointsCumulee_ << endl;
	o << "\t- Jours premium restant: " << joursRestants_ << endl;

}