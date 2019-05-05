#include <iostream>
#include<stdio.h>
#include "conio2.h"
#include<string.h>
#include<process.h>
#include<stdlib.h>
#include<unordered_map>
#include<vector>
#include<math.h>
#include<queue>
#include<algorithm>
#include <fstream>
#define max 50
using namespace std;

class cust_node
{
    public:
    char c_name[30];
    char ph_no[30];
    int rating;
    vector<cust_node *> refred;
    string ref_no;
    cust_node *parent;
    cust_node()
    {
       rating  = 0;
    }
     cust_node(char name [],char no[],string ref_id)
    {

        strcpy(c_name,name);
        strcpy(ph_no,no);
       ref_no = ref_id;
        rating  = 100;
        parent = NULL;
//        level = 1;
    }
    cust_node(cust_node *customer)
    {
        strcpy(c_name,customer->c_name);
        strcpy(ph_no,customer->ph_no);
        ref_no = customer->ref_no;
        rating  = customer->rating;
        parent = NULL;
    }
    friend ostream& operator<<(ostream& os, const cust_node& s)
	{
		// write out individual members of s with an end of line between each one
		os << s.c_name << '\n';
		os << s.ph_no << '\n';
		os << s.ref_no << '\n';
		os << s.rating << '\n';
		//os << s.parent;
		return os;
	}
	friend istream& operator>>(istream& is, cust_node& s)
	{
		// read in individual members of s
		is >> s.c_name >> s.ph_no >> s.ref_no >> s.rating;
		return is;
	}
};
class Something
{
public:
    int arr[100];
    int size;
   // char weight[30];
    //int size;

	friend std::ostream& operator<<(std::ostream& os, const Something& s)
	{
		// write out individual members of s with an end of line between each one
		//os << s.weight << '\n';
		os << s.size<< ' ';
		for(int i = 0;i<s.size;i++)
        {
            os << s.arr[i] << ' ';
        }
        os << '\n';
		return os;
	}

	// Extraction operator
	friend std::istream& operator>>(std::istream& is, Something& s)
	{
		// read in individual members of s
		int n;
		is >> n;
		int i = 0;
		int temp;
		while(i<n)
        {
		  is >> temp;
		  s.arr[i] = temp;
		  i++;
        }
        s.size = n;
		return is;
	}
};
class ci
{
    public:
    string city_name;
    int index;
    friend ostream& operator<<(ostream& os, const ci& s)
	{
		// write out individual members of s with an end of line between each one
		os << s.city_name << ' ';
		os << s.index<< '\n';
		return os;
	}
	friend istream& operator>>(istream& is, ci& s)
	{
		// read in individual members of s
		is >> s.city_name >> s.index;
		return is;
	}
};
class tot_order
{
public:
    char name[30];
    char ph_no[30];
    float bill;
   tot_order()
   {
    bill = 0;
   }
    tot_order(char *na,char *ph,float bi)
    {
        strcpy(name,na);
        strcpy(ph_no,ph);
        bill = bi;
    }

     friend ostream& operator<<(ostream& os, const tot_order& s)
	{
		// write out individual members of s with an end of line between each one
		os << s.name << ' ';
		os << s.ph_no<< ' ';
		os << s.bill << '\n';
		//os << s.rating << '\n';
		//os << s.parent;
		return os;
	}
	friend istream& operator>>(istream& is, tot_order& s)
	{
		// read in individual members of s
		is >> s.name >> s.ph_no >> s.bill;
		return is;
	}
};
unordered_map<string,cust_node*> cust_map;
queue<string> que_ref_id;
unordered_map<string,bool> current_map;
vector<int> dish_arr(12);
unordered_map<int,vector<int>> dish_map;
vector<tot_order> tot;
unordered_map<int,vector<pair<int,int>>> LIST;
unordered_map<string,int> ctoI;
unordered_map<int,string> itoC;
void save_city_to_file();
void convert_to_matrix(int ** graph,unordered_map<int,vector<pair<int,int>>>LIST,int n);
int delivery_order_count = 0;
int no_of_cities = LIST.size();
bool *destination = new bool[no_of_cities];

void add_city()
{
    clrscr();
    string city_name;
    gotoxy(66,14);
    cout << "ENTER CITY NAME:- ";
    cin >> city_name;
    int no_of_cities = LIST.size();
    if(ctoI.count(city_name) == 1)
    {
        clrscr();
        gotoxy(66,14);
        cout << "CITY ALREADY EXISTS" <<endl;
        delay(500);
        return;
    }

    int curr_city = no_of_cities;
    ctoI[city_name] = curr_city;
    itoC[curr_city] = city_name;
    int no_of_cities_connected_to;
    vector<pair<int,int>> v;
    gotoxy(66,16);
    cout << "ENTER NO OF CITIES " << city_name << " CONNECTS TO: " ;
    cin >> no_of_cities_connected_to;
    clrscr();
    for(int i = 0; i<no_of_cities_connected_to; i++)
    {

        string s;//city name connected to
        int dist_from_city;
        gotoxy(66,2*i+18);
        cout << "ENTER " << i+1 << " st CITY NAME AND DISTANCE FROM THIS CITY:-";
        cin >> s;
        if(ctoI.count(s) == 0)
        {
            clrscr();
            gotoxy(66,2*i+18);
            cout << "CITY DOES NOT EXIST IN THE GRAPH, TRY AGAIN";
            delay(1000);
            i--;
            clrscr();
            continue;
        }
        int city_index = ctoI[s];
        cin >> dist_from_city;
        pair<int,int> p(city_index,dist_from_city);
        v.push_back(p);

    }

    LIST[curr_city] = v;
    int n = LIST.size();
    int **graph = new int*[n];
    for(int i = 0;i<n;i++)
    {
        graph[i] = new int[n];
        for(int j = 0;j<n;j++)
        {
            graph[i][j] = 0;
        }
    }
    convert_to_matrix(graph,LIST,n);
    save_city_to_file();
}

