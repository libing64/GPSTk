//==============================================================================
//
//  This file is part of GPSTk, the GPS Toolkit.
//
//  The GPSTk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 3.0 of the License, or
//  any later version.
//
//  The GPSTk is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with GPSTk; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
//  
//  Copyright 2004-2019, The University of Texas at Austin
//
//==============================================================================

//==============================================================================
//
//  This software developed by Applied Research Laboratories at the University of
//  Texas at Austin, under contract to an agency or agencies within the U.S. 
//  Department of Defense. The U.S. Government retains all rights to use,
//  duplicate, distribute, disclose, or release this software. 
//
//  Pursuant to DoD Directive 523024 
//
//  DISTRIBUTION STATEMENT A: This software has been approved for public 
//                            release, distribution is unlimited.
//
//==============================================================================
/**
 * @file AstronomicalFunctions.cpp
 * Useful functions used in astronomical computations.
 */
 
#include "AstronomicalFunctions.hpp"
#include "YDSTime.hpp"
#include "JulianDate.hpp"


namespace gpstk
{

      /* Function to change from CIS to CTS(ECEF) coordinate system
       * (coordinates in meters)
       * @param posCis    Coordinates in CIS system (in meters).
       * @param t         Epoch
       *
       * @return Triple in CTS(ECEF) coordinate system.
       */
   Triple CIS2CTS(const Triple posCIS,
                  const CommonTime& t)
   {

         // Angle of Earth rotation, in radians
      double ts( UTC2SID(t)*TWO_PI/24.0 );

      Triple res;

      res.theArray[0] = ::cos(ts)*posCIS.theArray[0] +
                        ::sin(ts)*posCIS.theArray[1];

      res.theArray[1] = -::sin(ts)*posCIS.theArray[0] +
                         ::cos(ts)*posCIS.theArray[1];

      res.theArray[2] = posCIS.theArray[2];

      return res;
   } // End CIS2CTS()


      /* Function to convert from UTC to sidereal time
       * @param t         Epoch
       *
       * @return sidereal time in hours.
       */
   double UTC2SID(const CommonTime& t)
   {
      const YDSTime yds(t);

       // Hours of day (decimal)
      double h(yds.sod/3600.0);

         // Compute Julian Day, including decimals
      double jd(static_cast<double>(JulianDate(t).jd));

         // Temporal value, in centuries
      double tt( (jd - 2451545.0)/36525.0 );

      double sid( 24110.54841 + tt*( (8640184.812866) + 
                  tt*( (0.093104) - (6.2e-6*tt)) ) );

      sid = sid/3600.0 + h;
      sid = ::fmod(sid,24.0);

      if (sid < 0.0)
      {
         sid+=24.0;
      }

      return sid;
   }

} // end namespace gpstk
