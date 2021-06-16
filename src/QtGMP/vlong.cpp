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
#define MPZ                        (*((mpz_t *)data()))
#define RANX(d)                    ((RANDSTATE *)d.data())

vlong:: vlong      (void)
      : QByteArray (    )
{
  resize     ( sizeof(mpz_t) ) ;
  ::mpz_init ( MPZ           ) ;
}

vlong:: vlong      (const vlong & v)
      : QByteArray (               )
{
  resize     ( sizeof(mpz_t) )      ;
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  ::mpz_init ( *m            )      ;
  ::mpz_set  ( *m , *s       )      ;
}

vlong:: vlong      ( const unsigned long v )
      : QByteArray (                       )
{
  resize            ( sizeof(mpz_t) ) ;
  ::mpz_init_set_ui ( MPZ , v       ) ;
}

vlong:: vlong      ( const long v )
      : QByteArray (              )
{
  resize            ( sizeof(mpz_t) ) ;
  ::mpz_init_set_si ( MPZ , v       ) ;
}

vlong:: vlong      ( const char * v,const int base )
      : QByteArray (                               )
{
  resize             ( sizeof(mpz_t)  ) ;
  ::mpz_init_set_str ( MPZ , v , base ) ;
}

vlong:: vlong      ( const std::string & v,const int base )
      : QByteArray (                                      )
{
  resize             ( sizeof(mpz_t)                      ) ;
  ::mpz_init_set_str ( MPZ , (char *) v . data ( ) , base ) ;
}

vlong:: vlong      ( const QString & v,const int base )
      : QByteArray (                                  )
{
  resize             ( sizeof(mpz_t)                           ) ;
  ::mpz_init_set_str ( MPZ , (char *) v . constData ( ) , base ) ;
}

vlong::~vlong (void)
{
  ::mpz_clear ( MPZ ) ;
}

vlong & vlong::operator = (vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  ::mpz_set   ( *m , *s )           ;
  return ME                         ;
}

vlong & vlong::operator = (unsigned long v)
{
  ::mpz_set_ui ( MPZ , v ) ;
  return ME                ;
}

vlong & vlong::operator = (long v)
{
  ::mpz_set_si ( MPZ , v ) ;
  return ME                ;
}

vlong & vlong::operator = (const char * v)
{
  ::mpz_set_str ( MPZ , v , 10 ) ;
  return ME                      ;
}

vlong & vlong::operator = (std::string & v)
{
  ::mpz_set_str ( MPZ , (char *) v . data() , 10 ) ;
  return ME                                        ;
}

vlong & vlong::operator = (QString & v)
{
  ::mpz_set_str ( MPZ , (char *) v . constData() , 10 ) ;
  return ME                                             ;
}

vlong & vlong::operator = (double v)
{
  ::mpz_set_d ( MPZ , v ) ;
  return ME               ;
}

vlong & vlong::operator = (vdouble & v)
{
  ::mpz_set_f ( MPZ , *(mpf_t *)v.data() ) ;
  return ME                                ;
}

vlong & vlong::operator = (vrational & v)
{
  ::mpz_set_q ( MPZ , *(mpq_t *)v.data() ) ;
  return ME                                ;
}

vlong & vlong::operator += (vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  ::mpz_add   ( *m , *m , *s      ) ;
  return ME                         ;
}

vlong & vlong::operator += (unsigned long v)
{
  nKickOut     ( v == 0 , ME   ) ;
  ::mpz_add_ui ( MPZ , MPZ , v ) ;
  return ME                      ;
}

vlong & vlong::operator += (long v)
{
  nKickOut ( v == 0 , ME )                  ;
  if (v>=0) ::mpz_add_ui ( MPZ , MPZ ,  v ) ;
       else ::mpz_sub_ui ( MPZ , MPZ , -v ) ;
  return ME                                 ;
}

vlong & vlong::operator += (const char * v)
{
  nKickOut ( IsNull(v) , ME )       ;
  vlong V = v                       ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  ::mpz_add ( MPZ , MPZ , *s )      ;
  return ME                         ;
}

