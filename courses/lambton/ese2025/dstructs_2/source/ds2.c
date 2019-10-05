/*
 * ds2.c
 *
 *  Created on: Oct. 3, 2019
 *      Author: takis
 */


#include <stdio.h>
#include <stdlib.h>
#include "dstructs.h"

#define		N		10

int main()
{
	int loadarr[N] = { 23, 46, 227, 81, 320,
				       17,  9,  26, 25, 22  };

	/* create a linked list from loadarr data */
	ll_t* mylisthead;
	mylisthead = (ll_t *) malloc(sizeof(ll_t));
	mylisthead -> data = loadarr[0];
	mylisthead -> pNext = NULL;
	size_t i = 1;
	while (i != N)
	{
		addNode(mylisthead, loadarr[i]);
		++i;
	}

	/* find the largest element in the list */
	int max = mylisthead -> data;
	int nexti;
	ll_t* pw = mylisthead -> pNext; /* working pointer, initialized to head's child pointer */
	while ( (pw -> pNext) != NULL )
	{
		nexti = pw -> data;
		if (max < nexti)
		{
			max = nexti;
		}
		pw = pw -> pNext; /* advance the pointer */
	}

	/* announce the results */
	printf("Your largest integer is %d", max);

	/* exit successfully */
	free(mylisthead);
	return EXIT_SUCCESS;
}
