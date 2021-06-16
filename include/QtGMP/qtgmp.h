/****************************************************************************
 *                                                                          *
 * Copyright (C) 2007 ~ 2016 Neutrino International Inc.                    *
 *                                                                          *
 * Author : Brian Lin <lin.foxman@gmail.com>, Skype: wolfram_lin            *
 *                                                                          *
 * QtGMP acts as an interface between Qt and GMP library.                   *
 * Please keep QtGMP as simple as possible.                                 *
 *                                                                          *
 * Qt Version   : 5.6.0                                                     *
 * CIOS Version : 1.6.0                                                     *
 *                                                                          *
 ****************************************************************************/

#ifndef QT_GMP_H
#define QT_GMP_H

#include <QtCore>

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#    if defined(QT_BUILD_QTGMP_LIB)
#      define Q_GMP_EXPORT Q_DECL_EXPORT
#    else
#      define Q_GMP_EXPORT Q_DECL_IMPORT
#    endif
#else
#      define Q_GMP_EXPORT
#endif

class Q_GMP_EXPORT vrandom    ;
class Q_GMP_EXPORT vlong      ;
class Q_GMP_EXPORT vdouble    ;
class Q_GMP_EXPORT vrational  ;
class Q_GMP_EXPORT vprecision ;

class Q_GMP_EXPORT vrandom : public QByteArray
{ // GMP or MPIR - Multiple Precision Arithmetic Random State
  public:

    explicit      vrandom      (void) ;
                  vrandom      (const vrandom & random) ;
    virtual      ~vrandom      (void) ;

    void          clear        (void) ;
    void          Default      (void) ;
    void          Mersenne     (void) ;
    void          Congruential (vlong & v,unsigned long c,unsigned long long e) ;
    int           Congruential (unsigned long long size) ;

    void          Seed         (vlong & v) ;
    void          Seed         (unsigned long c) ;

    unsigned long urandomb     (unsigned long n) ;
    unsigned long urandomm     (unsigned long n) ;

  protected:

  private:

} ;

class Q_GMP_EXPORT vlong : public QByteArray
{ // GMP or MPIR - Multiple Precision Arithmetic Integer Number
  public:

    explicit           vlong         (void) ;
                       vlong         (const vlong & v) ;
                       vlong         (const unsigned long v) ;
                       vlong         (const long v) ;
                       vlong         (const char * v,const int base = 10) ;
                       vlong         (const std::string & v,const int base = 10) ;
                       vlong         (const QString & v,const int base = 10) ;
    virtual           ~vlong         (void) ;

    vlong &            operator  =   (vlong & v) ;
    vlong &            operator  =   (unsigned long v) ;
    vlong &            operator  =   (long v) ;
    vlong &            operator  =   (const char * v) ;
    vlong &            operator  =   (std::string & v) ;
    vlong &            operator  =   (QString & v) ;
    vlong &            operator  =   (double v) ;
    vlong &            operator  =   (vdouble & v) ;
    vlong &            operator  =   (vrational & v) ;

    vlong &            operator +=   (vlong & v) ;
    vlong &            operator +=   (unsigned long v) ;
    vlong &            operator +=   (long v) ;
    vlong &            operator +=   (const char * v) ;
    vlong &            operator +=   (std::string & v) ;
    vlong &            operator +=   (QString & v) ;

    vlong &            operator -=   (vlong & v) ;
    vlong &            operator -=   (unsigned long v) ;
    vlong &            operator -=   (long v) ;
    vlong &            operator -=   (const char * v) ;
    vlong &            operator -=   (std::string & v) ;
    vlong &            operator -=   (QString & v) ;

    vlong &            operator *=   (vlong & v) ;
    vlong &            operator *=   (unsigned long v) ;
    vlong &            operator *=   (long v) ;
    vlong &            operator *=   (const char * v) ;
    vlong &            operator *=   (std::string & v) ;
    vlong &            operator *=   (QString & v) ;

