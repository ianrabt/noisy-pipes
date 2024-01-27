# Noisy pipes
## Main Idea
I've been reading through an information theory textbook, and thought it would
be nice to be able to play around with different communication channels and
error-correcting codes as follows:

```
$ cat ./data.original.txt | encode/repeat -e 3 \
    | channel/binary-symmetric 0.05 \
    | encode/repeat -d 3 > ./data.received.txt

$ diff ./data.*.txt
```

in order have a convienent toolbox to experiment with error correction.

## Goals
- implement some different channels
- write some visualization scripts (using `hexdump`, `diff`, etc) so it is easy
  to see what errors if any have occured.
- write a tester, which measures error rate over large amounts of data (as a
  simple shell script).
- support extensions to write custom lossy communication channels and encoders
  in Guile (scheme lisp).
- maybe write an extension which acts as a (purposely poor) proxy over two Unix
  sockets, to simulate bidirectional communication -- the command line syntax
  wouldn't be quite as nice as using pipes, however.

## building
1. (optional) `bear -- make` to generate `compile_commands.json`
2. install guile and gsl (e.g. `port install guile gsl`)
3. `make all`
