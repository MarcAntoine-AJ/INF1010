/*
 * Date : 1 Septembre 2019
 * Auteur : Wassim Khene
 */

#include <string>
#include <iostream>
#include <vector>
#include "debogageMemoire.hpp"
#include "gestionnaire.h"
using namespace std;

int main() {
	// Pour detecter les fuites de memoire
	initDebogageMemoire();

	// TESTS
	vector<bool> tests;

	Billet* b1 = new Billet();
	Billet* b2 = new Billet("A1A1A1", "Fred", 3000, "YUL - CDG", TarifBillet::Premiere, "2019-12-21");
	

	Membre * m1 = new Membre();
	Membre * m2 = new Membre("John");
	
	Coupon* c1 = new Coupon("5%", 0.05, 500);
	Coupon* c2 = new Coupon("10%", 0.1, 900);
	Coupon* c3 = new Coupon("20%", 0.2, 1700);

	Gestionnaire* g = new Gestionnaire();

	// Tests Billet
	// Test 1: Format tarif
	tests.push_back(b1->formatTarif(TarifBillet::Affaire) == "Affaire"
		&& b1->formatTarif(TarifBillet::Economie) == "Economie"
		&& b1->formatTarif(TarifBillet::Premiere) == "Premiere"
		&& b1->formatTarif(TarifBillet::PremiumEconomie) == "Premium economie");

	/*
	* Tests Membre
	*/
	// Test 2 - 3: initialisation de membre
	tests.push_back(m1->getCapaciteCoupons() == CAPACITE_INITIALE
		&& m1->getCapaciteBillets() == CAPACITE_INITIALE
		&& m2->getCapaciteCoupons() == CAPACITE_INITIALE
		&& m2->getCapaciteBillets() == CAPACITE_INITIALE);
	m1->setNom("Marc");
	tests.push_back(m1->getNom() == "Marc");

	// Tests 4: Modifier points
	m1->modifierPoints(150);
	m1->modifierPoints(20);
	m1->modifierPoints(-50);

	tests.push_back(m1->getPoints() == 120);
	m1->modifierPoints(-120);

	// Tests 5 - 6: Calculer points
	b1->setTarif(TarifBillet::Economie);
	b1->setPrix(1000);

	tests.push_back(m1->calculerPoints(b1) == 100
		&& m1->calculerPoints(b2) == 600);

	b1->setTarif(TarifBillet::PremiumEconomie);
	b2->setTarif(TarifBillet::Affaire);

	tests.push_back(m1->calculerPoints(b1) == 150
		&& m1->calculerPoints(b2) == 450);

	// Tests 7 - 9: Ajouter billets
	m1->ajouterBillet("A1B2C3", 3000, "YUL - YYZ", TarifBillet::Premiere, "2019-12-21");
	tests.push_back(m1->getNbBillets() == 1
		&& m1->getBillets()[0]->getNomPassager() == "Marc"
		&& m1->getPoints() == 600);
	
	m1->ajouterBillet("D4E5F6", 1000, "YUL - YVR", TarifBillet::Affaire, "2019-12-21");
	tests.push_back(m1->getNbBillets() == 2 && m1->getCapaciteBillets() == CAPACITE_INITIALE);

	m1->ajouterBillet("H7I8J9", 1500, "YUL - LGA", TarifBillet::PremiumEconomie, "2019-12-21");
	tests.push_back(m1->getNbBillets() == 3 
		&& m1->getCapaciteBillets() == CAPACITE_INITIALE * 2
		&& m1->getPoints() == 1050);

	// Tests 10 - 11: Ajouter coupons
	m1->ajouterCoupon(c1);
	m1->ajouterCoupon(c2);

	tests.push_back(m1->getNbCoupons() == 2 && m1->getCapaciteCoupons() == CAPACITE_INITIALE);

	m1->ajouterCoupon(c1);

	tests.push_back(m1->getNbCoupons() == 3 && m1->getCapaciteCoupons() == CAPACITE_INITIALE * 2);
	
	// Tests 12 - 13: Retirer coupon
	m1->retirerCoupon(c2);
	tests.push_back(m1->getNbCoupons() == 2
		&& m1->getCoupons()[0] == c1
		&& m1->getCoupons()[1] == c1);

	m1->retirerCoupon(c1);
	m1->ajouterCoupon(c2);
	tests.push_back(m1->getNbCoupons() == 2
		&& m1->getCoupons()[0] == c1
		&& m1->getCoupons()[1] == c2);
	
	// Tests 14 - 16: Acheter coupon

	// Pas assez de points
	m1->acheterCoupon(c3);

	tests.push_back(m1->getPoints() == 1050
		&& m1->getNbCoupons() == 2);

	// Achat de c1 et c2
	m1->modifierPoints(500);
	m1->acheterCoupon(c2);
	tests.push_back(m1->getPoints() == 650
		&& m1->getNbCoupons() == 3
		&& m1->getCoupons()[2] == c2);

	m1->acheterCoupon(c1);
	tests.push_back(m1->getPoints() == 150
		&& m1->getNbCoupons() == 4
		&& m1->getCoupons()[3] == c1);

	/*
	* Tests Gestionnaire
	*/
	
	// Test 17: Initialisation
	 tests.push_back(g->getCapaciteCoupons() == CAPACITE_INITIALE
		&& g->getCapaciteMembres() == CAPACITE_INITIALE);

	// Tests 18 - 19: Ajouter membre
	g->ajouterMembre("Marc");
	g->ajouterMembre("John");

	tests.push_back(g->getNbMembres() == 2
		&& g->getCapaciteMembres() == CAPACITE_INITIALE);

	g->ajouterMembre("Robert");

	tests.push_back(g->getNbMembres() == 3
		&& g->getCapaciteMembres() == CAPACITE_INITIALE * 2);

	// Tests 20 - 21: Ajouter coupon
	g->ajouterCoupon("5%", 0.05, 500);
	g->ajouterCoupon("10%", 0.1, 900);

	tests.push_back(g->getNbCoupons() == 2
		&& g->getCapaciteCoupons() == CAPACITE_INITIALE);

	g->ajouterCoupon("20%", 0.2, 1700);

	tests.push_back(g->getNbCoupons() == 3
		&& g->getCapaciteCoupons() == CAPACITE_INITIALE * 2);

	// Tests 22: Trouver membre
	tests.push_back(g->trouverMembre("John") != nullptr
		&& g->trouverMembre("ccc") == nullptr);

	// Tests 23 - 24: Acheter coupon
	Membre* marc = g->getMembres()[0];
	Membre* john = g->getMembres()[1];

	marc->modifierPoints(1000);
	g->acheterCoupon("John");
	g->acheterCoupon("Marc");

	tests.push_back(john->getNbCoupons() == 0
		&& john->getPoints() == 0
		&& marc->getNbCoupons() == 1
		&& marc->getCoupons()[0]->getCode() == "10%"
		&& marc->getPoints() == 100);

	marc->modifierPoints(2900);
	g->acheterCoupon("Marc");

	tests.push_back(marc->getNbCoupons() == 2
		&& marc->getCoupons()[1]->getCode() == "20%"
		&& marc->getPoints() == 1300);

	// Tests 25 - 26: Assigner billet:
	g->assignerBillet("John", "A1B2C3", 1000, "YUL - YYZ", TarifBillet::PremiumEconomie, "2019-12-21", true);
	g->assignerBillet("Marc", "D4E5F6", 2000, "YUL - YYZ", TarifBillet::Affaire, "2019-12-21", false);
	g->assignerBillet("Marc", "H7I8J9", 2000, "YUL - YYZ", TarifBillet::Affaire, "2019-12-21", true);
	
	tests.push_back(john->getNbBillets() == 1
		&& john->getBillets()[0]->getPrix() == 1000
		&& john->getBillets()[0]->getNomPassager() == "John"
		&& john->getPoints() == 150);
	tests.push_back(marc->getNbBillets() == 2
		&& marc->getBillets()[0]->getPrix() == 2000
		&& marc->getBillets()[0]->getNomPassager() == "Marc"
		&& marc->getBillets()[1]->getPrix() == 1600
		&& marc->getPoints() == 1960
		&& marc->getNbCoupons() == 1);

	// Affichage des tests
	cout << "TESTS" << endl;
	for (unsigned int i = 0; i < tests.size(); i++)
	{
		cout << "\tTest " << setfill('0') << setw(2) << i + 1 << "... ";
		if (tests[i])
			cout << "OK!" << endl;
		else
			cout << "ECHEC" << endl;
	}

	cout << "\n\n";
	// Affichage du programme
	g->afficherInfos();
	
	// Liberation de la memoire
	delete b1;
	delete b2;

	delete m1;
	delete m2;
	
	delete c1;
	delete c2;
	delete c3;

	delete g;
	
	return 0;  
}