    vlong &            operator /=   (vlong & v) ;
    vlong &            operator /=   (unsigned long v) ;
    vlong &            operator /=   (long v) ;
    vlong &            operator /=   (const char * v) ;
    vlong &            operator /=   (std::string & v) ;
    vlong &            operator /=   (QString & v) ;

    vlong &            operator %=   (vlong & v) ;
    vlong &            operator %=   (unsigned long v) ;
    vlong &            operator %=   (long v) ;
    vlong &            operator %=   (const char * v) ;
    vlong &            operator %=   (std::string & v) ;
    vlong &            operator %=   (QString & v) ;

    bool               operator >    (vlong & v) ;
    bool               operator >    (unsigned long v) ;
    bool               operator >    (long v) ;
    bool               operator >    (const char * v) ;
    bool               operator >    (std::string & v) ;
    bool               operator >    (QString & v) ;

    bool               operator <    (vlong & v) ;
    bool               operator <    (unsigned long v) ;
    bool               operator <    (long v) ;
    bool               operator <    (const char * v) ;
    bool               operator <    (std::string & v) ;
    bool               operator <    (QString & v) ;

    bool               operator >=   (vlong & v) ;
    bool               operator >=   (unsigned long v) ;
    bool               operator >=   (long v) ;
    bool               operator >=   (const char * v) ;
    bool               operator >=   (std::string & v) ;
    bool               operator >=   (QString & v) ;

    bool               operator <=   (vlong & v) ;
    bool               operator <=   (unsigned long v) ;
    bool               operator <=   (long v) ;
    bool               operator <=   (const char * v) ;
    bool               operator <=   (std::string & v) ;
    bool               operator <=   (QString & v) ;

    bool               operator ==   (vlong & v) ;
    bool               operator ==   (unsigned long v) ;
    bool               operator ==   (long v) ;
    bool               operator ==   (const char * v) ;
    bool               operator ==   (std::string & v) ;
    bool               operator ==   (QString & v) ;

    bool               operator !=   (vlong & v) ;
    bool               operator !=   (unsigned long v) ;
    bool               operator !=   (long v) ;
    bool               operator !=   (const char * v) ;
    bool               operator !=   (std::string & v) ;
    bool               operator !=   (QString & v) ;

    int                compare       (vlong & v) ;
    int                compare       (unsigned long v) ;
    int                compare       (long v) ;
    int                compare       (const char * v) ;
    int                compare       (std::string & v) ;
    int                compare       (QString & v) ;

    vlong &            setBit        (unsigned long long index) ;
    vlong &            clearBit      (unsigned long long index) ;
    vlong &            complement    (unsigned long long index) ;
    int                bit           (unsigned long long index) ;

    vlong &            operator ++   (void) ;
    vlong &            operator --   (void) ;
    vlong &            operator &=   (vlong & v) ;
    vlong &            operator |=   (vlong & v) ;
    vlong &            operator ^=   (vlong & v) ;
    vlong &            operator ~    (void) ;
    vlong &            operator ^    (unsigned long n) ; // A ^ n

    vlong &            neg           (void) ;
    vlong &            abs           (void) ;
    vlong &            swap          (vlong & v) ;
    vlong &            square        (void) ;
    vlong &            root          (unsigned long n) ;
    vlong &            sqrt          (void) ;
    vlong &            shift         (unsigned long long bits) ;
    vlong &            factorial     (unsigned long n); // assign this = n!
    vlong &            fibonacci     (unsigned long n); // assign this = Fibonacci (n-th)
    vlong &            binomial      (unsigned long k); // assign this = binomial coefficient
    vlong &            lucas         (unsigned long k); // assign this = Lucas number

