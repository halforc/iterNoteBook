assign
back_inserter

STL容器删除操作
Containr<int>  c;
如 删除所有值为1963的对象

连续内存容器(vector,deque或string)   
erase-remove 去除惯用值的最佳方法
```
c.erase(remove(c.begin(),c.end(),1963),c.end());
```

对于list 或者关联容器 set、multiset  map  multimap
remove是去除特定值的最佳方法
```
c.remove(1963)
```

如果删除的不是具体值而是判断式
如 bool badValue(int x)；//返回x是否是bad
序列容器和list只需要将remove换成remove_if
序列容器：
```
c.erase(remove_if(c.begin(),c.end(),badValue),c.end());
```
对于list:
```
c.remove_if(badValue);
```
对于关联容器
```
AssocContainer<int> c;
AssocContainer<int> goodValues;//用于容纳不删除的值的临时容器

remove_copy_if(c.begin(),c.end(),inserter(goodValues,goodValues.end()),badValue);从c中拷贝不删除的值到goodValues
c.swap(goodValues);//交换c和goodValues
```
注意！！！
错误方法:
```
AssocContainer<int> c;
for(AssocContainer<int>::iterator it = c.begin();it!=c.end();++it){
	if(badValue(*it) c.erase(it)
}
```
会出现未定义的行为。当容器的一个元素被删时，指向那个元素的所有迭代器都失效了。当c.erase返回时，it已经失效，对于循环是个坏消息，因为erase返回后，it通过for循环自增

避免的方法：在调用erase之前得到c中下一个元素的迭代器，即当我们调用时，在it上使用后置递增
```
AssocCotainer<int> c;
for(AssocContainer<int>::iterator it = c.begin();it!=c.end();++it){
	if(badValue(*it){
		logFile<<"Erasing"<<*it<<'\n';//写日志文件
	}
	else ++i;
}
```