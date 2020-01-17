/********************************************
* Titre: Travail pratique #5 - foncteur.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/
#pragma once

#include <string>
#include <vector>
#include <map>

#include "coupon.h"
#include "membrePremium.h"

//Foncteur AjouterCoupon
class AjouterCoupon
{
public:
	//Constructeur
	AjouterCoupon(vector<Coupon*>& conteneur) :conteneur_(conteneur)
	{

	}
	//Opérateur ()
	vector<Coupon*>& operator() (Coupon* coupon)
	{
		if (find(conteneur_.begin(), conteneur_.end(), coupon) == conteneur_.end())
		{
			conteneur_.push_back(coupon);
			return conteneur_;
		}
	}

private:
	vector<Coupon*>& conteneur_;
};
//Foncteur AjouterMembre
class AjouterMembre
{
public:
	//Constructeur
	AjouterMembre(map<string, Membre*>& conteneur) : conteneur_(conteneur) {


	}
	//Opérateur()
	map<string, Membre*>& operator() (pair<string, Membre*> membre)
	{
		conteneur_.insert(membre);
		return conteneur_;
	}
private:
	map<string, Membre*>& conteneur_;

};
//Foncteur Intervalle
class IntervallePrixBillet
{
public:
	//Constructeur
	IntervallePrixBillet(double borneInf, double borneSup) : borneInf_(borneInf), borneSup_(borneSup)
	{

	}
	//Opérateur ()
	bool operator() (Billet* billet)
	{
		return (borneInf_ <= billet->getPrix() && billet->getPrix() <= borneSup_);
	}
private:
	double borneInf_;
	double borneSup_;

};