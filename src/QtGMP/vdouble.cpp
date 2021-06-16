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
#define MPF                        (*((mpf_t *)data()))
#define RANX(d)                    ((RANDSTATE *)d.data())

vdouble:: vdouble    (void)
        : QByteArray (    )
{
  resize     ( sizeof(mpf_t) ) ;
  ::mpf_init ( MPF           ) ;
}

vdouble:: vdouble    (const vdouble & v)
        : QByteArray (                 )
{
  resize     ( sizeof(mpf_t) )      ;
  mpf_t * m = (mpf_t *)    data ( ) ;
  mpf_t * s = (mpf_t *)v . data ( ) ;
  ::mpf_init ( *m            )      ;
  ::mpf_set  ( *m , *s       )      ;
}

vdouble:: vdouble    ( const double v )
        : QByteArray (                )
{
  resize           ( sizeof(mpf_t) ) ;
  ::mpf_init_set_d ( MPF , v       ) ;
}

vdouble:: vdouble    ( const unsigned long v )
        : QByteArray (                       )
{
  resize            ( sizeof(mpf_t) ) ;
  ::mpf_init_set_ui ( MPF , v       ) ;
}

vdouble:: vdouble    ( const long v )
        : QByteArray (              )
{
  resize            ( sizeof(mpf_t) ) ;
  ::mpf_init_set_si ( MPF , v       ) ;
}

vdouble:: vdouble (const double v,const unsigned long prec)
{
  resize           ( sizeof(mpf_t) ) ;
  ::mpf_init_set_d ( MPF , v       ) ;
  ::mpf_set_prec   ( MPF , prec    ) ;
}

vdouble:: vdouble    ( const char * v,const int base )
        : QByteArray (                               )
{
  resize             ( sizeof(mpf_t)  ) ;
  ::mpf_init_set_str ( MPF , v , base ) ;
}

vdouble:: vdouble    ( const std::string & v,const int base )
        : QByteArray (                                      )
{
  resize             ( sizeof(mpf_t)                      ) ;
  ::mpf_init_set_str ( MPF , (char *) v . data ( ) , base ) ;
}

vdouble:: vdouble    ( const QString & v,const int base )
        : QByteArray (                                  )
{
  resize             ( sizeof(mpf_t)                           ) ;
  ::mpf_init_set_str ( MPF , (char *) v . constData ( ) , base ) ;
}

vdouble::~vdouble (void)
{
  ::mpf_clear ( MPF ) ;
}

unsigned long vdouble::defaultPrecision(void)
{
  return (unsigned long)::mpf_get_default_prec() ;
}

unsigned long vdouble::setDefaultPrecision(unsigned long prec)
{
  ::mpf_set_default_prec ( prec )                ;
  return (unsigned long)::mpf_get_default_prec() ;
}

unsigned long vdouble::precision(void)
{
  return (unsigned long)::mpf_get_prec(MPF) ;
}

unsigned long vdouble::setPrecision (unsigned long prec)
{
  ::mpf_set_prec(MPF,prec)                  ;
  return (unsigned long)::mpf_get_prec(MPF) ;
}

vdouble & vdouble::operator = (vdouble & v)
{
  mpf_t * m = (mpf_t *)    data ( ) ;
  mpf_t * s = (mpf_t *)v . data ( ) ;
  ::mpf_set   ( *m , *s )           ;
  return ME                         ;
}

vdouble & vdouble::operator = (double v)
{
  ::mpf_set_d ( MPF , v ) ;
  return ME               ;
}

vdouble & vdouble::operator = (unsigned long v)
{
  ::mpf_set_ui ( MPF , v ) ;
  return ME                ;
}

vdouble & vdouble::operator = (long v)
{
  ::mpf_set_si  ( MPF , v ) ;
  return ME                 ;
}

vdouble & vdouble::operator = (const char * v)
{
  ::mpf_set_str ( MPF , v , 10 ) ;
  return ME                      ;
}

vdouble & vdouble::operator = (std::string & v)
{
  ::mpf_set_str ( MPF , (char *) v . data() , 10 ) ;
  return ME                                        ;
}

vdouble & vdouble::operator = (QString & v)
{
  ::mpf_set_str ( MPF , (char *) v . constData() , 10 ) ;
  return ME                                             ;
}

vdouble & vdouble::operator = (vlong & v)
{
  mpz_t * s = (mpz_t *) v . data ( ) ;
  ::mpf_set_z ( MPF , *s )           ;
  return ME                          ;
}

