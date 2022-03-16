#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
void insert();
void display();
void update();
void del();

struct candidate
{
	char name[20];  //name of candidate
	char fname[20];  //Guadian name
	char dob[20];    //Date of birth
	char g;         //Gender
	long en;          //Enrollment number
 } ;
struct candidate c; 

int main() {
	int n;  //input entered by user
	
	printf("************************************************************************************************************************\n");
	printf("         ________________________________________\n");
	printf("        |                                        |\n");
	printf("        |           Welcome to UIDAI             |\n");
	printf("        |________________________________________|\n\n\n");
	printf("        Enter the input\n\n");
	printf("        1:New Registration\n");
	printf("        2:Check Aadhar card Status\n");
	printf("        3:Update Aadhar card\n");
	printf("        4:Delete Aadhar\n\n\n");
	printf("************************************************************************************************************************\n");
	scanf("%d",&n);
	switch(n){
		case 1: 
		       insert();
		       main();
		        break;
		case 2: 
		display();
		main();
		break;
		case 3: 
		update();
		main();
		 break;
		case 4: 
		 del();
		 main();
		 break;
		default:
			printf("Invalid Input\n");
			main();
	}
	return 0;
}
void insert(){
	FILE *fp;
	fp=fopen("new.txt","a+");
	if(fp==NULL){
		printf("File does not exist\n");
		return ;
	}
	fflush(stdin);
	printf("Enter Name of the candidate:\n");
	gets(c.name);
	printf("Enter Name of the Guardian:\n");
	gets(c.fname);
	printf("Enter Date of Birth:\n");
	gets(c.dob);
	printf("Enter the Gender:\n");
	scanf("%c",&c.g);
	printf("Enter the enrollment number :\n");
	scanf("%ld",&c.en);
	printf("\n\n");
	fwrite(&c,sizeof(c),1,fp);
	{   printf("        ____________________________\n");
	    printf("       |                            |\n");
 	    printf("       | Record Inserted Sucessfully|\n");
	    printf("       |____________________________|\n");
	}
	fclose(fp);
	printf("\n\n");
			
}
void display(){
	FILE *fp;
	fp=fopen("new.txt","r");
	
	if(fp==NULL){
		printf("File does not exist\n");
		return ;
	}
	printf("Candidate Record are as follows:\n\n");
	printf(" ________________________________________________________________\n");
	printf("|                                                                |\n");
	printf("|Enrollment \t Name of \tGuardian \tGender \t Date of |\n");
	
	printf("|Number \tCandidate\t  Name    \t       \t Birth   |\n");
	printf("|________________________________________________________________|\n");
	while(fread(&c,sizeof(c),1,fp)==1){
		printf(" %ld                %s           %s            %c     %s\n",c.en,c.name,c.fname,c.g,c.dob);
	}
	
	fclose(fp);	
	
}
void update(){
	  int num,flag=0;
	FILE *fp;
	fp=fopen("new.txt","r+");
	 if(fp==NULL){
		printf("File does not exist\n");
		return ;
	}
	printf("Enter the Enrollment number of Aadhar Whose Record who want update\n");
	scanf("%d",&num);
	printf("Previously Stored of given name\n");
	while(fread(&c,sizeof(c),1,fp)>0 && flag==0)
	{
		if (c.en==num){
			flag=1;
			printf(" Enrollment \t Name of \tGuardian \tGender \t Date of\n");
	printf(" Number \tCandidate\t  Name    \t       \t Birth  \n");
		         	printf(" %ld                %s           %s            %c     %s\n",c.en,c.name,c.fname,c.g,c.dob);
		    printf("Now Enter the New Record \n");
		    
		    fflush(stdin);
		    printf("Updated Name of the Candidate\n");
		    gets(c.name);
		    printf("Updated Name of the Guardian\n");
		    gets(c.fname);
		    printf("Updated Date Of the Birth\n");
		    gets(c.dob);
		    fseek(fp,-(long)sizeof(c),1);
		    fwrite(&c,sizeof(c),1,fp);
		    printf("Record Updated Sucessfully\n");
		}
	}
	if(flag==0){
		printf("Error:Something went wrong!!!\n");
		fclose(fp);
	}
}
void del(){
	char name[40];
	unsigned flag=0;
	FILE *fp,*ft;
	fp=fopen("new.txt","a+");
	if(fp==NULL){
		printf("Error:Cannot Open the File!!!\n");
		return ;
	}
	display();
	printf("Enter the enrollment number  you want to delete\n");
	scanf("%ld",&c.en);
	ft=fopen("new.txt","a+");
	while(fread(&c,sizeof(c),1,fp)==1){
		if(strcmp(name,c.name)!=0)
		{
			printf("Record Deleted Successfully\n");
			fwrite(&c,sizeof(c),1,ft);
		}
		else
		flag=1;
	}
	if(flag==0){
		printf("No Such Record Found!!!\n");
	}
	fclose(fp);
	fclose(ft);
	remove("new.txt");
	rename("new.txt","new.txt");
	display();
	
}
