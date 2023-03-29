//Muhammed Orhun Gale - 26754

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int numEnt = 0;

//Info arrays
char** genders;
char** names;
char** surnames;

void traverseDir(char *); //Traverse all directory and manipulate given txt files
void initilizeArrays();   //Initilizes info arrays
void getData();           //Gets data from the database and fills arrays
int searchName(char*);    //Searches that if a given name exist in the database or not
void txtManip(char*);     //Manipulates a txt file to change 

int main()
{
    //Initilize arrays that stored personal info and get data
    initilizeArrays();
    getData();

    //Start traversing directory to correct txt files
    char mainDir[200] = "."; 
    traverseDir(mainDir);

    return 0;
}


int searchName(char* name)
{
    for(int i = 0; i < numEnt; i++)
    {
        if(strcmp(name, names[i]) == 0)
        {
            return i;
        }
    }

    return -1;
}


void txtManip(char* path)
{
    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    fp = fopen(path,"r+");


    char * gen;
    char * name;
    char * surname;
    long int start = 0;
    long int cursor = 0;
    long int pos = 0;


    //Read line by line
    while (getline(&line, &len, fp) != -1) 
    {
        pos = ftell(fp);
        cursor = 0;
        //Parse line by space
        gen = strtok(line, " ");  //Parsed word will be used as gen later on since program finds a person by checking the 'hon'

        //While empty string
        while (gen != NULL) 
        {
            //If line ends label it as empty string
            if (strcmp(gen, "\n") == 0) {
                gen = strtok (NULL, " \n");
            }
            
            else{                
                cursor += strlen(gen) + 1; //Move curasor forward

                //Check if it is a gender indicator or not
                if (strcmp(gen, "Ms.") == 0 || strcmp(gen, "Mr.") == 0) {
                    
                    //If so parse next two words as name and surname
                    name = strtok (NULL, " \n");
                    surname = strtok (NULL, " \n");
                
                    //Check if it is in the database
                    int idx = searchName(name);
                    if (idx != -1) {
                        
                        //If so check if the hon is correct or not, if not correct change it to the correct one
                        if(strcmp(gen, "Ms.") == 0 && strcmp(genders[idx],"m") == 0)
                        {
                            strcpy(gen, "Mr.");
                        }

                        if(strcmp(gen, "Mr.") == 0 && strcmp(genders[idx], "f") == 0)
                        {
                            strcpy(gen, "Ms.");
                        }

                        //Check whether the surname is correct or not, if not change it with a fully changed new name
                        if (strcmp(surname, surnames[idx]) != 0) {

                            fseek (fp, start+cursor-4, SEEK_SET);
                            char replaced[strlen(gen) + strlen(name) + strlen(surname) + 2];

                            strcpy(replaced, gen);
                            strcat(replaced, " ");
                            strcat(replaced, name);
                            strcat(replaced, " ");
                            strcat(replaced, surnames[idx]);

                            fputs(replaced, fp); 
                            cursor += strlen(name) + strlen(surname) + 2;                       
                        }

                        //Just change the gender
                        else{
                            fseek (fp, start+cursor-4, SEEK_SET);
                            char replaced[strlen(gen) + strlen(name) + strlen(surname) + 2];

                            strcpy(replaced, gen);
                            strcat(replaced, " ");
                            strcat(replaced, name);
                            strcat(replaced, " ");
                            strcat(replaced, surname);

                            fputs(replaced, fp); 
                            cursor += strlen(name) + strlen(surname) + 2;   
                        }
                    }
                }
                gen = strtok (NULL, " \n");
            }
        }
        start = pos;
    }   
    fclose(fp);
}

void traverseDir(char *basePath)
{
    DIR *dir = opendir(basePath);
    char path[1000];
    struct dirent *dp;
   
   
    if (!dir)
    {
        return;
    }

    //Traverse directory
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            if(dp->d_type == DT_DIR)
            {
                strcpy(path, basePath);
                strcat(path, "/");
                strcat(path, dp->d_name);
                //If it is a directory traverse it too
                traverseDir(path);
            }

            else{
                char n[200];
                strcpy(n, dp->d_name);
                int len = strlen(n);
                if(n[len-4] == '.' && n[len-3] == 't'&& n[len-2] == 'x' && n[len-1] == 't')
                {
                    strcpy(path, basePath);
                    strcat(path, "/");
                    strcat(path, dp->d_name);
                    //If it is a txt manipulate it
                    txtManip(path);
                }
            }
        }
    }
    closedir(dir);
}


void initilizeArrays() 
{
    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    
    fp = fopen("database.txt", "r");
    while (getline(&line, &len, fp)!=-1) {
        numEnt++;
    }
    fclose(fp);


    genders = (char**) malloc(numEnt * sizeof(char*));
    names = (char**) malloc(numEnt * sizeof(char*));
    surnames = (char**) malloc(numEnt * sizeof(char*));
    for (int i = 0; i < numEnt; i++) 
    {
        genders[i] = (char*) malloc((10) * sizeof(char));
        names[i] = (char*) malloc((100) * sizeof(char));
        surnames[i] = (char*) malloc((100) * sizeof(char));

    }
}

void getData() 
{
    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    int counter = 0;
    fp = fopen("database.txt", "r");

    while (getline(&line, &len, fp) != -1) {
        char* gen = strtok(line, " \n");
        strcpy(genders[counter], gen);
        char* name = strtok(NULL, " \n");
        strcpy(names[counter], name);
        char* surname = strtok(NULL, " \n");
        strcpy(surnames[counter], surname);
        counter++;
    }
    fclose(fp);
}