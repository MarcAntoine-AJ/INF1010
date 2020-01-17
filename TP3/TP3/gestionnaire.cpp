/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "gestionnaire.h"

 //Constructeur par défaut
Gestionnaire::Gestionnaire()
{
}
//destructeur
Gestionnaire::~Gestionnaire()
{
	for (int i = 0; i < membres_.size(); i++) {
		delete membres_[i];
	}

	for (int i = 0; i < coupons_.size(); i++) {
		delete coupons_[i];
	}
}
//Getters
vector<Membre*> Gestionnaire::getMembres() const
{
	return membres_;
}

vector<Coupon*> Gestionnaire::getCoupons() const
{
	return coupons_;
}

//Méthode pour ajouter le bon type de membre
void Gestionnaire::ajouterMembre(const string& nomMembre, TypeMembre typeMembre)

{
	switch (typeMembre)
	{
	case TypeMembre::Membre_Occasionnel:
		membres_.push_back(new Membre(nomMembre, typeMembre));
		break;
	case TypeMembre::Membre_Premium:
		membres_.push_back(new MembrePremium(nomMembre));
		break;
	case TypeMembre::Membre_Regulier:
		membres_.push_back(new MembreRegulier(nomMembre, typeMembre));
		break;

	}

}
//Méthode pour ajouter un coupon
void Gestionnaire::ajouterCoupon(const string& code, double rabais, int cout)
{
	coupons_.push_back(new Coupon(code, rabais, cout));
}
//Méthode pour trouver le membre
Membre* Gestionnaire::trouverMembre(const string& nomMembre) const
{
	for (int i = 0; i < membres_.size(); i++) {
		if (*membres_[i] == nomMembre) {
			return membres_[i];
		}
	}
	cout << "Le membre " << nomMembre << " n'existe pas\n";

	return nullptr;
}
//Méthode pour assigner le bon billet 
void Gestionnaire::assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon, TypeBillet typeBillet)
{
	double prixReel;
	Membre* membre = trouverMembre(nomMembre);

	if (membre == nullptr) {
		return;
	}

	if (utiliserCoupon) {
		prixReel = prixBase - appliquerCoupon(membre, prixBase);
	}
	else {
		prixReel = prixBase;
	}
	if (typeBillet == TypeBillet::Flight_Pass)
	{
		prixReel = prixReel * 10;
	}

	switch (membre->getTypeMembre())
	{
	case TypeMembre::Membre_Premium:
		if (static_cast<MembrePremium*>(membre)->getpointsCumulee() >= 19000)
		{
			prixReel = prixReel * 0.9;
		}
		else
		{
			int pointAacumuler = 1000;
			double rabais = 0;
			rabais = 0.005 * (static_cast<MembrePremium*>(membre)->getpointsCumulee() / pointAacumuler);
			prixReel = prixReel * (1 - rabais);
		}
		static_cast<MembrePremium*>(membre)->ajouterBillet(pnr, prixReel, od, tarif, typeBillet, dateVol);
		break;

	case TypeMembre::Membre_Regulier:
		static_cast<MembreRegulier*>(membre)->ajouterBillet(pnr, prixReel, od, tarif, typeBillet, dateVol);
		break;

	case TypeMembre::Membre_Occasionnel:
		membre->ajouterBillet(pnr, prixReel, od, tarif, typeBillet, dateVol);
		break;

	}

}
//Méthode pour appliquer le coupon
double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	if (membre->getTypeMembre() == TypeMembre::Membre_Occasionnel)
	{
		return prix;
	}

	if (static_cast<MembreRegulier*>(membre)->getCoupons().size() == 0) {
		cout << "Le membre n'a pas de coupon utilisable\n";
		return 0;
	}

	Coupon* meilleurCoupon = static_cast<MembreRegulier*>(membre)->getCoupons()[0];
	vector<Coupon*> coupons = static_cast<MembreRegulier*>(membre)->getCoupons();
	for (int i = 1; i < coupons.size(); ++i) {
		if (*coupons[i] > * meilleurCoupon) {
			meilleurCoupon = coupons[i];
		}
	}

	*static_cast<MembreRegulier*>(membre) -= meilleurCoupon;

	return prix * meilleurCoupon->getRabais();
}
//Méthode pour acheter un coupon
void Gestionnaire::acheterCoupon(const string& nomMembre)
{
	if (coupons_.size() == 0) {
		cout << "Le gestionnaire n'a pas de coupon!" << endl;
		return;
	}

	Membre* membre = trouverMembre(nomMembre);

	if (membre == nullptr) {
		return;
	}
	if (membre->getTypeMembre() == TypeMembre::Membre_Occasionnel)
	{
		return;
	}

	Coupon* meilleurCoupon = nullptr;

	for (int i = 0; i < coupons_.size(); i++) {
		if (static_cast<MembreRegulier*>(membre)->getPoints() >= coupons_[i]->getCout()) {
			// Si on avait pas encore trouve de meilleur coupon, on fait la premiere assignation
			if (meilleurCoupon == nullptr) {
				meilleurCoupon = coupons_[i];
			}
			// Sinon on compare si le coupon courant a un rabais superieur au meilleur coupon
			else if (*coupons_[i] > * meilleurCoupon) {
				meilleurCoupon = coupons_[i];
			}
		}
	}

	if (meilleurCoupon) {
		switch (membre->getTypeMembre())
		{
		case TypeMembre::Membre_Premium:
			static_cast<MembrePremium*>(membre)->acheterCoupon(meilleurCoupon);
			break;
		case TypeMembre::Membre_Regulier:
			static_cast<MembreRegulier*>(membre)->acheterCoupon(meilleurCoupon);
			break;

		}

	}
	else {
		cout << "Le membre ne peut acheter de coupon\n";
	}
}

//opérateur d'affichage
ostream& operator<<(ostream& o, const Gestionnaire& gestionnaire)
{
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";
	for (int i = 0; i < gestionnaire.membres_.size(); i++) {
		switch (gestionnaire.membres_[i]->getTypeMembre())
		{
		case TypeMembre::Membre_Occasionnel:
			o << *gestionnaire.membres_[i];
			break;
		case TypeMembre::Membre_Premium:
			o << *static_cast<MembrePremium*>(gestionnaire.membres_[i]);
			break;
		case TypeMembre::Membre_Regulier:
			o << *static_cast<MembreRegulier*>(gestionnaire.membres_[i]);
			break;

		}


	}

	return o;
}
