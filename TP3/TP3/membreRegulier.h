/*
* Titre : membreRegulier.h - Travail Pratique #3
* Date : 20 Septembre 2019
* Auteur : Jeffrey Lavallee
*/


#ifndef MEMBRE_REGULIER_H
#define MEMBRE_REGULIER_H


#include "membre.h";

class MembreRegulier : public Membre {
public:

	//à faire
	MembreRegulier(const string& nom, TypeMembre typeMembre);

	int getPoints() const;
	vector<Coupon*> getCoupons() const;


	void acheterCoupon(Coupon* coupon);
	Membre& operator+=(Coupon* coupon);
	Membre& operator-=(Coupon* coupon);
	void modifierPoints(int points);

	//à faire 
	void ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol);


	double calculerPoints(Billet* billet) const;

	//à faire
	friend ostream& operator<<(ostream& os, const MembreRegulier& membreRegulier);

protected:
	int points_;
	vector<Coupon*> coupons_;
};

#endif