    vlong &            gcd           ( vlong & a , vlong & b ) ;
    vlong &            lcm           ( vlong & a , vlong & b ) ;
    int                jacobi        ( vlong & n ) ;
    int                legendre      ( vlong & p ) ;
    int                kronecker     ( vlong & p ) ;
    int                invert        ( vlong & modulo , vlong & result ) ;
    int                MillerRabin   (int reps) ;
    int                PerfectPower  (void) ;
    int                PerfectSquare (void) ;

    vlong &            urandomb      ( vrandom & r , unsigned long long n ) ;
    vlong &            urandomm      ( vrandom & r , vlong & n ) ;
    vlong &            rrandomb      ( vrandom & r , unsigned long long n ) ;

    unsigned long long population    (void) ;
    unsigned long long hamdist       (vlong & v) ;
    unsigned long long scan0         (unsigned long long startingBit) ;
    unsigned long long scan1         (unsigned long long startingBit) ;

    bool               odd           (void) ;
    bool               even          (void) ;
    int                sign          (void) ;
    qint64             digits        (int base = 10) ;

    void               clear         (void) ;

    bool               isULong       (void) ;
    bool               isLong        (void) ;
    bool               isUInt        (void) ;
    bool               isInt         (void) ;
    bool               isUShort      (void) ;
    bool               isShort       (void) ;

    long               toLong        (void) ;
    unsigned long      toULong       (void) ;
    QString            String        (int base = 10) ;

  protected:

  private:

} ;

class Q_GMP_EXPORT vdouble : public QByteArray
{ // GMP or MPIR - Multiple Precision Arithmetic Integer Number
  public:

    explicit vdouble (void) ;
             vdouble (const vdouble & v) ;
             vdouble (const double v) ;
             vdouble (const double v,const unsigned long prec) ;
             vdouble (const unsigned long v) ;
             vdouble (const long v) ;
             vdouble (const char * v,const int base = 10) ;
             vdouble (const std::string & v,const int base = 10) ;
             vdouble (const QString & v,const int base = 10) ;
    virtual ~vdouble (void) ;

    static unsigned long defaultPrecision    (void) ;
    static unsigned long setDefaultPrecision (unsigned long prec) ;

    unsigned long precision    (void) ;
    unsigned long setPrecision (unsigned long prec) ;

    vdouble & operator  = (vdouble & v) ;
    vdouble & operator  = (double v) ;
    vdouble & operator  = (unsigned long v) ;
    vdouble & operator  = (long v) ;
    vdouble & operator  = (const char * v) ;
    vdouble & operator  = (std::string & v) ;
    vdouble & operator  = (QString & v) ;
    vdouble & operator  = (vlong & v) ;
    vdouble & operator  = (vrational & v) ;

    vdouble & operator += (vdouble & v) ;
    vdouble & operator += (double v) ;
    vdouble & operator += (const char * v) ;
    vdouble & operator += (std::string & v) ;
    vdouble & operator += (QString & v) ;

    vdouble & operator -= (vdouble & v) ;
    vdouble & operator -= (double v) ;
    vdouble & operator -= (const char * v) ;
    vdouble & operator -= (std::string & v) ;
    vdouble & operator -= (QString & v) ;

    vdouble & operator *= (vdouble & v) ;
    vdouble & operator *= (double v) ;
    vdouble & operator *= (const char * v) ;
    vdouble & operator *= (std::string & v) ;
    vdouble & operator *= (QString & v) ;

    vdouble & operator /= (vdouble & v) ;
    vdouble & operator /= (double v) ;
    vdouble & operator /= (const char * v) ;
    vdouble & operator /= (std::string & v) ;
    vdouble & operator /= (QString & v) ;

    bool      operator >  (vdouble & v) ;
    bool      operator >  (double v) ;
    bool      operator >  (const char * v) ;
    bool      operator >  (std::string & v) ;
    bool      operator >  (QString & v) ;

