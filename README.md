# 🐚 Minishell

A UNIX shell implementation that replicates bash behavior, built as part of the 42 School curriculum. This project recreates core shell functionalities including command execution, pipes, redirections, environment variable expansion, and built-in commands.

## 📋 Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Implementation Details](#implementation-details)
  - [Command List Logic](#command-list-logic)
  - [Expansions](#expansions)
  - [Pipe Handling](#pipe-handling)
  - [Redirections](#redirections)
  - [Here-Documents](#here-documents)
- [Built-in Commands](#built-in-commands)
- [Project Structure](#project-structure)

## ✨ Features

- **Interactive prompt** with command history (using readline)
- **Environment variable expansion** (`$VAR`, `$?`)
- **Quote handling** (single `'` and double `"` quotes)
- **Pipe operator** (`|`) for chaining commands
- **Input/Output redirections**:
  - `<` (input redirection)
  - `>` (output redirection)
  - `<<` (here-document)
  - `>>` (append mode)
- **Signal handling** (Ctrl+C, Ctrl+D, Ctrl+\\)
- **Built-in commands**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Exit status tracking** (`$?`)

## 🚀 Installation

### Prerequisites

- GCC compiler
- GNU Make
- readline library

```bash
# Install readline on Ubuntu/Debian
sudo apt-get install libreadline-dev

# Install readline on macOS
brew install readline
```

### Compilation

```bash
# Clone the repository
git clone https://github.com/DMendes10/Minishell minishell
cd minishell

# Compile the project
make

# The executable 'minishell' will be created
```

### Cleaning

```bash
make clean   # Remove object files
make fclean  # Remove object files and executable
make re      # Rebuild everything
```

## 💻 Usage

### Launching the Shell

```bash
./minishell
```

You'll be greeted with the prompt:
```
@Minishell>
```

### Example Commands

```bash
# Basic commands
@Minishell> ls -la
@Minishell> echo "Hello, World!"

# Environment variables
@Minishell> echo $HOME
@Minishell> export MY_VAR="test"
@Minishell> echo $MY_VAR

# Pipes
@Minishell> ls -l | grep minishell | wc -l

# Redirections
@Minishell> echo "test" > file.txt
@Minishell> cat < file.txt
@Minishell> cat file.txt >> output.txt

# Here-documents
@Minishell> cat << EOF
> Hello
> World
> EOF

# Exit status
@Minishell> ls nonexistent
@Minishell> echo $?
```

## 🔧 Implementation Details

### Command List Logic

The shell uses a **linked list structure** (`t_cmdlist`) to organize and execute commands separated by pipes:

```c
typedef struct s_cmdlist
{
    char                **command;   // Command and arguments
    char                **input;     // Input redirections
    char                **output;    // Output redirections
    struct s_cmdlist    *next;       // Next command in pipe chain
} t_cmdlist;
```

#### Parsing Flow

1. **Lexer** (`lexer.c`): Tokenizes input, inserting separators around operators (`|`, `<`, `>`)
2. **Parser** (`parse.c`): Creates command nodes, each representing one command in a pipe sequence
3. **Command Separation**: When a pipe (`|`) is encountered, a new `t_cmdlist` node is created and linked

**Example:**
```bash
ls -la | grep minishell | wc -l
```

Creates three linked nodes:
```
[ls -la] -> [grep minishell] -> [wc -l] -> NULL
```

Each node contains:
- Command array: `["ls", "-la", NULL]`
- Input/output redirection arrays (if any)
- Pointer to next command in chain

### Expansions

Variable expansion occurs in three phases:

#### 1. Variable Detection (`expansion.c`)
```c
char *get_varkey(char *s)
```
- Scans for `$` symbols (respecting quote context)
- Extracts variable names following `$`
- Handles special case `$?` (exit status)

#### 2. Variable Resolution
```c
void search_and_replace(char **s, char *key, t_master *master)
```
- Searches environment list for matching variable
- For `$?`, converts exit code to string
- Preserves variables inside single quotes (`'`)

#### 3. Quote Processing (`rem_quotes.c`)
- Removes quotes after expansion
- Handles empty expansions
- Splits expanded strings on whitespace (unless quoted)

**Expansion Rules:**
- `$VAR` → Expands to value of VAR
- `$?` → Expands to last exit status
- `'$VAR'` → No expansion (literal)
- `"$VAR"` → Expands inside double quotes

### Pipe Handling

The pipe mechanism creates a chain of processes with connected file descriptors:

#### Process Flow (`executor_utils.c`)

```c
void executor(t_master *mstr, int cmd_count)
```

For each command in the pipe chain:

1. **Create Pipe**: `pipe(pipefd)` creates read/write file descriptors
2. **Fork Process**: Each command runs in a separate child process
3. **Redirect I/O**:
   - Child reads from `last_fd` (previous pipe's read end)
   - Child writes to `pipefd[1]` (current pipe's write end)
4. **Close Unused FDs**: Parent closes used descriptors
5. **Update last_fd**: Set to current pipe's read end for next command

**Visual Example:**
```
Command: cat file.txt | grep pattern | wc -l

Process 1 (cat):          Process 2 (grep):         Process 3 (wc):
stdin → file.txt          stdin ← pipe1[0]          stdin ← pipe2[0]
stdout → pipe1[1]         stdout → pipe2[1]         stdout → terminal

        pipe1            pipe2
[cat] --------→ [grep] --------→ [wc]
```

#### Special Cases

- **Built-ins in single commands**: Execute in parent process (no fork)
- **Built-ins in pipes**: Fork to maintain pipe chain integrity
- **Last command**: Doesn't create a new pipe

### Redirections

Redirections are stored as arrays in each `t_cmdlist` node and processed before command execution:

#### Input Redirections (`<`, `<<`)

```c
int input_redirect(t_master *mstr, t_cmdlist *cmd)
```

- **`< file`**: Opens file for reading, duplicates FD to stdin
- **`<< delimiter`**: Creates temporary file with here-document content
- Multiple redirections: Last one takes precedence

#### Output Redirections (`>`, `>>`)

```c
int output_redirect(t_master *mstr, t_cmdlist *cmd)
```

- **`> file`**: Opens file for writing (truncate), duplicates FD to stdout
- **`>> file`**: Opens file for writing (append mode)
- Multiple redirections: Last one takes precedence

#### Redirection Order

```c
void redir_handler(t_master *mstr, t_cmdlist *cmd)
```

1. Setup pipe connections (if in pipe chain)
2. Process input redirections (set stdin)
3. Process output redirections (set stdout)
4. Execute command with new FDs

**Example:**
```bash
# Multiple redirections - last wins
cat < input1.txt < input2.txt > output1.txt > output2.txt
# Reads from input2.txt, writes to output2.txt
```

### Here-Documents

Here-documents (`<<`) allow multi-line input until a delimiter is encountered:

#### Implementation (`here_doc.c`)

1. **Content Collection**: Read lines until delimiter
   ```c
   int hdoc_rdwr(t_master *mstr, t_cmdlist *cmd, char *del)
   ```
   - Prompts with `> `
   - Checks for delimiter match
   - Handles premature EOF (Ctrl+D)

2. **Expansion**: If delimiter is unquoted, expand variables
   ```c
   void expand_hdoc(t_master *mstr, char **redir)
   ```

3. **Execution**: File descriptor redirected to stdin

**Signal Handling:**
- Ctrl+C during heredoc: Interrupts input, returns to prompt
- Ctrl+D: Prints warning about premature EOF

**Example:**
```bash
cat << EOF
Hello $USER
Current dir: $PWD
EOF

# With quotes - no expansion
cat << 'EOF'
Hello $USER
EOF
```

## 🔨 Built-in Commands

| Command | Description | Implementation |
|---------|-------------|----------------|
| `echo [-n] [text]` | Print text to stdout | Supports `-n` flag (no newline) |
| `cd [path]` | Change directory | Updates PWD/OLDPWD env vars |
| `pwd` | Print working directory | Displays current directory |
| `export [VAR=value]` | Set environment variable | Creates/modifies env variables |
| `unset [VAR]` | Remove environment variable | Deletes from env list |
| `env` | Display environment | Prints all env variables |
| `exit [n]` | Exit shell | Optional numeric exit code |

### Built-in Execution Logic

- **Single command**: Executed in parent process (no fork)
- **In pipeline**: Executed in child process to maintain pipe chain

## 🎯 Project Grade

This project is part of the 42 School common core curriculum. Successfully implementing all features and passing evaluations demonstrates proficiency in:
- Process management (fork, exec, wait)
- File descriptor manipulation
- Signal handling
- Memory management
- String parsing and manipulation
- Data structure design
- FINAL GRADE : 101/100 (1 Bonus Point)
---

**Made with a lot of coffee by [ DMendes10](https://github.com/DMendes10) and [Maiathe-b](https://github.com/Maiathe-b)**