vdouble & vdouble::operator = (vrational & v)
{
  mpq_t * s = (mpq_t *) v . data ( ) ;
  ::mpf_set_q ( MPF , *s )           ;
  return ME                          ;
}

vdouble & vdouble::operator += (vdouble & v)
{
  mpf_t * m = (mpf_t *)    data ( ) ;
  mpf_t * s = (mpf_t *)v . data ( ) ;
  ::mpf_add   ( *m , *m , *s      ) ;
  return ME                         ;
}

vdouble & vdouble::operator += (double v)
{
  vdouble V  ;
  V   =   v  ;
  ME +=   V  ;
  return ME  ;
}

vdouble & vdouble::operator += (const char * v)
{
  vdouble V ;
  V   =   v ;
  ME +=   V ;
  return ME ;
}

vdouble & vdouble::operator += (std::string & v)
{
  vdouble V = v ;
  ME +=   V     ;
  return ME     ;
}

vdouble & vdouble::operator += (QString & v)
{
  vdouble V = v ;
  ME +=   V     ;
  return ME     ;
}

vdouble & vdouble::operator -= (vdouble & v)
{
  mpf_t * m = (mpf_t *)    data ( ) ;
  mpf_t * s = (mpf_t *)v . data ( ) ;
  ::mpf_sub   ( *m , *m , *s      ) ;
  return ME                         ;
}

vdouble & vdouble::operator -= (double v)
{
  vdouble V ;
  V   =   v ;
  ME -=   V ;
  return ME ;
}

vdouble & vdouble::operator -= (const char * v)
{
  vdouble V ;
  V   =   v ;
  ME -=   V ;
  return ME ;
}

vdouble & vdouble::operator -= (std::string & v)
{
  vdouble V = v ;
  ME -=   V     ;
  return ME     ;
}

vdouble & vdouble::operator -= (QString & v)
{
  vdouble V = v ;
  ME -=   V     ;
  return ME     ;
}

vdouble & vdouble::operator *= (vdouble & v)
{
  mpf_t * m = (mpf_t *)    data ( ) ;
  mpf_t * s = (mpf_t *)v . data ( ) ;
  ::mpf_mul   ( *m , *m , *s      ) ;
  return ME                         ;
}

vdouble & vdouble::operator *= (double v)
{
  vdouble V ;
  V   =   v ;
  ME *=   V ;
  return ME ;
}

vdouble & vdouble::operator *= (const char * v)
{
  vdouble V ;
  V   =   v ;
  ME *=   V ;
  return ME ;
}

vdouble & vdouble::operator *= (std::string & v)
{
  vdouble V = v ;
  ME *=   V     ;
  return ME     ;
}

vdouble & vdouble::operator *= (QString & v)
{
  vdouble V = v ;
  ME *=   V     ;
  return ME     ;
}

vdouble & vdouble::operator /= (vdouble & v)
{
  mpf_t * m = (mpf_t *)    data ( ) ;
  mpf_t * s = (mpf_t *)v . data ( ) ;
  ::mpf_div   ( *m , *m , *s      ) ;
  return ME                         ;
}

vdouble & vdouble::operator /= (double v)
{
  vdouble V   ( v                 ) ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  ::mpf_div   ( MPF , MPF , *s    ) ;
  return ME                         ;
}

vdouble & vdouble::operator /= (const char * v)
{
  vdouble V   ( v , 10            ) ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  ::mpf_div   ( MPF , MPF , *s    ) ;
  return ME                         ;
}

vdouble & vdouble::operator /= (std::string & v)
{
  vdouble V = v ;
  ME /=   V     ;
  return ME     ;
}

vdouble & vdouble::operator /= (QString & v)
{
  vdouble V = v ;
  ME /=   V     ;
  return ME     ;
}

bool vdouble::operator > (vdouble & v)
{
  mpf_t * m = (mpf_t *)    data ( ) ;
  mpf_t * s = (mpf_t *)v . data ( ) ;
  int b = ::mpf_cmp ( *m , *s )     ;
  return ( b > 0 )                  ;
}

bool vdouble::operator > (double v)
{
  int b = ::mpf_cmp_si( MPF , v ) ;
  return ( b > 0 )                ;
}

bool vdouble::operator > (const char * v)
{
  nKickOut ( IsNull(v) , false )    ;
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b > 0 )                  ;
}

bool vdouble::operator > (std::string & v)
{
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b > 0 )                  ;
}

bool vdouble::operator > (QString & v)
{
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b > 0 )                  ;
}

