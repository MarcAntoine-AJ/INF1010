/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe C�T�-MORNEAULT
 */

#include "billet.h"
 //Constructeur par d�faut
Billet::Billet() :
	pnr_(""),
	nomPassager_(""),
	prix_(0),
	od_(""),
	tarif_(TarifBillet::Economie), typeBillet_(TypeBillet::Billet_Base)
{
}
//Constructeur par param�tres
Billet::Billet(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet) :
	pnr_(pnr),
	nomPassager_(nomPassager),
	prix_(prix),
	od_(od),
	tarif_(tarif),
	typeBillet_(typeBillet)
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
TypeBillet Billet::getTypeBillet() const
{
	return typeBillet_;
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
void Billet::setTypeBillet(TypeBillet typeBillet)
{
	typeBillet_ = typeBillet;
}

//Retourne le type de Billet
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
//Op�rateur d'affichage
ostream& operator<<(ostream& o, const Billet& billet)
{
	o << "\t\t- Billet " << billet.pnr_ << " (Classe : " << billet.formatTarif(billet.tarif_) << ")" << endl;
	o << left << "\t\t\t" << setw(11) << "- Passager " << ": " << billet.nomPassager_ << endl;
	o << "\t\t\t" << setw(11) << "- Prix" << ": " << billet.prix_ << "$" << endl;
	o << "\t\t\t" << setw(11) << "- Trajet" << ": " << billet.od_ << endl;
	o << "\t\t\t" << setw(11) << "- Vol le" << ": " << endl;

	return o;
}
