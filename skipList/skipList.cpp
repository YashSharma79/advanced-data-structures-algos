#include <iostream>
#include <random>
#include "skipList.h"

int skipList::randomGenerator()
{
    std::random_device rd;                        // obtain a random number from hardware
    std::mt19937 gen(rd());                       // seed the generator
    std::uniform_int_distribution<> distr(1, 50); // define the range

    if (distr(gen) % 2 == 0)
    {
        return 1;
    }
    return 0;
}

node::node(int k, const std::string &v, int level)
    : key(k), value(v)
{
    for (int i = 0; i < level; ++i)
        next.__emplace_back(nullptr);
}

skipList::skipList()
{
    // Initialize the head of the skip list

    // smallest possible key
    maxLevel = 10;
    int headKey = std::numeric_limits<int>::min();
    head = new node(headKey, "head", maxLevel);

    // Initialize the last element of the list

    // largest possible key
    int nilKey = std::numeric_limits<int>::max();
    last = new node(nilKey, "NIL", maxLevel);

    // Connect start to end
    // connect all the levels/forward pointers of the head to NIL
    for (size_t i = 0; i < head->next.size(); ++i)
    {
        head->next[i] = last;
    }
}

skipList::~skipList()
{
    delete head;
    delete last;
}

string skipList::search(int key)
{
    node *currentNode = head;
    for (int i = maxLevel - 1; i >= 0; i--)
    {
        while (currentNode->next[i] != NULL)
        {
            if (currentNode->next[i]->key == key)
            {
                return currentNode->next[i]->value;
            }

            else if (currentNode->next[i]->key < key)
            {
                currentNode = currentNode->next[i];
            }
            else
            {
                break;
            }
        }
    }
    return NULL;
}

node *skipList::createNewNode(int key, string value, int level)
{
    node *newNode = new node(key, value, level);
    newNode->key = key;
    newNode->value = value;
    newNode->next.__emplace_back(nullptr);
    return newNode;
}

void skipList::insert(int key, string value)
{
    node *currentNode = head;
    // Initialise the update vector
    vector<node *> update(head->next);

    for (int i = maxLevel - 1; i >= 0; i--)
    {
        while (currentNode->next[i] != NULL && currentNode->next[i]->key < key)
        {
            currentNode = currentNode->next[i];
        }
        update[i] = currentNode;
    }

    //Update existing node
    if (currentNode->key == key)
    {
        currentNode->value = value;
    }

    else
    {
        cout << "Adding new node\n";

        node *node_tmp = currentNode->next[0];
        node *new_node = createNewNode(key, value, 10);
        new_node->next[0] = node_tmp;
        currentNode->next[0] = new_node;
        int level = 0;

        while (randomGenerator() && (level < maxLevel))
        {
            cout << "Adding new level\n";
            level++;
            node *node_itr = update[level];
            new_node->next[level] = node_itr->next[level];
            node_itr->next[level] = new_node;
        }
    }
}

void skipList::delete_key(int key)
{
    node *currentNode = head;
    vector<node *> update(head->next);

    for (int i = maxLevel - 1; i >= 0; i--)
    {
        while (currentNode->next[i] != NULL && currentNode->next[i]->key < key)
        {
            currentNode = currentNode->next[i];
        }

        update[i] = currentNode;
    }

    currentNode = currentNode->next[0];
    if (currentNode->key == key)
    {
        for (int i = maxLevel - 1; i >= 0; i--)
        {
            if (update[i]->next[i] == currentNode)
            {
                update[i]->next[i] = currentNode->next[i];
            }
        
            // delete currentNode;
        }

        //update list level
        while ((this->maxLevel > 1) && head->next[this->maxLevel] == NULL)
        {
            this->maxLevel = this->maxLevel - 1;
        }
    }
}

void skipList::print_list()
{

    for (int i = maxLevel - 1; i >= 0; i--)
    {
        node *currentNode = head;
        while(currentNode->next[i] != nullptr)
        {
            cout << "Key:" << currentNode->key;
            cout << " Value:" << currentNode->value;
            cout << " " ;
            currentNode = currentNode->next[i];
        }
        cout << " " <<endl;
    }

}

int main()
{

    int n;
    int key;
    string value;
    skipList list;

    cout << " The number of elements you want to   " << endl;
    cin >> n;
    cout << " Please enter the key/value to insert into skiplist " << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> key >> value;
        list.insert(key, value);
    }
    list.print_list();

    cout << "Enter the key to delete from skiplist" << endl;
    cin>>key;
    list.delete_key(key);
    list.print_list();

    return 0;
}
