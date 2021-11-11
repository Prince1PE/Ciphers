#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char* replaceChars(char* string, char find, char replace)   //I dont need this anymore
{
    //I've completly forgotten how this function works
    char *charInString = strchr(string, find);
    while (charInString)
    {
        *charInString = replace;   
        charInString= strchr(charInString,find);    
    }
    return string;  //returns string with replaced charecters
}

char* Encrypt(char* message, int key, bool Encode)
{
    static char EncryptedMessage[100];  
    int AsciiValue;
    for (int i = 0; i < strlen(message); i++)   // for each letter in message
    {
        AsciiValue = (int) message[i];  // converts letter to ascii
        if (AsciiValue == 32)
            {
                char newChar = (char) (AsciiValue);
                strncat(EncryptedMessage, &newChar, 1);
                continue;
            }
        else if (Encode)
        {
            char newChar = (char) (AsciiValue + key);   // shifts digits
            strncat(EncryptedMessage, &newChar,1);  // adds to encrypted message
        }
        else{   //If you want to decode
            char newChar = (char) (AsciiValue - key);
            strncat(EncryptedMessage, &newChar, 1);
        }
    }
    return EncryptedMessage;
}

const char* getMessage()
{
    static char message[100];
    printf("Enter your message: ");
    fgets(message, 100, stdin);
    message[strcspn(message,"\n")] = 0;
    return message;
}

int getKey()
{
    int key;
    printf("Enter the key you want to use: ");
    scanf("%i", &key);
    return key;
}

bool DecodeorEncode()
{
    char input[100];
    while (true)
    {    
        getchar();
        printf("Do you want to encode or decode?: ");
        fgets(input, 100, stdin);
        input[strcspn(input,"\n")] = 0;
        if (strstr(input, "Encode") || strstr(input, "encode"))
        {
            return true;
        }
        else if (strstr(input, "Decode") || strstr(input, "decode"))
        {
            return false;
        }
        else{
            printf("Please enter either Encode or decode.\n");
        }
    }
}

int main()
{
    //Decleration
    bool Encode;
    char message[100];
    int key;
    char EncryptedMessage[100];

    //Initialisation
    strcpy(message, getMessage());
    key = getKey();

    //Encode
    Encode = DecodeorEncode();

    //Output
    printf("Final string: %s\n",Encrypt(message, key, Encode));

}

