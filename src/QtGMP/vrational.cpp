#include "qtgmp.h"

#ifdef Q_OS_WIN
#include <mpir/mpir.h>
#include <mpfr/mpfr.h>
#else
#include <gmp/gmp.h>
#include <mpfr/mpfr.h>
#endif

typedef struct         {
  gmp_randstate_t ranx ;
} RANDSTATE            ;

#define IsNull(item)               (NULL==(item))
#define nKickOut(Condition,Result) if (Condition) return (Result)
#define ME                         (*this)
#define MPQ                        (*((mpq_t *)data()))
#define RANX(d)                    ((RANDSTATE *)d.data())

vrational:: vrational  (void)
          : QByteArray (    )
{
  resize     ( sizeof(mpq_t) ) ;
  ::mpq_init ( MPQ           ) ;
}

vrational:: vrational  (const vrational & v)
          : QByteArray (    )
{
  mpq_t * s = (mpq_t *) v . data ( ) ;
  resize     ( sizeof(mpq_t) )       ;
  ::mpq_init ( MPQ           )       ;
  ::mpq_set  ( MPQ , *s      )       ;
}

vrational:: vrational  (const double v)
          : QByteArray (    )
{
  resize      ( sizeof(mpq_t) ) ;
  ::mpq_init  ( MPQ           ) ;
  ::mpq_set_d ( MPQ , v       ) ;
}

vrational:: vrational  (const vdouble & v)
          : QByteArray (    )
{
  mpf_t * s = (mpf_t *) v . data ( ) ;
  resize      ( sizeof(mpq_t) )      ;
  ::mpq_init  ( MPQ           )      ;
  ::mpq_set_f ( MPQ , *s      )      ;
}

vrational:: vrational  (const char * v)
          : QByteArray (    )
{
  resize        ( sizeof(mpq_t) ) ;
  ::mpq_init    ( MPQ           ) ;
  if ( NULL == v ) return         ;
  ::mpq_set_str ( MPQ , v , 10  ) ;
}

vrational:: vrational  (const std::string & v)
          : QByteArray (    )
{
  resize        ( sizeof(mpq_t) )                     ;
  ::mpq_init    ( MPQ           )                     ;
  if ( v . size ( ) <= 0 ) return                     ;
  ::mpq_set_str ( MPQ , (char *) v . data ( ) , 10  ) ;
}

vrational:: vrational  (const QString &  v)
          : QByteArray (    )
{
  resize        ( sizeof(mpq_t) )                    ;
  ::mpq_init    ( MPQ           )                    ;
  if ( v . length ( ) <= 0 ) return                  ;
  ::mpq_set_str ( MPQ , (char *) v . data ( ) , 10 ) ;
}

vrational::~vrational (void)
{
  ::mpq_clear ( MPQ ) ;
}

