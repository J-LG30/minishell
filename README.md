# Minishell

A functioning Unix shell for Linux and Mac with features such as pipes, variable expansions, I/O redirections, and more.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

What things you need to install the software and how to install them

```
Give examples
```

### Installing

A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
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

