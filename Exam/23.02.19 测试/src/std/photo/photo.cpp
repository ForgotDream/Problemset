#include <cstdio>
#include <algorithm>
#include <iostream>

using std::endl;
using std::sort;
struct person{
	long weight;
	long number;
};
struct greater{
	bool operator()(const person& lhs, const person& rhs) const{
		if(lhs.weight>rhs.weight)return true;
		if(lhs.weight<rhs.weight)return false;
		return lhs.number<rhs.number;
	}
};
int main(){
	freopen("photo.in","r",stdin);
	freopen("photo.out","w",stdout);
	long n,k;
	std::cin>>n>>k;
	long plus[10];
	for(long i=0;i<10;++i)
		std::cin>>plus[i];
	person *ps=new person[n];
	for(long i=0;i<n;++i){
		std::cin>>ps[i].weight;
		ps[i].number=i+1;
	}
	std::sort(ps,ps+n,greater());
	for(long i=0;i<n;++i)
		ps[i].weight+=plus[i%10];
	std::sort(ps,ps+n,greater());
	for(long i=0;i<k-1;++i)
		std::cout<<ps[i].number<<' ';
	if(k>0)  std::cout<<ps[k-1].number<<endl;
}
