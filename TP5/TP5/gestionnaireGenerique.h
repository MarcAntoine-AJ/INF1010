/********************************************
* Titre: Travail pratique #5 - GestionnaireGenerique.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#pragma once

#include <algorithm>
#include "foncteur.h"

using namespace  std;

/*
	class GestionnaireGenerique

	Méthodes :
	C getConteneur() const;
	void ajouter(const T& t);
	int getNombreElements() const;

	Attributs :
	C conteneur_;
*/

/*
	* T   = pair<string, Membre*> ou Coupon*;
	* Conteneur   = map<string, Membre*> ou vector<Coupon*>;
	* FoncteurAjouter = AjouterMembre ou AjouterCoupon


*/
template< typename T, typename C, typename F >
class GestionnaireGenerique
{
public:


	C getConteneur() const;
	void ajouter(const T& t);
	int getNombreElements() const;

protected:
	C conteneur_;
};

//Getter
template< typename T, typename C, typename F >
C GestionnaireGenerique<T, C, F>::getConteneur() const
{
	return conteneur_;

}
//Fonction qui ajoute membre ou coupon
template< typename T, typename C, typename F >
void GestionnaireGenerique<T, C, F>::ajouter(const T& t)
{
	F foncteur(conteneur_);
	foncteur(t);
}
//Getter
template< typename T, typename C, typename F >
int GestionnaireGenerique<T, C, F>::getNombreElements()const
{
	return conteneur_.size();

}