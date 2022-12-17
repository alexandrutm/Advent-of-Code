#include "../lib.h"

struct node : public variant<int, vector<node>>
{
  node(int v)
    : variant(v)
  {
  }

  node(const vector<node> & v)
    : variant(v)
  {
  }
  bool operator<(const node & rhs) const;
};

struct CompareVisitor
{
  bool operator()(int left, int right) const { return left < right; }
  bool operator()(const vector<node> & left, const vector<node> & right) const
  {
    return lexicographical_compare(left.begin(), left.end(), right.begin(), right.end());
  }
  bool operator()(int left, const vector<node> & right) const
  {
    return operator()(vector<node>{ left }, right);
  }
  bool operator()(const vector<node> & left, int right) const
  {
    return operator()(left, vector<node>{ right });
  }
} compareVisitor;

bool node::operator<(const node & rhs) const
{
  return visit(compareVisitor, *this, rhs);
}

node parse(std::string_view & line)
{
  if (line[0] == '[')
  {
    vector<node> vr;
    if (line[1] != ']')
    {
      while (line[0] != ']')
      {
        line.remove_prefix(1);
        vr.push_back(parse(line));
      }
      line.remove_prefix(1);
    }
    else
    {
      line.remove_prefix(2);
    }
    return vr;
  }
  else
  {
    int  v;
    auto p = from_chars(line.data(), line.data() + line.size(), v);
    line.remove_prefix(p.ptr - line.data());
    return v;
  }
}

void day13()
{
  ifstream fin("data.txt");
  string   line;

  vector<node> all;
  int          sum = 0;

  while (!fin.eof())
  {
    getline(fin, line);

    string_view lineView = line;

    node v = parse(lineView);

    all.push_back(v);
    if (all.size() % 2 == 0)
    {
      getline(fin, line);
      if (all[all.size() - 2] < all.back())
      {
        sum += (all.size() / 2);
      }
    }
  }

  // p1
  cout << sum << endl;
  // p2
  string_view lineView1{ "[[2]]" };
  string_view lineView2{ "[[6]]" };

  node v2 = parse(lineView1), v6 = parse(lineView2);
  all.push_back(v2);
  all.push_back(v6);
  sort(all.begin(), all.end());
  size_t p2 = lower_bound(all.begin(), all.end(), v2) - all.begin();
  size_t p6 = lower_bound(all.begin(), all.end(), v6) - all.begin();
  cout << (p2 + 1) * (p6 + 1) << endl;
}
