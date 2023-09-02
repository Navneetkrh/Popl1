# Implementing FSM to detect tokens in a given program

## To run the code
Compile using:
```
g++ lexar.cpp -o lexar
```
Run normally:
```
./lexar
```
Run by redirecting input via buffer:

```
./lexar < input.in
```

## To view the final output on terminal
To view all tokens present in program:
```
cat pa_1.out
```

To view Symbol table which contains only unique tokens(keywords and identifier only):
```
cat symbol_table_1.out
```


## Methodologies
1. The code runs on `Full State Machine(FSM)` through which it identifies different tokens present inside the code.
2. `removeComments()` returns the program with removed comments.
3. Detects all type of `operators` including ++, --, +=, etc..
4. `symbol_table_1.out` contains the symbol table of keywords and identifier(distinct):
	* mainted a set to implement this mehtodology
5. Utilized `fstream` and `fopen` for file handling

## Assumptions
1. All comments being passed are `multi-lined` as well as `single lined` comments and thus no other way is possible through which comments can be passed:
	* Therefore handling of single line comment is done if the starting delimiters are `//`.
	* Done by implementing multiple if statements and handling `new line conditions`.
2. `.c code semantics` are assumed to be the input's grammar since there is no such information given about rules relating tokens.
3. `Increment` and `Decrement` operator can only be used if the precedent value is of type `int`, `Float` or `identifier`
4. Since we follow the `.c semantics`, therefore the identifiers:
	* cannot begin with `integer`, e.g. `1b` cannot a token and hence is represented with `-1`
	* can begin with `underscore(_)` or double `underscore(__)`
5. `Max size` of code is set to `5000` characters.
6. Keywords present outside of the given domain will be considered `identifier` even though we try to follow `.c semantics`
	* As all the keywords of c language are not included into the `FSM.cpp` program
	* Only the given keywords are considered as keyword tokens.