vlong & vlong::operator += (std::string & v)
{
  nKickOut ( ( v . size ( ) <= 0 ) , ME ) ;
  vlong V = v                             ;
  mpz_t * s = (mpz_t *)V . data ( )       ;
  ::mpz_add ( MPZ , MPZ , *s )            ;
  return ME                               ;
}

vlong & vlong::operator += (QString & v)
{
  nKickOut ( ( v . length ( ) <= 0 ) , ME ) ;
  vlong V = v                               ;
  mpz_t * s = (mpz_t *)V . data ( )         ;
  ::mpz_add ( MPZ , MPZ , *s )              ;
  return ME                                 ;
}

vlong & vlong::operator -= (vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  ::mpz_sub   ( *m , *m , *s      ) ;
  return ME                         ;
}

vlong & vlong::operator -= (unsigned long v)
{
  nKickOut     ( v == 0 , ME   ) ;
  ::mpz_sub_ui ( MPZ , MPZ , v ) ;
  return ME                      ;
}

vlong & vlong::operator -= (long v)
{
  nKickOut ( v == 0 , ME )                  ;
  if (v>=0) ::mpz_sub_ui ( MPZ , MPZ ,  v ) ;
       else ::mpz_add_ui ( MPZ , MPZ , -v ) ;
  return ME                                 ;
}

vlong & vlong::operator -= (const char * v)
{
  nKickOut ( IsNull(v) , ME )       ;
  vlong V                           ;
  V = v                             ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  ::mpz_sub ( MPZ , MPZ , *s )      ;
  return ME                         ;
}

vlong & vlong::operator -= (std::string & v)
{
  nKickOut ( ( v . size ( ) <= 0 ) , ME ) ;
  vlong V = v                             ;
  mpz_t * s = (mpz_t *)V . data ( )       ;
  ::mpz_sub ( MPZ , MPZ , *s )            ;
  return ME                               ;
}

vlong & vlong::operator -= (QString & v)
{
  nKickOut ( ( v . length ( ) <= 0 ) , ME ) ;
  vlong V = v                               ;
  mpz_t * s = (mpz_t *)V . data ( )         ;
  ::mpz_sub ( MPZ , MPZ , *s )              ;
  return ME                                 ;
}

vlong & vlong::operator *= (vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  ::mpz_mul   ( *m , *m , *s      ) ;
  return ME                         ;
}

vlong & vlong::operator *= (unsigned long v)
{
  ::mpz_mul_ui ( MPZ , MPZ , v ) ;
  return ME                      ;
}

vlong & vlong::operator *= (long v)
{
  ::mpz_mul_si ( MPZ , MPZ ,  v ) ;
  return ME                       ;
}

vlong & vlong::operator *= (const char * v)
{
  nKickOut ( IsNull(v) , ME )       ;
  vlong V                           ;
  V = v                             ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  ::mpz_mul ( MPZ , MPZ , *s )      ;
  return ME                         ;
}

vlong & vlong::operator *= (std::string & v)
{
  nKickOut ( ( v . size ( ) <= 0 ) , ME ) ;
  vlong V = v                             ;
  mpz_t * s = (mpz_t *)V . data ( )       ;
  ::mpz_mul ( MPZ , MPZ , *s )            ;
  return ME                               ;
}

vlong & vlong::operator *= (QString & v)
{
  nKickOut ( ( v . length ( ) <= 0 ) , ME ) ;
  vlong V = v                               ;
  mpz_t * s = (mpz_t *)V . data ( )         ;
  ::mpz_mul ( MPZ , MPZ , *s )              ;
  return ME                                 ;
}

vlong & vlong::operator /= (vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  ::mpz_tdiv_q  ( *m , *m , *s    ) ;
  return ME                         ;
}

vlong & vlong::operator /= (unsigned long v)
{
  ::mpz_tdiv_q_ui ( MPZ , MPZ , v ) ;
  return ME                         ;
}

