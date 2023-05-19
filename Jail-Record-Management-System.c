
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char name[50];
	char code[30];
    int age;
    char sex[2];
    char crime[30];
    char contact[12];
    int sentBD_M, sentBD_D, sentBD_Y;
    int sentMM, sentDD, sentYY;
} records;

records criminal[100];

//Total Record
int nOfRecords;
//Current Year
int currentY;
//Prototypes
void read();
void write();

void addRecord();
void updateRecord();
void viewRecord();
void deleteOption();
void summary();
void backupRecord();

void viewCode();
void viewCrime();
void viewContact();
void viewDate();
void viewSex();
void viewBirth();

//Login
void login();
void guard();
void currentYY();
void exitmsg();
int mainmenu(void);

int main(void) {
	
	read();
    login();
    currentYY();
    mainmenu();
}
void currentYY(){
	int validY=0;
	printf("\n");
    printf("=========================================================================\n");
    do{
	printf("\n");	
	printf("\t\t\t Enter Current Year:");
	int args = scanf("%d", &currentY);
	    if (args < 1) {
	    // Display an error message
	    char dummy;
	    scanf("%s", &dummy);  // eats a character off the buffer
	    printf("-- Please enter a correct Year: \n");
	    }
		else if (currentY<= 3000 && currentY  >= 1800){
			validY=1;
		}
		 if (validY==0){
		printf("-- Please enter a correct Year: \n"); 	
		}
	}while (validY==0);
	
		
}

int mainmenu(void) {
	
    char choice;
    while(1) {
    	printf("\n");
    	printf("=========================================================================\n");
        printf("\n");
        printf("\t\t Jail Record Management System Year %d \n",currentY);
        printf("\t\t\t[ Number of Records: %d ]\n", nOfRecords);
        printf("\n");
        printf("\t\t\t1. Add Record\n");
        printf("\t\t\t2. Update Record\n");
        printf("\t\t\t3. View/Search Record\n");
        printf("\t\t\t4. Delete Record\n");
        printf("\t\t\t5. Record Summary\n");
        printf("\t\t\t6. Backup Records\n");
        printf("\t\t\t7. Exit\n");

        printf("\n");
        printf("Enter your choice : ");
        scanf("%s", &choice);
        fflush(stdin);

        switch(choice) {
            case '1':
                addRecord();
                break;
            case '2':
                updateRecord();
                break;
            case '3':
                viewRecord();
                break;
            case '4':
                deleteOption();
                break;
            case '5':
                summary();
                break;
            case '6':
                backupRecord();
                break;    
            case '7':
                printf("\n");
                exitmsg();
                exit(0);
                break;
            default:
                printf("\t\t\t-- Invalid input! --\n\n");
                break;
        }
    }
    
    return 0;
}

void exitmsg() {
	
    printf("\t\t\t---Thank you for using our Criminal Record System!---\n");
    printf("\t\t\t\t\t---End Program---\n");
}

void read() {
	
    FILE *file = fopen("crime.txt", "r");

    if (file == NULL) {
        printf("\n");
        printf("\t\tNo file for record yet, ");
        printf("Attempting to create a new record..\n");
        printf("\t\t\t      -- Please run the program again --");

        file = fopen("crime.txt", "w");

        fclose(file);

        exit(0);
    }

    nOfRecords = fread(criminal, sizeof(records), 100, file);

    fclose(file);

    return;
}

void write() {
	
    FILE *file = fopen("crime.txt", "w");

    if (file == NULL) {
        printf("System Error");
        exit(1);
    }

    fwrite(criminal, sizeof(records), nOfRecords, file);

    fclose(file);

    return;
}

//For Adding Records
void showCrime();
int isNameValid(const char *name);
int checkCrime (int option, int c);
int isCodeValid(const char *name);
int checkInput(int input);
int checkIfUnique();
int checkIfUniqueCode();
int validDate(int MM, int DD, int YY);
int checkYear( int year);
int checkContact(char con[10]);
int sexValid(const char *sex);
int checkIfUniqueContact();

void addRecord() {
	printf("\n");
    printf("=========================================================================\n");
    printf("\n");
    printf("\t\t\tAdd Records [Maximum: 100]\n");
    printf("\t\t\t[ Number of Records: %d ]\n", nOfRecords);
    printf("\n");

    int c = nOfRecords;

    char option ;
  	
        int status = 0;
        int unique = 0;
        int flag = 0;

        do {
            unique = 1;

            do {
                fflush(stdin);
                printf("Name: ");
                scanf("%[^\n]s", criminal[c].name);
                status = isNameValid(criminal[c].name);

                if (status == 0) {
                    printf("-- Please write the name correctly.\n");
                }
                
            } while(status == 0);

            do {
            	unique = 1;
                fflush(stdin);
                printf("Case Code: ");
                scanf("%[^\n]%*c", criminal[c].code);
                status = isCodeValid(criminal[c].code);

                if (status == 0) {
                    printf("-- Please write the case code correctly.\n");
                }
                
				unique = checkIfUniqueCode();
					if (unique == 0) {
					addRecord();
				 	}

            } while(status == 0 );
			 
            unique = checkIfUnique();

        } while(unique == 0);

        int validAge = 0;
        do {
            printf("Age: ");

            int args = scanf("%d", &criminal[c].age);
            if (args < 1) {
                // Display an error message
                char dummy;
                scanf("%s", &dummy);  // eats a character off the buffer
                printf("-- Please enter a correct age [15 - 70]\n");
                validAge = 0;
            }
            else {
                if (criminal[c].age >= 15 && criminal[c].age <= 70) {
                    validAge = 1;
                }

                if(validAge == 0) {
                    printf("-- Please enter a correct age [15 - 70]\n");
                    validAge == 0;
                }
            }

        } while (validAge == 0);
        
        do {
                fflush(stdin);
                printf("Sex[M/F]: ");
                scanf("%[^\n]%*c", criminal[c].sex);
                status = sexValid(criminal[c].sex);

                if (status == 0) {
                    printf("-- Please write [M/F] only\n");
                }

            } while(status == 0);
       
	    int MM, DD, YY;    
        int validBD = 0;
		char slash1, slash2;   
        do {
              	printf("Birthdate [MM-DD-YYYY]: ");
	            int args = scanf("%d%c%d%c%d", &criminal[c].sentBD_M, &slash1, &criminal[c].sentBD_D, &slash2, &criminal[c].sentBD_Y);
	            if (args < 1) {
	                // Display an error message
	                char dummy;
	                scanf("%s", &dummy);  // eats a character off the buffer
	                printf("-- Please enter a correct Date [MM-DD-YYYY] \n");
	            }
				else if (slash1 == '-' && slash2 == '-') {
					if ((currentY - criminal[c].sentBD_Y )==criminal[c].age){
						validBD = validDate (criminal[c].sentBD_M, criminal[c].sentBD_D, criminal[c].sentBD_Y);
					}
					else{	
						validBD = 0;
					}
            		
				}
				
                if (validBD == 0) {
                printf("\n-- Please enter a correct Birth Date [MM-DD-YYYY]");
                printf("\n");
                }
                
    		} while (validBD == 0);
        
		int validD = 0;
        
		do {
		    	printf("Date of Sentence [MM-DD-YYYY]: ");
            	int args = scanf("%d%c%d%c%d", &criminal[c].sentMM, &slash1, &criminal[c].sentDD, &slash2, &criminal[c].sentYY);
	            if (args < 1) {
	                // Display an error message
	                char dummy;
	                scanf("%s", &dummy);  // eats a character off the buffer
	                printf("-- Please enter a correct Date [MM-DD-YYYY] \n");
	            }
				else if ( slash1 == '-' && slash2 =='-') {
					if ((criminal[c].sentYY - criminal[c].sentBD_Y) >= 15){
						validD = validDate (criminal[c].sentMM, criminal[c].sentDD, criminal[c].sentYY);
					}
            		else {
            		printf("\n");
					printf("\tInvalid Sentence Date");	
					}     	
				}
				
                if (validD == 0) {
                printf("\n-- Please enter a correct Date [MM-DD-YYYY]:");
                printf("\n");
                }
                
    	} while (validD == 0);
    	
        fflush(stdin);
        int validG = 0;
        int optionForG;
        do {
            	showCrime();
            	printf("Crime: ");

            	int args = scanf("%d", &optionForG);
            	if (args < 1) {
                // Display an error message
                char dummy;
                scanf("%[^\n]s", &dummy);  // eats a character off the buffer
                printf("\t\t\t-- Please input correctly.\n");
                validG = 0;
            	}
            	else {
                	validG = checkCrime(optionForG, c);
            	}

            	if (args > 1 && validG == 0) {
                	printf("\t\t\t-- Please input correctly.\n");
            	}

        } while(validG == 0);
				
        do {
        		unique = 1;
                fflush(stdin);
                printf("Emergency Contact: [+63]");
                scanf("%[^\n]s", criminal[c].contact);
                status = checkContact(criminal[c].contact);
                printf("\n");
				fflush(stdin);
                if (status == 0) {
                    printf("-- Please write a 10-digit number [+63].\n");
                    unique=0;
                }
                else {
                	unique = checkIfUniqueContact();
                	if(unique==0 ){
					printf("\t---------Contact is already in the List---------\n");
					status==0;
					}
				}
            
			} while(unique==0 && status==0);

        fflush(stdin);

        printf("\n\t\t\tThe record is archived...\n");
        ++c;
        nOfRecords += 1;
        write();

		do {
        	printf("Add another record? [Y/N]: ");
        	scanf("%c", &option);
        	fflush(stdin);
        	printf("\n");
        
				if (option == 'n' || option == 'N'){
        			mainmenu();
				}
		 		else if (option == 'Y' || option == 'y'){
					addRecord();	
				}
				else if (  (option != 'Y' || option != 'y') || (option != 'n' || option != 'N')   ){
					printf ("\t\t Please input [Y/N]:\n");
				}
				
		} while ((option != 'Y' || option != 'y') || (option != 'n' || option != 'N'));
   
}

