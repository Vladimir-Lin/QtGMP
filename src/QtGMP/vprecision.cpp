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
#define MPFR                       (*((mpfr_t *)data()))
#define RANX(d)                    ((RANDSTATE *)d.data())

vprecision:: vprecision (void)
           : QByteArray (    )
{
  resize      ( sizeof(mpfr_t) ) ;
  ::mpfr_init ( MPFR           ) ;
}

vprecision:: vprecision (const int precision)
           : QByteArray (                   )
{
  resize       ( sizeof(mpfr_t)   ) ;
  ::mpfr_init2 ( MPFR , precision ) ;
}

vprecision:: vprecision (const unsigned long v,int rnd)
           : QByteArray (                             )
{
  resize        ( sizeof(mpfr_t)             ) ;
  ::mpfr_init   ( MPFR                       ) ;
  ::mpfr_set_ui ( MPFR , v , (mpfr_rnd_t)rnd ) ;
}

vprecision:: vprecision (const long v,int rnd)
           : QByteArray (                    )
{
  resize        ( sizeof(mpfr_t)              ) ;
  ::mpfr_init   ( MPFR                        ) ;
  ::mpfr_set_si ( MPFR , v , (mpfr_rnd_t) rnd ) ;
}

vprecision:: vprecision (const float v,int rnd)
           : QByteArray (                     )
{
  resize         ( sizeof(mpfr_t)              ) ;
  ::mpfr_init    ( MPFR                        ) ;
  ::mpfr_set_flt ( MPFR , v , (mpfr_rnd_t) rnd ) ;
}

vprecision:: vprecision (const double v,int rnd)
           : QByteArray (                      )
{
  resize       ( sizeof(mpfr_t)              ) ;
  ::mpfr_init  ( MPFR                        ) ;
  ::mpfr_set_d ( MPFR , v , (mpfr_rnd_t) rnd ) ;
}

vprecision:: vprecision (const long double v,int rnd)
           : QByteArray (                           )
{
  resize        ( sizeof(mpfr_t)              ) ;
  ::mpfr_init   ( MPFR                        ) ;
  ::mpfr_set_ld ( MPFR , v , (mpfr_rnd_t) rnd ) ;
}

vprecision:: vprecision (const vlong & v,int rnd)
           : QByteArray (                       )
{
  mpz_t * s = (mpz_t *) v . data ( )            ;
  resize       ( sizeof(mpfr_t)               ) ;
  ::mpfr_init  ( MPFR                         ) ;
  ::mpfr_set_z ( MPFR , *s , (mpfr_rnd_t) rnd ) ;
}

vprecision:: vprecision (const vdouble & v,int rnd)
           : QByteArray (                         )
{
  mpf_t * s = (mpf_t *) v . data ( )            ;
  resize       ( sizeof(mpfr_t)               ) ;
  ::mpfr_init  ( MPFR                         ) ;
  ::mpfr_set_f ( MPFR , *s , (mpfr_rnd_t) rnd ) ;
}

vprecision:: vprecision (const vrational & v,int rnd)
           : QByteArray (                           )
{
  mpq_t * s = (mpq_t *) v . data ( )            ;
  resize       ( sizeof(mpfr_t)               ) ;
  ::mpfr_init  ( MPFR                         ) ;
  ::mpfr_set_q ( MPFR , *s , (mpfr_rnd_t) rnd ) ;
}

vprecision:: vprecision (const vprecision & v,int rnd)
           : QByteArray (                            )
{
  mpfr_t * s = (mpfr_t *) v . data ( )         ;
  resize      ( sizeof(mpfr_t)   )             ;
  ::mpfr_init ( MPFR             )             ;
  ::mpfr_set  ( MPFR , *s , (mpfr_rnd_t) rnd ) ;
}

vprecision:: vprecision (const char * v,int base,int rnd)
           : QByteArray (                               )
{
  resize              ( sizeof(mpfr_t)                     ) ;
  ::mpfr_init_set_str ( MPFR , v , base , (mpfr_rnd_t) rnd ) ;
}

vprecision:: vprecision (const std::string & v,int base,int rnd)
           : QByteArray (                                      )
{
  resize              ( sizeof(mpfr_t) ) ;
  ::mpfr_init_set_str ( MPFR , (const char *) v . data ( ) , base , (mpfr_rnd_t) rnd ) ;
}

vprecision:: vprecision (const QString & v,int base,int rnd)
           : QByteArray (                                     )
{
  resize              ( sizeof(mpfr_t) ) ;
  ::mpfr_init_set_str ( MPFR , (const char *) v . constData ( ) , base , (mpfr_rnd_t) rnd ) ;
}

vprecision::~vprecision (void)
{
  ::mpfr_clear ( MPFR ) ;
}

void vprecision::setPrecision(int precision)
{
  ::mpfr_set_prec( MPFR , precision ) ;
}

vprecision & vprecision::operator = (unsigned long v)
{
  ::mpfr_set_ui ( MPFR , (unsigned long int) v , MPFR_RNDN ) ;
  return ME                                                  ;
}

vprecision & vprecision::operator = (long v)
{
  ::mpfr_set_si ( MPFR , (long int)v , MPFR_RNDN ) ;
  return ME                                        ;
}

