	.intel_syntax noprefix
	.section	__TEXT,__text,regular,pure_instructions
	.section	__TEXT,__literal8,8byte_literals
	.align	3
LCPI0_0:
	.quad	4602678819172646912     ## double 0.5
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_euler2intel
_euler2intel:                           ## @euler2intel
	mov	xmm4, xmm0
	pxor 	xmm0, xmm0
	pcmpeqw	xmm1, xmm1
	psllq	xmm1, 54
	psrlq	xmm1, 2
	mov	xmm2, xmm1

loop:
	addsd	xmm0, xmm3

	vaddsd	xmm3, xmm1, xmm2
	vaddsd	xmm1, xmm2, xmm3
	vaddsd	xmm2, xmm3, xmm1

	ucomisd	xmm3, xmm4
	jb	loop

	ret


.subsections_via_symbols
