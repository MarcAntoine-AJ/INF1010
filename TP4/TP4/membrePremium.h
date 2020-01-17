/*
* Titre : membrePremium.h - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#ifndef MEMBRE_PREMIUM_H
#define MEMBRE_PREMIUM_H

#include "membreRegulier.h"
#include "debogageMemoire.hpp"

class MembrePremium : public MembreRegulier {
public:
	// Constructeur
	MembrePremium(const string& nom);

	// Setters
	void setJourRestants(unsigned int joursRestants);
	void modifierPointsCumulee(unsigned int pointCumulee);

	// Getters
	unsigned int getJourRestants() const;
	unsigned int getpointsCumulee() const;

	void ajouterBillet(Billet* billet) override;
	double calculerCoutCoupon(Coupon* coupon) const;
	// TODO
	bool peutAcheterCoupon(Coupon* coupon) const override;
	void acheterCoupon(Coupon* coupon) override;
	// TODO
	void afficher(ostream& o) const  override;
private:
	unsigned int joursRestants_;
	unsigned int pointsCumulee_;
};
#endif // !MEMBRE_PREMIUM_H