vprecision & vprecision::operator = (float v)
{
  ::mpfr_set_flt ( MPFR , v , MPFR_RNDN ) ;
  return ME                               ;
}

vprecision & vprecision::operator = (double v)
{
  ::mpfr_set_d ( MPFR , v , MPFR_RNDN ) ;
  return ME                             ;
}

vprecision & vprecision::operator = (long double v)
{
  ::mpfr_set_ld ( MPFR , v , MPFR_RNDN ) ;
  return ME                              ;
}

vprecision & vprecision::operator = (vlong & v)
{
  mpz_t * Z = (mpz_t *)v . data ( )      ;
  ::mpfr_set_z ( MPFR , *Z , MPFR_RNDN ) ;
  return ME                              ;
}

vprecision & vprecision::operator = (vdouble & v)
{
  mpf_t * Z = (mpf_t *)v . data ( )      ;
  ::mpfr_set_f ( MPFR , *Z , MPFR_RNDN ) ;
  return ME                              ;
}

vprecision & vprecision::operator = (vrational & v)
{
  mpq_t * Z = (mpq_t *)v . data ( )      ;
  ::mpfr_set_q ( MPFR , *Z , MPFR_RNDN ) ;
  return ME                              ;
}

vprecision & vprecision::operator = (vprecision & v)
{
  mpfr_t * Z = (mpfr_t *)v . data ( )  ;
  ::mpfr_set ( MPFR , *Z , MPFR_RNDN ) ;
  return ME                            ;
}

