# Minishell

A functioning Unix shell for Ubuntu and MacOS with features such as pipes, variable expansions, I/O redirections, and more.

## Getting Started

These instructions will get you a copy of the shell up and running on your machine!

### Prerequisites

To compile/use the shell, you will need the GNU readline library installed on your computer.

To check if it is already installed, copy this command into your terminal:

Ubuntu command:
```
dpkg -l | grep readline
```
MacOS command:
```
brew list readline
```
If these have an output along the line of ..../include/readline...., you should be good to go!

If not, to install readline copy this command into your terminal:

Ubuntu command:
```
sudo apt install libreadline-dev
```

MacOS command:
```
brew install readline
```

You can confirm the installation of the library by using the other commands above.

### Installing

On Ubuntu machines, you can install the shell by cloning the github repo onto your machine, entering the repo directory and using the command:

```
make
```

On MacOS, you need to modify the Makefile slightly.
Use this command to find where readline has been installed:
```
brew --prefix readline
```

Then, in the Makefile underneath the line where it says:
```
#version for macs: replace these with the paths on your machine
```

Replace it with:

```
LIB_DIR = -L/the_path_you_got/lib
LIB_INC = -I/the_path_you_got/include
```

Where the path you got is the output of brew --prefix readline.

And now you should be good to go! You can simply run:

```
make
```

Actually run the shell with the command:

```
./minishell
```

Some command ideas to test the shell:

```
echo "hello world" > testing.txt
ls | grep "a"
export HOTEL="trivago"
env
```

## Authors

* **Juliette Le Goff**
* **David Almeida**

## Acknowledgments

* Thank you to all our friends and fellow students at 42 who gave us inspiration on how to develop the shell, and helped us in thoroughly testing its functionality!


Grammar rules:
N:B word in CAPITALS are tokens w/ that token type. Words in lower case are non-terminals and words in upper case are terminals.
expression → command
        | command PIPE expression

command → redirectin command
        | redirectout command
        | command_word command

redirectin -> REDIR_IN command_word
        | REDIR_APP command_word

redirectout → REDIR_OUT command_word
        | REDIR_DELIMIT command_word

command_word -> WORD

