/*
* Titre : membreRegulier.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe C�T�-MORNEAULT
*/

#include "membreRegulier.h"
//Constructeur par param�tres
MembreRegulier::MembreRegulier(const string& nom) :
	Membre(nom), points_(0)
{
}
//Getters
int MembreRegulier::getPoints() const
{
	return points_;
}

vector<Coupon*> MembreRegulier::getCoupons() const
{
	return coupons_;
}
//M�thode pour ajouter un billet
void MembreRegulier::ajouterBillet(Billet* billet)
{
	Membre::ajouterBillet(billet);
	modifierPoints(calculerPoints(billets_.back()));
}
//Op�rateurs
Membre& MembreRegulier::operator+=(Coupon* coupon)
{
	coupons_.push_back(coupon);

	return *this;
}

Membre& MembreRegulier::operator-=(Coupon* coupon)
{
	for (size_t i = 0; i < coupons_.size(); ++i) {
		if (coupons_[i] == coupon) {
			coupons_[i] = coupons_[coupons_.size() - 1];
			coupons_.pop_back();
			return *this;
		}
	}

	return *this;
}
//M�thode pour modifier les points
void MembreRegulier::modifierPoints(int points)
{
	points_ += points;
}
//M�thode pour calculer des points
double MembreRegulier::calculerPoints(Billet* billet) const
{
	double bonus = 0;
	switch (billet->getTarif()) {
	case TarifBillet::PremiumEconomie:
		bonus = 50;
		break;
	case TarifBillet::Affaire:
		bonus = 150;
		break;
	case TarifBillet::Premiere:
		bonus = 300;
		break;
	default:
		break;
	}

	return billet->getPrix() * 0.10 + bonus;
}

// TODO
//M�thode pour voir s'il peut acheter un coupon
bool MembreRegulier::peutAcheterCoupon(Coupon* coupon) const
{
	bool valeur = false;
	if (points_ > coupon->getCout())
	{
		valeur = true;
	}
	return valeur;
}
//M�thode pour acheter un coupon
void MembreRegulier::acheterCoupon(Coupon* coupon)
{
	if (peutAcheterCoupon(coupon)) {
		*this += coupon;
		modifierPoints(-coupon->getCout());
	}
}
// TODO
//M�thode d'Affichage
void MembreRegulier::afficher(ostream& o) const
{
	Membre::afficher(o);
	o << "\t" << "- Points : " << points_ << endl;
	o << "\t" << "- Coupons :" << endl;
	for (size_t i = 0; i < coupons_.size(); ++i) {
		coupons_[i]->afficher(o);
	}


}
