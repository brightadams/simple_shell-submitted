#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define END_OF_FILE -2
#define EXIT -3


int hist;

extern char **environ;

char *name;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory pathName.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
        char *dir;
        struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command'string_chars function.
 */
typedef struct builtin_s
{
        char *name;
        int (*f)(char **argv, char **head);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
        char *value;
        char *name;
        struct alias_s *next;
} alias_t;


alias_t *aliases;


list_t *get_dir_path(char *pathName);
int execute(char **args, char **head);
void free_list(list_t *head);
char *stringify(int numb);
ssize_t line_getter(char **linePtr, size_t *n, FILE *stream);
void *re_allocate(void *pointer, unsigned int size_of_old_line, unsigned int new_size);
char **_strtok(char *line_read, char *deli);
char *command_path(char *command);


int _args_handler(int *exe_ret);
int args_checker(char **args);
void remove_args_from_memory(char **args, char **head);
char **replace_aliases(char **args);
void _line_input(char **line_read, ssize_t read);
void variable_replacement(char **args, int *exe_ret);
int exec_args(char **args, char **head, int *exe_ret);
char *_args_get(char *line_read, int *exe_ret);
int _args_call(char **args, char **head, int *exe_ret);


char *_find_char(char *string_chars, char c);
int _string_prefix_len(char *string_chars, char *accept);
int compare_string(char *string1_pointer, char *string2_pointer);
int compare_n_string(const char *string1_pointer, const char *string2_pointer, size_t n);
char *_copy_string(char *string_destination, const char *string_source);
int _str_len(const char *string_chars);
char *_string_concat(char *string_destination, const char *string_source);
char *_string_n_concat(char *string_destination, const char *string_source, size_t n);


int (*get_builtin(char *command))(char **args, char **head);
int shellby_cd(char **args, char __attribute__((__unused__)) **head);
int alias_for_shellby(char **args, char __attribute__((__unused__)) **head);
int shellby_help(char **args, char __attribute__((__unused__)) **head);
int _modify_env(char **args, char __attribute__((__unused__)) **head);
int _remove_env(char **args, char __attribute__((__unused__)) **head);
int shellby_exit(char **args, char **head);
int _curr_env(char **args, char __attribute__((__unused__)) **head);


int alias_for_shellby(char **args, char __attribute__((__unused__)) **head);
void set_alias_value(char *variable_name, char *value);
void display_alias(alias_t *alias);


void _line_input(char **line_read, ssize_t read);
ssize_t _new_line(char *line_read);
void _operators_logical(char *line_read, ssize_t *n_length);



char **_env_get(const char *varia);
void _env_free(void);
char **dup_env(void);


char *error_syntax(char **args);
char *_perm_errors(char **args);
char *not_found_errors(char **args);
int error_creator(char **args, int err);
char *shellby_error_env(char **args);
char *error_for_alias(char **args);
char *exit_errors(char **args);
char *cd_errors(char **args);




alias_t *append_alias(alias_t **head, char *name, char *value);
list_t *node_append(list_t **head, char *dir);
void free_alias(alias_t *head);
void free_list(list_t *head);

void _env_help(void);
void _setenv_help(void);
void _unsetenv_helper(void);
void help_history(void);
void show_all_commands(void);
void show_help_alias(void);
void show_help_cd(void);
void exit_help(void);
void help_helper(void);

int file_executor(char *file_path, int *exe_ret);

#endif 
