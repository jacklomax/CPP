#include <iostream>
#include <string.h>
#include<iomanip>
#include<set>
#include<vector>
#include<algorithm>
#define endl '\n'
#define MAXN 5
#define MAXSTRENGTH 20000
using namespace std;
int POWER[MAXN]={0};
int stre[MAXN]={0};
int reduction,city;
struct infor {
	char name[7];
	int element;
};
struct infor weaponlist[3]={"sword",0,"bomb",1,"arrow",2};

class weapon_{
	public:
	string wp_name;
	int index;
	int damage;
	int durability;
	weapon_(){index=damage=0,wp_name="",durability=0;}
	weapon_(const char *s){wp_name.insert(0,s),index=damage=0,durability=0;}
	bool operator<(const weapon_ & w){
		if(this->index<w.index){
			return true;
		}else if(this->index==w.index&&w.wp_name=="arrow"){
			if(this->durability<w.durability){
				return true;
			}
		}
		return false;
	}
};
class sword:public weapon_{
	public:
	sword(const int x){
		damage=x*2/10;
		index=0;
		wp_name="sword";
	}
};
class bomb:public weapon_{
	public:
	int dtoself;
	bomb(const int x){
		damage=x*4/10;
		dtoself=damage/2;
		durability=1;
		index=1;
		wp_name="bomb";
	}
	int use(){
		if(durability==1){
			durability--;
			return 1;
		}else{
			return 0;
		}
	}
	int dts(){
		return dtoself;
	}
	
};
class arrow:public weapon_{
	public:
	
	arrow(const int x){
		damage=x*3/10;
		durability=2;
		index=2;
		wp_name="arrow";
	}
	int use(){
		if(durability>0){
			durability--;
			return 1;
		}else{
			return 0;
		}
	}
};
//myless
class myless{
	public:
		bool operator()(weapon_ * x,weapon_ * y){
			return *x<*y;
		}
};
//warrior
class warrior{
	int index;
	int attackpower;
	string name;
	public:
	int pos;
	int strength;
	vector<weapon_*> wpl;
	string team;
	int wi;
		warrior(const string & b,const string & a,int sh=0,int ix=0,int at=0,int p=0){
			index=ix;
			strength=sh;
			int i=0;
			name=a;
			team=b;
			pos=p;
			attackpower=at;
			wi=0;
		}
		void getval(int v,char *s){
			int i=0;
			while(s[i]!=0){
				name[i]=s[i];
				i++;
			}
			name[i]=0;
			strength=v;
		}
		int outsh(){
			return strength;
		}
		int outix(){
			return index;
		}
		int outforce(){
			return attackpower;
		}
		string & outna(){
			return name;
		}
		void addindex(){
			index++;
		}
		void resetix(){
			index=0;
		}
		int dol(){
			if(strength>0){
				return 1;
			}else{
				return 0;
			}
		}
		void setdamage(){
			for(int i=0;i<wpl.size();++i){
				if(wpl[i]->index==0){
					wpl[i]->damage=attackpower*2/10;
				}else if(wpl[i]->index==1){
					wpl[i]->damage=attackpower*4/10;
					((bomb*)wpl[i])->dtoself=wpl[i]->damage/2;
				}else if(wpl[i]->index==2){
					wpl[i]->damage=attackpower*3/10;
				}
			}
		}
		void getfromloser(warrior * x){
			int a=-1,b=-1,xcount=x->wpl.size();
			if(xcount!=0){
				x->arrangewp();
				for(int i=0;i<xcount;++i){
					if(x->wpl[i]->wp_name=="arrow"){
						a=i;
						break;
					}
				}
				if(a!=-1){
					for(int i=a;i<xcount;++i){
						if(x->wpl[i]->wp_name!="arrow"){
							b=i;
							break;
						}
					}
					if(b==-1){
						b=xcount;
					}
					reverse(x->wpl.begin()+a,x->wpl.begin()+b);
				}
				
				int i=0;
				while(wpl.size()<10){
					wpl.push_back(x->wpl[i]);
					x->wpl.erase(x->wpl.begin()+i);
					if(i==x->wpl.size()){
						break;
					}
				}
				setdamage();
			}

		}
		void nextwp(){
			if(wpl.size()==0){
				wi=-1;
			}else if(wi==wpl.size()){
				wi--;
			}else{
				wi++;
				if(wi==wpl.size()){
					wi=0;
				}
			}	
		}
		//current weapon
		weapon_*  cwp(){
			if(wpl.size()>0){
				return wpl[wi];
			}else{
				return NULL;
			}
			
		}
		int outwi(){
			return wi;
		}
		void injure(const int d){
			strength-=d;
		}
		int wpcount(){
			return wpl.size();
		}
		int wpsum(){
			int sum=0;
			for(int i=0;i<wpl.size();i++){
				if(wpl[i]->damage>0){
					return 1;
					break;
				}
			}
			return 0;
		}
		void arrangewp(){
			sort(wpl.begin(),wpl.end(),myless());
			if(wpl.size()>0){
				wi=0;
			}
		}
		void PrintWeapon(){
			int count_sword=0,count_bomb=0,count_arrow=0;
			for(int j=0;j<wpl.size();++j){
				if(wpl[j]->wp_name=="sword"){
					count_sword++;
				}else if(wpl[j]->wp_name=="bomb"){
					count_bomb++;
				}else if(wpl[j]->wp_name=="arrow"){
					count_arrow++;
				}
			}
			cout<<count_sword<<" "<<"sword"<<" "<<count_bomb<<" ";
			cout<<"bomb"<<" "<<count_arrow<<" "<<"arrow";
		}
		void initweapon(int ix){
			if(ix%3==0){
				wpl.push_back(new sword(outforce()));
			}else if(ix%3==1){
				wpl.push_back(new bomb(outforce()));
			}else{
				wpl.push_back(new arrow(outforce()));
			}
		}
		int ifstatic(){
			if(wpl.size()==0){
				return 1;
			}else{
				for(int i=0;i<wpl.size();++i){
					if(wpl[i]->wp_name!="sword"){
						return 0;
					}else{
						if(wpl[i]->damage!=0){
							return 0;
						}
					}
				}
				return 1;
			}
		}
		
};

