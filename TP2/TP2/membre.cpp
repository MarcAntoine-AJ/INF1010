/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "membre.h"
#include <vector>


 //Constructeur par defaut
Membre::Membre() :
	nom_(""),
	points_(0)
{

}
//Constructeur par parametres
Membre::Membre(const string& nom) :
	nom_(nom),
	points_(0)
{

}
//Constructeur par copie
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_),
	points_(membre.points_),
	coupons_(membre.coupons_)
{

	for (int i = 0; i < membre.billets_.size(); i++)
	{
		Billet* billet = new Billet(*membre.billets_[i]);
		billets_.push_back(billet);
	}

}
//Destructeur
Membre::~Membre()
{
	for (int i = 0; i < billets_.size(); i++) {
		delete billets_[i];
	}

}
//Getters
string Membre::getNom() const
{
	return nom_;
}

int Membre::getPoints() const
{
	return points_;
}

vector<Billet*> Membre::getBillets() const
{
	return billets_;
}

vector<Coupon*> Membre::getCoupons() const
{
	return coupons_;
}


//Setters
void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

//Modifie le nombre de points
void Membre::modifierPoints(int points)
{
	points_ += points;
}
//Ajoute un billet
void Membre::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol)
{
	Billet* billet = new Billet(pnr, nom_, prix, od, tarif, dateVol);

	billets_.push_back(billet);
	modifierPoints(calculerPoints(billet));
}
//Achete un coupon
void Membre::acheterCoupon(Coupon* coupon)
{
	if (points_ > coupon->getCout()) {
		// TODO: Utiliser la surcharge de l'operateur += de la classe Membre plutot qu'utiliser la methode ajouterCoupon
		*this += coupon;
		modifierPoints(-coupon->getCout());
	}
}
//Calcul le nombre de points pour un billet
double  Membre::calculerPoints(Billet* billet) const
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

// TODO: Remplacer cette methode par l'operateur +=
//Surcharge de operateur += pour ajouter des coupons
Membre& Membre:: operator+= (Coupon* coupon)
{
	coupons_.push_back(coupon);
	return *this;
}

//Surcharge de operateur -= pour retirer des coupons
Membre& Membre ::operator-=(Coupon* coupon)
{
	for (int i = 0; i < coupons_.size(); i++) {
		if (coupons_[i] == coupon) {

			for (int j = i; j < coupons_.size() - 1; j++) {
				coupons_[j] = coupons_[j + 1];
			}

		}
	}
	coupons_.pop_back();
	return *this;
}

//Surcharge de operateur =
Membre& Membre ::operator=(const Membre& membre)
{
	if (this != &membre)
	{
		nom_ = membre.nom_;
		points_ = membre.points_;

		for (int i = 0; i < billets_.size(); i++)
		{
			delete billets_[i];
			billets_[i] = nullptr;
		}

		for (int i = 0; i < membre.billets_.size(); i++)
		{
			Billet* billet = new Billet(*membre.billets_[i]);
			billets_.push_back(billet);
		}
		billets_;


		coupons_ = membre.coupons_;



	}

	return *this;
}

//Surcharge de operateur == pour un membre a gauche
bool Membre :: operator==(const string& membre) const
{
	if (nom_ == membre)
	{
		return true;
	}
	else
	{
		return false;
	}

}
//Surcharge de operateur == pour un membre a droite
bool operator == (const string& nom, const Membre& membre)
{
	if (nom == membre.nom_)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// TODO: Remplacer cette methode par la surcharge de l'operateur <<
//Surcharge de operateur << pour afficher infos
ostream& operator<<(ostream& os, const Membre& membre)
{
	os << setfill(' ')
		<< "- Membre " << membre.nom_ << ":" << endl
		<< "\t" << left << setw(10) << "- Points" << ": " << membre.points_ << endl
		<< "\t" << "- Billets :" << endl;

	for (int i = 0; i < membre.billets_.size(); i++) {
		os << *membre.billets_[i] << endl;
	}

	os << "\t" << "- Coupons :" << endl;
	for (int i = 0; i < membre.coupons_.size(); i++) {
		os << *membre.coupons_[i] << endl;
	}
	os << endl;

	return os;
}
