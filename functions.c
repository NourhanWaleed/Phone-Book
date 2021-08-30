#include "functions.h"

void save (const int count){
    printf("Enter the file name and extension (eg.: textfile.txt):\n");
    gets(filename);
    FILE * fpointer;
    fpointer = fopen(filename,"w");
    for (int i = 0; i < count; i++) {
        fprintf(fpointer,"%s,%s,%d-%d-%d,%s,%s,%s\n",pcontacts[i].lastname,pcontacts[i].firstname,pcontacts[i].birthdate.day,pcontacts[i].birthdate.month,pcontacts[i].birthdate.year,pcontacts[i].address,pcontacts[i].email,pcontacts[i].phonenumber);
    }fclose(fpointer);
}
void load (int *count){
    FILE * fpointer;
    char *token;
    char *oneperson =malloc(sizeof(contact));//the data of one person will be added to this variable as string
    int n = 0;
    printf("Enter the file name and extension (eg.: textfile.txt):\n");
    gets(filename);
    setbuf(stdin,NULL);

    fpointer = fopen(filename,"r");
    if (fpointer == NULL) {
        printf("File not found. Please try again.\n");
        return;
    }

    char* test = fgets(oneperson,sizeof(contact),fpointer);
    while(test){
        token = strtok(oneperson,",");
        strcpy(pcontacts[n].lastname,token);
        token = strtok(NULL,",");
        strcpy(pcontacts[n].firstname,token);
        token = strtok(NULL,"-");
        pcontacts[n].birthdate.day = atoi(token);
        token = strtok(NULL,"-");
        pcontacts[n].birthdate.month = atoi(token);
        token = strtok(NULL,",");
        pcontacts[n].birthdate.year = atoi(token);
        token = strtok(NULL,",");
        strcpy(pcontacts[n].address,token);
        token = strtok(NULL,",");
        strcpy(pcontacts[n].email,token);
        token = strtok(NULL,",\n");
        strcpy(pcontacts[n].phonenumber,token);
        n++;
        test = fgets(oneperson,sizeof(contact),fpointer);
    }
    *(count) = n;
    free(oneperson);
    fclose(fpointer);
}
void printcontact(const int i){
    printf("Last name: %s\n",pcontacts[i].lastname);
    printf("First name: %s\n",pcontacts[i].firstname);
    printf("Date of birth: %d-%d-%d\n",pcontacts[i].birthdate.day,pcontacts[i].birthdate.month,pcontacts[i].birthdate.year);
    printf("Address: %s\n",pcontacts[i].address);
    printf("e-mail: %s\n",pcontacts[i].email);
    printf("Phone number: %s\n",pcontacts[i].phonenumber);
    printf("\n");
}
void printall(const int count){
    sort(count);
    for (int i = 0; i < count; i++) {
        printcontact(i);
    }
}
void delete(int *count){
    int n = *count,a=0,b=0;
    int i = searchlastname(n,&a,&b);
    if (i == 1){
        printcontact(a);
        printf("Are you sure you want to delete this contact? (y/n)\n");
        char yesorno[2] ;
        scanf("%s",yesorno);
        switch (yesorno[0]){
            case 'y':
                pcontacts[a] = pcontacts[(*count)-1];
                (*count)--;
                break;
            case 'n':
                return;
            default:
                printf("Invalid input. Please try again.\n");
                return;
        }
    } else if ( i > 1){
        i = searchfirstname(&a,&b);
        if (i >= 1){
            printcontact(a);
            printf("Are you sure you want to delete this contact? (y/n)\n");
            char yesorno[2] ;
            scanf("%s",yesorno);
            switch (yesorno[0]){
                case 'y':
                    pcontacts[a] = pcontacts[(*count)-1];
                    (*count)--;
                    break;
                case 'n':
                    return;
                default:
                    printf("Invalid input. Plesae try again.\n");
                    return;
            }
        } else{ return;}
    } else{ return;}
}
int searchlastname(const int count, int *a, int* b){//returns number of contacts found and changes a and b as indexes
    sort(count);
    int flag=0;
    char keyword[20];
    printf("Enter the last name : ");
    scanf("%s",keyword);
    for(int i=0; i < count; i++){
        flag=strcasecmp(pcontacts[i].lastname, keyword);
        if(flag==0){
            *a = i;
            break;
        } else if (i==(count - 1)){
            printf("Contact is not found\n");
            return 0;
        }
    }for(int i=(count - 1); i >= 0; i--){
        flag=strcasecmp(pcontacts[i].lastname, keyword);
        if(flag==0){
            *b = i;
            break;
        } else if (i == 0){
            printf("Contact is not found\n");
            return 0;
        }
    }
    if (*a == *b){
        return 1;
    } else{
        return (*b - *a)+1;//number of contacts with this last name
    }
}
void sort(const int count){
    contact temp;
    //phone number
    for (int c = 0 ; c < count - 1; c++) {
        for (int d = 0 ; d < count - c - 1; d++) {
            if (strcmp(pcontacts[d].phonenumber,pcontacts[d+1].phonenumber)>0) {
                /* Swapping */
                temp      = pcontacts[d];
                pcontacts[d]   = pcontacts[d+1];
                pcontacts[d+1] = temp;
            }
        }
    }
    //first name
    for (int e = 0 ; e < count - 1; e++) {
        for (int f = 0 ; f < count - e - 1; f++) {
            if (strcasecmp(pcontacts[f].firstname,pcontacts[f+1].firstname)>0) {
                /* Swapping */
                temp      = pcontacts[f];
                pcontacts[f]   = pcontacts[f+1];
                pcontacts[f+1] = temp;
            }
        }
    }
    //last name
    for (int g = 0 ; g < count - 1; g++) {
        for (int h = 0 ; h < count - g - 1; h++) {
            if (strcasecmp(pcontacts[h].lastname,pcontacts[h+1].lastname)>0) {
                /* Swapping */
                temp      = pcontacts[h];
                pcontacts[h]   = pcontacts[h+1];
                pcontacts[h+1] = temp;
            }
        }
    }
}
void modify(const int count){
    int a=0,b=0;
    int i = searchlastname(count,&a,&b);
    if (i == 1){
        pcontacts[a] = pcontacts[(count)-1];
        int n = count;
        Add(&n);
        return;
    } else if ( i > 1){
        i = searchfirstname(&a,&b);
        if (i >= 1){
            pcontacts[a] = pcontacts[(count)-1];
            int n = count;
            Add(&n);
            return;
        } else{ return;}
    } else{ return;}
}
void Add(int *count){
    setbuf(stdin,NULL);
    contact temp;
    char sday[3], smonth[3], syear[6];
    printf("Enter the contact details(Please do not use a comma(,) in your input)\n");
    do{
        printf("Last name: ");
        gets(temp.lastname);
    }while (!checkalpha(temp.lastname));
    do{
        printf("First name: ");
        gets(temp.firstname);
    }while (!checkalpha(temp.firstname));
    printf("Date of birth: \n");
    do {
        printf("Day: ");
        gets(sday);
    }while (!isnum(sday));
    temp.birthdate.day = atoi(sday);

    do {
        printf("Month: ");
        gets(smonth);
    }while (!isnum(smonth));
    temp.birthdate.month = atoi(smonth);
    do {
        printf("year: ");
        gets(syear);
    }while (!isnum(syear));
    temp.birthdate.year = atoi(syear);
    do {
        printf("Address: ");
        gets(temp.address);
    }while (!nocomma(temp.address));
    do {
        printf("e-mail: ");
        gets(temp.email);
    }while(!ismail(temp.email));
    do {
        printf("Phone number: ");
        gets(temp.phonenumber);
    }while(!isnum(temp.phonenumber));
    pcontacts[(*count)] = temp;
    (*count)++;
}
int isnum(char checked[12]){
    int n = strlen(checked);
    for (int i = 0; i < n; i++) {
        if (!isdigit(checked[i]) || checked[i] == ','){
            printf("Invalid input.\n");
            return 0;
        }
    }return 1;
}
int checkalpha(char checked[150]){
    int n = strlen(checked);
    for (int i = 0; i < n; ++i) {
        if((!isalpha(checked[i]) || (checked[i] == ',') )&& checked[i]!= ' '){
            printf("Invalid input.\n");
            return 0;
        }
    }
    return 1;
}
int ismail(char mail[150]){
    int atsign = 0;
    int dot = 0;
    int n = strlen(mail);
    if (n == 0){
        return 1;
    }
    if (nocomma(mail)){
        for (int i = 0; i < n; ++i) {
            if (mail[i] == '@'){
                atsign ++;
                continue;
            }if (mail[i] == '.' && atsign == 1){dot ++;}
        }if ((atsign == 1 && dot == 1)){
            return 1;
        } else{
            printf("Invalid input.\n");
            return 0;
        }
    }else{
        printf("Invalid input.\n");
        return 0;
    }
}
int nocomma(char string[150]) {
    int n = strlen(string);
    for (int i = 0; i < n; ++i) {
        if (string[i] == ',') {
            printf("Invalid input.\n");
            return 0;
        }
    }
    return 1;
}
int searchfirstname(int *a, int* b){
    int flag=0;
    char keyword[20];
    int anew = *a, bnew = *b;
    printf("Enter the first name : ");
    scanf("%s",keyword);
    for(int i= anew; i <= bnew; i++){
        flag=strcasecmp(pcontacts[i].firstname, keyword);
        if(flag==0){
            *a = i;
            break;
        } else if (i== bnew){
            printf("Contact is not found.\n");
            return 0;
        }
    }for(int i=bnew; i >= anew; i--){
        flag=strcasecmp(pcontacts[i].firstname, keyword);
        if(flag==0){
            *b = i;
            break;
        } else if (i == anew){
            printf("Contact is not found.\n");
            return 0;
        }
    }
    if (*a == *b){
        return 1;
    } else{
        return (*b - *a)+1;//number of contacts with this first name
    }
}