void showCrime() {
	
    printf("\n");
    printf("\t// Please Select a Number:\n");
    printf("\t1.Theft      |  2.Rape       |  3.Physical Injury  |  4.Robbery           |  5.Murder\n");
    printf("\t6.Carnapping |  7.Homicide   |  8.Illegal Drugs    |  9.Multiple Crimes\n");
}

int checkInput(int input) {
	
    int valid = 1;

    if (input < 1) {
        // Display an error message
        char dummy;
        scanf("%s", &dummy);  // eats a character off the buffer
        printf("-- Please input correctly.\n");
        valid = 0;
    }

    return valid;
}

int checkIfUnique() {
	
    int isUnique = 1;
    
	for (int c = 0; c < nOfRecords; ++c) {
        if (!strcmp(criminal[nOfRecords].name, criminal[c].name) && !strcmp(criminal[nOfRecords].code, criminal[c].code))  {
            isUnique = 0;
            printf("-- This person is already in the record!\n");
        }
    }

    return isUnique;
}

int checkIfUniqueCode() {
	
 	int isUnique = 1;
    
	for (int c = 0; c < nOfRecords; ++c) {
        if ( !strcmp(criminal[nOfRecords].code, criminal[c].code)) {
            isUnique = 0;   
        }
    }
    
    if (isUnique == 0){
		printf("-- This Case Code is already in the record!\n");
	}

    return isUnique;
}

int checkIfUniqueContact() {
	
 	int isUnique = 1;
    
	for (int c = 0; c < nOfRecords; ++c) {
        if ( !strcmp(criminal[nOfRecords].contact, criminal[c].contact)) {
            isUnique = 0;   
        }
    }
    
    return isUnique;
}

int validDate(int MM, int DD, int YY) {
	
	int leap = 0;
    leap = checkYear(YY);

    if ( MM !=2 && (MM==4 || MM==6 || MM==9 || MM==11 )) {
		if (DD <= 30 && DD >= 1) {
		    if (YY <= 3000 && YY >= 1800) {
		        return 1;
		    } 
			else {
		        return 0;
		    }
		} 
		else {
		    return 0;
		}
    }
	else if (MM !=2 && (MM == 1 || MM==3 || MM==5 || MM==7 || MM==8 || MM==10 || MM==12)) {
        if (DD <= 31 && DD >= 1) {
		    if (YY <= 3000 && YY >= 1800) {
		        return 1;
		    } 
			else {
		        return 0;
		    }
		} 
		else {
		    return 0;
		}
	}
    else if (leap==0 && MM == 2 ) {
        if (DD <= 28 && DD >= 1)  {
		    if (YY <= 3000 && YY >= 1800) {
		        return 1;
		    } 
			else {
		        return 0;
		    }
		} 
		else {
			return 0;
		}
    }
    else if ( leap==1 && MM ==2 ) {
        if (DD <= 29 && DD >= 1) {
			return 1;
		} 
		else {
		    return 0;
		}
    }
	else {
		return 0;
	}
				
}
    
int checkYear(int year) {
 
    if (year % 400 == 0) {
        return 1;
    } else if (year % 100 == 0) {
        return 0;
    } else if (year % 4 == 0) {
        return 1;
    } else {
        return 0;
    }
    
}

int checkContact(char con[10]) {
	
    int validCon = 0;
	int l = 0;
    int c = 0;
    l = strlen(con);

    for(c = 0; c < l ; ++c) {
    	if(con[0] == '9' && l==10){
    		if(((con[c] >= 48  && con[c] <= 57) || (con[c] >='0'  && con[c] <= '9'))  ) {
	             validCon = validCon + 1;
    		}
    	}
	}
	if (validCon==10) {
		validCon=1;
	}
	else { 
		validCon=0;
	}	
	
    return validCon;
}
		
int isNameValid(const char *name){
    int validName = 0, check=0;
    int l = 0;
    int c = 0;
    l = strlen(name);
	for(c = 0; c < l ; ++c)
    {  
    if (!(name[c] >= '0' && name[c] <= '9')){
       	check++;
	}
	}
	if (check == l){
	validName=1;
  }
    return validName;
}

int isCodeValid(const char *name){
    int validName = 0, check=0;
    int l = 0;
    int c = 0;
    l = strlen(name);
	for(c = 0; c < l ; ++c)
    {  
    if (!(name[c] == '\n' )){
       	check++;
	}
	}
	if (check == l){
	validName=1;
  }
    return validName;
}

int sexValid(const char *sex) {
	
    int validsex = 0;
    int c = 0;
    
    for(c = 0; c < 1 ; ++c) {
        if((sex[c] != '\n') && ((sex[c] == 'M') || (sex[c] == 'F'))) {
            validsex = 1;
            break;
        }
    }
    
    return validsex;
}

int checkCrime (int option, int c) {
	
    int validCrime = 1;
    
    switch(option) {
        case 1:
            strcpy(criminal[c].crime, "Theft");
            break;
        case 2:
            strcpy(criminal[c].crime, "Rape");
            break;
        case 3:
            strcpy(criminal[c].crime, "Physical Injury");
            fflush(stdin);
            break;
        case 4:
            strcpy(criminal[c].crime, "Robbery");
            break;
        case 5:
            strcpy(criminal[c].crime, "Murder");
            break;
        case 6:
            strcpy(criminal[c].crime, "Carnapping");
            break;
        case 7:
            strcpy(criminal[c].crime, "Homicide");
            break;
        case 8:
            strcpy(criminal[c].crime, "Illegal Drugs");
            fflush(stdin);
            break;
        case 9:
            strcpy(criminal[c].crime, "Multiple Crimes");
            fflush(stdin);
            break;
        default:
            validCrime = 0;
            printf("\t\t\t-- Please input a valid Crime --\n");
            break;
    }

    return validCrime;
}

