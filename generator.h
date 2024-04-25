/* ************************************************************************** */
/* Project name: Compiler implementation for IFJ23 imperative language        */
/* File authors: xforma19 – David Formánek                                    */
/*               xchova25 – David Chovanec                                    */
/* ************************************************************************** */

#ifndef GENERATOR_H
#define GENERATOR_H

#include "node.h"
#include "symtable.h"
#include "symbol.h"


#define MAX_STACK_SIZE 1000
#define MAX_STRING_LENGTH 500

typedef struct {
    char* items[MAX_STACK_SIZE];
    int top;
} FuncStack;

typedef struct {
    int items[MAX_STACK_SIZE];
    int top; 
} CountStack;

void generateCode(Node *root, SymTable *sym_table);
void initializeCountStack(CountStack* stack);
void initializeFuncStack(FuncStack* stack);
void generateStatementList(Node *node, SymTable *sym_table);
void generateVarDeclare(Node *node, SymTable *sym_table);
void generateAssign(Node *node, SymTable *sym_table);
void generateLiteral(Node *node, SymTable *sym_table);
void generateVariable(Node *node, SymTable *sym_table);
void generateCodeBlock(Node *node, SymTable *sym_table);
void generateFuncDeclare(Node *node, SymTable *sym_table);
void generateFuncCall(Node *node, SymTable *sym_table);
void generateWhile(Node *node, SymTable *sym_table);
void generateIf(Node *node, SymTable *sym_table);
void generateValueOrDefault(Node *node, SymTable *sym_table);
void generateBinaryOperation(Node *node, SymTable *sym_table);
void generateUnpack(Node *node, SymTable *sym_table);
void generateReturn(Node *node, SymTable *sym_table);
void initializeFuncStack(FuncStack* stack);
void pushFunc(FuncStack* stack, const char* str);
char* popFunc(FuncStack* stack);
void initializeCountStack(CountStack* stack);
void pushCount(CountStack* stack, int item);
int popCount(CountStack* stack);
void skip_defvar(Node *root);
void skip_defvar(Node *root);
void skipStatementList(Node *node) ;
void skipVarDeclare(Node *node);
void skipAssign(Node *node);
void skipLiteral(Node *node);
void skipVariable(Node *node);
void skipCodeBlock(Node *node);
void skipFuncDeclare(Node *node);
void skipFuncCall(Node *node);
void skipWhile(Node *node);
void skipIf(Node *node);
void skipValueOrDefault(Node *node);
void skipBinaryOperation(Node *node);
void skipUnpack(Node *node);
void skipReturn(Node *node);
char *get_func(FuncStack *stack);
void transform(char **strtr);
void AppendSpecChar(char **strr,int ch,unsigned int *index);
#endif