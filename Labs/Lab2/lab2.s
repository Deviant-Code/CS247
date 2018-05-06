	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	subq	$560, %rsp              ## imm = 0x230
	xorl	%eax, %eax
	movl	$1, %ecx
	movl	%ecx, %edx
	leaq	-512(%rbp), %r8
	movq	___stack_chk_guard@GOTPCREL(%rip), %r9
	movq	(%r9), %r9
	movq	%r9, -8(%rbp)
	movl	$0, -516(%rbp)
	movl	%edi, -520(%rbp)
	movq	%rsi, -528(%rbp)
	movq	%r8, %rdi
	movl	%eax, %esi
	callq	_memset
	cmpl	$2, -520(%rbp)
	jl	LBB0_4
## BB#1:
	movq	-528(%rbp), %rax
	movq	8(%rax), %rax
	movsbl	(%rax), %edi
	callq	_isdigit
	cmpl	$0, %eax
	jne	LBB0_3
## BB#2:
	movq	-528(%rbp), %rax
	movq	8(%rax), %rax
	movsbl	(%rax), %ecx
	cmpl	$45, %ecx
	jne	LBB0_4
LBB0_3:
	movq	-528(%rbp), %rax
	movq	8(%rax), %rdi
	callq	_atoi
	movl	%eax, -532(%rbp)
	jmp	LBB0_5
LBB0_4:
	leaq	L_.str(%rip), %rsi
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	movb	$0, %al
	callq	_fprintf
	movl	$1, -516(%rbp)
	movl	%eax, -540(%rbp)        ## 4-byte Spill
	jmp	LBB0_10
LBB0_5:
	cmpl	$3, -520(%rbp)
	jl	LBB0_8
## BB#6:
	movq	-528(%rbp), %rax
	movq	16(%rax), %rax
	movsbl	(%rax), %edi
	callq	_isdigit
	cmpl	$0, %eax
	je	LBB0_8
## BB#7:
	movq	-528(%rbp), %rax
	movq	16(%rax), %rdi
	callq	_atoi
	movl	%eax, -536(%rbp)
	jmp	LBB0_9
LBB0_8:
	leaq	L_.str(%rip), %rsi
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	movb	$0, %al
	callq	_fprintf
	movl	$1, -516(%rbp)
	movl	%eax, -544(%rbp)        ## 4-byte Spill
	jmp	LBB0_10
LBB0_9:
	leaq	-512(%rbp), %rsi
	movl	-532(%rbp), %edi
	movl	-536(%rbp), %edx
	callq	_itoa
	leaq	L_.str.1(%rip), %rdi
	movq	%rax, %rsi
	movb	$0, %al
	callq	_printf
	movl	$0, -516(%rbp)
	movl	%eax, -548(%rbp)        ## 4-byte Spill
LBB0_10:
	movl	-516(%rbp), %eax
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-8(%rbp), %rdx
	cmpq	%rdx, %rcx
	movl	%eax, -552(%rbp)        ## 4-byte Spill
	jne	LBB0_12
## BB#11:
	movl	-552(%rbp), %eax        ## 4-byte Reload
	addq	$560, %rsp              ## imm = 0x230
	popq	%rbp
	retq
LBB0_12:
	callq	___stack_chk_fail
	.cfi_endproc
                                        ## -- End function
	.globl	_itoa                   ## -- Begin function itoa
	.p2align	4, 0x90
_itoa:                                  ## @itoa
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi3:
	.cfi_def_cfa_offset 16
Lcfi4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi5:
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movl	%edi, -12(%rbp)
	movq	%rsi, -24(%rbp)
	movl	%edx, -28(%rbp)
	cmpl	$0, -12(%rbp)
	jne	LBB1_2
