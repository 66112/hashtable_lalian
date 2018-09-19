#include "HashTable.h"

void test()
{
	HashTable ht;
	HashTableInit(&ht, 4);
	/*HashTableInsert(&ht, "insert", 0);
	HashTableInsert(&ht, "sort", 1);*/
	HashTableInsert(&ht, 14, 2);
	HashTableInsert(&ht, 36, 3);
	HashTableInsert(&ht, 49, 4);
	HashTableInsert(&ht, 68, 5);
	HashTableInsert(&ht, 57, 6);
	HashTableInsert(&ht, 11, 7);
	//HashTableRemove(&ht, 11);
	//HashTableRemove(&ht, 22);
	PrintHashTable(&ht);
	HashTableDestory(&ht);
}
int main()
{
	test();
	return 0;
}