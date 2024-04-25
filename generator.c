/* ************************************************************************** */
/* Project name: Compiler implementation for IFJ23 imperative language        */
/* File authors: xforma19 – David Formánek                                    */
/*               xchova25 – David Chovanec                                    */
/* ************************************************************************** */

#include "generator.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "symtable.h"
#include "symbol.h"
#include "node.h"
#include "dstring.h"
#include "datatype.h"
#include "printgenerator.h"

bool is_main = true;
int counter = 0;
int frame_depth = 0;
FuncStack FuncglobalStack;
CountStack CountglobalStack;

void generateCode(Node *root, SymTable *sym_table)
{
    if (counter == 0)
    {
        initializeCountStack(&CountglobalStack);
        initializeFuncStack(&FuncglobalStack);
        pushFunc(&FuncglobalStack, "start");
        counter++;
        start_code();
        write();
        read_int();
        int2double();
        ord();
        chr();
        read_double();
        read_string();
        double2int();
        lenght();
        substring();
    }

    if (root == NULL)
    {
        return;
    }

    switch (root->node_type)
    {
    case NT_StatementList:
        generateStatementList(root, sym_table);
        break;
    case NT_CodeBlock:
        generateCodeBlock(root, sym_table);
        break;
    case NT_VarDeclare:
        generateVarDeclare(root, sym_table);
        break;
    case NT_Assign:
        generateAssign(root, sym_table);
        break;
    case NT_Literal:
        generateLiteral(root, sym_table);
        break;
    case NT_Variable:
        generateVariable(root, sym_table);
        break;
    case NT_FuncDeclare:
        generateFuncDeclare(root, sym_table);
        break;
    case NT_FuncCall:
        generateFuncCall(root, sym_table);
        break;
    case NT_While:
        generateWhile(root, sym_table);
        break;
    case NT_If:
        generateIf(root, sym_table);
        break;
    case NT_ValueOrDefault:
        generateValueOrDefault(root, sym_table);
        break;
    case NT_Equal:
    case NT_NotEqual:
    case NT_Lower:
    case NT_Greater:
    case NT_LowerEqual:
    case NT_GreaterEqual:
    case NT_Add:
    case NT_Subtract:
    case NT_Multiply:
    case NT_Divide:
        generateBinaryOperation(root, sym_table);
        break;
    case NT_Unpack:
        generateUnpack(root, sym_table);
        break;
    case NT_Return:
        generateReturn(root, sym_table);
        break;

    default:
        fprintf(stderr, "Chyba: Neočekávaný typ uzlu: %d\n", root->node_type);
        break;
    }
}

// start of functions for final code

void generateStatementList(Node *node, SymTable *sym_table)
{
    printf("#generateStatementList\n");
    CodeBlockNode *node_list = (CodeBlockNode *)node->value;
    frame_depth = node_list->scope->scope_depth;
    printf("#zanoreni je %d\n", frame_depth);

    // NodeList *node_list = (NodeList *)node->value;

    for (int i = 0; i < node_list->statements->length; i++)
    {
        Node *currentNode = nodeList_get(node_list->statements, i);
        if (currentNode->node_type == NT_FuncDeclare)
        {
            generateCode(nodeList_get(node_list->statements, i), sym_table);
        }
    }
    start_main();
    for (int i = 0; i < node_list->statements->length; i++)
    {
        Node *currentNode = nodeList_get(node_list->statements, i);
        if (currentNode->node_type != NT_FuncDeclare)
        {
            generateCode(nodeList_get(node_list->statements, i), sym_table);
        }
    }
}

void generateVarDeclare(Node *node, SymTable *sym_table)
{
    printf("#generateVarDeclare\n");
    FuncDeclareNode *func_node = (FuncDeclareNode *)node->value;
    char *id = (char *)func_node->id;
    char *is_in_while = get_func(&FuncglobalStack);
    if (strcmp(is_in_while, "while") != 0)
    {

        if (func_node->scope->scope_depth == 1)
        {
            defvar_gf(id);
        }
        else
        {
            defvar_tf(id);
        }
    }
}

