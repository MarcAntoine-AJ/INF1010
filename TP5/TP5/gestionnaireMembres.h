#pragma once
/********************************************
* Titre: Travail pratique #5 - gestionnaireMembres.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#ifndef GESTIONNAIREMEMBRES_H
#define	GESTIONNAIREMEMBRES_H

#include <vector>

#include "membrePremium.h"
#include "solde.h"
#include "gestionnaireGenerique.h"
#include "foncteur.h"

class GestionnaireMembres : public GestionnaireGenerique<pair<string, Membre*>, map<string, Membre*>, AjouterMembre> {
public:
	void assignerBillet(Billet* billet, const string& nomMembre, int rabaisCoupon);
	double calculerRevenu() const;

	int calculerNombreBilletsEnSolde() const;
	//Getters
	Billet* getBilletMin(string nomMembre) const;

	Billet* getBilletMax(string nomMembre) const;

	vector<Billet*>trouverBilletParIntervallle(Membre* membre, double prixInf, double prixSup) const;

	void afficher(ostream& o) const;
};
#endif // !GESTIONNAIREMEMBRES_H



