#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdbool.h>

// ----------------- VARIABLER ETC ----------------


// en struktur som representerar en vara
struct vara {
    char * name;
    char * description;
    int price;
    char * shelf;
    int antal;
};


// Ett lager med varor
struct vara storage[100];


// För att kunna ångra
struct vara storageCopy[100];


// temporära variabler etc för de funktioner som endsat tillfälligt sparar data
size_t len = 0;
ssize_t readStuff;


// ----------------- FUNKTIONER -----------------


// Undersöker om en karaktär är en char
bool checkIfChar(answer)
{
    int i = 1;
    while (getchar() != '\n')
    {
        i++;
    }
    if (i == 1)
    {
        return true;
    }
    return false;
}


// Funktionen tar en input som måste vara en char annars får användaren skriva om
char getCharAdvanced()
{
    char ans;
    while (true)
    {
        scanf("%c",&ans); //Läser in svar från användaren
        if (checkIfChar(ans)) // true om det är en char
        {
            break;
        }
        printf("\nSka endast vara en bokstav. Skriv igen: ");
    }
    return ans;
}


// Undersöker om en lista med char innehåller endast siffror
bool checkIfInt(char *ans)
{
    long len = strlen(ans);
    int i;
    for (i=0; i < len; i++)
    {
        if (isdigit(ans[i])==false)
        {
            return false;
        }
    }
    return true;
}


// Funktionen tar en input som måste vara siffror annars får användaren skriva om
int getIntAdvanced()
{
    char answer[128];
    while (true) {
        scanf("%s", answer);
        while (getchar() != '\n');
        if (checkIfInt(answer) && (atoi(answer)>0))
        {
            return atoi(answer);
        }
        printf("\nOgilting inmatning. Måste vara ett positivt heltal: ");
    }
    return atoi(answer);
}


// Funktionen tar en input som måste vara siffror, f eller a annars får användaren skriva om
int getIntOrFAAdvanced()
{
    char answer[128];
    while (true)
    {
        scanf("%s", answer);
        while (getchar() != '\n');
        
        if (strncmp(answer, "f", 1) == 0 || strncmp(answer, "F", 1) == 0  )
        {
            return 500;
        }
        if (strncmp(answer, "a", 1) == 0 || strncmp(answer, "A", 1) == 0  )
        {
            return 501;
        }
        if (checkIfInt(answer) && (atoi(answer)>0))
        {
            return atoi(answer);
        }
        printf("\nOgilting inmatning. Måste vara ett positivt heltaleller a: ");
    }
    return atoi(answer);
}


//Funktion som kopierar lagerhyllan till "storageCopy"
void saveCopy()
{
  int i;
  for (i=0; i < 100; i++)
    {
      if (storage[i].price != 0) 
	{
	  storageCopy[i].name = malloc (1 + strlen (storage[i].name));
	  strncpy (storageCopy[i].name, storage[i].name, strlen(storage[i].name));
	  
	  storageCopy[i].description = malloc (1 + strlen (storage[i].description));
	  strncpy (storageCopy[i].description, storage[i].description, strlen(storage[i].description));
	  
	  storageCopy[i].shelf = malloc (1 + strlen (storage[i].shelf));
	  strncpy (storageCopy[i].shelf, storage[i].shelf, strlen(storage[i].shelf));
	  
	  storageCopy[i].price = storage[i].price;
	  storageCopy[i].antal = storage[i].antal;
	}      
      storageCopy[i] = storage[i];
    }
}


// Sparar en kopia som man kan återsätta med om användaren vill ångra
void useSavedCopy()
{
    int i;
    for (i=0; i < 100; i++)
    {
        storage[i] = storageCopy[i];
    }
}


// Skriver ut valen som användaren har
void printAlts()
{
    printf(" \n                                     \
           \n [L]ägga till en vara		  \
           \n [T]a bort en vara 	          \
           \n [R]edigera en vara		  \
           \n Ån[g]ra senaste ändringen 	  \
           \n Lista [h]ela varukatalogen	  \
           \n [A]vsluta				  \
           \n\n Vad vill du göra idag? _");
}


