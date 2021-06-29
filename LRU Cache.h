#include<iostream>
#include<vector>
#include<map>
#include<list>
using namespace std;
//对于LRU Cache的替换算法其实最难的地方就在于底层的结构设计
class LRUCache {
public:
	LRUCache(int capacity) {
		_capacity = capacity;
	}

	int get(int key) {
		//如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
		auto ret = _hashmap.find(key);
		if (ret != _hashmap.end())
		{
			//保证LRU机制，把刚get的数据放到链表的头上
			//说明找到了，应该把这个值从该位置提取到链表的头部位置
			list<pair<int, int>>::iterator pos = ret->second;
			pair<int, int> kv = *pos;
			_lrulist.erase(pos);
			_lrulist.push_front(kv);
			_hashmap[key] = _lrulist.begin();
			return kv.second;
		}
		else
		{
			return -1;
		}
	}

	void put(int key, int value) {
		//对于put来说，首先就是要清楚，是要插入新的，还是更新
		auto ret = _hashmap.find(key);
		if (ret != _hashmap.end())
		{
			//说明在里面找到了，那么就是更新
			list<pair<int, int>>::iterator pos = ret->second;
			_lrulist.erase(pos);
			_lrulist.push_front(make_pair(key, value)); //这里的value是新的
			//此时对于hashmap来说，这个key值所对应的迭代器也应该更新
			_hashmap[key] = _lrulist.begin();
		}
		else
		{
			//没有找到，那就进行插入新的
			//但是这里还需要再次区分1.你的cache已经满了 2.你的cache没有满
			if (_lrulist.size() == _capacity)
			{
				//情况一，已经满了
				//需要将链表的尾部进行删除，hashmap中也对应删除
				//然后在分别在list和hash中进行插入
				pair<int, int> back = _lrulist.back();
				_lrulist.pop_back();
				_hashmap.erase(back.first);
			}

			_lrulist.push_front(make_pair(key, value));
			_hashmap.insert(make_pair(key, _lrulist.begin()));
		}
	}
private:
	//之所以第二个参数存储的是迭代器，就是为了能够在链表中找到key值所在的位置
	unordered_map<int, list<pair<int, int>>::iterator> _hashmap;
	list<pair<int, int>> _lrulist;
	size_t _capacity;
};
