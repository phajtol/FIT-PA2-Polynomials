#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cmath>
#include <cfloat>
#include <cassert>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

ios_base & dummy_polynomial_manipulator ( ios_base & x )
{ 
  return x;
}

ios_base & ( * ( polynomial_variable ( const string & varName ) ) ) ( ios_base & x )
{
  return dummy_polynomial_manipulator;
}


class CPolynomial
{
  public:
    // default constructor
    CPolynomial(void){
      coefficients.push_back(0);
    }

    // operator +
    CPolynomial operator + (const CPolynomial & other) const {
      CPolynomial res;

      if (this->Degree() < other.Degree()) {
        for (unsigned int i = 0; i <= this->Degree(); ++i) {
          res[i] = this->coefficients[i] + other[i];
        }
        for (unsigned int i = this->Degree() + 1; i <= other.Degree(); ++i) {
          res[i] = other[i];
        }
      } else {
        for (unsigned int i = 0; i <= other.Degree(); ++i) {
          res[i] = this->coefficients[i] + other[i];
        }
        for (unsigned int i = other.Degree() + 1; i <= this->Degree(); ++i) {
          res[i] = this->coefficients[i];
        }
      }

      return res;
    }

    // operator -
    CPolynomial operator - (const CPolynomial & other) const {
        CPolynomial res;
        res = (*this) + (other * -1);
        return res;
    }

    // operator * (polynomial, double)
    CPolynomial operator * (const double & number) const {
      CPolynomial res;

      if (number == 0) {
        return res;
      }

      for (int i = (int) this->Degree(); i >= 0; --i) {
        res[i] = coefficients[i] * number;
      }
      return res;
    }

    CPolynomial operator * (const CPolynomial & polynom) const {
      CPolynomial res;

      if( (polynom.Degree() == 0 && polynom[0] == 0) || (this->Degree() == 0 && (*this)[0] == 0) ) {
        return res;
      }

      for (unsigned int i = 0; i < (polynom.Degree() + this->Degree()); ++i) {
        res[i] = 0;
      }

      for (unsigned int i = 0; i <= this->Degree(); ++i) {
          for(int j = 0; j <= polynom.Degree(); ++j){
              res[i+j] += this->coefficients[i] * polynom[j];
          }
      }

      return res;
    }

    // operator ==
    bool operator == (const CPolynomial & cmp) const {
      if (this->Degree() != cmp.Degree()) {
        return false;
      }

      for (unsigned int i = 0; i <= cmp.Degree(); ++i) {
          if (this->coefficients[i] != cmp[i]) {
            return false;
          }
      }

      return true;
    }

    // operator !=
    bool operator != (const CPolynomial & cmp) const {
      return !(*this == cmp);
    }

    // operator []
    const double& operator [] (const int n) const {
        return coefficients[n];
    }

    double& operator [] (const int n) {
        if (n >= coefficients.size()) {
          coefficients.resize(n + 1, 0);
        }

        return coefficients[n];
    }
    

    // operator ()
    double operator () (double x) const {
      double res = 0;

      for (unsigned int i = 0; i <= this->Degree(); ++i) {
          res += coefficients[i] * pow(x, i);
      }

      return res;
    }

    // operator <<
    friend ostream& operator << (ostream& out, const CPolynomial& pol){
      //vypisanie
      for (int i = (int) pol.Degree(); i >= 0; --i) {
          if (pol.coefficients[i] != 0) {
            //znamienko
            if (pol.coefficients[i] > 0 && i != pol.Degree()) {
              out << " + ";
            } else if (pol.coefficients[i] < 0 && i != pol.Degree()) {
              out << " - ";
            } else if (pol.coefficients[i] < 0) {
              out << "- ";
            }

            //ak koeficient == 1
            if (abs(pol.coefficients[i]) != 1 || i == 0) {
              out << abs(pol.coefficients[i]);
            }
            if (abs(pol.coefficients[i]) != 1 && i != 0) {
              out << "*";
            }

            //nevypisovanie x^0
            if (i != 0) {
              out << "x^" << i;
            }
          } else if (i == 0) {
              if (pol.coefficients[i] == 0 && pol.Degree() == 0) {
                out << "0";
              } else if (pol.coefficients[i] > 0) {
                out << "+ " << abs(pol.coefficients[i]);
              } else if (pol.coefficients[i] < 0) {
                out << "- " << abs(pol.coefficients[i]);
              }

          }
      }

      return out;
    }

    // Degree (), returns unsigned value
    unsigned int Degree(void) const {
      for (unsigned int i = coefficients.size() - 1; i > 0; --i) {
        if(coefficients[i] != 0.0) {
          return i;
        }
      }
      
      return 0;
    }

    //custom
    void print(void){
      cout << "== obsah vektora coefficients ==" << endl;
      for(unsigned int i = 0; i <= Degree(); ++i)
        cout << "coefficients[" << i << "] = " << coefficients[i] << endl;
      cout << "== koniec obsahu vektora ==" << endl;
    }
    //end custom

