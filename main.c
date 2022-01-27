#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define DATA_SIZE 1000

//FUNCTION DECLARATIONS
void passwordCreate(); 
void passwordRead();
void mainMenu();
//void storeNewPassword();
void deletePassword();
void updatePassword();


//GLOBAL VARIABLE DECLARATIONS
FILE *ptr_storage = NULL;
char data[DATA_SIZE];
//HERE'S MAIN JOHNNY
int main() {
	mainMenu();
	
}//mains ending bracket

void mainMenu() {
	int userInput;
	printf("\n--------WELCOME TO PASSWORD STORAGE----------\n\n");
	printf(" New password entry:      <1>\n");
	printf(" View existing passwords: <2>\n");
	printf(" Delete passwords:        <3>\n");
	printf(" Update passwords:        <4>\n\n");
	printf("-----------------------------------------------\n");
	printf(" Please enter a selection: ");
	scanf_s("%d", &userInput);
	
	//big ol' switch statement that routes to appropriate function based on the user input
	switch(userInput) {
		case 1:
			fflush(stdin);
			system("cls");
			passwordCreate();
			break;
		case 2: 
			fflush(stdin);
			system("cls");
			passwordRead();
			break;
		case 3: 
			fflush(stdin);
			system("cls");
			deletePassword();
			break;
		case 4: 
			fflush(stdin);
			system("cls");
			updatePassword();
			break;
		default: 
			fflush(stdin);
			system("cls"); 
			printf("Invalid selection, please try again.\n");
			mainMenu();
	}
	
}

//the password create function
void passwordCreate() {
	//declareth the variables
	char passwordSite[50];
	char userId[50];
	char password[50];
	
	
	//GET NAME OF SITE FROM USER
	printf("\nWhat site is this password for?:");
	scanf_s("%s", &passwordSite);//get site from user and store in passwordsite var
	ptr_storage = fopen("storage.txt", "a");//open this file in append mode. Will always add to end of file
	
	//error check
	if(ptr_storage == NULL) {
		printf("Unable to create file.\n");
		exit(EXIT_FAILURE);
	}
	fprintf(ptr_storage, "Site: %-16s ", passwordSite);//print site to opened file; formatted correctly
	fflush(stdin);
	fclose(ptr_storage);//close file
	
	
	//GET USER ID FROM USER
	printf("What is the User Id for this site?:");//get user id from user
	scanf_s("%s", &userId);//store in userId var
	ptr_storage = fopen("storage.txt", "a");//open file in append mode
	
	//error check
	if(ptr_storage == NULL) {
		printf("Unable to create file.\n");
		exit(EXIT_FAILURE);
	}
	
	fprintf(ptr_storage, "UserID: %-16s ", userId);//print formatted user id to file
	fflush(stdin);
	fclose(ptr_storage);//close file
	
	
	//GET PASSWORD FROM USER
	printf("What is the password for this site?:");//get password from user
	scanf_s("%s", &password);//store to password var
	ptr_storage = fopen("storage.txt", "a");//open file in append mode
	
	//error check
	if(ptr_storage == NULL) {
		printf("Unable to create file.\n");
		exit(EXIT_FAILURE);
	}
	fprintf(ptr_storage, "Password: %-16s\n", password);//write formatted password to file. This is the only one with a \n char.
	fflush(stdin);
	fclose(ptr_storage);//close file
	
	
	
	//OUTPUT VALUES TO CONSOLE AS CONFIRMATION
	printf("\nNew entry added as follows....\n");
	printf("-----------------------------------------------\n");
	printf("Site name: %s\n", passwordSite);
	printf("Site User Id: %s\n", userId);
	printf("Site password: %s\n", password);
	printf("-----------------------------------------------\n");
	
	mainMenu();//return to main menu
	
}//end of passwordCreate function


//SHOW ALL EXISTING PASSWORDS/PASSWORD READ
void passwordRead() {
	printf("\n********************STORED PASSWORDS********************\n\n");
	FILE *ptr_read_file; //creating a read file pointer....always a pointer
	char temp[100];//temp variable to hold each line
	ptr_read_file = fopen("storage.txt", "r"); //this is our file to read from
	
	while(!feof(ptr_read_file)){//while its not the end of the file
		if(fgets(temp, 100, ptr_read_file)!= NULL){//if the file isn't null
			puts(temp);//print the data to the screen
		}
	}//end of while loop
	
	fclose(ptr_read_file); //close the file for reading
	mainMenu();//call the mainMenu() function to select from menu again
		
	}//end of passwordRead() function
	
