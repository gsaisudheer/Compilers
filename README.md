# Compilers
Coursework assignment for Compilers

### Scanner and Parser for Tiny Programming Language
My implementation of  scanner and parser for the Tiny programming language. This is a simplified programming language used to learn the construction of a compiler. 
For more details on this programming language, it's constructs and usage, please refer to the book *Compiler Construction: Principles and Practice* by *Kenneth C Louden*.


Following are the steps to run this code.

```
$gcc scanner.c util.c
```

Run the executable as follows:

```
$ a.out fullSample.tny
```

The output will be produced in the `output.tny` file which will be used by the parser.

```
$ gcc parser.c util.c
``` 

Run the executable as follows:

```
$ ./a.out fullSample.tny
```

Successful compilation (of the code written in tiny language) is indicated by the program producing 0 errors on the console.

### Lex and Yacc
You'll need `flex` and `bison` to perform this part. Once installed, run the following commands:

```
$ flex tiny.l
```

This will produce an output `lex.yy.c`

Compile the file produced using the following command to produce an executable

```
$ gcc lex.yy.c
```

To perform the scanning and to write the output to the file `scanOutput.txt`, run the following command

```
$ ./a.out sample.txt scanOutput.txt
```

To produce a C file `tiny.tab.c`, execute the following command

```
$ bison tiny.y
```
You can then use `gcc` to compile `tiny.tab.c`