//Undersöker om lagerhyllan som användaren skriver in redan används av en annan vara
bool checkIfOccupied(char * tempShelf, char * tempName)
{
    int j;
    for(j=0; j<100; j++)
    {
        if (storage[j].shelf != NULL)
        {
            if (strcmp(storage[j].shelf, tempShelf) == 0 && strcmp(tempName, storage[j].name) != 0)
            {
                return true; // är upptagen
            }
        }
    }
    return false; // är inte upptagen
}


// För att få korrekt format på hyllan
char *getShelfCorrectFormat()
{
    char * shelf = NULL;
    while(true == true)
    {
        getline(&shelf, &len, stdin);
        long len = strlen(shelf);
        int i = 0;
        bool check = true;
        if (isalpha(shelf[0]) != 0)
        {
            if ((shelf[1]) == '\n')
            {
                check = false;
            }
            for (i=1; i < len; i++)
            {
                if ((isdigit(shelf[i])==false) && ((shelf[i]) != '\n'))
                {
                    check = false;
                }
            }
            if (check == true)
            {
                return shelf;
            }
        }
        printf("\nOgiltig inmatning. Skriv igen: ");
    }
}


// Funktionen tar en input som måste vara rätt formatoch ledig annars får användaren skriva om
char * getShelf(char * tempName)
{
    printf("\nSkriv in hylla i formatet 'BokstavTal': ");
    char * shelf = getShelfCorrectFormat();
    
    while (checkIfOccupied(shelf, tempName))
    {
        printf("\nPlatsen är upptagen. Skriv in en ny: "); //Säger till användaren skriva en ny plats om den är upptagen
        shelf = getShelfCorrectFormat(); //Läser in lagerhyllan igen
    }
    return shelf;
}


// Ändrar namnet på varan
void editName(char * currentName, int index)
{
    char * tName = NULL;
    printf (" \nNuvarande namn: %s", currentName);
    printf("\n-------------------------------------------------------- \nNytt namn: ");
    getline(&tName, &len, stdin);
    storage[index].name = malloc (1 + strlen (tName));
    strncpy (storage[index].name, tName, strlen(tName));
}


// Ändrar beskrivningen på varan
void editDesc(char * desc, int index)
{
    char * tempDesc = NULL;
    printf ("%s %s %s"," \nNuvarande beskrivning: ", desc, "\n--------------------------------------------------------\
            \nNy beskrivning: _");
    getline(&tempDesc, &len, stdin);
    storage[index].description = malloc (1 + strlen (tempDesc));
    strncpy (storage[index].description, tempDesc, strlen(tempDesc));
}


// Ändrar priset på varan
void editPrice(int price, int index)
{
    int tempPrice;
    printf ("%s %i %s %i %s"," \nNuvarande pris: ", price/100,",", price%100,
            "kr \n--------------------------------------------------------\
            \nNytt pris (i öre): _");
    tempPrice = getIntAdvanced();
    //while (tempPrice < 1);
    storage[index].price = tempPrice;
}


// Ändrar platsen på varan
void editShelf(char * shelf, int index, char * name)
{
    char * tempShelf = NULL;
    printf ("%s %s %s"," \nNuvarande hyllplats: ", shelf,
            "\n--------------------------------------------------------\
            \nNy hyllplats: _");
    tempShelf = getShelf(name);
    storage[index].shelf = malloc (1 + strlen (tempShelf));
    strncpy (storage[index].shelf, tempShelf, strlen(tempShelf));
}


// Ändrar antalet av varan
void editAmount(int amount, int index)
{
    int tempAmount;
    printf ("%s %i %s"," \nNuvarande antal: ", amount,
            "\n--------------------------------------------------------\
            \nNytt antal: _");
    tempAmount = getIntAdvanced();
    while (tempAmount < 1);
    storage[index].antal = tempAmount;
}


// Listar egenskaperna hos den valda varan
void showProductsDetails(int arrayIndex)
{
    printf("Namn: %s", storage[arrayIndex].name);
    printf("Beskrivning: %s", storage[arrayIndex].description);
    printf("Pris: %d %s %d kr \n", (storage[arrayIndex].price/100), ",", (storage[arrayIndex].price%100));
    printf("Lagerhylla: %s", storage[arrayIndex].shelf);
    printf("Antal: %d \n", storage[arrayIndex].antal);
}


