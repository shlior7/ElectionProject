#define _CRTDBG_MAP_ALLOC
#include "Menu.h"
#include <crtdbg.h>
/***  Summary
 ******************************************
 *Welcome to our Election Application! ****
 *efficient and organized *****************
 *and totally Russian hacker proof ********
 *just follow the menu ********************
 *Initialize your country *****************
 *and it will do the rest *****************
 *calculating Representatives *************
 *and voting percentages ******************
 *enjoy!!:) *******************************
 ******************************************
 * Summary
 */

int main() {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
	Menu m1;
	m1.ElectionMenu();
	}
	_CrtDumpMemoryLeaks();
}
