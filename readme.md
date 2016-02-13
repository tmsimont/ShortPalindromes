A [complete write-up of this project](http://www.trevorsimonton.com/blog/2016/02/13/variation-of-the-edit-distance-problem.html) is available on my blog

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
./dp massaman 1
0    1    2    3    4    5    6    7    8
1    0    1    2    3    4    5    6    7
2    1    2    3    2    3    4    5
3    2    3    2    3    2   *2
4    3    4    3    4    2
5    4    5    4    5
6    5    6    5
7    6    7
8    7
ins n before frnt
ins a before frnt
namassaman
```