//For Viewing Records
void viewAllRecord();
void viewSpecific();

void viewRecord() {
	
    char choice;
    

    if (nOfRecords!=0){
    while(1) {
        printf("\n");
    	printf("=========================================================================\n");
        printf("\t\t\t1. View All Records\n");
        printf("\t\t\t2. View Specific Record\n");
        printf("\t\t\t3. Back\n");

        printf("Enter your choice: ");
        scanf("%s", &choice);

        switch(choice) {
            case '1':
                viewAllRecord();
                break;
            case '2':
                viewSpecific();
                break;
            case '3':
                mainmenu();
                break;
            default:
                printf("Invalid Input!");
                break;
        }
    }
}
else{
    	printf("\n");
    	printf("\t\t---------------No Record Yet------------------\n\n");
    	mainmenu();
	}
    return;
}

void viewAllRecord() {
	
    printf("\n");
    printf("=========================================================================\n");
	
	printf("\n[ All Records ] --\n");

    for (int c = 0; c < nOfRecords; ++c) {
        printf("\n");
        printf("Name: %s\n", criminal[c].name);
        printf("Case Code: %s\n", criminal[c].code);
        printf("Age: %d years old\n", criminal[c].age);
        printf("Sex: %s\n", criminal[c].sex);
        printf("Crime: %s\n", criminal[c].crime);
        printf("Birthdate: %d-%d-%d\n", criminal[c].sentBD_M, criminal[c].sentBD_D, criminal[c].sentBD_Y);
        printf("Date of Sentence: %d-%d-%d\n", criminal[c].sentMM, criminal[c].sentDD, criminal[c].sentYY);
        printf("Emergency Contact: [+63]%s\n", criminal[c].contact);
        //printf("\n");
        printf("---------------------------------------------------------\n");
    }

    printf("\n---> Scroll up to view all records <---\n");
    
	
}

void print_data(int i) {
	
    printf("\n");
    printf("\t\t\tName: %s\n", criminal[i].name);
    printf("\t\t\tCase Code: %s\n", criminal[i].code);
    printf("\t\t\tAge: %d years old\n", criminal[i].age);
    printf("\t\t\tSex: %s\n", criminal[i].sex);
    printf("\t\t\tCrime: %s\n", criminal[i].crime);
    printf("\t\t\tBirthdate: %d-%d-%d\n", criminal[i].sentBD_M, criminal[i].sentBD_D, criminal[i].sentBD_Y);
    printf("\t\t\tDate of Sentence: %d-%d-%d\n", criminal[i].sentMM, criminal[i].sentDD, criminal[i].sentYY);
    printf("\t\t\tEmergency Contact: [+63]%s\n", criminal[i].contact);
    printf("\t\t\t---------------------------------------------------------\n");

    return;
}

//For Viewing Specific Records
void viewByAge();
void viewName();
void viewSex();
void viewBirth();

void viewSpecific() {
	
    while(1) {
        printf("\n");
    	printf("=========================================================================\n");
        printf("\t\t\t1. By Name\n");
        printf("\t\t\t2. By Case Code\n");
        printf("\t\t\t3. By Age\n");
        printf("\t\t\t4. By Sex\n");
        printf("\t\t\t5. By Crime\n");
        printf("\t\t\t6. By Birthdate\n");
        printf("\t\t\t7. By Date of Sentence\n");
        printf("\t\t\t8. By Contact\n");
        printf("\t\t\t9. Back\n");

        char choice;
        printf("Enter the number: ");
        scanf("%s",&choice);
        fflush(stdin);
        switch(choice)
        {
            case '1':
                viewName();
                break;
            case '2':
                viewCode();
                break;
            case '3':
                viewByAge();
                break;
            case '4':
                viewSex();
                break;
            case '5':
                viewCrime();
                break;
            case '6':
                viewBirth();
                break;
            case '7':
                viewDate();
                break;
            case '8':
                viewContact();
                break;
            case '9':
                viewRecord();
                break;
            default:
                printf("-- Enter a valid number.\n");
                break;
        }
    }

}

void viewName() {
	
    int found=0, status=0;
    char search_name[255];

	do {
	    fflush(stdin);printf("\n");
    	printf("=========================================================================\n");
	    printf("Enter Name (Case Sensitive): ");
	    scanf(" %[^\n]",search_name);
	    status = isNameValid(search_name);

		if (status == 1) {
	    	for (int i=0; i<nOfRecords; i++) {
	        	if(strcmp(search_name,criminal[i].name)==0) {
	            	print_data(i);
	            	found++;
	        	}
	    	}
	    
	    	if(found == 0) {
	        	printf("\n");
	        	printf("\t\t\t-- %s is Not Found --\n",search_name);
	        
				return;
	    	}
		}
		else if (status == 0) {
    		printf("-- Please write the name correctly.\n");
    	}
    
	} while (status==0);
	
	return;
}

void viewDate() {
	
	int found=0, validBD = 0;
    int search_month, search_day, search_year;
    char hyphen1, hyphen2;
    
	do{
	    fflush(stdin);
	    printf("\n");
    	printf("=========================================================================\n");
	    printf("Enter Date of Sentence [MM-DD-YYYY]: ");
	    scanf("%d%c%d%c%d", &search_month, &hyphen1, &search_day, &hyphen2, &search_year);
		validBD = validDate (search_month, search_day, search_year);

		if ((hyphen1 == '-' && hyphen2 == '-') && (validBD == 1)){
	
		    for(int i=0; i<nOfRecords; i++) {
		        if(search_month==criminal[i].sentMM) {
		        	if (search_day==criminal[i].sentDD) {
		        		if (search_year==criminal[i].sentYY) {
		        			print_data(i);
		           		 	found++;	
						}
					}
		        }
		    }
		    
		    if(found == 0) {
		        printf("\n");
		        printf("\t\t\t-- Date of Sentence Not Found --\n");
		        return;
		    }
	  	}
	  	
		if (validBD == 0) {
	      	printf("\n-- Please enter a correct Date [MM-DD-YYYY]");
	       	printf("\n");
	    }

	} while(validBD == 0);
	
 	return;  
}

void viewContact() {
	
    int found=0, status=0;
    char search_criminal[255];
    do{
    printf("\n");
    printf("=========================================================================\n");
    printf("Enter Emergency Contact: [+63]");
    scanf(" %[^\n]",search_criminal);
    fflush(stdin);
    status = checkContact(search_criminal);

if (status==1){
    for(int i=0; i<nOfRecords; i++) {
        if(strcmp(search_criminal,criminal[i].contact)==0) {
            print_data(i);
            found++;
        }
    }
    
    if(found == 0) {
        printf("\n");
        printf("\t\t\t-- %s is Not Found --\n",search_criminal);
    }
}
 if (status == 0)
    {
    printf("\t\t\t-- Please write Contact correctly.\n");
    printf("\t\t\t[+63]_+10 digits\n");
    }
} while (status==0);
    return;
}

void viewCode() {

    int found=0;
    char search_code[255];
    printf("\n");
    printf("=========================================================================\n");
    printf("Enter Case Code: ");
    scanf(" %[^\n]",search_code);
    fflush(stdin);

    for(int i=0; i<nOfRecords; i++) {
        if(strcmp(search_code,criminal[i].code)==0) {
            print_data(i);
            found++;
        }
    }
    
    if(found == 0) {
        printf("\n");
        printf("\t\t\t-- %s is Not Found --\n",search_code);
    }

    return;
}

