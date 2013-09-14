//----------------------------------*-C++-*----------------------------------------------//
/*!
 * \file   quadrature/Product_Chebyshev_Legendre.cc
 * \author James S. Warsa
 * \date   Wed Sep  1 10:19:52 2004
 * \brief  A class for Product Chebyshev-Gauss-Legendre quadrature sets.
 * \note   Copyright 2004 The Regents of the University of California.
 */
//---------------------------------------------------------------------------------------//
// $Id: Product_Chebyshev_Legendre.cc 6718 2012-08-30 20:03:01Z warsa $
//---------------------------------------------------------------------------------------//

// #include <iostream>
// #include <iomanip>
// #include <cmath>
// #include <algorithm>

#include "Product_Chebyshev_Legendre.hh"

#include "gauleg.hh"
#include "ds++/to_string.hh"

namespace rtt_quadrature
{
using namespace rtt_dsxx;

//---------------------------------------------------------------------------------------//
string Product_Chebyshev_Legendre::name() const { return "Product Chebyshev Legendre"; }

//---------------------------------------------------------------------------------------//
string Product_Chebyshev_Legendre::parse_name()  const { return "product cl"; }
        
//---------------------------------------------------------------------------------------//
Quadrature_Class Product_Chebyshev_Legendre::quadrature_class() const
{
    return OCTANT_QUADRATURE;
}

//---------------------------------------------------------------------------------------//
unsigned Product_Chebyshev_Legendre::number_of_levels() const { return sn_order_; }
    
//---------------------------------------------------------------------------------------//
string Product_Chebyshev_Legendre::as_text(string const &indent) const
{
    string Result =
        indent + "type = " + parse_name() +
        indent + "  order = " + to_string(sn_order()) + " " + to_string(azimuthal_order_) +
        Octant_Quadrature::as_text(indent);

    return Result;
}

//---------------------------------------------------------------------------------------//
void
Product_Chebyshev_Legendre::create_octant_ordinates_(vector<double> &mu,
                                                     vector<double> &eta,
                                                     vector<double> &wt) const
{
    using std::fabs;
    using std::sqrt;
    using std::cos;
    using rtt_dsxx::soft_equiv;

    // The number of quadrature levels is equal to the requested SN order.
    size_t levels = sn_order();

    // We build the 3-D first, then edit as appropriate.

    size_t numOrdinates = levels*azimuthal_order_/4;

    // Force the direction vectors to be the correct length.
    mu.resize(numOrdinates);
    eta.resize(numOrdinates);
    wt.resize(numOrdinates);

    double const mu1 = -1; // range of direction
    double const mu2 =  1;
    vector<double> GL_mu(levels);
    vector<double> GL_wt(levels);
    gauleg( mu1, mu2, GL_mu, GL_wt, sn_order() );

    // NOTE: this aligns the gauss points with the x-axis (r-axis in cylindrical coords)

    unsigned icount=0;

    for (unsigned i=0; i<levels/2; ++i)
    {
        double xmu=GL_mu[i];
        double xwt=GL_wt[i];
        double xsr=sqrt(1.0-xmu*xmu);
            
        for (unsigned j=0; j<azimuthal_order_/2; ++j)
        {
            unsigned ordinate=icount;

            mu[ordinate]  = xsr*cos(rtt_units::PI*(2.0*j+1.0)/azimuthal_order_/2.0);
            eta[ordinate] = xsr*sin(rtt_units::PI*(2.0*j+1.0)/azimuthal_order_/2.0);
            wt[ordinate]  = xwt/azimuthal_order_;

            ++icount;
        }
    }
}


} // end namespace rtt_quadrature

//---------------------------------------------------------------------------------------//
//                 end of Product_Chebyshev_Legendre.cc
//---------------------------------------------------------------------------------------//