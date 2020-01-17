/*
* Titre : membrePremium.h - Travail Pratique #3
* Date : 20 Septembre 2019
* Auteur : Jeffrey Lavallee
*/


#ifndef MEMBRE_PREMIUM_H
#define MEMBRE_PREMIUM_H


#include "membreRegulier.h"

class MembrePremium : public MembreRegulier {
public:
	//� faire
	MembrePremium(const string& nom);

	//setters
	//� faire
	void setJourRestants(unsigned int joursRestants);
	//� faire
	void modifierPointsCumules(unsigned int pointCumulee);


	//getters
	//� faire
	unsigned int getJourRestants() const;
	//� faire
	unsigned int getpointsCumulee() const;

	//� faire
	void ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol);
	//� faire
	void acheterCoupon(Coupon* coupon);

	//� faire
	friend ostream& operator<<(ostream& os, const MembrePremium& membrePremium);

private:
	unsigned int joursRestants_;
	unsigned int pointsCumules_;

};

#endif