//DELETE PASSWORD FUNCTION
void deletePassword() {
		int lno; //line number that user wants removed
		char ch;//variable that will copy each char from the file into the new file
		int temp3 = 1;//line variable that we will compare the user deletion line too. Starts at line 1
		FILE *ptr_read_file, *ptr_write_file; //our read in and read out file pointers
		char temp2[DATA_SIZE], temp[] = "temp.txt";//data storage buffer and temp file
		printf("\nWhich site would you like to delete from the list (Enter the number)?\n");
		printf("\n----------------------------------------------------------\n");
		ptr_read_file = fopen("storage.txt", "r");//open the file for reading
		
		//display the passwords to the screen with a number to choose from
		int counter = 1; //used to add a line number to the passwords
		while(!feof(ptr_read_file)){//while its not the end of the file
			if(fgets(temp2, 100, ptr_read_file)!= NULL){//if the line is not null
				printf("%d: ", counter);//print this here
				puts(temp2);//then print this here
				counter ++;//update the counter
			}
		}//end of while loop
		fclose(ptr_read_file); //close the file for reading for display
		printf("----------------------------------------------------------\n");
		
		scanf("%d", &lno);//get line to remove from user
		
		if(lno > counter - 1 || lno < 1){//if user enters invalid number value
			printf("\nInvalid Selection, please try again.\n\n");
			mainMenu();
		}
		
		ptr_read_file = fopen("storage.txt", "r");//open up the file to read from for deletion
		ptr_write_file = fopen(temp, "w");//open up the file to copy to for deletion
		
		ch = getc(ptr_read_file);//gonna go get them there chars from the read file
		
		while(ch != EOF) {//while the char is not the EOF character, which is like this y shaped wierdness, or a 0xFF
			
			if(temp3 != lno && ch != EOF) {//do not print the line number OR the EOF char
					putc(ch, ptr_write_file);//print each char to the temp file
			}
			if(ch == '\n') {//this must come after the lno check, so that entry 1 can be deleted if chosen
				temp3++;//here is where we update the counter. Basically, only update it if we encounter a new line. Cause....cause it's a new line counter
			}
			ch = getc(ptr_read_file);//read each char from the original file
		}
		//close both of the files read and write
		fclose(ptr_read_file);
		fclose(ptr_write_file);
		//delete the original storage file, then rename the temp file to storage file name.
		remove("storage.txt");
		rename("temp.txt", "storage.txt");
		system("cls"); //clear the screen
		printf("\n***************PASSWORD DELETED***************\n");
		mainMenu();//go back to main menu 
	}//end of delete password function
	

//UPDATE PASSWORD FUNCTION
void updatePassword() {
	//create the file pointers that we are going to reuse SEVERAL times
	FILE *ptr_open;
	FILE *write_file;
	
	//file to open in read mode; r+ will create the file if it doesn't exist
	ptr_open = fopen("storage.txt", "r+");
	
	//error check
	if(ptr_open == NULL) {
		printf("Failed to open file\n");
		exit(EXIT_FAILURE);
	}
	
	//display the choices to the screen
	printf("-----------------------STORED DATA-----------------------\n");
	printf("----------------------------------------------------------\n");
	char temp2[DATA_SIZE]; //data buffer for files
	char oldWord[DATA_SIZE];//old word variable
	char newWord[DATA_SIZE];//new word variable
	char read[100];//file buffer for second while loop
	int counter = 1; //used to add a line number to the passwords
		while(!feof(ptr_open)){//while its not the end of the file
			if(fgets(temp2, 100, ptr_open)!= NULL){
				printf("%d: ", counter);
				puts(temp2);
				counter ++;
			}
		}//end of while loop
		fclose(ptr_open); //close the file for reading for display
		printf("----------------------------------------------------------\n");
		printf("\nWhich word would you like to update: ");
		scanf("%s", &oldWord); //get word to replace
		fflush(stdin);
		printf("\nWhat is the new word: "); //get new word
		scanf("%s", &newWord);
		fflush(stdin);
		
		//open file to read from and file to write too
		ptr_open = fopen("storage.txt", "r+");//open for read/write
		write_file = fopen("temp.txt", "w+");//open for read/write; create if doesn't exist
		
		//error check
		if(ptr_open == NULL || write_file == NULL){
			printf("File cannot be opened");
			exit(0);
		}
		
		//comparing the word with the file **this does not read blank spaces, so we have to format
		int wordCounter = 1;//create a comparison counter for while loop
		while(!feof(ptr_open)){//while not end of file
			fscanf(ptr_open, "%s", read);//this is scanning for strings, not chars. So it's using the space or \n as a delimiter
			if(strcmp(read, oldWord) == 0) {//if the word read is the same as the old word
				strcpy(read, newWord);//replace it with the new word
			}
			
			if(wordCounter % 2 == 0){//if word counter is divisible by two (we only want every second word stored in the temp file)
				fprintf(write_file, "%s ", read);//print the value of read to the new file
			}
			
			wordCounter++;//increment our counter
		}
		//close the read and write files
		fclose(ptr_open);
		fclose(write_file);
		
		//CREATE THE FINAL FORMATTED FILE
		//open two files; one for reading from and one for writing too
		ptr_open = fopen("temp.txt", "r+");
		write_file = fopen("temp2.txt", "w+");
		char read2[100];//our buffer to hold each word
		int whereCounter = 1;//our counter for the while loop starts at the first line
		//rewind(ptr_open);
		while(1){//oh snap.....an infinite loop. I know, i know. There is a break below
			fscanf(ptr_open, "%s", read2);//start reading each word
			if(feof(ptr_open)){//haha, here is the break. Sadly, i cannot do this in the while condition, or it will print the last word twice
				break;
			}
			//well this is something, isn't it. The formatted file is in 3 column chunks. So, we need to take each
			//word from the temp file, and determine it's position based on the number three. This was my solution. You
			//got somthing better, hit me up.
			if((whereCounter + 2) % 3 == 0) {//if the counter + 2 is divisible by 3, we know its column one
				fprintf(write_file, "Site: %-16s ", read2);//add the formatting and write to the new file
			}else if((whereCounter + 1) % 3 == 0){//if the counter + 1 is divisible by 3, we know its column two
				fprintf(write_file, "UserID: %-16s ", read2);//add the formatting and write to the new file
			}else {//if neither, it's column three
				fprintf(write_file, "Password: %-16s \n", read2);//add the formatting and write to the new file
			}
			whereCounter++;//increment the counter
		}
		//close the files
		fclose(ptr_open);
		fclose(write_file);
		//delete the temp files and rename temp2 to storage
		remove("storage.txt");
		remove("temp.txt");
		rename("temp2.txt", "storage.txt");
		//return to the main menu
		mainMenu();

}//end of update password function