vlong & vlong::operator /= (long v)
{
  if (v>0)                              {
    ::mpz_tdiv_q_ui  ( MPZ , MPZ ,  v ) ;
  } else                                {
    ::mpz_tdiv_q_ui  ( MPZ , MPZ , -v ) ;
    ::mpz_neg        ( MPZ , MPZ      ) ;
  }                                     ;
  return ME                             ;
}

vlong & vlong::operator /= (const char * v)
{
  nKickOut ( IsNull(v) , ME )       ;
  vlong V                           ;
  V = v                             ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  ::mpz_tdiv_q ( MPZ , MPZ , *s )   ;
  return ME                         ;
}

vlong & vlong::operator /= (std::string & v)
{
  nKickOut ( ( v . size ( ) <= 0 ) , ME ) ;
  vlong V = v                             ;
  mpz_t * s = (mpz_t *)V . data ( )       ;
  ::mpz_tdiv_q ( MPZ , MPZ , *s )         ;
  return ME                               ;
}

vlong & vlong::operator /= (QString & v)
{
  nKickOut ( ( v . length ( ) <= 0 ) , ME ) ;
  vlong V = v                               ;
  mpz_t * s = (mpz_t *)V . data ( )         ;
  ::mpz_tdiv_q ( MPZ , MPZ , *s )           ;
  return ME                                 ;
}

vlong & vlong::operator %= (vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  ::mpz_mod ( *m , *m , *s    )     ;
  return ME                         ;
}

vlong & vlong::operator %= (unsigned long v)
{
  ::mpz_mod_ui ( MPZ , MPZ , v ) ;
  return ME                      ;
}

vlong & vlong::operator %= (long v)
{
  vlong V                           ;
  V = v                             ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  ::mpz_mod ( MPZ , MPZ , *s )      ;
  return ME                         ;
}

vlong & vlong::operator %= (const char * v)
{
  nKickOut ( IsNull(v) , ME )       ;
  vlong V                           ;
  V = v                             ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  ::mpz_mod ( MPZ , MPZ , *s )      ;
  return ME                         ;
}

vlong & vlong::operator %= (std::string & v)
{
  nKickOut ( ( v . size ( ) <= 0 ) , ME ) ;
  vlong V = v                             ;
  mpz_t * s = (mpz_t *)V . data ( )       ;
  ::mpz_mod ( MPZ , MPZ , *s )            ;
  return ME                               ;
}

vlong & vlong::operator %= (QString & v)
{
  nKickOut ( ( v . length ( ) <= 0 ) , ME ) ;
  vlong V = v                               ;
  mpz_t * s = (mpz_t *)V . data ( )         ;
  ::mpz_mod ( MPZ , MPZ , *s )              ;
  return ME                                 ;
}

bool vlong::operator > (vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  int b = ::mpz_cmp ( *m , *s )     ;
  return ( b > 0 )                  ;
}

bool vlong::operator > (unsigned long v)
{
  int b = mpz_cmp_ui( MPZ , v ) ;
  return ( b > 0 )              ;
}

bool vlong::operator > (long v)
{
  int b = mpz_cmp_si( MPZ , v ) ;
  return ( b > 0 )              ;
}

bool vlong::operator > (const char * v)
{
  nKickOut ( IsNull(v) , false )    ;
  vlong V                           ;
  V = v                             ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  int b = ::mpz_cmp ( MPZ , *s )    ;
  return ( b > 0 )                  ;
}

bool vlong::operator > (std::string & v)
{
  nKickOut ( ( v . size ( ) <= 0 ) , false ) ;
  vlong V = v                                ;
  mpz_t * s = (mpz_t *)V . data ( )          ;
  int b = ::mpz_cmp ( MPZ , *s )             ;
  return ( b > 0 )                           ;
}

bool vlong::operator > (QString & v)
{
  nKickOut ( ( v . length ( ) <= 0 ) , false ) ;
  vlong V = v                                  ;
  mpz_t * s = (mpz_t *)V . data ( )            ;
  int b = ::mpz_cmp ( MPZ , *s )               ;
  return ( b > 0 )                             ;
}

