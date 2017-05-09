template < typename T >
class MapSquareList
{
	struct Entry
	{
		struct Entry* pNext;
		T tData;
	};
	Entry* _pHead;
public:
	MyLinkedList()
		: _pHead(NULL)
	{}
	void InsertHead(T tData);
	void List();
};