#include <stdio.h>
#include <Windows.h>


								// BILDSCHIRMAUSGABE
void header(char* txt, float ver)
{
	printf("\n\t\t###___%s___### v%.2f\n\n\n\n", txt, ver);
}
					
void print_hpt_menue()
{
	printf("\tAuswahlmen\201\n\t------------\n\n");
	printf("\t1. Neues Spiel\n");
	printf("\t2. Spielstand laden\n");
	printf("\t3. Beenden\n\n");
	printf("\tWas m\224chtest du tun?\n\tEingabe: ");
}						
								
void printsudoku(int sudoku[][10])
{
	int i, j;



	for (i = 1; i < 10; i++)
	{
		printf("\t");
		
		if (i == 4 || i == 7)
		{
			 printf("\n\t");
		}
		
			for (j = 1; j < 10; j++)
			{
				if (sudoku[i][j] == 0)
				{
					if (j == 4 || j == 7)
						printf("  |");
						printf("   ");
				}
				else
				{

				
					
				if (j == 4 || j == 7)
				printf("  |");

				printf("%3d", sudoku[i][j]);
				}
			}
		printf("   \n");
	}	printf("\n");
}

void print_hilfe(int code)
{

	switch (code)
	{
	case 1: printf("\t***Keine Fehler gefunden***\n\n"); break;
	case 2:	printf("\t***Sudoku ist bereits gel\224st***\n\n"); break;
	case 3:	printf("\t***Sudoku wurde rechnerisch gel\224st***\n\n"); break;
	case 4:	printf("\t***Kein Speicherstand verf\201gbar***\n\n"); break;



	};
}

void print_loesung(int sudoku[][10]) 
{
	system("cls");
	header("Sudoku", 0.1f);
	printsudoku(sudoku);
	printf("\tZur\201ck zum Spiel? ");
	printf("Enter dr\201cken");
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	// Lese den nächsten Tastendruck
	getch();


}


								// DAU EINGABE ABFRAGEN
int eingabecheck(int min,int max, int versuche)
{
	int eing=0;

	if (versuche == 0)
	{
		printf("\n\tZu viele Fehleingaben. Programm bitte erneut starten");
		exit(0);
	}
	else

		if ((scanf("%d", &eing)) != 1)
		{
			printf("\n\tFalsche Eingabe. Bitte eine Dezimalzahl eingeben.\n");
			while (fgetc(stdin) != '\n')
				versuche--;
			return eingabecheck(min, max, versuche);
		}

	if ((eing < min) || (eing > max))
	{
		printf("\n\tFalsche Eingabe. Bitte Wertebereich[%d-%d]beachten\n", min, max);
		versuche--;
		return eingabecheck(min, max, versuche);

	}

	return eing;

}

								//** SUDOKUS AUS TEXTDATEI LADEN
void loadsudoku(int sudoku1[][10], char *datname)
{
	FILE* datei;

	datei = fopen(datname, "r");

	if (datei == NULL)
	{
		printf("Fehler beim Öffnen\n");
	}

	else
	{
		//printf("Datei ge\224ffnet\n\n");
		int a,i, j;
		int r = 0;


		for (i = 1; (r >= 0 && i < 10); i++) // Schleife zum Auslesen der Txt-Datei
		{
			for (j = 1; (r >= 0 && j < 10); j++)
			{

				r = fscanf(datei, "%d", &a);
				if (r < 0) {
					break;
				}
				sudoku1[i][j] = a;
			}
		}

	fclose(datei);
	}

	
} 
void loadsudoku_L(int sudoku[][10], char *datname)
{
	FILE* datei;

	datei = fopen(datname, "r");

	if (datei == NULL)
	{
		printf("Fehler beim Öffnen\n");
	}

	else
	{
		//printf("Datei ge\224ffnet\n\n");
		int a, i, j;
		int r = 0;


		for (i = 1; (r >= 0 && i < 10); i++) // Schleife zum Auslesen der Txt-Datei
		{
			for (j = 1; (r >= 0 && j < 10); j++)
			{

				r = fscanf(datei, "%d", &a);
				if (r < 0) {
					break;
				}
				sudoku[i][j] = a;
			}
		}

		fclose(datei);
	}


}
						