bool vlong::operator < (vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  int b = ::mpz_cmp ( *m , *s )     ;
  return ( b < 0 )                  ;
}

bool vlong::operator < (unsigned long v)
{
  int b = mpz_cmp_ui( MPZ , v ) ;
  return ( b < 0 )              ;
}

bool vlong::operator < (long v)
{
  int b = mpz_cmp_si( MPZ , v ) ;
  return ( b < 0 )              ;
}

bool vlong::operator < (const char * v)
{
  nKickOut ( IsNull(v) , false )    ;
  vlong V = v                          ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  int b = ::mpz_cmp ( MPZ , *s )    ;
  return ( b < 0 )                  ;
}

bool vlong::operator < (std::string & v)
{
  nKickOut ( ( v . size ( ) <= 0 ) , false ) ;
  vlong V = v                                ;
  mpz_t * s = (mpz_t *)V . data ( )          ;
  int b = ::mpz_cmp ( MPZ , *s )             ;
  return ( b < 0 )                           ;
}

bool vlong::operator < (QString & v)
{
  nKickOut ( ( v . length ( ) <= 0 ) , false ) ;
  vlong V = v                                  ;
  mpz_t * s = (mpz_t *)V . data ( )            ;
  int b = ::mpz_cmp ( MPZ , *s )               ;
  return ( b < 0 )                             ;
}

bool vlong::operator >= (vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  int b = ::mpz_cmp ( *m , *s )     ;
  return ( b >= 0 )                 ;
}

bool vlong::operator >= (unsigned long v)
{
  int b = mpz_cmp_ui( MPZ , v ) ;
  return ( b >= 0 )             ;
}

bool vlong::operator >= (long v)
{
  int b = mpz_cmp_si( MPZ , v ) ;
  return ( b >= 0 )             ;
}

bool vlong::operator >= (const char * v)
{
  nKickOut ( IsNull(v) , false )    ;
  vlong V = v                       ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  int b = ::mpz_cmp ( MPZ , *s )    ;
  return ( b >= 0 )                 ;
}

bool vlong::operator >= (std::string & v)
{
  nKickOut ( ( v . size ( ) <= 0 ) , false ) ;
  vlong V = v                                ;
  mpz_t * s = (mpz_t *)V . data ( )          ;
  int b = ::mpz_cmp ( MPZ , *s )             ;
  return ( b >= 0 )                          ;
}

bool vlong::operator >= (QString & v)
{
  nKickOut ( ( v . length ( ) <= 0 ) , false ) ;
  vlong V = v                                  ;
  mpz_t * s = (mpz_t *)V . data ( )            ;
  int b = ::mpz_cmp ( MPZ , *s )               ;
  return ( b >= 0 )                            ;
}

bool vlong::operator <= (vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  int b = ::mpz_cmp ( *m , *s )     ;
  return ( b <= 0 )                 ;
}

bool vlong::operator <= (unsigned long v)
{
  int b = mpz_cmp_ui( MPZ , v ) ;
  return ( b <= 0 )             ;
}

bool vlong::operator <= (long v)
{
  int b = mpz_cmp_si( MPZ , v ) ;
  return ( b <= 0 )             ;
}

bool vlong::operator <= (const char * v)
{
  nKickOut ( IsNull(v) , false )    ;
  vlong V = v                       ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  int b = ::mpz_cmp ( MPZ , *s )    ;
  return ( b <= 0 )                 ;
}

bool vlong::operator <= (std::string & v)
{
  nKickOut ( ( v . size ( ) <= 0 ) , false ) ;
  vlong V = v                                ;
  mpz_t * s = (mpz_t *)V . data ( )          ;
  int b = ::mpz_cmp ( MPZ , *s )             ;
  return ( b <= 0 )                          ;
}

bool vlong::operator <= (QString & v)
{
  nKickOut ( ( v . length ( ) <= 0 ) , false ) ;
  vlong V = v                                  ;
  mpz_t * s = (mpz_t *)V . data ( )            ;
  int b = ::mpz_cmp ( MPZ , *s )               ;
  return ( b <= 0 )                            ;
}

