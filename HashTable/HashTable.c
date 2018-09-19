#include "HashTable.h"

//size_t StrHash(KeyDataType key)
//{
//	size_t sum = 0;
//	while (*key)
//	{
//		sum += *key;
//		key++;
//	}
//	return sum;
//}

int HashFunc(HashTable* ht, KeyDataType key)
{
	assert(ht);
	//return StrHash(key)%(ht->capacity);
	return key % ht->capacity;
}

void HashTableInit(HashTable* ht, size_t capacity)
{
	ht->_tables = (HashData*)malloc(sizeof(HashData)* capacity);
	ht->size = 0;
	ht->capacity = capacity;
	for (size_t i = 0; i < ht->capacity; i++)
	{
		ht->_tables[i].state = EMPTY;
	}
}

void IncreaseCapacity(HashTable* ht)
{
	assert(ht);
	HashTable newht;
	HashTableInit(&newht, ht->capacity * 2);
	for (size_t i = 0; i < ht->capacity; i++)
	{
		if (ht->_tables[i].state==EXITS)
			HashTableInsert(&newht, ht->_tables[i].key, ht->_tables[i].value);
	}
	HashTableDestory(ht);
	ht->_tables = newht._tables;
	ht->size = newht.size;
	ht->capacity = newht.capacity;
}

int HashTableInsert(HashTable* ht, KeyDataType key, ValueDataType value)
{
	assert(ht);
	if ((ht->size * 10/ ht->capacity)>=7)                //负载因子大于0.7，扩容
	{
		IncreaseCapacity(ht);
		//ht->_tables = (HashData*)realloc(ht->_tables, sizeof(HashData)*ht->capacity * 2);
		//ht->capacity = ht->capacity * 2;
	}
	int pos = HashFunc(ht, key);
	while (ht->_tables[pos].state == EXITS)
	{
		pos++;
		if (pos == ht->capacity)
		{
			pos = 0;
		}
	}
	ht->_tables[pos].key = key;
	ht->_tables[pos].value = value;
	ht->_tables[pos].state = EXITS;
	ht->size++;
	return 1;
}

HashData* HashTableFind(HashTable* ht, KeyDataType key)
{
	assert(ht);
	int pos = HashFunc(ht, key);
	while (ht->_tables[pos].state != EMPTY)
	{
		if (ht->_tables[pos].key == key)
		{
			printf("找到了！\n");
			return &(ht->_tables[pos]);
		}
		else
		{
			pos++;
		}
	}
	printf("没找到！\n");
	return NULL;
}

int HashTableRemove(HashTable* ht, KeyDataType key)
{
	assert(ht);
	HashData* del = HashTableFind(ht, key);
	if (del)
	{
		del->state = DELETE;
		printf("删除成功!\n");
		ht->size--;
		return 1;
	}
	return 0;
}

void HashTableDestory(HashTable* ht)
{
	assert(ht);
	free(ht->_tables);
	ht->_tables = NULL;
	ht->capacity = 0;
	ht->size = 0;
}

void PrintHashTable(HashTable* ht)
{
	assert(ht);
	size_t pos = 0;
	for (pos = 0; pos < ht->capacity; pos++)
	{
		if (ht->_tables[pos].state == EXITS)
		{
			printf("%d : %d\n", ht->_tables[pos].key, ht->_tables[pos].value);
		}
	}
}