int ChooseItem()
{
    int i = 0, loops = 0, tempAnswer = 0;
    bool inStorage = true;
    do
    {
        loops += 20;
        while(i<loops && storage[i].price > 0)
        {
            printf("%i %s %s", (i+1)%20, storage[i].name, "\n");
            i++;
        }
        if ( i < 90 && storage[i+1].price > 0)
        {
            printf("Vill du se [f]ler varor, visa en vara igenom att skriva varans nummer eller [a]vsluta?\n");
        }
        else
        {
            printf("Välj en vara genom att skriva varans nummer eller [a]vsluta?\n");
        }
        inStorage = true;
        while (inStorage)
        {
            tempAnswer = getIntOrFAAdvanced();
            
            if ((tempAnswer < 500) && (storage[(tempAnswer-1)].price < 1))
            {
                printf("\nVaran finns inte i lager. Välj en annan: ");
            }
            else
            {
                inStorage = false;
            }
        }
    } while (tempAnswer == 500);
    
    if (tempAnswer == 501)
    {
        return -1;
    }
    
    if (tempAnswer > 0)
    {
        showProductsDetails(tempAnswer-1);
        return (tempAnswer-1);
    }
    return -1;
}


//Visar de val som användaren kan ändra
void printEditOptions()
{
    printf("\n [N]amn			      \
           \n [B]eskrivning		      \
           \n [P]ris			      \
           \n [L]agerhylla		      \
           \n An[t]al			      \
           \n				      \
           \n Välj vad du vill ändra eller [a]vbryt: ");
}


// Definieras här så att den kan användas
bool addEditDelete(char * tempName, char * tempDesc, int tempPrice, char * tempShelf, int tempAmount, bool canUseUndo);


// Läser in valet från användaren
char editWhich()
{
    char whatToEdit = getCharAdvanced(); // Läser in svaret på vilken rad som ska ändras
    bool looping = true;
    while (looping) // Loopar om input är ogiltigt
    {
        switch(whatToEdit)
        {
            case 'N':
            case 'n': return 'n';
            case 'B':
            case 'b': return 'b';
            case 'P':
            case 'p': return 'p';
            case 'L':
            case 'l': return 'l';
            case 'T':
            case 't': return 't';
            case 'A':
            case 'a': return 'a';
            default:
                printf("Felaktig input, försök igen: ");
                whatToEdit = getCharAdvanced();
        }
    }
    return 'a';
}


// Ändrar en vara
bool editItem (bool canUseUndo)
{
    printf("\n\n------ Du har valt att ändra en vara ------\n");
    
    if (storage[0].price < 1)
    {
        printf("\nDet finns inga varor i lagret.\n");
        return true;
    }
    int index = ChooseItem();
    
    if (index == -1)
    {
        return true;
    }
    
    char * name = storage[index].name; // varan på det valda indexet(s adress) kopieras till
    char * desc = storage[index].description; // en gemensam variabel för både redigera från
    int price = storage[index].price; // lägga till en vara och ändra en vra i storage
    char * shelf = storage[index].shelf;
    int amount = storage[index].antal;
    
    printEditOptions();
    char whatToEdit = editWhich();
    switch(whatToEdit)
    {
        case 'n': // ändra namnet
            saveCopy();
            canUseUndo = true;
            editName(name, index);
            break;
        case 'b': // ändra beskrivningen
            saveCopy();
            canUseUndo = true;
            editDesc(desc, index);
            break;
        case 'p':  // ändra pris
            saveCopy();
            canUseUndo = true;
            editPrice(price, index);
            break;
        case 'l': //ändra hylla
            saveCopy();
            canUseUndo = true;
            editShelf(shelf, index, name);
            break;
        case 't':
            saveCopy();
            canUseUndo = true;
            editAmount(amount, index);
            break;
        default: break; // Avslutar funktionen
    }
    return canUseUndo;
}


// Lägger till den valda varan
void addItem(char * tempName, char * tempDesc, int tempPrice, char * tempShelf, int tempAmount)
{
    int i;
    for(i=0; i<100; i++) // Loop för att hitta första tomma plats
    {
        if (storage[i].price == 0 || strcmp(tempName, storage[i].name) == 0)
        {
            storage[i].name = malloc (1 + strlen (tempName));
            strncpy (storage[i].name, tempName, strlen(tempName));
            storage[i].description = malloc (1 + strlen (tempDesc));
            strncpy (storage[i].description, tempDesc, strlen(tempDesc));
            storage[i].price = tempPrice;
            storage[i].shelf = malloc (1 + strlen (tempShelf));
            strncpy (storage[i].shelf, tempShelf, strlen(tempShelf));
            storage[i].antal += tempAmount;
            break;
        }
    }
}


