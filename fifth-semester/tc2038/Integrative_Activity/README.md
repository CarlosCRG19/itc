# Integrative Activity #1
The current folder contains code that solves the first term project, which can be divided into three very famous problems:
* Pattern Searching
* Palindrome Detection
* Longest Common Substring

## Test Case
The contents of the files to be evaluated are the following:

* `transmission1.txt`
```
5AE14700B75E2709B548F07034B1F9954F2888E73E44C5C0D1ABA6ABCDEFFEDCBA58A514A8884281FD42A4D6606E94EF3E63EA2A0F59CEDEC9C3C94F26F641D76379035DD1896207B0FE2380EBD936A29567BE8DD776B1DBBA1AE51D24C4DA9146D88B55DE3A280A52356F356CE3CA410E8B6C10BB5056FFEFC55

09B5D82EFF567418D20FBB23C0A7A82F6C445D0B1348FC87FC0F1FDC0A68186245A6A5FB20101470CD0FDA9438727190A05C6E2BCF723A0E9BA
```

It contains __a single__ palindrome: `ABCDEFFEDCBA`.

* `transmission2.txt`
```
BDB7AEF6953906C3925AE147008601CB22795F5EA6723DE5123E58C26018EDBFEDCBAABCDEF74E8B000FC47B184E9C7FB979250B862D74D5EFB19AAABFFBAAA91A2277446B99A3006B1AC1E7A305F941D30AB5064A5012CD5F6133CDC2C93FB688F781058E27A5472442300A9F0EC784AD9ABC071CE289076B40DEF056FFEFC55
```

It contains __a pair__ palindromes: `FEDCBAABCDEF` and `19AAABFFBAAA91`.

These two files share comon substrings: `056FFEFC55` and `5AE14700`.

* `mcode1.txt`
```
9C3C94F26F641D7
```
Its content is only present in `transmission1.txt`.

* `mcode2.txt`
```
6E2BCF723A0E9BA
```
Its content is only present in `transmission1.txt`.

* `mcode3.txt`
```
941D30AB5064A50
```
Its content is only present in `transmission2.txt`.

<br/>

Knowing all of the above, the expected output is
```cpp
// Part 1 - String Matching
true
true
false
false
false
true
// Part 2 - Palindrome Detection
55 66
116 129
// Part 3 - Longest Common Substring
236 245
248 257