    bool      operator <  (vdouble & v) ;
    bool      operator <  (double v) ;
    bool      operator <  (const char * v) ;
    bool      operator <  (std::string & v) ;
    bool      operator <  (QString & v) ;

    bool      operator >= (vdouble & v) ;
    bool      operator >= (double v) ;
    bool      operator >= (const char * v) ;
    bool      operator >= (std::string & v) ;
    bool      operator >= (QString & v) ;

    bool      operator <= (vdouble & v) ;
    bool      operator <= (double v) ;
    bool      operator <= (const char * v) ;
    bool      operator <= (std::string & v) ;
    bool      operator <= (QString & v) ;

    bool      operator == (vdouble & v) ;
    bool      operator == (double v) ;
    bool      operator == (const char * v) ;
    bool      operator == (std::string & v) ;
    bool      operator == (QString & v) ;

    bool      operator != (vdouble & v) ;
    bool      operator != (double v) ;
    bool      operator != (const char * v) ;
    bool      operator != (std::string & v) ;
    bool      operator != (QString & v) ;

    vdouble & operator ^  (unsigned long n) ; // A ^ n

    int       compare     (vdouble & v) ;
    int       compare     (double v) ;
    int       compare     (const char * v) ;
    int       compare     (std::string & v) ;
    int       compare     (QString & v) ;

    int       equal       (vdouble & v,unsigned long long bits) ;

    vdouble & neg         (void) ;
    vdouble & abs         (void) ;
    vdouble & ceil        (void) ;
    vdouble & floor       (void) ;
    vdouble & truncate    (void) ;
    vdouble & swap        (vdouble & v) ;
    vdouble & shift       (unsigned long long bits) ;
    vdouble & rshift      (unsigned long long bits) ;
    vdouble & square      (void) ;
    vdouble & sqrt        (void) ;

    vdouble & urandomb    (vrandom & r,unsigned long long n) ;
    vdouble & random2     (long long size,long exp) ;

    int       sign        (void) ;

    bool      isULong     (void) ;
    bool      isLong      (void) ;
    bool      isUInt      (void) ;
    bool      isInt       (void) ;
    bool      isUShort    (void) ;
    bool      isShort     (void) ;

    void      clear       (void) ;

    int       toInt       (void) ;
    double    toDouble    (void) ;
    QString   String      (int digits,int base = 10) ;

  protected:

  private:

} ;

class Q_GMP_EXPORT vrational : public QByteArray
{ // GMP or MPIR - Multiple Precision Arithmetic Integer Number
  public:

    explicit    vrational      (void) ;
                vrational      (const vrational & value) ;
                vrational      (const double value) ;
                vrational      (const vdouble & value) ;
                vrational      (const char * value) ;
                vrational      (const std::string & value) ;
                vrational      (const QString & value) ;
    virtual    ~vrational      (void) ;

    void        Numerator      (vlong & num) ;
    void        Denominator    (vlong & den) ;

    void        setNumerator   (vlong & num) ;
    void        setDenominator (vlong & den) ;

    vrational & operator     = (vlong & value) ;
    vrational & operator     = (vdouble & value) ;
    vrational & operator     = (vrational & value) ;
    vrational & operator     = (double value) ;
    vrational & operator     = (const char * value) ;
    vrational & operator     = (std::string & value) ;
    vrational & operator     = (QString & value) ;

    vrational & operator    += (vrational & rational) ;
    vrational & operator    -= (vrational & rational) ;
    vrational & operator    *= (vrational & rational) ;
    vrational & operator    /= (vrational & rational) ;

    vrational & swap           (vrational & rational) ;
    vrational & neg            (void) ;
    vrational & abs            (void) ;
    vrational & inverse        (void) ;
    vrational & shift          (unsigned long long n) ;
    vrational & rshift         (unsigned long long n) ;

    int         compare        (vrational & rational) ;
    bool        equal          (vrational & rational) ;

    int         sign           (void) ;

    void        canonicalize   (void) ;
    void        clear          (void) ;