bool vdouble::operator < (vdouble & v)
{
  mpf_t * m = (mpf_t *)    data ( ) ;
  mpf_t * s = (mpf_t *)v . data ( ) ;
  int b = ::mpf_cmp ( *m , *s )     ;
  return ( b < 0 )                  ;
}

bool vdouble::operator < (double v)
{
  vdouble V         ;
  V     = v         ;
  return ( ME < V ) ;
}

bool vdouble::operator < (const char * v)
{
  nKickOut ( IsNull(v) , false )    ;
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b < 0 )                  ;
}

bool vdouble::operator < (std::string & v)
{
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b < 0 )                  ;
}

bool vdouble::operator < (QString & v)
{
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b < 0 )                  ;
}

bool vdouble::operator >= (vdouble & v)
{
  mpf_t * m = (mpf_t *)    data ( ) ;
  mpf_t * s = (mpf_t *)v . data ( ) ;
  int b = ::mpf_cmp ( *m , *s )     ;
  return ( b >= 0 )                 ;
}

bool vdouble::operator >= (double v)
{
  vdouble V          ;
  V     = v          ;
  return ( ME >= V ) ;
}

bool vdouble::operator >= (const char * v)
{
  nKickOut ( IsNull(v) , false )    ;
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b >= 0 )                 ;
}

bool vdouble::operator >= (std::string & v)
{
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b >= 0 )                 ;
}

bool vdouble::operator >= (QString & v)
{
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b >= 0 )                 ;
}

bool vdouble::operator <= (vdouble & v)
{
  mpf_t * m = (mpf_t *)    data ( ) ;
  mpf_t * s = (mpf_t *)v . data ( ) ;
  int b = ::mpf_cmp ( *m , *s )     ;
  return ( b <= 0 )                 ;
}

bool vdouble::operator <= (double v)
{
  vdouble V          ;
  V     = v          ;
  return ( ME <= V ) ;
}

bool vdouble::operator <= (const char * v)
{
  nKickOut ( IsNull(v) , false )    ;
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b <= 0 )                 ;
}

bool vdouble::operator <= (std::string & v)
{
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b <= 0 )                 ;
}

bool vdouble::operator <= (QString & v)
{
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b <= 0 )                 ;
}

bool vdouble::operator == (vdouble & v)
{
  mpf_t * m = (mpf_t *)    data ( ) ;
  mpf_t * s = (mpf_t *)v . data ( ) ;
  int b = ::mpf_cmp ( *m , *s )     ;
  return ( b == 0 )                 ;
}

bool vdouble::operator == (double v)
{
  return ( 0 == ::mpf_cmp_d ( MPF , v ) ) ;
}

bool vdouble::operator == (const char * v)
{
  nKickOut ( IsNull(v) , false )    ;
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b == 0 )                 ;
}

bool vdouble::operator == (std::string & v)
{
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b == 0 )                 ;
}

bool vdouble::operator == (QString & v)
{
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b == 0 )                 ;
}

bool vdouble::operator != (vdouble & v)
{
  mpf_t * m = (mpf_t *)    data ( ) ;
  mpf_t * s = (mpf_t *)v . data ( ) ;
  int b = ::mpf_cmp ( *m , *s )     ;
  return ( b != 0 )                 ;
}

bool vdouble::operator != (double v)
{
  return ( 0 != ::mpf_cmp_d ( MPF , v ) ) ;
}

bool vdouble::operator != (const char * v)
{
  nKickOut ( IsNull(v) , false )    ;
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b != 0 )                 ;
}

bool vdouble::operator != (std::string & v)
{
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b != 0 )                 ;
}

bool vdouble::operator != (QString & v)
{
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  int b = ::mpf_cmp ( MPF , *s )    ;
  return ( b != 0 )                 ;
}

vdouble & vdouble::operator ^ (unsigned long n)
{
  ::mpf_pow_ui ( MPF , MPF , n ) ;
  return ME                      ;
}

int vdouble::compare(vdouble & v)
{
  mpf_t * m = (mpf_t *)    data ( ) ;
  mpf_t * s = (mpf_t *)v . data ( ) ;
  return ::mpf_cmp ( *m , *s )      ;
}

int vdouble::compare(double v)
{
  return ::mpf_cmp_d ( MPF , v ) ;
}

int vdouble::compare(const char * v)
{
  nKickOut ( IsNull(v) , false )    ;
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  return ::mpf_cmp ( MPF , *s )     ;
}

int vdouble::compare(std::string & v)
{
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  return ::mpf_cmp ( MPF , *s )     ;
}

