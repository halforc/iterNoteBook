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