int load_save(int sudoku[][10], int sudoku_L[][10], int *history, int *history_ct)
{
	FILE* datei;

	datei = fopen("Speicherstand.txt", "r");

	if (datei == NULL)
	{
		printf("Fehler beim Öffnen\n");
		return 1;
	}

	else
	{
		//printf("Datei ge\224ffnet\n\n");
		int a, i, j;
		int r = 0;


		for (i = 1; (r >= 0 && i < 10); i++) // Schleife zum Auslesen der Txt-Datei
		{
			for (j = 1; (r >= 0 && j < 10); j++)
			{

				r = fscanf(datei, "%d", &a);
				if (r < 0) {
					break;
				}
				sudoku[i][j] = a;
			}
		}

		for (i = 1; (r >= 0 && i < 10); i++) // Schleife zum Auslesen der Txt-Datei
		{
			for (j = 1; (r >= 0 && j < 10); j++)
			{

				r = fscanf(datei, "%d", &a);
				if (r < 0) {
					break;
				}
				sudoku_L[i][j] = a;
			}
		}
		
		
		

			for (i = 0; (r >= 0 && i < 100); i++)
			{

				r = fscanf(datei, "%d", &a);
				if (r < 0) {
					break;
				}
				history[i] = a;

			}
			// LADE COUNTER FÜR UNDO FKT
			fscanf(datei, "%d", &a);
			*history_ct = a;
		
		fclose(datei);
		return 0;
	}
	}


void save_sudoku(int sudoku[][10],int sudoku_L[][10],int *history, int *history_ct)
{
	FILE* datei;

	datei = fopen("Speicherstand.txt", "w");

	if (datei == NULL)
	{
		printf("\tFehler beim \224ffnen\n");
	}

	else
	{
		//printf("Datei ge\224ffnet\n\n");
		int i, j;
		int r = 0;

		// Schleife zum Schreiben der Txt-Datei
		for (i = 1; (r >= 0 && i < 10); i++) 
		{
			for (j = 1; (r >= 0 && j < 10); j++)
			{

				r = fprintf(datei, "%d ", sudoku[i][j]);
				
			}
			fprintf(datei,"\n");
		}

		fprintf(datei, "\n");
											// Schleife zum Schreiben des LÖSUNGSSUDOKUS
		for (i = 1; (r >= 0 && i < 10); i++) 
		{
			for (j = 1; (r >= 0 && j < 10); j++)
			{

				r = fprintf(datei, "%d ", sudoku_L[i][j]);

			}
			fprintf(datei, "\n");
		}

		fprintf(datei, "\n");
											// SCHREIBE HISTORY VON UNDO FKT
		
			
			for (i = 0; (r >= 0 && i < 100); i++)
			{
				if (history[i] != 0)
				{
					r = fprintf(datei, "%d ", history[i]);
				}

			}
			// SCHREIBE COUNTER FÜR UNDO FKT
			r = fprintf(datei, "%d ", *history_ct);





		
			fclose(datei);
		
	}


}

									//PROGRAMMFUNKTIONEN
									//-VERGLEICH / EINGABEN ÜBERPRÜFEN
int compareSudoku(int sudoku1[][10], int sudoku1_L[][10])
{
	int i, j; 
	

	for (i = 1; i < 10; i++)
	{
		for (j = 1; j < 10; j++)
		{
			if (sudoku1[i][j] != sudoku1_L[i][j])
			{
				if (sudoku1[i][j] == 0) {}
				else
				{
					return  2;
					
				}
			} 
							
			return 1;

		}
	}
	return 1;
}

									//-UNDO FKT - MACHT EINGABEN RÜCKGÄNGIG
