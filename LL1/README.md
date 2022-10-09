The grammar must be seperated by commas
like this :
**
 E-> TP , P-> +TP | @ , T-> FQ,Q-> *FQ|@,F-> i|(E)
**

The actual cpp file is LLparser.cpp

hence run : g++ LLparser.cpp && ./a.out input.txt

The input.txt contains the grammar which is to be given as input.

Next it prompts to enter the string to validate if the grammar is LL1.

After entering the string, the dot file automatically generates and opens.

ex:

The Grammar is LL1 Accepted
Enter the string to check for the above Grammar

--> Entered string is ' i ' here.

g.dot is generated
and output.svg is generated and opened.
