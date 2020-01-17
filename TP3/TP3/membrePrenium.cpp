#include "membrePremium.h"

//Constructeur par paramètres
MembrePremium::MembrePremium(const string& nom) : MembreRegulier(nom, TypeMembre::Membre_Premium)
{
	joursRestants_ = JOUR_RESTANT_INITIALE;
	pointsCumules_ = 0;
}
//Getters
unsigned int MembrePremium::getJourRestants() const
{
	return joursRestants_;
}

unsigned int MembrePremium::getpointsCumulee() const
{

	return pointsCumules_;
}
//Setters
void MembrePremium::setJourRestants(unsigned int joursRestants)
{
	joursRestants_ = joursRestants;
}
//Permet de modifier les points cumules
void MembrePremium::modifierPointsCumules(unsigned int pointsCumules)
{
	pointsCumules_ += pointsCumules;
}
//Permet d'acheter un coupon
void MembrePremium::acheterCoupon(Coupon* coupon)
{
	double rabais = 0;
	if (pointsCumules_ >= 19000)
	{
		rabais = 0.2;

	}
	else
	{
		double pointAacumuler = 1000;
		double pointsActuels = points_;
		rabais = (0.01 * (pointsActuels / pointAacumuler));
	}

	if (points_ > (coupon->getCout() * (1 - rabais))) {
		*this += coupon;
		modifierPoints(-(coupon->getCout() * (1 - rabais)));
	}





}
//Méthode pour ajouter un billet
void MembrePremium::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol)
{
	MembreRegulier::ajouterBillet(pnr, prix, od, tarif, typeBillet, dateVol);
	modifierPointsCumules(calculerPoints(billets_[billets_.size() - 1]));
}
//Opérateur d'affichage
ostream& operator<<(ostream& os, const MembrePremium& membrePremium)
{
	os << static_cast<MembreRegulier>(membrePremium);
	os << "Jours restants : " << membrePremium.joursRestants_ << endl;
	os << "Points cumules : " << membrePremium.pointsCumules_ << endl;

	return os << endl;

}