void viewSex() {
	
    int found=0, status=0;
    char search_criminal[50];
do{
	printf("\n");
    printf("=========================================================================\n");
    printf("Enter Sex: ");
    scanf("%s",search_criminal);
	status = sexValid(search_criminal);
	if (status==1){
	    for(int i=0; i<nOfRecords; i++) {
	        if(strcmp(search_criminal,criminal[i].sex)==0) {
	            print_data(i);
	            found++;
	        }
	    }
	    
	    if(found == 0) {
	        printf("\n");
	        printf("\t\t\t-- %s is Not Found --\n",search_criminal);
	    }
    }
    if (status==0){
    	printf("\t\t\t Enter Sex [M/F]:\n");
	}
}while(status==0);
    return;
}

void viewBirth() {
	
    int found=0, validBD = 0;
    int search_month, search_day, search_year;
    char hyphen1, hyphen2;
    
	do {
		printf("\n");
    	printf("=========================================================================\n");
    	printf("\t\t\tEnter Birthdate;");
	    fflush(stdin);
	    scanf("%d%c%d%c%d", &search_month, &hyphen1, &search_day, &hyphen2, &search_year);
		validBD = validDate (search_month, search_day, search_year);

		if ((hyphen1 == '-' && hyphen2 =='-') && (validBD == 1)) {
	
		    for(int i=0; i<nOfRecords; i++) {
		        if(search_month==criminal[i].sentBD_M){
		        	if (search_day==criminal[i].sentBD_D){
		        		if (search_year==criminal[i].sentBD_Y){
		        			print_data(i);
		           		 	found++;	
						}
					} 
		        }
		    }
		    
			if(found == 0) {
		        printf("\n");
		        printf("\t\t\t-- Birthdate Not Found --\n");
		        return;
		    }
	  	}
	  	
	  	if (validBD == 0) {
	      	printf("\n-- Please enter a correct Date [MM-DD-YYYY]");
	       	printf("\n");
	    }

	} while(validBD == 0);
	
 	return;
}

void viewCrime() {
	
    int i=0,found=0, validG = 0;
    int search_crime=0;
    char crime_name[50];
    do{
    
	showCrime();
	printf("\n");
    printf("=========================================================================\n");
    printf(" Crime: ");
	int args = scanf("%d", &search_crime);

if (args < 1)
    {
    	char dummy;
        scanf("%s", &dummy);  // eats a character off the buffer
        printf("\t\t\t-- Please input correctly.\n");
        validG = 0;
    }
else if (search_crime >=1 && search_crime <=9) {
	//if (search_crime <=9 && search_crime >=1){
			
        if(search_crime ==1){
            strcpy(crime_name, "Theft");
    		for(int i=0; i<nOfRecords; i++) {
    			if(strcmp(crime_name,criminal[i].crime)==0) {
      	 		print_data(i);
       			 found++;
        		}
    		}
			if(found == 0) {
    			printf("\n");
    			printf("\t\t\t-- %s Has no record yet --\n",crime_name);
    			viewSpecific();
			}        
            return;
    	}
        else if(search_crime ==2){
            strcpy(crime_name, "Rape");
            for(int i=0; i<nOfRecords; i++) {
				if(strcmp(crime_name,criminal[i].crime)==0) {
				print_data(i);
				found++;
				}
			}
			if(found == 0) {
				printf("\n");
				printf("\t\t\t-- %s Has no record yet --\n",crime_name);
				viewSpecific();
			}
			return;
    	}
        else if(search_crime ==3){
            strcpy(crime_name, "Physical Injury");
            for(int i=0; i<nOfRecords; i++) {
				if(strcmp(crime_name,criminal[i].crime)==0) {
				print_data(i);
				found++;
				}
			}
			if(found == 0) {
				printf("\n");
				printf("\t\t\t-- %s Has no record yet --\n",crime_name);
				viewSpecific();
			}
			return;
            }
        else if(search_crime ==4){
            strcpy(crime_name, "Robbery");
			for(int i=0; i<nOfRecords; i++) {
				if(strcmp(crime_name,criminal[i].crime)==0) {
				print_data(i);
				found++;
				}
			}
			if(found == 0) {
				printf("\n");
				printf("\t\t\t-- %s Has no record yet --\n",crime_name);
				viewSpecific();
			}
			return;    
            }
        else if(search_crime ==5){
            strcpy(crime_name, "Murder");
            for(int i=0; i<nOfRecords; i++) {
				if(strcmp(crime_name,criminal[i].crime)==0) {
				print_data(i);
				found++;
				}
			}
			if(found == 0) {
				printf("\n");
				printf("\t\t\t-- %s Has no record yet --\n",crime_name);
				viewSpecific();
			}
			return;
            }
        else if(search_crime ==6){
            strcpy(crime_name, "Carnapping");
        	for(int i=0; i<nOfRecords; i++) {
				if(strcmp(crime_name,criminal[i].crime)==0) {
				print_data(i);
				found++;
				}
			}
			if(found == 0) {
				printf("\n");
				printf("\t\t\t-- %s Has no record yet --\n",crime_name);
				viewSpecific();
			}
			return;
            }
        else if(search_crime ==7){
            strcpy(crime_name, "Homicide");
        	for(int i=0; i<nOfRecords; i++) {
				if(strcmp(crime_name,criminal[i].crime)==0) {
				print_data(i);
				found++;
				}
			}
			if(found == 0) {
				printf("\n");
				printf("\t\t\t-- %s Has no record yet --\n",crime_name);
				viewSpecific();
			}
			return;
            }
        else if(search_crime ==8){
            strcpy(crime_name, "Illegal Drugs");
        	for(int i=0; i<nOfRecords; i++) {
				if(strcmp(crime_name,criminal[i].crime)==0) {
				print_data(i);
				found++;
				}
			}
			if(found == 0) {
				printf("\n");
				printf("\t\t\t-- %s Has no record yet --\n",crime_name);
				viewSpecific();
			}
			return;
            }
        else if (search_crime ==9){
            strcpy(crime_name, "Multiple Crimes");
        	for(int i=0; i<nOfRecords; i++) {
				if(strcmp(crime_name,criminal[i].crime)==0) {
				print_data(i);
				found++;
				}
			}
			if(found == 0) {
				printf("\n");
				printf("\t\t\t-- %s Has no record yet --\n",crime_name);
				viewSpecific();
			}
			return;
            }	
	} 
	if (!(search_crime <=1 && search_crime >=9)) {
    printf("\t\t\t-- Please input a valid Crime --\n");
    viewCrime();
    validG = 0;
	}  
} while(validG = 0);

    return;
}

void viewByAge() {
	
    int search_age;
    int found = 0;

    int validAge = 0;
    do {
    	printf("\n");
    	printf("=========================================================================\n");
        printf("Enter Age: ");
        int args = scanf("%d", &search_age);
		fflush(stdin);
        if (args < 1) {
            char dummy;
            scanf("%s", &dummy);
            printf("Enter a valid age\n");
            validAge = 0;
        }
        else {

        if (search_age >= 15 && search_age <= 70) {
              validAge = 1;
            }

        if(validAge == 0) {
               printf("-- Please enter a correct age [15 - 70]\n");
              validAge == 0;
        	}
  		}
    } while(validAge == 0);

    fflush(stdin);
    printf("\t\t\t// Criminals by age %d\n", search_age);
    
	for(int i=0; i<nOfRecords; i++) {
        if(search_age == criminal[i].age) {
            print_data(i);
            found++;
        }
    }
    
    if(found == 0) {
        printf("\t\t\t-- Nothing Found --\n");
    }

    return;
}

//For Deleting Records
void deleteACriminal();
void deleteRecord();
void deleteRecord_2 ();
void removeAllRecord();

int deleteCounter = 0;