void generateAssign(Node *node, SymTable *sym_table)
{
    printf("#generateAssign\n");
    BinaryNode *binary_node = (BinaryNode *)node->value;
    LiteralNode *literalNode = (LiteralNode *)binary_node->left->value;
    VariableNode *var_declare = (VariableNode *)binary_node->left->value;
    Symbol *symbol = (Symbol *)symTable_get(sym_table, var_declare->id, var_declare->scope);
    VariableSymbol *var = (VariableSymbol *)symbol->value;
    char *id = (char *)literalNode->value;
    char *smb1;
    char *smb2;

    if (binary_node->right->node_type == NT_Add && strcmp(varType_toString(var->variable_type), "String") == 0)
    {
        BinaryNode *add_node = (BinaryNode *)binary_node->right->value;
        FuncDeclareNode *func_node = (FuncDeclareNode *)binary_node->left->node_type;
        if (binary_node->left->node_type == NT_VarDeclare)
        {
            if (func_node->scope->scope_depth == 1)
            {
                printf("DEFVAR GF@%s\n", id);
            }
            else
            {
                printf("DEFVAR TF@%s\n", id);
            }
        }
        if (func_node->scope->scope_depth == 1)
        {
            printf("CONCAT GF@%s", id);
        }
        else
        {
            printf("CONCAT TF@%s", id);
        }
        if (add_node->left->node_type == NT_Literal)
        {
            LiteralNode *literaladd = (LiteralNode *)add_node->left->value;
            smb1 = (char *)literaladd->value;
            transform(&smb1);
            printf(" string@%s", smb1);
        }
        else
        {
            VariableNode *var_add = (VariableNode *)add_node->left->value;
            smb1 = (char *)var_add->id;
            if (func_node->scope->scope_depth == 1)
            {
                printf(" GF@%s", smb1);
            }
            else
            {
                printf(" TF@%s", smb1);
            }
        }

        if (add_node->right->node_type == NT_Literal)
        {
            LiteralNode *literaladd = (LiteralNode *)add_node->right->value;
            smb2 = (char *)literaladd->value;
            transform(&smb2);
            printf(" string@%s\n", smb2);
        }
        else
        {
            VariableNode *var_add = (VariableNode *)add_node->right->value;
            smb2 = (char *)var_add->id;
            if (func_node->scope->scope_depth == 1)
            {
                printf(" GF@%s\n", smb2);
            }
            else
            {
                printf(" TF@%s\n", smb2);
            }
        }
    }
    else
    {
        generateCode(binary_node->left, sym_table);
        generateCode(binary_node->right, sym_table);

        if (var_declare->scope->scope_depth == 1)
        {
            print_assign_gf(id);
        }
        else if (var_declare->scope->scope_depth == frame_depth)
        {
            print_assign_tf(id);
        }
        else if (var_declare->scope->scope_depth + 1 == frame_depth)
        {
            print_assign_lf(id);
        }
        else
        {
            print_assign_gf(id);
        }
    }
    /*if(binary_node->right->node_type == NT_FuncCall)
    {
        print_popframe();
        //print_clears();
    }
    */
}

void generateLiteral(Node *node, SymTable *sym_table)
{
    printf("#generateLiteral\n");
    LiteralNode *literalNode = (LiteralNode *)node->value;
    switch (literalNode->variable_type->type)
    {
    case DT_Int:
        push_int(atoi(literalNode->value));
        break;
    case DT_Double:
        push_float(atof(literalNode->value));
        break;
    case DT_Bool:
        push_bool(strcmp(literalNode->value, "true") == 0);
        break;
    case DT_String:
        transform(&literalNode->value);
        push_string(literalNode->value);
        break;
    case DT_Nil:
        push_nil();
        break;
    }
}

void generateVariable(Node *node, SymTable *sym_table)
{
    printf("#generateVariable\n");
    VariableNode *varnode = (VariableNode *)node->value;
    // printf("ddddddddddddddddddddddddddddddddddddddddddddddddddddddddd\n");
    // scope_print(varnode->scope);
    printf("#zanoreni je %d\n", frame_depth);
    char *id = (char *)varnode->id;
    printf("#var zanoreni%d\n", varnode->scope->scope_depth);
    if (varnode->scope->scope_depth == 1)
    {
        push_var_gf(id);
    }
    else if (varnode->scope->scope_depth == frame_depth)
    {
        push_var_tf(id);
    }
    else if (varnode->scope->scope_depth + 1 == frame_depth)
    {
        push_var_lf(id);
    }
    else
    {
        push_var_gf(id);
    }
}

