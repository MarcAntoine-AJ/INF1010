/********************************************
* Titre: Travail pratique #5 - membreRegulier.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#ifndef MEMBRE_REGULIER_H
#define MEMBRE_REGULIER_H

#include "membre.h"

class MembreRegulier : public Membre {
public:
	// Constructeur
	MembreRegulier(const string& nom);

	// Getters
	int getPoints() const;
	vector<Coupon*> getCoupons() const;

	Membre& operator+=(Coupon* coupon);
	Membre& operator-=(Coupon* coupon);
	void modifierPoints(int points);
	void ajouterBillet(Billet* billet) override;

	double calculerPoints(Billet* billet) const;
	virtual bool peutAcheterCoupon(Coupon* coupon) const;
	virtual void acheterCoupon(Coupon* coupon);

	void afficher(ostream& o) const override;
protected:
	int points_;
	vector<Coupon*> coupons_;
};
#endif // !MEMBRE_REGULIER_H