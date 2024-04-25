/* ************************************************************************** */
/* Project name: Compiler implementation for IFJ23 imperative language        */
/* File authors: xforma19 – David Formánek                                    */
/*               xchova25 – David Chovanec                                    */
/* ************************************************************************** */

#include "printgenerator.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void start_code()
{
    printf(".IFJcode23\n");
    printf("DEFVAR GF@%%counter\n");
    printf("JUMP $$main\n");
}

void print_createframe()
{
    printf("CREATEFRAME\n");
}

void print_pushframe()
{
    printf("PUSHFRAME\n");
}

void print_popframe()
{
    printf("POPFRAME\n");
}

void print_return()
{
    printf("RETURN\n");
}

void print_clears()
{
    printf("CLEARS\n");
}

void print_adds()
{
    printf("ADDS\n");
}

void print_subs()
{
    printf("SUBS\n");
}

void print_muls()
{
    printf("MULS\n");
}

void print_divs()
{
    printf("DIVS\n");
}

void print_idivs()
{
    printf("IDIVS\n");
}

void print_lts()
{
    printf("LTS\n");
}

void print_eqlits()
{
    printf("GTS\n");
    printf("NOTS\n");
}

void print_gts()
{
    printf("GTS\n");
}

void print_eqgts()
{
    printf("LTS\n");
    printf("NOT\n");
}

void print_eqs()
{
    printf("EQS\n");
}

void print_nots()
{
    printf("EQS\n");
    printf("NOTS\n");
}

void print_int2floats()
{
    printf("INT2SLOATS\n");
}

void print_float2ints()
{
    printf("FLOAT2INTS\n");
}

void print_int2chars()
{
    printf("INT2CHARS\n");
}

void print_stri2ints()
{
    printf("STRI2INTS\n");
}

void defvar_lf(char *string)
{
    printf("DEFVAR LF@%s\n", string);
    printf("MOVE LF@%s nil@nil\n", string);
}

void defvar_gf(char *string)
{
    printf("DEFVAR GF@%s\n", string);
    printf("MOVE GF@%s nil@nil\n", string);
}

void defvar_tf(char *string)
{
    printf("DEFVAR TF@%s\n", string);
    printf("MOVE TF@%s nil@nil\n", string);
}

void print_assign_lf(char *string)
{
    printf("POPS LF@%s\n", string);
}

void print_assign_tf(char *string)
{
    printf("POPS TF@%s\n", string);
}

void print_assign_gf(char *string)
{
    printf("POPS GF@%s\n", string);
}

void print_call(char *string)
{
    printf("CALL $%s\n", string);
}

void print_label(char *string)
{
    printf("LABEL %s\n", string);
}

void print_write(char *string)
{
    printf("WRITE %s\n", string);
}

void start_while(int numb)
{
    printf("LABEL $while%d\n", numb);
}

void while_condition(int numb)
{
    printf("PUSHS bool@true\n");
    printf("JUMPIFNEQS $endloop%d\n", numb);
}

void end_while(int numb)
{
    print_popframe();
    printf("JUMP $while%d\n", numb);
    printf("LABEL $endloop%d\n", numb);
}

void push_int(int numb)
{
    printf("PUSHS int@%d\n", numb);
}
void push_float(float numb)
{
    printf("PUSHS float@%a\n", numb);
}
void push_bool(bool type)
{
    printf("PUSHS bool@%d\n", type);
}
void push_string(char *string)
{
    printf("PUSHS string@%s\n", string);
}

void push_nil()
{
    printf("PUSHS nil@nil\n");
}

void push_var_gf(char *string)
{
    printf("PUSHS GF@%s\n", string);
}

void push_var_lf(char *string)
{
    printf("PUSHS LF@%s\n", string);
}

void push_var_tf(char *string)
{
    printf("PUSHS TF@%s\n", string);
}

void start_if(int numb)
{
    printf("PUSHS bool@false\n");
    printf("JUMPIFEQS $else%d\n", numb);
}

void else_if(int numb)
{
    printf("JUMP $end_if%d\n", numb);
    printf("LABEL $else%d\n", numb);
}

void end_if(int numb)
{
    printf("LABEL $end_if%d\n", numb);
}

void start_main()
{
    printf("LABEL $$main\n");
    printf("CREATEFRAME\n");
}

void declare_func(char *string)
{
    printf("LABEL $%s\n", string);
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
}

void value_start(int numb)
{
    push_nil();
    printf("JUMPIFNEQS $truevalue%d\n", numb);
}

void end_value_lf(int numb, char *string)
{
    printf("JUMP $endvalue%d\n", numb);
    printf("LABEL $truevalue%d\n", numb);

    // printf("LABEL $endvalue%d\n", numb);
}

void end_value_tf(int numb, char *string)
{
    printf("JUMP $endvalue%d\n", numb);
    printf("LABEL $truevalue%d\n", numb);

    // printf("LABEL $endvalue%d\n", numb);
}

void end_value_gf(int numb, char *string)
{
    printf("JUMP $endvalue%d\n", numb);
    printf("LABEL $truevalue%d\n", numb);

    // printf("LABEL $endvalue%d\n", numb);
}

void func_defvar(char *string)
{
    printf("DEFVAR TF@%s\n", string);
    printf("POPS TF@%s\n", string);
}

