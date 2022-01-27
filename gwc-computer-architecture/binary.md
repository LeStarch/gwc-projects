# Binary and Computers

Binary is a way of representing numbers. It is often used in computers. In this lesson we will explore binary and binary math.


## Decimal and Humans

In modern Math, humans typically use base 10 or decimal to represent the numbers we use. Decimal is composed of 10 digits (0-9). Numbers are expressed in the form
`C0 * 10^n + C1 * 10^(n-1) ... + CN-1 * 10^1 + CN * 10^0` or some number in the 1s place, some number in the 10s place, some number in the 100s place and so on.

Let's look at an example: 83204 (Eighty-Three Thousand Two-Hundred and Four). This number can be written as:

```
(8 * 10000) + (3 * 1000) + (2 * 100) + (0 * 10) + (4*1)
```

or 

```
(8 * 10^4) + (3 * 10^3) + 2 * 10^2 + (0 * 10^1) + (4 * 10^0) 
```

or

```
Eight Ten-Thousands and 3 Thousands and 2 Hundreds and no Tens and 4 Ones 
```

Let's try an example:  write 834923 in the expanded form we just saw!

When we do math on these numbers we must obey the rule that no digit shall be more than 9. This can be seen in the following example: 93 + 28

```
  93
+ 28
----
```

First we add `3 + 8 = 11` and since 11  is greater than 10 we must carry-over:

```
  1
  93
+ 28
----
   1
```

Next add `9 + 2 + 1 = 12` since 12 is larger than 10 we must carry-over:

```
 11
  93
+ 28
----
 121
```

And that is our answer: 121!

## Binary Representation

Binary or base 2 works the same way as decimal with the exception that it only has two digits (0, 1). This means its numbers must be represented in powers of two!
Here is an example: 101 (notice there are only 0s and 1s).  This number is:

```
(1 * 2^2) + (0 * 2^1) + (1 * 2^0)
```

or

```
(1 * 4) + (0 * 2) + (1 * 1)
```
or

```
One Four and no Twos and one One
```

Can you write the following in expanded form?  101101.


Now can you conver to binary?  What is 25 in binary notation?


**Note:** since binary can only have one or zero for each digit this can also be read "on" or "off" for each digit. Since the core building block of a computer is
a switch, "on" and "off" make a lot of sense. This is:

```
Four 'On' and Two 'Off' and One 'On
```

## Binary Addition

In order to add two binary numbers we follow the same process as we did with decimal numbers but our carry-over limit is now two and we are adding only zeros and
ones. First, lets start with the basics: `0 + 0 = 0` and `0 + 1 = 1`. The hardest addition in all of binary is next: `1 + 1 = 10`.  Did you get `2`?  Remember 
there are no `2`s in binary so we have to carry over to the next digit getting `10` or in expanded notation `(2^1 + 0)`!

Let's try an example of extended addition:

```
  101
+  11
-----
    
```

`1 + 1 = 10 (2 in decimal)` and thus we need a carry-over.

```
   1
  101
+  11
-----
    0
```

The next digit is `1 + 0 + 1 = 10 (2 in decimal)` and thus we need another carry-over.

```
  11
  101
+  11
-----
   00
```

The next digit is `1 + 1 + 0 = 10 (2 in decimal)` and thus we need yet another carry-over.


```
 111
  101
+  11
-----
  000
```

And the final digit is `1 + 0 + 0 = 1 (1 in decimal)`.  No carry-over needed.

```
 111
  101
+  11
-----
 1000
```

That is our answer `1000`. Binary has a lot of carry-overs, but is easy to add different digits.  Here, are some practice problems:

**Example 1**
```
 1111
+   1
-----
```

**Example 2**
```
 1111
+  11
-----
```

**Example 3**
```
 1011
+ 110
-----
```


**Example 4**
```
 11011011
+   10110
-----
```

## Truth Tables and Binary Logic

Here is where we see a trick that decimal cannot do: truth tables and log.  We are going to introduce some new math operators "AND", "OR", "NOT", and "XOR". Let's
start with "AND". AND means both digits musy be 1, on, or true, to result in a 1, on, or true. Otherwise the result is 0, off, or false. You can se this below:

| A | B | A AND B |
|---|---|---------|
| 0 | 0 | 0       |
| 0 | 1 | 0       |
| 1 | 0 | 0       |
| 1 | 1 | 1       |

Let us try "OR" next. "OR" means either digit 1, on, or true results in a 1, on, or true. Only when both digits are 0, off, false does this result in a 0, off, or
false.

| A | B | A OR B  |
|---|---|---------|
| 0 | 0 | 0       |
| 0 | 1 | 1       |
| 1 | 0 | 1       |
| 1 | 1 | 1       |

Let us do "NOT" next. "NOT" works on a single digit.  It changes it to the other digit. In other words, not "on" becomes "off" and not "off" becomes "on".

| A | NOT A   |
|---|---------|
| 0 | 1       |
| 1 | 0       |

Finally we look at "XOR" or exclusive or. This is equivalent to "OR" with the minor change that it returns 0, off, false, if both digits are 1, on, or true. That
is one OR the other but not both.

| A | B | A XOR B |
|---|---|---------|
| 0 | 0 | 0       |
| 0 | 1 | 1       |
| 1 | 0 | 1       |
| 1 | 1 | 0       |

**Note:** these operators are often applied digit-by-digit of a number. Let's take a look:

```
    101101
OR   10110
----------
    111111
````

```
    101101
AND  10110
----------
    000100
````

Now you try!

```
    101101
XOR  10110
----------

````