void generateCodeBlock(Node *node, SymTable *sym_table)
{
    printf("#generateCodeBlock\n");
    CodeBlockNode *node_list = (CodeBlockNode *)node->value;
    frame_depth = node_list->scope->scope_depth;
    printf("#zanoreni je %d\n", frame_depth);

    for (int i = 0; i < node_list->statements->length; i++)
    {
        frame_depth = node_list->scope->scope_depth;
        generateCode(nodeList_get(node_list->statements, i), sym_table);
    }
}

void generateFuncDeclare(Node *node, SymTable *sym_table)
{
    printf("#generateFuncDeclare\n");
    is_main = false;
    FuncDeclareNode *func_node = (FuncDeclareNode *)node->value;

    declare_func(func_node->id);
    Symbol *symbol = symTable_get(sym_table, func_node->id, func_node->scope);
    FunctionSymbol *function = (FunctionSymbol *)symbol->value;
    for (int i = 0; i < function->parameter_names->length; i++)
    {

        Symbol *param_symbol = (Symbol *)linkedList_get(function->parameters, i);
        VariableSymbol *param = (VariableSymbol *)param_symbol->value;
        func_defvar(param_symbol->id);
    }
    generateCode(func_node->body, sym_table);
    print_popframe();
    print_return();
    is_main = true;
}

void generateFuncCall(Node *node, SymTable *sym_table)
{
    printf("#generateFuncCall\n");
    FuncCallNode *node_call = (FuncCallNode *)node->value;
    NodeList *node_list = (NodeList *)node->value;

    for (int i = node_call->arguments->length; i >= 0; i--)
    {
        generateCode(nodeList_get(node_call->arguments, i), sym_table);
    }
    char *name_func = node_call->id;
    if (strcmp(name_func, "write") == 0)
    {
        printf("MOVE GF@%%counter int@%d\n", node_call->arguments->length);
    }
    print_call(node_call->id);
}
// vypisu navesti pote telo podmikny projdu potom podminku pro skok na konec a potom telowhile
void generateWhile(Node *node, SymTable *sym_table)
{
    printf("#generateWhile\n");
    BinaryNode *binary_node = (BinaryNode *)node->value;
    skip_defvar(binary_node->right);
    pushFunc(&FuncglobalStack, "while");
    // pushCount(&CountglobalStack, counter);
    int numb = counter;
    counter++;

    start_while(numb);
    generateCode(binary_node->left, sym_table);
    while_condition(numb);
    frame_depth = frame_depth + 1;
    print_pushframe();
    print_createframe();
    generateCode(binary_node->right, sym_table);
    end_while(numb);
    // popCount(&CountglobalStack);
    popFunc(&FuncglobalStack);
    // print_popframe();
    // print_clears();
    frame_depth = frame_depth - 1;
}

void generateIf(Node *node, SymTable *sym_table)
{
    printf("#generateIf\n");

    int numb = counter;
    counter++;

    IfNode *if_node = (IfNode *)node->value;
    generateCode(if_node->condition, sym_table);
    start_if(numb);
    print_pushframe();
    print_createframe();
    generateCode(if_node->if_true, sym_table);
    print_popframe();
    else_if(numb);
    print_pushframe();
    print_createframe();
    generateCode(if_node->if_false, sym_table);
    print_popframe();
    end_if(numb);
}

void generateValueOrDefault(Node *node, SymTable *sym_table)
{
    printf("#generateValueOrDefault\n");
    BinaryNode *binary_node = (BinaryNode *)node->value;
    LiteralNode *literalNode = (LiteralNode *)binary_node->left->value;

    char *id = (char *)literalNode->value;
    int numb = counter;
    counter++;
    generateCode(binary_node->left, sym_table);
    value_start(numb);
    generateCode(binary_node->right, sym_table);
    if (is_main)
    {
        end_value_gf(numb, id);
    }
    else
    {
        end_value_tf(numb, id);
    }
    generateCode(binary_node->left, sym_table);
    printf("LABEL $endvalue%d\n", numb);
}