void deleteOption() {
    char choice;
   if (nOfRecords!=0){
   
    while(1) {
    	printf("\n");
    	printf("=========================================================================\n");
        printf("\n");
        printf("\t\t\tWhat do you want to do?\n");
        printf("\t\t\t 1. Remove a Record\n");
        printf("\t\t\t 2. Remove all records [Be careful]\n");
        printf("\t\t\t 3. Back\n");

        printf("\n");
        printf("Enter your choice: ");
        scanf("%s", &choice);
        fflush(stdin);

        switch(choice)
        {
            case '1':
                deleteRecord();
                break;
            case '2':
                removeAllRecord();
                mainmenu();
                break;
            case '3':
                mainmenu();
                break;
            default:
                printf("\t\t\t-- Invalid Input! --");
                break;
        }
    }
}
else{
    	printf("\n");
    	printf("\t\t---------------No Record Yet------------------\n\n");
    	mainmenu();
	}
}

void deleteRecord () {
	 char choice;
    char deleteName[50];
    char deleteCode[30];
    int found = 0;

    if (nOfRecords == 0) {
    	printf("\n");
    	printf("=========================================================================\n");
        printf("\t\t\t-- You have no records to delete.\n");
        mainmenu();
    }
	
    viewAllRecord();
	printf("\n");
    printf("----------------------------------------------------------------------\n");
    printf("\n");
    printf("\tEnter the details of the criminal you want to delete\n");
    printf("Name: ");
    scanf("%[^\n]s", deleteName);
    fflush(stdin);
    printf("Case Code: ");
    scanf("%[^\n]%*c", deleteCode);
    fflush(stdin);

    for (int c = 0; c < nOfRecords; ++c) {
        if ( !strcmp(deleteName, criminal[c].name) && !strcmp(deleteCode, criminal[c].code)) {
            found = 1;
            printf("\n");
    		printf("=========================================================================\n");
            printf("\n");
            printf("\t\t\t-- Record Found --\n");
            printf("\n");
            printf("\t\t\t   Name: %s\n", criminal[c].name);
            printf("\t\t\t   Case Code: %s\n", criminal[c].code);
            printf("\t\t\t   Age: %d years old\n", criminal[c].age);
            printf("\t\t\t   Sex: %s\n", criminal[c].sex);
            printf("\t\t\t   Crime: %s\n", criminal[c].crime);
            printf("\t\t\t   Birthdate: %d-%d-%d\n", criminal[c].sentBD_M,criminal[c].sentBD_D,criminal[c].sentBD_Y);
            printf("\t\t\t   Date of Sentence: %d-%d-%d\n", criminal[c].sentMM,criminal[c].sentDD,criminal[c].sentYY);
            printf("\t\t\t   Emergency Contact: [+63]%s\n", criminal[c].contact);
            printf("\n");
            deleteCounter = c;
        }
    }

    if (found == 0) {
        printf("\t\t| Record Not Found\n");
        printf("\t\t| Please input the name correctly\n\n");
        deleteRecord_2 ();
    }

do {
    if (found == 1) {
        printf("\n");
        printf("Delete this Criminal? [Y/N]: ");
        scanf("%s", &choice);
		fflush(stdin);

        if (choice == 'Y' || choice == 'y') {
        	guard();
			printf("\n");
            deleteACriminal();
            printf("\t\t\t-- Record deleted --\n");
            write();
            deleteOption();
        } 
		else if (choice == 'N' || choice == 'n'){
            printf("\n\t\t\t--   Cancelled   --\n");
            deleteOption();
        }
        if ((choice != 'Y' || choice != 'y') || (choice != 'N' || choice != 'n') ){
    	printf("\t\t Invalid Input!");
	}
}
} while ((choice != 'Y' || choice != 'y') || (choice != 'N' || choice != 'n') );

return;
}



void deleteRecord_2 () {
    char choice;
	char deleteName[50];
    char deleteCode[30];
    int found = 0;

    if (nOfRecords == 0) {
    	printf("\n");
    printf("=========================================================================\n");
        printf("\t\t\t-- You have no records to delete.\n");
        mainmenu();
    }
    
	printf("\n");
    printf("=========================================================================\n");
    printf("\n");
    printf("\tEnter the details of the criminal you want to delete\n");
    printf("Name: ");
    scanf("%[^\n]s", deleteName);
    fflush(stdin);
    printf("Case Code: ");
    scanf("%[^\n]%*c", deleteCode);
    fflush(stdin);

    for(int c = 0; c < nOfRecords; ++c) {
        if ( !strcmp(deleteName, criminal[c].name) && !strcmp(deleteCode, criminal[c].code)) {
            found = 1;
            printf("\n");
    		printf("=========================================================================\n");
            printf("\n");
            printf("\t\t\t-- Record Found --\n");
            printf("\n");
            printf("\t\t\t   %s\n", criminal[c].name);
            printf("\t\t\t   Case Code: %s\n", criminal[c].code);
            printf("\t\t\t   %d years old\n", criminal[c].age);
            printf("\t\t\t   %s\n", criminal[c].name);
            printf("\t\t\t   Crime: %s\n", criminal[c].crime);
            printf("\t\t\t   Date of Sentence: %d-%d-%d\n", criminal[c].sentMM,criminal[c].sentDD,criminal[c].sentYY);
            printf("\t\t\t   Emergency Contact: [+63]%s\n", criminal[c].contact);
            printf("\n");
            deleteCounter = c;
        }

    }

    if (found == 0) {
        printf("\t\t| Record Not Found\n");
        printf("\t\t| Please Check the name  and code correctly\n\n");
        deleteRecord_2 ();
    }
    
do {
    if (found == 1) {
        printf("\n");
        printf("Delete this Criminal? [Y/N]: ");
        scanf("%s", &choice);
		fflush(stdin);

        if (choice == 'Y' || choice == 'y') {
        	guard();
			printf("\n");
            deleteACriminal();
            printf("\t\t\t-- Record deleted --\n");
            write();
            deleteOption();
        } 
		else if (choice == 'N' || choice == 'n'){
            printf("\n\t\t\t--   Cancelled   --\n");
            deleteOption();
        }
        if ((choice != 'Y' || choice != 'y') || (choice != 'N' || choice != 'n') ){
    	printf("\t\t Invalid Input!");
	}
}
} while ((choice != 'Y' || choice != 'y') || (choice != 'N' || choice != 'n') );

return;
}
    
void deleteACriminal() {

    while (deleteCounter < nOfRecords) {
        strcpy(criminal[deleteCounter].name, criminal[deleteCounter + 1].name);
        strcpy(criminal[deleteCounter].code, criminal[deleteCounter + 1].code);
        criminal[deleteCounter].age = criminal[deleteCounter+1].age;
        strcpy(criminal[deleteCounter].sex, criminal[deleteCounter + 1].sex);
        strcpy(criminal[deleteCounter].crime, criminal[deleteCounter+1].crime);
        criminal[deleteCounter].sentMM = criminal[deleteCounter + 1].sentBD_M;
        criminal[deleteCounter].sentDD = criminal[deleteCounter + 1].sentBD_D;
        criminal[deleteCounter].sentYY = criminal[deleteCounter + 1].sentBD_Y;
        criminal[deleteCounter].sentMM = criminal[deleteCounter + 1].sentMM;
        criminal[deleteCounter].sentDD = criminal[deleteCounter + 1].sentDD;
        criminal[deleteCounter].sentYY = criminal[deleteCounter + 1].sentYY;
        strcpy(criminal[deleteCounter].contact, criminal[deleteCounter + 1].contact);

        ++deleteCounter;
    }

    --nOfRecords;

    return;
}

