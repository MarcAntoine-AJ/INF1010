/********************************************
* Titre: Travail pratique #5 - membrePremium.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#ifndef MEMBRE_PREMIUM_H
#define MEMBRE_PREMIUM_H

#include "membreRegulier.h"

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
	bool peutAcheterCoupon(Coupon* coupon) const override;
	void acheterCoupon(Coupon* coupon) override;

	void afficher(ostream& o) const override;
private:
	unsigned int joursRestants_;
	unsigned int pointsCumulee_;
};
#endif // !MEMBRE_PREMIUM_H