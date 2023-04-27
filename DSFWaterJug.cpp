#include <stack> 
#include <map> 
#include <algorithm> 
using namespace std; 
// Representation of a state (x, y) 
// x and y are the amounts of water in litres in the two jugs respectively 
struct state 
{ 
int x, y; 
// Used by map to efficiently implement lookup of seen states 
bool operator < (const state& that) const 
{ 
if (x != that.x) return x < that.x; 
return y < that.y; 
} 
};
// Capacities of the two jugs respectively and the target amount int 
capacity_x, capacity_y, target; 
void dfs(state start, stack <pair <state, int> >& path) 
{ 
stack <state> s; 
state goal = (state) {-1, -1}; 
// Stores seen states so that they are not revisited and 
// maintains their parent states for finding a path through 
// the state space 
// Mapping from a state to its parent state and rule no. that 
// led to this state 
map <state, pair <state, int> > parentOf; 
s.push(start); 
parentOf[start] = make_pair(start, 0); 
while (!s.empty()) 
{ 
// Get the state at the front of the stack 
state top = s.top(); 
s.pop(); 
// If the target state has been found, break if 
(top.x == target || top.y == target) 
{ 
goal = top;
break;
} 
// Find the successors of this state 
// This step uses production rules to produce successors of the current state 
// while pruning away branches which have been seen before 
// Rule 1: (x, y) -> (capacity_x, y) if x < capacity_x 
// Fill the first jug 
if (top.x < capacity_x) 
{ 
state child = (state) {capacity_x, top.y}; 
// Consider this state for visiting only if it has not been visited before if 
(parentOf.find(child) == parentOf.end()) 
{ 
s.push(child); 
parentOf[child] = make_pair(top, 1); 
} 
} 
// Rule 2: (x, y) -> (x, capacity_y) if y < capacity_y 
// Fill the second jug 
if (top.y < capacity_y) 
{ 
state child = (state) {top.x, capacity_y}; 
if (parentOf.find(child) == parentOf.end()) 
{ 
s.push(child); 
parentOf[child] = make_pair(top, 2); 
} 
} 
// Rule 3: (x, y) -> (0, y) if x > 0 
// Empty the first jug if 
(top.x > 0) 
{ 
state child = (state) {0, top.y}; 
if (parentOf.find(child) == parentOf.end()) 
{ 
s.push(child); 
parentOf[child] = make_pair(top, 3); 
} 
} 
// Rule 4: (x, y) -> (x, 0) if y > 0 
// Empty the second jug if 
(top.y > 0) 
{ 
state child = (state) {top.x, 0}; 
if (parentOf.find(child) == parentOf.end()) 
{ 
s.push(child); 
parentOf[child] = make_pair(top, 4); 
}