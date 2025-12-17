#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <ostream>
 
struct Term {
    double coef;
    int exp;
    Term* next;
    Term(double coef = 0.0, int exp = 0);

    bool operator==(const Term& other) const;
    bool operator!=(const Term& other) const;
};

class UnivariatePolynomial
{
private:
    Term* dummyhead;

public:
    UnivariatePolynomial();
    UnivariatePolynomial(const UnivariatePolynomial& other);
    ~UnivariatePolynomial();

    Term* head() const;

    void add(double coef, int exp);
    
    int at(int exp) const;
    Term* find(int exp) const;
    Term* pop(int exp);
    void remove(int exp);

    bool isEmpty() const;
    bool empty() const;
    void clear();

    bool operator==(const UnivariatePolynomial& other) const;
    bool operator!=(const UnivariatePolynomial& other) const;

    UnivariatePolynomial& operator=(const UnivariatePolynomial& other);
    UnivariatePolynomial operator-() const;

    UnivariatePolynomial operator+(const UnivariatePolynomial& other) const;
    UnivariatePolynomial operator-(const UnivariatePolynomial& other) const;
    UnivariatePolynomial operator*(const UnivariatePolynomial& other) const;
    UnivariatePolynomial operator*(double ) const;

    UnivariatePolynomial& operator+=(const UnivariatePolynomial& other);
    UnivariatePolynomial& operator-=(const UnivariatePolynomial& other);
    UnivariatePolynomial& operator*=(const UnivariatePolynomial& other);
    UnivariatePolynomial& operator*=(double );

    void add(const UnivariatePolynomial& other);
    
    UnivariatePolynomial derivative();

    friend std::ostream& operator<<(std::ostream& , const UnivariatePolynomial& );
};

#endif
