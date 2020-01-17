/*
 * Date : 12 Septembre 2019
 * Auteur : Marc-Antoine Abou Jaoude
 */

#include "gestionnaire.h"
#include <vector>

 //Constructeur par defaut
Gestionnaire::Gestionnaire()
{

}
//Destructeur
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



//Methode pour ajouter un membre
void Gestionnaire::ajouterMembre(const string& nomMembre)
{
	Membre* membre = new Membre(nomMembre);

	membres_.push_back(membre);
}
//Methode pour ajouter un coupon
void Gestionnaire::ajouterCoupon(const string& code, double rabais, int cout)
{
	Coupon* coupon = new Coupon(code, rabais, cout);

	coupons_.push_back(coupon);
}
//Methode pour trouver un membre
Membre* Gestionnaire::trouverMembre(const string& nomMembre) const
{
	for (int i = 0; i < membres_.size(); i++) {
		// TODO: Faite cette comparaison avec la surcharge de l'operateur == de la classe Membre
		if (*membres_[i] == nomMembre) {
			return membres_[i];
		}
	}
	cout << "Le membre " << nomMembre << " n'existe pas\n";

	return nullptr;
}
//Methode pour assigner un billet
void Gestionnaire::assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon)
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
	membre->ajouterBillet(pnr, prixReel, od, tarif, dateVol);
}
//Methode pour appliquer un coupon
double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	if (membre->getCoupons().size() == 0) {
		cout << "Le membre n'a pas de coupon utilisable\n";
		return 0;
	}
	Coupon* meilleurCoupon = membre->getCoupons()[0];
	for (int i = 1; i < membre->getCoupons().size(); i++) {
		// TODO: Faites cette comparaison par la surcharge de l'operateur > de la classe Coupon
		if (*(membre->getCoupons()[i]) > * meilleurCoupon) {
			meilleurCoupon = membre->getCoupons()[i];
		}
	}

	// TODO: Utiliser la surcharge de l'operateur -= de la classe Membre plutot qu'utiliser la methode retirerCoupon
	*membre -= meilleurCoupon;

	return prix * meilleurCoupon->getRabais();
}
//Methode pour acheter un coupon
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

	Coupon* meilleurCoupon = nullptr;

	for (int i = 0; i < coupons_.size(); i++) {
		if (membre->getPoints() >= coupons_[i]->getCout()) {
			// Si on avait pas encore trouve de meilleur coupon, on fait la premiere assignation
			if (meilleurCoupon == nullptr) {
				meilleurCoupon = coupons_[i];
			}
			// Sinon on compare si le coupon courant a un rabais superieur au meilleur coupon
			// TODO: Faites cette comparaison avec la surcharge de l'operateur > de la classe Coupon
			else if (*coupons_[i] > * meilleurCoupon) {
				meilleurCoupon = coupons_[i];
			}
		}
	}

	if (meilleurCoupon) {
		membre->acheterCoupon(meilleurCoupon);
	}
	else {
		cout << "Le membre ne peut acheter de coupon\n";
	}
}

//Surcharge de operateur << pour afficher les infos
ostream& operator << (ostream& os, const Gestionnaire& gestionnaire)
{
	os << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";
	for (int i = 0; i < gestionnaire.membres_.size(); i++) {
		os << *gestionnaire.membres_[i] << endl;
	}
	return os;
}

