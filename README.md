# clox

Compiler for the lox language. C implementation of *[Crafting Interpreters]* by
Robert Nystrom.

[Crafting Interpreters]: https://craftinginterpreters.com

## Build & run

```console
$ cmake --workflow --preset default
$ build/clox example/hello.lox
```

## clox compiler

`clox` is a single-pass compiler for the lox language written in C. It
internally compiles lox to bytecode that is interpreted by a stack virtual
machine (VM). Right now the compiled bytecode is not exportable.

Here are some nice internal features:
* clox uses a mark-sweep garbage collector (GC). Accessible objects are recursively
  descended and marked as used. Then the GC frees all unused objects.
* All strings are interned. The VM stores only one immutable copy of every
  string and all string usages reference those. It provides memory efficiency
  and fast string comparison. Unused strings are freed by the garbage collector.
* Closures reference non-local variables with upvalues, ie. references on their
  stack location. If stack is poped, upvalues fetch and locally store (*close*)
  their referenced variable.

## Lox language

[Lox] is a toy language designed by *Robert Nystrom* for its *Crafting
Interpreters* book. It is high level, dynamically typed, automatic memory
managed, object oriented.

[Lox]: https://craftinginterpreters.com/the-lox-language.html

### Hello World
```
// First example
print "Hello World";
```

### Dynamic typing
```
var name = "Bob";
var greetings = "Hi";

print greetings + " " + name;
```

### Functions & control flow
```
fun factorial(n) {
    var res = 1;
    for (var i = 2; i <= n; i = i+1) {
        res = res * i;
    }
    return res;
}

fun factorial_rec(n) {
    if (n < 2) {
        return 1;
    } else {
        return factorial_rec(n-1) * n;
    }
}

print factorial(6);
print factorial_rec(7);
```

### Closures
```
fun log(prefix) {
    fun pprint(message) {
        print "[" + prefix + "] " + message;
    }
    return pprint;
}

var debug = log("+");
debug("Start exec");  // [+] Start exec
```


### Classes and Inheritance
```
class Rect {
    init(x, y) {
        this.x = x;
        this.y = y;
    }
    area() { return this.x * this.y; }
    str() { return "Rectangle"; }
}

class ColoredRect < Rect {
    init(x, y, color) {
        super.init(x, y);
        this.color = color;
    }
    str() { return super.str() + " in " + this.color; }
}

var r = ColoredRect(3, 4, "yellow");
print r.area();  // 12
print r.str();  // Rectangle in yellow
```
