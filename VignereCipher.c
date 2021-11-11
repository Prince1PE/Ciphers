//Encrypt: Code(N) = (Message(N) + Key(N)) % 26 (+-97 for ascii)
// Code(N) = (Message(N) - Key(N)) % 26 (+-97 for ascii)

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* Encrypt(char* message, char* key, bool Encode)
{
    //Declaring variables
    static char EncryptedMessage[300];
    char tempstr[50];
    int counter = 0;
    int spaceloc[20];
    for (int i = 0; i < strlen(message); i++)
    {

        char space = ' ';
        if (message[i] == ' ')  //if there is a space
        {
            strncat(EncryptedMessage, &space, 1);   //attatch a space
            continue;   //and move on
        }//I could've done this ages ago, i dont know why i never thought of this
        if (Encode)
        {
            char AsciiMessage = ((int) tolower(message[i])) - 97;   // This gives an ascii value for the message
            char AsciiKey = ((int) tolower(key[i])) - 97;   // This gives an ascii value for the key
            char EncodedChar = (char) (((AsciiMessage + AsciiKey) % 26) + 97);  //This works out what the encoded value is
            strncat(EncryptedMessage, &EncodedChar, 1); //And adds it to the encoded message
            // printf("%c (%i) + %c (%i) = %c(%i)\n", message[i], AsciiMessage, key[i], AsciiKey, EncodedChar, (int) EncodedChar - 97);
        }
        else{
            char AsciiMessage = ((int) tolower(message[i])) - 97;
            char AsciiKey = ((int) tolower(key[i])) - 97;
            char EncodedChar;
            if(((AsciiMessage - AsciiKey) % 26) < 0)    //This will check if the ascii value is below 0
            {
                EncodedChar = (char) (((AsciiMessage - AsciiKey) % 26) + 123);  // 123 = 97 + 26
            }
            else{
                EncodedChar = (char) (((AsciiMessage - AsciiKey) % 26) + 97);
            }
            strncat(EncryptedMessage, &EncodedChar, 1);
        
        // printf("%c (%i) - %c (%i) = %c(%i)\n", message[i], AsciiMessage, key[i], AsciiKey, EncodedChar, (int) EncodedChar - 97);
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

const char* getKey(char* message)
{

    static char key[100];
    char input[100];
    char space = ' ';
    printf("Enter your key: ");
    fgets(input, 100, stdin);
    input[strcspn(input,"\n")] = 0;
    //TODO
    //Check for non alphabetic charecters
    //Check for spaces

    for (int i = 0; i < strlen(message); i++)
    {
        if (message[i] == ' ')
        {
            strncat(key, &space, 1);
        }
        
        strncat(key, &input[i % strlen(input)],1);
    }
    return key;
}

bool DecodeorEncode()
{
    char input[100];
    while (true)
    {    
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
    char key[100];
    char EncryptedMessage[100];

    //Initialisation
    strcpy(message, getMessage());
    strcpy(key, getKey(message));
    Encode = DecodeorEncode();
    //Split into different words and encode one at a time

    //Encode
    strcpy(EncryptedMessage, Encrypt(message, key, Encode));
    printf("Final string: %s\n", EncryptedMessage);
    //Output
    // Encrypt(message, key, Encode);
}