void generateBinaryOperation(Node *node, SymTable *sym_table)
{
    printf("#generateBinaryOperation\n");
    BinaryNode *binary_node = (BinaryNode *)node->value;

    generateCode(binary_node->left, sym_table);
    generateCode(binary_node->right, sym_table);
    switch (node->node_type)
    {
    case NT_Add:
        print_adds();
        break;
    case NT_Subtract:
        print_subs();
        break;
    case NT_Multiply:
        print_muls();
        break;
    case NT_Divide:
        if (binary_node->left->node_type == NT_Variable)
        {
            VariableNode *var_declare = (VariableNode *)binary_node->left->value;
            Symbol *symbol = (Symbol *)symTable_get(sym_table, var_declare->id, var_declare->scope);
            VariableSymbol *var = (VariableSymbol *)symbol->value;

            if (strcmp(varType_toString(var->variable_type), "Int") == 0)
            {
                print_idivs();
                break;
            }
        }
        else if (binary_node->right->node_type == NT_Variable)
        {
            VariableNode *var_declare = (VariableNode *)binary_node->right->value;
            Symbol *symbol = (Symbol *)symTable_get(sym_table, var_declare->id, var_declare->scope);
            VariableSymbol *var = (VariableSymbol *)symbol->value;

            if (strcmp(varType_toString(var->variable_type), "Int") == 0)
            {
                print_idivs();
                break;
            }
        }
        else if (binary_node->left->node_type == NT_Literal)
        {
            LiteralNode *var_declare = (LiteralNode *)binary_node->left->value;

            if (var_declare->variable_type->type == DT_Int)
            {
                print_idivs();
                break;
            }
        }
        else if (binary_node->right->node_type == NT_Literal)
        {
            LiteralNode *var_declare = (LiteralNode *)binary_node->right->value;

            if (var_declare->variable_type->type == DT_Int)
            {
                print_idivs();
                break;
            }
        }
        print_divs();
        break;
    case NT_Equal:
        print_eqs();
        break;
    case NT_NotEqual:
        print_nots();
        break;
    case NT_Lower:
        print_lts();
        break;
    case NT_Greater:
        print_gts();
        break;
    case NT_LowerEqual:
        print_eqlits();
        break;
    case NT_GreaterEqual:
        print_eqgts();
        break;

    default:
        break;
    }
}

void generateUnpack(Node *node, SymTable *sym_table)
{
    printf("#generateUnpack\n");
    generateCode(node->value, sym_table);
}

void generateReturn(Node *node, SymTable *sym_table)
{
    printf("#generateReturn\n");
    generateCode(node->value, sym_table);
}

// funkce zasobniku

void initializeFuncStack(FuncStack *stack)
{
    stack->top = -1;
}

void pushFunc(FuncStack *stack, const char *str)
{
    stack->items[++(stack->top)] = strdup(str);
}

char *popFunc(FuncStack *stack)
{
    return stack->items[(stack->top)--];
}

void initializeCountStack(CountStack *stack)
{
    stack->top = -1;
}

void pushCount(CountStack *stack, int item)
{
    stack->items[++(stack->top)] = item;
}

int popCount(CountStack *stack)
{

    return stack->items[(stack->top)--];
}

char *get_func(FuncStack *stack)
{
    return stack->items[stack->top];
}

// skip defvar------------------------------------------------------------------------------------------------------------------------------------------------------------
void skip_defvar(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    switch (root->node_type)
    {
    case NT_StatementList:
        skipStatementList(root);
        break;
    case NT_CodeBlock:
        skipCodeBlock(root);
        break;
    case NT_VarDeclare:
        skipVarDeclare(root);
        break;
    case NT_Assign:
        skipAssign(root);
        break;
    case NT_Literal:
        skipLiteral(root);
        break;
    case NT_Variable:
        skipVariable(root);
        break;
    case NT_FuncDeclare:
        skipFuncDeclare(root);
        break;
    case NT_FuncCall:
        skipFuncCall(root);
        break;
    case NT_While:
        skipWhile(root);
        break;
    case NT_If:
        skipIf(root);
        break;
    case NT_ValueOrDefault:
        skipValueOrDefault(root);
        break;
    case NT_Equal:
    case NT_NotEqual:
    case NT_Lower:
    case NT_Greater:
    case NT_LowerEqual:
    case NT_GreaterEqual:
    case NT_Add:
    case NT_Subtract:
    case NT_Multiply:
    case NT_Divide:
        skipBinaryOperation(root);
        break;
    case NT_Unpack:
        skipUnpack(root);
        break;
    case NT_Return:
        skipReturn(root);
        break;

    default:
        fprintf(stderr, "Chyba: Neočekávaný typ uzlu: %d\n", root->node_type);
        break;
    }
}

