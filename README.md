# **Pipex**

## :speech_balloon: **About**
This project's mandatory part consists in the implementation of one pipe and overwrite redirections, while the bonus part involves the support of multiple pipes and adds the implementation of append redirections.

## 🙋‍♀️ **Authorship**
- [Rita Marques](https://github.com/rimarque)

## :inbox_tray: **Cloning the repository**

```shell
git clone git@github.com:rimarque/FDF.git 
```

# Mandatory Part

## 💎 **Features**
```
- Executes the commands given as arguments, with the use of execve() function
- Executes a pipe between the commands, with use of pipe() and fork() functions
- Supports overwrite rederections:
  - redirects input from the file given as first argument
  - redirects output to the file given as last argument
```

## :link: **Compilation**
To compile the program you should run `make`.
This rule will generate an executable file named `pipex`.

## :pencil2: Execution

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

## :pencil2: Execution

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
