#define LINE_BUFFER_SIZE        128
#define MALLOC_CHECK(pointer)   if(pointer == NULL){ \
                            fprintf(stderr, "ERROR: %s - Unable to allocate memory!\n", __func__); \
                            exit(EXIT_FAILURE);}




typedef struct{
    char            *key;
    void            *value;
} ini_key_t;

typedef struct{
    char            *name;
    int             nkeys;
    ini_key_t       **keys;
} ini_section_t;


typedef struct{
    int             nkeys;
    ini_key_t       **keys;
    int             nsections;
    ini_section_t   **sections;
} ini_file_t;

ini_file_t *parse_file(char *path);