void skipStatementList(Node *node)
{
    NodeList *node_list = (NodeList *)node->value;

    for (int i = 0; i < node_list->length; i++)
    {
        skip_defvar(nodeList_get(node_list, i));
    }
}

void skipVarDeclare(Node *node)
{
    printf("#SkipVarDeclare\n");
    FuncDeclareNode *func_node = (FuncDeclareNode *)node->value;
    char *id = (char *)func_node->id;
    char *is_in_while = get_func(&FuncglobalStack);
    if (strcmp(is_in_while, "while") != 0)
    {

        if (func_node->scope->scope_depth == 1)
        {
            defvar_gf(id);
        }
        else
        {
            defvar_lf(id);
        }
    }
}

void skipAssign(Node *node)
{
    BinaryNode *binary_node = (BinaryNode *)node->value;
    skip_defvar(binary_node->left);
    skip_defvar(binary_node->right);
}

void skipLiteral(Node *node)
{
}

void skipVariable(Node *node)
{
}

void skipCodeBlock(Node *node)
{
    CodeBlockNode *node_list = (CodeBlockNode *)node->value;

    for (int i = 0; i < node_list->statements->length; i++)
    {
        skip_defvar(nodeList_get(node_list->statements, i));
    }
}

void skipFuncDeclare(Node *node)
{
}

void skipFuncCall(Node *node)
{
}
// vypisu navesti pote telo podmikny projdu potom podminku pro skok na konec a potom telowhile
void skipWhile(Node *node)
{
    BinaryNode *binary_node = (BinaryNode *)node->value;

    skip_defvar(binary_node->left);
    skip_defvar(binary_node->right);
}

void skipIf(Node *node)
{
    IfNode *if_node = (IfNode *)node->value;
    skip_defvar(if_node->condition);
    skip_defvar(if_node->if_true);
    skip_defvar(if_node->if_false);
}

void skipValueOrDefault(Node *node)
{
}

void skipBinaryOperation(Node *node)
{
    BinaryNode *binary_node = (BinaryNode *)node->value;

    skip_defvar(binary_node->left);
    skip_defvar(binary_node->right);
}

void skipUnpack(Node *node)
{
}

void skipReturn(Node *node)
{
}
/*------------------------------------------------------------------------------------------------------------------------------------------------*/
void AppendSpecChar(char **strr, int ch, unsigned int *index)
{
    char *str = *strr;
    // In case the actual char's int value is higher than 127
    if (ch < 0)
    {
        ch = ch + 256;
    }

    // Convert decimal/int value to a string
    char tmp[4];
    sprintf(tmp, "%d", ch);

    // Terminating the string
    tmp[3] = '\0';

    // Formatting the string
    switch (strlen(tmp))
    {
    case 1:
        tmp[1] = tmp[0];
        tmp[0] = '0';
    case 2:
        tmp[2] = tmp[1];
        tmp[1] = tmp[0];
        tmp[0] = '0';
        break;
    }

    // Apending the string
    str[*index] = '\\';
    (*index)++;
    int i = 0;
    while (tmp[i] != '\0')
    {
        str[*index] = tmp[i];
        (*index)++;
        i++;
    }
}

// Transforms a swift string into a IFJCode23 string
void transform(char **strtr)
{
    char *str = *strtr;
    unsigned int i = 0;
    unsigned int j = 0;
    size_t size = strlen(str);

    // Biggest possible incease of the string length
    int sizeinc = 4;

    char *tstring = calloc(sizeof(char) * size, size);

    while (str[i] != '\0')
    {

        if (j >= size - sizeinc)
        {
            tstring = realloc(tstring, sizeof(char) * (size + sizeinc));
            size = size + sizeinc;

            memset(&tstring[size - sizeinc], 0, sizeinc);
        }

        // If its a letter
        if ((str[i] <= 'z' && str[i] >= 'a') || (str[i] <= 'Z' && str[i] >= 'A'))
        {
            tstring[j] = str[i];
            j++;
        }
        // If its a digit
        else if (str[i] <= '9' && str[i] >= '0')
        {
            tstring[j] = str[i];
            j++;
        }
        // If its a special character
        else
        {
            AppendSpecChar(&tstring, (int)str[i], &j);
        }
        i++;
    }
    *strtr = tstring;
}
