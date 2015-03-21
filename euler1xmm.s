	.section	__TEXT,__text,regular,pure_instructions
	.section	__TEXT,__literal8,8byte_literals
	.align	3
M1:
	.quad	-4616189618054758400    ## double -1
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
	addsd	M1(%rip), %xmm1
	xorps	%xmm0, %xmm0	# xmm0 = r
	xorps	%xmm2, %xmm2	# xmm2 = 0
	.align	4, 0x90
while:
	movsd	%xmm1, %xmm3
	movsd	%xmm1, %xmm5
	divsd	D3(%rip), %xmm3	# xmm3 = q3
	divsd	D5(%rip), %xmm5	# xmm5 = q5
	roundsd	$3, %xmm3, %xmm4# xmm4 = t3
	roundsd	$3, %xmm5, %xmm6# xmm6 = t5
	subsd	%xmm4, %xmm3	# xmm3 = q3 - t3
	movsd	%xmm5, %xmm8	# xmm8 = q5
	subsd	%xmm6, %xmm8	# xmm8 = q5 - t5
	mulsd	%xmm3, %xmm8	# xmm8 = *
	cmpeqsd	%xmm2, %xmm8	# xmm8 = !nz
	movd	%xmm8, %rax	# rax = !nz
	andl	$1, %eax	# eax = !nz
	xorps	%xmm7, %xmm7	# xmm7 = 0
	cvtsi2sdl	%eax, %xmm7	# xmm7 = !nz
	mulsd	%xmm1, %xmm7	# xmm7 = i * !nz
	addsd	%xmm7, %xmm0	# xmm0 = r += i * !nz
	addsd	M1(%rip), %xmm1	# xmm1 = --i
	ucomisd	%xmm2, %xmm1	# i > 0
	ja	while
## BB#2:
	popq	%rbp
	retq


.subsections_via_symbols
