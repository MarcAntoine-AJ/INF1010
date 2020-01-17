/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "membre.h"

 //Constructeur par défaut de membre
Membre::Membre() :
	nom_(""), typeMembre_(TypeMembre::Membre_Occasionnel)
{
}

//Constructeur par paramètres de membre
Membre::Membre(const string& nom, TypeMembre typeMembre) :
	nom_(nom), typeMembre_(typeMembre)
{
}

//Constructeur par copie de membre
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_), typeMembre_(membre.typeMembre_)
{

	for (int i = 0; i < membre.billets_.size(); ++i) {



		switch (membre.billets_[i]->getTypeBillet())
		{

		case TypeBillet::Billet_Base:

		{
			Billet* billet = new Billet(*membre.billets_[i]);
			billets_.push_back(billet);

		}

		break;

		case TypeBillet::Billet_Regulier:

		{
			BilletRegulier* billetRegulier = new BilletRegulier(*static_cast<BilletRegulier*>(membre.billets_[i]));
			billets_.push_back(billetRegulier);

		}

		break;

		case TypeBillet::Flight_Pass:

		{
			FlightPass* billetFlightPass = new FlightPass(*static_cast<FlightPass*>(membre.billets_[i]));
			billets_.push_back(billetFlightPass);

		}

		break;



		}


	}



}
//Destructeur de membre
Membre::~Membre()
{
	for (int i = 0; i < billets_.size(); i++) {
		delete billets_[i];
	}
}
//Getters
string Membre::getNom() const
{
	return nom_;
}

vector<Billet*> Membre::getBillets() const
{
	return billets_;
}
TypeMembre Membre::getTypeMembre() const
{
	return typeMembre_;
}

//Setters
void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

//Méthode pour ajouter billet
void Membre::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol)
{


	switch (typeBillet)
	{
	case TypeBillet::Billet_Base:

	{
		Billet* billet = new Billet(pnr, nom_, prix, od, tarif, typeBillet);
		billets_.push_back(billet);

	}

	break;

	case TypeBillet::Billet_Regulier:
	{
		BilletRegulier* billetRegulier = new BilletRegulier(pnr, nom_, prix, od, tarif, dateVol, typeBillet);
		billets_.push_back(billetRegulier);

	}

	break;

	case TypeBillet::Flight_Pass:
	{
		FlightPass* billetFlightPass = new FlightPass(pnr, nom_, prix, od, tarif, typeBillet);
		billets_.push_back(billetFlightPass);

	}



	break;



	}
}


//Opérateur == avec string a droite
bool Membre::operator==(const string& nomMembre) const
{
	return nom_ == nomMembre;
}
//Opérateur == avec membre a droite
bool operator==(const string& nomMembre, const Membre& membre)
{
	return nomMembre == membre.nom_;
}
//Operateur d'affectation
Membre& Membre::operator=(const Membre& membre)
{
	if (this != &membre) {
		nom_ = membre.nom_;
		typeMembre_ = membre.typeMembre_;


		for (int i = 0; i < billets_.size(); ++i) {
			delete billets_[i];
		}

		billets_.clear();

		for (int i = 0; i < membre.billets_.size(); i++) {

			switch (membre.billets_[i]->getTypeBillet())
			{
			case TypeBillet::Billet_Base:
			{
				Billet* billet = new Billet(*membre.billets_[i]);
				billets_.push_back(billet);
			}

			break;

			case TypeBillet::Billet_Regulier:

			{
				BilletRegulier* billetRegulier = new BilletRegulier(*static_cast<BilletRegulier*>(membre.billets_[i]));
				billets_.push_back(billetRegulier);
			}

			break;

			case TypeBillet::Flight_Pass:

			{
				FlightPass* billetFlightPass = new FlightPass(*static_cast<FlightPass*>(membre.billets_[i]));
				billets_.push_back(billetFlightPass);

			}

			break;

			}
		}

		return *this;
	}
}

//Methode qui permet d'utiliser un billet
void Membre::utiliserBillet(const string& pnr)
{
	bool notFound = true;
	int position = 0;
	for (int i = 0; i < billets_.size() && notFound; i++)
	{
		if (billets_[i]->getPnr() == pnr)
		{
			notFound = false;
			position = i;
		}
	}
	if (!notFound) {

		if (billets_[position]->getTypeBillet() == TypeBillet::Flight_Pass) {


			static_cast<FlightPass*>(billets_[position])->decrementeNbUtilisations();


			if ((static_cast<FlightPass*>(billets_[position])->getNbUtilisationsRestante()) == 0)
			{
				delete billets_[position];
				for (int i = position; i < billets_.size() - 1; i++)
				{
					billets_[i] = billets_[i + 1];
				}
				billets_.pop_back();
			}


		}
		else
		{
			delete billets_[position];
			for (int i = position; i < billets_.size() - 1; i++)
			{
				billets_[i] = billets_[i + 1];
			}
			billets_.pop_back();
		}



	}
	else
	{
		cout << "Billet pas trouver" << endl;
	}
}
//Opérateur d'affichage
ostream& operator<< (ostream& o, const Membre& membre)
{
	o << setfill(' ');
	o << "- Membre " << membre.nom_ << ":" << endl;
	o << "\t" << "- Billets :" << endl;
	for (int i = 0; i < membre.billets_.size(); i++) {
		switch (membre.billets_[i]->getTypeBillet())
		{
		case TypeBillet::Billet_Base:
			o << membre.billets_[i];
			break;

		case TypeBillet::Billet_Regulier:
			o << *static_cast<BilletRegulier*>(membre.billets_[i]);
			break;

		case TypeBillet::Flight_Pass:
			o << *static_cast<FlightPass*>(membre.billets_[i]);
			break;


		}




	}
	return o << endl;
}