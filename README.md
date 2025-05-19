# Sea Shell - A Unix shell written in C
**Note**: *This project is under construction. It lacks a lot of basic functionalities that you might expect from a shell like `bash` or `zsh`*


# Features:
- Handles all external executables, like `ls`, `pwd`, `man`, etc.
- Supported built-in commands:
    - `cd`: Change current working directory (not completed yet).
    - `exit`: Exits the current shell session.
    - `exec`: Execute an external program.
    - `help`: Display available built-ins (not completed yet).
- Displays the username of the current logged in user and machine name.
- Displays the current working directory.

## Currently working on:
- Allowing the user to edit the command before pressing enter.
- Tab auto-completion.
- Executing comma separated commands.
- Adding `seash_history` file and history preview using arrow key and `history` command.

## Advanced features to be added in near future:
- IO redirection.
- Pipelining.
- Shell globing.
- Job control.
- A `.rc` file support.
- Scripting capabilities (maybe).