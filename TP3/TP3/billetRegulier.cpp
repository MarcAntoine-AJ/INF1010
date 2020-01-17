#include "billetRegulier.h"


//Constructeur par paramètres
BilletRegulier::BilletRegulier(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol, TypeBillet typeBillet)
	: Billet(pnr, nomPassager, prix, od, tarif, typeBillet), dateVol_(dateVol)
{
}
//Getters
string BilletRegulier::getDateVol()const
{
	return dateVol_;
}
//Setters
void BilletRegulier::setDateVol(string dateVol)
{
	dateVol_ = dateVol;
}
//Opérateur d'affichage
ostream& operator<<(ostream& os, const BilletRegulier& billetRegulier)
{
	os << static_cast<Billet> (billetRegulier);
	os << "date Vol : " << billetRegulier.dateVol_ << endl;
	return os;


}