    double      toDouble       (void) ;
    QString     toString       (int base = 10) ;

  protected:

  private:

} ;

class Q_GMP_EXPORT vprecision : public QByteArray
{ // MPFR floating-point functions
  public :

    typedef enum {
      RNDN  =  0 , /* round to nearest, with ties to even */
      RNDZ  =  1 , /* round toward zero */
      RNDU  =  2 , /* round toward +Inf */
      RNDD  =  3 , /* round toward -Inf */
      RNDA  =  4 , /* round away from zero */
      RNDF  =  5 , /* faithful rounding (not implemented yet) */
      RNDNA = -1 } /* round to nearest, with ties away from zero (mpfr_round) */
      RoundTypes ;

    explicit      vprecision    (void) ;
                  vprecision    (const int precision) ;
                  vprecision    (const unsigned long v,int rnd = RNDN) ;
                  vprecision    (const long          v,int rnd = RNDN) ;
                  vprecision    (const float         v,int rnd = RNDN) ;
                  vprecision    (const double        v,int rnd = RNDN) ;
                  vprecision    (const long double   v,int rnd = RNDN) ;
                  vprecision    (const vlong       & v,int rnd = RNDN) ;
                  vprecision    (const vdouble     & v,int rnd = RNDN) ;
                  vprecision    (const vrational   & v,int rnd = RNDN) ;
                  vprecision    (const vprecision  & v,int rnd = RNDN) ;
                  vprecision    (const char        * v,int base = 10,int rnd = RNDN) ;
                  vprecision    (const std::string & v,int base = 10,int rnd = RNDN) ;
                  vprecision    (const QString     & v,int base = 10,int rnd = RNDN) ;
    virtual      ~vprecision    (void) ;

    void          setPrecision  (int precision) ;

    vprecision &  operator  =   (unsigned long v) ; // MPFR_RNDN
    vprecision &  operator  =   (long          v) ; // MPFR_RNDN
    vprecision &  operator  =   (float         v) ; // MPFR_RNDN
    vprecision &  operator  =   (double        v) ; // MPFR_RNDN
    vprecision &  operator  =   (long double   v) ; // MPFR_RNDN
    vprecision &  operator  =   (vlong       & v) ; // MPFR_RNDN
    vprecision &  operator  =   (vdouble     & v) ; // MPFR_RNDN
    vprecision &  operator  =   (vrational   & v) ; // MPFR_RNDN
    vprecision &  operator  =   (vprecision  & v) ; // MPFR_RNDN
    vprecision &  operator  =   (const char  * v) ; // MPFR_RNDN
    vprecision &  operator  =   (std::string & v) ; // MPFR_RNDN
    vprecision &  operator  =   (QString     & v) ; // MPFR_RNDN

    vprecision &  operator +=   (vlong & v) ;
    vprecision &  operator +=   (vrational & v) ;
    vprecision &  operator +=   (vprecision & v) ;
    vprecision &  operator +=   (unsigned long v) ;
    vprecision &  operator +=   (long v) ;
    vprecision &  operator +=   (double v) ;
    vprecision &  operator +=   (const char * v) ;
    vprecision &  operator +=   (std::string & v) ;
    vprecision &  operator +=   (QString & v) ;

    vprecision &  operator -=   (vlong & v) ;
    vprecision &  operator -=   (vrational & v) ;
    vprecision &  operator -=   (vprecision & v) ;
    vprecision &  operator -=   (unsigned long v) ;
    vprecision &  operator -=   (long v) ;
    vprecision &  operator -=   (double v) ;
    vprecision &  operator -=   (const char * v) ;
    vprecision &  operator -=   (std::string & v) ;
    vprecision &  operator -=   (QString & v) ;

