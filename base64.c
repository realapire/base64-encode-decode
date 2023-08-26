#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

const char *base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *base64_encode(const unsigned char *data, size_t input_length)
{
    size_t output_length = 4 * ((input_length + 2) / 3);
    char *encoded_data = (char *)malloc(output_length + 1);
    if (encoded_data == NULL)
    {
        return NULL;
    }

    for (size_t i = 0, j = 0; i < input_length;)
    {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        encoded_data[j++] = base64_chars[(triple >> 18) & 0x3F];
        encoded_data[j++] = base64_chars[(triple >> 12) & 0x3F];
        encoded_data[j++] = base64_chars[(triple >> 6) & 0x3F];
        encoded_data[j++] = base64_chars[triple & 0x3F];
    }

    while (output_length > 0 && encoded_data[output_length - 1] == '=')
    {
        output_length--;
    }
    encoded_data[output_length] = '\0';

    return encoded_data;
}

unsigned char *base64_decode(const char *input, size_t *output_length)
{
    size_t input_length = strlen(input);
    if (input_length % 4 != 0)
    {
        return NULL;
    }

    *output_length = (3 * input_length) / 4;
    if (input[input_length - 1] == '=')
    {
        (*output_length)--;
    }
    if (input[input_length - 2] == '=')
    {
        (*output_length)--;
    }

    unsigned char *decoded_data = (unsigned char *)malloc(*output_length);
    if (decoded_data == NULL)
    {
        return NULL;
    }

    size_t j = 0;
    uint32_t sextet_bits = 0;
    int sextet_count = 0;

    for (size_t i = 0; i < input_length; i++)
    {
        uint32_t base64_value = 0;
        if (input[i] == '=')
        {
            base64_value = 0;
        }
        else
        {
            const char *char_pointer = strchr(base64_chars, input[i]);
            if (char_pointer == NULL)
            {
                free(decoded_data);
                return NULL; // Invalid Base64 character
            }
            base64_value = char_pointer - base64_chars;
        }

        sextet_bits = (sextet_bits << 6) | base64_value;
        sextet_count++;

        if (sextet_count == 4)
        {
            decoded_data[j++] = (sextet_bits >> 16) & 0xFF;
            decoded_data[j++] = (sextet_bits >> 8) & 0xFF;
            decoded_data[j++] = sextet_bits & 0xFF;
            sextet_bits = 0;
            sextet_count = 0;
        }
    }

    return decoded_data;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <input>\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    size_t input_length = strlen(input);

    int is_base64 = 1;
    for (size_t i = 0; i < input_length; i++)
    {
        if (strchr(base64_chars, input[i]) == NULL && input[i] != '=')
        {
            is_base64 = 0;
            break;
        }
    }

    if (is_base64)
    {
        size_t decoded_length;
        unsigned char *decoded_data = base64_decode(input, &decoded_length);
        if (decoded_data != NULL)
        {
            decoded_data[decoded_length] = '\0';
            printf("Decoded Value: %s\n", decoded_data);
            free(decoded_data);
        }
        else
        {
            printf("Decoding failed.\n");
        }
    }
    else
    {
        char *encoded_data = base64_encode((unsigned char *)input, input_length);
        if (encoded_data != NULL)
        {
            printf("Encoded Base64: %s\n", encoded_data);
            free(encoded_data);
        }
        else
        {
            printf("Encoding failed.\n");
        }
    }

    return 0;
}