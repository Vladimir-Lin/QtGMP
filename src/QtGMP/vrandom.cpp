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
#define RANDOM                     ((RANDSTATE *)data())
#define RANX(d)                    ((RANDSTATE *)d.data())

vrandom:: vrandom    (void)
        : QByteArray (    )
{
  resize   ( sizeof(RANDSTATE)              ) ;
  ::memset ( data() , 0 , sizeof(RANDSTATE) ) ;
}

vrandom:: vrandom    (const vrandom & random)
        : QByteArray (    )
{
  resize             ( sizeof(RANDSTATE)                        ) ;
  ::memset           ( data() , 0 , sizeof(RANDSTATE)           ) ;
  if ( 0 == RANX ( random ) -> ranx ) return                      ;
  ::gmp_randinit_set ( RANDOM -> ranx , RANX ( random ) -> ranx ) ;
}

vrandom::~vrandom (void)
{
  if ( 0 == RANDOM->ranx ) return    ;
  ::gmp_randclear ( RANDOM -> ranx ) ;
}

void vrandom::clear (void)
{
  if ( 0 == RANDOM -> ranx ) return           ;
  ::gmp_randclear ( RANDOM -> ranx )          ;
  ::memset ( data() , 0 , sizeof(RANDSTATE) ) ;
}

void vrandom::Default(void)
{
  clear                  (                ) ;
  ::gmp_randinit_default ( RANDOM -> ranx ) ;
}

void vrandom::Mersenne(void)
{
  clear             (                ) ;
  ::gmp_randinit_mt ( RANDOM -> ranx ) ;
}

void vrandom::Congruential(vlong & v,unsigned long c,unsigned long long e)
{
  clear ( )                       ;
  ::gmp_randinit_lc_2exp          (
    RANDOM -> ranx                ,
    (*((mpz_t *) v . data ( ) ) ) ,
    c                             ,
    e                           ) ;
}

int vrandom::Congruential (unsigned long long size)
{
  clear                              (                       ) ;
  return ::gmp_randinit_lc_2exp_size ( RANDOM -> ranx , size ) ;
}

void vrandom::Seed(vlong & v)
{
  ::gmp_randseed ( RANDOM -> ranx , (*((mpz_t *) v . data ( ) ) ) ) ;
}

void vrandom::Seed(unsigned long c)
{
  ::gmp_randseed_ui ( RANDOM -> ranx , c ) ;
}

unsigned long vrandom::urandomb(unsigned long n)
{
  return ::gmp_urandomb_ui ( RANDOM -> ranx , n ) ;
}

unsigned long vrandom::urandomm(unsigned long n)
{
  return ::gmp_urandomm_ui ( RANDOM -> ranx , n ) ;
}
