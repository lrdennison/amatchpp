== Amatchpp: an improved C++ version of the amatch gem

=== Motivation

The search routines in Amatch::Sellers do not provide where the string
was found.

Sellers and Levenshtein are based upon the same dynamic programming
algorithm which produces a cost-of-edit-operation transition matrix.
Once the algorithm is run, one needs to examine the node costs and
determine which edit operations resulted in that solution.

Amatch uses a space-compressed version of the cost-of-edit-operation
matrix.  As result, the ability to backtrace and determine where the
string is found was lost.

Amatchpp retains the full matrix and provides backtrace support to
identify the start/end locations.  In addition, it constructs an edit
string which provides charcter-by-character directions on how to
transform the matched substring into the pattern.

Please see the github project wiki for more details:

https://github.com/lrdennison/amatchpp

=== Attribution
This gem is based upon the amatch-0.2.5 gem which was written by:

Florian Frank mailto:flori@ping.de