bool vlong::operator == (vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  int b = ::mpz_cmp ( *m , *s )     ;
  return ( b == 0 )                 ;
}

bool vlong::operator == (unsigned long v)
{
  int b = mpz_cmp_ui( MPZ , v ) ;
  return ( b == 0 )             ;
}

bool vlong::operator == (long v)
{
  int b = mpz_cmp_si( MPZ , v ) ;
  return ( b == 0 )             ;
}

bool vlong::operator == (const char * v)
{
  nKickOut ( IsNull(v) , false )    ;
  vlong V = v                       ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  int b = ::mpz_cmp ( MPZ , *s )    ;
  return ( b == 0 )                 ;
}

bool vlong::operator == (std::string & v)
{
  nKickOut ( ( v . size ( ) <= 0 ) , false ) ;
  vlong V = v                                ;
  mpz_t * s = (mpz_t *)V . data ( )          ;
  int b = ::mpz_cmp ( MPZ , *s )             ;
  return ( b == 0 )                          ;
}

bool vlong::operator == (QString & v)
{
  nKickOut ( ( v . length ( ) <= 0 ) , false ) ;
  vlong V = v                                  ;
  mpz_t * s = (mpz_t *)V . data ( )            ;
  int b = ::mpz_cmp ( MPZ , *s )               ;
  return ( b == 0 )                            ;
}

bool vlong::operator != (vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  int b = ::mpz_cmp ( *m , *s )     ;
  return ( b != 0 )                 ;
}

bool vlong::operator != (unsigned long v)
{
  int b = mpz_cmp_ui( MPZ , v ) ;
  return ( b != 0 )             ;
}

bool vlong::operator != (long v)
{
  int b = mpz_cmp_si( MPZ , v ) ;
  return ( b != 0 )             ;
}

bool vlong::operator != (const char * v)
{
  vlong V = v                       ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  int b = ::mpz_cmp ( MPZ , *s )    ;
  return ( b != 0 )                 ;
}

bool vlong::operator != (std::string & v)
{
  vlong V = v                                ;
  mpz_t * s = (mpz_t *)V . data ( )          ;
  int b = ::mpz_cmp ( MPZ , *s )             ;
  return ( b != 0 )                          ;
}

bool vlong::operator != (QString & v)
{
  vlong V = v                                  ;
  mpz_t * s = (mpz_t *)V . data ( )            ;
  int b = ::mpz_cmp ( MPZ , *s )               ;
  return ( b != 0 )                            ;
}

int vlong::compare(vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  return ::mpz_cmp ( *m , *s )      ;
}

int vlong::compare(unsigned long v)
{
  return ::mpz_cmp_ui( MPZ , v ) ;
}

int vlong::compare(long v)
{
  return ::mpz_cmp_si( MPZ , v ) ;
}

int vlong::compare(const char * v)
{
  vlong V = v                       ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  return ::mpz_cmp ( MPZ , *s )     ;
}

int vlong::compare(std::string & v)
{
  vlong V = v                       ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  return ::mpz_cmp ( MPZ , *s )     ;
}

int vlong::compare(QString & v)
{
  vlong V = v                       ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  return ::mpz_cmp ( MPZ , *s )     ;
}

vlong & vlong::setBit(unsigned long long index)
{
  ::mpz_setbit ( MPZ , index ) ;
  return ME                    ;
}

vlong & vlong::clearBit(unsigned long long index)
{
  ::mpz_clrbit ( MPZ , index ) ;
  return ME                    ;
}

vlong & vlong::complement(unsigned long long index)
{
  ::mpz_combit ( MPZ , index ) ;
  return ME                    ;
}

int vlong::bit(unsigned long long index)
{
  return ::mpz_tstbit ( MPZ , index ) ;
}

vlong & vlong::operator ++ (void)
{
  vlong V ( "1" )                           ;
  mpz_t * s = (mpz_t *)V . data ( )         ;
  ::mpz_add ( MPZ , MPZ , *s )              ;
  return ME                                 ;
}

