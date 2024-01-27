# Noisy pipes
## WIP
NOTE: I've just started this project, so it's under construction! I'll remove
this message once things are a bit further along and I've added some polish.

## Main Idea
I've been reading through an information theory textbook, and thought it would
be nice to be able to play around with different communication channels and
error-correcting codes as follows:

```
$ cat ./data.original.txt \
    | codes/repetition encode 3 \
    | channel/binary-symmetric 0.05 \
    | codes/repetition decode 3 \
   > ./data.received.txt

$ diff $(hexdump ./data.original.txt) $(./data.received.txt)
```

in order have a convienent toolbox to experiment with error correction.

I'm interested in adding support for Unix socket proxies, for bidirrectional
communication.

Right now I'm implementing encoding, decoding, and corruption of binary data,
but to make things easier to reason about, I might include a mode where input
and output must be ASCII char's for each code and channel. The math would be
modified such that instead of base 2 opperations, corruption would be
represented as a random map of character codes 32-127 to a different ASCII code.
Having to use hexdump isn't too bad for now, though.

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
