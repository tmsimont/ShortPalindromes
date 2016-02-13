# ShortPalindromes with dynamic programming

This is a solution to a top coder problem called [ShortPalindromes](https://arena.topcoder.com/#/u/practiceCode/1292/1736/1861/2/1292).

I used an approach similar to the [Levenshtein distance](http://www.trevorsimonton.com/projects/cs/depth-articles/2015/12/06/dynamic-programming-levenshtien-distance.html) calculation.

## The problem
The goal of this problem is to figure out how to transform any string into a palindrome. The trick is that you can insert characters anywhere into the string.

The combinatorics introduced by allowing insertion of characters anywhere in the string are explosive.

My solution uses a chart to describe insert/match actions as two pointers move from one end of the input string to another. This is like the chart used for Levenshtein distance, but instead of two different strings, we use one forward version and one backward version of the same string. The tricky part is that they meet along the main diagonal, so we don't have just one solution in the bottom right, we have many solutions along the diagonal. Finding the minimum score along the diagonal, however, is trivial.

## Running the program
The first argument to pass into the program is the string you want to turn into a palindrome. 

You can choose to output the entire chart by entering a second argument.

For example:
```
./dp amnplnacanalpanama 1
   0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18
   1    0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17
   2    1    0    1    1    2    2    3    4    4    5    5    6    6    7    8    9   10
   3    2    1    0    1    2    3    4    5    5    6    6    7    7    8    9   10
   4    3    2    1    2    1    2    3    4    5    5    6    7    8    7    8
   5    4    3    2    3    2    3    2    3    4    5    6    7    8    8
   6    5    4    3    4    3    4    3    2    3    4    5    6    7
   7    6    5    4    5    4    5    4    3    4    3    4    5
   8    7    6    5    4    5    4    5    4    3    4   *3
   9    8    7    6    5    6    5    6    5    4    5
  10    9    8    7    6    7    6    7    6    5
  11   10    9    8    7    6    7    8    7
  12   11   10    9    8    7    6    7
  13   12   11   10    9    8    7
  14   13   12   11   10    9
  15   14   13   12   11
  16   15   14   13
  17   16   15
  18   17
ins a before frnt
ins a before frnt
ins a before frnt
amanaplanacanalpanama
```

I plan to write up a blog post on my approach for the curious :)
