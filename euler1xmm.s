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
	.align	4, 0x90
while:
	movsd	%xmm1, %xmm6	# xmm6 = i
	movsd	%xmm1, %xmm5	# xmm5 = i
	divsd	D3(%rip), %xmm5	# xmm5 = q3
	divsd	D5(%rip), %xmm6	# xmm6 = q5
	roundsd	$3, %xmm5, %xmm9# xmm9 = t3
	roundsd	$3, %xmm6, %xmm4# xmm4 = t5
	subsd	%xmm9, %xmm5	# xmm5 = q3 - t3
	movsd	%xmm6, %xmm3	# xmm3 = q5
	subsd	%xmm4, %xmm3	# xmm3 = q5 - t5
	mulsd	%xmm5, %xmm3	# xmm3 = *
	xorps	%xmm2, %xmm2	# xmm2 = 0
	cmpeqsd	%xmm2, %xmm3	# xmm3 = !nz
	movd	%xmm3, %rax	# rax = !nz
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
