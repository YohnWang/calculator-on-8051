#include"io.h"
#include<ctype.h>
#include<stdio.h>
//extern bit isdigit (unsigned char);
//extern int sscanf (char *, const char *, ...);
enum {OPERATOR,NUMBER};
union Elem
{
    float num;
    unsigned char op;
};
struct Exp
{
    unsigned char kind;
    union Elem    elem;
};
#define EXP_STR_SIZE 40
static struct Exp Exp_string[EXP_STR_SIZE];
static unsigned char char_ip=0;
static unsigned char exp_ip=0;
static unsigned char state=0;
static unsigned error_flag;
static unsigned char num_buf[20];

static float ans=0;
static void token()
{
    float tmp;
    unsigned char dot_flag=0;
    unsigned char num_buf_ip=0;
    error_flag=0;
    state=0;
    exp_ip=0;
    char_ip=0;
    buffin[buffin_top]=0;
    while(char_ip<buffin_top+1)
    {
        switch(state)
        {
        case 0:
            if(isdigit(buffin[char_ip])||buffin[char_ip]=='.')
            {
                state=1;
                num_buf[num_buf_ip++]=buffin[char_ip];
                //++num_buf_ip;
                if(buffin[char_ip]=='.')
                    dot_flag=1;
            }
            else if(buffin[char_ip]!=0&&buffin[char_ip]!='$')
            {
                state=0;
                Exp_string[exp_ip].kind=OPERATOR;
                Exp_string[exp_ip].elem.op=buffin[char_ip];
                ++exp_ip;
            }
            else if(buffin[char_ip]=='$')
            {
                state=0;
                Exp_string[exp_ip].kind=NUMBER;
                Exp_string[exp_ip].elem.num=ans;
                ++exp_ip;
            }
            else
            {

            }
            ++char_ip;
            break;
        case 1:
            if(isdigit(buffin[char_ip])||buffin[char_ip]=='.')
            {
                state=1;
                if(buffin[char_ip]=='.'&&dot_flag==0)
                {
                    dot_flag=1;
                }
                else if(buffin[char_ip]=='.'&&dot_flag==1)
                {
                    goto syntaxerror;
                }
                num_buf[num_buf_ip]=buffin[char_ip];
                ++num_buf_ip;
                ++char_ip;
            }
            else
            {
                state=0;
                dot_flag=0;
                num_buf[num_buf_ip]=0;
                sscanf(num_buf,"%f",&tmp);
                Exp_string[exp_ip].kind=NUMBER;
                Exp_string[exp_ip].elem.num=tmp;
                ++exp_ip;
                num_buf_ip=0;
            }
            break;
        case 2:
            break;
        default:
            break;
        }
    }
    //sprintf(buffout,"%c%s",exp_ip+'0',"is right");
    //printk();
    return ;

    syntaxerror:
        //sprintf(buffout,"%-16s","Syntax Error");
        //printk();
        error_flag=1;
        char_ip=0;
        exp_ip=0;
        state=0;
        num_buf_ip=0;
}
static char precedence(unsigned char op1,unsigned char op2)
{
    if (op1 == '(')
    {
        return -1;
    }
    if (op1 == '+' || op1 == '-')
    {
        if (op2 == '*' || op2 == '/')
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
    if (op1 == '*' || op1 == '/')
    {
        if (op2 == '+' || op2 == '-')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
	return 0;
}
static struct Exp Exp_stack[20];
static char stack_top;

static void init_stack()
{
    stack_top=-1;
    //error_flag=0;
}
static void push(struct Exp e)
{
    ++stack_top;
    Exp_stack[stack_top]=e;
}
static char isEmpty()
{
    return stack_top==-1;
}
static void pop()
{
    if(isEmpty())
    {
        error_flag=1;
        return ;
    }
    --stack_top;
}
static struct Exp top()
{
    if(isEmpty())
    {
        error_flag=1;
        return Exp_stack[0];
    }
    return Exp_stack[stack_top];
}

static struct Exp outstring[EXP_STR_SIZE];
static unsigned char sip;
static void intopost()
{
    unsigned char i;
    sip=0;
    //error_flag=0;
    init_stack();
    for(i=0;i<exp_ip;i++)
    {
        if(Exp_string[i].kind==NUMBER)
        {
            outstring[sip++]=Exp_string[i];
        }
        else
        {
            if(Exp_string[i].elem.op=='(')
                push(Exp_string[i]);
            else if(Exp_string[i].elem.op==')')
            {
                while(top().elem.op!='(' && !isEmpty())
                {
                    outstring[sip++]=top();
                    pop();
                }
                pop();
            }
            else
            {

                while(isEmpty()==0 && precedence(top().elem.op,Exp_string[i].elem.op) >= 0)
                {
                    outstring[sip++]=top();
                    pop();
                }
                push(Exp_string[i]);
            }
        }
    }
    while(!isEmpty())
    {
        outstring[sip++]=top();
        pop();
    }

}

static float calculate()
{
    unsigned char i=0;
    float num1,num2,res;
    init_stack();
    for(i=0;i<sip;i++)
    {
        if(outstring[i].kind==NUMBER)
        {
            push(outstring[i]);
        }
        else
        {
            num1=top().elem.num;
            pop();
            num2=top().elem.num;
            pop();
            switch(outstring[i].elem.op)
            {
            case '+':
                res=num1+num2;
                break;
            case '-':
                res=num2-num1;
                break;
            case '*':
                res=num1*num2;
                break;
            case '/':
                res=num2/num1;
                break;
            }
            outstring[i].kind=NUMBER;
            outstring[i].elem.num=res;
            push(outstring[i]);
        }
    }
    return top().elem.num;
}

void calc_driver()
{
    token();
    intopost();
    ans=calculate();
    sprintf(buffout,"%16g",ans);
    if(error_flag==1)
    {
        sprintf(buffout,"%16s","Syntax Error!");
    }
    printk();
}

