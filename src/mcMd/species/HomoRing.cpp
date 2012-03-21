#ifndef HOMORING_CPP
#define MCMD_HOMORING_CPP

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010, Jian Qin and David Morse (morse@cems.umn.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include "HomoRing.h"

namespace McMd
{

   using namespace Util;

   /* 
   * Default constructor.
   */
   HomoRing::HomoRing()
    : Ring(),
      type_(NullIndex)
   {} 
 
   /* 
   * Read nAtom and type.
   */
   void HomoRing::readSpeciesParam(std::istream &in)
   {
      read<int>(in,"nAtom", nAtom_);
      read<int>(in,"type", type_);
      nBond_  = nAtom_;
      #ifdef INTER_ANGLE
      nAngle_ = nAtom_;
      #endif
      #ifdef INTER_DIHEDRAL
      nDihedral_ = nAtom_;
      #endif
      buildRing();
   }
 
   /* 
   * Return type_ for every atom.
   */
   int HomoRing::calculateAtomTypeId(int index) const
   { return type_; }
 
   /* 
   * Return 0 for every bond.
   */
   int HomoRing::calculateBondTypeId(int index) const
   { return 0; }

   #ifdef INTER_ANGLE
   /* 
   * Return 0 for every angle.
   */
   int HomoRing::calculateAngleTypeId(int index) const
   { return 0; }
   #endif

   #ifdef INTER_DIHEDRAL
   /* 
   * Return 0 for every dihedral.
   */
   int HomoRing::calculateDihedralTypeId(int index) const
   { return 0; }
   #endif

} 
#endif
