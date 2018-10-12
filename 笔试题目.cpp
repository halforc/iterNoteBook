struct BSTreeNode{
	int value;
	BSTreeNode* left;
	BSTreeNode* right;
};
//二叉树转为单向链表
void flattenBSTreeToList(BSTreeNode* root){
	if(root == nullptr)
		return;
	flattenBSTreeToList(root->left);
	flattenBSTreeToList(root->right);
	BSTreeNode* temp = root->right;
	root->right = root->left;
	root->left = nullptr;
	while(root->right)
		root = root->right;
	root->right = temp;
}


//二叉树转为双向链表
void helper(BSTreeNode* head,BSTreeNode* tail,BSTreeNode* root){
	if(root == nullptr){
		head = nullptr;
		tail = nullptr;
		return;
	}
	BSTreeNode *lt,*rh;
	helper(head，lt,root->left);
	helper(rh,head,root->right);
	if(lt != nullptr){
		it->right = root;
		root->left = lt;
	}else{
		head = root;
	}
	if(rh != nullptr){
		rh->left = root;
		root->right = rh;
	}else{
		tail = root;
	}
}

void flattenBSTreeToDBList(BSTreeNode* root){
	BSTreeNode *head,*tail;
	flattenBSTreeToDBList(head,tail,root);
}

//包含min函数的栈
//使用辅助栈
/*
要获取当前栈中最小元素，只需要返回minimum stack的栈顶元素即可。
每次执行push操作，检查push的元素是否小于或等于minimum stack栈顶元素。如果是，则也push该元素到minimum stack中。
当执行pop操作的时候，检查pop的元素是否与当前最小值相等。如果相同，则需要将改元素从minimum stack中pop出去。
*/
class miniStack{
public:
	void push(int val){
		eleStack.push(val);
		if(minStack.empty() || val < minStack.top())
			minStack.push(val);
	}
	void pop(){
		if(eleStack.empty())
			throw new exception("stack is empty");
		if(eleStack.top() == minStack.top())
			minStack.pop();
		eleStack.pop();
	}
	bool min(int& val){
		if(minStack.empty())
			return false;
		val = minStack.top();
		return true;
	}
private:
	stack<int> eleStack;
	stack<int> minStack;
};
//不借用辅助栈
/*push(int elem)函数在栈中压入当前元素与当前栈中最小元素的差值，然后通过比较当前元素与当前栈中最小元素大小，并将它们中间的较小值压入。

pop()函数执行的时候，先pop出栈顶的两个值，这两个值分别是当前栈中最小值min和最后压入的元素与栈中最小值的差值diff。
如果diff<0，则表示最后压入栈的元素是最小的元素，因此只需将min-diff压入栈中，并将min值返回即可。min-diff就是当前元素弹出后，栈中剩下元素的最小值。
而如果diff>=0且栈不为空，则表示当前值不是最小值，所以需要在栈中压入最小值min并将diff+min返回；如果栈为空，则表示已经是最后一个数字，直接返回min即可。
*/
class miniStack{
public:
	void push(int val){
		if(eleStack.empty()){
			eleStack.push(val);
			eleStack.push(val);
		}else{
			int min = eleStack.top();
			eleStack.pop();
			eleStack.push(val-min);
			eleStack.push(val-min < min ? val-min : min);
		}
	}
	int pop(){
		if(eleStack.empty())
			throw new exception("stack is empty");
		int min = eleStack.top();
		eleStack.pop();
		int diff = eleStack.top();
		eleStack.pop();
		if(diff < 0){
			eleStack.push(min-diff);
			return min;
		}else{
			if(!eleStack.empty()){
				eleStack.push(min);
				return diff+min;
			}
			return min;
		}
		
	}
	int min(){		
		return eleStack.top();
	}
private:
	stack<int> eleStack;
};

//子数组最大和
int subArraySum(int a[],int n){
	if(n <= 0)
		throw new exception("array is empty");
	int max = -(1 << 31);
	int sum = 0;
	int cur = 0;
	while(cur < n){
		sum += a[cur++];
		if(sum > max){
			max = sum
		}else if(sum < 0){
			sum = 0;
		}
	}
	return max;
}

/*题目描述
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。
例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，
但4,3,5,1,2就不可能是该压栈序列的弹出序列。（注意：这两个序列的长度是相等的）*/

bool IsPopOrder(vector<int> pushV,vector<int> popV) {
	if(pushV.empty())	return false;
	vector<int> stack;
	for(int i = 0,j = 0;i<pushV.size();){
		stack.push_back(pushV[i]);
		while(j < popV.size() && stack.back() == popV[j]){
			stack.pop_back();
			++j;
		}
	}
	return stack.empty();
}

//二叉树中寻找和为某一值的所有路径
vector<vector<int>> findPath(BSTreeNode* root,int expectedNumber){
	vector<vector<int>> res;
	if(root == nullptr)	return res;
	vector<int> path;
	pathFinder(root,expectedNumber,res,path,0);
	return res;
}

void pathFinder(BSTreeNode* root,int expectedNumber,vector<vector<int>>& vec,vector<int>& path,int curSum){
	curSum += root->val;
	path.push_back(root->val);
	bool bIsLeaf = root->left == nullptr && root->right == nullptr;
	if(curSum == expectedNumber && bIsLeaf){
		vec.push_back(path);
	}
	if(root->left)
		pathFinder(root->left,expectedNumber,vec,path,curSum);
	if(root->right)
		pathFinder(root->right,expectedNumber,vec,path,curSum);
	curSum -= root->val;
	path.pop_back();
}