void save_to_file(int ** graph,int n)
{
    std::ofstream ofs("graph.txt");
    for(int i = 0;i<n;i++)
    {
        Something s1;
        s1.size = n;
        for(int j = 0;j<n;j++)
        {
            s1.arr[j] = graph[i][j];
        }
        ofs << s1; // store the object to file
    }
    ofs.close();
}
void save_city_to_file()
{
    std::ofstream ofs("city_index.txt");
    ci s1;
    for(auto it = ctoI.begin();it!=ctoI.end();it++)
    {
        string str = it->first;
        int index = it->second;
        s1.city_name = str;
        s1.index = index;
        ofs << s1;
    }
    ofs.close();
}
void convert_to_matrix(int ** graph,unordered_map<int,vector<pair<int,int>>> LIST,int n)
{
    for(auto it = LIST.begin();it!=LIST.end();it++)
    {
        int u = it->first;
        vector<pair<int,int>> v = it->second;
        for(int i = 0;i<v.size();i++)
        {
            pair<int,int> p = v[i];
            int d = p.second;
            int v = p.first;
            graph[u][v] = d;
            graph[v][u] = d;
        }
    }
    save_to_file(graph,n);
}
int minDistance(vector<int> dist, bool sptSet[])
{
   int V = LIST.size();
   int min = INT_MAX, min_index;

   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}


void dijkstra(int **graph, int src,vector<int> &dist,vector<int> &parent)
{
    int V = LIST.size();
     bool sptSet[V];

     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

     dist[src] = 0;
     parent[src] = -1;
     for (int count = 0; count < V-1; count++)
     {

       int u = minDistance(dist, sptSet);

       sptSet[u] = true;


       for (int v = 0; v < V; v++)
       {
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX  && dist[u]+graph[u][v] < dist[v])
         {
            dist[v] = dist[u] + graph[u][v];
            parent[v] = u;
         }
       }
     }
}
string path(int src,int dest,vector<int> parent)
{
	string str;
	while(1)
	{
		int p = parent[dest];
		str.push_back((char)(p+'0'));

		dest = p;
		if(dest == src)
		{
			break;
		}

	}
	reverse(str.begin(),str.end());
	return str;
}
string shortest_cycle(int **graph, bool* destination, int src,int start,int dest_size)
{
    int n = LIST.size();
	if(dest_size == 0)
	{
	  vector<int> dist(n);
	  vector<int> parent(n);
	  dijkstra(graph,src,dist,parent);
	  string s = path(src,start,parent);
	  s.push_back((char)(start + '0'));
	  return s;
	}
	vector<int> dist(n);
	vector<int> parent(n);

	dijkstra(graph,src,dist,parent);
	int min = INT_MAX;
	int shortest_city = 0;
	for(int i = 0;i<dist.size();i++)
	{
		if(dist[i] < min && destination[i])
		{
			min = dist[i];
			shortest_city = i;
		}
	}

	destination[shortest_city] = false;
	//cout << src << " " << shortest_city << endl;
	string s = path(src,shortest_city,parent);

	return s + shortest_cycle(graph,destination,shortest_city, start,dest_size-1);
}

void print_path(string s)
{
    clrscr();
    gotoxy(66,14);
    cout << "path to be followed is " <<endl;
    gotoxy(20,16);
    for(int i = 0;i<s.size()-1;i++)
    {
        int city_index = s[i]-'0';
        string city_name = itoC[city_index];
        cout << city_name << " --> ";
    }
    cout << itoC[s[s.size()-1] - '0'];
    gotoxy(66,18);
    cout <<"PRESS ANY KEY TO SEND ROUTE TO THE DELIVERY BOY";
    char c;
    cin >> c;
    clrscr();
    gotoxy(66,14);
    cout << "SENDING ";
    int i = 0;
    while(i<10)
    {
        cout << " - ";
        delay(100);
        i++;
    }
    clrscr();
    gotoxy(66,14);
    cout << " DONE ";
    delay(1000);
    cout << endl;
}
void travel(bool *destination)
{
    int n = LIST.size();//no_of_cities;
    int **graph = new int*[n];
    for(int i = 0;i<n;i++)
    {
        graph[i] = new int[n];
        for(int j = 0;j<n;j++)
        {
            graph[i][j] = 0;
        }
    }
    convert_to_matrix(graph,LIST,n);
    int dest_size = 0;
    for(int i = 0;i<n;i++)
    {
        if(destination[i])
        {
            dest_size++;
        }
    }
    //cout << dest_size << endl;
    //delay(5000);
    string path_to_be_followed = shortest_cycle(graph,destination,0,0,dest_size);
    print_path(path_to_be_followed);
}
void deliver()
{
    clrscr();
    string city_name;
    gotoxy(66,18);
    cout << "ENTER CITY NAME:-";
    cin >> city_name;
    while(ctoI.count(city_name) == 0)
    {
        clrscr();
        gotoxy(66,14);
        cout << "CITY DOES NOT EXIST";
        delay(750);
        clrscr();
      gotoxy(66,18);
      cout << "ENTER CITY NAME:-";
       cin >> city_name;
       if(city_name[0] == '-1')
       {
           return;
       }
    }
    int city_index = ctoI[city_name];
    destination[city_index] = true;
    if(delivery_order_count == 1)
    {
        delivery_order_count = 0;
        gotoxy(66,14);
        cout << "ORDER PLACED AND OUT FOR DELIVERY" <<endl;
        delay(1000);
        travel(destination);
    }
    else
    {
        gotoxy(66,14);
        cout << "ORDER PLACED" << endl;
        delay(1000);
        delivery_order_count++;
    }
}


