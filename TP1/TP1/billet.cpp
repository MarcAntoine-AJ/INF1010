/*
 * Date : 1 Septembre 2019
 * Auteur : Marc-Antoine Abou Jaoude
 */

#include <string>
#include <iostream>
#include <vector>
#include "billet.h"
#include "def.h"
using namespace std;
//Constructeur par defaut
Billet::Billet() 
	: pnr_("0"), nomPassager_("0"), prix_(0), od_("N/A"), tarif_(TarifBillet::Economie), dateVol_("N/A")
{
}
//Constructeur par parametre
Billet::Billet(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol) 
	: pnr_(pnr),nomPassager_(nomPassager),prix_(prix),od_(od),tarif_(tarif),dateVol_(dateVol)
{
}

// Getters
string Billet :: getPnr() const 
{
	return pnr_;
}
string Billet::getNomPassager() const 
{
	return nomPassager_;

}
double Billet::getPrix() const 
{
	return prix_;

}
string Billet :: getOd() const 
{
	return od_;
}
TarifBillet Billet :: getTarif()const 
{
	return tarif_;

}
string Billet :: getDateVol() const 
{
	return dateVol_;

}

// Setters
void Billet::setPnr(const string& pnr) 
{
	
	pnr_ = pnr;

}
void Billet :: setNomPassager(const string& nomPassager) 
{
	nomPassager_ = nomPassager;

}
void Billet::setPrix(double prix)
{
	prix_ = prix;
}
void Billet::setOd(const string& od) 
{
	od_ = od;

}
void Billet::setTarif(TarifBillet tarif) {

	tarif_ = tarif;
}
void Billet::setDateVol(const string& dateVol) {

	dateVol_ = dateVol;
}

//Retourne le tarif en string
string Billet::formatTarif(TarifBillet tarif) const
{
	switch (tarif) {

	case TarifBillet::Affaire: 
		return "Affaire";
		
	case TarifBillet::Economie: 
		return "Economie";
		
	case TarifBillet::Premiere:
		return "Premiere";
		
	case TarifBillet::PremiumEconomie:
		return "Premium economie";
	}
}

//Méthode d'affichage du billet
void Billet::afficherBillet() const 
{
	cout << "		Billet " << pnr_ << "( Classe : " << formatTarif(tarif_) << " )" << endl;
	cout << "			-Passager : " << nomPassager_ << endl;
	cout << "			-Prix : " << prix_ << endl;
	cout << "			-Trajet : " << od_ << endl;
	cout << "			-Vol le  : " << dateVol_ << endl;


}
Billet ::~Billet()
{

}