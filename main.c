/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Implementation of a simple shell
 *
 *        Version:  1.0
 *        Created:  Monday 19 April 2021 01:34:33  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  PRATHU BARONIA (praton), prathu.baronia@oneplus.com
 *   Organization:  OnePlus RnD
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "psh.h"

int main(int argc, char **argv)
{
	// Load any config files
	
	// Run the command loop
	psh_loop();

	// Perform shutdown and cleanup
	
	return EXIT_SUCCESS;
}
