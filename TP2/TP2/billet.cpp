/*
 * Date : 12 Septembre 2019
 * Auteur : Marc-Antoine Abou Jaoude
 */

#include "billet.h"


 //Constructeur par defaut
Billet::Billet() :
	pnr_(""),
	nomPassager_(""),
	prix_(0),
	od_(""),
	tarif_(TarifBillet::Economie),
	dateVol_("")
{
}
//Constructeur par parametres
Billet::Billet(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol) :
	pnr_(pnr),
	nomPassager_(nomPassager),
	prix_(prix),
	od_(od),
	tarif_(tarif),
	dateVol_(dateVol)
{
}
//Destructeur
Billet::~Billet()
{
}
//Getters
string Billet::getPnr() const
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

string Billet::getOd() const
{
	return od_;
}

TarifBillet Billet::getTarif() const
{
	return tarif_;
}

string Billet::getDateVol() const
{
	return dateVol_;
}
//Setters
void Billet::setPnr(const string& pnr)
{
	pnr_ = pnr;
}

void Billet::setNomPassager(const string& nomPassager)
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

void Billet::setTarif(TarifBillet tarif)
{
	tarif_ = tarif;
}

void Billet::setDateVol(const string& dateVol)
{
	dateVol_ = dateVol;
}

//Retourne en string le tarif
string Billet::formatTarif(TarifBillet tarif) const
{
	switch (tarif)
	{
	case TarifBillet::Economie:
		return "Economie";
	case TarifBillet::PremiumEconomie:
		return "Premium economie";
	case TarifBillet::Affaire:
		return "Affaire";
	case TarifBillet::Premiere:
		return "Premiere";
	default:
		return "";
	}
}

// TODO: Remplacer cette methode par l'operateur <<
//Surcharge de operateur << pour afficher infos
ostream& operator << (ostream& os, const Billet& billet)
{
	os << "\t\t- Billet " << billet.pnr_ << " (Classe : " << billet.formatTarif(billet.tarif_) << ")" << endl;
	os << left << "\t\t\t" << setw(11) << "- Passager " << ": " << billet.nomPassager_ << endl;
	os << "\t\t\t" << setw(11) << "- Prix" << ": " << billet.prix_ << "$" << endl;
	os << "\t\t\t" << setw(11) << "- Trajet" << ": " << billet.od_ << endl;
	os << "\t\t\t" << setw(11) << "- Vol le" << ": " << billet.dateVol_ << endl;
	return os;
}
