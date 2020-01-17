/********************************************
* Titre: Travail pratique #5 - membreRegulier.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "membreRegulier.h"

//Constructeur par paramètres
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
//Fonction pour ajouter un billet
void MembreRegulier::ajouterBillet(Billet* billet)
{
	Membre::ajouterBillet(billet);
	modifierPoints(calculerPoints(billets_.back()));
}
//Opérateur +=
Membre& MembreRegulier::operator+=(Coupon* coupon)
{
	coupons_.push_back(coupon);

	return *this;
}

//Opérateur -=
Membre& MembreRegulier::operator-=(Coupon* coupon)
{
	auto it = find(coupons_.begin(), coupons_.end(), coupon);
	if (it != coupons_.end()) {

		coupons_.erase(it);
		return *this;
	}
	return *this;
}
//Fonction pour modifier les points
void MembreRegulier::modifierPoints(int points)
{
	points_ += points;
}
//Fonction pour calculer les points
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
//Fonction pour vérifier si peut acheter
bool MembreRegulier::peutAcheterCoupon(Coupon* coupon) const
{
	return points_ >= coupon->getCout();
}
//Fonction pour acheter un coupon
void MembreRegulier::acheterCoupon(Coupon* coupon)
{
	if (peutAcheterCoupon(coupon)) {
		*this += coupon;
		modifierPoints(-coupon->getCout());
	}
}


//Fonction d'affichage
void MembreRegulier::afficher(ostream& o) const
{
	Membre::afficher(o);
	o << "\t" << "- Points : " << points_ << endl;
	o << "\t" << "- Coupons :" << endl;
	copy(coupons_.begin(), coupons_.end(), ostream_iterator<Coupon*>(o));
}