void removeAllRecord() {
	
	guard();
	printf("\n");

        char choice;
        do{
        fflush(stdin);
        printf("\n");
    	printf("=========================================================================\n");
        printf("\n");
        printf("                 ARE YOU SURE YOU WANT TO DELETE ALL RECORDS? [Y/N]:");
        scanf("%s", &choice);

        if (choice == 'Y' || choice == 'y') {
            guard();
			printf("\n");
			FILE *file;
	    	fclose(fopen("crime.txt", "wb"));
			printf("\t\t\t-- All Records Deleted --\n");
			printf("\n");
	    	printf("\t\t ** Please run the program again **\n");
	   		printf("=========================================================================\n");
			printf("\n");
	    	exit(0);
        } 
		else if (choice == 'n' || choice == 'N') {
            printf("\n\t\t\t--   Cancelled   --\n");
            mainmenu();
        }	
        if ((choice != 'n' || choice != 'N')||(choice != 'Y' || choice != 'y')){
        	printf("\n\t\t\t--   Invalid Input   --\n");	
		}
    }while ((choice != 'n' || choice != 'N')||(choice != 'Y' || choice != 'y'));

}

//For Record Summary
void crimeDistribution();

void summary() {
int choice = 0;
if (nOfRecords!=0){

    printf("\t\t\t*********************************************\n");
    printf("\t\t\t       [ R e c o r d   S u m m a r y ]\n");
    printf("\n");
    printf("\t\t\t\t   Number of Criminals: %d\n", nOfRecords);

if (nOfRecords != 0) {
    printf("\n");
    printf("\t\t\t	     Crime Distribution\n");
    if (nOfRecords != 0) 
	crimeDistribution();
	
    printf("\n");
    
 }
 printf("\t\t\t*********************************************\n");
 do{
 printf("\t\tBack [1]: ");
 printf("\t\tStay [2]: \n");
 printf("\t\tEnter your choice: ");
 scanf("%d", &choice);
        fflush(stdin);
 printf("\n");

            if (choice==1){
				mainmenu();
			} 
            else if  (choice==2){
                summary();
    		}
    	if (choice != 1 || choice !=2){
                printf("\t\t\t-- Invalid Input! --\n");
        	}

        }while (choice != 1 || choice !=2);
}
else{
    	printf("\n");
    	printf("\t\t---------------No Record Yet------------------\n\n");
    	mainmenu();
	}

}
//For Crime Distribution
void crimeDistribution() {
	
    int n1 = 0, n2 = 0, n3 = 0, n4 = 0, n5 = 0, n6 = 0, n7 = 0, n8 = 0, n9 = 0;

    for (int c = 0; c < nOfRecords; ++c) {
        if (!strcmp(criminal[c].crime, "Theft")) {
            ++n1;
        } else if (!strcmp(criminal[c].crime,"Rape")) {
            ++n2;
        } else if (!strcmp(criminal[c].crime,"Physical Injury")) {
            ++n3;
        } else if (!strcmp(criminal[c].crime,"Robbery")) {
            ++n4;
        } else if (!strcmp(criminal[c].crime,"Murder")) {
            ++n5;
        } else if (!strcmp(criminal[c].crime,"Carnapping")) {
            ++n6;
        } else if (!strcmp(criminal[c].crime, "Homicide")) {
            ++n7;
        } else if (!strcmp(criminal[c].crime,"Illegal Drugs")) {
            ++n8;
        } else if (!strcmp(criminal[c].crime, "Multiple Crimes")) {
            ++n9;
        }
    }

    printf("\tTheft      %d |  Rape       %d |  Physical Injury %d |  Robbery         %d |  Murder   %d\n",n1,n2,n3,n4,n5);
    printf("\tCarnapping %d |  Homicide   %d |  Illegal Drugs   %d |  Multiple Crimes %d\n",n6,n7,n8,n9);
 	printf("\t\t\t*********************************************\n");
	
	int size, i, j;
	float l, s;
	int N[9] = {n1, n2, n3, n4, n5, n6, n7, n8, n9};
		s=N[0];
		l=N[0];
		
	for (i=1;i < 10; i++) {
		if (N[i] < s) {
			s=N[i];
		}
		if (N[i]> l) {
			l=N[i];
		}
	}
	
	printf ("\n				Highest Crime Rate: (%.2f%%)\n", (l / nOfRecords )* 100);
	printf ("\n");
	
	for (i=0; i<9; i++){
		if (l == N[i]){
			j=i;
			if (j==0){
				printf ("			Theft (%g/%d)\n", l,nOfRecords);}
			else if (j==1){
				printf ("			Rape (%g/%d)\n", l,nOfRecords);}
			else if (j==2){
				printf ("			Physical Injury (%g/%d)\n", l,nOfRecords);}
			else if (j==3){
				printf ("			Robbery (%g/%d)\n", l,nOfRecords);}
			else if (j==4){
				printf ("			Murder (%g/%d)\n", l,nOfRecords);}
			else if (j==5){
				printf ("			Carnapping (%g/%d)\n", l,nOfRecords);}
			else if (j==6){
				printf ("			Homicide (%g/%d)\n", l,nOfRecords);}
			else if (j==7){
				printf ("			Illegal Drugs (%g/%d)\n", l,nOfRecords);}
			else if (j==8){
				printf ("			Multiple Crimes(%g/%d)\n", l,nOfRecords);}
		}
	}
	
	printf ("\n");
	printf("\t\t\t*********************************************\n");
	printf ("\n				Lowest Crime Rate : (%.2f%%)\n",(s / nOfRecords )* 100 );
	printf ("\n");
	
	for (i=0; i<9; i++){
		if (s == N[i]){
			j=i;
			if (j==0){
				printf ("			Theft (%g/%d)\n", s,nOfRecords);}
			else if (j==1){
				printf ("			Rape (%g/%d)\n", s,nOfRecords);}
			else if (j==2){
				printf ("			Physical Injury (%g/%d)\n", s,nOfRecords);}
			else if (j==3){
				printf ("			Robbery (%g/%d)\n", s,nOfRecords);}
			else if (j==4){
				printf ("			Murder (%g/%d)\n", s,nOfRecords);}
			else if (j==5){
				printf ("			Carnapping (%g/%d)\n", s,nOfRecords);}
			else if (j==6){
				printf ("			Homicide (%g/%d)\n", s,nOfRecords);}
			else if (j==7){
				printf ("			Illegal Drugs (%g/%d)\n", s,nOfRecords);}
			else if (j==8){
				printf ("			Multiple Crimes(%g/%d)\n", s,nOfRecords);}
	
			}
		}
		
    return;
}