//dragon
class dragon:public warrior{
	int weapon;
	double morale;
	public:
		dragon(const string & tn,int sh=0,int ix=0,int at=0,int p=0,const string a="dragon",double m=0,int w=0):weapon(w),morale(m),
		warrior(tn,a,sh,ix,at,p){
			initweapon(ix);
		}
		int getw(){
			return weapon;
		}
		void setw(const int x){
			weapon=x%3;
		}
		double getml(){
			return morale;
		}
		void setml(const double x){
			morale=x/outsh();
		}
		void PrintInfo(){
			cout<<"It has a "<<weaponlist[weapon].name;
			cout<<",and it's morale is "<<setiosflags(ios::fixed)<<setprecision(2)<<morale<<endl;
		}
};
class ninja:public warrior{
	int first,second;
	public:
		ninja(const string & tn,int sh=0,int ix=0,int at=0,int p=0,const string a="ninja",int f=0,int s=0):first(f),second(s),
		warrior(tn,a,sh,ix,at,p){
			initweapon(ix);
			initweapon(ix+1);
		}
		void PrintInfo(){
			cout<<"It has a "<<weaponlist[first].name<<" and a ";
			cout<<weaponlist[second].name<<endl;

		}
		void setw(const int x){
			first=x%3;
			second=(x+1)%3;
		}

		
};
class iceman:public warrior{
	int weapon;
	public:
		iceman(const string & tn,int sh=0,int ix=0,int at=0,int p=0,const string a="iceman",int w=0):weapon(w),warrior(tn,a,sh,ix,at,p){
			initweapon(ix);
		}
		void PrintInfo(){
			cout<<"It has a "<<weaponlist[weapon].name<<endl;
		}
		void setw(const int x){
			weapon=x%3;
		}
		void lifereduce(){
			strength=strength-strength/10;
		}
};
class lion:public warrior{
	int loyalty;
	public:
		lion(const int m,const string & tn,int sh=0,int ix=0,int at=0,int p=0,const string a="lion"):warrior(tn,a,sh,ix,at,p){
			initweapon(ix);
			loyalty=m;
		}
		void PrintInfo(){
			cout<<"Its loyalty is "<<loyalty<<endl;
		}
		void loyaltyreduce(){
			loyalty=loyalty-reduction;
		}
		int outloyal(){
			return loyalty;
		}
		
};
class wolf:public warrior{
	public:
		wolf(const string & tn,int sh=0,int ix=0,int at=0,int p=0,const string a="wolf"):warrior(tn,a,sh,ix,at,p){}
		void steal(warrior * w){
			int wcount=w->wpl.size();
			int i=0,a=-1,b=-1;
			int wp_sword=0,wp_bomb=0,wp_arrow=0;
			if(w->outna()!="wolf"&&wcount>0){
				w->arrangewp();
				for(int j=0;j<wcount;++j){
					if(w->wpl[j]->wp_name=="arrow"){
						a=j;
						break;
					}
				}
				if(a!=-1){
					for(int j=a;j<wcount;++j){
						if(w->wpl[j]->wp_name!="arrow"){
							b=j;
							break;
						}
					}
					if(b==-1){
						b=wcount;
					}
					reverse(w->wpl.begin()+a,w->wpl.begin()+b);
				}
				int index=w->wpl[0]->index;
				while(wpcount()<10){
					if(w->wpl[i]->index==index){
						wpl.push_back(w->wpl[i]);
						if(w->wpl[i]->wp_name=="sword"){
							wp_sword++;
						}else if(w->wpl[i]->wp_name=="bomb"){
							wp_bomb++;
						}else if(w->wpl[i]->wp_name=="arrow"){
							wp_arrow++;
						}
						w->wpl.erase(w->wpl.begin()+i);
					}else{
						break;
					}
					if(i==w->wpl.size()){
						break;
					}
				}
				if(wp_arrow+wp_bomb+wp_sword!=0){
					cout<<"wolf "<<outix()<<" took";
					if(wp_sword!=0){
						cout<<" "<<wp_sword<<" sword";
					}
					if(wp_bomb!=0){
						cout<<" "<<wp_bomb<<" bomb";
					}
					if(wp_arrow!=0){
						cout<<" "<<wp_arrow<<" arrow";
					}
					cout<<" from "<<w->team<<" "<<w->outna()<<" "<<w->outix();
					cout<<" in city "<<w->pos<<endl;
				}
				setdamage();
				
			}
		}
};
class battletime{
	public:
	int tt;
	battletime(){tt=0;}
	battletime(const battletime & x){
		tt=x.tt;
	}
	battletime & operator++(){
		tt++;
		return *this;
	}
	battletime operator++(int){
		battletime tmp(*this);
		tt++;
		return tmp;
	}
	friend ostream & operator<<(ostream & os ,const battletime & x){
		int hh=x.tt/60,mm;
		mm=x.tt-hh*60;
		os<<setw(3)<<setfill('0')<<hh<<":";
		os<<setw(2)<<setfill('0')<<mm;
		return os;
	}
	battletime & operator+=(const int add){
		tt=tt+add;
		return *this;
	}
	bool operator<=(int T){
		return tt<=T;
	}
	bool operator==(int T){
		return tt==T;
	}
	bool operator>(int T){
		return tt>T;
	}
	bool operator<(int T){
		return tt<T;
	}
	int operator%(int x){
		return tt%5;
	}
	int outmm(){
		int hh=tt/60;
		return tt-hh*60;
	}

};

