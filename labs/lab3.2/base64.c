#include <stdio.h>
#include "logger.h"
#include <string.h>
#include <stdlib.h>
#include <signal.h>

/*
REFERENCES 
https://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64
*/

char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
float progress;

static void showProgress(int sig);
void base64_encode(char *clrstr, char *b64dst);
void decodeblock(unsigned char in[], char *clrstr);

void decodeblock(unsigned char in[], char *clrstr)
{
    unsigned char out[4];
    out[0] = in[0] << 2 | in[1] >> 4;
    out[1] = in[1] << 4 | in[2] >> 2;
    out[2] = in[2] << 6 | in[3] >> 0;
    out[3] = '\0';
    strncat(clrstr, out, sizeof(out));
}

void b64_decode(char *b64src, char *clrdst)
{
    int ch, phase, i;
    unsigned char in[4];
    char *p;

    clrdst[0] = '\0';
    phase = 0;
    i = 0;
    while (b64src[i])
    {
        progress = ((float)i / (float)strlen(b64src)) * 100;
        if (signal(SIGINT, showProgress) == SIG_ERR)
            exit("Error in SIGINT");
        if (signal(SIGPWR, showProgress) == SIG_ERR)
            exit("Error in SIGPWR");

        ch = (int)b64src[i];
        if (ch == '=')
        {
            decodeblock(in, clrdst);
            break;
        }
        p = strchr(base64chars, ch);
        if (p)
        {
            in[phase] = p - base64chars;
            phase = (phase + 1) % 4;
            if (phase == 0)
            {
                decodeblock(in, clrdst);
                in[0] = in[1] = in[2] = in[3] = 0;
            }
        }
        i++;
    }
}

void encodeblock(unsigned char in[], char b64str[], int len)
{
    unsigned char out[5];
    out[0] = base64chars[in[0] >> 2];
    out[1] = base64chars[((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4)];
    out[2] = (unsigned char)(len > 1 ? base64chars[((in[1] & 0x0f) << 2) |
                                           ((in[2] & 0xc0) >> 6)] : '=');
    out[3] = (unsigned char)(len > 2 ? base64chars[in[2] & 0x3f] : '=');
    out[4] = '\0';
    strncat(b64str, out, sizeof(out));
}

void base64_encode(char *clrstr, char *b64dst)
{
    unsigned char in[3];
    int i, len = 0;
    int j = 0;
    b64dst[0] = '\0';
    while (clrstr[j])
    {
        progress = ((float)j / (float)strlen(clrstr)) * 100;
        if (signal(SIGINT, showProgress) == SIG_ERR)
        {
            exit("Wrong input in SIGINT");
        }

        if (signal(SIGPWR, showProgress) == SIG_ERR)
            exit("Wrong input in SIGPWR");

        len = 0;
        for (i = 0; i < 3; i++)
        {
            in[i] = (unsigned char)clrstr[j];
            if (clrstr[j])
            {
                len++;
                j++;
            }
            else
                in[i] = 0;
        }
        if (len)
        {
            encodeblock(in, b64dst, len);
        }
    }
}

int main(int argc, char **argv)
{
    // Place your magic here
    if (argc < 3)
    {
        printf("Error, not enough arguments. Usage: ./base64 --encode|--decode <input-file>\n");
        return -1;
    }

    char *buffer = NULL;
    size_t size = 0;
    FILE *fp = fopen(argv[2], "r");
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    buffer = malloc((size + 1) * sizeof(*buffer));
    fread(buffer, size, 1, fp);
    buffer[size] = '\0';
    char *result = (char *)malloc(size * 10);

    if (strcmp(argv[1], "--encode") == 0)
    {
        base64_encode(buffer, result);
        FILE *f = fopen("encoded.txt", "wb");
        fprintf(f, "%s\n", result);
        fclose(f);
    } else if (strcmp(argv[1], "--decode") == 0)
    {
        b64_decode(buffer, result);
        FILE *f = fopen("decoded.txt", "wb");
        fprintf(f, "%s\n", result);
        fclose(f);
    }
    else
    {
        printf("Invalid flag, try --encode or --decode.\n");
        return -1;
    }
    return 0;
}

static void showProgress(int sig)
{
    infof("Progress= %.0f%c\n", progress, 37);
}