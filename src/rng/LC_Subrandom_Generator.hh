//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   rng/LC_Subrandom_Generator.hh
 * \author Kent Budge
 * \brief  Definition of class LC_Subrandom_Generator
 * \note   Copyright (C) 2016-2019 Triad National Security, LLC.
 *         All rights reserved. */
//---------------------------------------------------------------------------//

#ifndef rng_LC_Subrandom_Generator_hh
#define rng_LC_Subrandom_Generator_hh

#include "Subrandom_Generator.hh"
#include "gsl/gsl_rng.h"

namespace rtt_rng {

//===========================================================================//
/*!
 * \class LC_Subrandom_Generator
 * \brief Generator for a sequence of subrandom (pseudorandom) vectors.
 *
 * This is an implementation of the old, hoary linear congruential
 * generator. The name is somewhat of a misnomer since this is a true
 * pseudorandom generator (is that an oxymoron?) rather than a subrandom
 * generator. In other words, the approximation to an integral computed using
 * this sequence as quadrature points converges smoothly, but only as
 * 1/sqrt(N) rather than 1/N.
 */
//===========================================================================//

class LC_Subrandom_Generator : public Subrandom_Generator {
public:
  // NESTED CLASSES AND TYPEDEFS

  // CREATORS

  //! Normal constructor.
  explicit LC_Subrandom_Generator(unsigned const count = 1);

  ~LC_Subrandom_Generator();

  // MANIPULATORS

  //! Advance sequence.
  void shift_vector();

  //! Get the next element in the current vector.
  double shift();

  // ACCESSORS

  bool check_class_invariants() const;

private:
  // NESTED CLASSES AND TYPEDEFS

  // IMPLEMENTATION

  //! not implemented
  LC_Subrandom_Generator(LC_Subrandom_Generator const &);
  // not implemented
  LC_Subrandom_Generator &operator=(LC_Subrandom_Generator const &);

  // DATA

  gsl_rng *generator_;
};

} // end namespace rtt_rng

#endif // rng_LC_Subrandom_Generator_hh

//---------------------------------------------------------------------------//
// end of rng/LC_Subrandom_Generator.hh
//---------------------------------------------------------------------------//