    vprecision &  operator *=   (vlong & v) ;
    vprecision &  operator *=   (vrational & v) ;
    vprecision &  operator *=   (vprecision & v) ;
    vprecision &  operator *=   (unsigned long v) ;
    vprecision &  operator *=   (long v) ;
    vprecision &  operator *=   (double v) ;
    vprecision &  operator *=   (const char * v) ;
    vprecision &  operator *=   (std::string & v) ;
    vprecision &  operator *=   (QString & v) ;

    vprecision &  operator /=   (vlong & v) ;
    vprecision &  operator /=   (vrational & v) ;
    vprecision &  operator /=   (vprecision & v) ;
    vprecision &  operator /=   (unsigned long v) ;
    vprecision &  operator /=   (long v) ;
    vprecision &  operator /=   (double v) ;
    vprecision &  operator /=   (const char * v) ;
    vprecision &  operator /=   (std::string & v) ;
    vprecision &  operator /=   (QString & v) ;

    bool          operator >    (vlong & v) ;
    bool          operator >    (vdouble & v) ;
    bool          operator >    (vrational & v) ;
    bool          operator >    (vprecision & v) ;
    bool          operator >    (unsigned long v) ;
    bool          operator >    (long v) ;
    bool          operator >    (double v) ;
    bool          operator >    (long double v) ;
    bool          operator >    (const char * v) ;
    bool          operator >    (std::string & v) ;
    bool          operator >    (QString & v) ;

    bool          operator <    (vlong & v) ;
    bool          operator <    (vdouble & v) ;
    bool          operator <    (vrational & v) ;
    bool          operator <    (vprecision & v) ;
    bool          operator <    (unsigned long v) ;
    bool          operator <    (long v) ;
    bool          operator <    (double v) ;
    bool          operator <    (long double v) ;
    bool          operator <    (const char * v) ;
    bool          operator <    (std::string & v) ;
    bool          operator <    (QString & v) ;

    bool          operator >=   (vlong & v) ;
    bool          operator >=   (vdouble & v) ;
    bool          operator >=   (vrational & v) ;
    bool          operator >=   (vprecision & v) ;
    bool          operator >=   (unsigned long v) ;
    bool          operator >=   (long v) ;
    bool          operator >=   (double v) ;
    bool          operator >=   (long double v) ;
    bool          operator >=   (const char * v) ;
    bool          operator >=   (std::string & v) ;
    bool          operator >=   (QString & v) ;

    bool          operator <=   (vlong & v) ;
    bool          operator <=   (vdouble & v) ;
    bool          operator <=   (vrational & v) ;
    bool          operator <=   (vprecision & v) ;
    bool          operator <=   (unsigned long v) ;
    bool          operator <=   (long v) ;
    bool          operator <=   (double v) ;
    bool          operator <=   (long double v) ;
    bool          operator <=   (const char * v) ;
    bool          operator <=   (std::string & v) ;
    bool          operator <=   (QString & v) ;

    bool          operator ==   (vlong & v) ;
    bool          operator ==   (vdouble & v) ;
    bool          operator ==   (vrational & v) ;
    bool          operator ==   (vprecision & v) ;
    bool          operator ==   (unsigned long v) ;
    bool          operator ==   (long v) ;
    bool          operator ==   (double v) ;
    bool          operator ==   (long double v) ;
    bool          operator ==   (const char * v) ;
    bool          operator ==   (std::string & v) ;
    bool          operator ==   (QString & v) ;

    bool          operator !=   (vlong & v) ;
    bool          operator !=   (vdouble & v) ;
    bool          operator !=   (vrational & v) ;
    bool          operator !=   (vprecision & v) ;
    bool          operator !=   (unsigned long v) ;
    bool          operator !=   (long v) ;
    bool          operator !=   (double v) ;
    bool          operator !=   (long double v) ;
    bool          operator !=   (const char * v) ;
    bool          operator !=   (std::string & v) ;
    bool          operator !=   (QString & v) ;

