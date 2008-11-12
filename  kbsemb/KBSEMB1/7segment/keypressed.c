/*
 * FUNCTIE     : key_pressed
 * DOEL        : Deze functie leest en 'debounces' een gegeven drukknop.
 * PARAMETERS  : welke_key is 1, 2 or 3
 * RETURNS     : als switch is niet ingedrukt, return 0
 *               als switch is ingedrukt, return 1
 * SIDE EFFECTS: wacht tenminste 20 ms wanneer de knop is ingedrukt
 */

T_Unsigned_8 key_pressed( T_Unsigned_8 welke_key )
{
  T_Unsigned_8 ingedrukt = false;
  T_Unsigned_8 key;
  T_Unsigned_8 i;

  switch( welke_key )
  {
    case 1:  key = 0x04; break;
    case 2:  key = 0x08; break;
    case 3:  key = 0x10; break;
  }

  i = PINB;
  if( i != 0) {
    /* knop is ingedrukt*/
    delay( 30 );
	while( i == key ) {
		ingedrukt = true;
		i = PINB;
	}
  }
  return ingedrukt;
}