//For Updating Records
void updateRecord() {
if (nOfRecords!=0){	
    int option=0;
    
	do {
		printf("\n");
    	printf("=========================================================================\n");
		printf("\n");
		printf("\t\tUpdate a Record [1]\n");
		printf("\t\tBack to Mainmenu [2]\n");
		printf("\t\tEnter Choice:");
		scanf("%d", &option);
		printf("\n");
			
		if(option==2) {
			mainmenu();
		}
		else if (option==1) {
			int total;
			printf("\n");
   			printf("=========================================================================\n");
	    	printf("\n");
	    	printf("// Criminal Record List\n");
	    	
		for(int k=0; k<nOfRecords; k++) {
	        printf("[%2i]  %s (Case Code: %s)\n", k+1, criminal[k].name, criminal[k].code);
	    }
	
	    int to_update,chosen_data;
	    printf("\n");
	
	    int validUpdate = 0;
	
    do {
        printf("Select the number  from the list you want to update.: ");
        //scanf("%i",&to_update);

        int args = scanf("%i",&to_update);
        if (args < 1) {
            // Display an error message
            char dummy;
            scanf("%s", &dummy);  // eats a character off the buffer
            printf("-- Please select the correct number.\n");
            validUpdate = 0;
        }

        if (to_update <= nOfRecords){
            validUpdate = 1;
            to_update--;
        } 
		else {
            validUpdate = 0;
            printf("-- Please enter a valid number.\n");
        }

    } while (validUpdate == 0);

    do {
        //For Printing selected Criminal
        printf("\n");
    	printf("=========================================================================\n");
        printf("\t\t\t// The Criminal you've selected\n");
        printf("\n");
        printf("\t\t\tName: %s\n", criminal[to_update].name);
        printf("\t\t\tCase Code: %s\n", criminal[to_update].code);
        printf("\t\t\tAge: %d years old\n", criminal[to_update].age);
        printf("\t\t\tSex: %s\n", criminal[to_update].sex);
        printf("\t\t\tCrime: %s\n", criminal[to_update].crime);
        printf("\t\t\tBirthdate: %d-%d-%d\n", criminal[to_update].sentBD_M,criminal[to_update].sentBD_D,criminal[to_update].sentBD_Y);
        printf("\t\t\tDate of Sentence: %d-%d-%d\n", criminal[to_update].sentMM,criminal[to_update].sentDD,criminal[to_update].sentYY);
        printf("\t\t\tEmergency Contact: [+63]%s\n", criminal[to_update].contact);

        int validInput = 0;
        do {
            printf("\n\t[1]Name [2]Age [3]Sex [4]Crime [5]Birthdate [6]Date of Sentence [7]Contact [8]Done\nSelect the data that you want to Update: ");
            //scanf("%i",&chosen_data);

            int args = scanf("%i",&chosen_data);
            if (args < 1) {
                // Display an error message
                char dummy;
                scanf("%s", &dummy);  // eats a character off the buffer
                printf("\t\t\t-- Please select a correct number --\n");
                validInput = 0;
            }

            if (chosen_data <= 8) {
                validInput = 1;
            } 
			else {
                validInput = 0;
                printf("\t\t\t-- Please select a correct number --\n");
            }
            
        } while(validInput == 0);

        if(chosen_data==1) {
            int status = 0;
            int unique = 0;
            do {
                unique = 0;
                fflush(stdin);
                printf("Name: ");
                scanf("%[^\n]s", criminal[to_update].name);
                status = isNameValid(criminal[to_update].name);

                if (status == 0) {
                    printf("-- Please write the name correctly.\n");
                }

                unique = checkIfUnique();

            } while(status == 0 && unique == 1);

            if ( status == 1 && unique == 1) {
                printf("\t\t\t-- Name Updated --\n");
            }
        }
        
        else if(chosen_data==2) {
            int validAge = 0;
            do {
                printf("Age: ");

                int args = scanf("%d", &criminal[to_update].age);
                if (args < 1) {
                    // Display an error message
                    char dummy;
                    scanf("%s", &dummy);  // eats a character off the buffer
                    printf("-- Please enter a correct age [15 - 70]\n");
                    validAge = 0;
                }
                else {
                    if (criminal[to_update].age >= 15 && criminal[to_update].age <= 70) {
                        validAge = 1;
                    }

                    if(validAge == 0) {
                        printf("-- Please enter a correct age [15 - 70]\n");
                        validAge == 0;
                    }
                }

            } while (validAge == 0);

            if (validAge == 1) {
                printf("\t\t\t-- Age Updated --\n");
            }
        }
        
        else if(chosen_data==3) {
            int status = 0;
            do {
                fflush(stdin);
                printf("Sex[M/F]: ");
                scanf("%[^\n]%*c", criminal[to_update].sex);
                status = sexValid(criminal[to_update].sex);

                if (status == 0) {
                    printf("-- Please write [M/F] only\n");
                }

            } while(status == 0);

            if ( status == 1) {
                printf("\t\t\t-- Sex Updated --\n");
            }
        }
        
        else if(chosen_data==4) {
            fflush(stdin);
            int validG = 0;
            int optionForG;
            do {
                showCrime();
                printf("Crime: ");

                int args = scanf("%d", &optionForG);
                if (args < 1) {
                    // Display an error message
                    char dummy;
                    scanf("%s", &dummy);  // eats a character off the buffer
                    printf("\t\t\t-- Please input correctly.\n");
                    validG = 0;
                }
                else {
                    validG = checkCrime(optionForG, to_update);
                }

                if (args > 1 && validG == 0) {
                    printf("\t\t\t-- Please input correctly.\n");
                }

            } while(validG == 0);

            if(validG == 1) {
                printf("\t\t\t-- Crime Updated --\n");
            }
        }
        
        else if(chosen_data==5) {
	        int validD = 0;
	        int BD_M, BD_D, BD_Y;
	        char slash1, slash2;
			do {
			    printf("\nBirthdate [MM-DD-YYYY]: ");
	            int args = scanf("%d%c%d%c%d", &criminal[to_update].sentBD_M, &slash1, &criminal[to_update].sentBD_D, &slash2, &criminal[to_update].sentBD_Y);
	            if (args < 1) {
	                // Display an error message
	                char dummy;
	                scanf("%s", &dummy);  // eats a character off the buffer
	                printf("-- Please enter a correct Date [MM-DD-YYYY] \n");
	            }
	            else if ( slash1 == '-' && slash2 =='-')  {
	            	if((currentY - criminal[to_update].sentBD_Y)==criminal[to_update].age){
	            		validD = validDate (criminal[to_update].sentBD_M, criminal[to_update].sentBD_D, criminal[to_update].sentBD_Y);
					}
					else{
					validD =0;	
					}
				}
	                if (validD == 0) {
	                printf("\n-- Please enter a correct Birth Date [MM-DD-YYYY]");
	                printf("\n");
	                }
	    	
	    	} while (validD == 0);
	    	
	    	if (validD ==1){
	    		printf("\t\t\t--Birthdate Updated--");
			}
        }
        
        else if(chosen_data==6) {
            int validD = 0;
	        int MM, DD, YY;
	        char slash1, slash2;
			do {
			    printf("\nDate of Sentence [MM-DD-YYYY]: ");
	            int args = scanf("%d%c%d%c%d", &criminal[to_update].sentMM, &slash1, &criminal[to_update].sentDD, &slash2, &criminal[to_update].sentYY);
	            if (args < 1) {
	                // Display an error message
	                char dummy;
	                scanf("%s", &dummy);  // eats a character off the buffer
	                printf("-- Please enter a correct Date [MM-DD-YYYY] \n");
	            }
	            else if ( slash1 == '-' && slash2 =='-')  {
	            	if ((criminal[to_update].sentYY - criminal[to_update].sentBD_Y) >= 15){
	            		validD = validDate (criminal[to_update].sentMM, criminal[to_update].sentDD, criminal[to_update].sentYY);
					}
					else {
            		printf("\n");
					printf("\tInvalid Sentence Date");	
					}
				}
	                if (validD == 0)
	                {
	                printf("\n-- Please enter a correct Date [MM-DD-YYYY]");
	                printf("\n");
	                }
	    	
	    	} while (validD == 0);
	    	
	    	if (validD ==1) {
	    		printf("\t\t\t--Date of Sentence Updated--");
			}
        }
        
        else if(chosen_data==7) {
			int unique = 0, status=0;	
			do {
				int unique = 0;
				printf("\n");
                fflush(stdin);
                printf("Emergency Contact: [+63]");
                scanf("%[^\n]s", criminal[to_update].contact);
                status = checkContact(criminal[to_update].contact);
                printf("\n");
                	
                if (status == 0) {
                    printf("-- Please write a 10-digit number [+63].\n");
                      
                }
                else {
                	for(int i=0; i<nOfRecords; i++)
					    {
					        if(( strcmp(criminal[to_update].contact, criminal[i].contact)==0))
					        {
					           unique++;
					        }
						}
				}
				if(unique>1){
				printf("\t---------Contact is already in the List---------\n");
					status=0;
				}
			}while((unique<=1)&& (status==0));
            if ( unique <=1 && status==1) {
                printf("\t\t\t-- Emergency Contact Updated --\n");
            }
	    }
        
        else if(chosen_data==8) {
            printf("\nDone....\n");
            chosen_data += 8;
        }
    
	} while(chosen_data>0 && chosen_data<8);
	
	char choice;
	do{
	    fflush(stdin);
	    printf("\nSave? [Y/N]: ");
	    scanf(" %s",&choice);
	    
		if(choice == 'Y' || choice== 'y') {
	        write();
	        printf("\t\t\t-- Saved --\n");
	        updateRecord();
	    }
	    else if (choice == 'n' || choice== 'N') {
	        printf("\t\t\t-- Cancelled --\n");
	        updateRecord();
	    }
	    if ((choice != 'Y' || choice != 'y') || (choice != 'n' || choice != 'N')){
			printf ("\t\t -Please input [Y/N]-\n");
		}
		
	} while ((choice != 'Y' || choice != 'y') || (choice != 'n' || choice != 'N'));

		}
		 if ( option !=1 || option !=2){
			printf("		Please Pick From [1/2]\n");
			printf("\n");	
		}
		
	} while ( option !=1 || option !=2);
}
else{
    	printf("\n");
    	printf("\t\t---------------No Record Yet------------------\n\n");
    	mainmenu();
	}
}

