# 写一个 SAT solver🎑

代码里面使用了 DPLL，tseitin 变化。用来判断输入是否 satisfiable。

# 如何使用？🎨

```
cd build
cmake ..
make
./satsolver
```

你可以将以下代码进行输入

```
a123

a+c
a*---a
a+b;a:0,b:1
 ( (-a)+(a*b)) * a * (c + -b) *-c
(a+b+c)*(a+b+-c)*(-b+a +c)*(-a*-c)
(a+b+c)*(a+b+-c)*(-b+a +c)*(a+-b+-c)*(-a+b+c)*(-a+b+-c)*(-a+-b+c)*(-a+-c+-c)
(a+b+c)*(a+b+-c)*(-b+a +c)*(a+-b+-c)*(-a+b+c)*(-a+b+-c)*(-a+-b+c)*(-a+-c+-b)
(a+b+c)*(a+b+-c)*(-b+a +c)*(a+-b+-c)*(-a+b+c)*(-a+b+-c)*(-a+-b+c)

```

将会返回这些代码是否 satisfiable。

```
sat
Error: invalid input
sat
unsat
Error: invalid input
unsat
unsat
unsat
unsat
sat

```
