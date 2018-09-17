#include "HashTable.h"
//size_t StrHash(KeyData key)
//{
//	size_t sum = 0;
//	while (*key)
//	{
//		sum += *key;
//	}
//	return sum;
//}

size_t HashFunc(HashTable* ht, KeyData key)        //计算位置
{
	assert(ht);
	return key%(ht->capacity);
}

HashData* BuyNode(KeyData key, ValueData value)
{
	HashData* newNode = (HashData*)malloc(sizeof(HashData));
	newNode->_key = key;
	newNode->_value = value;
	newNode->_next = NULL;
	return newNode;
}
size_t CheckPrime(size_t capacity)
{
	for (int i = 0; i < _PrimeSize; i++)
	{
		if (_PrimeList[i]>capacity)
		{
			return _PrimeList[i];
		}
	}
	return 0;
}

void HashTableInit(HashTable* ht, size_t capacity)
{
	assert(ht);
	ht->_data = (HashData**)malloc(sizeof(HashData*)*capacity);   //哈希表里只存每个桶的指针
	for (size_t i = 0; i < capacity; i++)
	{
		ht->_data[i] = NULL;
	}
	ht->capacity = capacity;
	ht->size = 0;
}

HashData* HashTableFind(HashTable* ht, KeyData key)
{
	assert(ht);
	size_t pos = HashFunc(ht, key);
	HashData* cur = ht->_data[pos];
	while (cur)
	{
		if (cur->_key == key)
		{
			printf("找到了->%d: %d\n",cur->_key,cur->_value);
			return cur;
		}
		cur = cur->_next;
	}
	printf("没找到！\n");
	return NULL;
}

void IncreaseCapacity(HashTable* ht)
{
	assert(ht);
	HashTable newht;
	HashTableInit(&newht, CheckPrime(ht->capacity));
	for (size_t i = 0; i < ht->capacity; i++)
	{
		if (ht->_data[i])
		{
			HashData* cur = ht->_data[i];
			while (cur)
			{
				HashTableInsert(&newht, cur->_key, cur->_value);
				cur = cur->_next;
			}
		}
	}
	HashTableDestory(ht);
	ht->_data = newht._data;
	ht->capacity = newht.capacity;
	ht->size = newht.size;
}

int HashTableInsert(HashTable* ht, KeyData key, ValueData value)
{
	assert(ht);
	size_t pos = HashFunc(ht, key);
	HashData* newNode = BuyNode(key, value);    
	if (ht->size == ht->capacity)
	{
		IncreaseCapacity(ht);
	}
	newNode->_next = ht->_data[pos];			//头插
	ht->_data[pos] = newNode;
	ht->size++;
	return 1;
}

int HashTableRemove(HashTable* ht, KeyData key)
{
	assert(ht);
	size_t pos = HashFunc(ht, key);
	HashData* cur = NULL, *prev = NULL;
	cur = ht->_data[pos];
	while (cur)
	{
		if (cur->_key == key)
		{
			if (prev == NULL)
				ht->_data[pos] = cur->_next;
			else
				prev->_next = cur->_next;
			free(cur);
			cur = NULL;
			ht->size--;
			printf("删除成功！\n");
			return 1;
		}
		prev = cur;
		cur = cur->_next;
	}
	printf("删除失败！\n");
	return 0;
}

void HashTableDestory(HashTable* ht)
{
	assert(ht);
	for (size_t i = 0; i < ht->capacity; i++)
	{
		HashData* pos = ht->_data[i];    
		if (pos != NULL)	                    //不能释放哈希表中的元素，只能释放桶中的元素
		{
			while (pos)                        //销毁一个位置挂的桶
			{
				HashData* del = pos->_next;
				free(pos);
				pos = NULL;
				pos = del;
			}
		}
	}
	free(ht->_data);                 //销毁哈希表
	ht->_data = NULL;
	ht->capacity = 0;
	ht->size = 0;
}

void PrintHashTable(HashTable* ht)
{
	assert(ht);
	size_t i = 0;
	for (i = 0; i < ht->capacity; i++)
	{
		HashData* pos = ht->_data[i];
		if (pos != NULL)
		{
			while (pos)
			{
				printf("%d : %d\n", pos->_key, pos->_value);
				pos = pos->_next;
			}
		}
	}
}


