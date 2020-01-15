# inic
basic .ini file parser

## Structs
* ini_file_t
    - `int nsections`: number of parsed sections
    - `ini_section_t **sections`: array of sections
    - `int nkeys`: number of parsed keys who are not part of a section
    - `ini_key_t **keys`: array of keys who are not part of a section

* ini_section_t
    - `char *name`: name of the section
    - `int nkeys`: number of keys stored in this section
    - `ini_key_t **keys`: array of keys in this section

* ini_key_t
    - `char *key`: key
    - `char *value`: value stored as string

## Usage
Place `inic.c`, `inic.h`, `list.h` and `list.c` in your project and include `inic.h`
```C
#include "path/to/inic.h"
.
.
```

Available functions:
* `parse_file`: gets path to file; returns pointer to `ini_file_t`
* `get_section`: gets `ini_file_t`, section name to search for and index if multiple sections with the same name exist (index start at 0); return pointer to found section as `*ini_section_t` (NULL if not found)
* `get_value`: gets section and key; returns value as `char *` (NULL if not found)