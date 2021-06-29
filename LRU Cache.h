#include<iostream>
#include<vector>
#include<map>
#include<list>
using namespace std;
//����LRU Cache���滻�㷨��ʵ���ѵĵط������ڵײ�Ľṹ���
class LRUCache {
public:
	LRUCache(int capacity) {
		_capacity = capacity;
	}

	int get(int key) {
		//�����Կ (key) �����ڻ����У����ȡ��Կ��ֵ�����������������򷵻� -1��
		auto ret = _hashmap.find(key);
		if (ret != _hashmap.end())
		{
			//��֤LRU���ƣ��Ѹ�get�����ݷŵ������ͷ��
			//˵���ҵ��ˣ�Ӧ�ð����ֵ�Ӹ�λ����ȡ�������ͷ��λ��
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
		//����put��˵�����Ⱦ���Ҫ�������Ҫ�����µģ����Ǹ���
		auto ret = _hashmap.find(key);
		if (ret != _hashmap.end())
		{
			//˵���������ҵ��ˣ���ô���Ǹ���
			list<pair<int, int>>::iterator pos = ret->second;
			_lrulist.erase(pos);
			_lrulist.push_front(make_pair(key, value)); //�����value���µ�
			//��ʱ����hashmap��˵�����keyֵ����Ӧ�ĵ�����ҲӦ�ø���
			_hashmap[key] = _lrulist.begin();
		}
		else
		{
			//û���ҵ����Ǿͽ��в����µ�
			//�������ﻹ��Ҫ�ٴ�����1.���cache�Ѿ����� 2.���cacheû����
			if (_lrulist.size() == _capacity)
			{
				//���һ���Ѿ�����
				//��Ҫ�������β������ɾ����hashmap��Ҳ��Ӧɾ��
				//Ȼ���ڷֱ���list��hash�н��в���
				pair<int, int> back = _lrulist.back();
				_lrulist.pop_back();
				_hashmap.erase(back.first);
			}

			_lrulist.push_front(make_pair(key, value));
			_hashmap.insert(make_pair(key, _lrulist.begin()));
		}
	}
private:
	//֮���Եڶ��������洢���ǵ�����������Ϊ���ܹ����������ҵ�keyֵ���ڵ�λ��
	unordered_map<int, list<pair<int, int>>::iterator> _hashmap;
	list<pair<int, int>> _lrulist;
	size_t _capacity;
};
