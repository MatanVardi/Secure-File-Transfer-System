#include "settings.h"

int main()
{
    FILE *input_file;
    FILE *output_file;

    char *input_path = "file.txt";
    char *output_path = "send.txt";

    input_file = fopen(input_path, "rb");
    if (input_file != NULL)
    {
        printf("The file exists!\n");

        int current_byte;
        int byte_index = 0;

        unsigned long long key = ENCRYPTION_KEY;
        unsigned char *key_bytes = (unsigned char *)&key;
        output_file = fopen(output_path, "wb");
        while ((current_byte = fgetc(input_file)) != EOF)
        {
            unsigned char encrypted_byte = (unsigned char)current_byte ^ key_bytes[byte_index % 8];
            fputc(encrypted_byte, output_file);
            byte_index++;
        }

        fclose(output_file);
        fclose(input_file);
        printf("Encryption complete!");
        printf("\n");
    }
    else
    {
        printf("The file doesn't exist");
        input_file = fopen(input_path, "w");
    }

    return 0;
}