vlong & vlong::operator -- (void)
{
  vlong V ( "1" )                   ;
  mpz_t * s = (mpz_t *)V . data ( ) ;
  ::mpz_sub ( MPZ , MPZ , *s )      ;
  return ME                         ;
}

vlong & vlong::operator &= (vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  ::mpz_and ( *m , *m , *s )        ;
  return ME                         ;
}

vlong & vlong::operator |= (vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  ::mpz_ior ( *m , *m , *s )        ;
  return ME                         ;
}

vlong & vlong::operator ^= (vlong & v)
{
  mpz_t * m = (mpz_t *)    data ( ) ;
  mpz_t * s = (mpz_t *)v . data ( ) ;
  ::mpz_xor ( *m , *m , *s )        ;
  return ME                         ;
}

vlong & vlong::operator ~ (void)
{
  ::mpz_com ( MPZ , MPZ ) ;
  return ME               ;
}

vlong & vlong::operator ^ (unsigned long n)
{
  ::mpz_pow_ui ( MPZ , MPZ , n ) ;
  return ME                      ;
}

vlong & vlong::neg(void)
{
  ::mpz_neg ( MPZ , MPZ ) ;
  return ME               ;
}

vlong & vlong::abs(void)
{
  ::mpz_abs ( MPZ , MPZ ) ;
  return ME               ;
}

vlong & vlong::swap(vlong & v)
{
  mpz_t * V = (mpz_t *)v . data ( ) ;
  ::mpz_swap ( MPZ , *V )           ;
  return ME                         ;
}

vlong & vlong::square(void)
{
  ::mpz_pow_ui ( MPZ , MPZ , 2 ) ;
  return ME                      ;
}

vlong & vlong::root(unsigned long n)
{
  ::mpz_root ( MPZ , MPZ , n ) ;
  return ME                    ;
}

vlong & vlong::sqrt(void)
{
  ::mpz_sqrt ( MPZ , MPZ ) ;
  return ME                ;
}

vlong & vlong::shift(unsigned long long bits)
{
  ::mpz_mul_2exp ( MPZ , MPZ , bits ) ;
  return ME                           ;
}

vlong & vlong::factorial(unsigned long n)
{
  ::mpz_fac_ui ( MPZ , n ) ;
  return ME                ;
}

vlong & vlong::fibonacci(unsigned long n)
{
  ::mpz_fib_ui ( MPZ , n ) ;
  return ME                ;
}

vlong & vlong::binomial(unsigned long k)
{
  ::mpz_bin_ui ( MPZ , MPZ , k ) ;
  return ME                      ;
}

vlong & vlong::lucas(unsigned long k)
{
  ::mpz_lucnum_ui ( MPZ , k ) ;
  return ME                   ;
}

vlong & vlong::gcd ( vlong & a , vlong & b )
{
  mpz_t * A = (mpz_t *)a . data ( ) ;
  mpz_t * B = (mpz_t *)b . data ( ) ;
  mpz_t * C = (mpz_t *)    data ( ) ;
  ::mpz_gcd ( *C , *A , *B )        ;
  return  ME                        ;
}

vlong & vlong::lcm ( vlong & a , vlong & b )
{
  mpz_t * A = (mpz_t *)a . data ( ) ;
  mpz_t * B = (mpz_t *)b . data ( ) ;
  mpz_t * C = (mpz_t *)    data ( ) ;
  ::mpz_lcm ( *C , *A , *B )        ;
  return  ME                        ;
}

int vlong::jacobi ( vlong & b )
{
  mpz_t * A = (mpz_t *)    data ( ) ;
  mpz_t * B = (mpz_t *)b . data ( ) ;
  return ::mpz_jacobi   ( *A , *B ) ;
}

int vlong::legendre ( vlong & b )
{
  mpz_t * A = (mpz_t *)    data ( ) ;
  mpz_t * B = (mpz_t *)b . data ( ) ;
  return ::mpz_legendre ( *A , *B ) ;
}

