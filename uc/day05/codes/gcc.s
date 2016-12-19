	.file	"gcc.c"
	.text
.globl add
	.type	add, @function
add:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	leal	(%edx,%eax), %eax
	popl	%ebp
	ret
	.size	add, .-add
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$36, %esp
	movl	$20, -20(%ebp)
	movl	$30, -16(%ebp)
	movl	$0, -8(%ebp)
	movl	$0, -12(%ebp)
	jmp	.L4
.L5:
	movl	-20(%ebp), %eax
	addl	-12(%ebp), %eax
	addl	-16(%ebp), %eax
	addl	%eax, -8(%ebp)
	addl	$1, -12(%ebp)
.L4:
	cmpl	$99, -12(%ebp)
	jle	.L5
	movl	-8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	movl	$0, %eax
	addl	$36, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.1.1 20061011 (Red Hat 4.1.1-30)"
	.section	.note.GNU-stack,"",@progbits
