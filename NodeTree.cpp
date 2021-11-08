#include "NodeTree.h"

int getInt(int left, int right)
{
    while (true) // ���� ������������ �� ��� ���, ���� ������������ �� ������ ���������� ��������
    {
        int number;
        std::cin >> number;

        // �������� �� ���������� ����������
        if (std::cin.fail()) // ���� ���������� ���������� ��������� ���������,
        {
            std::cin.clear(); // �� ���������� cin � '�������' ����� ������
            std::cin.ignore(32767, '\n'); // � ������� �������� ����������� ����� �� �������� ������
        }
        else
        {
            std::cin.ignore(32767, '\n'); // ������� ������ ��������
            if (number >= left && number <= right) return number;
        }
        std::cout << "\n\t���, �������� �������� �������. ���������� ��� ���.\n\t";
    }
}

const NodeTree& NodeTree::AddNode(int number)
{
    if (!key)
    {
        key = new int;
        *key = number;
    }
    else if (number < *key)
         {
            if(!Left) Left = new NodeTree;
            Left->AddNode(number);
         }
         else
         {
             if(!Right) Right = new NodeTree;
             Right->AddNode(number);
         }
    return *this;
}

bool NodeTree::Delete(int number)
{
    if (number < *key) { if (Left->Delete(number)) Left = nullptr; }
    else if (number > *key) { if (Right->Delete(number)) Right = nullptr; }
    else
        if (!Left && !Right)
        {
            delete this;
            return true;
        }
        else if (!Left)
        {
            delete key;
            *this = *Right;
        }
        else if (!Right)
        {
            delete key;
            *this = *Left;
        }
        else Right = Right->Del(*this);


    return false;
}

NodeTree* NodeTree::Del(NodeTree& P)
{
    if (!Left)
    {
        delete P.key;
        P.key = key;
        key = nullptr;
        return Right;
    }
    else { Left = Left->Del(P); return this; }
}

NodeTree::~NodeTree()
{
    if (key)
    {
        delete Left;
        delete Right;
        delete key;
        key = nullptr;
    }
}


const NodeTree& NodeTree::PrintTree(int h)
{
    
    if(Right) Right->PrintTree(h + 1);
    for (int i = 0; i < h; i++) std::cout << ' ';
    std::cout << *key  << std::endl;
    if(Left) Left->PrintTree(h + 1);
    return *this;
}

//���������� ��������
const NodeTree& NodeTree::randomTree(int size)
{
    srand(time(0));
    rand();
    for(; size > 0; size--) AddNode(rand() % 100);
    return *this;
}


//���������� � ����������
const NodeTree& NodeTree::inputDataTree()
{
    int number, size;
    std::cout << "\n\t������� ��������� ����� �������� � ������: ";
    size = getInt(1);
    do {
        number = getInt();
        AddNode(number);
        size--;
    } while (size > 0);
    return *this;
}

//���������� �� �����
const NodeTree& NodeTree::inputFileTree(std::string fileName)
{
    std::ifstream FileIn(fileName);
    if (!FileIn.is_open())
        throw "\n\t������� ���� <", fileName, "> �� ����� ���� ������!\n";
    else
    {
        int number;
        while (!FileIn.eof())
        {// �������� ������ ���������� ������ � ������
            FileIn >> number;
            std::cout << "������� �����: " << number << std::endl;
            AddNode(number);
        }
    }
    FileIn.close();
    return *this;
}

/*���������� ���������� ����� ���������, ������ ���������, ������� �������� � ����������.*/
int NodeTree::countGreater(int number) const
{
    int counter = 0;
    if (*key > number) counter++;
    if (Right) counter += Right->countGreater(number);
    if (Left) counter += Left->countGreater(number);
    return counter;
}
