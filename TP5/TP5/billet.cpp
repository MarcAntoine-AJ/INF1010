/********************************************
* Titre: Travail pratique #5 - billet.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "billet.h"
//Constructeur par défaut
Billet::Billet() :
	pnr_(""),
	nomPassager_(""),
	prix_(0),
	od_(""),
	tarif_(TarifBillet::Economie)
{
}
//Constructeur par paramètres
Billet::Billet(const string& pnr, double prix, const string& od, TarifBillet tarif) :
	pnr_(pnr),
	nomPassager_(""),
	prix_(prix),
	od_(od),
	tarif_(tarif)
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
//Retourne le string du tarif
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
//Opérateur d'affichage
ostream& operator<<(ostream& o, Billet const* billet)
{
	billet->afficher(o);
	return o;

}
//Fonction d'affichage
void Billet::afficher(ostream& o) const
{
	o << "\t\t- Billet " << pnr_ << " (Classe : " << formatTarif(tarif_) << ")" << endl;
	o << left << "\t\t\t" << setw(11) << "- Passager " << ": " << nomPassager_ << endl;
	o << "\t\t\t" << setw(11) << "- Prix" << ": " << prix_ << "$" << endl;
	o << "\t\t\t" << setw(11) << "- Trajet" << ": " << od_ << endl;
}

//todo operateur<<
