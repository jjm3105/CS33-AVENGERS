# CS33-AVENGERS

Stop the mad titan Thanos and save the world!  
  
In a linux environment, within the directory containing InfinityWar, please make sure to run the command:  
```
chmod +x InfinityWar
```
to enable write permissions for the executable.

## Starting gdb

In the directory where `InfinityWar` is contained, type:
```
gdb InfinityWar
```
This will start running gdb so we can start running gdb commands! The following steps will go through an example of commands you can use to solve the first phase of InfinityWar. Only type in the commands that come after "gdb".

```
(gdb) run
Starting program: /w/home.01/cs/ugrad/kristiel/InfinityWar 
Please put in the first phrase: 
```
The program is running.

```
(gdb) quit
```
This exits out of gdb.

## objdump

We use gdb to stop our program at certain points with breakpoints. We can either break on an address or a function name. To find names of functions we can break on, print out the disassembled version of the program with the following command (do this in your terminal and not in gdb):

```
objdump -d InfinityWar
```
The first few lines of output:
```
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
```

If we inspect the output of `objdump`, we will see many function names enclosed in angle brackets <> Take particular note of <main> which is the first function that is run. 

## Breakpoints

Start up gdb again with `gdb InfinityWar`.

```
(gdb) break main
Breakpoint 1 at 0x400771: file Stones.c, line 63.
``` 
This sets a break point at the main function


```
(gdb) run
Starting program: /w/home.24/cs/ugrad/.../cs33/CS33-AVENGERS-e2e5cfa7c26e74cdd23365d1ab1bf768967c7a92/InfinityWar 

Breakpoint 1, main () at Stones.c:63
63	Stones.c: No such file or directory.
Missing separate debuginfos, use: debuginfo-install glibc-2.17-260.el7_6.3.x86_64
``` 
You'll stop execution just before main. If you see the "Stones.c:..." error, just ignore it. It comes up because you don't have the source file. If you want to see what instructions are in main, you can use the disassemble command.

```
(gdb) disassemble main
Dump of assembler code for function main:
   0x0000000000400769 <+0>:	push   %rbp
   0x000000000040076a <+1>:	mov    %rsp,%rbp
   0x000000000040076d <+4>:	sub    $0x10,%rsp
=> 0x0000000000400771 <+8>:	mov    $0x4008e0,%edi
   0x0000000000400776 <+13>:	mov    $0x0,%eax
...
```

This is the same output as objdump, but we can use it to run on a specific function (which in this case is main) and it also calculates offsets for you.

The arrow on the left tells you which instruction you are about to run. 

## Printing the value of registers
```
(gdb) print $rdi
``` 
Note the dollar sign before the register. This will print out what's inside rdi. Recall that rdi is the register that contains the first parameter, so it is particularly useful to print its value right before calling another function. Since the value inside rdi is 1, the output will be:
```
$1 = 1
```

