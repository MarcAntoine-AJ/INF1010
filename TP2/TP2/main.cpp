/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

 /* REPONSES AUX QUESTIONS

 1.	Quel est l’utilité de l’opérateur = et du constructeur par copie?
 Le constructeur par copie et l'opérateur = permettent de copier les attributs d'un objet et de les assigner à un autre objet. Dans le cas du constructeur par copie,
 celui-ci fait une copie d'un objet et crée un nouvel objet avec cette copie. L'opérateur = s'applique généralement à un objet déja existant qui voit ses attributs se
 faire écraser pour être remplacer par les attributs copiés de l'autre objet. Les deux  servent donc à faire des copies seulement dans un contexte différent.

 2.	Dans quel cas est-il nécessaire de surcharger l’opérateur = et le constructeur par copie?
 Il est nécessaire de surcharger les opérateurs lorsqu'on veut faire des deep copy d'objet ou d'attributs étant donné que ces opérateurs font des shallow copy par défaut.
 Ceci est entre autres nécessaire dans le cas des pointeurs lorsqu'on ne veut pas que deux pointeurs pointent au même objet mais plutôt qu'il y ait deux entités indépendantes.

 3.	Pourquoi avons-nous dû surcharger l’opérateur = et le constructeur par copie pour la classe Membre?
 Dans le cas de la classe Membre, chaque billet est supposé être unique pour chaque membre. Ainsi, on ne veut pas avoir deux tableaux de pointeurs qui pointent aux mêmes éléments.
 Ainsi, il devient nécessaire que les objets copiés sont de nouvelles entités avec de nouveaux pointeurs. Ainsi, on a recours à des deep copy ce que le constructeur
 et l'opérateur ne font pas par défaut. Ils font plutôt des shallow copy.

 4.	Qu’est-ce qui différencie l’opérateur = du constructeur par copie?
 L'opérateur est généralement utilisé lorsqu'un objet existe déja et qu'on veut écraser ses valeurs par une copie tandis que le constructeur par copie sert à créer un nouvel objet
 en copiant les attributs d'un objet déjà existant. Dans le cas de l'opérateur, il devient aussi nécessaire de valider que les deux objets ne sont pas équivalent pour ne pas
 avoir d'erreur, l'erreur surgit puisqu'on supprime les éléments et on essaie de les assigner par la suite, ce qui n'est pas nécessaire 
 pour le constructeur par copie puisqu'on part de rien.

 */

#include <string>
#include <iostream>
#include <vector>
#include "debogageMemoire.hpp"
#include "gestionnaire.h"
#include "Header.h"
using namespace std;

