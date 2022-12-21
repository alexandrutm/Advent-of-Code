#include "../lib.h"

using namespace std;
typedef unsigned long long ll;
ll CalculateVal(map<string, tuple<char, string, string, ll>> & nodes, string currentNode)
{
  auto & [opSign, leftOp, rightOp, value] = nodes[currentNode];
  if (opSign == '+')
    value = CalculateVal(nodes, leftOp) + CalculateVal(nodes, rightOp);
  else if (opSign == '-')
    value = CalculateVal(nodes, leftOp) - CalculateVal(nodes, rightOp);
  else if (opSign == '*')
    value = CalculateVal(nodes, leftOp) * CalculateVal(nodes, rightOp);
  else if (opSign == '/')
    value = CalculateVal(nodes, leftOp) / CalculateVal(nodes, rightOp);

  cout << currentNode << " = " << leftOp << " " << opSign << " " << rightOp << " value = " << value
       << "\n";
  return value;
}
void main()
{
  ifstream                                     fin("data.txt");
  string                                       line;
  map<string, tuple<char, string, string, ll>> nodes;
  while (!fin.eof())
  {
    string label, left, right;
    char   opSign = '@';
    ll     value  = 0;
    getline(fin, line);
    label = line.substr(0, line.find(':'));
    // if there is number
    const string op = line.substr(line.find(':') + 2);
    regex        rx("-?\\d+");
    smatch       match;
    regex_search(op.begin(), op.end(), match, rx);
    if (match.size() > 0)
    {
      value = stoi(match[0]);
    }
    else
    {
      vector<string> tokens;
      stringstream   check(op);
      string         intermediate;
      while (getline(check, intermediate, ' '))
      {
        tokens.push_back(intermediate);
      }

      left   = tokens[0];
      opSign = *tokens[1].c_str();
      right  = tokens[2];
    }
    nodes.insert(make_pair(label, make_tuple(opSign, left, right, value)));
  }
  cout << CalculateVal(nodes, "root");
}