//headquarter
class army{
	
	public:
	static battletime timer;
	static int min;
	int i,M,count,outset,des;
	string name,desname;
	struct infor *warriormaker;
	vector<warrior*> warriorlist;
		army(const string & str,const string & desstr,struct infor *order=NULL,int s=0,int e=0,int z=0,int p=0,int j=0){
			int k=0;
			i=j;
			M=z;
			outset=s;
			des=e;
			count=p;
			name=str;
			warriormaker=order;
			desname=desstr;
		}
		void make(){
			int substre=stre[warriormaker[i].element];
			if(M>substre){
				M=M-substre;
				count++;
				if(strcmp(warriormaker[i].name,"dragon")==0){
					warriorlist.push_back(new dragon(name,substre,count,POWER[0],outset));
				}else if(strcmp(warriormaker[i].name,"ninja")==0){
					warriorlist.push_back(new ninja(name,substre,count,POWER[1],outset));
				}else if(strcmp(warriormaker[i].name,"iceman")==0){
					warriorlist.push_back(new iceman(name,substre,count,POWER[2],outset));
				}else if(strcmp(warriormaker[i].name,"lion")==0){
					warriorlist.push_back(new lion(M,name,substre,count,POWER[3],outset));
				}else if(strcmp(warriormaker[i].name,"wolf")==0){
					warriorlist.push_back(new wolf(name,substre,count,POWER[4],outset));
				}
				cout<<timer<<" ";
				cout<<name<<" "<<warriormaker[i].name<<" "<<count<<" born"<<endl;
				int k=warriorlist.size()-1;
				if(warriorlist[k]->outna()=="lion"){
					((lion *)warriorlist[k])->PrintInfo();
				}
				i++;
				if(i>=MAXN){
					i=0;
				}
			}	
		}
		void run(){
			for(int j=0;j<warriorlist.size();j++){
				if(warriorlist[j]->outna()=="lion"){
					if(((lion *)warriorlist[j])->outloyal()<=0){
						cout<<timer<<" "<<name<<" lion "<<warriorlist[j]->outix()<<" ran away"<<endl;
						for(int u=0;u<warriorlist[j]->wpl.size();++u){
							delete warriorlist[j]->wpl[u];
						}
						delete (lion *)warriorlist[j];
						warriorlist.erase(warriorlist.begin()+j);
					}
				}
			}
		}
		
