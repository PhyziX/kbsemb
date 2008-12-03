;  	
;		Mark Kappert
;		Jonathan van der Wielen
;		Gerhard Brink
;		Rick Dekker
;;
;		Opdracht 3B assembler
;
;		dit bestand vermeingvuldigd 2 getallen met elkaar:
;		ingevoerdeWaarde1 en ingevoerdeWaarde2
;	
;		het reultaat wordt gesplitst in 2 8 bits waarden
;
; ----------------------------------------------------------------
;
;	korte werking van het programma:
;	
;	1.van het getal waarmee vermeniguldigd wordt, wordt de carry bit verwijderd,
;	 en wordt het de bitjes van het getal 1 naar rechtes verplaatst( ROR)
;	2. hij controleerd of de verwijderde carry en '0'is
;		zodra dit het geval is gaat hij naar 4 en anders naar 3 en vervolgens naar 4
;	3.aan het resultaat van de laatste 8 bits wordt de ingevoerdeWaarde1 toegevoegd
;		en wordt aan de hoogste 8 bits rmh  + 1 toegevoegd
;	4. de carry bit wordt verwijderd;
;		ingevoerdeWaarde1 wordt verdubbeld (ROL )
;		de caary wordt omgedraaid en omgezet in MSB en wordt naar links verschoven (rol)
;	5. hij controleerd het getal waarmee vermenigvuldigd wordt '0' is
;		is dit het geval dan is hij klaar
;		anders gaat hij terug naar stap 1	
;
;------------------------------------------------------------------
; 
;	De registers
;
.DEF IngevoerdeWaarde1 = R0 ; Binary number to be multiplicated (8 Bit)
.DEF rmh = R1 ; Interim storage
.DEF IngevoerdeWaarde2 = R2 ; Binary number to be multiplicated with (8 Bit)
.DEF rel = R3 ; Result, LSB (16 Bit)
.DEF reh = R4 ; Result, MSB
.DEF rmp = R16 ; Multi purpose register for loading
;
;
;-------------------------------------------------------------------
;
        rjmp START
;
START:
        ldi rmp,0xB9 ; example binary 10111001
		mov IngevoerdeWaarde1,rmp  ; to the first binary register
        ldi rmp,0xB6 ; example binary 10110110
        mov IngevoerdeWaarde2,rmp  ; to the second binary register
;
; Here we start with the multiplication of the two binaries in rm1 und rm2, the result will go to reh:rel (16 Bit)
;
MULT8:
;
; Clear start values
        clr rmh ; clear interim storage
        clr rel ; clear result registers
        clr reh
;
; Here we start with the multiplication loop
;
MULT8a:
;
; Step 1: Rotate lowest bit of binary number 2 to the carry flag (divide by 2, rotate a zero into bit 7)
;
        clc ; clear carry bit
        ror IngevoerdeWaarde2 ; bit 0 to carry, bit 1 to 7 one position to the right, carry bit to bit 7
;
; Step 2: Branch depending if a 0 or 1 has been rotated to the carry bit
;
        brcc MULT8b ; jump over adding, if carry has a 0
;
; Step 3: Add 16 bits in rmh:rml to the result, with overflow from LSB to MSB
;
        add rel,IngevoerdeWaarde1 ; add LSB of IngevoerdeWaarde1 to the result
        adc reh,rmh ; add carry and MSB of rm1
;
MULT8b:
;
; Step 4: Multiply rmh:rm1 by 2 (16 bits, shift left)
;
        clc ; clear carry bit
        rol IngevoerdeWaarde1 ; rotate LSB left (multiply by 2)
        rol rmh ; rotate carry into MSB and MSB one left
;
; Step 5: Check if there are still one's in binary 2, if yes, go on multiplicating
;
        tst IngevoerdeWaarde2 ; all bits zero?
        brne MULT8a ; if not, go on in the loop
; End of the multiplication, result in reh:rel
;
; Endless loop
;
LOOP:
       rjmp loop
