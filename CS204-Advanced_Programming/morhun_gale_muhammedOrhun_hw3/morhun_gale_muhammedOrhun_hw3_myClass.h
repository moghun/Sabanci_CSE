
#include <string>
using namespace std;

struct SubSeqNode
{
	int value;
	SubSeqNode * next;

	SubSeqNode::SubSeqNode()
		: next(nullptr)
	{};


	SubSeqNode::SubSeqNode(int num, SubSeqNode* p)
		: value(num), next(p)
	{};
};

struct SubSeqHeadNode
{
	int size; // number of elements in the subsequence
	SubSeqNode * sHead; // head of the subsequence list
	SubSeqHeadNode * next;

	SubSeqHeadNode::SubSeqHeadNode()
	{};

	SubSeqHeadNode::SubSeqHeadNode(int s, SubSeqNode* lHead)
		: size(s), sHead(lHead), next(nullptr)
	{};

	SubSeqHeadNode::SubSeqHeadNode(int s, SubSeqNode* lHead, SubSeqHeadNode* r)
		: size(s), sHead(lHead), next(r)
	{};
};



class SubSeqsList
{
public:
	SubSeqsList(); //default constructor that creates an empty list

	void add(int);
	void del(int);
	bool search(int);
	void print();
	void clear();
	

private:
	SubSeqHeadNode * hHead;

	SubSeqNode* copySub(SubSeqNode*);
	int lastEl(SubSeqNode*, int);
	bool checkExist(SubSeqNode*, int);
	bool compare(SubSeqNode*, SubSeqNode*);
	void addSubSeq(SubSeqNode*, int);
	void deleteSubSeq(SubSeqNode*);
};