#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "inic.h"
#include "list.h"

/*
* @param char* - line to parse
* @return ini_section_t* - section with name but rest is NULL
*/
ini_section_t *parse_section(char *line){

    int name_len = 0;
    char *current = line + 1;
    while(*current != ']'){
        name_len++;
        current = current + 1;
    }

    char *sec_name = malloc((name_len + 1) * sizeof(char));
    MALLOC_CHECK(sec_name);
    
    strncpy(sec_name, line + 1, name_len);
    sec_name[name_len] = '\0';

    ini_section_t *out = malloc(sizeof(ini_section_t));
    MALLOC_CHECK(out);

    out->name = sec_name;
    return out;
}


/*
* @param char* - line to parse
* @return ini_key_t* - parsed key with value
*/
ini_key_t *parse_key(char *line){
    return NULL;
}


/*
* @param char* - path to ini file
* @return ini_file_t* - parsed file with all sections and keys
*/
ini_file_t *parse_file(char *path){
    // open file
    FILE *fd = fopen(path, "r");
    if(fd == NULL){
        perror(path);
    }

    // struct to return
    ini_file_t *ini_file = malloc(sizeof(ini_file_t));

    // tmp list for flexible section/key storing
    list_t *li_sections = linit();
    list_t *li_keys = linit();

    ini_key_t **arr_keys = NULL;
    ini_section_t *sec = NULL;

    char line [LINE_BUFFER_SIZE];
    // read file line by line and parse
    while(fgets(line, sizeof line, fd) != NULL){

        switch(line[0]){
            // skip empty line
            case '\n':
                continue;

            // section
            case '[':
                // no section was bevor this section
                if(li_keys->size != 0){
                    arr_keys = malloc(li_keys->size * sizeof(ini_key_t *));
                    MALLOC_CHECK(arr_keys);

                    ltoa(li_keys, (void **) arr_keys);
                    // no section bevor this one
                    if(sec == NULL){
                        ini_file->keys = arr_keys;
                        ini_file->nkeys = li_keys->size;
                    } else {
                        sec->keys = arr_keys;
                        sec->nkeys = li_keys->size;

                        // clear pointer for next section
                        sec = NULL;
                    }

                    lfinit(li_keys, 0);
                    li_keys = linit();
                }

                // new sections
                sec = parse_section(line);
                lappend(li_sections, sec);
                break;

            // default: key
            default:
                lappend(li_keys, parse_key(line));
        }
    }

    // add keys to last section
    arr_keys = malloc(li_keys->size * sizeof(ini_key_t *));
    MALLOC_CHECK(arr_keys);
    ltoa(li_keys, (void **) arr_keys);

    sec->nkeys = li_keys->size;
    sec->keys = arr_keys;


    // add all sections to ini_file
    ini_section_t **arr_section = malloc(li_sections->size * sizeof(ini_section_t *));
    MALLOC_CHECK(arr_section);
    ltoa(li_sections,(void **) arr_section);

    ini_file->sections = arr_section;
    ini_file->nsections = li_sections->size;

    // close file
    fclose(fd);

    // free list pointer (not data)
    lfinit(li_sections, 0);
    lfinit(li_keys, 0);

    // return array of sections
    return ini_file;
}