  private:
    vector<double> coefficients;
};


#ifndef __PROGTEST__
bool smallDiff ( double a, double b )
{
  return fabs(a-b) < numeric_limits<double>::epsilon();
}

bool dumpMatch ( const CPolynomial & x, const vector<double> & ref )
{
  if(x.Degree()+1 != ref.size()) return false;
  for(int i = 0; i < ref.size(); ++i)
      if(!smallDiff(x[i],ref[i])) return false;
  return true;
}

int main(void)
{

  CPolynomial a,b,c;
    vector<double> refVector, refVector2, refVector3, refVector4, refVector5;
    refVector.push_back(20.0);
    refVector.push_back(-7.0);
    refVector.push_back(-0.0);
    refVector.push_back(-2.0);

    refVector2.push_back(20.0);
    refVector2.push_back(-7.0);
    refVector2.push_back(0.0);
    refVector2.push_back(-2.0);
    refVector2.push_back(0.0);
    refVector2.push_back(-1.0);

    refVector3.push_back(20.0);
    refVector3.push_back(-7.0);
    refVector3.push_back(-0.0);
    refVector3.push_back(-2.0);
    refVector3.push_back(-0.0);
    refVector3.push_back(1.0);

    refVector4.push_back(0.0);
    refVector4.push_back(-0.0);
    refVector4.push_back(0.0);
    refVector4.push_back(-0.0);
    refVector4.push_back(-0.0);
    refVector4.push_back(-20.0);
    refVector4.push_back(7.0);
    refVector4.push_back(0.0);
    refVector4.push_back(2.0);

    refVector5.push_back(0.0);



    /*a[0] = 1;
    a[1] = 5;
    b[0] = 2;
    b[1] = 1;

    cout << "a = " << a << endl;
    a.print();
    cout << "b = " << b << endl;
    b.print();
    cout << "a*b = " << (a*b) << endl;
    c = a*b;
    c.print();*/


  //CPolynomial a, b, c;
  ostringstream out;


  a[0] = -10;
  a[1] = 3.5;
  a[3] = 1;

    /*a.print();

    cout << "a.Degree = " << a.Degree() << endl;

    cout << "a(2) = " << a(2) << endl;*/
  assert ( smallDiff ( a ( 2 ), 5 ) );
  out . str ("");
  out << a;
  assert ( out . str () == "x^3 + 3.5*x^1 - 10" );

  a = a * -2;
  //assert ( a . Degree () == 3
  //         && dumpMatch ( a, vector<double> { 20.0, -7.0, -0.0, -2.0 } ) );
    assert ( a . Degree () == 3
             && dumpMatch ( a, refVector) );

  out . str ("");
  out << a;
  assert ( out . str () == "- 2*x^3 - 7*x^1 + 20" );
  out . str ("");
  out << b;

  assert ( out . str () == "0" );
  b[5] = -1;
  out . str ("");
  out << b;
  assert ( out . str () == "- x^5" );
  c = a + b;
  assert ( c . Degree () == 5
           //&& dumpMatch ( c, vector<double>{ 20.0, -7.0, 0.0, -2.0, 0.0, -1.0 } ) );
           && dumpMatch ( c, refVector2 ) );

  out . str ("");
  out << c;
  assert ( out . str () == "- x^5 - 2*x^3 - 7*x^1 + 20" );
  c = a - b;
  assert ( c . Degree () == 5
           //&& dumpMatch ( c, vector<double>{ 20.0, -7.0, -0.0, -2.0, -0.0, 1.0 } ) );
           && dumpMatch ( c, refVector3 ) );

  out . str ("");
  out << c;
  assert ( out . str () == "x^5 - 2*x^3 - 7*x^1 + 20" );
  c = a * b;
  assert ( c . Degree () == 8
           //&& dumpMatch ( c, vector<double>{ 0.0, -0.0, 0.0, -0.0, -0.0, -20.0, 7.0, 0.0, 2.0 } ) );
           && dumpMatch ( c, refVector4 ) );

  out . str ("");
  out << c;
  assert ( out . str () == "2*x^8 + 7*x^6 - 20*x^5" );
  assert ( a != b );
  b[5] = 0;
  assert ( !(a == b) );
  a = a * 0;
  assert ( a . Degree () == 0
           //&& dumpMatch ( a, vector<double>{ 0.0 } ) );
           && dumpMatch ( a, refVector5 ) );

    //a.print();
    //b.print();
  assert ( a == b );

  // bonus
  /*a[2] = 4;
  a[1] = -3;
  b[3] = 7;
  out . str ("");
  out << polynomial_variable ( "y" ) << "a=" << a << ", b=" << b;
  assert ( out . str () == "a=4*y^2 - 3*y^1, b=7*y^3" );

  out . str ("");
  out << polynomial_variable ( "test" ) << c;
  assert ( out . str () == "2*test^8 + 7*test^6 - 20*test^5" );*/
  return 0;
}
#endif /* __PROGTEST__ */