void vrational::Numerator(vlong & v)
{
  mpq_t * m = (mpq_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  ::mpq_get_num ( *s , *m )         ;
}

void vrational::Denominator(vlong & v)
{
  mpq_t * m = (mpq_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  ::mpq_get_den ( *s , *m )         ;
}

void vrational::setNumerator(vlong & v)
{
  mpq_t * m = (mpq_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  ::mpq_set_num ( *m , *s )         ;
}

void vrational::setDenominator(vlong & v)
{
  mpq_t * m = (mpq_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  ::mpq_set_den ( *m , *s )         ;
}

vrational & vrational::operator = (vlong & v)
{
  mpq_t * m = (mpq_t *)     data ( ) ;
  mpz_t * s = (mpz_t *) v . data ( ) ;
  ::mpq_set_z ( *m , *s )            ;
  return ME                          ;
}

vrational & vrational::operator = (vdouble & v)
{
  mpq_t * m = (mpq_t *)    data ( ) ;
  mpf_t * s = (mpf_t *)v . data ( ) ;
  ::mpq_set_f ( *m , *s )           ;
  return ME                         ;
}

vrational & vrational::operator = (vrational & v)
{
  mpq_t * m = (mpq_t *)    data ( ) ;
  mpq_t * s = (mpq_t *)v . data ( ) ;
  ::mpq_set ( *m , *s )             ;
  return ME                         ;
}

vrational & vrational::operator = (double v)
{
  ::mpq_set_d ( MPQ , v ) ;
  return ME               ;
}

vrational & vrational::operator = (const char * v)
{
  if ( NULL == v )               {
    clear ( )                    ;
    return ME                    ;
  }                              ;
  ::mpq_set_str ( MPQ , v , 10 ) ;
  return ME                      ;
}

vrational & vrational::operator = (std::string & v)
{
  ::mpq_set_str ( MPQ , (char *) v . data() , 10 ) ;
  return ME                                        ;
}

vrational & vrational::operator = (QString & v)
{
  ::mpq_set_str ( MPQ , (char *) v . constData() , 10 ) ;
  return ME                                             ;
}

vrational & vrational::operator += (vrational & v)
{
  mpq_t * m = (mpq_t *)     data ( ) ;
  mpq_t * s = (mpq_t *) v . data ( ) ;
  ::mpq_add ( *m , *m , *s )         ;
  return ME                          ;
}

vrational & vrational::operator -= (vrational & v)
{
  mpq_t * m = (mpq_t *)     data ( ) ;
  mpq_t * s = (mpq_t *) v . data ( ) ;
  ::mpq_sub ( *m , *m , *s )         ;
  return ME                          ;
}

vrational & vrational::operator *= (vrational & v)
{
  mpq_t * m = (mpq_t *)     data ( ) ;
  mpq_t * s = (mpq_t *) v . data ( ) ;
  ::mpq_mul ( *m , *m , *s )         ;
  return ME                          ;
}

vrational & vrational::operator /= (vrational & v)
{
  mpq_t * m = (mpq_t *)     data ( ) ;
  mpq_t * s = (mpq_t *) v . data ( ) ;
  ::mpq_div ( *m , *m , *s )         ;
  return ME                          ;
}

vrational & vrational::swap(vrational & v)
{
  mpq_t * m = (mpq_t *)     data ( ) ;
  mpq_t * s = (mpq_t *) v . data ( ) ;
  ::mpq_swap ( *m , *s )             ;
  return ME                          ;
}

vrational & vrational::neg(void)
{
  ::mpq_neg ( MPQ , MPQ ) ;
  return ME               ;
}

vrational & vrational::abs(void)
{
  ::mpq_abs ( MPQ , MPQ ) ;
  return ME               ;
}

vrational & vrational::inverse(void)
{
  ::mpq_inv ( MPQ , MPQ ) ;
  return ME               ;
}

vrational & vrational::shift(unsigned long long n)
{
  ::mpq_mul_2exp ( MPQ , MPQ , n ) ;
  return ME                        ;
}

vrational & vrational::rshift(unsigned long long n)
{
  ::mpq_div_2exp ( MPQ , MPQ , n ) ;
  return ME                        ;
}

int vrational::compare(vrational & v)
{
  mpq_t * m = (mpq_t *)    data ( ) ;
  mpq_t * s = (mpq_t *)v . data ( ) ;
  return ::mpq_cmp ( *m , *s )      ;
}

bool vrational::equal(vrational & v)
{
  mpq_t * m = (mpq_t *)    data ( ) ;
  mpq_t * s = (mpq_t *)v . data ( ) ;
  return ::mpq_equal ( *m , *s )!=0 ;
  return false                      ;
}

int vrational::sign(void)
{
  return mpq_sgn ( MPQ ) ;
}

void vrational::canonicalize(void)
{
  ::mpq_canonicalize ( MPQ ) ;
}

void vrational::clear(void)
{
  ::mpq_clear ( MPQ ) ;
}

double vrational::toDouble(void)
{
  return ::mpq_get_d(MPQ) ;
}

QString vrational::toString(int base)
{
  QString S                                ;
  char *  s = ::mpq_get_str(NULL,base,MPQ) ;
  nKickOut ( IsNull(s) , S )               ;
  S = s                                    ;
  delete [] s                              ;
  return S                                 ;
}
