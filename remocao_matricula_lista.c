int matricula_busca;

   struct no *busca = (struct no*)malloc(sizeof(struct no));

   printf("\nDigite um numero de matricula para busca e posterior remocao: ");
   scanf("%d",&matricula_busca);

   if(busca_matricula(matricula_busca)!=NULL)
   {
      printf("\n\t\tVALOR ENCONTRADO\n");
      remover(busca_matricula(matricula_busca));
   }
   else
   {
      printf("\n\t\tVALOR NAO ENCONTRADO\n");
   }

   imprimeLista();