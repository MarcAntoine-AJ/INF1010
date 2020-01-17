/*
* Titre : gestionnaire.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "gestionnaire.h"

//Constructeur par défaut
Gestionnaire::Gestionnaire()
{
}
//Destructeur
Gestionnaire::~Gestionnaire()
{
	for (size_t i = 0; i < membres_.size(); ++i) {
		delete membres_[i];
	}

	for (size_t i = 0; i < coupons_.size(); ++i) {
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

void Gestionnaire::ajouterMembre(Membre* membre)
{
	membres_.push_back(membre);
}

void Gestionnaire::ajouterCoupon(Coupon* coupon)
{
	coupons_.push_back(coupon);
}
//Méthode pour trouver un membre
Membre* Gestionnaire::trouverMembre(const string& nomMembre) const
{
	for (size_t i = 0; i < membres_.size(); ++i) {
		if (*membres_[i] == nomMembre) {
			return membres_[i];
		}
	}
	cout << "Le membre " << nomMembre << " n'existe pas\n";

	return nullptr;
}

// TODO
//Méthode pour assigner un billet
void Gestionnaire::assignerBillet(Billet* billet, const string& nomMembre, bool utiliserCoupon)
{
	Membre* membre = trouverMembre(nomMembre);
	double prix = 0;
	if (membre == nullptr) {
		delete billet;
		return;
	}
	if (dynamic_cast<Solde*> (billet))
	{
		prix = dynamic_cast<Solde*> (billet)->getPrixBase();
	}
	else
	{
		prix = billet->getPrix();
	}


	if (utiliserCoupon)
	{
		prix -= appliquerCoupon(membre, prix);
	}


	if (dynamic_cast <MembrePremium*>(membre))
	{
		double rabais = 0.005 * dynamic_cast<MembrePremium*>(membre)->getpointsCumulee() / 1000;
		if (rabais > 0.1)
			rabais = 0.1;

		prix *= (1 - rabais);

	}
	billet->setPrix(prix);
	membre->ajouterBillet(billet);
}
//Méthode pour appliquer un coupon
double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
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

	Coupon* meilleurCoupon = nullptr;

	if (auto membreRegulier = dynamic_cast<MembreRegulier*>(membre)) {
		for (size_t i = 0; i < coupons_.size(); ++i) {
			if (membreRegulier->peutAcheterCoupon(coupons_[i])) {
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

// TODO
//Méthode pour calculer le revenu
double Gestionnaire::calculerRevenu() const
{
	double somme = 0;
	for (int i = 0; i < membres_.size(); i++)
	{
		for (int j = 0; j < membres_[i]->getBillets().size(); j++)
		{
			somme = somme + membres_[i]->getBillets()[j]->getPrix();
		}
	}

	return somme;
}

// TODO
//Méthode pour calculer le nombre de billets en solde
int Gestionnaire::calculerNombreBilletsEnSolde() const
{
	int nombreBilletSolde = 0;

	for (int i = 0; i < membres_.size(); i++)
	{
		for (int j = 0; j < membres_[i]->getBillets().size(); j++)
		{

			if (dynamic_cast<Solde*>(membres_[i]->getBillets()[j]))
			{
				nombreBilletSolde++;
			}
		}
	}

	return nombreBilletSolde;
}

// TODO
//Méthode d'affichage
void Gestionnaire::afficher(ostream& o) const
{
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";

	for (int i = 0; i < membres_.size(); ++i) {
		membres_[i]->afficher(o);
	}
}