void inc_rating(cust_node * refferer)
{
    int count = 1;
    float inc_percentage = 1;
    int value = 100;
    while(count <= 4 && refferer != NULL)
    {
        refferer->rating += inc_percentage*value; /*inceasing ratings of parent*/
        refferer = refferer->parent;
        inc_percentage = (float)inc_percentage/2;
        count++;
    }
}
string convert_to_string(char *s)
{
    string str;
    int l = 0;
    while(s[l]!='\0')
    {
        str.push_back(s[l]);
        l++;
    }
    return str;
}

void add_to_graph(char *name,char *ph_no,string ref_id)
{
  cust_node *customer = new cust_node(name,ph_no,ref_id);
    string s_ph_no = convert_to_string(ph_no);

    //string s_ref_id = convert_to_string(ref_id);
                            /*making a customer in a k array tree*/
cust_map[s_ph_no] = customer;
                          // ph_no is ref_id
        //cout << strcmp(ref_id,"none") <<endl;
  if(ref_id.compare("none")!=0 && cust_map.count(ref_id) == 1)
  {

      cust_node *refferer = cust_map[ref_id];
      inc_rating(refferer);
      customer->parent = refferer;
      refferer->refred.push_back(customer);
      return;
  }
  else if(ref_id.compare("none") == 0)
  {
      return;
  }
  else
  {
      clrscr();
        gotoxy(66,14);
      cout << "ref_id_does_not_exist" <<endl;
       gotoxy(66,16);
      cout << "Enter refferer_id again:-";
       cin >> ref_id;
      add_to_graph(name,ph_no,ref_id);
  }
}

 struct cust
  {
    char name[50];
	char phno[50];
}c,q[max],a;

int front=0,rear=-1;

void insert()
{

    if(rear==max-1)
{gotoxy(80,13);
    printf("-*-*-*-*-*-*-*-*-");
 gotoxy(80,14);
 printf("Queue is overflow");
 gotoxy(80,15);
 printf("-*-*-*-*-*-*-*-*-");
 getch();
 }
    else
    {
        rear++;
        strcpy(q[rear].name,c.name);
        strcpy(q[rear].phno,c.phno);
        string ref_id;
        if(cust_map.count(q[rear].phno) == 0)
        {
         gotoxy(66,14);
        cout << "Enter ref_id (if_any):-";
        cin >> ref_id;
        add_to_graph(c.name,c.phno,ref_id);
        que_ref_id.push(ref_id);
        }
gotoxy(65,15);
   printf("-*-*-*-*-*-*-*-*-*-*-*-");
 gotoxy(67,16);
 printf("ADDED TO WAITING LIST");
 gotoxy(65,17);
 printf("-*-*-*-*-*-*-*-*-*-*-*-");
   getch(); }
}
void delet()
{

    if((front==0)&&(rear==-1))
    {gotoxy(80,13);
        printf("-*-*-*-*-*-*-*-*-");
 gotoxy(80,14);
 printf("Queue is underflow");
 gotoxy(80,15);
 printf("-*-*-*-*-*-*-*-*-");
        getch();

    }
    strcpy(a.name,q[front].name);
    strcpy(a.phno,q[front].phno);
    front++;

    if(front>rear)
    {
        front=0;
        rear=-1;
    }
}

void display()
{
    int i,j=1;
    if(front==0&&rear==-1)
    {
    gotoxy(80,13);
    printf("-*-*-*-*-*-*-*-*-");
 gotoxy(80,14);
 printf("Queue is overflow");
 gotoxy(80,15);
 printf("-*-*-*-*-*-*-*-*-");
        getch();

    }
    gotoxy(45,13) ;
		printf("SNo.");
		gotoxy(65,13);
		printf("Name");
		gotoxy(90,13);
		printf("Phone Number");
         int c=14;
    for(i=front;i<=rear;i++,j++)
        {   gotoxy(45,c) ;
			printf("%d",j);
		     gotoxy(65,c) ;
			printf("%s",q[i].name);
		      gotoxy(90,c) ;
			printf("%s",q[i].phno);
			c++;
        }



}
  struct node
  {int item;
	char food[50];
    int cost;
    struct node *next;
int quantity;
	};
struct details
{
char name[50];
char phno[50];
struct node *list;
}t[3];