// Ändrar temporärt den nya varan
bool changeBeforeAdd (char * tempName, char * tempDesc, int tempPrice, char * tempShelf, int tempAmount, bool canUseUndo)
{
    printEditOptions();
    char whatToEdit = editWhich();
    switch(whatToEdit)
    {
        case 'n':
            printf("\nSkriv in det nya namnet: ");
            do
            {
                getline(&tempName, &len, stdin);
                
                if (&tempName == NULL || (tempName[0] == '\n'))
                {
                    printf("Felaktig input, försök igen\n");
                }
            } while(&tempName == NULL || (tempName[0] == '\n'));
            break;
            
        case 'b':
            printf("\nSkriv in den nya beskrivningen: ");
            do
            {
                getline(&tempDesc, &len, stdin);
            } while(&tempDesc != NULL && (tempDesc[0] == '\n'));
            break; // ändra beskrivningen
            
        case 'p':
            printf("\nSkriv in det nya priset (i öre): ");
            tempPrice = getIntAdvanced();
            break; // ändra pris
            
        case 'l':
            tempShelf = getShelf(tempName);
            break; //ändra hylla
            
        case 't':
            printf("\nSkriv in antal: ");
            tempAmount = getIntAdvanced();
            break; //ändra antal
            
        default:
            break; // Går ut ur loopen
    }
    return addEditDelete(tempName, tempDesc, tempPrice, tempShelf, tempAmount, canUseUndo);
}

bool addEditDelete(char * tempName, char * tempDesc, int tempPrice, char * tempShelf, int tempAmount, bool canUseUndo){
    char toDo;
    bool whatToDo = true;
    while (whatToDo) // Loopar om input är fel eller om användaren valt att redigera
    {
        printf("\nVill du lägga till varan [J]a/[N]ej, eller [R]edigera varan? ");
        toDo = getCharAdvanced();
        switch (toDo)
        {
            case 'J':
            case 'j':
                saveCopy();
                canUseUndo = true;
                addItem(tempName, tempDesc, tempPrice, tempShelf, tempAmount);
                whatToDo = false;
                break;
            case 'N':
            case 'n': whatToDo = false; break;
            case 'R':
            case 'r': canUseUndo = changeBeforeAdd(tempName, tempDesc, tempPrice, tempShelf, tempAmount, canUseUndo); whatToDo = false; break;;
        }
    }
    return canUseUndo;
}

//Funktion för att lägga till en vara
bool add(bool canUseUndo)
{
    char * tempName = NULL;
    char * tempDesc = NULL;
    int tempPrice;
    char * tempShelf = NULL;
    int tempAmount;
    
    printf("\n\n------ Du har valt att lägga till en vara ------\n");
    
    printf("\nSkriv in namn: ");
    do {
        getline(&tempName, &len, stdin);
    } while(&tempName != NULL && (tempName[0] == '\n'));//Läser in namnet på varan
    
    printf("\nSkriv in beskrivning: ");
    do {
        getline(&tempDesc, &len, stdin);
    } while(&tempDesc != NULL && (tempDesc[0] == '\n')); //Läser in descriptionen på varan
    
    printf("\nSkriv in pris (i öre): ");
    tempPrice = getIntAdvanced();
    
    tempShelf = getShelf(tempName); // Läser in hyllan från användaren och att det blir giltig input
    
    printf("\nSkriv in antal: ");
    tempAmount = getIntAdvanced();
    
    return(addEditDelete(tempName, tempDesc, tempPrice, tempShelf, tempAmount, canUseUndo));
}


//Funktion som tar bort en vara
void soLongNthxForFish(int toBeDeleted){
    storage[toBeDeleted].name = NULL;
    storage[toBeDeleted].description = NULL;
    storage[toBeDeleted].price = 0;
    storage[toBeDeleted].shelf = NULL;
    storage[toBeDeleted].antal = 0;
}