```
(gdb) stepi
``` 
This runs the current assembly instruction. The output gives you the address of the following assembly instruction. Since we were previously at address `0x000000000040076d`, the output is:
```
0x0000000000400776	63	in Stones.c
```
Notice that `0x0000000000400771 <+8>:	mov    $0x4008e0,%edi` has been run, which moved a new value into rdi. Let's print that value:
```
(gdb) print $rdi
$2 = 4196576
```
This doesn't look like the value `$0x4008e0` that was moved into rdi, so what is going on? We didn't specify the print format, so the default was in decimal. To set the format to hexadecimal, we add "/x" to the print command. Also note that the print command can be shortened to p. 
```
(gdb) p/x $rdi
$3 = 0x4008e0
```
x is not the only formatting character. Some other useful ones are d and c, which print in decimal and character format. For a full list of format characters, see [here](https://sourceware.org/gdb/onlinedocs/gdb/Output-Formats.html#Output-Formats).
```
(gdb) p/d 0xf
$4 = 15
```

```
(gdb) p/c 65
$5 = 65 'A'
```

## Examining the contents of memory
We will also want to look at the contents of memory addresses. These might be in the form of literals you see in the assembly instructions or values stored in registers. If we notice in the main function:
```
Dump of assembler code for function main:
   0x0000000000400769 <+0>:	push   %rbp
   0x000000000040076a <+1>:	mov    %rsp,%rbp
   0x000000000040076d <+4>:	sub    $0x10,%rsp
=> 0x0000000000400771 <+8>:	mov    $0x4008e0,%edi
   0x0000000000400776 <+13>:	mov    $0x0,%eax
   0x000000000040077b <+18>:	callq  0x400520 <printf@plt>
...
```
The address `$0x4008e0` is moved to rdi right before the function printf. If we take a look at the documentation for printf [here](http://www.cplusplus.com/reference/cstdio/printf/), we will notice that printf takes in a char pointer as its first parameter. The bomb lab will also use many standard C functions, so if you find something unfamiliar, you should definitely check out the documentation. Since printf takes in a char pointer, we can assume that `0x4008e0` points to a C string in memory. To examine memory, we use the gdb x command. Like p, you can also specify the format after the slash. In this case, we will use the s format, which stands for string.
```
(gdb) x/s 0x4008e0
0x4008e0:	"Please put in the first phrase: "
```
Oh! So what we're passing into printf is the prompt string for the first phase. That makes sense for the first thing to run in main. The following is a demonstration of other formats for the x command

```
(gdb) x/20xb 0x4008e0
0x4008e0:	0x50	0x6c	0x65	0x61	0x73	0x65	0x20	0x70
0x4008e8:	0x75	0x74	0x20	0x69	0x6e	0x20	0x74	0x68
0x4008f0:	0x65	0x20	0x66	0x69
``` 
20xb means to print 20 bytes in hexadecimal. 

Notice that this is the exact same data that was shown previously for `0x4008e0`, just in hexadecimal format instead of string format. To double check that it's the same, let's print out the first hexadecimal byte as a character:
```
(gdb) p/c 0x50
$6 = 80 'P'
```
Sure enough, this matches the first letter in the string (capital P in Please).

## Continue
Let's move on to the first phase in main by breaking at the CapAmerica function. 
```
(gdb) break CapAmerica
Breakpoint 2 at 0x4006fe: file Stones.c, line 40
```
Note that if we want to delete a breakpoint, we can use the delete command with the number of the breakpoint
```
(gdb) delete 1
```
To continue running until you hit the next breakpoint:
```
(gdb) continue
Continuing.
Please put in the first phrase: hi
Breakpoint 2, CapAmerica (speech=0x601080 <input> "hi") at Stones.c:40
40	in Stones.c
```
Enter a random phrase when the program prompts you. Running the program in gdb is just as if you ran the program in your terminal (meaning that the bomb can explode). 

## Viewing upcoming instructions
Now we've stopped at the beginning of the CapAmerica function. We could use the `disas` command to get the instructions for this function, but we'll also teach you a second way. Recall that rip is the register that contains the instruction pointer. That means the address of the current instruction is stored in this register. Let's print it out.
```
(gdb) p $rip
$8 = (void (*)()) 0x4006fe <CapAmerica+12>
```
Like any other contents in memory, we can look at it with the x command. The particularly useful format to use here is i, which interprets bytes as instructions.
```
(gdb) x/i $rip
=> 0x4006fe <CapAmerica+12>:	mov    -0x8(%rbp),%rax
```
To print more than one upcoming instruction, add a number:
```
(gdb) x/6i $rip
=> 0x4006fe <CapAmerica+12>:	mov    -0x8(%rbp),%rax
   0x400702 <CapAmerica+16>:	mov    $0x4008c8,%esi
   0x400707 <CapAmerica+21>:	mov    %rax,%rdi
   0x40070a <CapAmerica+24>:	callq  0x400550 <strcmp@plt>
   0x40070f <CapAmerica+29>:	test   %eax,%eax
   0x400711 <CapAmerica+31>:	jne    0x40071a <CapAmerica+40>
``` 
## Solving the first phase
Recall that [strcmp](http://www.cplusplus.com/reference/cstring/strcmp/) is a C function that takes in two char pointers and returns 0 if they are equal. Also recall that rdi is the register of the first parameter and rsi is the register of the second parameter. Notice in the assembly instructions of CapAmerica that `$0x4008c8` and some register value (presumably the user input) are moved into rsi and rdi. We can deduce that the function is trying to compare the two strings to see if they're equal. Let's check out what the string stored in `$0x4008c8` is!

```
(gdb) x/s 0x4008c8
```

And that's the phrase that solves the first phase! Now try the second one on your own or start the bomb lab! If you're really stuck, check out the Spoilers folder in this repo for the source code (you won't get the source code in the bomb lab though). Good luck!
