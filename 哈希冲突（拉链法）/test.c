#include "HashTable.h"
void test()
{
	HashTable ht;
	HashTableInit(&ht, 52);
	for (size_t i = 0; i < 100; i++)
	{
		HashTableInsert(&ht, i, i);
	}
	HashTableInsert(&ht, 55, 0);
	HashTableInsert(&ht, 89, 0);
	HashTableRemove(&ht, 99);
	HashTableRemove(&ht, 0);

	PrintHashTable(&ht);
	HashTableDestory(&ht);
}
int main()
{
	test();
	return 0;
}