	.section	__TEXT,__text,regular,pure_instructions
	.section	__TEXT,__literal8,8byte_literals
	.align	3
D1:
	.quad	0x3ff0000000000000    ## double 1
D3:
	.quad	4613937818241073152     ## double 3
D5:
	.quad	4617315517961601024     ## double 5
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_euler1xmm
	.align	4, 0x90
_euler1xmm:                             ## @euler1xmm
## BB#0:
	pushq	%rbp
	movq	%rsp, %rbp
	movsd	%xmm0, %xmm1	# xmm1 = i
	subsd	D1(%rip), %xmm1
	vpermilpd $0, D1(%rip), %xmm11
	movsd	D3(%rip), %xmm12
	movhpd	D5(%rip), %xmm12
	xorps	%xmm0, %xmm0	# xmm0 = r
	vpermilpd $0, %xmm0, %xmm2	# xmm2 = 0,0
	.align	4, 0x90
while:
	vpermilpd $0, %xmm1, %xmm3
	divpd	%xmm12, %xmm3	# xmm3 = q3,q5
	roundpd	$3, %xmm3, %xmm4# xmm4 = t3,t5
	cmpneqpd %xmm4, %xmm3	# xmm3 = q3=t3,q5=t5
	vpermilpd $1, %xmm3, %xmm8
	mulsd	%xmm3, %xmm8
	cmpeqsd	%xmm2, %xmm8	# xmm8 = !nz
	andpd	%xmm1, %xmm8	# xmm8 = i * !nz
	addsd	%xmm8, %xmm0	# xmm0 = r += i * !nz
	subsd	D1(%rip), %xmm1	# xmm1 = --i
	ucomisd	%xmm2, %xmm1	# i > 0
	ja	while
## BB#2:
	popq	%rbp
	retq


.subsections_via_symbols
