/*
 * Date : 1 Septembre 2019
 * Auteur : Marc-Antoine Abou Jaoude
 */

#ifndef COUPON_H
#define COUPON_H

#include <string>
#include <iostream>

using namespace std;

class Coupon {
public:
	// TODO: Implementer toutes les methodes
	Coupon();
	Coupon(const string& code, double rabais, int cout);
	
	// TODO: Implementer si necessaire
	~Coupon();

	// Getters
	string  getCode() const;
	double  getRabais() const;
	int  getCout() const;

	// Setters
	void setCode(const string& code);
	void setRabais(double rabais);
	void setCout(int cout);

	void afficherCoupon() const;
private:
	string code_;
	double rabais_;
	int cout_;
}; 

#endif // !COUPON_H

