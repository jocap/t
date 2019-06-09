T(1) - General Commands Manual

### NAME

**t** - open another terminal in same directory

### SYNOPSIS

**t**
\[*command&nbsp;...*]

### DESCRIPTION

**t**
opens another terminal in the same directory as the currently focused
terminal window.

It relies on baskerville's
**xtitle**
tool to fetch the title of the current terminal window.
This string should consist of the current path.
In my
`.kshrc`,
I achieve this using the following code:

	PS1=$PS1'\[\e]2;$PWD\a\]' # set title to pwd on every prompt

If
**t**
detects that the title string is an existant directory, it opens a
terminal in that directory.
If it is a file, it opens the terminal in the dirname of that file.

If the path does not exist, the terminal is opened in the user's home
directory.

### PARAMETERS

\[*command ...*]

> a command for the launched terminal to run

### CUSTOMIZATION

By default,
**t**
runs
urxvtc(1).
To change this, edit the C source.

### AUTHOR

John Ankarstr&#246;m &lt;[john@ankarstrom.se](mailto:john@ankarstrom.se)&gt;

OpenBSD 6.4 - June 9, 2019
