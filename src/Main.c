#include <stdio.h>

#include "headers/Config-Reader.h"
#include "headers/Constants.h"


int main(void) {
	
	ConfigObject cfg = ReadConfig(CONFIG_PATH);

	return 0;
}