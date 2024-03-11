
The Bash manual: (actually pretty easy to read and helpful)
https://www.gnu.org/software/bash/manual/bash.html#Single-Quotes

3.1.1 Shell Operation
The following is a brief description of the shell’s operation when it reads and executes a command. Basically, the shell does the following:

Reads its input from a file (see Shell Scripts), from a string supplied as an argument to the -c invocation option (see Invoking Bash), or from the user’s terminal.
Breaks the input into words and operators, obeying the quoting rules described in Quoting. These tokens are separated by metacharacters. Alias expansion is performed by this step (see Aliases).
Parses the tokens into simple and compound commands (see Shell Commands).
Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames (see Filename Expansion) and commands and arguments.
Performs any necessary redirections (see Redirections) and removes the redirection operators and their operands from the argument list.
Executes the command (see Executing Commands).
Optionally waits for the command to complete and collects its exit status (see Exit Status).

Above is a subsection of the manual and i think it explains really clearly how the shell should work + steps we should take!!

For how quoting works:
https://rg1-teaching.mpi-inf.mpg.de/unixffb-ss98/quoting-guide.html

this guide from a textbook on writing your own shell:
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

another guide for shell syntax kinda like bash manual:
https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html

Grammar rules:
N:B word in CAPITALS are tokens w/ that token type. Words in lower case are non-terminals and words in upper case are terminals.
expression → command
        | command PIPE expression

command → command_prefix command_word command_suffix

command_prefix -> redirectin
        | command_prefix redirectin
        | redirectout
        | command_prefix redirectout

command_suffix -> redirectin
        | command_suffix redirectin
        | redirectout
        | command_suffix redirectout

redirectin -> REDIR_IN command_word
        | REDIR_APP command_word

redirectout → REDIR_OUT command_word
        | REDIR_DELIMIT command_word

command_word -> S_STR 
        | D_STR
        | WORD

https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_03