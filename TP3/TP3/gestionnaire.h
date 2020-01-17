/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#ifndef GESTIONNAIRE_H
#define	GESTIONNAIRE_H

#include <vector>

#include "membrePremium.h"

class Gestionnaire {
public:
	// Constructeurs
	Gestionnaire();

	~Gestionnaire();

	// Getters
	vector<Membre*> getMembres() const;
	vector<Coupon*> getCoupons() const;

	//à modifier
	void ajouterMembre(const string& nomMembre, TypeMembre typeMembre);

	void ajouterCoupon(const string& code, double rabais, int cout);

	Membre* trouverMembre(const string& nomMembre) const;

	//à modifier
	void assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon, TypeBillet typeBillet);

	//à modifier
	double appliquerCoupon(Membre* membre, double prix);

	//à modifier
	void acheterCoupon(const string& nomMembre);

	//à modifier
	friend ostream& operator<<(ostream& o, const Gestionnaire& gestionnaire);
private:
	vector<Membre*> membres_;
	vector<Coupon*> coupons_;
};

#endif // !GESTIONNAIRE_H



