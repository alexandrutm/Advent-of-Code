#include "../lib.h"

string MOVEIN    = "$ cd";
string MOVEOUT   = "$ cd ..";
string GOTOROOT  = "$ cd /";
string PRINTLIST = "$ ls";

ull MaxSize        = 100000;
ull AvailableSpace = 70000000;
ull UnusedSpace    = 30000000;

// NecessaySpace-(AvailableSpace-rootSize)
ull MustFree = 10216456;

vector<ull> dirSizes1;
vector<ull> dirSizes2;

struct Node
{
  string         data;
  vector<Node *> child;

  Node * dad;

  ull size = 0;

  bool visited = false;
};

Node * newNode(string data, Node * dad)
{
  Node * temp = new Node;
  temp->data  = data;
  temp->dad   = dad;
  return temp;
}

bool comparesubstr(string str1, string str2)
{
  string cdroot  = "/";
  string moveout = "..";

  if (str1.substr(0, 4) == str2)
  {
    if ((str1.find(cdroot) == string::npos) && (str1.find(moveout) == string::npos))
      return true;
  }

  return false;
}

int DFS(Node * root)
{
  root->visited = true;

  std::stringstream ss(root->data);
  ull               size;
  ss >> size;

  // file
  if (root->child.size() == 0)
    return size;

  for (auto node : root->child)
    if (!node->visited)
    {
      root->size += DFS(node);
    }

  if (root->size < MaxSize)
    dirSizes1.push_back(root->size);

  if (root->size > MustFree)
    dirSizes2.push_back(root->size);

  return root->size;
}

void day07()
{
  ifstream fin("data.txt");

  string line;

  Node * currentNode = newNode("/", nullptr);
  Node * root        = currentNode;

  bool add = false;

  while (!fin.eof())
  {
    getline(fin, line);

    if (line == PRINTLIST)
    {
      add = true;
      continue;
    }
    else if (comparesubstr(line, MOVEIN))
    {
      for (auto node : currentNode->child)
      {
        if (line.find(node->data.substr(4)) != string::npos)
        {
          currentNode = node;

          add = false;
          break;
        }
      }
      continue;
    }
    else if (line == MOVEOUT)
    {
      currentNode = currentNode->dad;
      continue;
    }
    else if (line == GOTOROOT && root != currentNode)
    {
      currentNode = root;
      continue;
    }

    if (add)
      currentNode->child.push_back(newNode(line, currentNode));
  }

  DFS(root);
  cout << "First Half: " << accumulate(dirSizes1.begin(), dirSizes1.end(), 0);

  cout << "Second half: " << *min_element(dirSizes2.begin(), dirSizes2.end());
}

void main()
{
  day07();
}
