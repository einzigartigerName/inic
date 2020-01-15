#include <stddef.h>

struct list_elem {
    struct list_elem    *next;	    // Next Element in List
    void	            *data;	    // Data
};

typedef struct list {
    size_t              size;       // Size of List
	struct list_elem    *first;     // First Element of List
	struct list_elem    *last;  	// Last Element of List
} list_t;

typedef void*   (*cpy_data)     (void *);
typedef void    (*print_elem)   (void *);
typedef int     (*cmp_elem)     (const void*, const void*);

/* function prototypes */
list_t                  *linit      ();
struct list_elem        *linsert    (list_t *list, void *data);
struct list_elem        *lappend    (list_t *list, void *data);
void                    lconcat     (list_t* dest, list_t *list);
list_t                  *lcpy       (list_t *list, cpy_data cpy);
struct list_elem        *lget       (list_t *list, size_t index);
void                    lput        (list_t *list, size_t index, void *data);
int                     lrm         (list_t *list, struct list_elem *elem);
void                    lrmf        (list_t *list);
void                    lrml        (list_t *list);
struct list_elem        *lfind      (list_t *list, void *data, cmp_elem cmp);
void                    lprint      (list_t *list, print_elem print);
void                    lrev        (list_t *list);
void                    ltoa        (list_t *list, void *arr[]);
void                    lfinit      (list_t *list, int fdata);
