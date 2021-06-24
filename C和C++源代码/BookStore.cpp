#include<iostream>
#include<string>
using namespace std;

class Quote {
private: 
	string bookNo;
protected:
	double price = 0.0;
public:
	Quote() = default;
	//No matter wether the argument is a const object,we can always bint it to a alias which we can't use to chage the origian object
	//And Here we use public member function to access  protected member data
	Quote(const string &book,double sales_price):bookNo(book),price(sales_price){}
	string isbn()const {return bookNo;};
	virtual double net_price(size_t n)const {return n * price;}
	virtual ~Quote() = default;
};

class Bulk_quote :public Quote {
private:
	size_t min_qty = 0;
	double discount = 0.0;
public:
	Bulk_quote() = default;
	Bulk_quote(const string &book, double p, size_t qty, double disc) :
		Quote(book, p), min_qty(qty), discount(disc) {}
	double net_price(size_t) const override;
};

double Bulk_quote::net_price(size_t cnt)const {
	if (cnt >= min_qty)
		return cnt * (1 - discount)*price;
	else
		return cnt * price;
}

double print_total(ostream &os, const Quote &item, size_t n) {
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}