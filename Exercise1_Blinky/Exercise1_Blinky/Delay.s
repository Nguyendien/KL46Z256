

; Delay function
; generate 100 ms delay
; Input: R0 contain iteration number
	AREA DelayA, CODE, READONLY ; declare code area
	ENTRY
	EXPORT Delay ; make delay function visible to main()

Delay 	LDR r0, =0x1B7740
LOOP	SUBS r0,r0,#1 
		CMP r0,#0
		BEQ LOOPEND
		B	LOOP
LOOPEND BX lr
		END