    int           compare       (vlong & v) ;
    int           compare       (vdouble & v) ;
    int           compare       (vrational & v) ;
    int           compare       (vprecision & v) ;
    int           compare       (unsigned long v) ;
    int           compare       (long v) ;
    int           compare       (double v) ;
    int           compare       (long double v) ;
    int           compare       (const char * v) ;
    int           compare       (std::string & v) ;
    int           compare       (QString & v) ;

    bool          isULong       (int rnd = RNDN) ;
    bool          isLong        (int rnd = RNDN) ;
    bool          isUInt        (int rnd = RNDN) ;
    bool          isInt         (int rnd = RNDN) ;
    bool          isUShort      (int rnd = RNDN) ;
    bool          isShort       (int rnd = RNDN) ;

    bool          isNan         (void) ;
    bool          isInf         (void) ;
    bool          isNumber      (void) ;
    bool          isZero        (void) ;
    bool          isRegular     (void) ;

    vprecision &  set           (unsigned long v,int rnd = RNDN) ;
    vprecision &  set           (long          v,int rnd = RNDN) ;
    vprecision &  set           (float         v,int rnd = RNDN) ;
    vprecision &  set           (double        v,int rnd = RNDN) ;
    vprecision &  set           (long double   v,int rnd = RNDN) ;
    vprecision &  set           (vlong       & v,int rnd = RNDN) ;
    vprecision &  set           (vdouble     & v,int rnd = RNDN) ;
    vprecision &  set           (vrational   & v,int rnd = RNDN) ;
    vprecision &  set           (vprecision  & v,int rnd = RNDN) ;
    vprecision &  set           (const char  * v,int base = 10,int rnd = RNDN) ; // MPFR_RNDN
    vprecision &  set           (std::string & v,int base = 10,int rnd = RNDN) ; // MPFR_RNDN
    vprecision &  set           (QString     & v,int base = 10,int rnd = RNDN) ; // MPFR_RNDN

    vprecision &  setNan        (void) ;
    vprecision &  setInf        (int sign = 1) ;
    vprecision &  setZero       (int sign = 1) ;

    vprecision &  swap          (vprecision  & v) ;

    vprecision &  ceil          (void) ;
    vprecision &  floor         (void) ;
    vprecision &  round         (void) ;
    vprecision &  truncate      (void) ;
    vprecision &  rint          (int rnd = RNDN) ;
    vprecision &  rintCeil      (int rnd = RNDN) ;
    vprecision &  rintFloor     (int rnd = RNDN) ;
    vprecision &  rintRound     (int rnd = RNDN) ;
    vprecision &  rintTruncate  (int rnd = RNDN) ;
    vprecision &  fractional    (int rnd = RNDN) ;
    vprecision &  modf          (vprecision & v,int rnd = RNDN) ;
    vprecision &  fmod          (vprecision & v,int rnd = RNDN) ;
    vprecision &  remainder     (vprecision & v,int rnd = RNDN) ;
    vprecision &  sqrt          (int rnd = RNDN) ;
    vprecision &  reciprocal    (int rnd = RNDN) ; // reciprocal square root
    vprecision &  cbrt          (int rnd = RNDN) ;
    vprecision &  root          (unsigned long k,int rnd = RNDN) ;
    vprecision &  pow           (unsigned long n,int rnd = RNDN) ;
    vprecision &  pow           (long n,int rnd = RNDN) ;
    vprecision &  pow           (vlong & v,int rnd = RNDN) ;
    vprecision &  pow           (vprecision & v,int rnd = RNDN) ;
    vprecision &  neg           (int rnd = RNDN) ;
    vprecision &  abs           (int rnd = RNDN) ;
    vprecision &  dim           (vprecision & v,int rnd = RNDN) ;

    vprecision &  log           (int rnd = RNDN) ;
    vprecision &  log2          (int rnd = RNDN) ;
    vprecision &  log10         (int rnd = RNDN) ;
    vprecision &  log1p         (int rnd = RNDN) ;

