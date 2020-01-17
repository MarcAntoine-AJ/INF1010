/********************************************
* Titre: Travail pratique #5 - membre.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#ifndef MEMBRE_H
#define MEMBRE_H

#include <string>
#include <vector>
#include <iterator> 
#include <iomanip>

#include "flightPass.h"
#include "billetRegulier.h"
#include "coupon.h"

using namespace std;

class Membre {
public:
	// Constructeurs
	Membre();
	Membre(const string& nom);
	Membre(const Membre& membre);

	virtual ~Membre();

	// Getters
	string getNom() const;

	vector<Billet*> getBillets() const;

	// Setters
	void setNom(const string& nom);


	vector<Billet*>::iterator trouverBillet(const string& pnr);



	void utiliserBillet(const string& pnr);
	virtual void ajouterBillet(Billet* billet);

	bool operator==(const string& nomMembre) const;
	friend bool operator==(const string& nomMembre, const Membre& membre);

	Membre& operator=(const Membre& membre);

	virtual void afficher(ostream& o) const;
protected:
	string nom_;
	vector<Billet*> billets_;
};
#endif // !MEMBRE_H
