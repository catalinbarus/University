Student: Barus Catalin-Stefan
Group: 321 CD

***** AA Homework 2 *****

Disclaimer: If you see spacing issues, open the readme in Sublime Text or 
equivalent program.


**** Task 1 ****

The first matter that arose was identifying what was the initial problem that
is supposed to be reduced to the SAT form. We do know that multiple families
can have multiple good relationships with other families, so immeadiately we can
tell that this can be traditionally represented using a graph, where each 
vertex is a familiy and the edges represent all the relationships. With figuring
the main implementation out of the way, what comes next is the spy restriction.
We do know from the given information that no close families can have the same
spy, in other words, each adjecent vertex must have a different spy. This is
ultimateley the k Coloring problem, where instead of colours, we have spies.
Next, comes figuring out how to represent this problem in a SAT format. I began
by assigning k variables for each node, so for instance, if we have a total of 3
spies, each node would have 3 variables. Let us give the first vertex the
variables 1, 2, 3. Naturally, the second vertex would have the variables 4, 5, 
and 6, and so on. After establishing the variables, we need to determine the
right clauses to give to the oracle. Based on the information given and the
applied restrictions we do know that: one node can only have one spy, so for
instance node 1, can either have spy number 1, 2 or 3; then we can enhance this
restriction even further, by grouping all possible combinations of 2 spies for
each node, node 1 can either have spy 1 or 2, spy 1 or 3, or, spy 2 or 3, and
no more than that; additionally, we do know that two adjacent vertexes cannot
have the same spy, so that must mean it has an unique set of variables as well.
Assuming again, that vertex 1 and vertex 2 are adjacent, that would mean that a
possible clause would be that we could either have -1 or -4, -2 or -5, or, -3 or
-6. Based on these clauses written in the cnf files, the oracle can give us the
desired answer. The way to decipher it this way is pretty intuitive as well, 
for each set of k variables for each vertex, the index of the one variable that
is positive from that set, gives us the right spy for that family. So for
instance, if for the first family we got a result similar to this: -1 -2 3, it
would mean that the first family can be infiltrated by spy number 3, and so on
for all the remaining families.

Complexity wise, the algorithm may take a few seconds longer for larger tests,
since the way I computed the function that writes in the cnf files takes as much
as 3 nested loops, so at a worst case scenario we can deal with cubic complexity
speeds.

**** Task 2 ****

The problem this time requires, for the same general idea of having to represent
the families as a graph, to determine one extended family. From the information
given in the text of the homework, one extended family is a set of k families
where each family gets along with the others. In computer science terms, this
problem does esentially sound like the clique problem. In order to reduce it to
a SAT form we will begin from the same premises as the previous task, so the way
variables are distributed is the same with the exception that now they are
supposed the show the index of a family inside of a clique. This time around,
the main restrictions to be found in the clauses were already provided for the
most part by the hinted pergament given to us. We do know, based on the
pergament, that each vertex inside of a clique of size k, can be the i-th vertex
in that clique, where i = 1:k. So for a clique of 3 vertxes, we would either
have variables 1 or 4 or 7, variables 2 or 5 or 8, or variavles 3 or 6 or 9; we
now know that each vertex in the clique is unique, so that means one vertex can
have one variable, so for vertex 1 for instance we would again have all possible
combinations of 2 variables just like in the previous task; naturally, all 
vertexes in a clique are adjacent, so for each adjacent vertex, we can have an
unique variable as well, so if vertex 1 and 2 were adjacent we would have these
clasues, either -1 or -4, -2 or -5, or -3 or -6; we can also apply a restriction
for vertexes that are not adjacent, if we were to have vertexes 1 and 2 non 
adjacent for instance, then we would have clauses similar to these ones: 
-1 or -4, -1 or -5, -1 or -6, -2 or -4, -2 or -5, -2 or -6, -3 or -4, -3 or -5, 
-3 or -6.

Complexity wise, again, the code may take a bit longer for large tests, since
at worst we could experience cubic complexity speeds.