struct Restuarant
{
  char food[50];
  int price;
} menu[] =
{
	{"Double Cheeseburger", 30},//0
	{"Onion Rings", 20},//1
	{"Veggie Burger", 50},//2
	{"Bottled Drink", 95},//3
	{"Ice Cream Cone", 65},//4
	{"Cold Drink", 50},//5
	{"Pizza", 250},//6
	{"Cream Rolls", 150},//7
	{"Paneer Rolls", 120},//8
	{"Cheese Burger ", 130},//9
	{"Lemonade", 40},//10
	{"Juice", 40}//11
};
void display_menu()
{
int i=12;int c=0;
    	clrscr();
		gotoxy(36,8) ;
		printf("ORDER MENU") ;
		gotoxy(15,11) ;
		printf("Item No.");
		gotoxy(35,11);
		printf("Item Name");
		gotoxy(65,11);
		printf("Item Price");
		while(c<12)
		{gotoxy(15,i) ;
			printf("%d",c);
		     gotoxy(35,i) ;
			printf("%s",menu[c].food);
		      gotoxy(65,i) ;
			printf("%d",menu[c].price);
			c++;
			i++;
		}

}
void removeDuplicates(struct node *start)
{
    struct node *ptr1, *ptr2, *dup;
    ptr1 = start;


    while (ptr1 != NULL && ptr1->next != NULL)
    {
        ptr2 = ptr1;


        while (ptr2->next != NULL)
        {

            if (ptr1->item == ptr2->next->item)
            {

                dup = ptr2->next;
                ptr1->quantity=ptr1->quantity+ptr2->next->quantity;
                ptr2->next = ptr2->next->next;
                delete (dup);
            }
            else
                ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
}
void cleartable(int p)
{
    int i=14;int c =0;
    string str = convert_to_string(t[p].phno);
    current_map[str] = false;
    	clrscr();
		gotoxy(70,5);
 printf(".----. .-..-.   .-.   ");
 gotoxy(70,6);
 printf("| {}  }| || |   | |   ");
 gotoxy(70,7);
 printf("| {}  }| || `--.| `--.");
 gotoxy(70,8);
 printf("`----' `-'`----'`----'");
		gotoxy(55,11);
		printf("Name:");
		gotoxy(61,11);
		printf("%s",t[p].name);
		gotoxy(84,11);
		printf("Phone No.:");
		gotoxy(95,11);
		printf("%s",t[p].phno);
		gotoxy(45,13) ;
		printf("Item No.");
		gotoxy(65,13);
		printf("Item Name");
		gotoxy(90,13);
		printf("Item Price");

		gotoxy(105,13);
		printf("Quantity");
        gotoxy(115,13);
		printf("Total");
removeDuplicates(t[p].list);
int q=0;
		while(t[p].list!=NULL)
    {
        gotoxy(45,i) ;
			printf("%d",t[p].list->item);
		     gotoxy(65,i) ;
			printf("%s",t[p].list->food);
		      gotoxy(90,i) ;
			printf("%d",t[p].list->cost);
			gotoxy(105,i);
		printf("%d",t[p].list->quantity);
        gotoxy(115,i);
		printf("%d",t[p].list->cost*t[p].list->quantity);
			q+=t[p].list->cost*t[p].list->quantity;
			i++;
		t[p].list=t[p].list->next;
		}
gotoxy(115,i);
printf("----------");
i=i+1;
gotoxy(118,i);
printf("%d",q);
i=i+1;
gotoxy(115,i);
printf("----------");

cust_node* customer = cust_map[str];
gotoxy(105,i+2);
cout << "Customer current MCOUPONS is: " << customer->rating;
int x;
gotoxy(105,i+4);
cout << "MCOUPONS to be used: ";
cin >> x;
while(x > customer->rating)
{
    gotoxy(105,i+3);
    cout << "MCOUPONS NOT VALID";
    gotoxy(105,i+4);
     cout << "MCOUPONS to be used: ";
     cin >>x;
}
int val = q-(.1*x) > 0? q-(.1*x):0;
gotoxy(105,i+5);
cout << "TOTAL AMOUNT PAYABLE: " << val;
tot_order pt(customer->c_name,customer->ph_no,val);
tot.push_back(pt);
if(val == 0)
{
    x = q*10;
}
customer->rating -= x;

(t[p].list)=NULL;
getch();
}


void add(struct node **q, int item,int quan,char *no)
{
	struct node *temp;
	temp=*q;
    string ph_no = convert_to_string(no);
    cust_node* customer = cust_map[ph_no];
    customer->rating += round(.2*(menu[item].price*quan));
    dish_arr[item] += quan;
   // cout << dish_arr[item] <<endl;
    //cout << customer->rating <<endl;
	if(temp==NULL)
	{
		*q=new (struct node);
		temp=*q;

	}
	else
	{
	  while(temp->next!=NULL)
	  {

		  temp=temp->next;
	  }

		temp->next=new (struct node);
		temp=temp->next;
	}

	temp->item=item;
	temp->cost=menu[item].price;
strcpy(temp->food,menu[item].food);
	temp->quantity=quan;
	temp->next=NULL;


}
void frame1()
  {
  int i,j;
  for(i=3,j=1;i<165;i++,j++)//
  {
  gotoxy(i,2);
  printf("%c",205);

  }

  for(i=3;i<47;i++,j++)
  {
  gotoxy(164,i);
  printf("%c",205);

  }

  for(i=164;i>2;i--,j--)//
  {
  gotoxy(i,47);
  printf("%c",205);

  }

  for(i=46;i>2;i--,j--)
  {gotoxy(3,i);
  printf("%c",205);

  }

  }





  void frame()
  {
  int i,j;
  for(i=3,j=1;i<165;i++,j++)//
  {
  gotoxy(i,2);
  printf("%c",205);

  delay(10);

  }

  for(i=3;i<47;i++,j++)
  {
  gotoxy(164,i);
  printf("%c",205);

  delay(10);

  }

  for(i=164;i>2;i--,j--)//
  {
  gotoxy(i,47);
  printf("%c",205);

  delay(10);

  }

  for(i=46;i>2;i--,j--)
  {gotoxy(3,i);
  printf("%c",205);

  delay(10);

  }

  }

  char mainmenu()
  { char chmain='a';

 textbackground(WHITE);
 textcolor(1);
 clrscr();
 frame1();
 gotoxy(50,14);
 printf(".-.  .-.  .--.  .-..-. .-.    .-.  .-..----..-. .-..-. .-. ");
 gotoxy(50,15);
 printf("}  \\/  { / {} \\ { ||  \\{ |    }  \\/  {} |__}|  \\{ || } { | ");
 gotoxy(50,16);
 printf("| {  } |/  /\\  \\| }| }\\  {    | {  } |} '__}| }\\  {\\ `-' / ");
 gotoxy(50,17);
 printf("`-'  `-'`-'  `-'`-'`-' `-'    `-'  `-'`----'`-' `-' `---'  ");

 gotoxy(65,20);
 printf("1---");
 gotoxy(70,20);
 printf("NEW  CUSTOMER ");
 gotoxy(65,22);
 printf("2---");
 gotoxy(70,22);
 printf("MODIFY EXISTING TABLE");
 gotoxy(65,24);
 printf("3---");
 gotoxy(70,24);
 printf("CLEAR TABLE AND GENERATE BILL");
 gotoxy(65,26);
 printf("4---");
 gotoxy(70,26);
 printf("CURRENT STATUS OF TABLE AVAILABILITY");
 gotoxy(65,28);
 printf("5---");
 gotoxy(70,28);
 printf("WAITING CUSTOMER");
 gotoxy(65,30);
 printf("6---");
 gotoxy(70,30);
 printf("EXIT");
 gotoxy(65,32);
 printf("7---");
 gotoxy(70,32);
 printf("VIEW DISH ACCORDING TO POPULARITY");
 gotoxy(65,34);
 printf("8---");
 gotoxy(70,34);
 printf("EXTEND THE NETWORK");
 gotoxy(55,38);
 printf("\tPlease enter your choice:");
 chmain=getch();

 clrscr();
return chmain;


  }
  char addcustomer()
  {
    strcpy(c.name,"aman");
  strcpy(c.phno,"9811983274");

      textbackground(WHITE);
 textcolor(1);
 clrscr();
frame1();
 int i,count=0;
 for(i=0;i<3;i++)
    if(t[i].list==NULL)
    count++;

 gotoxy(145,4);
 printf("%d TABLE REMAINING",count);
 gotoxy(50,14);
 printf(".-. . . .-. .-. .-. .  . .-. .-.   .-. .-. .-. .-. .-. .   .-.");
 gotoxy(50,15);
 printf("|   | | `-.  |  | | |\\/| |-  |(    |  )|-   |  |-|  |  |   `-.");
 gotoxy(50,16);
 printf("`-' `-' `-'  '  `-' '  ` `-' ' '   `-' `-'  '  ` ' `-' `-' `-' ");

 gotoxy(65,18);
 printf("1---");
 gotoxy(70,18);
 printf("Name : ");
 gotoxy(65,21);
 printf("2---");
 gotoxy(70,21);
 printf("PHONE NO.:");

  gotoxy(20,25);
 printf("\tPRESS 0 TO RETURN");
gotoxy(77,18);
scanf("%s",c.name);
if(c.name[0]=='0')
 return c.name[0];
gotoxy(80,21);
scanf("%s",c.phno);
string s = convert_to_string(c.phno);
if(current_map.count(s) == 1)
{
    if(current_map[s])
    {
    clrscr();
    gotoxy(80,24);
    cout <<"CUSTOMER ALREADY EXIST";
    delay(900);
    return '0';
    }
}
current_map[s] = true;

return c.name[0];

}

char addcustomer2()
  {
    strcpy(c.name,"aman");
  strcpy(c.phno,"9811983274");

      textbackground(WHITE);
 textcolor(1);
 clrscr();
frame1();

 gotoxy(50,14);
 printf(".-. . . .-. .-. .-. .  . .-. .-.   .-. .-. .-. .-. .-. .   .-.");
 gotoxy(50,15);
 printf("|   | | `-.  |  | | |\\/| |-  |(    |  )|-   |  |-|  |  |   `-.");
 gotoxy(50,16);
 printf("`-' `-' `-'  '  `-' '  ` `-' ' '   `-' `-'  '  ` ' `-' `-' `-' ");

 gotoxy(65,18);
 printf("1---");
 gotoxy(70,18);
 printf("Name : ");
 gotoxy(65,21);
 printf("2---");
 gotoxy(70,21);
 printf("PHONE NO.:");

  gotoxy(20,25);
 printf("\tPRESS 0 TO RETURN");
gotoxy(77,18);
scanf("%s",c.name);
if(c.name[0]=='0')
 return c.name[0];
gotoxy(80,21);
scanf("%s",c.phno);
string s = convert_to_string(c.phno);
if(cust_map.count(s) == 0)
{
 string ref_id;
 clrscr();
 gotoxy(66,14);
 cout << "Enter ref_id (if_any):-";
 cin >> ref_id;
 add_to_graph(c.name,c.phno,ref_id);
}
return c.name[0];

}

void takeorder(vector<pair<int,int>> &v)
{
    string ph_no = convert_to_string(c.phno);
    cust_node* customer = cust_map[ph_no];
    char ch1;
    int no;
    int quan1;
    while(ch1!='0')
    {
    clrscr();
    display_menu();
    gotoxy(34,30);
    printf("Enter Item No.:");
      scanf("%d",&no);//99 to break;
      if(no>=12)
        continue;
      gotoxy(34,32);
      printf("Enter Quantity:");
      scanf("%d",&quan1);
      if(quan1==0)
        continue;
     pair<int,int> p(no,quan1);
     v.push_back(p);
     customer->rating += round(.2*(menu[no].price*quan1));
     dish_arr[no] += quan1;
      gotoxy(34,34);
      printf("Press any Key to Continue or Press 0 to Return:");
      scanf(" %c",&ch1);
    }
}

void bill_generation(vector< pair<int,int> > v)
{
    float total = 0;
    clrscr();
    gotoxy(66,16);
    cout << "ITEM               PRICE               QUANTITY               TOTAL"<<endl;
    int i = 0;
    for( i = 0;i<v.size();i++)
    {
        gotoxy(66,i+18);
        cout <<v[i].first<<"                 "<<menu[v[i].first].price<<"                 x"<<v[i].second<<"                 "<<menu[v[i].first].price*v[i].second<<endl;
        total+=menu[v[i].first].price*v[i].second;
    }
    gotoxy(66,i+19);
    cout << "TOTAL:-" << total <<endl;
string str = convert_to_string(c.phno);
cust_node* customer = cust_map[str];
i++;
gotoxy(66,i+19);
cout << "Customer current MCOUPONS is: " << customer->rating;
int x;
i++;
gotoxy(66,i+19);
cout << "MCOUPONS to be used: ";
cin >> x;
while(x > customer->rating)
{
    cout << "MCOUPONS NOT VALID";
     cout << "MCOUPONS to be used: ";
     cin >> x;
}
int q = total;
float val = q-(.1*x) > 0? q-(.1*x):0;
i++;
gotoxy(66,i+19);
cout << "TOTAL AMOUNT PAYABLE: " << val;
delay(1000);
if(val == 0)
{
    x = q*10;
}
customer->rating -= x;

}
class foo
{
    public:
    int a;
    int b;

    foo(int x,int y)
    {
        a = x;
        b = y;
    } // default constructor to make it a little more c++ and less c

    //friend std::istream &operator>>(std::istream &is, foo &f);

    friend ostream &operator<<(ostream &os,foo& s)
    {
        os << s.a << '\n';
		os << s.b << '\n';
		return os;
    }
    friend istream &operator>>(istream &is, foo &f)
    {
    return is >> f.a >> f.b;
     }
};
void read()
{


        cust_node s2;
        s2.parent = NULL;
        ifstream ifs("xyz2.dat");
        while(ifs >> s2)
	  {
		cust_node* customer = new cust_node(&s2);
		string phno = convert_to_string(customer->ph_no);
		cust_map[phno] = customer;
	   }
    for(auto it = cust_map.begin();it!=cust_map.end();it++)
    {
        cust_node*customer = it->second;
        string refid = customer->ref_no;
        if(refid.compare("none")!=0)
        {
        cust_node*p = cust_map[refid];
        customer->parent = p;
        }
        //cout << customer->ph_no;
    }
    bool flag = false;
    ifstream ifs2("dish_priority.dat");
    foo s3(0,0);
    while(ifs2 >> s3)
    {
         int index = s3.b;
         int value = s3.a;
         dish_arr[index] = value;
         flag = true;
    }
    if(!flag)
    {
       for(int i = 0;i<12;i++)
       {
        dish_arr[i] = 0;
       }
    }
    ifstream ifs3("bill.dat");
    tot_order pt;
    while(ifs3 >> pt)
    {
        tot.push_back(pt);
    }

    ifstream ifs4("graph.txt");
    Something s4;
    int row = 0;
    while(ifs4 >> s4)
    {
        int n = s4.size;
        vector<pair<int,int> > v;
        for(int j = 0;j<n;j++)
        {
            if(s4.arr[j] != 0)
            {
                v.push_back(make_pair(j,s4.arr[j]));
            }
        }
        LIST[row] = v;
        row++;
    }

    ifstream ifs5("city_index.txt");
    ci s5;
    while(ifs5 >> s5)
    {
        ctoI[s5.city_name] = s5.index;
        itoC[s5.index] = s5.city_name;
    }
}

class paradise{
public :
    void m()
    {
    clrscr();
 int i,j,count=3;
 char ch='a';
 int l;
for(l=0;l<3;l++)
t[l].list=NULL;

textcolor(WHITE);

 char y1[]=".           .       ";

 char y3[]="|    _  _. _|*._  _ ";

 char y4[]="|___(_)(_](_]|[ )(_]";

 char y5[]="                 ._|";
 gotoxy(66,11);
 cputs(y1);
 gotoxy(66,12);
 cputs(y3);
 gotoxy(66,13);
 cputs(y4);
 gotoxy(66,14);
 cputs(y5);
 char y2='-';
 textcolor(12);
 for(i=0;i<2;i++)
 {
 for(j=66;j<86;j++)
 {
 gotoxy(j,16);
 clreol();
 putch(y2);
 delay(200);
 }
 clreol();
 delay(250);
 }
 textcolor(3);
 char z[]=".__ .__..__ .__..__ ._. __..___";
 char z1[]="[__)[__][__)[__]|  \\ | (__ [__ ";
 char z2[]="|   |  ||  \\|  ||__/_|_.__)[___";
 for(i=1;i<17;i++)
 {
 clrscr();
 gotoxy(66,i);
 cputs(z);
 gotoxy(66,i+1);
 cputs(z1);
gotoxy(66,i+2);
 cputs(z2);
 delay(150);
 }


 for(i=1;i<150;i=i+10)
 {

 delay(175);

 }

 clrscr();
    read();
 char pass[]=" ";
 char password[30];
 do{
 gotoxy(66,13);
 printf("Enter the Password");
 int i=0;
 char tp;
 while((tp=getch())!='\r')
 {
 printf("*");
 password[i]=tp;
 i++;
 }
 password[i]='\0';
 if(strcmp(password,pass)==0)
 break;
 else
 gotoxy(66,14);
 printf("Wrong Password");
 getch();
 clrscr();
 }while(1);


textbackground(WHITE);
 textcolor(1);
 clrscr();
frame();

ctoI["Noida"] = 0;
 ctoI["Indirapuram"] = 1;
 ctoI["Vaishali"] = 2;
ctoI["Kaushambi"] = 3;
 ctoI["LaxmiNagar"] = 4;


itoC[0] = "Noida";
itoC[1] = "Indirapuram";
itoC[2] = "Vaishali";
itoC[3] = "Kaushambi";
itoC[4] = "LaxmiNagar";

delay(1000);
save_city_to_file();
vector<pair<int,int>> v;
v.push_back(make_pair(1,1));
v.push_back(make_pair(4,10));
LIST[0] = v;
v.clear();
v.push_back(make_pair(0,1));
v.push_back(make_pair(2,5));
LIST[1] = v;
v.clear();
v.push_back(make_pair(1,5));
v.push_back(make_pair(4,7));
v.push_back(make_pair(3,2));
LIST[2] = v;
v.clear();
v.push_back(make_pair(2,2));
v.push_back(make_pair(4,6));
LIST[3] = v;
v.clear();
v.push_back(make_pair(0,10));
v.push_back(make_pair(2,7));
v.push_back(make_pair(3,6));
LIST[4] = v;
int ctr=0;
do{
clrscr();
ch=mainmenu();
if (ch=='6')
{

     ofstream ofs2("dish_priority.dat");
     int i = 0;
      for(auto it  = dish_map.begin();it!=dish_map.end();it++)
      {
          vector<int> v = it->second;
          for(int j = 0;j<v.size();j++)
          {
              foo f1(it->first,v[j]);
              i++;
              ofs2 << f1;
          }
      }
ofs2.close();
     ofstream ofs("xyz2.dat");
      for ( auto it = cust_map.begin(); it != cust_map.end(); ++it)
    {
      cust_node *customer = it->second;
      cust_node s1(customer);
      s1.parent = NULL;
	  ofs << s1;
    }
    ofs.close();
ofstream ofs3("bill.dat");
for(int i = 0;i<tot.size();i++)
{
    ofs3 << tot[i];
}
ofs3.close();
    gotoxy(80,13);
 printf("----------");
 gotoxy(80,14);
 printf(" Thank You");
 gotoxy(80,15);
 printf("----------");
}
if(ch == '6')
{
    exit(0);
}
if(ch=='1')
{
char ch1=' ';
int z=100;
int t1;
for(t1=0;t1<3;t1++)
{
    if(t[t1].list==NULL)
    {
        z=t1;
        break;
    }

}
ctr=z;
clrscr();
gotoxy(66,14);

for(int i = 0;i<no_of_cities;i++)
{
        destination[i] = false;
}

g:
cout << "ENTER 1 IF THE ORDER IS FOR DELIVERY: " ;
int choice;
cin >> choice;
if(choice == 1)
{
    ch1 = addcustomer2();
    vector<pair<int,int>> v;
    takeorder(v);
    bill_generation(v);
    deliver();
}
else
{
ch1=addcustomer();
if(ctr==100 && ch1!='0')
{
    clrscr();
    insert();
    continue;
}

if(ch1!='0')
{
strcpy(t[ctr].name,c.name);
strcpy(t[ctr].phno,c.phno);
if(cust_map.count(t[ctr].phno) == 0)
{
string ref_id;
clrscr();
gotoxy(66,14);
cout << "Enter ref_id (if_any):-";
cin >> ref_id;
add_to_graph(t[ctr].name,t[ctr].phno,ref_id);
}

int no,quan1;
      while(ch1!='0')
    {
    clrscr();
    display_menu();
    gotoxy(34,30);
    printf("Enter Item No.:");
      scanf("%d",&no);//99 to break;
      if(no>=12)
        goto g;
      gotoxy(34,32);
      printf("Enter Quantity:");
      scanf("%d",&quan1);
      if(quan1==0)
        continue;

      add(&(t[ctr].list),no,quan1,t[ctr].phno);

      gotoxy(34,34);
      printf("Press any Key to Continue or Press 0 to Return:");
      scanf(" %c",&ch1);
      }
continue;
}
}
if(ch1=='0')
    {
        continue;
    }
}
if (ch=='2')//add more
{
    clrscr();
    int l;
gotoxy(66,13);
printf("Enter Table Number:");
scanf("%d",&l);
l--;
if(t[l].list==NULL)
{clrscr();
    gotoxy(66,13);
    printf("TABLE IS EMPTY!!!!!!");
    gotoxy(66,14);
    printf("Returning to Main Menu");
    gotoxy(66,15);
    printf("Press Enter to Continue");
getch();
continue;

}
else
{
char ch1=' ';
int no,quan1;
      while(ch1!='0')
      {
          clrscr();
    display_menu();
       gotoxy(34,30);
    printf("Enter Item No.:");
      scanf("%d",&no);//99 to break;
      if(no>=12)
        continue;
     gotoxy(34,32);
      printf("Enter Quantity:");
      scanf("%d",&quan1);
      if(quan1==0)
        continue;
      add(&(t[l].list),no,quan1,t[l].phno);

      gotoxy(34,34);
      printf("Press any Key to Continue or Press 0 to Return:");
      scanf(" %c",&ch1);
      }



continue;
}


}


if(ch=='3')
   {
       int tex=0;
        gotoxy(62,22);
    cout << "TABLE NO";
    gotoxy(78,22);
   cout <<"NAME";
   gotoxy(89,22);
    cout << "PHONE NO";
    gotoxy(60,23);
    cout << "----------------------------------------";
    for(int i = 0;i<3;i++)
    {
        gotoxy(62,i+24);
     cout  << i+1;
    gotoxy(78,i+24);
    if(t[i].list != NULL)
   cout  <<t[i].name;
   else
    cout << "empty";
   gotoxy(89,i+24);
   if(t[i].list != NULL)
    cout << t[i].phno;
    else
    cout << "empty";
    }
    int p;
    gotoxy(65,14);
    printf("Enter Table Number to be Cleared:");
    scanf("%d",&p);
    p--;
    if(t[p].list==NULL)
    {
        gotoxy(70,16);
        printf("Table is Already Empty!!!!");getch();
        continue;
        }
    cleartable(p);

    if(!(front==0&&rear==-1))
    {
        delet();
        tex=1;
        clrscr();
        gotoxy(55,11);
        printf("Allotting Table to Waiting list Customer");
    gotoxy(60,13);
		printf("Name:");
		gotoxy(66,13);
		printf("%s",a.name);
		gotoxy(89,13);
		printf("Phone No.:");
		gotoxy(100,13);
		printf("%s",a.phno);


strcpy(t[p].name,a.name);
strcpy(t[p].phno,a.phno);
gotoxy(55,15);
printf("Table Number:%d has been allotted to this Customer",p+1);
getch();
int no,quan1;
char ch1=' ';
      while(ch1!='0')
      {
          clrscr();
    display_menu();
    gotoxy(34,30);
    printf("Enter Item No.:");
      scanf("%d",&no);//99 to break;
      if(no>=12)
        continue;
     gotoxy(34,32);
      printf("Enter Quantity:");
      scanf("%d",&quan1);
      if(quan1==0)
        continue;
      add(&(t[l].list),no,quan1,t[l].phno);
      gotoxy(34,34);
      printf("Press any Key to Continue or Press 0 to Return:");
  scanf(" %c",&ch1);
      }

    }
    if(p>0&&p<=3&&(tex==0))
        count++;

   }
if(ch=='4')//table left
   {
int z=0;
    gotoxy(66,13);
    printf("Table Empty:");
gotoxy(78,13);
printf("%d    Table Numbers are: ",count);
for(l=0;l<3;l++)
if(t[l].list==NULL)

    {
        printf("%d ",l+1);
         z=1;
   }
if(z==0)
    printf("0");

   getch();

   }
if(ch=='5')//display queue
{
    display();
    getch();
}
if(ch == '7')
{
     dish_map.clear();

    for(int i = 0;i<dish_arr.size();i++)
    {
        dish_map[dish_arr[i]].push_back(i);
        //cout << dish_arr[i] << " ";
    }
    vector<int> x(dish_arr.begin(),dish_arr.end());
    make_heap(x.begin(),x.end());
    sort_heap(x.begin(),x.end());

    clrscr();
    gotoxy(65,15);
    cout << "Dish no" << "                " << "Dish_Name";
    int k =0;
    for(int i = x.size()-1;i>=0;)
    {

        vector<int> v = dish_map[x[i]];
        for(int j = 0;j<v.size();j++)
        {
            gotoxy(65,k+18);
            cout << v[j] << "                " << menu[v[j]].food;
            k++;
            i--;
        }
    }
getch();
}
if(ch == '8')
{
    add_city();
}
}while(1);


    }

};
int main()
{
   paradise p;
   p.m();

return 0;

}
