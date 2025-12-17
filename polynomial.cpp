#include "polynomial.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

bool isEqualTo(double number1, double number2 = 0.0, double epsilon = 1e-10) {
    if (number1 == number2) return true;

    double diff = std::abs(number1 - number2);

    if (std::abs(number1) < epsilon || std::abs(number2)  < epsilon) return diff < epsilon;
    return diff / std::min(std::abs(number1), std::abs(number2)) < epsilon;
}

Term::Term(double coef, int exp): coef(coef), exp(exp), next(nullptr) {}

bool Term::operator==(const Term& other) const {
    return exp == other.exp && isEqualTo(coef, other.coef);
}

bool Term::operator!=(const Term& other) const {
    return exp != other.exp || !isEqualTo(coef, other.coef);
}

UnivariatePolynomial::UnivariatePolynomial(): dummyhead(new Term()) {}

UnivariatePolynomial::UnivariatePolynomial(const UnivariatePolynomial& other): dummyhead(new Term()) {
    Term* current = other.dummyhead->next;
    Term* prev = dummyhead;
    while (current!= nullptr) {
        Term* newTerm = new Term(current->coef, current->exp);
        prev = prev->next = newTerm;
        current = current->next;
    }
    prev->next = nullptr;
}

UnivariatePolynomial::~UnivariatePolynomial() {
    Term* current = dummyhead;
    while (current!= nullptr) {
        Term* next = current->next;
        delete current;
        current = next;
    }
}

Term* UnivariatePolynomial::head() const {
    return dummyhead;
}

void UnivariatePolynomial::add(double coef, int exp) {
    if (isEqualTo(coef)) {
        return;
    }

    Term* current = dummyhead;

    while (current->next != nullptr && current->next->exp > exp) {
        current = current->next;
    }

    if (current->next != nullptr && current->next->exp == exp) {
        current->next->coef += coef;
        if (isEqualTo(current->next->coef)) {
            Term* toBeDeleted = current->next;
            current->next = current->next->next;
            delete toBeDeleted;
        }
        return;
    }

    Term* newTerm = new Term(coef, exp);
    newTerm->next = current->next;
    current->next = newTerm;
    return;
}

int UnivariatePolynomial::at(int exp) const {
    Term* current = dummyhead->next;
    while (current != nullptr) {
        if (current->exp == exp) {
            return current->coef;
        } else if (current->exp < exp) {
            return 0;
        }
        current = current->next;
    }
    return 0;
}

Term* UnivariatePolynomial::find(int exp) const {
    Term* current = dummyhead->next;
    while (current != nullptr) {
        if (current->exp == exp) {
            return current;
        } else if (current->exp < exp) {
            return nullptr;
        }
        current = current->next;
    }
    return nullptr;
}

Term* UnivariatePolynomial::pop(int exp) {
    Term* prev = dummyhead;
    Term* current = dummyhead->next;

    while (current != nullptr) {
        if (current->exp < exp) {
            return nullptr;
        }

        if (current->exp == exp) {
            prev->next = current->next;
            current->next = nullptr;
            return current;
        }
    }

    return nullptr;
}

void UnivariatePolynomial::remove(int exp) {
    Term* prev = dummyhead;
    Term* current = dummyhead->next;

    while (current != nullptr) {
        if (current->exp < exp) {
            return;
        }

        if (current->exp == exp) {
            prev->next = current->next;
            delete current;
            return;
        }
    }
}

bool UnivariatePolynomial::isEmpty() const {
    return dummyhead->next == nullptr;
}

bool UnivariatePolynomial::empty() const {
    return dummyhead->next == nullptr;
}

void UnivariatePolynomial::clear() {
    if (isEmpty()) {
        return;
    }
    Term* current = dummyhead->next;
    while (current != nullptr) {
        Term* next = current->next;
        delete current;
        current = next;
    }
    dummyhead->next = nullptr;
}