void undo(int sudoku[][10],int* history, int *history_ct)
{
	
	int z, s;

	



		z = history[*history_ct];
		s = history[*history_ct + 1];

		history[*history_ct] = 0;
		history[*history_ct + 1] = 0;

		if (*history_ct >= 2)
		{
			*history_ct = *history_ct - 2;
		}

		sudoku[z][s] = 0;
	

	

}

									//-HISTORY FÜR UNDO FUNKTION - SCHREIBT BISHERIGE Z UND S IN ARRAY und ERHÖHT COUNTER
void valuehistory(int *history, int *history_ct, int* z, int* s)
{
	int i,j;

	for (i = 0,j=1; i < 98; i += 2, j += 2)
	{ 
		if (history[i] == 0)
		{
			
			if (history[i] != history[0])
			{
				*history_ct = *history_ct + 2;
			}
		
			
		history[i] = *z;
		history[j] = *s;

		

		break;
		}
		

	}

}
									
//-PRÜFT, OB ZAHL IN ZEILE, SPALTE oder BLOCK STEHT
int checkvalue(int sudoku[][10], int zahl, int z, int s)
{
	int i, j;

	//PRÜFUNG, OB ZAHL IN ZEILE ODER SPALTE STEHT
	for (i=1; i < 10; i++)
	{
		for (j=1; j < 10; j++)
		{
			if ((sudoku[z][j] == zahl) || (sudoku[i][s] == zahl))
			{
				return 1;
			}
			
		}

	}

	//PRÜFUNG, OB ZAHL IN 9er MATRIX STEHT+++EINE SCHLEIFE PRO BLOCK
	if (z <= 3 && s <= 3)  //BLOCK I 
	{
		for (i = 1; i <= 3; i++)
		{
			for (j = 1; j <= 3; j++)
			{
				if (sudoku[i][j] == zahl)
				{
					return 1;
				}
			}

		}

	}
	else if (z <= 3 && (s < 7 && s>3)) // II 
	{
		for (i = 1; i <= 3; i++)
		{
			for (j = 4; j <= 6; j++)
			{
				if (sudoku[i][j] == zahl)
				{
					return 1;
				}
			}

		}

	}
	else if (z <= 3 && (s < 10 && s>6)) // III
	{
		for (i = 1; i <= 3; i++)
		{
			for (j = 7; j <= 9; j++)
			{
				if (sudoku[i][j] == zahl)
				{
					return 1;
				}
			}

		}

	}

				else if ((z>3 && z<7) && s <= 3) //IV
		{
		for (i = 4; i <= 6; i++)
		{
			for (j = 1; j <= 3; j++)
			{
				if (sudoku[i][j] == zahl)
				{
					return 1;
				}
			}
		}

		}
				else if ((z > 3 && z < 7) && (s < 7 && s>3)) //V
		{
		for (i = 4; i <= 6; i++)
		{
			for (j = 4; j <= 6; j++)
			{
				if (sudoku[i][j] == zahl)
				{
					return 1;
				}
			}

		}

		}
				else if ((z > 3 && z < 7) && (s < 10 && s>6)) //VI
		{
		for (i = 4; i <= 6; i++)
		{
			for (j = 7; j <= 9; j++)
			{
				if (sudoku[i][j] == zahl)
				{
					return 1;
				}
			}

		}

		}

					else if ((z > 6 && z < 10) && s <= 3) //VII 
			{
				for (i = 7; i <= 9; i++)
				{
					for (j = 1; j <= 3; j++)
					{
					if (sudoku[i][j] == zahl)
					{
						return 1;
					}
					}

				}

			}
					else if ((z > 6 && z < 10) && (s < 7 && s>3))//VIII 
			{
			for (i = 7; i <= 9; i++)
			{
				for (j = 4; j <= 6; j++)
				{
					if (sudoku[i][j] == zahl)
					{
						return 1;
					}
				}

			}

			}
					else if ((z > 6 && z < 10) && (s < 10 && s>6))//IX
			{
			for (i = 7; i <= 9; i++)
			{
				for (j = 7; j <= 9; j++)
				{
					if (sudoku[i][j] == zahl)
					{
						return 1;
					}
				}

			}

			}

			return 0;
}

									//-EINGABE DES NUTZERS IM SUDOKU
