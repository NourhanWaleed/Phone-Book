#include "functions.h"

int main(){

    setbuf(stdout,NULL);
    int count=0,a=0,b=0,found = 0;
    char choice[3];

    while(1){
        printf("Choose one of the following(by entering the choice number):\n");
        printf("1.LOAD \t2.QUERY \t3.ADD \t4.DELETE \t5.MODIFY \t6.PRINT \t7.SAVE \t8.QUIT\n");
        scanf("%s",choice);
        if (atoi(choice) > 8){
            puts("Invalid input.");
            continue;
        }
        setbuf(stdin,NULL);
        switch (choice[0]){
            case '1':
                load(&count);
                continue;
            case '2':
                if (count==0){
                    printf("Contact not found.");
                    continue;
                }
                found = searchlastname(count,&a,&b);
                if (found  != 0){
                    for (int i = a; i <= b; i++) {
                        printcontact(i);
                        printf("\n");
                    }
                }
                continue;
            case '3':
                if (count != 100){
                    Add(&count);
                } else{printf("Full phone book.\n");}
                continue;
            case '4':
                delete(&count);
                sort(count);
                continue;
            case '5':
                modify(count);
                sort(count);
                continue;
            case '6':
                sort(count);
                printall(count);
                continue;
            case '7':
                save(count);
                continue;
            case'8' :
                printf("Warning: in case you didn't save them, all of your changes will be discarded.\nDo you wish to proceed? (y/n)\n");
                char yesorno[2];
                scanf("%s",yesorno);

                switch (yesorno[0]){
                    case 'y':
                        exit(0);
                    case 'n':
                        continue;
                    default:
                        printf("Invalid input. Please try again.\n");
                }continue;

            default:
                printf("Invalid input. Please try again.\n");
                continue;
        }
    }
}