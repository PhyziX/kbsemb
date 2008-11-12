;***** STK500 LEDS and SWITCH demonstration
.include "8515def.inc"
.def Temp =r16 ; Temporary register
.def SetDDR =r22 ; Set DDRA & DDRC
.def SetC =r19 ; Set CPORT
.def Delay =r17 ; Delay variable 1
.def Delay2 =r18 ; Delay variable 2
.def Delay3 =r20 ; Delay variable 3
;***** Initialization
RESET:
ldi Temp,0x01
ldi SetDDR, 0xFF
ldi SetC, 0x04
ldi Delay, 255
ldi Delay2, 255
ldi Delay3, 10
ldi r21, 0
out DDRA,SetDDR ; Set PORTA to output
out DDRC, SetDDR ; Set PORTC to output
out DDRB, r21  ; Set PORTB to input
out DDRD, r21 ; Set PORTD to input
out PORTC, SetC ; Set PORTC to output

;**** Test input/output
LOOP:
out PORTA,Temp ; Update LEDS
out PINA, Temp ; Update LEDS
sbic PINB,0x02 ; If (Port B, pin1 == 1)
add Temp, Temp ; multiply temp with 2
sbic PINB, 0x03 ; If (Port B, pin3 == 1)
swap Temp
sbic PINB, 0x04 ; If (Port B, pin2 == 1)
com Temp ; mirror values

;**** Now wait a while to make LED changes visible.
DLY:
dec Delay
brne DLY
ldi Delay, 255
dec Delay2
brne DLY
ldi Delay2, 255
dec Delay3
brne DLY
ldi Delay3, 10
rjmp LOOP ; Repeat loop forever

