/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include <string>
#include <iostream>
#include <vector>
#include "debogageMemoire.hpp"
#include "gestionnaire.h"
using namespace std;

int main() {
	initDebogageMemoire();

	vector<bool> tests;


	// TESTS
	Billet* b1 = new Billet();
	Billet* b2 = new Billet("A1A1A1", "Fred", 3000, "YUL - CDG", TarifBillet::Premiere, Billet_Base);

	//Membre * m1 = new Membre();
	Membre* m2 = new Membre("John", Membre_Occasionnel);
	MembrePremium* mp1 = new MembrePremium("Alex");

	MembreRegulier* mr1 = new MembreRegulier("Marc", Membre_Regulier);

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
	* Tests Coupon
	*/
	// Test 2: operateur >
	tests.push_back(*c3 > * c2
		&& *c2 > * c1
		&& !(*c1 > * c2)
		&& !(*c2 > * c3));

	// Test 3: operateur <
	tests.push_back(*c1 < *c2
		&& *c2 < *c3
		&& !(*c3 < *c2)
		&& !(*c2 < *c1));

	/*
	* Tests Membre
	*/
	// Test 4 - 5 - 6: initialisation de membre regulier
	tests.push_back(mr1->getCoupons().size() == 0
		&& mr1->getBillets().size() == 0);
	tests.push_back(mr1->getNom() == "Marc");
	tests.push_back(mr1->getTypeMembre() == Membre_Regulier);

	//test 7-8-9 initialisation de membre premium
	tests.push_back(mp1->getNom() == "Alex");
	tests.push_back(mp1->getTypeMembre() == Membre_Premium);
	tests.push_back(mp1->getCoupons().size() == 0
		&& mp1->getBillets().size() == 0);

	// Tests 10: Modifier points
	mr1->modifierPoints(150);
	mr1->modifierPoints(20);
	mr1->modifierPoints(-50);

	tests.push_back(mr1->getPoints() == 120);
	mr1->modifierPoints(-120);

	// Tests 11 - 12: calculer points
	b1->setTarif(TarifBillet::Economie);
	b1->setPrix(1000);

	tests.push_back(mr1->calculerPoints(b1) == 100
		&& mr1->calculerPoints(b2) == 600);

	b1->setTarif(TarifBillet::PremiumEconomie);
	b2->setTarif(TarifBillet::Affaire);

	tests.push_back(mr1->calculerPoints(b1) == 150
		&& mr1->calculerPoints(b2) == 450);

	// Tests 13 - 14 - 15: Ajouter billets Membre Regulier
	mr1->ajouterBillet("A1B2C3", 3000, "YUL - YYZ", TarifBillet::Premiere, Billet_Regulier, "2019-12-21");
	tests.push_back(mr1->getBillets().size() == 1
		&& mr1->getBillets()[0]->getNomPassager() == "Marc"
		&& mr1->getPoints() == 600);

	mr1->ajouterBillet("D4E5F6", 1000, "YUL - YVR", TarifBillet::Affaire, Flight_Pass, "2019-12-21");
	tests.push_back(mr1->getBillets().size() == 2);

	mr1->ajouterBillet("H7I8J9", 1500, "YUL - LGA", TarifBillet::PremiumEconomie, Billet_Regulier, "2019-12-21");
	tests.push_back(mr1->getBillets().size() == 3
		&& mr1->getPoints() == 1050);

	//Test 16 17 18 ajouter Billets Membre Premium
	mp1->ajouterBillet("csd22", 3000, "YUL - YYZ", TarifBillet::Premiere, Billet_Regulier, "2019-12-21");
	tests.push_back(mp1->getBillets().size() == 1
		&& mp1->getBillets()[0]->getNomPassager() == "Alex"
		&& mp1->getPoints() == 600
		&& mp1->getpointsCumulee() == 600);

	mp1->ajouterBillet("vbrbb", 1000, "YUL - YVR", TarifBillet::Affaire, Flight_Pass, "2019-12-21");
	tests.push_back(mp1->getBillets().size() == 2 && mp1->getpointsCumulee() == mp1->getPoints());

	mp1->ajouterBillet("H7I8Jcv9", 1500, "YUL - LGA", TarifBillet::PremiumEconomie, Billet_Regulier, "2019-12-21");
	tests.push_back(mp1->getBillets().size() == 3
		&& mp1->getPoints() == 1050 && mp1->getpointsCumulee() == 1050);

	//Test 19-20 utilisee billets flight Pass
	for (int i = 0; i < 8; i++) {
		mp1->utiliserBillet("vbrbb");
	}
	mp1->utiliserBillet("vbrbb");

	tests.push_back(mp1->getBillets().size() == 3);

	mp1->utiliserBillet("vbrbb");
	tests.push_back(mp1->getBillets().size() == 2);

	//Test 21 utilisee billets regulier
	mp1->utiliserBillet("csd22");
	tests.push_back(mp1->getBillets().size() == 1);



	// Tests 22 - 23 - 24: Operateur +=
	tests.push_back(&(*mr1 += c1) == mr1);

	*mr1 += c2;
	tests.push_back(mr1->getCoupons().size() == 2);

	*mr1 += c1;
	tests.push_back(mr1->getCoupons().size() == 3);

	// Tests 25 - 26 - 27: Operateur -=
	tests.push_back(&(*mr1 -= c2) == mr1);
	tests.push_back(mr1->getCoupons().size() == 2
		&& mr1->getCoupons()[0] == c1
		&& mr1->getCoupons()[1] == c1);

	*mr1 -= c1;
	*mr1 += c2;
	tests.push_back(mr1->getCoupons().size() == 2
		&& mr1->getCoupons()[0] == c1
		&& mr1->getCoupons()[1] == c2);

	// Tests 28 - 29 - 30 : Acheter coupon Membre regulier
	// Pas assez de points
	mr1->acheterCoupon(c3);

	tests.push_back(mr1->getPoints() == 1050
		&& mr1->getCoupons().size() == 2);

	// Achat de c1 et c2
	mr1->modifierPoints(500);
	mr1->acheterCoupon(c2);
	tests.push_back(mr1->getPoints() == 650
		&& mr1->getCoupons().size() == 3
		&& mr1->getCoupons()[2] == c2);

	mr1->acheterCoupon(c1);
	tests.push_back(mr1->getPoints() == 150
		&& mr1->getCoupons().size() == 4
		&& mr1->getCoupons()[3] == c1);

	//test 30-31 acheter coupons Membre Premium
	mp1->acheterCoupon(c3);
	tests.push_back(mp1->getCoupons().size() == 0);


	mp1->modifierPoints(632);
	mp1->acheterCoupon(c3);
	tests.push_back(mp1->getCoupons().size() == 1 && mp1->getPoints() == 11);

	// Tests 32 - 33: Operateur == 
	tests.push_back(*mr1 == "Marc"
		&& *m2 == "John"
		&& !(*mr1 == "John")
		&& !(*m2 == "Marc"));

	tests.push_back("Marc" == *mr1
		&& "John" == *m2
		&& !("Marc" == *m2)
		&& !("John" == *mr1));

	/*
	* Tests Gestionnaire
	*/

	// Testss 34: Initialisation Regulier
	tests.push_back(g->getCoupons().size() == 0
		&& g->getMembres().size() == 0);

	// Tests 35 - 36: Ajouter membre
	g->ajouterMembre("Marc", Membre_Regulier);
	g->ajouterMembre("John", Membre_Regulier);

	tests.push_back(g->getMembres().size() == 2);

	g->ajouterMembre("Robert", Membre_Regulier);

	tests.push_back(g->getMembres().size() == 3 && g->getMembres()[2]->getTypeMembre() == Membre_Regulier);

	//Tests 37 : ajouter Membre Premium
	g->ajouterMembre("Alex", Membre_Premium);
	tests.push_back(g->getMembres().size() == 4 && g->getMembres()[3]->getTypeMembre() == Membre_Premium);

	// Tests 38 - 39: Ajouter coupon
	g->ajouterCoupon("5%", 0.05, 500);
	g->ajouterCoupon("10%", 0.1, 900);

	tests.push_back(g->getCoupons().size() == 2);

	g->ajouterCoupon("20%", 0.2, 1700);

	tests.push_back(g->getCoupons().size() == 3);

	// Tests 40: Trouver membre
	tests.push_back(g->trouverMembre("John") != nullptr
		&& g->trouverMembre("ccc") == nullptr);

	// Tests 41 - 42: Acheter coupon Membre Regulier
	MembreRegulier* marc = static_cast<MembreRegulier*>(g->getMembres()[0]);
	MembreRegulier* john = static_cast<MembreRegulier*>(g->getMembres()[1]);
	MembrePremium* alex = static_cast<MembrePremium*>(g->getMembres()[3]);

	marc->modifierPoints(1000);
	g->acheterCoupon("John");
	g->acheterCoupon("Marc");

	tests.push_back(john->getCoupons().size() == 0
		&& john->getPoints() == 0
		&& marc->getCoupons().size() == 1
		&& marc->getCoupons()[0]->getCode() == "10%"
		&& marc->getPoints() == 100);

	marc->modifierPoints(2900);
	g->acheterCoupon("Marc");

	tests.push_back(marc->getCoupons().size() == 2
		&& marc->getCoupons()[1]->getCode() == "20%"
		&& marc->getPoints() == 1300);

	//Tests 43 : Acheter coupon Membre Premium
	alex->modifierPoints(950);
	alex->modifierPointsCumules(950);
	g->acheterCoupon("Alex");

	tests.push_back(alex->getCoupons().size() == 1
		&& alex->getPoints() == 59
		&& alex->getCoupons()[0]->getCode() == "10%");

	alex->modifierPoints(-59);
	alex->modifierPointsCumules(-950);
	*alex -= g->getCoupons()[1];

	// Tests  44 - 45: Assigner billet avec billet Regulier:
	g->assignerBillet("John", "A1B2C3", 1000, "YUL - YYZ", TarifBillet::PremiumEconomie, "2019-12-21", true, Billet_Regulier);
	g->assignerBillet("Marc", "D4E5F6", 2000, "YUL - YYZ", TarifBillet::Affaire, "2019-12-21", false, Billet_Regulier);
	g->assignerBillet("Marc", "H7I8J9", 2000, "YUL - YYZ", TarifBillet::Affaire, "2019-12-21", true, Billet_Regulier);

	tests.push_back(john->getBillets().size() == 1
		&& john->getBillets()[0]->getPrix() == 1000
		&& john->getBillets()[0]->getNomPassager() == "John"
		&& john->getPoints() == 150);
	tests.push_back(marc->getBillets().size() == 2
		&& marc->getBillets()[0]->getPrix() == 2000
		&& marc->getBillets()[0]->getNomPassager() == "Marc"
		&& marc->getBillets()[1]->getPrix() == 1600
		&& marc->getPoints() == 1960
		&& marc->getCoupons().size() == 1);

	//test 46-47: Assigner billet avec flightPass
	g->assignerBillet("John", "f1", 1000, "YUL - YYZ", TarifBillet::PremiumEconomie, "2019-12-21", true, Flight_Pass);
	g->assignerBillet("Marc", "f2", 2000, "YUL - YYZ", TarifBillet::Affaire, "2019-12-21", false, Flight_Pass);
	g->assignerBillet("Marc", "f3", 2000, "YUL - YYZ", TarifBillet::Affaire, "2019-12-21", true, Flight_Pass);

	tests.push_back(john->getBillets().size() == 2
		&& john->getBillets()[1]->getPrix() == 10000
		&& john->getBillets()[1]->getNomPassager() == "John"
		&& john->getPoints() == 1200);
	tests.push_back(marc->getBillets().size() == 4
		&& marc->getBillets()[2]->getPrix() == 20000
		&& marc->getBillets()[2]->getNomPassager() == "Marc"
		&& marc->getBillets()[3]->getPrix() == 18000
		&& marc->getPoints() == 6060
		&& marc->getCoupons().size() == 0);

	//test 48-49: Assigner billet avec membre Premium
	g->assignerBillet("Alex", "f1", 1000, "YUL - YYZ", TarifBillet::PremiumEconomie, "2019-12-21", true, Flight_Pass);

	alex->acheterCoupon(c2);

	g->assignerBillet("Alex", "A1B2C3", 1000, "YUL - YYZ", TarifBillet::PremiumEconomie, "2019-12-21", true, Billet_Regulier);

	tests.push_back(alex->getBillets().size() == 2
		&& alex->getBillets()[0]->getPrix() == 10000
		&& alex->getBillets()[0]->getTypeBillet() == Flight_Pass
		&& alex->getBillets()[1]->getTypeBillet() == Billet_Regulier
		&& alex->getPoints() == 299
		&& alex->getpointsCumulee() == 1189
		&& alex->getCoupons().size() == 0);


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

	cout << endl;
	//// Affichage du programme
	cout << *g;

	// Liberation de la memoire
	delete b1;
	delete b2;

	delete mp1;
	delete mr1;
	delete m2;

	delete c1;
	delete c2;
	delete c3;

	delete g;

	return 0;
}