//Funktion som tar bort vara samt sorterar
bool popItem(){
    printf("\n\n------ Du har valt att ta bort en vara ------\n");
    
    if (storage[0].price < 1)
    {
        printf("\nDet finns inga varor i lagret.\n\n");
        return true;
    }
    
    int toBeDeleted = ChooseItem();
    if (toBeDeleted == -1)
    {
        return true;
    }
    bool looping1 = true;
    while (looping1)
    {
        printf("\nVill avbryta? J/N: ");
        char answer = getCharAdvanced();
        switch(answer)
        {
            case 'J':
            case 'j': return 0;
            case 'N':
            case 'n':
                looping1 = false;
                break;
            default: printf("Felaktig input, försök igen\n");
        }
    }
    
    saveCopy();
    while (toBeDeleted < 100 && storage[toBeDeleted+1].price > 0)
    {
        storage[toBeDeleted].name = malloc (1 + strlen (storage[toBeDeleted+1].name));
        strncpy (storage[toBeDeleted].name, storage[toBeDeleted+1].name, strlen(storage[toBeDeleted+1].name));
        storage[toBeDeleted].description = malloc (1 + strlen (storage[toBeDeleted+1].description));
        strncpy (storage[toBeDeleted].description, storage[toBeDeleted+1].description, strlen(storage[toBeDeleted+1].description));
        storage[toBeDeleted].price = storage[toBeDeleted+1].price;
        storage[toBeDeleted].shelf = malloc (1 + strlen (storage[toBeDeleted+1].shelf));
        strncpy (storage[toBeDeleted].shelf, storage[toBeDeleted+1].shelf, strlen(storage[toBeDeleted+1].shelf));
        storage[toBeDeleted].antal = storage[toBeDeleted+1].antal;
        toBeDeleted++;
        soLongNthxForFish(toBeDeleted);
    }
    soLongNthxForFish(toBeDeleted);
    return true;
}


//Funktion som ångrar användarens senaste handling
bool undo(bool canUseUndo)
{
    printf("\n\n------ Du har valt att ångra senaste ändringen ------\n");
    if (canUseUndo)
    {
        useSavedCopy();
        printf("\nÅngrat.\n\n");
        return false;
    }
    else
    {
        printf("\nFinns inget att ångra.\n\n");
    }
    return true;
}


// Funktion som visar varorna i en lista
int showProducts() //
{
    printf("\n\n------ Du har valt att se alla varor ------\n");
    
    if (storage[0].price < 1)
    {
        printf("\nDet finns inga varor i lagret.\n\n");
        return -1;
    }
    
    printf("\nDet här är produkterna:\n\n");
    return ChooseItem(); //indexnumret
}


// Funktion som avslutar programmet om önskas
int endProgram()
{
    while (true)
    {
        printf("\nVill du verkligen avsluta? J/N: ");
        char answer = getCharAdvanced();
        switch(answer)
        {
            case 'J':
            case 'j':  exit(0); // Avslutar programmet normalt
            case 'N':
            case 'n': return 0;
            default: printf("Felaktig input, försök igen\n");
        }
    }
}

// Funktion som avgör vad användaren vill göra och använder rätt funktion för det
bool changeStorage(char alts, bool canUseUndo)
{
    switch(alts)
    {
        case 'L':
        case 'l': canUseUndo = add(canUseUndo); break;
        case 'T':
        case 't': canUseUndo = popItem(); break;
        case 'R':
        case 'r': canUseUndo = editItem(canUseUndo); break;
        case 'G':
        case 'g': canUseUndo = undo(canUseUndo); break;
        case 'H':
        case 'h': showProducts(); break;
        case 'A':
        case 'a': endProgram(); break;
        default: printf("Felaktig input, försök igen\n");
    }
    return canUseUndo;
}



// ---------------- MAIN -----------------


//Det här är mainfunktionen som loopar tills användaren väljer att avsluta programmet
int main()
{
    int i;
    for (i = 0; i <100; i++)
    {
        storage[i].antal = 0;
        storageCopy[i].antal = 0;
    }
    bool canUseUndo = false;
    char alternative = 'o';
    printf("\n\nVälkommen till storagehantering 1.0 \n=================================\n");
    
    while (alternative != 'A') //Loopar tills användaren vill avsluta
    {
        printf("-------------------------------\n");
        printf("\nValmöjligheter:\n");
        printAlts(); //Skriver ut alternativen
        alternative = getCharAdvanced(); //Läser in svar från användaren
        canUseUndo = changeStorage(alternative, canUseUndo); //Gör den önskvärda ändringen
    }
    return 0;
}
