# sudoku_base

`sudoku_base` is a piece of code that solves Sudoku puzzles. As the name suggests, `sudoku_base` is the backend for solving these puzzles, and is not meant to serve as a frontend.

### Simple Solver

`sudoku_base` includes a sample program called `sudoku` which solves arbitrary puzzles. `sudoku` is a command line tool that uses the code contained within `sudoku_base`. To solve puzzles over the command line, you can do something like this.

    $ cat data8-hard-inkala.txt
    8 ? ? ? ? ? ? ? ?
    ? ? 3 6 ? ? ? ? ?
    ? 7 ? ? 9 ? 2 ? ?
    ? 5 ? ? ? 7 ? ? ?
    ? ? ? ? 4 5 7 ? ?
    ? ? ? 1 ? ? ? 3 ?
    ? ? 1 ? ? ? ? 6 8
    ? ? 8 5 ? ? ? 1 ?
    ? 9 ? ? ? ? 4 ? ?
    $ ./sudoku &amp;lt; data8-hard-inkala.txt
    Read the board in OK.
    Here's the current state of the board.
    8 ? ? ? ? ? ? ? ?
    ? ? 3 6 ? ? ? ? ?
    ? 7 ? ? 9 ? 2 ? ?
    ? 5 ? ? ? 7 ? ? ?
    ? ? ? ? 4 5 7 ? ?
    ? ? ? 1 ? ? ? 3 ?
    ? ? 1 ? ? ? ? 6 8
    ? ? 8 5 ? ? ? 1 ?
    ? 9 ? ? ? ? 4 ? ?
    Solving the puzzle...
    A solution was found!
    8 1 2 7 5 3 6 4 9
    9 4 3 6 8 2 1 7 5
    6 7 5 4 9 1 2 8 3
    1 5 4 2 3 7 8 9 6
    3 6 9 8 4 5 7 2 1
    2 8 7 1 6 9 5 3 4
    5 2 1 9 7 4 3 6 8
    4 3 8 5 2 6 9 1 7
    7 9 6 3 1 8 4 5 2

This is solving [one of the world's hardest Sudoku puzzles](http://www.mirror.co.uk/news/weird-news/worlds-hardest-sudoku-can-you-242294\. in a couple dozen milliseconds.

### Web Solver

You can also solve Sudoku puzzles online using a web app I created. It is built on top of Ruby on Rails and `sudoku_base`. I actually wrote a Ruby Gem that makes use of the code in `sudoku_base`, so if you want to make your own puzzle solver in Ruby, that's fine too.
