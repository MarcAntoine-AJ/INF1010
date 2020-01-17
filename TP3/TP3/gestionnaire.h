/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe C�T�-MORNEAULT
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

	//� modifier
	void ajouterMembre(const string& nomMembre, TypeMembre typeMembre);

	void ajouterCoupon(const string& code, double rabais, int cout);

	Membre* trouverMembre(const string& nomMembre) const;

	//� modifier
	void assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon, TypeBillet typeBillet);

	//� modifier
	double appliquerCoupon(Membre* membre, double prix);

	//� modifier
	void acheterCoupon(const string& nomMembre);

	//� modifier
	friend ostream& operator<<(ostream& o, const Gestionnaire& gestionnaire);
private:
	vector<Membre*> membres_;
	vector<Coupon*> coupons_;
};

#endif // !GESTIONNAIRE_H



