#include "membreRegulier.h"

//Constructeur par paramètres
MembreRegulier::MembreRegulier(const string& nom, TypeMembre typeMembre)
	: Membre(nom, typeMembre), points_(0)
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
//Méthode pour acheter un coupon
void MembreRegulier::acheterCoupon(Coupon* coupon)
{
	if (points_ > coupon->getCout()) {
		*this += coupon;
		modifierPoints(-coupon->getCout());
	}
}
//Méthode pour ajouter un billet
void MembreRegulier::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol)
{
	Membre::ajouterBillet(pnr, prix, od, tarif, typeBillet, dateVol);
	modifierPoints(calculerPoints(billets_[billets_.size() - 1]));
}
Membre& MembreRegulier::operator+=(Coupon* coupon)
{
	coupons_.push_back(coupon);

	return *this;
}
//Opérateur -=
Membre& MembreRegulier::operator-=(Coupon* coupon)
{
	for (int i = 0; i < coupons_.size(); i++) {
		if (coupons_[i] == coupon) {
			coupons_[i] = coupons_[coupons_.size() - 1];
			coupons_.pop_back();
			return *this;
		}
	}

	return *this;
}
//Méthode pour modifier les points
void MembreRegulier::modifierPoints(int points)
{
	points_ += points;
}
//Méthode qui calcule les points et retourne les points calculés
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

//Opérateur d'affichage
ostream& operator<< (ostream& os, const MembreRegulier& membreRegulier)
{
	os << static_cast<Membre>(membreRegulier);
	os << "Points : " << membreRegulier.points_ << endl;
	for (int i = 0; i < membreRegulier.coupons_.size(); i++)
	{
		os << *membreRegulier.coupons_[i] << endl;

	}

	return os << endl;
}

