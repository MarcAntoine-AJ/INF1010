/*
* Titre : membre.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "membre.h"
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

// TODO
//Constructeur par copies
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_)
{
	for (size_t i = 0; i < membre.billets_.size(); ++i) {
		billets_.push_back(membre.billets_[i]->clone());
	}
}
//Destructeur
Membre::~Membre()
{
	for (size_t i = 0; i < billets_.size(); ++i) {
		delete billets_[i];
	}
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

//Setter
void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

// TODO
//Méthode pour utiliser un billet
void Membre::utiliserBillet(const string& pnr)
{
	int indexTrouve = -1;
	for (size_t i = 0; i < billets_.size(); ++i) {
		if (billets_[i]->getPnr() == pnr) {
			indexTrouve = i;
			break;
		}
	}

	if (indexTrouve == -1) {
		cout << "Le billet n'est pas trouve" << endl;
		return;
	}

	if (dynamic_cast<FlightPass*> (billets_[indexTrouve])) {

		dynamic_cast<FlightPass*> (billets_[indexTrouve])->decrementeNbUtilisations();
		if (dynamic_cast<FlightPass*> (billets_[indexTrouve])->getNbUtilisationsRestante() > 0) {
			return;
		}
	}

	delete billets_[indexTrouve];
	billets_[indexTrouve] = billets_[billets_.size() - 1];
	billets_.pop_back();
}
//Méthode pour ajouter un billet
void Membre::ajouterBillet(Billet* billet)
{
	billet->setNomPassager(nom_);
	billets_.push_back(billet);
}
//Opérateurs
bool Membre::operator==(const string& nomMembre) const
{
	return nom_ == nomMembre;
}

bool operator==(const string& nomMembre, const Membre& membre)
{
	return nomMembre == membre.nom_;
}

// TODO
Membre& Membre::operator=(const Membre& membre)
{
	if (this != &membre) {
		nom_ = membre.nom_;

		for (size_t i = 0; i < billets_.size(); ++i) {
			delete billets_[i];
		}

		billets_.clear();

		for (size_t i = 0; i < membre.billets_.size(); ++i) {
			billets_.push_back(membre.billets_[i]->clone());
		}
	}

	return *this;
}


// TODO
//Méthode d'Affichage
void Membre::afficher(ostream& o) const
{
	o << setfill(' ');
	o << "- Membre " << nom_ << ":" << endl;
	o << "\t" << "- Billets :" << endl;

	for (size_t i = 0; i < billets_.size(); i++)
	{
		billets_[i]->afficher(o);

	}
}