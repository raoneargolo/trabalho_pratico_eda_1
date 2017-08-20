   char nome_busca[tamanho_caracteres];
   
   printf("\nDigite um nome para busca: ");
   fflush(stdin);
   //fgets(nome_busca,tamanho_caracteres,stdin);
   scanf("%s",nome_busca);

   //struct no *busca = (struct no*)malloc(sizeof(struct no));

   if(busca_nome(nome_busca)!=NULL)
   {
      printf("\nDESGRACA! ACHEI\n");
   }
   else
   {
      printf("\nDESGRACA! NAO ACHEI\n");
   }