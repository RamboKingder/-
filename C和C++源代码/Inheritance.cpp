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
	Quote(const string& book,double sales_price):bookNo(book),price(sales_price){}
	string isbn()const { return bookNo; }
	virtual double net_price(size_t n)const { return n * price; }
	virtual ~Quote() = default;
};

class Disc_quote :public Quote{
protected:
	size_t quantity = 0;//适用折扣价的最低购买量
	double discount = 0.0;//以小数表示的折扣额
public:
	Disc_quote() = default;
	Disc_quote(const string &book, double price, size_t qty, double disc) :
		Quote(book, price), quantity(qty), discount(disc) {}
	double net_price(size_t)const = 0;//pure virtual function,which tells the client that this is meaningless.
};

class Bulk_quote :public Disc_quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const string& book, double p, size_t qty, double disc):Disc_quote(book,p,qty,disc){}
	double net_price(size_t n)const override;
};

double Bulk_quote::net_price(size_t cnt)const {
	if (cnt >= quantity)
		return cnt * (1 - discount)*price;
	else
		return cnt * price;
}
double print_total(ostream &os, const Quote &item, size_t n) {//dynamic binding
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}
int main(void) {
	Quote base("121-666", 30);
	Bulk_quote derived("121-666", 30, 40, 0.1);
	print_total(cout, base, 100);
	print_total(cout, derived, 100);

	return 0;
}