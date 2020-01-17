/********************************************
* Titre: Travail pratique #5 - main.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include <string>
#include <iostream>
#include <vector>
#include "gestionnaireCoupons.h"
#include "gestionnaireMembres.h"
#include "flightPassSolde.h"
#include "billetRegulierSolde.h"

using namespace std;

int main() {

	vector<bool> tests;

	// TESTS
	Billet* b1 = new BilletRegulier("B4Y6S1", 2000, "YUL - LGA", TarifBillet::Premiere, "2019-12-21");
	Billet* b2 = new BilletRegulier("A1A1A1", 3000, "YUL - CDG", TarifBillet::Premiere, "2019-12-21");
	Billet* brs1 = new BilletRegulierSolde("O8I9P0", 2500, "YUL - LGA", TarifBillet::PremiumEconomie, "2019-12-21", 0.5);
	Billet* fps1 = new FlightPassSolde("HH6T3R", 25000, "YUL - LGA", TarifBillet::PremiumEconomie, 0.25);

	//Membre * m1 = new Membre();
	Membre * m2 = new Membre("John");
	MembrePremium* mp1 = new MembrePremium("Alex");

	MembreRegulier* mr1 = new MembreRegulier("Marc");

	Coupon* c1 = new Coupon("5%", 0.05, 500);
	Coupon* c2 = new Coupon("10%", 0.1, 900);
	Coupon* c3 = new Coupon("20%", 0.2, 1700);

	GestionnaireCoupons* g_coupons = new GestionnaireCoupons();
	GestionnaireMembres* g_membres = new GestionnaireMembres();

	// Tests Billet
	// Test 1: Format tarif
	tests.push_back(b1->formatTarif(TarifBillet::Affaire) == "Affaire"
		&& b1->formatTarif(TarifBillet::Economie) == "Economie"
		&& b1->formatTarif(TarifBillet::Premiere) == "Premiere"
		&& b1->formatTarif(TarifBillet::PremiumEconomie) == "Premium economie");

	// Test 2-3: getPrix()
	tests.push_back(brs1->getPrix() == 2500 * (1 - 0.5));
	tests.push_back(fps1->getPrix() == 25000 * (1 - 0.25));

	// Test 4-5: clone()
	Billet* brs2 = brs1->clone();
	tests.push_back(typeid(*brs2) == typeid(BilletRegulierSolde));

	Billet* fps2 = fps1->clone();
	tests.push_back(typeid(*fps2) == typeid(FlightPassSolde));

	/*
	* Tests Coupon
	*/
	// Test 6: operateur >
	tests.push_back(*c3 > *c2
		&& *c2 > *c1
		&& !(*c1 > *c2)
		&& !(*c2 > *c3));

	// Test 7: operateur <
	tests.push_back(*c1 < *c2
		&& *c2 < *c3
		&& !(*c3 < *c2)
		&& !(*c2 < *c1));

	/*
	* Tests Membre
	*/
	// Test 8-9-10: initialisation de membre regulier
	tests.push_back(mr1->getCoupons().size() == 0
		&& mr1->getBillets().size() == 0);
	tests.push_back(mr1->getNom() == "Marc");
	tests.push_back(typeid(*mr1) == typeid(MembreRegulier));

	// Test 11-12-13: initialisation de membre premium
	tests.push_back(mp1->getNom() == "Alex");
	tests.push_back(typeid(*mp1) == typeid(MembrePremium));
	tests.push_back(mp1->getCoupons().size() == 0
		&& mp1->getBillets().size() == 0);

	// Test 14: Modifier points
	mr1->modifierPoints(150);
	mr1->modifierPoints(20);
	mr1->modifierPoints(-50);

	tests.push_back(mr1->getPoints() == 120);


	mr1->modifierPoints(-120);

	// Test 15-16: calculer points
	b1->setTarif(TarifBillet::Economie);
	b1->setPrix(1000);

	tests.push_back(mr1->calculerPoints(b1) == 100
		&& mr1->calculerPoints(b2) == 600);

	b1->setTarif(TarifBillet::PremiumEconomie);
	b2->setTarif(TarifBillet::Affaire);

	tests.push_back(mr1->calculerPoints(b1) == 150
		&& mr1->calculerPoints(b2) == 450);

	// Test 17-18-19-20-21: Ajouter billets Membre Regulier
	mr1->ajouterBillet(new BilletRegulier("A1B2C3", 3000, "YUL - YYZ", TarifBillet::Premiere, "2019-12-21"));
	tests.push_back(mr1->getBillets().size() == 1
		&& mr1->getBillets()[0]->getNomPassager() == "Marc"
		&& mr1->getPoints() == 600);

	mr1->ajouterBillet(new FlightPass("D4E5F6", 1000, "YUL - YVR", TarifBillet::Affaire));
	tests.push_back(mr1->getBillets().size() == 2);

	mr1->ajouterBillet(new BilletRegulier("H7I8J9", 1500, "YUL - LGA", TarifBillet::PremiumEconomie, "2019-12-21"));
	tests.push_back(mr1->getBillets().size() == 3
		&& mr1->getPoints() == 1050);

	mr1->ajouterBillet(new FlightPassSolde("A6V3F4", 4000, "YUL - YVR", TarifBillet::Affaire, 0.2));
	tests.push_back(mr1->getBillets().size() == 4
		&& mr1->getPoints() == 1520);

	mr1->ajouterBillet(new BilletRegulierSolde("G7T5E3", 850, "YUL - YVR", TarifBillet::Economie, "2019-12-21", 0.1));
	tests.push_back(mr1->getBillets().size() == 5
		&& mr1->getPoints() == 1596);

	mr1->modifierPoints(-546);

	// Test 22-23-24-25-26: ajouter Billets Membre Premium
	mp1->ajouterBillet(new BilletRegulier("csd22", 3000, "YUL - YYZ", TarifBillet::Premiere, "2019-12-21"));
	tests.push_back(mp1->getBillets().size() == 1
		&& mp1->getBillets()[0]->getNomPassager() == "Alex"
		&& mp1->getPoints() == 600
		&& mp1->getpointsCumulee() == 600);

	mp1->ajouterBillet(new FlightPass("vbrbb", 1000, "YUL - YVR", TarifBillet::Affaire));
	tests.push_back(mp1->getBillets().size() == 2 && mp1->getpointsCumulee() == mp1->getPoints());

	mp1->ajouterBillet(new BilletRegulier("H7I8Jcv9", 1500, "YUL - LGA", TarifBillet::PremiumEconomie, "2019-12-21"));
	tests.push_back(mp1->getBillets().size() == 3
		&& mp1->getPoints() == 1050 && mp1->getpointsCumulee() == 1050);

	mp1->ajouterBillet(new FlightPassSolde("B9O7R3", 6500, "YUL - YVR", TarifBillet::Affaire, 0.25));
	tests.push_back(mp1->getBillets().size() == 4
		&& mp1->getPoints() == 1687 && mp1->getpointsCumulee() == 1687);

	mp1->ajouterBillet(new BilletRegulierSolde("D2R5T1", 750, "YUL - YVR", TarifBillet::Economie, "2019-12-21", 0.2));
	tests.push_back(mp1->getBillets().size() == 5
		&& mp1->getPoints() == 1747 && mp1->getpointsCumulee() == 1747);

	mp1->modifierPoints(-697);
	mp1->modifierPointsCumulee(-697);


	// Test 27-28 utilisee billets flight Pass
	for (int i = 0; i < 8; i++) {
		mp1->utiliserBillet("B9O7R3");
	}
	mp1->utiliserBillet("B9O7R3");

	tests.push_back(mp1->getBillets().size() == 5);

	mp1->utiliserBillet("B9O7R3");
	tests.push_back(mp1->getBillets().size() == 4);

	// Test 29 utilisee billets regulier solde
	mp1->utiliserBillet("D2R5T1");
	tests.push_back(mp1->getBillets().size() == 3);

	// Tests 30-31-32: Operateur +=
	tests.push_back(&(*mr1 += c1) == mr1);

	*mr1 += c2;
	tests.push_back(mr1->getCoupons().size() == 2);

	*mr1 += c1;
	tests.push_back(mr1->getCoupons().size() == 3);

	// Test 33-34-35: Operateur -=
	tests.push_back(&(*mr1 -= c2) == mr1);
	tests.push_back(mr1->getCoupons().size() == 2
		&& mr1->getCoupons()[0] == c1
		&& mr1->getCoupons()[1] == c1);

	*mr1 -= c1;
	*mr1 += c2;
	tests.push_back(mr1->getCoupons().size() == 2
		&& mr1->getCoupons()[0] == c1
		&& mr1->getCoupons()[1] == c2);

	// Test 36-37-38 : Acheter coupon Membre regulier
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

	// Test 39-40 acheter coupons Membre Premium
	mp1->acheterCoupon(c3);
	tests.push_back(mp1->getCoupons().size() == 0);


	mp1->modifierPoints(632);
	mp1->modifierPointsCumulee(632);
	mp1->acheterCoupon(c3);
	tests.push_back(mp1->getCoupons().size() == 1 && mp1->getPoints() == 11);

	// Test 41-42: Operateur == 
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

	// Test 43: Initialisation Regulier
	tests.push_back(g_coupons->getConteneur().size() == 0
		&& g_membres->getConteneur().size() == 0);

	// Test 44-45: Ajouter membre
	MembreRegulier* marcRegulier = new MembreRegulier("Marc");
	MembreRegulier* johnRegulier = new MembreRegulier("John");
	MembreRegulier* robertRegulier = new MembreRegulier("Robert");
	MembrePremium* alexPremium = new MembrePremium("Alex");
	g_membres->ajouter(make_pair(marcRegulier->getNom(),marcRegulier));
	g_membres->ajouter(make_pair(johnRegulier->getNom(), johnRegulier));

	tests.push_back(g_membres->getConteneur().size() == 2);

	g_membres->ajouter(make_pair(robertRegulier->getNom(), robertRegulier));

	tests.push_back(g_membres->getConteneur().size() == 3 && typeid(*g_membres->getConteneur()["Robert"]) == typeid(MembreRegulier));

	// Test 46: ajouter Membre Premium
	g_membres->ajouter(make_pair(alexPremium->getNom(), alexPremium));
	tests.push_back(g_membres->getConteneur().size() == 4 && typeid(*g_membres->getConteneur()["Alex"]) == typeid(MembrePremium));

	// Test 47-48: Ajouter coupon
	g_coupons->ajouter(new Coupon("5%", 0.05, 500));
	g_coupons->ajouter(new Coupon("10%", 0.1, 900));

	tests.push_back(g_coupons->getConteneur().size() == 2);

	g_coupons->ajouter(new Coupon("20%", 0.2, 1700));

	tests.push_back(g_coupons->getConteneur().size() == 3);

	// Test 49: Trouver membre
	tests.push_back(g_membres->getConteneur()["John"] != nullptr
		&& g_membres->getConteneur()["cc"] == nullptr);

	// Test 50-51: Acheter coupon Membre Regulier
	MembreRegulier* marc = static_cast<MembreRegulier*>(g_membres->getConteneur()["Marc"]);
	MembreRegulier* john = static_cast<MembreRegulier*>(g_membres->getConteneur()["John"]);
	MembreRegulier* robert = static_cast<MembreRegulier*>(g_membres->getConteneur()["Robert"]);
	MembrePremium* alex = static_cast<MembrePremium*>(g_membres->getConteneur()["Alex"]);

	marc->modifierPoints(1000);
	g_coupons->acheterCoupon(john);
	g_coupons->acheterCoupon(marc);

	tests.push_back(john->getCoupons().size() == 0
		&& john->getPoints() == 0
		&& marc->getCoupons().size() == 1
		&& marc->getCoupons()[0]->getCode() == "10%"
		&& marc->getPoints() == 100);

	marc->modifierPoints(2900);
	g_coupons->acheterCoupon(marc);

	tests.push_back(marc->getCoupons().size() == 2
		&& marc->getCoupons()[1]->getCode() == "20%"
		&& marc->getPoints() == 1300);

	//Tests 52 : Acheter coupon Membre Premium
	alex->modifierPoints(950);
	alex->modifierPointsCumulee(950);
	g_coupons->acheterCoupon(alex);

	tests.push_back(alex->getCoupons().size() == 1
		&& alex->getPoints() == 59
		&& alex->getCoupons()[0]->getCode() == "10%");

	alex->modifierPoints(-59);
	alex->modifierPointsCumulee(-950);
	*alex -= g_coupons->getConteneur()[1];

	// Test 53-54: Assigner billet avec billet Regulier:
	g_membres->assignerBillet(new BilletRegulier("A1B2C3", 1000, "YUL - YYZ", TarifBillet::PremiumEconomie, "2019-12-21"), "John", g_coupons->appliquerCoupon(g_membres->getConteneur()["John"], 1000));
	;
	g_membres->assignerBillet(new BilletRegulier("D4E5F6", 2000, "YUL - YYZ", TarifBillet::Affaire, "2019-12-21"), "Marc", 0);
	g_membres->assignerBillet(new BilletRegulier("H7I8J9", 2000, "YUL - YYZ", TarifBillet::Affaire, "2019-12-21"), "Marc", g_coupons->appliquerCoupon(g_membres->getConteneur()["Marc"], 2000));
	g_coupons->appliquerCoupon(g_membres->getConteneur()["John"], 1000);


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

	// Test 55-56: Assigner billet avec flightPass
	g_membres->assignerBillet(new FlightPass("f1", 10000, "YUL - YYZ", TarifBillet::PremiumEconomie), "John", g_coupons->appliquerCoupon(g_membres->getConteneur()["John"], 10000));
	g_membres->assignerBillet(new FlightPass("f2", 20000, "YUL - YYZ", TarifBillet::Affaire), "Marc", 0);
	g_membres->assignerBillet(new FlightPass("f3", 20000, "YUL - YYZ", TarifBillet::Affaire), "Marc", g_coupons->appliquerCoupon(g_membres->getConteneur()["Marc"], 20000));

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

	// Test 57: Assigner billet avec membre Premium
	g_membres->assignerBillet(new FlightPass("f1", 10000, "YUL - YYZ", TarifBillet::PremiumEconomie), "Alex", g_coupons->appliquerCoupon(g_membres->getConteneur()["Alex"], 10000));

	alex->acheterCoupon(c2);

	g_membres->assignerBillet(new BilletRegulier("A1B2C3", 1000, "YUL - YYZ", TarifBillet::PremiumEconomie, "2019-12-21"), "Alex", g_coupons->appliquerCoupon(g_membres->getConteneur()["Alex"], 1000));

	tests.push_back(alex->getBillets().size() == 2
		&& alex->getBillets()[0]->getPrix() == 10000
		&& typeid(*alex->getBillets()[0]) == typeid(FlightPass)
		&& typeid(*alex->getBillets()[1]) == typeid(BilletRegulier)
		&& alex->getPoints() == 299
		&& alex->getpointsCumulee() == 1189
		&& alex->getCoupons().size() == 0);

	// Test 58-59: Assigner BilletRegulierSolde
	g_membres->assignerBillet(new BilletRegulierSolde("T8U7P0", 4500, "YUL - YYZ", TarifBillet::Economie, "2019-12-21", 0.25), "Robert", 0);
	tests.push_back(robert->getBillets().size() == 1
		&& robert->getPoints() == 337
		&& robert->getBillets()[0]->getPrix() == 0.75 * 4500
		&& typeid(*robert->getBillets()[0]) == typeid(BilletRegulierSolde));

	john->acheterCoupon(c2);
	g_membres->assignerBillet(new BilletRegulierSolde("G7U8E2", 2500, "YUL - YYZ", TarifBillet::Economie, "2019-12-21", 0.5), "John", g_coupons->appliquerCoupon(g_membres->getConteneur()["John"], 2500));
	tests.push_back(john->getBillets().size() == 3
		&& john->getPoints() == 412
		&& john->getBillets()[2]->getPrix() == 2500 * 0.9 * 0.5
		&& typeid(*john->getBillets()[2]) == typeid(BilletRegulierSolde));

	// Test 60-61: Assigner FlightPassSolde
	g_membres->assignerBillet(new FlightPassSolde("T5R2F4", 10000, "YUL - YYZ", TarifBillet::Economie, 0.1), "Alex", g_coupons->appliquerCoupon(g_membres->getConteneur()["Alex"], 10000));
	tests.push_back(alex->getBillets().size() == 3
		&& alex->getpointsCumulee() == 2083
		&& alex->getPoints() == 1193
		&& alex->getBillets()[2]->getPrix() == 10000 * (1 - 1189 * 0.005 / 1000) * 0.9
		&& typeid(*alex->getBillets()[2]) == typeid(FlightPassSolde));

	alex->modifierPoints(700);
	alex->modifierPointsCumulee(700);
	alex->acheterCoupon(c2);
	g_membres->assignerBillet(new FlightPassSolde("J9K5L0", 25000, "YUL - YYZ", TarifBillet::Economie, 0.5), "Alex", g_coupons->appliquerCoupon(g_membres->getConteneur()["Alex"], 25000));
	tests.push_back(alex->getBillets().size() == 4
		&& alex->getpointsCumulee() == 3892
		&& alex->getPoints() == 2128
		&& alex->getBillets()[3]->getPrix() == 25000 * 0.9 * (1 - 2783 * 0.005 / 1000) * 0.5
		&& typeid(*alex->getBillets()[3]) == typeid(FlightPassSolde));

	g_coupons->acheterCoupon(marcRegulier);

	// Test 62: calculerNombreBilletsEnSolde
	tests.push_back(g_membres->calculerNombreBilletsEnSolde() == 4);

	// Test 63: calculerRevenu
	tests.push_back(int(g_membres->calculerRevenu()) == 88035);

	// Test 64 : getBilletMin()
	tests.push_back(g_membres->getBilletMin("Alex")->getPnr() == "A1B2C3");

	// Test 65 : getBilletMax()
	tests.push_back(g_membres->getBilletMax("Alex")->getPnr() == "J9K5L0");

	// Test 66 : trouverBilletParIntervallle()
	tests.push_back(g_membres->trouverBilletParIntervallle(alex, 800.0, 10000.0).size() == 3 && g_membres->trouverBilletParIntervallle(alex, 600.0, 830.0).size() == 0);


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
	g_membres->afficher(cout);

	// Liberation de la memoire
	delete b1;
	delete b2;
	delete brs1;
	delete brs2;
	delete fps1;
	delete fps2;

	delete mp1;
	delete mr1;
	delete m2;

	delete c1;
	delete c2;
	delete c3;

	delete g_membres;
	delete g_coupons;

	return 0;
}