/********************************************
* Titre: Travail pratique #5 - solde.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#ifndef SOLDE_H
#define SOLDE_H

using namespace std;

class Solde {
public:
	// Constructeurs
	Solde(double pourcentageSolde);
	virtual ~Solde();

	// Getter
	double getPourcentageSolde() const;
	virtual double getPrixBase() const = 0;

	// Setter
	void setPourcentageSolde(double pourcentageSolde);
protected:
	double pourcentageSolde_;
};
#endif // !SOLDE_H