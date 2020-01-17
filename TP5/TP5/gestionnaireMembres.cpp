/********************************************
* Titre: Travail pratique #5 - gestionnaireMembres.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "GestionnaireMembres.h"
#include <numeric>
//Fonction pour assigner un billet
void GestionnaireMembres::assignerBillet(Billet* billet, const string& nomMembre, int rabaisCoupon)
{
	Membre* membre = conteneur_[nomMembre];

	if (membre == nullptr) {
		delete billet;
		return;
	}

	double prix = billet->getPrix();

	if (auto solde = dynamic_cast<Solde*>(billet)) {
		prix = solde->getPrixBase();
	}


	prix -= rabaisCoupon;


	if (auto membrePremium = dynamic_cast<MembrePremium*>(membre)) {
		double rabais = 0.005 * membrePremium->getpointsCumulee() / 1000;
		if (rabais > 0.1)
			rabais = 0.1;

		prix *= (1 - rabais);
	}

	billet->setPrix(prix);
	membre->ajouterBillet(billet);
}
//Retourne le billet minimal
Billet* GestionnaireMembres::getBilletMin(string nomMembre) const
{
	auto it = conteneur_.find(nomMembre);
	vector<Billet*> vecteur = it->second->getBillets();
	auto min = min_element(vecteur.begin(), vecteur.end(), [](Billet* billet1, Billet* billet2)->bool {
		return billet1->getPrix() < billet2->getPrix();
		});
	return *min;
}

//Calcul le revenu
double GestionnaireMembres::calculerRevenu() const
{

	double revenu = 0;

	for_each(conteneur_.begin(), conteneur_.end(), [&revenu](pair<string, Membre*> pair) {
		vector<Billet*> vecteur = pair.second->getBillets();

		for_each(vecteur.begin(), vecteur.end(), [&revenu](Billet* billet)
			{
				if (billet != nullptr) {
					revenu += billet->getPrix();
				}
			});


		});

	return revenu;
}
//Calcul le nombre de billets en solde
int GestionnaireMembres::calculerNombreBilletsEnSolde() const
{

	int nbBilletsSolde = 0;

	for_each(conteneur_.begin(), conteneur_.end(), [&nbBilletsSolde](pair<string, Membre*> pair) {

		vector<Billet*> vecteur = pair.second->getBillets();

		nbBilletsSolde += count_if(vecteur.begin(), vecteur.end(), [](Billet* billet) {

			bool condition = (dynamic_cast<Solde*>(billet) != nullptr);

			return condition;
			});
		});

	return nbBilletsSolde;
}
//Fonction d'affichage
void GestionnaireMembres::afficher(ostream& o) const
{
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";
	for_each(conteneur_.begin(), conteneur_.end(), [&o](pair<string, Membre*> pair)
		{
			pair.second->afficher(o);
		});
}
//Fonction pour trouver les éléments dans l'intervalle
vector<Billet*>GestionnaireMembres::trouverBilletParIntervallle(Membre* membre, double prixInf, double prixSup) const
{
	IntervallePrixBillet foncteur(prixInf, prixSup);
	vector<Billet*> vecteurCopie;
	vector<Billet*> vecteur = membre->getBillets();
	copy_if(vecteur.begin(), vecteur.end(), back_inserter(vecteurCopie), foncteur);
	return vecteurCopie;

}


//Retourne le billet max
Billet* GestionnaireMembres::getBilletMax(string nomMembre) const
{
	auto it = conteneur_.find(nomMembre);
	vector<Billet*> vecteur = it->second->getBillets();
	auto max = max_element(vecteur.begin(), vecteur.end(), [](Billet* billet1, Billet* billet2) -> bool {
		return billet1->getPrix() < billet2->getPrix();
		});
	return *max;
}
