# **FdF**

## :speech_balloon: **About**
This project's mandatory part consists in the implementation of one pipe and overwrite redirections (input and output), while the bonus part involves the support of multiple pipes and adds the implementation of append redirections (including heredoc).

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
- Executes the pipe between the commands, with use of pipe() and fork() functions
- Redirects input from the file given as first argument
- Redirects output to the file given as last argument
```

## :link: **Compilation**
To compile the program you should run `make`.
This rule will generate an executable file named `pipex`.

## :: Execution

To launch the executable you should follow this syntax:

```sh
$ ./pipex infile cmd1 cmd2 outfile
```
<td><image src="img/mandatory.png"></td>

# Bonus Part

## 💎 **Features**
```
- Executes the commands given as arguments, with the use of execve() function
- Executes the pipe between the commands, with use of pipe() and fork() functions
- Redirects input from the file given as first argument
- Redirects output to the file given as last argument
```

## :link: **Compilation**
To compile the program you should run `make bonus`.
This rule will generate an executable file named `bonus`.

## :: Execution

To launch the executable you should follow this syntax:

```sh
$ ./bonus infile cmd1 cmd2 cmd3 ... outfile
```
<td><image src="img/bonus.png"></td>
