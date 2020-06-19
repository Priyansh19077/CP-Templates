
// phi(P) = P-1;
// phi(P^K) = P^k-P^k-1;
// phi(X) = X*(1-1/p1)*.....*(1-1/pn);
// if gcd(a,b) == 1 phi(a*b)=phi(a)*phi(b);
// if d1, d2, d3, .... , dn are divisors of n
// phi(d1) + phi(d2) + phi(d3)... +phi(dn)=n;


Inbuilt Binary Search:

vector<int> A = {1, 2, 3, 4};
sort(A.begin(), A.end());
bool present = binary_search(A.begin(), A.end(), value);	//for vector
bool present1 = binary_search(arr, arr + n, value);	//for array

Lower Bound Occurence of an Element:
vector<int> A1 = {1, 2, 3, 4, 100, 100, 100, 100, 120};
vector<int>::iterator it = lower_bound(A1.begin(), A1.end(), 100);	//<=that element //if given element is lesser than the lower most then it gives the position of the lower most only so take care of that

Return Value: An iterator to the lower bound of val in the range. If all the elements in the range compare less than val, the function returns last. If all the elements in the range are larger than val, the function returns a pointer to the first element.

vector<int>::iterator it2 = upper_bound(A1.begin(), A1.end(), 1000); //just greater than that element

Return type : An iterator to the upper bound of val in the range. If all the element in the range compare less than val, the function returns last

cout << *it << endl; //gives the value
cout << (it - A1.begin()) << endl;//gives the position //1 based indexing
cout << *it2 << endl;
cout << (it2 - A1.begin()) << endl; //gives the position of the element >given element
//if no such element exists then this would be n meaning that all elements are smaller than this

both operations can be applied to array as well by simply doing
int pos = lower_bound(A, A + n, val) - A;
//this will give the position of the element
to get the count of occurence of an element also that can also be done in logN time using this approach
it2 - it1 will give the number of elements with that value

for (int x : A) //this statement can be used with vectors easily to print
	cout << x << endl;
//we can also use auto feature to not type the type of the particular data type as well
//to make any changes in the values along with this we can do something like this
for (int& x : A)
{
	x++;
	cout << x << endl;
}
for (int x : A)
	cout << x << endl;
vector<int> A = {11, 1, 2, 3, 14};
int*arr = new int[5]();
arr[0] = 11;
arr[1] = 1;
arr[2] = 2;
arr[3] = 3;
arr[4] = 14;
cout << A[1] << nline;
// sort(A.begin(), A.end());
sort(arr, arr + 5);
bool present = binary_search(arr, arr + 5, 10);
cout << present << endl;
vector<int> A1 = {1, 2, 3, 4, 100, 100, 100, 100, 120};
vector<int>::iterator it = lower_bound(A1.begin(), A1.end(), 10000);
vector<int>::iterator it2 = upper_bound(A1.begin(), A1.end(), 1000);
cout << *it << endl;
cout << (it - A1.begin()) << endl;
cout << *it2 << endl;
cout << (it2 - A1.begin()) << endl;
//sorting the vector in reverse order can be done in the same way
// sort(A.begin(), A.end(), compare);
for (int x : A) //this statement can be used with vectors easily to print
	cout << x << endl;
//we can also use auto feature to not type the type of the particular data type as well
//to make any changes in the values along with this we can do something like this
for (int& x : A)
{
	x++;
	cout << x << endl;
}
for (int x : A)
	cout << x << endl; //cjanges will not be visible here if we dont write that & sign there


//Talking about A set now
//This can be used to do this lower bound and upper bound dynamically
//Because the set will keep everything in a sorted manner and we can easily perform lower and upper bound on it then even when it is changing dynamically
//Insert operation will take LogN time in this case.
//In case of vector inserting at front takes order of N time but inserting at back takes order of LogN time
//In case of strings it keeps the strings in lexicographical order

set<string> S;
S.insert("asdf");
S.insert("abcd");
S.insert("aaaa");
S.insert("abb");

//How to check if an element is present or not in the set
for (int x : S)
	cout << x << endl;

auto it = S.find(1000);
// cout << *it << endl;
if (it == S.end())
	cout << "NOT PRESENT";
else
	cout << "PRESENT";

set<int> S;
S.insert(1);
S.insert(20);
S.insert(100);
S.insert(100);
for (int x : S)
	cout << x << endl;
set<int>::iterator it = S.find(1000);
cout << *it << endl; //we can also do *it==value but that would not be safe because these are random values and it might happend sometimes that it matches exactly with the given value
if (it == S.end())
	cout << "NOT PRESENT";
else
	cout << "PRESENT";
//using lower bound in set
auto it2 = S.lower_bound(-1);
cout << *it2 << endl;
//we can also remove a certain element using S.erase(value)
S.erase(100);
for (int x : S)
	cout << x << endl;
//this will remove all the occurenece of the element
//this is redundant to say as we wont have the same element more than once in the set
//this is a great way to solve the K query problem also in very less code
//There is no concept of getting the position using the lower bound as there will be only one occurenece of the number

auto it = s.lower_bound(2);
cout << "\nThe lower bound of key 2 is ";
cout << (*it) << endl;

// when 3 is not present
// points to next greater after 3
it = s.lower_bound(3);
cout << "The lower bound of key 3 is ";
cout << (*it) << endl;

// when 8 exceeds the max element in set
it = s.lower_bound(8);
cout << "The lower bound of key 8 is ";
cout << (*it) << endl;

//for sets this lower bound function works in a different manner
//upper bound function works fine in the set


//looking at map data structure now

//in a map it is trivial to do map.insert({1,1});
//by default the value for 1 will be 0 so we can just write mp[1]++; and it will become 1
//by default the values in the value part are 0 for int
map<int, int> mp;
cout << mp.max_size() << endl;
mp.clear();
//to clear all the values from the map
//mp.erase(key); can be used to delete the particular key from the map
//mp.erase(mp.begin(), mp.find(3)); this can be used to delete all the elements till the given iterator passed to it from the starting
mp.insert({1, 1});
//another great function of the map is that the keys remain sorted in it so the lower and upper bound functions can also be used in it
map<int, int> ::iterator it;
mp[4]++;
mp[2]++;
for (it = mp.begin(); it != mp.end(); it++)
	cout << it->first << " " << it->second << endl;
map<int, int> ::iterator it1 = mp.find(100);
if (it1 == mp.end())
	cout << "YES" << endl;
else
	cout << "NO" << endl;
//all the values not that particular value also so all the values less than 3 will be deleted here if 3 is present in the map otherwise all the keys will be deleted
mp.erase(mp.begin(), mp.find(3)); //using this function when no such key is present in the map will delete all the contents of the map as the iterator returned will point to mp.end()
for (it = mp.begin(); it != mp.end(); it++)
	cout << it->first << " " << it->second << endl;
cout << 1 << endl;