int vlong::kronecker ( vlong & b )
{
  mpz_t * A = (mpz_t *)    data ( )  ;
  mpz_t * B = (mpz_t *)b . data ( )  ;
  return ::mpz_kronecker ( *A , *B ) ;
}

int vlong::invert ( vlong & modulo , vlong & result )
{
  mpz_t * M = (mpz_t *) modulo . data ( ) ;
  mpz_t * R = (mpz_t *) result . data ( ) ;
  return ::mpz_invert ( *R , MPZ , *M )   ;
}

int vlong::MillerRabin(int reps)
{
  return ::mpz_probab_prime_p ( MPZ , reps ) ;
}

int vlong::PerfectPower(void)
{
  return ::mpz_perfect_power_p ( MPZ ) ;
}

int vlong::PerfectSquare(void)
{
  return ::mpz_perfect_square_p ( MPZ ) ;
}

vlong & vlong::urandomb(vrandom & r,unsigned long long n)
{
  ::mpz_urandomb ( MPZ , RANX ( r ) -> ranx , n ) ;
  return ME                                       ;
}

vlong & vlong::urandomm(vrandom & r,vlong & n)
{
  mpz_t * B = (mpz_t *)n . data ( )                ;
  ::mpz_urandomm ( MPZ , RANX ( r ) -> ranx , *B ) ;
  return ME                                        ;
}

vlong & vlong::rrandomb(vrandom & r,unsigned long long n)
{
  ::mpz_rrandomb ( MPZ , RANX ( r ) -> ranx , n ) ;
  return ME                                       ;
}

unsigned long long vlong::population(void)
{
  return ::mpz_popcount ( MPZ ) ;
}

unsigned long long vlong::hamdist(vlong & v)
{
  mpz_t * V = (mpz_t *)v . data ( ) ;
  return ::mpz_hamdist ( MPZ , *V ) ;
}

unsigned long long vlong::scan0(unsigned long long startingBit)
{
  return ::mpz_scan0 ( MPZ , startingBit ) ;
}

unsigned long long vlong::scan1(unsigned long long startingBit)
{
  return ::mpz_scan1 ( MPZ , startingBit ) ;
}

bool vlong::odd(void)
{
  return ( 0 != mpz_odd_p  ( MPZ ) ) ;
}

bool vlong::even(void)
{
  return ( 0 != mpz_even_p ( MPZ ) ) ;
}

int vlong::sign(void)
{
  return mpz_sgn ( MPZ ) ;
}

qint64 vlong::digits(int base)
{
  return (qint64)::mpz_sizeinbase ( MPZ , base ) ;
}

void vlong::clear(void)
{
  ::mpz_clear ( MPZ ) ;
}

bool vlong::isULong(void)
{
  return ( 0 != ::mpz_fits_ulong_p ( MPZ ) ) ;
}

bool vlong::isLong(void)
{
  return ( 0 != ::mpz_fits_slong_p ( MPZ ) ) ;
}

bool vlong::isUInt(void)
{
  return ( 0 != ::mpz_fits_uint_p ( MPZ ) ) ;
}

bool vlong::isInt(void)
{
  return ( 0 != ::mpz_fits_sint_p ( MPZ ) ) ;
}

bool vlong::isUShort(void)
{
  return ( 0 != ::mpz_fits_ushort_p ( MPZ ) ) ;
}

bool vlong::isShort(void)
{
  return ( 0 != ::mpz_fits_sshort_p ( MPZ ) ) ;
}

long vlong::toLong(void)
{
  return (long)::mpz_get_si ( MPZ ) ;
}

unsigned long vlong::toULong(void)
{
  return (long)::mpz_get_ui ( MPZ ) ;
}

QString vlong::String(int base)
{
  QString S                                ;
  char *  s = ::mpz_get_str(NULL,base,MPZ) ;
  nKickOut ( IsNull(s) , S )               ;
  S = s                                    ;
  delete [] s                              ;
  return S                                 ;
}
