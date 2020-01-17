#include <string>
#include <iostream>
#include <vector>
#include "gestionnaire.h"
#include "def.h"
using namespace std;
//Constructeur par défaut 
Gestionnaire::Gestionnaire() 
	: membres_(new Membre*[CAPACITE_INITIALE]),nbMembres_(0),capaciteMembres_(CAPACITE_INITIALE),coupons_(new Coupon*[CAPACITE_INITIALE]),nbCoupons_(0),capaciteCoupons_(CAPACITE_INITIALE)
	
{
	for (int i = 0; i < capaciteMembres_; i++)
	{
		membres_[i] = nullptr;
	}

	for (int i = 0; i < capaciteCoupons_; i++)
	{
		coupons_[i] = nullptr;
	}

}

// Getters
Membre** Gestionnaire ::getMembres() const
{
	return membres_;
}
int Gestionnaire :: getNbMembres() const
{
	return nbMembres_;
}
int Gestionnaire :: getCapaciteMembres() const 
{
	return capaciteMembres_;
}
Coupon** Gestionnaire::getCoupons() const 
{
	return coupons_;
}
int Gestionnaire::getNbCoupons() const 
{
	return nbCoupons_;
}
int Gestionnaire :: getCapaciteCoupons() const
{
	return capaciteCoupons_;
}
//Méthode pour ajouter un membre
void Gestionnaire::ajouterMembre(const string& nomMembre)
{
	bool foundEmptyCase = false;
	Membre* newMembre = new Membre(nomMembre);
	nbMembres_ = nbMembres_ + 1;

	if (nbMembres_ > capaciteMembres_)
	{
		//On modifie la taille du tableau
		Membre** tempMembres = new  Membre * [2 * capaciteMembres_];
		for(int i=0;i< 2 * capaciteMembres_;i++)
		{
			tempMembres[i] = nullptr;
		}
		for (int i = 0; i < capaciteMembres_; i++)
		{
			tempMembres[i] = membres_[i];
		}
		delete[] membres_;
		membres_ = tempMembres;
		capaciteMembres_ = 2 * capaciteMembres_;

	}

	//On ajoute le membre
	membres_[nbMembres_ - 1] = newMembre;
	

}
//On ajoute le coupon
void Gestionnaire::ajouterCoupon(const string& code, double rabais, int cout)
{
	Coupon * newCoupon = new Coupon(code, rabais, cout);
	bool foundEmptyCase = false;
	nbCoupons_ = nbCoupons_ + 1;

	if (nbCoupons_ > capaciteCoupons_)
	{
		//On modifie la taille du tableau
		Coupon** tempCoupons = new  Coupon * [2 * capaciteCoupons_];
		for (int i = 0; i < 2 * capaciteCoupons_; i++)
		{
			tempCoupons[i] = nullptr;
		}
		for (int i = 0; i < capaciteCoupons_; i++)
		{
			tempCoupons[i] = coupons_[i];
		}
		delete[] coupons_;
		coupons_ = tempCoupons;
		capaciteCoupons_ = 2 * capaciteCoupons_;

	}

	//On ajoute le coupon
	coupons_[nbCoupons_ - 1] = newCoupon;



}
//Methode pour trouver un membre
Membre* Gestionnaire::trouverMembre(const string& nomMembre) const 

{
	int indexTrouver=0;
	bool foundMember = false;
	for (int i = 0; (i < capaciteMembres_) & (!foundMember); i++)
		
	{
		
		 
		if(membres_[i]!=nullptr)
		{
			
			if(membres_[i]->getNom() == nomMembre)
	{
		foundMember = true;
		indexTrouver = i;
		
	}
		
		}
	
	}if (foundMember) {
		return membres_[indexTrouver];

	}else
	{
		cout << "Le membre : " << nomMembre << "n'a pas ete trouve" << endl;
	return nullptr;
	}
	
}
//Methode pour assigner un billet

void Gestionnaire ::assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon)
{
	double prix = prixBase;
	Membre* membreAssigner = trouverMembre(nomMembre);
	if(membreAssigner!=nullptr)
	{
	if(utiliserCoupon)
	{
		prix =prix - appliquerCoupon(membreAssigner,prix);
	} 
	
	membreAssigner->ajouterBillet( pnr, prix,  od,  tarif,  dateVol);


}
	}
	
	
	
//Methode pour appliquer le rabais du coupon
double Gestionnaire ::appliquerCoupon(Membre* membre, double prix)
{
	double rabaisPlusHaut = 0;
	int indexCouponAppliquer = 0;
	//On verifie s'il a un coupon
	if(membre->getNbCoupons()==0)
	{
		cout << "Aucun Coupon disponible" << endl;
		return 0;
	}
	//Dans le cas ou il a un coupon
	else {
for (int i=0;i<membre->getCapaciteCoupons();i++)
	{
		if (((membre->getCoupons()[i])->getRabais()) > rabaisPlusHaut) {
			rabaisPlusHaut = (membre->getCoupons()[i])->getRabais();
			indexCouponAppliquer = i;

	}
	}
membre->retirerCoupon(membre->getCoupons()[indexCouponAppliquer]);
	return ( (prix * rabaisPlusHaut));

	}
	
}
//Methode pour acheter un coupon
void Gestionnaire ::acheterCoupon(const string& nomMembre)
{
	double rabaisPlusHaut = 0;
	int indexCoupon = 0;
	bool aucunCoupon = true;
	Membre* membre = trouverMembre(nomMembre);
	if (membre!=nullptr)
	{
	for (int i =0;i<capaciteCoupons_;i++)
	{
		if(coupons_[i]!=nullptr)
		{
			
			if((coupons_[i]->getRabais()>rabaisPlusHaut) & (membre->getPoints()>= coupons_[i]->getCout()))
	{
				aucunCoupon = false;
		rabaisPlusHaut = coupons_[i]->getRabais();
		 indexCoupon = i;
	}
		
		}
	
	}
	
		if(!aucunCoupon)
		{
			membre->acheterCoupon(coupons_[indexCoupon]);
		}else
		{
			cout << "Points insuffisants pour acheter les coupons" << endl;
		}
	}

}
//Methode pour afficher les informations
void Gestionnaire::afficherInfos() const 
{
	for(int i=0;i<capaciteMembres_;i++)
	{
		if (membres_[i] != nullptr) 
		{
membres_[i]->afficherMembre();
		}
		
	}

}
//Destructeur de Gestionnaire
Gestionnaire ::~Gestionnaire()
{
	

	for (int i = 0; i < capaciteMembres_; i++)
	{
		delete membres_[i];
	}

	for (int i = 0; i < capaciteCoupons_; i++)
	{
		delete coupons_[i] ;
	}

    delete[] membres_;
	delete[] coupons_;



}