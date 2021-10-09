#include <vector>
#include <string>

using namespace std;
//A level i node has i forward pointers indexed through 1 to i
//No need to store level of node in the node? Why?
//Multiple forward pointers
// First forward pointer points to level 1
//Second forward pointer points to level 2
// Going down means using the next forward pointer
struct node
{
    node (int k, const std::string& v, int level);
    int key;
    string value;
    time_t timestamp;
    bool deleted;
    vector<node*> next;
};

class skipList
{
public:
    skipList();
    ~skipList();
    int maxLevel;
    void insert(int key, string value);
    void delete_key(int key);
    string search(int value);
    node* createNewNode(int key, string val, int level);
    void print_list();
private:
    node* head;
    node* last;
    int randomGenerator();
};
