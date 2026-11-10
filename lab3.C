#include <stdio.h>
#include <string.h>

#define MAX 100

// Structure to store song information
struct Song
{
    char singer[100];
    char name[100];
    float price;
    int year;
};

// Function declarations
int enterData(struct Song songs[], int count);
void saveData(struct Song songs[], int count);
int readData(struct Song songs[]);
void sortSongs(struct Song songs[], int count);
void printCatalogue(struct Song songs[], int count);


int main()
{
    struct Song songs[MAX];
    int count = 0;
    int choice;

    // Display menu until user chooses to exit
    do
    {
        printf("\n--- SONG CATALOGUE ---\n");
        printf("1. Enter data\n");
        printf("2. Save data to file\n");
        printf("3. Read data from file\n");
        printf("4. Print catalogue\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        getchar();

        // Select menu option
        switch(choice)
        {
            case 1:
                count = enterData(songs, count);
                break;

            case 2:
                saveData(songs, count);
                break;

            case 3:
                count = readData(songs);
                break;

            case 4:
                sortSongs(songs, count);
                printCatalogue(songs, count);
                break;

            case 5:
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 5);

    return 0;
}


// Function to enter song information
int enterData(struct Song songs[], int count)
{
    int number;

    printf("How many songs do you want to enter? ");
    scanf("%d", &number);
    getchar();

    for(int i = 0; i < number && count < MAX; i++)
    {
        printf("\nEnter band/singer: ");
        fgets(songs[count].singer, 100, stdin);
        songs[count].singer[strcspn(songs[count].singer, "\n")] = '\0';

        printf("Enter song name: ");
        fgets(songs[count].name, 100, stdin);
        songs[count].name[strcspn(songs[count].name, "\n")] = '\0';

        printf("Enter price: ");
        scanf("%f", &songs[count].price);

        printf("Enter release year: ");
        scanf("%d", &songs[count].year);
        getchar();

        count++;
    }

    return count;
}


// Function to save songs to a file
void saveData(struct Song songs[], int count)
{
    FILE *file;

    file = fopen("catalogue.txt", "w");

    if(file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    for(int i = 0; i < count; i++)
    {
        fprintf(file, "%s|%s|%.2f|%d\n",
        songs[i].singer,
        songs[i].name,
        songs[i].price,
        songs[i].year);
    }

    fclose(file);

    printf("Songs saved successfully.\n");
}


// Function to read songs from a file
int readData(struct Song songs[])
{
    FILE *file;
    int count = 0;

    file = fopen("catalogue.txt", "r");

    if(file == NULL)
    {
        printf("File could not be opened.\n");
        return 0;
    }

    while(count < MAX &&
    fscanf(file, "%99[^|]|%99[^|]|%f|%d\n",
    songs[count].singer,
    songs[count].name,
    &songs[count].price,
    &songs[count].year) == 4)
    {
        count++;
    }

    fclose(file);

    printf("%d songs read from file.\n", count);

    return count;
}


// Function to sort songs by release year
void sortSongs(struct Song songs[], int count)
{
    struct Song temp;

    for(int i = 0; i < count - 1; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            if(songs[j].year > songs[j + 1].year)
            {
                temp = songs[j];
                songs[j] = songs[j + 1];
                songs[j + 1] = temp;
            }
        }
    }
}


// Function to print the catalogue
void printCatalogue(struct Song songs[], int count)
{
    for(int i = 0; i < count; i++)
    {
        printf("\nName of Band: %s\n", songs[i].singer);
        printf("Name of Song: %s\n", songs[i].name);
        printf("Price: %.2f\n", songs[i].price);
        printf("Year of Release: %d\n", songs[i].year);
    }
}

The Song Catalogue program is written in C and allows the user to enter, save, retrieve, sort and display information about songs.
 At the beginning of the program, the stdio.h and string.h libraries are included to allow the use of input, output and string functions. A constant called MAX is set to 100, which limits the catalogue to 100 songs.
 A structure called Song is created to store four pieces of information about each song: the band or singer's name, the song title, the price and the release year. An array of these structures is then created in the main function to store multiple songs.
  The program uses a do-while loop to repeatedly display a menu containing five options, allowing the user to enter data, save data to a file, read data from a file, print the catalogue or exit the program. A switch statement is used to identify the option selected by the user and call the appropriate function. 
  The enterData() function allows the user to input the band or singer, song name, price and release year using fgets() and scanf(). The information is stored in the song array, and a counter is increased each time a new song is entered. The saveData() function uses fopen() to open a file called catalogue.txt in write mode and fprintf() to save the song information.
   Once all the songs have been saved, fclose() closes the file.
   The readData() function opens the same file in read mode and uses fscanf() to retrieve the saved information and place it back into the song array. It also increases the counter each time a song is successfully read. The sortSongs() function uses a sorting method called bubble sort to arrange the songs from the oldest release year to the newest. 
   It compares neighbouring songs and swaps them if they are in the wrong order, using a temporary structure to hold information during the swap. Finally, the printCatalogue() function uses a for loop to display each song's information on the screen, including the band or singer, song title, price and release year.
    Overall, the program uses structures, arrays, functions, loops, conditional statements and file handling to create a simple song catalogue that allows users to manage and organise song information.