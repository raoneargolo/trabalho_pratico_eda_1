// INSERIR POR MATRICULA
	
	printf("Informe uma matricula para inserir na lista:\n");
	scanf("%d",&matricula_busca);

   if(busca_matricula(matricula_busca)!=NULL)
   {
      printf("\nNUMERO DE MATRICULA EM USO\n");
   }
   else
   {
      printf("\nMATRICULA LIBERADA PARA INSERCAO\n");
      printf("\nInforme os dados:\n");
      
      linha.matricula=matricula_busca;
      printf("Nome:");
      scanf("%s",linha.nome);
      
      printf("Sobrenome:");
      scanf("%s",linha.sobrenome);
      
      printf("Email:");
      scanf("%s",linha.email);
      
      printf("Telefone:");
      scanf("%s",linha.telefone);

      printf("Salario:");
      scanf("%lf",&linha.salario);
	
      t_ini = time (NULL);
      
      inserir(linha);

      imprimeLista();

      t_fim = time (NULL);
      
      // CALCULO DO TEMPO
      tempo = difftime (t_fim, t_ini);
	  printf("Tempo apos inserir novo registro: %.2f\n", tempo );
   }