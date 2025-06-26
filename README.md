# A Unix shell written in C
**Note**: *This project is under construction. It lacks a lot of basic functionalities that you might expect from a shell like `bash` or `zsh`.*

# How to use:
**Note**: *This shell is only tested on Linux as of now. It may or may not work on MacOs. It doesn't work on Windows at all.*

- Firstly, clone the repo:
```shell
git clone https://github.com/raghav-4002/unix-shell.git ~/unix-shell/
cd ~/unix-shell
```
- Make sure that you have [GCC](https://gcc.gnu.org/) installed in your system.
- If you also have [GNU Make](https://www.gnu.org/software/make/) installed, run the command:
```shell
make
```
- Otherwise, you have to manually compile it using:
```
gcc -Iinclude src/*.c -o shell
```
- You can run the shell using:
```bash
./shell
```
- To exit, just run `exit`.


# Features:
- Handles all external executables, like `ls`, `pwd`, `man`, etc.
- Supported built-in commands:
    - `cd`: Change current working directory (not completed yet).
    - `exit`: Exits the current shell session.
    - `exec`: Execute an external program.
    - `help`: Display available built-ins (not completed yet).
- Displays the username of the current logged in user and machine name.
- Displays the current working directory.
- Can execute multiple commands separated by semicolons.

## Currently working on:
- [x] Allowing the user to edit the command before pressing enter.
- [x] Executing semi-colon separated commands.
- [ ] Advanced logical precedence using parenthesis.
- [ ] Adding support for Pipelining.
- [ ] Adding IO redirection.
- [ ] Job control.
- [ ] Shell globbing and expansion.
- [ ] Tab auto-completion.
- [ ] Adding `.rc` file and history preview using arrow key and `history` command.
- [ ] Scripting capabilities.

# How it works:
- Accepts user input in raw string format.
- Tokenizes the input using lexical analysis, separating commands from operators like `&&` and `||`, into components named `elements`.
- Parses these `elements` into an *abstract syntax tree* according to the precedence of logical operators.
- Traverses the tree, executing commands.
