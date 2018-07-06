/*************************************************************
 *
 * $Id: ListTest.c 1972 2014-11-12 10:23:55Z phil $
 * 
 *************************************************************
 */
/**
 * Sample test program for generic Lists : application to strings.
 *
 *************************************************************/

static char rcsId[] = "@(#) $Id: ListTest.c 1972 2014-11-12 10:23:55Z phil $";

#include <stdio.h>
#include <string.h>
#include "List.h"


/*************************************************************
 * Function to compare two elements (strings) : based on strcmp
 * @param s1 the first string to compare
 * @param s2 the second string to compare
 * @return <0 if s1 is less than s2
 * @return 0 if s1 equals s2
 * @return >0 otherwise
 *************************************************************/
static int compString (void * s1, void * s2) {
  return strcmp((char*)s1, (char*)s2);
}

/*************************************************************
 * Function to display an element of the list
 * @param s the string to display
 *************************************************************
 */
static void prString(void * s) {
  printf("%s",(char*)s);
}

/*************************************************************
 * another display function, just to test "forEach"
 * @param s the string to display
 *************************************************************/
static void prString2 (void * s) {
  printf("%s\n",(char*)s);
}

/*************************************************************
 * test program: creation of a list of strings then tests
 * for main list functionalities.
 *************************************************************/

int main() {
  int i;
  char * tab[] = {"belle marquise", "vos beaux yeux", "me font",
		  "mourir", "d'amour" };

  /* list creation */
  List* l = newList(compString,prString);
  if (!l) return 1;

  /* populating list */
  for (i=0; i < sizeof(tab)/sizeof(char*); i++)
    addList(l,tab[i]);

  /* display list - should be sorted */
  displayList(l);
  putchar('\n');

  /*  test contain predicate */
  if (isInList(l,"mourir"))
    puts("mourir is in list");
  else
    puts("mourir is not in list");
  if (isInList(l,"vivre"))
    puts("vivre is in list");
  else
    puts("vivre is not in list");

  /* test length (beware: sizeof is long int!) */
  printf("length : %d (expected %ld)\n", lengthList(l),
	 sizeof(tab)/sizeof(char*));

  /* test forEach */
  puts("forEach:");
  forEach(l,prString2);
  
  /* final cleanup */
  delList(l);

  return 0;
}
/*************************************************************/