//不用加减乘除  实现加法
int add(int num1,int num2){
	while(num2){
		int temp = num1 ^ num2;
		num2 = (num1 & num2) << 1;
		num1 = temp;
	}
	return num1;
}

//二叉树镜像
void Mirror(TreeNode *pRoot) {
	if(pRoot == nullptr)
		return;
	swap(pRoot->left,pRoot->right);
	Mirror(pRoot->left);
	Mirror(pRoot->right);
}

//最长公共子序列  不连续
/*
关系式：
			|0								i == 0 || j == 0
LCS[i][j] = |LCS[i-1][j-1]+1				x[i-1] = y[j-1]
			|max(LCS[i-1][j],LCS[i][j-1])	otherwise；
			*/
//从上到下 递归 O(mn)  O(mn)
int LCSLength(string x,string y,int m,int n,auto &lookup){
	if(m == 0 || n == 0)
		return 0;
	string key = to_string(m) + "|" + to_string(n);
	if(lookup.find(key) == lookup.end()){
		if(x[m-1] == y[n-1])
			lookup[key] = LCSLength(x,y,m-1,n-1,lookup) + 1;
		else
			lookup[key] = max(LCSLength(x,y,m-1,n,lookup),
								LCSLength(x,y,m,n-1,lookup));
	}
	return lookup[key];
}
//从下到上 迭代
int LCSLength(string x,string y){
	int m = str.size(),n=y.size();
	int lookup[m+1][n+1];
	int i = 0,j=0;
	for(;i<m+1;++i)	lookup[i][n+1] = 0;
	for(;j<n+1;++j)	lookup[m+1][j] = 0;

	for(i = 1;i<m+1;++i){
		for(j = 1;j<n+1;++j){
			if(x[i-1] == y[j-1])
				lookup[i][j] = lookup[i-1][j-1] + 1;
			else
				lookup[i][j] = max(lookup[i][j-1],lookup[i-1][j]);
		}
	}
	return lookup[m][n];
}

//最长公共子串  连续
/*
关系式：
LCS[i][j] = |LCS[i-1][j-1]+1				x[i-1] = y[j-1]
			|0								otherwise；
			*/
string LCSLength(string x,string y,int m,int n){
	int maxLength = 0;
	int endIndex = m;
	int lookup[m+1][n+1];
	memset(lookup,0,sizeof(lookup));
	for(int i = 1;i<m+1;++i){
		for(int j = 0;j<n+1;++j){
			if(x[i-1] == y[j-1]){
				lookup[i][j] = lookup[i-1][j-1]+1;
				if(lookup[i][j] > maxLength){
					maxLength = lookup[i][j];
					endIndex = i;
				}
			}
		}
	}
	return x.substr(endIndex-maxLength,maxLength);
}

/*最长回文子序列
关系式：
			|1								i=j
LCS[i..j] = |L(i+1,j-1)+2					x[i] = x[j]
			|max(LCS[i-1..j],LCS[i..j-1])	x[i] != x[j]
			*/
int longestPalindrome(string x,int i,int j){
	if(i > j)	return 0;
	if(i == j)	return 1;
	if(x[i] == x[j])
		return 	longestPalindrome(x,i+1,j-1)+2;
	
	return max(longestPalindrome(x,i+1,j),
				longestPalindrome(x,i,j-1));
}

//

//动态规划
//背包问题  
/*
有 n 个重量个价值分别为 w_i, v_i 的物品。
从这些物品中选出总重量不超过 W 的物品，使其总价值最大。

示例
1                // 用例数
5 10             // 物品数 背包容量 N <= 1000 , V <= 1000
1 2 3 4 5
5 4 3 2 1

14
*/
//定义：dp[i][j] := 从前 i 个物品中选取总重量不超过 j 的物品时总价值的最大值
//i 从 1 开始计，包括第 i 个物品
//初始化 dp[0][j] = 0;
/*
状态转移：
dp[i][j] =  |dp[i-1][j]                                j<w[i]
			|max(dp[i-1][j],dp[i-1][j-w[i]] + v[i])    j >= w[i]
*/
//二维DP
 int packetSolve(int N,int V,vector<int>& value,vector<int>& weight){
	 vector<vector<int>> dp(N+1,vector<int>(N+1,0));

	 for(int i = 1;i<=N;++i){
		 for(int j = 0;j<=V;++j){
			if(j < weight[i])
			 	dp[i][j] = dp[i-1][j];
			else{
				dp[i][j] = max(dp[i-1][j],dp[i-1][j-weight[i]] + value[i]);
			}
		 }
	 }
	 return dp[N][V];
 }


//字符串

//字符串拷贝
char* strCopy(char *strDes,const char *strSource){
	if(strDes == strSource)
		return strDes;
	assert((strDes != nullptr) && (strSource != nullptr));
	char *pDes = strDes;
	while((*strDes++ = *strSource++) != '\0');
	return pDes;
}
//字符串拷贝
char *strnCpy(char *strDes,const char *strSource,int count){
	assert（strDes!=nullptr && strSource!=nullptr）;
	char *pDes = strDes;
	while(count-- && *strSource != '\0')
		*strDes++ = * strSource;
	*strDes = '\0';//最后加上结束标志
	return pDes;
}

//首次出现某字符
int findChar(const char* str,char c){
	assert(str != nullptr);
	int index = 0;
	for(;*str!=c;++str){
		if(*str == '\0')
			return -1;
		++index;
	}
	return index;
}

//链表
//倒数第K个节点
ListNode* findLastKthNode(ListNode *head,int k){
	assert(k >= 0);
	ListNode *slow = head,*fast = head;
	for(;k>0 && fast!=nullptr;--k)
		fast = fast->next;
	if(k > 0)
		return nullptr;
	while(fast){
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}