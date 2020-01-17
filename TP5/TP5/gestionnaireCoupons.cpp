/********************************************
* Titre: Travail pratique #5 - gestionnaireCoupons.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "GestionnaireCoupons.h"
//Fonction pour appliquer le coupon
double GestionnaireCoupons::appliquerCoupon(Membre* membre, double prix)
{
	MembreRegulier* membreReg = dynamic_cast<MembreRegulier*>(membre);

	if (!membreReg || membreReg->getCoupons().size() == 0) {
		cout << "Le membre n'a pas de coupon utilisable\n";
		return 0;
	}

	Coupon* meilleurCoupon = membreReg->getCoupons()[0];
	vector<Coupon*> coupons = membreReg->getCoupons();
	for (size_t i = 1; i < coupons.size(); ++i) {
		if (*coupons[i] > * meilleurCoupon) {
			meilleurCoupon = coupons[i];
		}
	}

	*membreReg -= meilleurCoupon;

	return prix * meilleurCoupon->getRabais();
}
//Fonction pour acheter un coupon
void GestionnaireCoupons::acheterCoupon(Membre* membre)
{
	if (conteneur_.size() == 0) {
		cout << "Le GestionnaireCoupons n'a pas de coupon!" << endl;
		return;
	}

	Coupon* meilleurCoupon = nullptr;

	if (auto membreRegulier = dynamic_cast<MembreRegulier*>(membre)) {
		for (size_t i = 0; i < conteneur_.size(); ++i) {
			if (membreRegulier->peutAcheterCoupon(conteneur_[i])) {
				// Si on avait pas encore trouve de meilleur coupon, on fait la premiere assignation
				if (meilleurCoupon == nullptr) {
					meilleurCoupon = conteneur_[i];
				}
				// Sinon on compare si le coupon courant a un rabais superieur au meilleur coupon
				else if (*conteneur_[i] > * meilleurCoupon) {
					meilleurCoupon = conteneur_[i];
				}
			}
		}
		if (meilleurCoupon) {
			membreRegulier->acheterCoupon(meilleurCoupon);
		}
		else {
			cout << "Le membre ne peut acheter de coupon\n";
		}
	}
	else {
		cout << "Le membre ne peut acheter de coupon\n";
	}
}