    vprecision &  exp           (int rnd = RNDN) ;
    vprecision &  exp2          (int rnd = RNDN) ;
    vprecision &  exp10         (int rnd = RNDN) ;
    vprecision &  expm1         (int rnd = RNDN) ;
    vprecision &  expIntegral   (int rnd = RNDN) ;

    vprecision &  cos           (int rnd = RNDN) ;
    vprecision &  sin           (int rnd = RNDN) ;
    vprecision &  tan           (int rnd = RNDN) ;
    vprecision &  sec           (int rnd = RNDN) ;
    vprecision &  csc           (int rnd = RNDN) ;
    vprecision &  cot           (int rnd = RNDN) ;
    vprecision &  acos          (int rnd = RNDN) ;
    vprecision &  asin          (int rnd = RNDN) ;
    vprecision &  atan          (int rnd = RNDN) ;
    vprecision &  cosh          (int rnd = RNDN) ;
    vprecision &  sinh          (int rnd = RNDN) ;
    vprecision &  tanh          (int rnd = RNDN) ;
    vprecision &  sech          (int rnd = RNDN) ;
    vprecision &  csch          (int rnd = RNDN) ;
    vprecision &  coth          (int rnd = RNDN) ;
    vprecision &  acosh         (int rnd = RNDN) ;
    vprecision &  asinh         (int rnd = RNDN) ;
    vprecision &  atanh         (int rnd = RNDN) ;

    vprecision &  atan2         (vprecision & x,int rnd = RNDN) ;
    vprecision &  factorial     (unsigned long n,int rnd = RNDN) ;

    vprecision &  li2           (int rnd = RNDN) ;
    vprecision &  gamma         (int rnd = RNDN) ;
    vprecision &  lngamma       (int rnd = RNDN) ;
    vprecision &  digamma       (int rnd = RNDN) ;
    vprecision &  zeta          (int rnd = RNDN) ;
    vprecision &  erf           (int rnd = RNDN) ;
    vprecision &  erfc          (int rnd = RNDN) ;

    vprecision &  j0            (int rnd = RNDN) ;
    vprecision &  j1            (int rnd = RNDN) ;
    vprecision &  jn            (long n,int rnd = RNDN) ;

    vprecision &  y0            (int rnd = RNDN) ;
    vprecision &  y1            (int rnd = RNDN) ;
    vprecision &  yn            (long n,int rnd = RNDN) ;

    vprecision &  agm           (vprecision & y,int rnd = RNDN) ;
    vprecision &  hypot         (vprecision & y,int rnd = RNDN) ;
    vprecision &  airy          (int rnd = RNDN) ;

    vprecision &  urandomb      (vrandom & r) ;
    vprecision &  urandom       (vrandom & r,int rnd = RNDN) ;

    long          exponent      (void) ;
    int           signBit       (void) ;
    int           setSign       (int s,int rnd = RNDN) ;
    int           sign          (void) ;

    void          FreeCache     (void) ;
    void          clear         (void) ;

    vlong         toVLong       (int rnd = RNDN) ;
    vdouble       toVDouble     (int rnd = RNDN) ;
    float         toFloat       (int rnd = RNDN) ;
    double        toDouble      (int rnd = RNDN) ;
    long double   toLongDouble  (int rnd = RNDN) ;
    long          toLong        (int rnd = RNDN) ;
    unsigned long toULong       (int rnd = RNDN) ;
    QString       String        (int digits,int base = 10,int rnd = RNDN) ;

  protected:

  private:

} ;

Q_DECLARE_METATYPE(vrandom)
Q_DECLARE_METATYPE(vlong)
Q_DECLARE_METATYPE(vdouble)
Q_DECLARE_METATYPE(vrational)
Q_DECLARE_METATYPE(vprecision)

QT_END_NAMESPACE

#endif
