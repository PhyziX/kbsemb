.include "4433def.inc"


;***** Interrupt Vectors
.cseg
.org	0x0000
	rjmp	RESET		; Reset Handle

.org	0x00c
	rjmp	schuif_licht	; Handle voor Timer1 Overflow Interrupt

;** Variable declaration
.def	temp	=r16		; Temporary storage register
.def	led		=r17		; LED value
.def	bool	=r18		; Boolean for increase / decrease check
.def	streg	=r19		; Variable for SREG

RESET:

;***** Initialize variables, set PORTs, set Timer/Counter1 values
	ldi	temp,low(RAMEND)
	out	SP,temp

	ldi bool, 0x01		; Increase (1)/ Decrease (0) boolean
	ldi led, 0x01		; LED value
	ldi temp, 0xFF
	out DDRA, temp 		; Set PORTA to output
	out DDRC, temp 		; Set PORTC to output
	out DDRB, temp  	; Set PORTB to input
	ldi temp, 0x00
	out DDRD, temp 		; Set PORTD to input
	ldi temp, 0x04
	out PORTC, temp 	; Set PORTC to output
		
	cli					; Disable interrupts
	ldi temp, 0x80
	out TCCR1A, temp	; Set check for compare flag A
	ldi temp, 0x04		; (0x01 test value)
	out TCCR1B, temp 	; Set counter frequency (0x04 = Cl_fr/256)
	ldi temp, 0xF4		; (0x01 test value)
	out OCR1H, temp		; Compare register high (value to compare to counter)
	ldi temp, 0x24		; (0x01 test value)
	out OCR1L, temp		; Compare register low
	ldi	temp, 0x10
    out	TIMSK, temp		; Set compare flag (tell the counter to compare to OCR1A)
	ldi temp, 0x00
	out TCNT1H, temp	; Set high counter value to zero
	out TCNT1L, temp	; Set low counter value to zero
	sei					; Enable interrupts


	
; Start an endless loop

forever: 
	rjmp	forever


schuif_licht:

	in streg, SREG		; Put SREG in register
	ldi temp, 0x00		; Reset counter
	out TCNT1H, temp
	out TCNT1L, temp
	
	out PORTA, led		; Set port / pin
	out PINA, led

	cpi bool, 0x01		; If bool == 1
	breq increase		; 
	rjmp decrease

increase:
	ldi bool, 0x01		; Set boolean at 1
	cpi led, 0x80		; If led == 0x80
	breq decrease		; Goto decrease
	lsl led				; Move 1 to the left
	rjmp return			; Goto return

decrease:
	ldi bool, 0x00		; Set boolean at 0
	cpi led, 0x01		; If led == 0x01
	breq increase		; Goto increase
	lsr led				; Move 1 to the right
	rjmp return			; Goto return

return:
	out SREG, streg		; Get statusregister
  	reti				; Return to program