void changevalue(int sudoku[10][10], int* history, int* history_ct)
{
	system("cls");
	header("Sudoku", 0.1f);
	printsudoku(sudoku);
	int z, s, zahl, check = 0;

	printf("\n\tWelchen Wert m\224chtest du \204ndern?\n");
	printf("\tZeile = "); z = eingabecheck(1, 9, 5); // ZEILE ANGEBEN
	printf("\tSpalte = "); s = eingabecheck(1, 9, 5); //SPALTE ANGEBEN


	if (sudoku[z][s] == 0)
	{

		printf("\n\tWelche Zahl soll eingeschrieben werden?\n");
		printf("\tEingabe = ");
		zahl = eingabecheck(1, 9, 5);
		check = checkvalue(sudoku, zahl, z, s);
		if (check == 0)
		{
			valuehistory(history, history_ct, &z, &s); //BERECHNUNG UNDO
			sudoku[z][s] = zahl;
		}
		else
		{

			printf("\tDie Zahl existiert in der Zeile/Spalte bereits!\n\n");

		}



	}
	else
	{
		printf("\tFehler: Das Feld ist nicht leer.\n\n");
	}



}

									//-Prüft, ob Sudoku voll
int find_empty(int sudoku[][10])
{
	int i, j;

	for (i=1; i < 10; i++)
	{
		for (j=1; j < 10; j++)
		{
			if ((sudoku[i][j]) == 0)
			{
				return 1;
			}
		
		}
	}
	return 0;
}
									//Loest Sudoku rechnerisch
int calculate_sudoku(int sudoku[][10])
{
	int zahl,i,j;
	system("cls");
	header("Sudoku", 0.1f);

	if (find_empty(sudoku))
	{

		for (i=1; i < 10; i++)
		{
			for (j=1; j < 10; j++)
			{ 

				if (sudoku[i][j] == 0)
				{

					for (zahl = 1; zahl < 10; zahl++)
					{
						if ((checkvalue(sudoku, zahl, i, j)) == 0)
						{
							sudoku[i][j] = zahl;


					
								
								if (calculate_sudoku(sudoku) == 1)
								{
									sudoku[i][j] = 0;
									
								}
								else { return 0; }

							
								if (zahl == 9)
								{

									return 1;

								}

								
						}
						else
						{	
				
							if (zahl == 9)
							{	
								
								return 1;
								
							}
						
						}

					}
				}

			} 
		}
	}

	else //find_empty
	{
		return 0;
	}

	
			
	printsudoku(sudoku);
	return 0;
}

int array_null(int sudoku[][10])
{
	int i, j;

	for (i = 1; i < 10; i++)
	{
		for (j = 1; j < 10; j++)
		{
			if ((sudoku[i][j]) != 0)
			{
				return 0;
			}

		}
	}
	return 1;
}
	
int correction(int sudoku[][10], int sudoku_L[][10])
{
	int i, j;

	for (i = 1; i < 10; i++)
	{
		for (j = 1; j < 10; j++)
		{
			if (sudoku[i][j] != sudoku_L[i][j])
			{
				sudoku[i][j] = 0;
			}


		}
	}
}
									//ZWEIG2 - SPIELMODUS