void read_int()
{
    printf("LABEL $readInt\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("DEFVAR TF@save\n");
    printf("READ TF@save int\n");
    printf("DEFVAR TF@vartype\n");
    printf("TYPE TF@vartype TF@save\n");
    printf("JUMPIFEQ $isgood_int TF@vartype string@int\n");
    printf("MOVE TF@save nil@nil\n");
    printf("LABEL $isgood_int\n");
    printf("PUSHS TF@save\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void read_double()
{
    printf("LABEL $readDouble\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("DEFVAR TF@save\n");
    printf("READ TF@save float\n");
    printf("DEFVAR TF@vartype\n");
    printf("TYPE TF@vartype TF@save\n");
    printf("JUMPIFEQ $isgood_float TF@vartype string@float\n");
    printf("MOVE TF@save nil@nil\n");
    printf("LABEL $isgood_float\n");
    printf("PUSHS TF@save\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void read_string()
{
    printf("LABEL $readString\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("DEFVAR TF@save\n");
    printf("READ TF@save string\n");
    printf("DEFVAR TF@vartype\n");
    printf("TYPE TF@vartype TF@save\n");
    printf("JUMPIFEQ $isgood_string TF@vartype string@string\n");
    printf("MOVE TF@save nil@nil\n");
    printf("LABEL $isgood_string\n");
    printf("PUSHS TF@save\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void write()
{
    printf("LABEL $write\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("DEFVAR TF@print\n");
    printf("LABEL $write_loop\n");
    printf("JUMPIFEQ $end_write GF@%%counter int@0\n");
    printf("POPS TF@print\n");
    printf("WRITE TF@print\n");
    printf("SUB GF@%%counter GF@%%counter int@1\n");
    printf("JUMP $write_loop\n");
    printf("LABEL $end_write\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void int2double()
{
    printf("LABEL $Int2Double\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("DEFVAR TF@double\n");
    printf("POPS TF@double\n");
    printf("DEFVAR TF@return\n");
    printf("INT2FLOAT TF@return TF@double\n");
    printf("PUSHS TF@return\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void double2int()
{
    printf("LABEL $Double2Int\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("DEFVAR TF@int\n");
    printf("POPS TF@int\n");
    printf("DEFVAR TF@return\n");
    printf("FLOAT2INT TF@return TF@int\n");
    printf("PUSHS TF@return\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void lenght()
{
    printf("LABEL $lenght\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("DEFVAR TF@string\n");
    printf("POPS TF@string\n");
    printf("DEFVAR TF@return\n");
    printf("STRLEN TF@return TF@string\n");
    printf("PUSHS TF@return\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void substring()
{
    printf("LABEL $substring\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("DEFVAR TF@decide\n");
    printf("DEFVAR TF@return\n");
    printf("DEFVAR TF@save_string\n");
    printf("MOVE TF@return nil@nil\n");
    printf("DEFVAR TF@s\n");
    printf("POPS TF@s\n");
    printf("DEFVAR TF@i\n");
    printf("POPS TF@i\n");
    printf("DEFVAR TF@j\n");
    printf("POPS TF@j\n");
    printf("LT TF@decide TF@i int@0\n"); // i<0
    printf("JUMPIFNEQ $end_substr TF@decide bool@true\n");
    printf("LT TF@decide TF@j int@0\n"); // j<0
    printf("JUMPIFNEQ $end_substr TF@decide bool@true\n");
    printf("GT TF@decide TF@i TF@j\n"); // i>j
    printf("JUMPIFEQ $end_substr TF@decide bool@true\n");
    printf("DEFVAR TF@strlen\n");
    printf("STRLEN TF@strlen TF@s\n");
    printf("ADD TF@strlen TF@strlen int@1\n");
    printf("GT TF@tmp TF@i TF@strlen\n");
    printf("JUMPIFNEQ $end_substr TF@tmp bool@true\n");
    printf("SUB TF@strlen TF@strlen int@1\n");
    printf("LT TF@decide TF@j TF@strlen\n");
    printf("JUMPIFNEQ $end_substr TF@&tmp bool@true\n");

    printf("LABEL $loop_substr\n");
    printf("LT TF@decide TF@i TF@j\n");
    printf("JUMPIFNEQ $end_substr TF@decide bool@true\n");
    printf("GETCHAR TF@save_string TF@s TF@i\n");
    printf("CONCAT TF@return TF@return TF@save_string\n");
    printf("ADD TF@i TF@i int@1\n");
    printf("JUMP $loop_substr\n");
    printf("LABEL $end_substr\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void ord()
{
    printf("LABEL $ord\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("DEFVAR TF@string\n");
    printf("DEFVAR TF@return\n");
    printf("POPS TF@string\n");
    printf("JUMPIFEQ $nothing TF@string string@\n");
    printf("JUMP $isgood\n");
    printf("STRI2INT TF@return TF@string int@0\n");
    printf("LABEL $nothing\n");
    printf("MOVE TF@return int@0\n");
    printf("LABEL $isgood\n");
    printf("PUSHS TF@return\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}

void chr()
{
    printf("LABEL $chr\n");
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("DEFVAR TF@int\n");
    printf("POPS TF@int\n");
    printf("DEFVAR TF@return\n");
    printf("INT2CHAR TF@return TF@int\n");
    printf("PUSHS TF@return\n");
    // printf("LABEL $outOfRangechr\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
}
