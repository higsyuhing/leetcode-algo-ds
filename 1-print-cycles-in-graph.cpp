/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    
    
    void helper_findcycle(Node* curr, Node* par, map<Node*, int>& color, 
                         map<Node*, int>& mark, map<Node*, Node*>& parent, 
                         int& cyclenum){
        
        if (color.count(curr) && color[curr] == 1){
            // if (color[curr] == 2) return; 
            
            // color == 1
            cyclenum++; 
            Node* tmp = par; 
            mark[curr] = cyclenum; 
            cout << curr->val << ":" << cyclenum << endl; 
            
            while (tmp != curr){
                cout << tmp->val << ":" << cyclenum << endl; 
                mark[tmp] = cyclenum; 
                tmp = parent[tmp]; 
            }
            
            return; 
        }
        
        parent[curr] = par; 
        color[curr] = 1; 
        
        for (Node* next : curr->neighbors){
            if (next == par) continue; 
            
            helper_findcycle(next, curr, color, mark, parent, cyclenum); 
        }
        
        color[curr] = 0; 
        // color[curr] = 2; 
    }
    
    
    Node* cloneGraph(Node* node) {
        
        ////// 20220715, test code for analysis for printing all cycles in the graph. 
        
        // int nodecount = graphcount(node); 
        map<Node*, int> color, mark; 
        map<Node*, Node*> parent; 
        int cyclenum = 0; 
        
        helper_findcycle(node, NULL, color, mark, parent, cyclenum); 
        
        // for (auto const& [key, cycleid] : mark){
        //     Node *curr = (Node *)key; 
        //     cout << curr->val << ":" << cycleid << endl; 
        // }
        
        
        
        
        
        
        
        
        if(node == NULL) return NULL; 
        
        unordered_map<Node*, Node*> mapo2n; 
        queue<Node *> tempqueue; 
        
        tempqueue.push(node); 
        Node *tempnode, *newnode, *neighbornode; 
        while(tempqueue.size() != 0){
            tempnode = tempqueue.front(); 
            tempqueue.pop(); 
            
            newnode = new Node(tempnode->val); 
            mapo2n[tempnode] = newnode; 
            for(int i = 0; i < tempnode->neighbors.size(); i++){
                neighbornode = tempnode->neighbors[i]; 
                if(mapo2n.find(neighbornode) == mapo2n.end())
                    tempqueue.push(neighbornode); 
            }
        }
        
        for(auto it = mapo2n.begin(); it != mapo2n.end(); it++){
            tempnode = it->first; 
            newnode = it->second; 
            
            for(int i = 0; i < tempnode->neighbors.size(); i++){
                neighbornode = tempnode->neighbors[i]; 
                newnode->neighbors.push_back(mapo2n[neighbornode]); 
            }
        }
        
        return mapo2n[node]; 
    }
};


/*
based on problem framework 133.cpp

test input: 
[[2,4],[1,3,5],[2,4,8],[1,3],[2,6,8],[5,7],[6,8],[5,7,3]]

1-2-5-6
| | | |
4-3-8-7

output: 
1:1
4:1
3:1
2:1
2:2
5:2
8:2
3:2
8:3
7:3
6:3
5:3

Note: 
- the print after the DFS might be overwritten with "mark" data structure
    print inside the function can solve this.. 
- this can also handle directed graph, iterating "next" has no effect. 
- DFS cannot find all cycles: 
    find by a depth trace: 1-2-3-4 -> 1-2-3-8-5 -> 1-2-3-8-5-6-7

update: 
- get rid of color = 2

1:1
4:1
3:1
2:1

2:2
5:2
8:2
3:2

8:3
7:3
6:3
5:3

2:4
5:4
6:4
7:4
8:4
3:4

8:5
5:5
6:5
7:5

5:6
8:6
7:6
6:6

2:7
3:7
8:7
7:7
6:7
5:7

1:8
4:8
3:8
8:8
7:8
6:8
5:8
2:8

5:9
6:9
7:9
8:9

2:10
3:10
8:10
5:10

1:11
4:11
3:11
8:11
5:11
2:11

1:12
2:12
3:12
4:12

5:13
8:13
7:13
6:13

3:14
8:14
7:14
6:14
5:14
2:14

5:15
6:15
7:15
8:15

3:16
8:16
5:16
2:16

1:17
2:17
5:17
8:17
3:17
4:17

3:18
2:18
5:18
8:18

8:19
7:19
6:19
5:19

1:20
2:20
5:20
6:20
7:20
8:20
3:20
4:20

3:21
2:21
5:21
6:21
7:21
8:21

8:22
5:22
6:22
7:22

- it will duplicately counting them.. 
    from different nodes / directions
- eliminate: storage and sort. 
    this part is not hard: define an order and then sort them. 

DONE. 

*/






