#include <stdio.h>
#include <string.h>

#define MAX 100 //maximum number of songs that can be stored in the catalogue


struct Song //stores information about a song, including the band/singer, song name, price, and release year
{
    char singer[100], name[100];
    float price;
    int year;
};

int enterData(struct Song songs[], int count); //initialising the enterData function
void saveData(struct Song songs[], int count); //initialising the saveData function
int readData(struct Song songs[]); //initialising the readData function
void sort(struct Song songs[], int count); //initialising the sort function
void print(struct Song songs[], int count); //initialising the print function


int main() //main function that runs the program
{
    struct Song songs[MAX]; //array of Song structures to store the song information
    int count = 0; //counter to keep track of the number of songs entered
    int choice; //variable to store the user's menu choice


    do //do-while loop to repeatedly display the menu and process user input
    {
        printf("\n--- SONG CATALOGUE ---\n"); //displaying the menu options to the user
        printf("1. Enter data\n");
        printf("2. Save data\n");
        printf("3. Read data\n");
        printf("4. Print info\n");
        printf("5. Exit\n");
        printf("USER INPUT: \n");

        scanf("%d", &choice); //reading the user's menu choice
        getchar(); 

        switch(choice) //switch statement to process the user's menu choice
        {
            case 1: //if the user chooses to enter data, call the enterData function and update the count variable
                count = enterData(songs, count);
                break;

            case 2:
                saveData(songs, count); //call the saveData function to save the song information to a file
                break;

            case 3:
                count = readData(songs); //call the readData function to read the song information from a file and update the count variable
                break;

            case 4:
                sort(songs, count); //call the sort function to sort the song information by release year
                print(songs, count); //call the print function to display the song information on the screen
                break;

            case 5:
                printf("Exitting program\n"); //if the user chooses to exit, display a message and break out of the loop
                break;

            default:
                printf("Invalid choice.\n"); //if the user enters an invalid choice, display an error message
        }

    } while(choice != 5); //continue looping until the user chooses to exit

    return 0; //return 0 to indicate successful program execution
}



int enterData(struct Song songs[], int count) //function to allow the user to enter song information
{ 
    int number;

    printf("How many songs do you want to enter? "); //prompt the user to enter the number of songs they want to input
    scanf("%d", &number); 
    getchar(); 

    for(int i = 0; i < number && count < MAX; i++) //loop to allow the user to enter information for the specified number of songs, up to the maximum limit
    {
        printf("\nEnter band/singer: "); //prompt the user to enter the band/singer name
        fgets(songs[count].singer, 100, stdin); //read the band/singer name from the user input
        songs[count].singer[strcspn(songs[count].singer, "\n")] = '\0'; //remove the newline character from the end of the string

        printf("Enter song name: ");
        fgets(songs[count].name, 100, stdin); //read the song name from the user input
        songs[count].name[strcspn(songs[count].name, "\n")] = '\0'; //remove the newline character from the end of the string

        printf("Enter price: "); //prompt the user to enter the price of the song
        scanf("%f", &songs[count].price); //read the price from the user input

        printf("Enter release year: "); //prompt the user to enter the release year of the song
        scanf("%d", &songs[count].year); //read the release year from the user input
        getchar(); //consume the newline character left in the input buffer

        count++; //increment the count variable to keep track of the number of songs entered
    }

    return count; //return the updated count variable to the main function
}


void saveData(struct Song songs[], int count) //function to save the song information to a file
{
    FILE *file; //pointer to a file structure to handle file operations

    file = fopen("catalogue.txt", "a"); //open the file "catalogue.txt" in append mode to add new song information without overwriting existing data

    if(file == 0) //check if the file was opened successfully
    {
        printf("Error opening file.\n");
        return;
    }

    for(int i = 0; i < count; i++) //loop to write the song information to the file for each song in the array
    {
        fprintf(file, "%s|%s|%.2f|%d\n", //write the band/singer name, song name, price and release year to the file in a specific format
        songs[i].singer,
        songs[i].name,
        songs[i].price,
        songs[i].year); 
    }

    fclose(file); //close the file after writing the song information

    printf("Songs saved successfully.\n");
}


int readData(struct Song songs[]) //function to read the song information from a file
{
    FILE *file; //pointer to a file structure to handle file operations
    int count = 0; //counter to keep track of the number of songs read from the file

    file = fopen("catalogue.txt", "r"); //open the file "catalogue.txt" in read mode to retrieve the song information

    if(file == 0) //check if the file was opened successfully
    {
        printf("File could not be opened.\n");
        return 0;
    }

    while(count < MAX && //fscanf() reads the song information from the file and stores it in the corresponding fields of the Song structure
    fscanf(file, "%99[^|]|%99[^|]|%f|%d\n", //
    songs[count].singer,
    songs[count].name,
    &songs[count].price,
    &songs[count].year) == 4) //check if fscanf() successfully read all four fields of the Song structure
    {
        count++; //increment the count variable to keep track of the number of songs read from the file
    }

    fclose(file); //close the file after reading the song information

    printf("%d songs read from file.\n", count); //display the number of songs read from the file to the user

    return count;
}


void sort(struct Song songs[], int count) //function to sort the song information by release year using bubble sort algorithm
{
    struct Song temp; //temporary variable to hold a Song structure during the swapping process

    for(int i = 0; i < count - 1; i++)  //outer loop to iterate through the array of songs
    {
        for(int j = 0; j < count - i - 1; j++) //inner loop to compare adjacent songs and swap them if they are in the wrong order
        {
            if(songs[j].year > songs[j + 1].year) //compare the release year of the current song with the next song
            {
                temp = songs[j]; //swap the two songs if they are in the wrong order
                songs[j] = songs[j + 1]; //swap the current song with the next song
                songs[j + 1] = temp; //swap the next song with the temporary variable to complete the swap
            } 
        }
    }
}


void print(struct Song songs[], int count) //function to display the song information on the screen
{
    for(int i = 0; i < count; i++) //loop to iterate through the array of songs and print the information for each song
    {
        printf("\nName of Band: %s\n", songs[i].singer);
        printf("Name of Song: %s\n", songs[i].name);
        printf("Price: %.2f\n", songs[i].price);
        printf("Year of Release: %d\n", songs[i].year);
    }
}







