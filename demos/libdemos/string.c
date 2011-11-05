/*
 * $Id: string.c,v 1.2 2000/09/13 08:00:17 konkers Exp $
 * 
 * many string related functions including memcpy and buddies
 */
#include "stdlib.h"
#include "string.h"

/*
 * strlen
 *
 * works just like the library function
 */
int strlen( char * str )
{
	int len=0;
	while( *str )
	{
		len++;
		str++;
	}
	return len;
}

/*
 * strcmp 
 *
 * works just like the library function 
 */

int strcmp( char * str1, char *str2 )
{
    while( (*str1) &&
	   (*str2) &&
	   (*str1 == *str2) )
    {
	str1++;
	str2++;
    }
    return *str1 - *str2;
}

/*
 * strcpy 
 *
 * works just like the library function 
 */

char *strcpy( char *str1, char *str2 )
{
    while( *str2 ) {
	*(str1++) =  *(str2++);
    }
    *str1='\0';
    return str1;
}

/*
 * strncpy
 *
 * works just like the library function
 */
char *strncpy( char *str1, char *str2, int len )
{
    while( len-- && *str2 )
    {
		*(str1++) =  *(str2++);
    }
    *str1='\0';
    return str1;
}

/*
 * strcat
 *
 * works like the library function
 */
char *strcat( char *str1, char *str2 )
{
    while( *str1++ )
	;

    str1--;

    while( *str2 )
    {
	*str1++ = *str2++;
    }
    *str1='\0';
    return str1;
}


/*
 * strncmp
 *
 * works just like the library func
 */
int strncmp( unsigned char *str1, unsigned char *str2, int n )
{

    while( n-- && (*str1) && (*str2) && (*str1 == *str2) )
    {
	str1++;
	str2++;
    }
    return *str1 - *str2;
}

void memcpy( void *reg2, const void *reg1, unsigned int n)
{
#ifdef ASM_OPT
    asm( "cld\n\t"
	 "rep\n\t"
	 "movsb": : "c" (n), "S" (reg1), "D" (reg2));
#else
 while( n-- )
     *((unsigned char *)reg2)++ = *((unsigned char *)reg1)++;
#endif
}


void memset( void *mem, int c, size_t n )
{
#ifdef ASM_OPT
    asm( "cld\n\t"
	 "rep\n\t"
	 "stosb": :"c" (n), "a" (c), "D" (mem));
#else
    size_t i;
    for( i=0 ; i<n ; i++, *( ((unsigned char*)mem)++)=c);
#endif
}


int memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char* p1 = s1;
    const unsigned char* end1 = p1 + n;
    const unsigned char* p2 = s2;
    int                  d  = 0;

    for(;;){
        if (d || p1 >= end1) break;
        d = (int)*p1++ - (int)*p2++;
    }
    return d;
/*while( n-- )
    {
	if( *( (unsigned char *)s1) - *( (unsigned char *)s2) )
	    return *( (unsigned char *)s1) - *( (unsigned char *)s2);
	( (unsigned char *)s1)++;
	( (unsigned char *)s2)++;
		
    }
    return 0;*/
}
