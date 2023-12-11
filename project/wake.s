	.arch msp430g2553
	.p2align 1,0
	.text

	.global wakeu
	
	;; MUST ONLY BE CALLED IN AN INTERUPT
wakeu:
	and #0xffef, 8(r1) 
	pop r0
	
