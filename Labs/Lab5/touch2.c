#include <stdio.h>

int main(){

	int x, y, z;
	int x = 19;
	int y = 34;
	int z = 12;
	x += x;


}

/*
   0x00000000004004d6 <+0>:	push   %rbp    					# Save old val of rbp
   0x00000000004004d7 <+1>:	mov    %rsp,%rbp				# Set rbp to the value of rsp
=> 0x00000000004004da <+4>:	movl   $0x13,-0x10(%rbp)		# x = 19
   0x00000000004004e1 <+11>:	movl   $0x22,-0xc(%rbp)		# y = 34;
   0x00000000004004e8 <+18>:	movl   $0xc,-0x8(%rbp)		# z = 12;
   0x00000000004004ef <+25>:	mov    -0x10(%rbp),%edx 
   0x00000000004004f2 <+28>:	mov    %edx,%eax
   0x00000000004004f4 <+30>:	add    %eax,%eax
   0x00000000004004f6 <+32>:	add    %eax,%edx
   0x00000000004004f8 <+34>:	mov    -0xc(%rbp),%eax
   0x00000000004004fb <+37>:	shl    $0x2,%eax
   0x00000000004004fe <+40>:	add    %eax,%edx
   0x0000000000400500 <+42>:	mov    -0x8(%rbp),%eax
   0x0000000000400503 <+45>:	add    %eax,%eax
   0x0000000000400505 <+47>:	add    %edx,%eax
   0x0000000000400507 <+49>:	mov    %eax,-0x4(%rbp)
   0x000000000040050a <+52>:	mov    -0x4(%rbp),%eax
   0x000000000040050d <+55>:	pop    %rbp
   0x000000000040050e <+56>:	retq   
*/