		void step(){
				for(int k=0;k<warriorlist.size();k++){
					if(warriorlist[k]->pos!=des){
						if(des<outset){
							warriorlist[k]->pos--;
						}else{
							warriorlist[k]->pos++;
						}
						if(warriorlist[k]->outna()=="iceman"){
							((iceman *)warriorlist[k])->lifereduce();
						}else if(warriorlist[k]->outna()=="lion"){
							((lion*)warriorlist[k])->loyaltyreduce();
						}
					}
				}
		}
		void PrintPos(int e){
			if(warriorlist[e]->pos!=des){
				cout<<timer<<" "<<name<<" "<<warriorlist[e]->outna()<<" "<<warriorlist[e]->outix()<<" marched to city ";
				cout<<warriorlist[e]->pos<<" with "<<warriorlist[e]->outsh();
				cout<<" elements and force "<<warriorlist[e]->outforce()<<endl;
			}else{
				cout<<timer<<" "<<name<<" "<<warriorlist[e]->outna()<<" ";
				cout<<warriorlist[e]->outix()<<" reached "<<desname<<" headquarter with ";
				cout<<warriorlist[e]->outsh()<<" elements and force "<<warriorlist[e]->outforce()<<endl;
				cout<<timer<<" "<<desname<<" headquarter was taken"<<endl;
			}
		}
		void reset(){
			M=outset=des=i=count=0;
			timer.tt=0;
			min=MAXSTRENGTH;
			for(int j=0;j<warriorlist.size();j++){
				delete warriorlist[j];
			}
			warriorlist.clear();
		}
		
		int Ci(){
			return i;
		}
		static void Cmin(int x){
			min=x;
		}
		