vprecision & vprecision::operator = (const char * v)
{
  ::mpfr_set_str  ( MPFR , v , 10 , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator = (std::string & v)
{
  ::mpfr_set_str  ( MPFR , (const char *) v . data ( ) , 10 , MPFR_RNDN ) ;
  return ME ;
}

vprecision & vprecision::operator = (QString & v)
{
  ::mpfr_set_str  ( MPFR , (const char *) v . constData ( ) , 10 , MPFR_RNDN ) ;
  return ME ;
}

vprecision & vprecision::operator += (vlong & v)
{
  mpz_t * s = (mpz_t *) v . data ( )            ;
  ::mpfr_add_z ( MPFR , MPFR , *s , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator += (vrational & v)
{
  mpq_t * s = (mpq_t *) v . data ( )            ;
  ::mpfr_add_q ( MPFR , MPFR , *s , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator += (vprecision & v)
{
  mpfr_t * s = (mpfr_t *) v . data ( )        ;
  ::mpfr_add ( MPFR , MPFR , *s , MPFR_RNDN ) ;
  return ME                                   ;
}

vprecision & vprecision::operator += (unsigned long v)
{
  ::mpfr_add_ui ( MPFR , MPFR , v , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator += (long v)
{
  ::mpfr_add_si ( MPFR , MPFR , v , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator += (double v)
{
  ::mpfr_add_d ( MPFR , MPFR , v , MPFR_RNDN ) ;
  return ME                                    ;
}

vprecision & vprecision::operator += (const char * v)
{
  vprecision V = v ;
  ME += V          ;
  return ME        ;
}

vprecision & vprecision::operator += (std::string & v)
{
  vprecision V = v ;
  ME += V          ;
  return ME        ;
}

vprecision & vprecision::operator += (QString & v)
{
  vprecision V = v ;
  ME += V          ;
  return ME        ;
}

vprecision & vprecision::operator -= (vlong & v)
{
  mpz_t * s = (mpz_t *) v . data ( )            ;
  ::mpfr_sub_z ( MPFR , MPFR , *s , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator -= (vrational & v)
{
  mpq_t * s = (mpq_t *) v . data ( )            ;
  ::mpfr_sub_q ( MPFR , MPFR , *s , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator -= (vprecision & v)
{
  mpfr_t * s = (mpfr_t *) v . data ( )        ;
  ::mpfr_sub ( MPFR , MPFR , *s , MPFR_RNDN ) ;
  return ME                                   ;
}

vprecision & vprecision::operator -= (unsigned long v)
{
  ::mpfr_sub_ui ( MPFR , MPFR , v , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator -= (long v)
{
  ::mpfr_sub_si ( MPFR , MPFR , v , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator -= (double v)
{
  ::mpfr_sub_d ( MPFR , MPFR , v , MPFR_RNDN ) ;
  return ME                                    ;
}

vprecision & vprecision::operator -= (const char * v)
{
  vprecision V = v ;
  ME -= V          ;
  return ME        ;
}

vprecision & vprecision::operator -= (std::string & v)
{
  vprecision V = v ;
  ME -= V          ;
  return ME        ;
}

vprecision & vprecision::operator -= (QString & v)
{
  vprecision V = v ;
  ME -= V          ;
  return ME        ;
}

vprecision & vprecision::operator *= (vlong & v)
{
  mpz_t * s = (mpz_t *) v . data ( )            ;
  ::mpfr_mul_z ( MPFR , MPFR , *s , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator *= (vrational & v)
{
  mpq_t * s = (mpq_t *) v . data ( )            ;
  ::mpfr_mul_q ( MPFR , MPFR , *s , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator *= (vprecision & v)
{
  mpfr_t * s = (mpfr_t *) v . data ( )        ;
  ::mpfr_mul ( MPFR , MPFR , *s , MPFR_RNDN ) ;
  return ME                                   ;
}

vprecision & vprecision::operator *= (unsigned long v)
{
  ::mpfr_mul_ui ( MPFR , MPFR , v , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator *= (long v)
{
  ::mpfr_mul_si ( MPFR , MPFR , v , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator *= (double v)
{
  ::mpfr_mul_d ( MPFR , MPFR , v , MPFR_RNDN ) ;
  return ME                                    ;
}

vprecision & vprecision::operator *= (const char * v)
{
  vprecision V = v ;
  ME *= V          ;
  return ME        ;
}

vprecision & vprecision::operator *= (std::string & v)
{
  vprecision V = v ;
  ME *= V          ;
  return ME        ;
}

vprecision & vprecision::operator *= (QString & v)
{
  vprecision V = v ;
  ME *= V          ;
  return ME        ;
}

vprecision & vprecision::operator /= (vlong & v)
{
  mpz_t * s = (mpz_t *) v . data ( )            ;
  ::mpfr_div_z ( MPFR , MPFR , *s , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator /= (vrational & v)
{
  mpq_t * s = (mpq_t *) v . data ( )            ;
  ::mpfr_div_q ( MPFR , MPFR , *s , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator /= (vprecision & v)
{
  mpfr_t * s = (mpfr_t *) v . data ( )        ;
  ::mpfr_div ( MPFR , MPFR , *s , MPFR_RNDN ) ;
  return ME                                   ;
}

vprecision & vprecision::operator /= (unsigned long v)
{
  ::mpfr_div_ui ( MPFR , MPFR , v , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator /= (long v)
{
  ::mpfr_div_si ( MPFR , MPFR , v , MPFR_RNDN ) ;
  return ME                                     ;
}

vprecision & vprecision::operator /= (double v)
{
  ::mpfr_div_d ( MPFR , MPFR , v , MPFR_RNDN ) ;
  return ME                                    ;
}

vprecision & vprecision::operator /= (const char * v)
{
  vprecision V = v ;
  ME /= V          ;
  return ME        ;
}

vprecision & vprecision::operator /= (std::string & v)
{
  vprecision V = v ;
  ME /= V          ;
  return ME        ;
}

vprecision & vprecision::operator /= (QString & v)
{
  vprecision V = v ;
  ME /= V          ;
  return ME        ;
}

bool vprecision::operator > (vlong & v)
{
  mpz_t * s = (mpz_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_z ( MPFR , *s ) ;
  return ( b > 0 )                       ;
}

bool vprecision::operator > (vdouble & v)
{
  mpf_t * s = (mpf_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_f ( MPFR , *s ) ;
  return ( b > 0 )                       ;
}

bool vprecision::operator > (vrational & v)
{
  mpq_t * s = (mpq_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_q ( MPFR , *s ) ;
  return ( b > 0 )                       ;
}

bool vprecision::operator > (vprecision & v)
{
  mpfr_t * s = (mpfr_t *) v . data ( ) ;
  int     b = ::mpfr_cmp ( MPFR , *s ) ;
  return ( b > 0 )                     ;
}

bool vprecision::operator > (unsigned long v)
{
  return ( ::mpfr_cmp_ui ( MPFR , v ) > 0 ) ;
}

bool vprecision::operator > (long v)
{
  return ( ::mpfr_cmp_si ( MPFR , v ) > 0 ) ;
}

bool vprecision::operator > (double v)
{
  return ( ::mpfr_cmp_d ( MPFR , v ) > 0 ) ;
}

bool vprecision::operator > (long double v)
{
  return ( ::mpfr_cmp_ld ( MPFR , v ) > 0 ) ;
}

bool vprecision::operator > (const char * v)
{
  vprecision V = v  ;
  return ( ME > V ) ;
}

bool vprecision::operator > (std::string & v)
{
  vprecision V = v  ;
  return ( ME > V ) ;
}

bool vprecision::operator > (QString & v)
{
  vprecision V = v  ;
  return ( ME > V ) ;
}

bool vprecision::operator < (vlong & v)
{
  mpz_t * s = (mpz_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_z ( MPFR , *s ) ;
  return ( b < 0 )                       ;
}

bool vprecision::operator < (vdouble & v)
{
  mpf_t * s = (mpf_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_f ( MPFR , *s ) ;
  return ( b < 0 )                       ;
}

bool vprecision::operator < (vrational & v)
{
  mpq_t * s = (mpq_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_q ( MPFR , *s ) ;
  return ( b < 0 )                       ;
}

bool vprecision::operator < (vprecision & v)
{
  mpfr_t * s = (mpfr_t *) v . data ( ) ;
  int     b = ::mpfr_cmp ( MPFR , *s ) ;
  return ( b < 0 )                     ;
}

bool vprecision::operator < (unsigned long v)
{
  return ( ::mpfr_cmp_ui ( MPFR , v ) < 0 ) ;
}

bool vprecision::operator < (long v)
{
  return ( ::mpfr_cmp_si ( MPFR , v ) < 0 ) ;
}

bool vprecision::operator < (double v)
{
  return ( ::mpfr_cmp_d ( MPFR , v ) < 0 ) ;
}

bool vprecision::operator < (long double v)
{
  return ( ::mpfr_cmp_ld ( MPFR , v ) < 0 ) ;
}

bool vprecision::operator < (const char * v)
{
  vprecision V = v  ;
  return ( ME < V ) ;
}

bool vprecision::operator < (std::string & v)
{
  vprecision V = v  ;
  return ( ME < V ) ;
}

bool vprecision::operator < (QString & v)
{
  vprecision V = v  ;
  return ( ME < V ) ;
}

bool vprecision::operator >= (vlong & v)
{
  mpz_t * s = (mpz_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_z ( MPFR , *s ) ;
  return ( b >= 0 )                      ;
}

bool vprecision::operator >= (vdouble & v)
{
  mpf_t * s = (mpf_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_f ( MPFR , *s ) ;
  return ( b >= 0 )                      ;
}

bool vprecision::operator >= (vrational & v)
{
  mpq_t * s = (mpq_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_q ( MPFR , *s ) ;
  return ( b >= 0 )                      ;
}

bool vprecision::operator >= (vprecision & v)
{
  mpfr_t * s = (mpfr_t *) v . data ( ) ;
  int     b = ::mpfr_cmp ( MPFR , *s ) ;
  return ( b >= 0 )                    ;
}

bool vprecision::operator >= (unsigned long v)
{
  return ( ::mpfr_cmp_ui ( MPFR , v ) >= 0 ) ;
}

bool vprecision::operator >= (long v)
{
  return ( ::mpfr_cmp_si ( MPFR , v ) >= 0 ) ;
}

bool vprecision::operator >= (double v)
{
  return ( ::mpfr_cmp_d ( MPFR , v ) >= 0 ) ;
}

bool vprecision::operator >= (long double v)
{
  return ( ::mpfr_cmp_ld ( MPFR , v ) >= 0 ) ;
}

bool vprecision::operator >= (const char * v)
{
  vprecision V = v   ;
  return ( ME >= V ) ;
}

bool vprecision::operator >= (std::string & v)
{
  vprecision V = v   ;
  return ( ME >= V ) ;
}

bool vprecision::operator >= (QString & v)
{
  vprecision V = v   ;
  return ( ME >= V ) ;
}

bool vprecision::operator <= (vlong & v)
{
  mpz_t * s = (mpz_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_z ( MPFR , *s ) ;
  return ( b <= 0 )                      ;
}

bool vprecision::operator <= (vdouble & v)
{
  mpf_t * s = (mpf_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_f ( MPFR , *s ) ;
  return ( b <= 0 )                      ;
}

bool vprecision::operator <= (vrational & v)
{
  mpq_t * s = (mpq_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_q ( MPFR , *s ) ;
  return ( b <= 0 )                      ;
}

bool vprecision::operator <= (vprecision & v)
{
  mpfr_t * s = (mpfr_t *) v . data ( ) ;
  int     b = ::mpfr_cmp ( MPFR , *s ) ;
  return ( b <= 0 )                    ;
}

bool vprecision::operator <= (unsigned long v)
{
  return ( ::mpfr_cmp_ui ( MPFR , v ) <= 0 ) ;
}

bool vprecision::operator <= (long v)
{
  return ( ::mpfr_cmp_si ( MPFR , v ) <= 0 ) ;
}

bool vprecision::operator <= (double v)
{
  return ( ::mpfr_cmp_d ( MPFR , v ) <= 0 ) ;
}

bool vprecision::operator <= (long double v)
{
  return ( ::mpfr_cmp_ld ( MPFR , v ) <= 0 ) ;
}

bool vprecision::operator <= (const char * v)
{
  vprecision V = v   ;
  return ( ME <= V ) ;
}

bool vprecision::operator <= (std::string & v)
{
  vprecision V = v   ;
  return ( ME <= V ) ;
}

bool vprecision::operator <= (QString & v)
{
  vprecision V = v   ;
  return ( ME <= V ) ;
}

bool vprecision::operator == (vlong & v)
{
  mpz_t * s = (mpz_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_z ( MPFR , *s ) ;
  return ( b == 0 )                      ;
}

bool vprecision::operator == (vdouble & v)
{
  mpf_t * s = (mpf_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_f ( MPFR , *s ) ;
  return ( b == 0 )                      ;
}

bool vprecision::operator == (vrational & v)
{
  mpq_t * s = (mpq_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_q ( MPFR , *s ) ;
  return ( b == 0 )                      ;
}

bool vprecision::operator == (vprecision & v)
{
  mpfr_t * s = (mpfr_t *) v . data ( ) ;
  int     b = ::mpfr_cmp ( MPFR , *s ) ;
  return ( b == 0 )                    ;
}

bool vprecision::operator == (unsigned long v)
{
  return ( ::mpfr_cmp_ui ( MPFR , v ) == 0 ) ;
}

bool vprecision::operator == (long v)
{
  return ( ::mpfr_cmp_si ( MPFR , v ) == 0 ) ;
}

bool vprecision::operator == (double v)
{
  return ( ::mpfr_cmp_d ( MPFR , v ) == 0 ) ;
}

bool vprecision::operator == (long double v)
{
  return ( ::mpfr_cmp_ld ( MPFR , v ) == 0 ) ;
}

bool vprecision::operator == (const char * v)
{
  vprecision V = v   ;
  return ( ME == V ) ;
}

bool vprecision::operator == (std::string & v)
{
  vprecision V = v   ;
  return ( ME == V ) ;
}

bool vprecision::operator == (QString & v)
{
  vprecision V = v   ;
  return ( ME == V ) ;
}

bool vprecision::operator != (vlong & v)
{
  mpz_t * s = (mpz_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_z ( MPFR , *s ) ;
  return ( b != 0 )                      ;
}

bool vprecision::operator != (vdouble & v)
{
  mpf_t * s = (mpf_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_f ( MPFR , *s ) ;
  return ( b != 0 )                      ;
}

bool vprecision::operator != (vrational & v)
{
  mpq_t * s = (mpq_t *) v . data ( )     ;
  int     b = ::mpfr_cmp_q ( MPFR , *s ) ;
  return ( b != 0 )                      ;
}

bool vprecision::operator != (vprecision & v)
{
  mpfr_t * s = (mpfr_t *) v . data ( ) ;
  int     b = ::mpfr_cmp ( MPFR , *s ) ;
  return ( b != 0 )                    ;
}

bool vprecision::operator != (unsigned long v)
{
  return ( ::mpfr_cmp_ui ( MPFR , v ) != 0 ) ;
}

bool vprecision::operator != (long v)
{
  return ( ::mpfr_cmp_si ( MPFR , v ) != 0 ) ;
}

bool vprecision::operator != (double v)
{
  return ( ::mpfr_cmp_d ( MPFR , v ) != 0 ) ;
}

bool vprecision::operator != (long double v)
{
  return ( ::mpfr_cmp_ld ( MPFR , v ) != 0 ) ;
}

bool vprecision::operator != (const char * v)
{
  vprecision V = v   ;
  return ( ME != V ) ;
}

bool vprecision::operator != (std::string & v)
{
  vprecision V = v   ;
  return ( ME != V ) ;
}

bool vprecision::operator != (QString & v)
{
  vprecision V = v   ;
  return ( ME != V ) ;
}

int vprecision::compare(vlong & v)
{
  mpz_t * s = (mpz_t *) v . data ( ) ;
  return ::mpfr_cmp_z ( MPFR , *s )  ;
}

int vprecision::compare(vdouble & v)
{
  mpf_t * s = (mpf_t *) v . data ( ) ;
  return ::mpfr_cmp_f ( MPFR , *s )  ;
}

int vprecision::compare(vrational & v)
{
  mpq_t * s = (mpq_t *) v . data ( ) ;
  return ::mpfr_cmp_q ( MPFR , *s )  ;
}

int vprecision::compare(vprecision & v)
{
  mpfr_t * s = (mpfr_t *) v . data ( ) ;
  return ::mpfr_cmp ( MPFR , *s )      ;
}

int vprecision::compare(unsigned long v)
{
  return ::mpfr_cmp_ui ( MPFR , v ) ;
}

int vprecision::compare(long v)
{
  return ::mpfr_cmp_si ( MPFR , v ) ;
}

int vprecision::compare(double v)
{
  return ::mpfr_cmp_d ( MPFR , v ) ;
}

int vprecision::compare(long double v)
{
  return ::mpfr_cmp_ld ( MPFR , v ) ;
}

int vprecision::compare(const char * v)
{
  vprecision V = v     ;
  return compare ( V ) ;
}

int vprecision::compare(std::string & v)
{
  vprecision V = v     ;
  return compare ( V ) ;
}

int vprecision::compare(QString & v)
{
  vprecision V = v     ;
  return compare ( V ) ;
}

bool vprecision::isULong(int rnd)
{
  return ( 0 != ::mpfr_fits_ulong_p ( MPFR , (mpfr_rnd_t) rnd ) ) ;
}

bool vprecision::isLong(int rnd)
{
  return ( 0 != ::mpfr_fits_ulong_p ( MPFR , (mpfr_rnd_t) rnd ) ) ;
}

bool vprecision::isUInt(int rnd)
{
  return ( 0 != ::mpfr_fits_uint_p ( MPFR , (mpfr_rnd_t) rnd ) ) ;
}

bool vprecision::isInt(int rnd)
{
  return ( 0 != ::mpfr_fits_sint_p ( MPFR , (mpfr_rnd_t) rnd ) ) ;
}

bool vprecision::isUShort(int rnd)
{
  return ( 0 != ::mpfr_fits_ushort_p ( MPFR , (mpfr_rnd_t) rnd ) ) ;
}

bool vprecision::isShort(int rnd)
{
  return ( 0 != ::mpfr_fits_sshort_p ( MPFR , (mpfr_rnd_t) rnd ) ) ;
}

bool vprecision::isNan(void)
{
  return ( 0 != mpfr_nan_p ( MPFR ) ) ;
}

bool vprecision::isInf(void)
{
  return ( 0 != mpfr_inf_p ( MPFR ) ) ;
}

bool vprecision::isNumber(void)
{
  return ( 0 != mpfr_number_p ( MPFR ) ) ;
}

bool vprecision::isZero(void)
{
  return ( 0 != mpfr_zero_p ( MPFR ) ) ;
}

bool vprecision::isRegular(void)
{
  return ( 0 != mpfr_regular_p ( MPFR ) ) ;
}

vprecision & vprecision::set(unsigned long v,int rnd)
{
  ::mpfr_set_ui ( MPFR , (unsigned long int) v , (mpfr_rnd_t) rnd ) ;
  return ME                                                         ;
}

vprecision & vprecision::set(long v,int rnd)
{
  ::mpfr_set_si ( MPFR , (long int)v , (mpfr_rnd_t) rnd ) ;
  return ME                                               ;
}

vprecision & vprecision::set(float v,int rnd)
{
  ::mpfr_set_flt ( MPFR , v , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::set(double v,int rnd)
{
  ::mpfr_set_d ( MPFR , v , (mpfr_rnd_t) rnd ) ;
  return ME                                    ;
}

vprecision & vprecision::set(long double v,int rnd)
{
  ::mpfr_set_ld ( MPFR , v , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::set(vlong & v,int rnd)
{
  mpz_t * Z = (mpz_t *)v . data ( )             ;
  ::mpfr_set_z ( MPFR , *Z , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::set(vdouble & v,int rnd)
{
  mpf_t * Z = (mpf_t *)v . data ( )             ;
  ::mpfr_set_f ( MPFR , *Z , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::set(vrational & v,int rnd)
{
  mpq_t * Z = (mpq_t *)v . data ( )              ;
  ::mpfr_set_q ( MPFR , *Z , (mpfr_rnd_t) rnd  ) ;
  return ME                                      ;
}

vprecision & vprecision::set(vprecision & v,int rnd)
{
  mpfr_t * Z = (mpfr_t *)v . data ( )        ;
  ::mpfr_set ( MPFR , *Z, (mpfr_rnd_t) rnd ) ;
  return ME                                  ;
}

vprecision & vprecision::set(const char * v,int base,int rnd)
{
  ::mpfr_set_str  ( MPFR , v , base , (mpfr_rnd_t) rnd ) ;
  return ME                                              ;
}

vprecision & vprecision::set(std::string & v,int base,int rnd)
{
  ::mpfr_set_str  ( MPFR , (const char *) v . data ( ) , base , (mpfr_rnd_t) rnd ) ;
  return ME ;
}

vprecision & vprecision::set(QString & v,int base,int rnd)
{
  ::mpfr_set_str  ( MPFR , (const char *) v . constData ( ) , base , (mpfr_rnd_t) rnd ) ;
  return ME ;
}

vprecision & vprecision::setNan(void)
{
  ::mpfr_set_nan ( MPFR ) ;
  return ME               ;
}

vprecision & vprecision::setInf(int sign)
{
  ::mpfr_set_inf ( MPFR , sign ) ;
  return ME                      ;
}

vprecision & vprecision::setZero(int sign)
{
  ::mpfr_set_zero ( MPFR , sign ) ;
  return ME                       ;
}

vprecision & vprecision::swap(vprecision & v)
{
  mpfr_t * s = (mpfr_t *) v . data ( ) ;
  ::mpfr_swap ( MPFR , *s )            ;
  return ME                            ;
}

vprecision & vprecision::ceil(void)
{
  ::mpfr_ceil ( MPFR , MPFR ) ;
  return ME                   ;
}

vprecision & vprecision::floor(void)
{
  ::mpfr_floor ( MPFR , MPFR ) ;
  return ME                    ;
}

vprecision & vprecision::round(void)
{
  ::mpfr_round ( MPFR , MPFR ) ;
  return ME                    ;
}

vprecision & vprecision::truncate(void)
{
  ::mpfr_trunc ( MPFR , MPFR ) ;
  return ME                    ;
}

vprecision & vprecision::rint(int rnd)
{
  ::mpfr_rint ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::rintCeil(int rnd)
{
  ::mpfr_rint_ceil  ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                            ;
}

vprecision & vprecision::rintFloor(int rnd)
{
  ::mpfr_rint_floor ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                            ;
}

vprecision & vprecision::rintRound(int rnd)
{
  ::mpfr_rint_round ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                            ;
}

vprecision & vprecision::rintTruncate(int rnd)
{
  ::mpfr_rint_trunc ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                            ;
}

vprecision & vprecision::fractional(int rnd)
{
  ::mpfr_frac ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::modf(vprecision & v,int rnd)
{
  mpfr_t * s = (mpfr_t *) v . data ( )                ;
  ::mpfr_modf ( MPFR , MPFR , *s , (mpfr_rnd_t) rnd ) ;
  return ME                                           ;
}

vprecision & vprecision::fmod(vprecision & v,int rnd)
{
  mpfr_t * s = (mpfr_t *) v . data ( )                ;
  ::mpfr_fmod ( MPFR , MPFR , *s , (mpfr_rnd_t) rnd ) ;
  return ME                                           ;
}

vprecision & vprecision::remainder(vprecision & v,int rnd)
{
  mpfr_t * s = (mpfr_t *) v . data ( )                     ;
  ::mpfr_remainder ( MPFR , MPFR , *s , (mpfr_rnd_t) rnd ) ;
  return ME                                                ;
}

vprecision & vprecision::sqrt(int rnd)
{
  ::mpfr_sqrt ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::reciprocal(int rnd)
{
  ::mpfr_rec_sqrt ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                          ;
}

vprecision & vprecision::cbrt(int rnd)
{
  ::mpfr_cbrt ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::root(unsigned long k,int rnd)
{
  ::mpfr_root  ( MPFR , MPFR , k , (mpfr_rnd_t) rnd ) ;
  return ME                                           ;
}

vprecision & vprecision::pow(unsigned long n,int rnd)
{
  ::mpfr_pow_ui ( MPFR , MPFR , n , (mpfr_rnd_t) rnd ) ;
  return ME                                            ;
}

vprecision & vprecision::pow(long n,int rnd)
{
  ::mpfr_pow_si ( MPFR , MPFR , n , (mpfr_rnd_t) rnd ) ;
  return ME                                            ;
}

vprecision & vprecision::pow(vlong & v,int rnd)
{
  mpz_t * s = (mpz_t *) v . data ( )                   ;
  ::mpfr_pow_z ( MPFR , MPFR , *s , (mpfr_rnd_t) rnd ) ;
  return ME                                            ;
}

vprecision & vprecision::pow(vprecision & v,int rnd)
{
  mpfr_t * s = (mpfr_t *) v . data ( )               ;
  ::mpfr_pow ( MPFR , MPFR , *s , (mpfr_rnd_t) rnd ) ;
  return ME                                          ;
}

vprecision & vprecision::neg(int rnd)
{
  ::mpfr_neg ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::abs(int rnd)
{
  ::mpfr_abs ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::dim(vprecision & v,int rnd)
{
  mpfr_t * s = (mpfr_t *) v . data ( )               ;
  ::mpfr_dim ( MPFR , MPFR , *s , (mpfr_rnd_t) rnd ) ;
  return ME                                          ;
}

vprecision & vprecision::log(int rnd)
{
  ::mpfr_log ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::log2(int rnd)
{
  ::mpfr_log2 ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::log10(int rnd)
{
  ::mpfr_log10 ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                       ;
}

vprecision & vprecision::log1p(int rnd)
{
  ::mpfr_log1p ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                       ;
}

vprecision & vprecision::exp(int rnd)
{
  ::mpfr_exp ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::exp2(int rnd)
{
  ::mpfr_exp2 ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::exp10(int rnd)
{
  ::mpfr_exp10 ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                       ;
}

vprecision & vprecision::expm1(int rnd)
{
  ::mpfr_expm1 ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                       ;
}

vprecision & vprecision::expIntegral(int rnd)
{
  ::mpfr_eint ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::cos(int rnd)
{
  ::mpfr_cos ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::sin(int rnd)
{
  ::mpfr_sin ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::tan(int rnd)
{
  ::mpfr_tan ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::sec(int rnd)
{
  ::mpfr_sec ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::csc(int rnd)
{
  ::mpfr_csc ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::cot(int rnd)
{
  ::mpfr_cot ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::acos(int rnd)
{
  ::mpfr_acos ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::asin(int rnd)
{
  ::mpfr_asin ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::atan(int rnd)
{
  ::mpfr_atan ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::cosh(int rnd)
{
  ::mpfr_cosh ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::sinh(int rnd)
{
  ::mpfr_sinh ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::tanh(int rnd)
{
  ::mpfr_tanh ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::sech(int rnd)
{
  ::mpfr_sech ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::csch(int rnd)
{
  ::mpfr_csch ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::coth(int rnd)
{
  ::mpfr_coth ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::acosh(int rnd)
{
  ::mpfr_acosh ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                       ;
}

vprecision & vprecision::asinh(int rnd)
{
  ::mpfr_asinh ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                       ;
}

vprecision & vprecision::atanh(int rnd)
{
  ::mpfr_atanh ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                       ;
}

vprecision & vprecision::atan2(vprecision & x,int rnd)
{
  mpfr_t * s = (mpfr_t *) x . data ( )                 ;
  ::mpfr_atan2 ( MPFR , MPFR , *s , (mpfr_rnd_t) rnd ) ;
  return ME                                            ;
}

vprecision & vprecision::factorial(unsigned long n,int rnd)
{
  ::mpfr_fac_ui ( MPFR , n , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::li2(int rnd)
{
  ::mpfr_li2 ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::gamma(int rnd)
{
  ::mpfr_gamma ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                       ;
}

vprecision & vprecision::lngamma(int rnd)
{
  ::mpfr_lngamma ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                         ;
}

vprecision & vprecision::digamma(int rnd)
{
  ::mpfr_digamma ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                         ;
}

vprecision & vprecision::zeta(int rnd)
{
  ::mpfr_zeta ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::erf(int rnd)
{
  ::mpfr_erf ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                     ;
}

vprecision & vprecision::erfc(int rnd)
{
  ::mpfr_erfc ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                      ;
}

vprecision & vprecision::j0(int rnd)
{
  ::mpfr_j0 ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                    ;
}

vprecision & vprecision::j1(int rnd)
{
  ::mpfr_j1 ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                    ;
}

vprecision & vprecision::jn(long n,int rnd)
{
  ::mpfr_jn ( MPFR , n , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                        ;
}

vprecision & vprecision::y0(int rnd)
{
  ::mpfr_y0 ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                    ;
}

vprecision & vprecision::y1(int rnd)
{
  ::mpfr_y1 ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                    ;
}

vprecision & vprecision::yn(long n,int rnd)
{
  ::mpfr_yn ( MPFR , n , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                        ;
}

vprecision & vprecision::agm(vprecision & y,int rnd)
{
  mpfr_t * s = (mpfr_t *) y . data ( )               ;
  ::mpfr_agm ( MPFR , MPFR , *s , (mpfr_rnd_t) rnd ) ;
  return ME                                          ;
}

vprecision & vprecision::hypot(vprecision & y,int rnd)
{
  mpfr_t * s = (mpfr_t *) y . data ( )                 ;
  ::mpfr_hypot ( MPFR , MPFR , *s , (mpfr_rnd_t) rnd ) ;
  return ME                                            ;
}

vprecision & vprecision::airy(int rnd)
{
  ::mpfr_ai ( MPFR , MPFR , (mpfr_rnd_t) rnd ) ;
  return ME                                    ;
}

vprecision & vprecision::urandomb(vrandom & r)
{
  ::mpfr_urandomb ( MPFR , RANX ( r ) -> ranx ) ;
  return ME                                     ;
}

vprecision & vprecision::urandom(vrandom & r,int rnd)
{
  ::mpfr_urandom ( MPFR , RANX ( r ) -> ranx , (mpfr_rnd_t) rnd ) ;
  return ME                                                       ;
}

long vprecision::exponent(void)
{
  return mpfr_get_exp ( MPFR ) ;
}

int vprecision::signBit(void)
{
  return mpfr_signbit ( MPFR ) ;
}

int vprecision::setSign(int s,int rnd)
{
  return ::mpfr_setsign ( MPFR , MPFR , s , (mpfr_rnd_t) rnd ) ;
}

int vprecision::sign(void)
{
  return mpfr_sgn ( MPFR ) ;
}

void vprecision::FreeCache(void)
{
  ::mpfr_free_cache ( ) ;
}

void vprecision::clear(void)
{
  ::mpfr_clear ( MPFR ) ;
}

vlong vprecision::toVLong(int rnd)
{
  vlong v                                                        ;
  ::mpfr_get_z ( *(mpz_t *) v.data() , MPFR , (mpfr_rnd_t) rnd ) ;
  return v                                                       ;
}

vdouble vprecision::toVDouble(int rnd)
{
  vdouble v                                                      ;
  ::mpfr_get_f ( *(mpf_t *) v.data() , MPFR , (mpfr_rnd_t) rnd ) ;
  return v                                                       ;
}

float vprecision::toFloat(int rnd)
{
  return ::mpfr_get_flt ( MPFR , (mpfr_rnd_t) rnd ) ;
}

double vprecision::toDouble(int rnd)
{
  return ::mpfr_get_d ( MPFR , (mpfr_rnd_t) rnd ) ;
}

long double vprecision::toLongDouble(int rnd)
{
  return ::mpfr_get_ld ( MPFR , (mpfr_rnd_t) rnd ) ;
}

long vprecision::toLong(int rnd)
{
  return ::mpfr_get_si ( MPFR , (mpfr_rnd_t) rnd ) ;
}

unsigned long vprecision::toULong(int rnd)
{
  return ::mpfr_get_ui ( MPFR , (mpfr_rnd_t) rnd ) ;
}

QString vprecision::String(int digits,int base,int rnd)
{
  QString S                                                ;
  QString R                                                ;
  mp_exp_t exp                                             ;
  char *  r = new char [digits + 16]                       ;
  memset(r,0,digits + 16)                                  ;
  ::mpfr_get_str (r,&exp,base,digits,MPFR,(mpfr_rnd_t)rnd) ;
  if (strlen(r)<=0)                                        {
    delete [] r                                            ;
    return S                                               ;
  }                                                        ;
  S = r                                                    ;
  delete [] r                                              ;
  if (exp<0)                                               {
    int len = (int)exp                                     ;
    len = -len                                             ;
    QString Z = "0"                                        ;
    Z = Z.repeated(len)                                    ;
    R  = "0."                                              ;
    R += Z                                                 ;
    R += S                                                 ;
  } else
  if (exp==0)                                              {
    R  = "0."                                              ;
    R += S                                                 ;
  } else                                                   {
    int mid = (int) exp                                    ;
    int len = S.length() - mid                             ;
    R  = S . left ( (int)exp )                             ;
    R += "."                                               ;
    if (len<=0)                                            {
      R += "0"                                             ;
    } else                                                 {
      R += S . mid  ( mid , len )                          ;
    }                                                      ;
  }                                                        ;
  return R                                                 ;
}
