/*
* Titre : solde.h - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

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
	virtual double getPrixBase()= 0 ;

	// Setter
	void setPourcentageSolde(double pourcentageSolde);
protected:
	double pourcentageSolde_;
};
#endif // !SOLDE_H