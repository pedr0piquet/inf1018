/*
int nums[] = {10, -21, -30, 45};
int main() {
  int i, *p;
  for (i = 0, p = nums; i != 4; i++, p++)
    printf("%d\n", *p);
  return 0;
}
*/

/*
DICIONARIO
Reg	Valor
EBX	i
R12	p
EAX	(temporario) *p
*/

.data /* area de dados*/
nums:  .int  10, -21, -30, 45 /*vetor de inteiros, nums e um label que representa um end de memoria*/
Sf:  .string "%d\n"    # string de formato para printf

.text /* area de texto */
.globl  main  /*faz a main ser global*/
main: /*label main*/

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp  /*funcionamento da funcao e uma caixa preta, nao tem explicacao ainda*/
  movq    %rsp, %rbp
  subq    $16, %rsp
  movq    %rbx, -8(%rbp)
  movq    %r12, -16(%rbp)
/********************************************************/

  movl  $0, %ebx  /* ebx = 0; -> i = 0; */
  movq  $nums, %r12  /* r12 = &nums -> p = nums; */

L1:/* teste_for */
  cmpl  $4, %ebx  /* if (ebx :: 4) ?  -> i != 4 ? */
  je  L2          /* jump if equal; goto L2(sai_do_for) */
/* () significa "conteudo da memoria" e nao o valor do registrador*/
  movl  (%r12), %eax    /* eax = *r12 */

/*************************************************************/
/* este trecho imprime o valor de %eax (estraga %eax)  */
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl    %eax, %esi   /* segundo parametro  (inteiro) */
  call  printf       /* chama a funcao da biblioteca */
/*************************************************************/

  addl  $1, %ebx  /* ebx += 1; -> i++ */
  addq  $4, %r12  /* r12 += 4; -> p++; equivalente em c para p = p + 1 PONTEIRO SEMPRE TEM 64 BITS*/
/* em c pode somar 1, mas em assembly vc tem que somar 4 bytes(p e ponteiro de int) */
  jmp  L1         /* goto L1(teste_for); */

L2: /* sai_do_for */
/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq  -8(%rbp), %rbx /*caixa preta tambem, para funcao funcionar*/
  movq  -16(%rbp), %r12
  leave
  ret
/***************************************************************/