int main() {
	initDebogageMemoire();

	vector<bool> tests;

	// TESTS
	Billet* b1 = new Billet();
	Billet* b2 = new Billet("A1A1A1", "Fred", 3000, "YUL - CDG", TarifBillet::Premiere, "2019-12-21");

	Membre* m1 = new Membre();
	Membre* m2 = new Membre("John");
	Membre* m3;
	Membre* m4;

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
	// Test 4 - 5: initialisation de membre
	tests.push_back(m1->getCoupons().size() == 0
		&& m1->getBillets().size() == 0
		&& m2->getCoupons().size() == 0
		&& m2->getBillets().size() == 0);
	m1->setNom("Marc");
	tests.push_back(m1->getNom() == "Marc");

	// Tests 6: Modifier points
	m1->modifierPoints(150);
	m1->modifierPoints(20);
	m1->modifierPoints(-50);

	tests.push_back(m1->getPoints() == 120);
	m1->modifierPoints(-120);

	// Tests 7 - 8: calculer points
	b1->setTarif(TarifBillet::Economie);
	b1->setPrix(1000);

	tests.push_back(m1->calculerPoints(b1) == 100
		&& m1->calculerPoints(b2) == 600);

	b1->setTarif(TarifBillet::PremiumEconomie);
	b2->setTarif(TarifBillet::Affaire);

	tests.push_back(m1->calculerPoints(b1) == 150
		&& m1->calculerPoints(b2) == 450);

	// Tests 9 - 11: Ajouter billets
	m1->ajouterBillet("A1B2C3", 3000, "YUL - YYZ", TarifBillet::Premiere, "2019-12-21");
	tests.push_back(m1->getBillets().size() == 1
		&& m1->getBillets()[0]->getNomPassager() == "Marc"
		&& m1->getPoints() == 600);

	m1->ajouterBillet("D4E5F6", 1000, "YUL - YVR", TarifBillet::Affaire, "2019-12-21");
	tests.push_back(m1->getBillets().size() == 2);

	m1->ajouterBillet("H7I8J9", 1500, "YUL - LGA", TarifBillet::PremiumEconomie, "2019-12-21");
	tests.push_back(m1->getBillets().size() == 3
		&& m1->getPoints() == 1050);

	// Tests 12 - 14: Operateur +=
	tests.push_back(&(*m1 += c1) == m1);

	*m1 += c2;
	tests.push_back(m1->getCoupons().size() == 2);

	*m1 += c1;
	tests.push_back(m1->getCoupons().size() == 3);

	// Tests 15 - 17: Operateur -=
	tests.push_back(&(*m1 -= c2) == m1);
	tests.push_back(m1->getCoupons().size() == 2
		&& m1->getCoupons()[0] == c1
		&& m1->getCoupons()[1] == c1);

	*m1 -= c1;
	*m1 += c2;
	tests.push_back(m1->getCoupons().size() == 2
		&& m1->getCoupons()[0] == c1
		&& m1->getCoupons()[1] == c2);

	// Tests 18 - 20: Acheter coupon
	// Pas assez de points
	m1->acheterCoupon(c3);

	tests.push_back(m1->getPoints() == 1050
		&& m1->getCoupons().size() == 2);

	// Achat de c1 et c2
	m1->modifierPoints(500);
	m1->acheterCoupon(c2);
	tests.push_back(m1->getPoints() == 650
		&& m1->getCoupons().size() == 3
		&& m1->getCoupons()[2] == c2);

	m1->acheterCoupon(c1);
	tests.push_back(m1->getPoints() == 150
		&& m1->getCoupons().size() == 4
		&& m1->getCoupons()[3] == c1);

	// Tests 21 - 22: Operateur == 
	tests.push_back(*m1 == "Marc"
		&& *m2 == "John"
		&& !(*m1 == "John")
		&& !(*m2 == "Marc"));

	tests.push_back("Marc" == *m1
		&& "John" == *m2
		&& !("Marc" == *m2)
		&& !("John" == *m1));

	// Tests 23 - 24: Constructeur par copie
	m3 = new Membre(*m1);
	tests.push_back(m3->getNom() == m1->getNom()
		&& m3->getPoints() == m1->getPoints()
		&& m3->getCoupons() == m1->getCoupons()
		&& m3->getBillets() != m1->getBillets()
	);

	m4 = new Membre(*m2);
	tests.push_back(m4->getNom() == m2->getNom()
		&& m4->getPoints() == m2->getPoints()
		&& m4->getCoupons() == m2->getCoupons()
	);

	// Test 25: Operateur d'assignation ne fait rien si c'est le meme objet
	vector<Billet*> m1Billets = m1->getBillets();
	vector<Coupon*> m1Coupons = m1->getCoupons();

	*m1 = *m1;
	tests.push_back(m1->getNom() == "Marc"
		&& m1->getPoints() == 150
		&& m1->getCoupons() == m1Coupons
		&& m1->getBillets() == m1Billets
	);

	// Test 26: Operateur d'assignation retourne une reference vers l'objet
	tests.push_back(&(*m1 = *m1) == m1);

	// Test 27: Operateur d'assignation modifie correctement les attributs
	*m3 = *m1;
	tests.push_back(m3->getNom() == "Marc"
		&& m3->getPoints() == 150
		&& m3->getCoupons() == m1Coupons
		&& m3->getBillets() != m1Billets
	);

	/*
	* Tests Gestionnaire
	*/

	// Test 28: Initialisation
	tests.push_back(g->getCoupons().size() == 0
		&& g->getMembres().size() == 0);

	// Tests 29 - 30: Ajouter membre
	g->ajouterMembre("Marc");
	g->ajouterMembre("John");

	tests.push_back(g->getMembres().size() == 2);

	g->ajouterMembre("Robert");

	tests.push_back(g->getMembres().size() == 3);

	// Tests 31 - 32: Ajouter coupon
	g->ajouterCoupon("5%", 0.05, 500);
	g->ajouterCoupon("10%", 0.1, 900);

	tests.push_back(g->getCoupons().size() == 2);

	g->ajouterCoupon("20%", 0.2, 1700);

	tests.push_back(g->getCoupons().size() == 3);

	// Tests 33: Trouver membre
	tests.push_back(g->trouverMembre("John") != nullptr
		&& g->trouverMembre("ccc") == nullptr);

	// Tests 34 - 35: Acheter coupon
	Membre* marc = g->getMembres()[0];
	Membre* john = g->getMembres()[1];

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

	// Tests 36 - 37: Assigner billet:
	g->assignerBillet("John", "A1B2C3", 1000, "YUL - YYZ", TarifBillet::PremiumEconomie, "2019-12-21", true);
	g->assignerBillet("Marc", "D4E5F6", 2000, "YUL - YYZ", TarifBillet::Affaire, "2019-12-21", false);
	g->assignerBillet("Marc", "H7I8J9", 2000, "YUL - YYZ", TarifBillet::Affaire, "2019-12-21", true);

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
	Pomme pomme(Membre());
	cout << endl;
	//// Affichage du programme
	cout << *g;

	// Liberation de la memoire
	delete b1;
	delete b2;

	delete m1;
	delete m2;
	delete m3;
	delete m4;

	delete c1;
	delete c2;
	delete c3;

	delete g;

	return 0;
}