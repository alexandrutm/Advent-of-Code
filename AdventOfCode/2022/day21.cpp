#include "../lib.h"

long long CalculateVal(map<string, tuple<char, string, string, long long>> & nodes,
                       string                                                currentNode)
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

  return value;
}

void day21()
{
  ifstream                                            fin("data.txt");
  string                                              line;
  map<string, tuple<char, string, string, long long>> nodes;
  while (!fin.eof())
  {
    string    label, left, right;
    char      opSign = '@';
    long long value  = 0;
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
  // p1
  // cout << CalculateVal(nodes, "root");

  auto [opSign, leftOp, rightOp, value] = nodes["root"];
  auto      rightVal                    = CalculateVal(nodes, rightOp);
  long long firstElem                   = 0;
  long long lastElem                    = LLONG_MAX;
  while (1)
  {
    map<string, tuple<char, string, string, long long>> nodesIntermed = nodes;
    auto & [opSignHum, leftOpHum, rightOpHum, humnVal]                = nodesIntermed["humn"];
    // get random val for humn
    long long mid = firstElem + (lastElem - firstElem) / 2;
    humnVal       = mid;
    auto leftVal  = CalculateVal(nodesIntermed, leftOp);
    // cout << leftVal <<" "<< rightVal << " " << humnVal << "\n";
    if (leftVal == rightVal)
    {
      cout << humnVal;
      break;
    }
    else if (leftVal > rightVal)
    {
      firstElem = mid;
    }
    else if (leftVal < rightVal)
    {
      lastElem = mid - 1;
    }
  }
}
