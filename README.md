# CS33-AVENGERS

Stop the mad titan Thanos and save the world!  
  
In a linux environment, within the directory containing InfinityWar, please make sure to run the command:  
```
chmod +x InfinityWar
```
to enable write permissions for the executable.

## Once you're in the directory

```
gdb InfinityWar
```
gdb ```run```
output: "Type a random phrase: "

gdb ```quit```
this exits out of gdb

type the following to get all of the function names:

```objdump -d InfinityWar```
the first few lines of output:

InfinityWar:     file format elf64-x86-64


Disassembly of section .init:

00000000004004d8 <_init>:
  4004d8:	48 83 ec 08          	sub    $0x8,%rsp
  4004dc:	48 8b 05 15 0b 20 00 	mov    0x200b15(%rip),%rax        # 600ff8 <__gmon_start__>
  4004e3:	48 85 c0             	test   %rax,%rax
  4004e6:	74 05                	je     4004ed <_init+0x15>
  4004e8:	e8 83 00 00 00       	callq  400570 <.plt.got>
  4004ed:	48 83 c4 08          	add    $0x8,%rsp
  4004f1:	c3                   	retq   
...


```break main``` this sets a break point at the main function
output: Breakpoint 1 at 0x400771: file Stones.c, line 63.

gdb ```run``` you'll stop just before main
these are the first few lines of output:

Starting program: /w/home.24/cs/ugrad/.../cs33/CS33-AVENGERS-e2e5cfa7c26e74cdd23365d1ab1bf768967c7a92/InfinityWar 

Breakpoint 1, main () at Stones.c:63
63	Stones.c: No such file or directory.
Missing separate debuginfos, use: debuginfo-install glibc-2.17-260.el7_6.3.x86_64
(gdb) disassemble main
Dump of assembler code for function main:
   0x0000000000400769 <+0>:	push   %rbp
   0x000000000040076a <+1>:	mov    %rsp,%rbp
   0x000000000040076d <+4>:	sub    $0x10,%rsp
=> 0x0000000000400771 <+8>:	mov    $0x4008e0,%edi
   0x0000000000400776 <+13>:	mov    $0x0,%eax
...

gdb ```disassemble main``` this is the same as objdump, but we can use it to run on a specific function (which in this case is main)
these are the first few lines of output:

Dump of assembler code for function main:
   0x0000000000400769 <+0>:	push   %rbp
   0x000000000040076a <+1>:	mov    %rsp,%rbp
   0x000000000040076d <+4>:	sub    $0x10,%rsp
=> 0x0000000000400771 <+8>:	mov    $0x4008e0,%edi
   0x0000000000400776 <+13>:	mov    $0x0,%eax
...

```print $rdi``` %rdi holds the first parameter --> right now, there's a garbage value in %rdi
output: $1 = 1

```stepi``` this goes to the next single line of C code
output: 0x0000000000400776	63	in Stones.c

```print $rdi```
output: $2 = 4196576

```p/x $rdi``` this gets the same address number in hexadecimal form
output: $3 = 0x4008e0

```p/d 0xf``` in decimal form
output: $4 = 15

```p/c 65``` or in ASCII form
output: $5 = 65 'A'

```x/s 0x4008e0``` this gets the contents of that address and puts in in string form
output:  0x4008e0:	"Please put in the first phrase: "

0x400520 <printf@plt> --> pointer to previous string goes to printf

```x/20xb 0x4008e0``` prints hexadecimial bytes for same address
each character is a byte

gdb ```p/c 0x50``` this shows the corresponding to an address
output: $6 = 80 'P'

set another break point:
gdb ```break CapAmerica``` this becomes breakpoint 2
output: Breakpoint 2 at 0x4006fe: file Stones.c, line 40.

gdb ```continue``` allows you to keep running until you hit the next breakpoint
output:

Continuing.
Please put in the first phrase: hi

Breakpoint 2, CapAmerica (speech=0x601080 <input> "hi") at Stones.c:40
40	in Stones.c

gdb ```p $rip``` prints the %rip
output: $8 = (void (*)()) 0x4006fe <CapAmerica+12>

gdb ```x/i $rip``` print one intruction line
output: => 0x4006fe <CapAmerica+12>:	mov    -0x8(%rbp),%rax

gdb ```x/i20 $rip``` print 20 intruction lines
first few lines of output:
=> 0x4006fe <CapAmerica+12>:	mov    -0x8(%rbp),%rax
   0x400702 <CapAmerica+16>:	mov    $0x4008c8,%esi
   0x400707 <CapAmerica+21>:	mov    %rax,%rdi
   0x40070a <CapAmerica+24>:	callq  0x400550 <strcmp@plt>
   0x40070f <CapAmerica+29>:	test   %eax,%eax
   0x400711 <CapAmerica+31>:	jne    0x40071a <CapAmerica+40>
...

gdb ```x/20xb $rip```prints hexadecimial bytes for %rip
output:
0x4006fe <CapAmerica+12>:	0x48	0x8b	0x45	0xf8	0xbe	0xc8	0x08	0x40
0x400706 <CapAmerica+20>:	0x00	0x48	0x89	0xc7	0xe8	0x41	0xfe	0xff

gdb ```stepi```
output: 0x0000000000400702	40	in Stones.c
gdb ```stepi```
output: 0x0000000000400707	40	in Stones.c

gdb ```x/s 0x4008c8``` gets the phrase! you'll have to get the output for this one on your own :)

gdb ```x/20c 0x4008c8``` looks at each character's corresponding key in the entire string
note: the string always ends in a null byte at address 0