## BB#1:
	leaq	L_.str.2(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB1_23
LBB1_2:
	movl	$0, -32(%rbp)
	cmpl	$0, -12(%rbp)
	jge	LBB1_4
## BB#3:
	movl	-32(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -32(%rbp)
	imull	$-1, -12(%rbp), %eax
	movl	%eax, -12(%rbp)
LBB1_4:
	cmpl	$1, -28(%rbp)
	jne	LBB1_11
## BB#5:
	movl	$0, -36(%rbp)
LBB1_6:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$0, -12(%rbp)
	jle	LBB1_10
## BB#7:                                ##   in Loop: Header=BB1_6 Depth=1
	cmpl	$500, -36(%rbp)         ## imm = 0x1F4
	jle	LBB1_9
## BB#8:
	leaq	L_.str.3(%rip), %rsi
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	movb	$0, %al
	callq	_fprintf
	movq	-24(%rbp), %rsi
	movb	$0, (%rsi)
	movq	-24(%rbp), %rsi
	movq	%rsi, -8(%rbp)
	movl	%eax, -56(%rbp)         ## 4-byte Spill
	jmp	LBB1_23
LBB1_9:                                 ##   in Loop: Header=BB1_6 Depth=1
	movl	-12(%rbp), %eax
	addl	$-1, %eax
	movl	%eax, -12(%rbp)
	movq	-24(%rbp), %rcx
	movslq	-36(%rbp), %rdx
	movb	$124, (%rcx,%rdx)
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	LBB1_6
LBB1_10:
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	LBB1_23
LBB1_11:
	movl	$0, -40(%rbp)
LBB1_12:                                ## =>This Inner Loop Header: Depth=1
	cmpl	$0, -12(%rbp)
	jle	LBB1_17
## BB#13:                               ##   in Loop: Header=BB1_12 Depth=1
	movl	-12(%rbp), %eax
	cltd
	idivl	-28(%rbp)
	movl	%edx, -44(%rbp)
	cmpl	$9, -44(%rbp)
	jle	LBB1_15
## BB#14:                               ##   in Loop: Header=BB1_12 Depth=1
	movl	-44(%rbp), %eax
	subl	$10, %eax
	movl	%eax, -44(%rbp)
	movl	-44(%rbp), %eax
	addl	$97, %eax
	movb	%al, %cl
	movq	-24(%rbp), %rdx
	movslq	-40(%rbp), %rsi
	movb	%cl, (%rdx,%rsi)
	jmp	LBB1_16
LBB1_15:                                ##   in Loop: Header=BB1_12 Depth=1
	movl	-44(%rbp), %eax
	addl	$48, %eax
	movb	%al, %cl
	movq	-24(%rbp), %rdx
	movslq	-40(%rbp), %rsi
	movb	%cl, (%rdx,%rsi)
LBB1_16:                                ##   in Loop: Header=BB1_12 Depth=1
	movl	-28(%rbp), %eax
	movl	-12(%rbp), %ecx
	movl	%eax, -60(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	cltd
	movl	-60(%rbp), %ecx         ## 4-byte Reload
	idivl	%ecx
	movl	%eax, -12(%rbp)
	movl	-40(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -40(%rbp)
	jmp	LBB1_12
LBB1_17:
	cmpl	$0, -32(%rbp)
	je	LBB1_19
## BB#18:
	movq	-24(%rbp), %rax
	movslq	-40(%rbp), %rcx
	movb	$45, (%rax,%rcx)
	movl	-40(%rbp), %edx
	addl	$1, %edx
	movl	%edx, -40(%rbp)
LBB1_19:
	movl	$0, -52(%rbp)
	movl	-40(%rbp), %eax
	addl	$-1, %eax
	movl	%eax, -40(%rbp)
LBB1_20:                                ## =>This Inner Loop Header: Depth=1
	movl	-40(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jl	LBB1_22
## BB#21:                               ##   in Loop: Header=BB1_20 Depth=1
	movq	-24(%rbp), %rax
	movslq	-52(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	movb	%dl, -45(%rbp)
	movq	-24(%rbp), %rax
	movslq	-40(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	movq	-24(%rbp), %rax
	movslq	-52(%rbp), %rcx
	movb	%dl, (%rax,%rcx)
	movb	-45(%rbp), %dl
	movq	-24(%rbp), %rax
	movslq	-40(%rbp), %rcx
	movb	%dl, (%rax,%rcx)
	movl	-52(%rbp), %esi
	addl	$1, %esi
	movl	%esi, -52(%rbp)
	movl	-40(%rbp), %esi
	addl	$-1, %esi
	movl	%esi, -40(%rbp)
	jmp	LBB1_20
LBB1_22:
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
LBB1_23:
	movq	-8(%rbp), %rax
	addq	$64, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"ERROR: './itoa number base'\n"

L_.str.1:                               ## @.str.1
	.asciz	"%s\n"

L_.str.2:                               ## @.str.2
	.asciz	"0"

L_.str.3:                               ## @.str.3
	.asciz	"ERROR: Number conversion too big for array."


.subsections_via_symbols
