   int matricula_busca;

   struct no *busca = (struct no*)malloc(sizeof(struct no));

   printf("\nDigite um numero de matricula para busca e posterior remocao: ");
   scanf("%d",&matricula_busca);

   if(busca_matricula(matricula_busca)!=NULL)
   {
      //raiz = deletar_avl(raiz,matricula_busca);
      //printf("\n\t\tArvore AVL apos remocao\n");
      //impressao_formato_arvore(raiz,0);
      printf("\n\t\tACHEI\n");
   }
   else
   {
      printf("\n\t\tVALOR NAO ENCONTRADO\n");
   }