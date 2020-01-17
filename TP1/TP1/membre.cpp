#include <string>
#include <iostream>
#include <vector>
#include "billet.h"
#include "membre.h"
#include "def.h"
using namespace std;


//Constructeur par defaut
Membre::Membre() 
	: nom_("N/A"),points_(0),capaciteBillets_(CAPACITE_INITIALE),billets_(new Billet* [CAPACITE_INITIALE]),nbBillets_(0),
	capaciteCoupons_(CAPACITE_INITIALE),coupons_(new Coupon* [CAPACITE_INITIALE]),nbCoupons_(0)
{
	
	
	for (int i=0;i<capaciteBillets_;i++)
	{
	billets_[i]=nullptr; 
	} 
	
	for (int i = 0; i < capaciteCoupons_; i++)
	{
		coupons_[i] = nullptr;
	}
	
	
}
//Constructeur par parametres
Membre::Membre(const string& nom) : nom_(nom), points_(0), capaciteBillets_(CAPACITE_INITIALE), billets_(new Billet* [CAPACITE_INITIALE]), nbBillets_(0),
capaciteCoupons_(CAPACITE_INITIALE), coupons_(new Coupon* [CAPACITE_INITIALE]),nbCoupons_(0)
{
	
	for (int i = 0; i < capaciteBillets_; i++)
	{
		billets_[i] = nullptr;
	}
	
	for (int i = 0; i < capaciteCoupons_; i++)
	{
		coupons_[i] = nullptr;
	}
	

}

// Getters
string Membre::getNom() const 
{
	return nom_;
}
int Membre::getPoints() const
{
	return points_;
}
Billet** Membre::getBillets() const 
{
	return billets_;
}
int Membre::getNbBillets() const 
{
	return nbBillets_;
}
int Membre::getCapaciteBillets() const 
{
	return capaciteBillets_;
}
Coupon** Membre::getCoupons() const
{
	return coupons_;
}
int Membre::getNbCoupons() const 
{
	return nbCoupons_;
}
int Membre::getCapaciteCoupons() const 
{
	return capaciteCoupons_;
}

// Setters
void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

void Membre::modifierPoints(int points)
{
	points_ = points_ + points;
}

void Membre::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol)
{

	bool foundEmptyCase = false;
	Billet *  newBillet = new Billet( pnr, nom_,  prix,  od,  tarif,  dateVol); 
	nbBillets_=nbBillets_+1;
	
	if(nbBillets_ > capaciteBillets_)
	{
	//On modifie la taille du tableau
		Billet** tempBillets = new  Billet*[2*capaciteBillets_];
		
		for (int i = 0; i < 2 * capaciteBillets_; i++)
	{
		tempBillets[i] = nullptr;
	}
		for(int i=0;i<capaciteBillets_;i++)
		{
			tempBillets[i] = billets_[i];
		}
		delete[] billets_;
		billets_ = tempBillets;
		capaciteBillets_ = 2 * capaciteBillets_;
        
	} 
		
		//On ajoute le billet
	billets_[nbBillets_ - 1] = newBillet;
		points_ = points_ + calculerPoints(newBillet);

	
}
//Calcul le nombre de points selon le tarif
double Membre ::calculerPoints(Billet * billet) const
{
	double  pourcentage = 0.10;
	double  pointsAffaire = 150;
	double  pointsPrenium = 50;
	double  pointsPremiere = 300;
	double pointsSupp = (billet->getPrix())*pourcentage;
	TarifBillet tarif = billet->getTarif();
	switch (tarif) {

	case TarifBillet::Affaire:
		pointsSupp = pointsSupp + pointsAffaire;
		break;
	case TarifBillet::Premiere:
		pointsSupp = pointsSupp + pointsPremiere;
		break;
	case TarifBillet::PremiumEconomie:
		pointsSupp = pointsSupp + pointsPrenium;
		break;

	

	}
	return pointsSupp;
}
// Ajoute le coupon dans le tableau
void Membre::ajouterCoupon(Coupon * coupon)
{
	bool foundEmptyCase = false;
	nbCoupons_=nbCoupons_+1;

	if (nbCoupons_ > capaciteCoupons_)
	{
		//On modifie la taille du tableau
		Coupon** tempCoupons = new  Coupon * [2 * capaciteCoupons_];
		for (int i = 0; i < 2 * capaciteCoupons_; i++)
		{
			tempCoupons[i] = nullptr;
		}
		for (int i = 0; i < capaciteCoupons_; i++)
		{
			tempCoupons[i] = coupons_[i];
		}
		delete[] coupons_;
		coupons_ = tempCoupons;
		capaciteCoupons_ = 2 * capaciteCoupons_;

	}

	//On ajoute le coupon
	coupons_[nbCoupons_ - 1] = coupon;
	


}
//Retire le coupon
void Membre::retirerCoupon(Coupon* coupon) 
{
	bool couponTrouver = false;
	int indexCouponTrouver=capaciteCoupons_;
	//On cherche l'index du coupon
	for(int i =0;(i<capaciteCoupons_) & (!couponTrouver);i++)
	{
		if (coupons_[i] == coupon) 
		{
			indexCouponTrouver = i;
			couponTrouver = true;
	}
	}
	//On retire le coupon de la liste
	coupons_[indexCouponTrouver] = nullptr;
	//On réarrange le tableau
	for(int i =indexCouponTrouver+1;i<capaciteCoupons_;i++)
	{
		coupons_[i - 1] = coupons_[i];
	}
	nbCoupons_ = nbCoupons_ - 1;
}
//Méthode pour acheter un coupon
void Membre::acheterCoupon(Coupon* coupon)
{
	if(points_>=coupon->getCout())
	{
		points_ = points_ - coupon->getCout();
		ajouterCoupon(coupon);
	
	}
}
//Destructeur de coupons
Membre ::~Membre()
{
	for(int i=0;i<capaciteBillets_;i++)
	{
		delete billets_[i];
	}
	delete[] billets_;
	delete[] coupons_;

}
//Méthode pour afficher un membre
void Membre::afficherMembre() const 
{
	cout << "-Membre " << nom_ << " : " << endl;
	cout << "  Points : " << points_ << endl;
	cout << "  Billets : " << endl;
	for(int i =0;i<capaciteBillets_;i++)
	{
		if (billets_[i] != nullptr) 
		{
billets_[i]->afficherBillet();
		}
		
	}
	cout << "   Coupons : " << endl;
	for (int i = 0; i < capaciteCoupons_; i++)
	{
		if (coupons_[i] != nullptr) 
		{
coupons_[i]->afficherCoupon();
		}
		
	}

}



