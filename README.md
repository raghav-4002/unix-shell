# Sea Shell - A Unix shell written in C
**Note**: *This project is under construction. It lacks a lot of basic functionalities that you might expect from a shell like `bash` or `zsh`.*

# How to use it:
**Note**: *This shell is only tested on Linux as of now. It may or may not work on MacOs. It doesn't work on Windows at all.*

- Firstly, clone the repo:
```shell
git clone https://github.com/raghav-4002/sea-shell.git ~/sea-shell/
cd ~/sea-shell
```
- Make sure that you have [GCC](https://gcc.gnu.org/) installed in your system.
- If you also have [GNU Make](https://www.gnu.org/software/make/) installed, run the command:
```shell
make
```
- Otherwise, you have to manually compile it using:
```
gcc -Iinclude src/*.c -o seash
```
- You can run the shell using:
```bash
./seash
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
- [ ] Allowing the user to edit the command before pressing enter.
- [ ] Tab auto-completion.
- [x] Executing semi-colon separated commands.
- [ ] Adding `seash_history` file and history preview using arrow key and `history` command.

## Advanced features to be added in near future:
- IO redirection.
- Pipelining.
- Shell globing.
- Job control.
- A `seashrc` file support.
- Scripting capabilities (maybe).

# How it works:
- Accepts user input.
- Tokenizes the input into tokens separated by space.
- Parses those tokens to check if it's a built-in or an executable.
- Handles basic errors like command not found and directory not found.
