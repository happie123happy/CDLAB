#include <iostream>

using namespace std;

class Date{
	int day;
	int month;
	int year;

	
	public:
	
	Date(int day=0,int month=0,int year=0 ){
		this->day=day;
		this->month=month;
		this->year=year;
	}
		
	int operator - (Date const &obj) {
        Date res;
        
        long long days1=(year)*360+(month)*30+(day);
        long long days2=(obj.year)*360+(obj.month)*30+(obj.day);
		
		int cnt=0;
		
		cnt=max(days1,days2)-min(days1,days2);
		
         return cnt;
    }
    
    void print() {
	 cout << day << "/" << month << "/" << year << '\n'; 
	 }
	
	Date operator + (unsigned int obj) {
         Date res;
		
		res.year=year+((obj/360));	
		obj=obj%360;
		res.month=month+(obj/30);
		if(res.month>12){
		res.year+=1;	
		res.month=(res.month)%12;	
		}
		obj=obj%30;	
	
		int sum=day+obj;
		
		if(sum<=30){
		
		res.day=sum;
		
		}
		else{
		res.day=(sum%30);
		if(res.month!=12){
		res.month+=1;
		}
		else{
		res.month=1;
		res.year+=1;	
		}
		
		}

         return res;
    }

	Date operator - (unsigned int obj) {
         Date res;
		
		res.year=year-((obj/360));	
		obj=obj%360;
		res.month=month-(obj/30);
		if(res.month<1)
		{
		res.month=12-(res.month);	
		res.year-=1;
		}
		obj=obj%30;
		int diff=day-obj;
		
		if(diff>0){
		
		res.day=diff;
		
		}
		else{
		res.day=30+(diff);
		if(res.month!=1){
		res.month-=1;
		}
		else{
		res.month=12;
		res.year-=1;	
		}
		}

         return res;
    }


};

int main(){
	
	Date o1(30,12,2010);
	Date o2(1,1,2010);
	
//	Date res=o1+366;
//	res.print();
//	res=o2-368;
//	res.print();
	int res1=o1-o2;
	cout<<res1<<endl;
//	Date res2=o1-o2;
//	res.print();
	
	cout<<"Hello"<<endl;
	return 0;
}

/*
Date operator + (Date const &obj) {
         Date res;
         int days=this->day+(30*month)+obj.day+(30*obj.month);
		
		if(year==obj.year){
			res.year=obj.year;	
		}
		else{
			res.year=year+obj.year;
		}
		
		if(month==obj.month){
				res.month=obj.month;	
			}
		else{
				res.month=((days)/30);
				res.year=res.year+((days/365));
		}
		
		int sum=day+obj.day;
		
		if(sum<=30){
		
		res.day=sum;
		
		}
		else{
		res.day=(sum%30)+1;
		res.month+=(sum/30);	
		}

         return res;
    }


int operator - (Date const &obj) {
         Date res;
		
		if(year==obj.year){
			res.year=obj.year;	
		}
		else{
			res.year=max(year,obj.year)-min(year,obj.year);
		}
		
		if(month==obj.month){
				res.month=obj.month;	
			}
		else{
				res.month=max(month,obj.month)-min(month,obj.month);		
		}
		
		int sum=max(day,obj.day)-min(day,obj.day);
		
		res.day=sum;
		
         return (res.year)*365+(res.month)*30+(res.day);
    }
*/
