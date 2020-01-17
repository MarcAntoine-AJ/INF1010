/********************************************
* Titre: Travail pratique #5 - membre.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "membre.h"
#include <algorithm>
//Constructeur par défaut
Membre::Membre() :
	nom_("")
{
}
//Constructeur par paramètres
Membre::Membre(const string& nom) :
	nom_(nom)
{
}

//Constructeur par copies
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_)
{
	transform(membre.billets_.begin(), membre.billets_.end(), billets_.begin(), [](Billet* billet) {
		return billet->clone();
		});




}

//Destructeur
Membre::~Membre()
{
	for_each(billets_.begin(), billets_.end(), [](Billet* billet) { delete billet; });
}
//Getters
string Membre::getNom() const
{
	return nom_;
}

vector<Billet*> Membre::getBillets() const
{
	return billets_;
}
//Setters
void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

//Fonction pour trouver un billet
vector<Billet*>::iterator Membre::trouverBillet(const string& pnr)
{
	auto it = find_if(billets_.begin(), billets_.end(), [&pnr](Billet* billet)->bool {
		return billet->getPnr() == pnr;
		}
	);
	return it;
}


//Fonction pour utiliser un billet
void Membre::utiliserBillet(const string& pnr)
{
	auto it = trouverBillet(pnr);
	if (it == billets_.end())
	{
		cout << "Le billet n'est pas trouve" << endl;
		return;
	}

	if (auto flightPass = dynamic_cast<FlightPass*>(*it)) {
		flightPass->decrementeNbUtilisations();
		if (flightPass->getNbUtilisationsRestante() > 0) {
			return;
		}
	}
	delete* it;
	billets_.erase(it);
}
//Fonction qui ajouter un billet
void Membre::ajouterBillet(Billet* billet)
{
	billet->setNomPassager(nom_);
	billets_.push_back(billet);
}
//Opérateur d'égalité
bool Membre::operator==(const string& nomMembre) const
{
	return nom_ == nomMembre;
}
//Opérateur d'égalité
bool operator==(const string& nomMembre, const Membre& membre)
{
	return nomMembre == membre.nom_;
}


//Opérateur d'affectation
Membre& Membre::operator=(const Membre& membre)
{
	if (this != &membre) {
		nom_ = membre.nom_;

		for_each(billets_.begin(), billets_.end(), [](Billet* billet) { delete billet; });

		billets_.clear();

		transform(membre.billets_.begin(), membre.billets_.end(), billets_.begin(), [](Billet* billet) {
			return billet->clone();
			});


	}

	return *this;
}


//Fonction d'affichage
void Membre::afficher(ostream& o) const
{
	o << setfill(' ');
	o << "- Membre " << nom_ << ":" << endl;
	o << "\t" << "- Billets :" << endl;
	copy(billets_.begin(), billets_.end(), ostream_iterator<Billet*>(o));
}