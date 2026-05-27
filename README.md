# Minishell

A minimal Unix shell implementation written in C, replicating basic features of Bash. This project is part of the Hive Helsinki / 42 curriculum and focuses on process management, signal handling, parsing, and built-in commands.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Built-in Commands](#built-in-commands)
- [Signal Handling](#signal-handling)
- [Code Structure](#code-structure)
- [Acknowledgments](#acknowledgments)

## Overview

Minishell is a custom shell that interprets and executes user commands. It supports:
- Command execution with absolute/relative paths or via `PATH`.
- Input/output redirections (`<`, `>`, `>>`).
- Pipes (`|`) to connect multiple commands.
- Heredoc (`<<`) with variable expansion and quote handling.
- Environment variable expansion (`$VAR` and `$?`).
- Signal handling (SIGINT, SIGQUIT) with interactive behaviour.
- A set of built-in commands.

The shell is written from scratch in C, using custom string utilities and dynamic arrays (vectors) to manage tokens and redirections.

## Features

- **Command parsing** – Handles quotes, escapes, and separators.
- **Redirections** – `>`, `>>`, `<`, `<<`.
- **Pipes** – Unlimited number of piped commands.
- **Environment variables** – Expand `$VAR`, `$?` (exit status of last command).
- **Heredoc** – Reads until a delimiter; supports quotes (no expansion) and variable expansion when delimiter is unquoted.
- **Signal handling** – `Ctrl+C` shows new prompt, `Ctrl+\` does nothing, `Ctrl+D` exits.
- **History** – Uses readline for line editing and history.
- **Built-in commands** – `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

## Installation

Clone the repository and compile with `make`:

```bash
git clone https://github.com/vietsusi/Minishell
cd minishell
make
```
## Run
./minishell

## Built‑ins
Command	Description
echo [-n]         Print arguments
cd [dir]	        Change directory (~, -, HOME, OLDPWD)
pwd	              Print working directory
export [VAR=val]	Set environment variable (or list all sorted)
unset [VAR]	      Remove variable
env	              Print all variables
exit [n]	        Exit shell

## Features
| pipes, < > >> redirections, << heredoc (with/without expansion)
$VAR and $? expansion
Ctrl+C → new prompt, Ctrl+\ ignored, Ctrl+D exits
Signal handling during heredoc

## Author
Made by cdohanic(https://github.com/cristichitz) and vinguyen