void backupRecord() {	
	int answer;
	
if (nOfRecords==0){
	printf("\n");
    printf("=========================================================================\n");
	printf("\n\t\t Restore all record from backup files  :[1]\n");
	printf("\n\t\t\t\t\t\tCancel :[2]\n");
	
	printf("\n\t\t Enter your choice: ");
	scanf(" %i", &answer);
	

	if (answer == 1) { 
		printf("=========================================================================\n");
		printf("\n");
		printf("\t\t   Copying all records from backup file\n");

		char ch;
		FILE *source, *target;
		char source_file[]="crime_backup.txt";
		char target_file[]="crime.txt";
		
		source = fopen(source_file, "r+");
		if (source == NULL) {
			printf("\n");
	        printf("\t\t No file for record yet,\n");
	        printf("\t\t-- Please run the program again --");
	
	        fclose(source);
	
	        exit(0);
	   	}
	   
	   	target = fopen(target_file, "w+");
	   	if (target == NULL) {
	    	printf("\n");
	        printf("\t\t No file for record yet, ");
	        printf("\t\t-- Please run the program again --");
	
	        fclose(source);
	
	        exit(0);
	   	}	
	   
	    while ((ch = fgetc(source)) != EOF)
		fputc(ch, target);
		printf("\n");
		printf("\t         --All records are copied successfully!--\n");
		fclose(source);
		fclose(target);
		printf("=========================================================================\n");
		printf("\n");
	    printf("\t\t ** Please run the program again **\n");
	    printf("=========================================================================\n");
		printf("\n");
	    exit(0);
		
	}
	else if (answer == 2 ){
		printf("\n");
		printf("\t\t------Canceled------\n\n");
		mainmenu();
	}
	else{
		printf("\t\t\t-----Please chose from [ 1 / 2]-----\n");
		backupRecord();
	}
}
else{

	printf("\n");
    printf("=========================================================================\n");
	printf("\n\t\t Backup all currently existing records :[1]\n");
	printf("\n\t\t Restore all record from backup files  :[2]\n");
	printf("\n\t\t\t\t\t\tCancel :[3]\n");
	
	printf("\n\t\t Enter your choice: ");
	scanf(" %i", &answer);
	
	if (answer == 1) { 
		
	printf("=========================================================================\n");
	printf("\n");
	printf("\t\t  Copying all currently existing records\n");

		char ch;
		FILE *source, *target;
		char source_file[]="crime.txt";
		char target_file[]="crime_backup.txt";
		
		source = fopen(source_file, "r");
		if (source == NULL) {
			printf("\n");
	        printf("\t\tNo file for record yet,\n");
	        printf("\t\t-- Please run the program again --");
	
	        fclose(source);
	
	        exit(0);
	   	}
	   
	   	target = fopen(target_file, "w");
	   	if (target == NULL) {
	    	printf("\n");
	        printf("\t\tNo file for record yet, ");
	        printf("\t\t\t-- Please run the program again --");
	
	        fclose(source);
	
	        exit(0);
	   	}	
	   
		while ((ch = fgetc(source)) != EOF)
		fputc(ch, target);
		
		printf("\n");
		printf("\t      --All previous records are copied successfully!--\n");
		fclose(source);
		fclose(target);
		printf("=========================================================================\n");
		printf("\n");
	    printf("\t\t ** Please run the program again **\n");
	    printf("=========================================================================\n");
		printf("\n");
	    exit(0);
		
		
	}
	else if (answer == 2) { 
		printf("=========================================================================\n");
		printf("\n");
		printf("\t\t   Copying all records from backup file\n");

		char ch;
		FILE *source, *target;
		char source_file[]="crime_backup.txt";
		char target_file[]="crime.txt";
		
		source = fopen(source_file, "r+");
		if (source == NULL) {
			printf("\n");
	        printf("\t\t No file for record yet,\n");
	        printf("\t\t-- Please run the program again --");
	
	        fclose(source);
	
	        exit(0);
	   	}
	   
	   	target = fopen(target_file, "w+");
	   	if (target == NULL) {
	    	printf("\n");
	        printf("\t\t No file for record yet, ");
	        printf("\t\t-- Please run the program again --");
	
	        fclose(source);
	
	        exit(0);
	   	}	
	   
	    while ((ch = fgetc(source)) != EOF)
		fputc(ch, target);
		printf("\n");
		printf("\t         --All records are copied successfully!--\n");
		fclose(source);
		fclose(target);
		printf("=========================================================================\n");
		printf("\n");
	    printf("\t\t ** Please run the program again **\n");
	    printf("=========================================================================\n");
		printf("\n");
	    exit(0);
		
	}
	else if (answer == 3 ){
		printf("\n");
		printf("\t\t------Canceled------\n\n");
		mainmenu();
	}
	else{
		printf("\t\t\t-----Please chose from [ 1 / 2]-----\n");
		backupRecord();
	}
}
}

int getch(void);

void login() {
	
	int a=0,i=0;
    char uname[10],c=' '; 
    char pword[10],code[10];
    char user[10]="user";
    char pass[10]="pass";
    
	do{
	    printf("\n  =======================  LOGIN  =======================  \n");
	    printf("\n  Enter Username: ");
		scanf("%s", &uname); 
		printf("\n  Enter Password: ");
		
		while(i<10) {
	    pword[i]=getch();
	    c=pword[i];
	    	
			if(c==13) 
				break;
		    else printf("*");
		    	i++;
		}
		
		pword[i]='\0';
		//char code=pword;
		i=0;
		//scanf("%s",&pword); 
			if(strcmp(uname,"user")==0 && strcmp(pword,"pass")==0) {
				printf("\n\n\n    WELCOME! Login Sucessful!");
				printf("\n\n\n");
				//getch();//holds the screen
				break;
			}
		else {
			printf("\n\n\n    SORRY! Login Unsucessful!");
			a++;
			
			//getch();//holds the screen
		}
		
	} while(a<=2);
	
	if (a>2) {
		printf("\n\n  =======================  WARNING!  =======================  ");
		printf("\n\nYou have reached the maximum login attempts. Exit your program and try again.");
	
		exit(0);
	}
	
}

void guard() {
	
	int a=0,i=0;
	char c=' '; 
    char pword[10],code[10];
    char pass[10]="pass";
    
    printf("           ===========================================================\n");
	
	do {
		printf("\n                               Enter Password: ");
		
		while(i<10) {
		pword[i]=getch();
		c=pword[i];
			if(c==13) 
				break;
			else 
				printf("*");
			    i++;
		}
		
		pword[i]='\0';
		i=0;
	 
		if(strcmp(pword,"pass")==0) {
			return;
		}
		else {
			a++;
		}
	}
	
	while(a<=2);
		if (a>2){
			printf("\n\n           =======================  WARNING!  =======================  ");
			printf("\n\n                      !You have reached the maximum attempts!");
			printf("\n\n\n");
			mainmenu();
		}
}

