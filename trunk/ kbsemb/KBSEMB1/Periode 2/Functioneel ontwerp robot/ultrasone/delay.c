/*
 * (C) Christelijke Hogeschool Windesheim 2002
 *             *** delay.c ***
 */

#include "portab.h"

/*
 * FUNCTIE     : delay
 * DOEL        : Deze functie wacht gedurende de opgegeven tijd in us
 * PARAMETERS  : us wachttijd in microsecondes
 * RETURNS     : void
 * SIDE EFFECTS: none
 */

void delay( const int us )
{
  T_Unsigned_16 i, j;
  int count = us*12;
  for ( i = 0; i <= count; i++ )
  {

  }
}