		void getm(int x){
			M=x;
		}
		void getcity(const int s,const int e){
			outset=s;
			des=e;
		}
		warrior* wat(int x){
			for(int j=0;j<warriorlist.size();j++){
				if(warriorlist[j]->pos==x){
					return warriorlist[j];
				}
			}
			return NULL;
		}
		void PrintAtCity(int c){
			warrior*tmp=wat(c);
			if(tmp!=NULL){
				cout<<timer<<" "<<name<<" "<<tmp->outna()<<" ";
				cout<<tmp->outix()<<" has ";
				tmp->PrintWeapon();
				cout<<" and "<<tmp->outsh()<<" elements"<<endl;
			}
		}
		int ifarrive(){
			if(warriorlist.size()!=0){
				return warriorlist[0]->pos==des;
			}else{
				return 0;
			}
		}
		//delete warrior
		void die(warrior*x){
			for(int i=0;i<warriorlist.size();++i){
				if(warriorlist[i]==x){
					for(int k=0;k<warriorlist[i]->wpl.size();++k){
						delete warriorlist[i]->wpl[k];
					}
					delete warriorlist[i];
					this->warriorlist.erase(warriorlist.begin()+i);
					break;
				}
			}
		}
};

void march(army & a,army & b){
	a.step();
	b.step();
	int wa=a.warriorlist.size()-1,wb=b.warriorlist.size()-1;
	for(int c=0,ca=wa,cb=0;c<=city+1;c++){
		if(ca>=0&&a.warriorlist[ca]->pos==c&&c!=0){
			a.PrintPos(ca);
			ca--;
		}
		if(cb<=wb&&b.warriorlist[cb]->pos==c&&c!=city+1){
			b.PrintPos(cb);
			cb++;
		}
	}
}
//battleResult
int battle(warrior * a,warrior * b){
	if(a->outsh()<=0&&b->outsh()<=0){
		return -2;//all died
	}else if(a->outsh()>0&&b->outsh()>0&&a->ifstatic()&&b->ifstatic()){
		return 0;//all stable
	}else if(a->outsh()>0&&b->outsh()<=0){
		return 1;//a alive b died
	}else if(a->outsh()<=0&&b->outsh()>0){
		return -1;//a died b alive
	}else{
		return 2;
	}
};

void lattackr(warrior *l,warrior *r){
	if(l->wpl.size()!=0){
		r->injure(l->cwp()->damage);
		if(l->cwp()->wp_name=="bomb"){
			if(l->outna()!="ninja"){
				l->injure(((bomb*)(l->cwp()))->dts());
			}
			delete l->cwp();
			l->wpl.erase(l->outwi()+l->wpl.begin());
		}else{
			if(l->cwp()->wp_name=="arrow"){
				if(l->cwp()->durability==1){
					delete l->cwp();
					l->wpl.erase(l->outwi()+l->wpl.begin());
				}else{
					((arrow*)(l->cwp()))->use();
				}
			}
		}
		l->nextwp();
	}
}

//vs
int vs(warrior *rw,warrior *bw,const int p){
	int result;
	rw->arrangewp();
	bw->arrangewp();
	if(p%2!=0){
		while(1){
			lattackr(rw,bw);
			if(battle(rw,bw)!=2){
				break;
			}
			lattackr(bw,rw);
			if(battle(rw,bw)!=2){
				break;
			}
		}
	}else{
		while(1){
			lattackr(bw,rw);
			if(battle(rw,bw)!=2){
				break;
			}
			lattackr(rw,bw);
			if(battle(rw,bw)!=2){
				break;
			}
		}
	}
	result=battle(rw,bw);
	cout<<army::timer<<" ";
	if(result==-2){
		cout<<"both red "<<rw->outna()<<" "<<rw->outix()<<" and blue ";
		cout<<bw->outna()<<" "<<bw->outix()<<" died in city "<<p<<endl;
	}else if(result==0){
		cout<<"both red "<<rw->outna()<<" "<<rw->outix()<<" and blue ";
		cout<<bw->outna()<<" "<<bw->outix()<<" were alive in city "<<p<<endl;
	}else if(result==1){
		cout<<"red "<<rw->outna()<<" "<<rw->outix()<<" killed ";
		cout<<"blue "<<bw->outna()<<" "<<bw->outix()<<" in city "<<p;
		cout<<" remaining "<<rw->outsh()<<" elements"<<endl;
		rw->getfromloser(bw);
	}else if(result==-1){
		cout<<"blue "<<bw->outna()<<" "<<bw->outix()<<" killed ";
		cout<<"red "<<rw->outna()<<" "<<rw->outix()<<" in city "<<p;
		cout<<" remaining "<<bw->outsh()<<" elements"<<endl;
		bw->getfromloser(rw);
	}
	if(rw->outna()=="dragon"&&rw->outsh()>0){
		cout<<army::timer<<" red dragon "<<rw->outix();
		cout<<" yelled in city "<<p<<endl;
	}
	if(bw->outna()=="dragon"&&bw->outsh()>0){
		cout<<army::timer<<" blue dragon "<<bw->outix();
		cout<<" yelled in city "<<p<<endl;
	}
	return result;
}