void hpt_spiel(int sudoku[][10], int sudoku_L[][10], int *history, int *history_ct)
{
	
	unsigned int ausw;
	int fehler = 0;
	
		do
		{

		
		system("cls");
		header("Sudoku", 0.1f);
		printsudoku(sudoku);
		print_hilfe(fehler);
		printf("\tSpielmen\201\n\t------------\n\n");
		printf("\t1 - Wert eingeben\n");
		printf("\t2 - Letzten Schritt r\201ckg\204ngig machen\n");
		printf("\t3 - Bisherige Eingaben \201berpr\201fen\n");
		printf("\t4 - Spielzustand speichern\n");
		printf("\t5 - L\224sungstipp\n");
		printf("\t6 - L\224sung berechnen(rechenaufw\204ndig!)\n");
		printf("\t7 - Zur\201ck ins Hauptmen\201\n");
		printf("\tWas m\224chtest du tun?\n\tEingabe: ");

		ausw = eingabecheck(1, 7, 5);


		switch (ausw)
		{
		case 1: changevalue(sudoku, history, history_ct), fehler = 0;

			break;

		case 2:	
				if(find_empty(sudoku)==0)
				{
					fehler = 2;
				}else
				undo(sudoku, history, history_ct), fehler = 0;

			break;

		case 3:	fehler = compareSudoku(sudoku, sudoku_L);
			break;

		case 4:	save_sudoku(sudoku, sudoku_L, history, history_ct);
			break;
		
		case 5: print_loesung(sudoku_L);
			break;

		case 6: 
			correction(sudoku, sudoku_L);
			if (calculate_sudoku(sudoku) == 0)
			{
				fehler = 3;
			}
			break;

		case 7:system("cls"); main();
			break;

		default: printf("\tFalsche Eingabe\n");
		}

		} while (ausw != 7);
	
} 
									//ZWEIG1 NEUES SPIEL
void sp_auswahl(int sudoku[][10], int sudoku_L[][10],int *history, int *history_ct) 
{
	unsigned int ausw;
	

	system("cls");
	header("Sudokubeleg", 0.1f);

	printf("\tSudoku Spieleauswahl\n\t------------\n\n");
	printf("\t1 - Sudoku Nr.1 (Leicht)\n");
	printf("\t2 - Sudoku Nr.2 (Normal)\n");
	printf("\t3 - Sudoku Nr.3 (Schwer)\n\n");
	printf("\t4 - Zur\201ck ins Hauptmen\201\n\n");
	printf("\tWas m\224chtest du tun?\n\tEingabe: ");

	ausw = eingabecheck(1, 4, 5);

	switch (ausw)
	{
	case 1: loadsudoku(sudoku,"Sudoku1.txt");
			loadsudoku_L(sudoku_L, "Sudoku1_Loesung.txt");
			hpt_spiel(sudoku,sudoku_L,history,history_ct);
			exit(0);
		break;

	case 2: loadsudoku(sudoku,"Sudoku2.txt");
			loadsudoku_L(sudoku_L, "Sudoku2_Loesung.txt");
			hpt_spiel(sudoku, sudoku_L,history,history_ct);
			exit(0);
		break;

	case 3: loadsudoku(sudoku,"Sudoku3.txt");
			loadsudoku_L(sudoku_L, "Sudoku3_Loesung.txt");
			hpt_spiel(sudoku, sudoku_L,history,history_ct);
			exit(0);
		break;

	case 4: system("cls");
		break; 

	default: printf("\tFalsche Eingabe\n");
	}

}





int main()
{
	unsigned int ausw;
	int sudoku[10][10] = { 0 };
	int sudoku_L[10][10] = { 0 };
	int history[100] = { 0 };
	int history_ct = 0;
	int fehler = 0;

	do {

		header("Sudokubeleg", 1.0f);
		print_hpt_menue();
		print_hilfe(fehler);

		ausw = eingabecheck(1, 3, 5);

		switch (ausw)
		{
		case 1: sp_auswahl(sudoku,sudoku_L,history,&history_ct);
			break;

		case 2:	
				load_save(sudoku, sudoku_L, history, &history_ct);
				if (array_null(sudoku)==1)
				{
					fehler = 4;
					history_ct = 0;
					system("cls");
				
				}
				else
				{
					load_save(sudoku, sudoku_L, history, &history_ct);
					hpt_spiel(sudoku, sudoku_L, history, &history_ct);
				}
			break;

		case 3: exit(0);
			break;

		default: printf("\tFalsche Eingabe\n");
		}

	} while (ausw != 3);
	

}	

	


