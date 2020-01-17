#include "flightPass.h"

//Constructeur par param�tres
FlightPass::FlightPass(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet)
	: Billet(pnr, nomPassager, prix, od, tarif, typeBillet)
{
	nbUtilisationsRestante_ = NB_UTILISATIONS_INITIALE;

}
//Diminue le nombre d'utilisations
void FlightPass::decrementeNbUtilisations()
{
	nbUtilisationsRestante_--;

}
//Getter
int FlightPass::getNbUtilisationsRestante() const
{
	return nbUtilisationsRestante_;
}
//Op�rateur d'affichage
ostream& operator<< (ostream& os, const FlightPass& flightPass)
{
	os << static_cast<Billet>(flightPass);
	os << "Nombre utilisations restantes : " << flightPass.nbUtilisationsRestante_ << endl;
	return os;

}