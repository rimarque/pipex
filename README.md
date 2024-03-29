# **Pipex**

## :speech_balloon: **About**
The mandatory part of this project involves using processes to implement a single pipe for chaining the commands provided as arguments, while also supporting overwrite redirections. The bonus part includes the execution of multiple pipes and implementation of append redirections.

## 🙋‍♀️ **Authorship**
- [Rita Marques](https://github.com/rimarque)

## :inbox_tray: **Cloning the repository**

```shell
git clone git@github.com:rimarque/FDF.git 
```

# Mandatory Part

## 💎 **Features**
```
- Executes the commands given as arguments, with the use of execve() and fork() functions
- Executes a pipe between the commands, with use of pipe()
- Supports overwrite redirections:
  - redirects input from the file given as first argument
  - redirects output to the file given as last argument
```

## :link: **Compilation**
To compile the program you should run `make`.
This rule will generate an executable file named `pipex`.

## :gun: Execution

To launch the executable you should follow this syntax:

```sh
$ ./pipex infile cmd1 cmd2 outfile
```
<td><image src="img/mandatory.png"></td>

# Bonus Part

## 💎 **Features**
```
- Supports multiple pipes, enabling users to chain multiple commands together
- Supports overwrite and append rederections (including heredoc)
```

## :link: **Compilation**
To compile the program you should run `make bonus`.
This rule will generate an executable file named `bonus`.

## 🔫 Execution

To launch the executable you should follow this syntax:

Executes overwrite redirections:

```sh
$ ./bonus infile cmd1 cmd2 cmd3 ... cmdn outfile
```
<td><image src="img/bonus_overwrite.png"></td>

Executes append redirections:

```sh
$ ./bonus here_doc LIMITER cmd1 cmd2 cmd3 ... cmdn outfile
```
<td><image src="img/bonus_append.png"></td>