int army::min=MAXSTRENGTH;
battletime army::timer;

int main()
{

	int n,t,i=0,min=MAXSTRENGTH,k,T;
	//dragon 、ninja、iceman、lion、wolf
	struct infor order1[MAXN]={"iceman",2,"lion",3,"wolf",4,"ninja",1,"dragon",0};
	struct infor order2[MAXN]={"lion",3,"dragon",0,"ninja",1,"iceman",2,"wolf",4};
	
	army red("red","blue",order1);
	army blue("blue","red",order2);
	cin>>n;
	for(k=1;k<=n;k++){
		cin>>t>>city>>reduction>>T;
		
		red.getm(t);
		blue.getm(t);
		red.getcity(0,city+1);
		blue.getcity(city+1,0);
		for(i=0;i<MAXN;i++){
			cin>>stre[i];
			if(stre[i]<min){
				min=stre[i];
			}
		}
		army::Cmin(min);
		for(i=0;i<MAXN;i++){
			cin>>POWER[i];
		}
		cout<<"Case "<<k<<":"<<endl;

		while(1){
			int minute=army::timer.outmm();
			if(minute==0){
				red.make();
				blue.make();
			}else if(minute==5){
				red.run();
				blue.run();
			}else if(minute==10){
				march(red,blue);
				if(red.ifarrive()){
					break;
				}
				if(blue.ifarrive()){
					break;
				}
			}else if(minute==35){
				warrior*rw,*bw;
				for(i=1;i<=city;i++){
					rw=red.wat(i);
					bw=blue.wat(i);
					if(rw==NULL||bw==NULL){
						continue;
					}
					if(rw->outna()=="wolf"&&bw->outna()!="wolf"&&bw->wpl.size()!=0){
						cout<<army::timer<<" red ";
						((wolf *)rw)->steal(bw);
					}else if(rw->outna()!="wolf"&&bw->outna()=="wolf"&&rw->wpl.size()!=0){
						cout<<army::timer<<" blue ";
						((wolf *)bw)->steal(rw);
					}
				}
			}else if(minute==40){
				warrior*rw,*bw;
				int result;
				for(i=1;i<=city;i++){
					rw=red.wat(i);
					bw=blue.wat(i);
					if(rw==NULL||bw==NULL){
						continue;
					}
					result=vs(rw,bw,i);
					if(result==1){
						blue.die(bw);
					}else if(result==-1){
						red.die(rw);
					}else if(result==-2){
						red.die(rw);
						blue.die(bw);
					}
				}
			}else if(minute==50){
				cout<<army::timer<<" "<<red.M<<" elements in red headquarter"<<endl;
				cout<<army::timer<<" "<<blue.M<<" elements in blue headquarter"<<endl;
			}else if(minute==55){
				for(int i=0;i<=city+1;i++){
					red.PrintAtCity(i);
					blue.PrintAtCity(i);
				}
				
			}if(army::timer==T){
				break;
			}
			army::timer+=5;
		}
		red.reset();
		blue.reset();
		min=MAXSTRENGTH;
	}
	
	return 0;
}