bool UnivariatePolynomial::operator==(const UnivariatePolynomial& other) const {
    Term* current1 = dummyhead->next;
    Term* current2 = other.dummyhead->next;

    while (current1 != nullptr && current2 != nullptr) {
        if (*current1 != *current2) {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    return current1 == nullptr && current2 == nullptr;
}

bool UnivariatePolynomial::operator!=(const UnivariatePolynomial& other) const {
    return !(*this == other);
}

UnivariatePolynomial& UnivariatePolynomial::operator=(const UnivariatePolynomial& other) {
    if (this == &other) {
        return *this;
    }

    if (*this == other) {
        return *this;
    }

    if (!isEmpty()) {
        clear();
    }

    Term* current = other.dummyhead->next;
    Term* prev = dummyhead;
    while (current != nullptr) {
        Term* newTerm = new Term(current->coef, current->exp);
        prev = prev->next = newTerm;
        current = current->next;
    }
    prev->next = nullptr;

    return *this;
}

UnivariatePolynomial UnivariatePolynomial::operator-() const {
    UnivariatePolynomial result;
    Term* current = dummyhead->next;
    Term* res_end = result.head();
    while (current != nullptr) {
        res_end = res_end->next = new Term(-current->coef, current->exp);
        current = current->next;
    }
    return result;
}

UnivariatePolynomial UnivariatePolynomial::operator+(const UnivariatePolynomial& other) const {
    UnivariatePolynomial result;
    Term* current1 = dummyhead->next;
    Term* current2 = other.dummyhead->next;

    Term* current = result.head()->next;

    while (current1 && current2) {
        if (current1->exp > current2->exp) {
            current = current->next = new Term(current1->coef, current1->exp);
            current1 = current1->next;
            continue;
        }else if (current1->exp < current2->exp) {
            current = current->next = new Term(current2->coef, current2->exp);
            current2 = current2->next;
            continue;
        }else {
            current = current->next = new Term(current1->coef + current2->coef, current1->exp);
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    while (!current1 && current2) {
        current = current->next = new Term(current2->coef, current2->exp);
        current2 = current2->next;
    }

    while (current1 && !current2) {
        current = current->next = new Term(current1->coef, current1->exp);
        current1 = current1->next;
    }

    return result;
}

UnivariatePolynomial UnivariatePolynomial::operator-(const UnivariatePolynomial& other) const {
    return *this + (-other);
}

UnivariatePolynomial UnivariatePolynomial::operator*(const UnivariatePolynomial& other) const {
    UnivariatePolynomial result;
    
    for (Term* i = dummyhead->next; i != nullptr; i = i->next) {
        for (Term* j = other.dummyhead->next; j != nullptr; j = j->next) {
            result.add(i->coef * j->coef, i->exp + j->exp);
        }
    }

    return result;
}

UnivariatePolynomial UnivariatePolynomial::operator*(double scalar) const {
    UnivariatePolynomial result;
    Term* res_end = result.head();
    Term* current = dummyhead->next;

    while (current) {
        res_end = res_end->next = new Term(scalar * current->coef, current->exp);
        current = current->next;
    }

    return result;
}

UnivariatePolynomial& UnivariatePolynomial::operator+=(const UnivariatePolynomial& other) {
    *this = *this + other;
    return *this;
}

UnivariatePolynomial& UnivariatePolynomial::operator-=(const UnivariatePolynomial& other) {
    *this = *this - other;
    return *this;
}

UnivariatePolynomial& UnivariatePolynomial::operator*=(const UnivariatePolynomial& other) {
    *this = *this * other;
    return *this;
}

UnivariatePolynomial& UnivariatePolynomial::operator*=(double scalar) {
    *this = *this * scalar;
    return *this;
}

void UnivariatePolynomial::add(const UnivariatePolynomial& other) {
    *this += other;
}

UnivariatePolynomial UnivariatePolynomial::derivative() {
    UnivariatePolynomial result;

    Term* res_end = result.head();
    Term* current = dummyhead->next;

    while (current) {
        if (current->exp == 0) {
            current = current->next;
            continue;
        }
        res_end = res_end->next = new Term(current->exp * current->coef, current->exp - 1);
        current = current->next;
    }

    return result;
}

std::ostream& operator<<(std::ostream& os, const UnivariatePolynomial& poly) {
    if (poly.empty()) {
        os << 0 << std::flush;
        return os;
    }

    Term* current = poly.head()->next;
    while (current) {
        os << (current->coef < 0 ? "-" : "+") << std::abs(current->coef);
        if (current->exp != 0) {
            os << "x^" << current->exp;
        }
        current = current->next;
    }
    os << std::flush;
    return os;
}