int vdouble::compare(QString & v)
{
  vlong V = v                       ;
  mpf_t * s = (mpf_t *)V . data ( ) ;
  return ::mpf_cmp ( MPF , *s )     ;
}

int vdouble::equal(vdouble & v,unsigned long long bits)
{
  mpf_t * s = (mpf_t *)v . data ( )   ;
  return ::mpf_eq ( MPF , *s , bits ) ;
}

vdouble & vdouble::neg(void)
{
  ::mpf_neg ( MPF , MPF ) ;
  return ME               ;
}

vdouble & vdouble::abs(void)
{
  ::mpf_abs ( MPF , MPF ) ;
  return ME               ;
}

vdouble & vdouble::ceil(void)
{
  ::mpf_ceil ( MPF , MPF ) ;
  return ME                ;
}

vdouble & vdouble::floor(void)
{
  ::mpf_floor ( MPF , MPF ) ;
  return ME                 ;
}

vdouble & vdouble::truncate(void)
{
  ::mpf_trunc ( MPF , MPF ) ;
  return ME                 ;
}

vdouble & vdouble::swap(vdouble & v)
{
  mpf_t * s = (mpf_t *) v . data ( ) ;
  ::mpf_swap ( MPF , *s )            ;
  return ME                          ;
}

vdouble & vdouble::shift(unsigned long long bits)
{
  ::mpf_mul_2exp ( MPF , MPF , bits ) ;
  return ME                           ;
}

vdouble & vdouble::rshift(unsigned long long bits)
{
  ::mpf_div_2exp ( MPF , MPF , bits ) ;
  return ME                           ;
}

vdouble & vdouble::square(void)
{
  ::mpf_pow_ui ( MPF , MPF , 2 ) ;
  return ME                      ;
}

vdouble & vdouble::sqrt(void)
{
  ::mpf_sqrt ( MPF , MPF ) ;
  return ME                ;
}

vdouble & vdouble::urandomb(vrandom & r,unsigned long long n)
{
  ::mpf_urandomb ( MPF , RANX ( r ) -> ranx , n ) ;
  return ME                                       ;
}

vdouble & vdouble::random2(long long size,long e)
{
  ::mpf_random2 ( MPF , size , e ) ;
  return ME                        ;
}

int vdouble::sign(void)
{
  return mpf_sgn ( MPF ) ;
}

bool vdouble::isULong(void)
{
  return ( 0 != ::mpf_fits_ulong_p ( MPF ) ) ;
}

bool vdouble::isLong(void)
{
  return ( 0 != ::mpf_fits_slong_p ( MPF ) ) ;
}

bool vdouble::isUInt(void)
{
  return ( 0 != ::mpf_fits_uint_p ( MPF ) ) ;
}

bool vdouble::isInt(void)
{
  return ( 0 != ::mpf_fits_sint_p ( MPF ) ) ;
}

bool vdouble::isUShort(void)
{
  return ( 0 != ::mpf_fits_ushort_p ( MPF ) ) ;
}

bool vdouble::isShort(void)
{
  return ( 0 != ::mpf_fits_sshort_p ( MPF ) ) ;
}

void vdouble::clear(void)
{
  ::mpf_clear ( MPF ) ;
}

int vdouble::toInt(void)
{
  return ::mpf_integer_p ( MPF ) ;
}

double vdouble::toDouble(void)
{
  return (double)::mpf_get_d ( MPF ) ;
}

QString vdouble::String(int digits,int base)
{
  QString S                             ;
  QString R                             ;
  mp_exp_t exp                          ;
  char *  r = new char [digits + 16]    ;
  memset(r,0,digits + 16)               ;
  ::mpf_get_str(r,&exp,base,digits,MPF) ;
  if (strlen(r)<=0)                     {
    delete [] r                         ;
    return S                            ;
  }                                     ;
  S = r                                 ;
  delete [] r                           ;
  if (exp<0)                            {
    int len = (int)exp                  ;
    len = -len                          ;
    QString Z = "0"                     ;
    Z = Z.repeated(len)                 ;
    R  = "0."                           ;
    R += Z                              ;
    R += S                              ;
  } else
  if (exp==0)                           {
    R  = "0."                           ;
    R += S                              ;
  } else                                {
    int mid = (int) exp                 ;
    int len = S.length() - mid          ;
    R  = S . left ( (int)exp )          ;
    R += "."                            ;
    if (len<=0)                         {
      R += "0"                          ;
    } else                              {
      R += S . mid  ( mid , len )       ;
    }                                   ;
  }                                     ;
  return R                              ;
}
