#include"stdfx.h"

int main()
{
	DBManager * dbManager = new DBManager();

	dbManager->SearchAccount("a123", "1234");
	return 0;
}