/* ************************************************************************** */
/* Project name: Compiler implementation for IFJ23 imperative language        */
/* File authors: xforma19 – David Formánek                                    */
/*               xchova25 – David Chovanec                                    */
/* ************************************************************************** */

#ifndef PRINTGENERATOR_H
#define PRINTGENERATOR_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void start_code();
void print_createframe ();
void print_pushframe ();
void print_popframe ();
void print_return ();
void print_clears ();
void print_adds ();
void print_subs ();
void print_muls ();
void print_divs ();
void print_idivs ();
void print_lts ();
void print_eqlits();
void print_gts ();
void print_eqgts ();
void print_eqs ();
void print_nots ();
void print_int2floats ();
void print_float2ints ();
void print_int2chars ();
void print_stri2ints ();
void defvar_lf(char *string);
void defvar_gf(char *string);
void defvar_tf(char *string);
void print_assign_lf(char *string);
void print_assign_tf(char *string);
void print_assign_gf(char *string);
void print_call (char *string);
void print_label (char *string);
void print_write (char *string);
void start_while (int numb);
void while_condition (int numb);
void end_while (int numb);
void push_int (int numb);
void push_float (float numb);
void push_bool (bool type);
void push_string (char *string);
void push_nil();
void push_var_gf(char *string);
void push_var_lf(char *string);
void push_var_tf(char *string);
void start_if (int numb);
void else_if (int numb);
void end_if (int numb);
void start_main();
void declare_func(char *string);
void value_start(int numb);
void end_value_lf(int numb, char *string);
void end_value_tf(int numb, char *string);
void end_value_gf(int numb, char *string);
void func_defvar(char *string);
void read_int();
void read_double();
void read_string();
void write();
void int2double();
void double2int();
void lenght();
void substring();
void ord();
void chr();

#endif