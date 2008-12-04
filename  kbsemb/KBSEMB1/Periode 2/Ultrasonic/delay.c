/*
 * (C) Christelijke Hogeschool Windesheim 2002
 *             *** delay.c ***
 */

#include "portab.h"

/*
 * FUNCTIE     : delay
 * DOEL        : Deze functie wacht gedurende de opgegeven tijd in ms
 * PARAMETERS  : ms wachttijd in millisecondes
 * RETURNS     : void
 * SIDE EFFECTS: none
 */

void delay( const int ms )
{
  T_Unsigned_16 i, j;
  for ( i = 0; i <= ms; i++ )
  {
      for ( j = 0; j <= 1000; j++ )
    {
      /* doe niets */
    }
  }
}
