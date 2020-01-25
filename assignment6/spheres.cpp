//Copyright 2019 Dingjun Bian braybian@bu.edu
//Copyright 2019 Shiyang Hu shiyangh@bu.edu
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>



using std::vector;
using std::cout;
using std::cerr;
using std::stod;
using std::string;

struct ball {
  double m,R,rx, ry,rz, vx, vy,vz;  // r:position v:velocity
  string name;
};

struct Colli {      
  double event_time;
  int one, two;
};

struct Colliwall {      
  double event_time;
  int one;
};

struct Colli2 {      
  double event_time;
  int one, two,three,four;
  int on;
};
struct Collimul {      
  double event_time;
  int o1,o2,o3,o4,o5,o6,o7,o8,o9,o10,o11,o12,o13,o14,o15,o16;
  int on;
};


void collide_two_balls(ball *one, ball *two) {  //calculate the change of velocity
  double xx = two->rx - one->rx;
  double xy = two->ry - one->ry;
  double xz = two->rz - one->rz;
  double vx = two->vx - one->vx;
  double vy = two->vy - one->vy;
  double vz = two->vz - one->vz;
  double sub1 = vx * xx + vy * xy+vz*xz;
  double sub2 = xx * xx + xy * xy+xz*xz;  
  double m1=(2*two->m)/(one->m+two->m);
  double m2=(2*one->m)/(one->m+two->m);
  one->vz  +=  m1*(sub1) * (xz) / sub2;
  two->vz  +=  -(m2*sub1) * (xz) / sub2;
  one->vy  +=  (m1*sub1) * (xy) / sub2;
  two->vy  +=  -(m2*sub1) * (xy) / sub2;
  one->vx  += (m1*sub1) * (xx) / sub2;
  two->vx  += -(m2*sub1) * (xx) / sub2;
  ////cout<<"new v:"<<one->vx<<' '<<two->vx<<' '<<one->vy<<' '<<two->vy<<' '<<one->vz<<' '<<two->vz<<'\n';
}

void collide_with_wall(ball *one) {    //change the velocity of one ball hit the wall
  double down1=one->rx*one->rx;
  double down2=one->ry*one->ry;
  double down3=one->rz*one->rz;
  double possum=one->rx+one->ry+one->rz;
  double up1=one->vx*one->rx;
  double up2=one->vy*one->ry;
  double up3=one->vz*one->rz;
  double down=down1+down2+down3;
  double up=up1+up2+up3;
  double mid=2*up/down;
  one->vx=one->vx-mid*one->rx;
  one->vy=one->vy-mid*one->ry;
  one->vz=one->vz-mid*one->rz;
  ////cout<<"new v:"<<one->vx<<' '<<one->vy<<' '<<one->vz<<'\n';
}


double collide_time(const ball* one, const ball* two,double area) {  //calculate Colli time
   if ((one->rx==two->rx) and (one->ry==two->ry) and (one->rz==two->rz))
   {
     return 1e100;
   }
  double tcollball=1e100;
  double a = one->rx - two->rx;
  double b = one->ry - two->ry;
  double c = one->rz - two->rz;
  double d = one->vx - two->vx;
  double e = one->vy - two->vy;
  double f = one->vz - two->vz;
  double A = d * d + e * e+f*f;
  if (A==0)
  {
    return 1e100;
  }
  double B = 2 * (a * d + b * e+c*f);
  double C = a * a + b * b+c*c -(two->R+one->R)*(two->R+one->R) ;
  double rootarg = B * B - 4 * A * C;
  if (rootarg < 0) return 1e38;
  double root = sqrt(rootarg);
  double t1 = (-B - root) / (2 * A);
  double t2 = (-B + root) / (2 * A);
  //if ((t1 == 0) and (a * d + b * e+c*f < 0))
  //  return 0;
  //double sum1=(one->rx+one->vx*t1)*(one->rx+one->vx*t1)+(one->ry+one->vy*t1)*(one->ry+one->vy*t1)+(one->rz+one->vz*t1)*(one->rz+one->vz*t1);
  //double sum2=(two->rx+two->vx*t1)*(two->rx+two->vx*t1)+(two->ry+two->vy*t1)*(two->ry+two->vy*t1)+(two->rz+two->vz*t1)*(two->rz+two->vz*t1);
  //double sum3=(one->rx+one->vx*t2)*(one->rx+one->vx*t2)+(one->ry+one->vy*t2)*(one->ry+one->vy*t2)+(one->rz+one->vz*t2)*(one->rz+one->vz*t2);
  //double sum4=(two->rx+two->vx*t2)*(two->rx+two->vx*t2)+(two->ry+two->vy*t2)*(two->ry+two->vy*t2)+(two->rz+two->vz*t2)*(two->rz+two->vz*t2);
  //double areasum=area*area;
  if ((t1 > 0) and (t1<tcollball)){ /////////////
    tcollball= t1;
    }
  if ((t2<tcollball) and (t2>0)){
    tcollball=t2;
   }
  //cout<<"t1 and t2:"<<tcollball<<"\n"<<t1<<"\n"<<t2<<"\n";

  //cout<<"one R:"<<one->R<<" two R:"<<two->R<<"\n";
  return tcollball;
}


void update_position(ball *one, const double dt) {   //update location
  one->rx += one->vx * dt;
  one->ry += one->vy * dt;
  one->rz += one->vz * dt;
}


double wall_time(const ball* one,double area){      //calculate the time of one ball hit the wall
  double tmin=1e100;
  double a=one->vx*one->vx+one->vy*one->vy+one->vz*one->vz;
  double b=2*one->vx*one->rx+2*one->vy*one->ry+2*one->vz*one->rz;
  double c=one->rx*one->rx+one->ry*one->ry+one->rz*one->rz-(area-one->R)*(area-one->R);/////////////////////////////
  double sq=b*b-4*a*c;
  if (sq<0)
    return 1;
  double sqgen=sqrt(sq);
  double t_mid=(-b-sqgen)/(2*a);
  double t_misub2=(-b+ sqgen)/(2*a);
  if ((t_mid<tmin) and (t_mid>0))
    tmin=t_mid;
  if ((t_misub2<tmin) and (t_misub2>0))
    tmin=t_misub2;
  return tmin;
}

void initial_ball_report(const vector<ball> & balls,const vector<int> & bounce,double area,double times){  //inittial balls report
cout<<"Here are the initial spheres.\n";
cout<<"universe radius "<<area<<"\n";
cout<<"max collsions "<<times<<"\n";
double totalener=0;
double ener;
double momentum1=0;
double momentum2=0;
double momentum3=0;
for(int i=0;i<balls.size();i++){
cout<<balls[i].name<<" m="<<balls[i].m<<" R="<<balls[i].R<<" p= ("<<balls[i].rx<<','<<balls[i].ry<<','<<balls[i].rz<<") v=("<<balls[i].vx<<','<<balls[i].vy<<','<<balls[i].vz<<") bounces="<<bounce[i]<<"\n";
ener=balls[i].m*(balls[i].vx*balls[i].vx+balls[i].vy*balls[i].vy+balls[i].vz*balls[i].vz)/2;
totalener=totalener+ener;
momentum1=momentum1+balls[i].m*balls[i].vx;
momentum2=momentum2+balls[i].m*balls[i].vy;
momentum3=momentum3+balls[i].m*balls[i].vz;
  }
cout<<"energy: "<<totalener<<"\n";
cout<<"momentum: ("<<momentum1<<','<<momentum2<<','<<momentum3<<")\n";
}


void ballcolli_report(const ball* one, const ball* two,const vector<ball> & balls, double curr_time,const vector<int> & bounce){
double energy=0;
double momentum1=0;
double momentum2=0;
double momentum3=0;
cout<<"time of event: "<<curr_time<<"\n";
cout<<"colliding "<<one->name<<' '<<two->name<<"\n";
for(int i=0;i<balls.size();i++){
  cout<<balls[i].name<<" m="<<balls[i].m<<" R="<<balls[i].R<<" p= ("<<balls[i].rx<<','<<balls[i].ry<<','<<balls[i].rz<<") v=("<<balls[i].vx<<','<<balls[i].vy<<','<<balls[i].vz<<") bounce="<<bounce[i]<<"\n";
}
for (int i = 0; i < balls.size(); i++){
  energy=energy+balls[i].m*(balls[i].vx*balls[i].vx+balls[i].vy*balls[i].vy+balls[i].vz*balls[i].vz)/2;
}
for (int i = 0; i < balls.size(); i++){
   momentum1=momentum1+balls[i].m*balls[i].vx;
}
for (int i = 0; i <balls.size() ; i++){
  momentum2=momentum2+balls[i].m*balls[i].vy;
}
for (int i = 0; i < balls.size(); i++){
  momentum3=momentum3+balls[i].m*balls[i].vz;
}
cout<<"energy: "<<energy<<"\n";
cout<<"momentum: ("<<momentum1<<','<<momentum2<<','<<momentum3<<")\n";
}


void ballcolliwall_report(const ball* one, const vector<ball> & balls,double curr_time,const vector<int> & bounce){
double energy=0;
double momentum1=0;
double momentum2=0;
double momentum3=0;
cout<<"time of event: "<<curr_time<<"\n";
cout<<"reflecting "<<one->name<<"\n";
for(int i=0;i<balls.size();i++){
  cout<<balls[i].name<<" m="<<balls[i].m<<" R="<<balls[i].R<<" p= ("<<balls[i].rx<<','<<balls[i].ry<<','<<balls[i].rz<<") v=("<<balls[i].vx<<','<<balls[i].vy<<','<<balls[i].vz<<") bounce="<<bounce[i]<<"\n";
}
for (int i = 0; i < balls.size(); i++){
  energy=energy+balls[i].m*(balls[i].vx*balls[i].vx+balls[i].vy*balls[i].vy+balls[i].vz*balls[i].vz)/2;
}
for (int i = 0; i < balls.size(); i++){
   momentum1=momentum1+balls[i].m*balls[i].vx;
}
for (int i = 0; i <balls.size() ; i++){
  momentum2=momentum2+balls[i].m*balls[i].vy;
}
for (int i = 0; i < balls.size(); i++){
  momentum3=momentum3+balls[i].m*balls[i].vz;
}
cout<<"energy: "<<energy<<"\n";
cout<<"momentum: ("<<momentum1<<','<<momentum2<<','<<momentum3<<")\n";
}



Colli get_next_Colli(double curr_time, const vector<ball> &balls,double area) { //use Colli time to get the real Colli
  double next_Colli = 1e100;
  double ct, one, two;
  Colli c;
  for (int i = 0; i < balls.size() ; i++) {
    for (int j = i + 1; j < balls.size() ; j++) {
        if(i!=j)
      ct = collide_time(&balls[i], &balls[j],area);  //use collide time to get different time
      //cout<<"ct:"<<ct<<'\n';
      if ((ct >0) and (ct < next_Colli)) {
        next_Colli = ct;
        c.one = i;
        c.two = j;
      }
    }
  }
  c.event_time = next_Colli ;
  return c;  
}


Colli2 get_next_Colli2(double curr_time, const vector<ball> &balls,double area) { //use Colli time to get the real Colli
  double next_Colli = 1e100;
  double ct, one, two,three,four;
  Colli2 c;
  for (int i = 0; i < balls.size() ; i++) {
    for (int j = i + 1; j < balls.size() ; j++) {
        if(i!=j)
      ct = collide_time(&balls[i], &balls[j],area);  //use collide time to get different time
      if ((ct >0) and (ct < next_Colli)) {
        next_Colli = ct;
        c.one = i;
        c.two = j;
        //cout<<"two ball calli test:"<<ct<<"\n";
      }
     else if((ct==next_Colli)and(ct>0)and(ct<1e30)){
        c.three=i;
        c.four=j;
        c.on=1;
        //cout<<"two ball calli test2:"<<ct<<"\n";
      }
    }
  }
  c.event_time = next_Colli ;
  return c;  
}

Collimul get_mul_Colli(double curr_time, const vector<ball> &balls,double area) { //use Colli time to get the real Colli
  double next_Colli = 1e100;
  double ct, o1, o2,o3,o4,o5, o6,o7,o8,o9, o10,o11,o12,o13, o14,o15,o16;
  int s0,s1,s2,s3,s4,s5,s6;
  Collimul c;
  for (int i = 0; i < balls.size() ; i++) {
    for (int j = i + 1; j < balls.size() ; j++) {
        if(i!=j)
      ct = collide_time(&balls[i], &balls[j],area);  //use collide time to get different time
      if ((ct >0) and (ct < next_Colli)) {
        next_Colli = ct;
        c.o1 = i;
        c.o2= j;
        s0=1;
        //cout<<"two ball calli test:"<<ct<<"\n";
      }
     else if((ct==next_Colli)and(ct>0)and(ct<1e100)and(s0==1)){
        c.o3=i;
        c.o4=j;
        s1=1;
        s0=0;
        //cout<<"point2!!!!!!!!";
        //cout<<"two ball calli test2:"<<ct<<"\n";
      }
      else if((ct==next_Colli)and(ct>0)and(ct<1e100)and(s1==1)){
        c.o5=i;
        c.o6=j;
        s2=1;
        s1=0;
        //cout<<"point3!!!!!!!!";
        //cout<<"two ball calli test2:"<<ct<<"\n";
      }
      else if((ct==next_Colli)and(ct>0)and(ct<1e100)and(s2==1)){
        c.o7=i;
        c.o8=j;
        s3=1;
        s2=0;
        //cout<<"point4!!!!!!!!";
        //cout<<"two ball calli test2:"<<ct<<"\n";
      }
      else if((ct==next_Colli)and(ct>0)and(ct<1e100)and(s3==1)){
        c.o9=i;
        c.o10=j;
        s4=1;
        s3=0;
        //cout<<"point5!!!!!!!!";
        //cout<<"two ball calli test2:"<<ct<<"\n";
      }
      else if((ct==next_Colli)and(ct>0)and(ct<1e100)and(s4==1)){
        c.o11=i;
        c.o12=j;
        s5=1;
        s4=0;
        //cout<<"point6!!!!!!!!";
        //cout<<"two ball calli test2:"<<ct<<"\n";
      }
      else if((ct==next_Colli)and(ct>0)and(ct<1e100)and(s5==1)){
        c.o13=i;
        c.o14=j;
        s6=1;
        s5=0;
        //cout<<"point7!!!!!!!!";
        //cout<<"two ball calli test2:"<<ct<<"\n";
      }
      else if((ct==next_Colli)and(ct>0)and(ct<1e100)and(s6==1)){
        c.o15=i;
        c.o16=j;
        c.on=1;
        //cout<<"point8!!!!!!!!";
        //cout<<"two ball calli test2:"<<ct<<"\n";
      }
    }
  }
  c.event_time = next_Colli ;
  return c;  
}






Colliwall hit_thewall(const vector<ball> &balls, double curr_time,double area){    //compare different hit wall time and get the smallest one
  double hitwall_time=1e100;
  Colliwall colwal;
  double mid_time;
  for(int i=0;i<balls.size();i++){
    mid_time=wall_time(&balls[i], area);
    ////cout<<"mid_time:"<<mid_time;
      if ((mid_time<hitwall_time)and(mid_time>0)){
          hitwall_time=mid_time;
          colwal.one=i;
      }
  }
  colwal.event_time=hitwall_time;
  ////cout<<"colwal:"<<colwal.event_time<<"\n";
  return colwal;
}


int main(int argc, char const *argv[]) {
  cout<<"Please enter the mass, radius, x/y/z position, x/y/z velocity and name of each sphere When complete, use EOF / Ctrl-D to stop entering\n";
  cout.precision(6);
  vector<double> argv_info;  
  vector<ball> balls;
  ball s;
  int seperate=1;
  double curr_time, dt;
  double area,times;
  int one, two;  // balls involved in the event.
  try {            //get the report time from argv
    for (int i = 1; i < argc; i++) {
      double procue = std::stod(argv[i]);
      if  (procue >= 0)
        argv_info.push_back(procue);  //store info of argv to vector
    }
  } catch (...) {
    return 1;
  }
  if (argv_info.empty())
    return 1;
  area=argv_info[0];
  times=argv_info[1];
  curr_time = 0;
  std::stringstream ss;
  std::string line, rest, proc;
  while (std::getline(std::cin, line)) {   //after '/n' it will stop store string,next loop it will store the next string
    ss << line;
    try {
      ss >> proc;
      s.m = std::stod(proc);
      ss >> proc;
      s.R = std::stod(proc);
      ss >> proc;
      s.rx = std::stod(proc);
      ss >> proc;
      s.ry = std::stod(proc);
      ss >> proc;
      s.rz = std::stod(proc);
      ss >> proc;
      s.vx = std::stod(proc);
      ss >> proc;
      s.vy = std::stod(proc);
      ss >> proc;
      s.vz = std::stod(proc);
      ss >> s.name;
      }
    catch (...) {
      return 1;
    }
    ss.str("");
    ss.clear();
    balls.push_back(s);  //yi hang yi hang cun dao balls zhong
  }
  vector<int> bounce;
  for (int i = 0; i < balls.size(); i++)
  {
    bounce.push_back(0); /* code */
  }
  
  initial_ball_report(balls,bounce,area,times); //for the initial report
  //int  next_report_index = 0;
  Colli colli;
  Colliwall colwal;
  Colli2 colli2;
  Collimul collimul;
  while (true) {
    double next_event_time=1e100;
    // find the next Colli event and the colliding object
    colli = get_next_Colli(curr_time, balls,area);
    colwal=hit_thewall(balls,curr_time,area);
    colli2=get_next_Colli2(curr_time, balls,area);
    collimul=get_mul_Colli(curr_time, balls,area);

    
    if(collimul.on==1){
         next_event_time=collimul.event_time;
         seperate=3;
    }
    else if(colli2.on==1){
         next_event_time=colli2.event_time;
         seperate=2;
    }
    if((colli.event_time<next_event_time) and (colli.event_time>0)){
          next_event_time=colli.event_time;
          seperate=1;
          ////cout<<"qiu zhuang:"<<Colli.event_time<<'\n';
    }
    if((colwal.event_time<next_event_time) and (colwal.event_time>0)){
          next_event_time=colwal.event_time;
          seperate=0;
    }
    if (next_event_time>1e100)
    {
      return 1;
    }
    curr_time=curr_time+next_event_time;          
    ////cout<<"4 times:"<<curr_time<<' '<<next_event_time<<' '<<Colli.event_time<<' '<<colwal.event_time<<'\n';
    ////cout<<"seperate: "<<seperate<<"\n";
    for (int i = 0; i < balls.size(); i++)
      update_position(&balls[i], next_event_time);
    if (seperate==3){         //seperate=2 go to 2 balls Colli at the same time
      collide_two_balls(&balls[collimul.o1], &balls[collimul.o2]);   //update velocity
      bounce[collimul.o1]=bounce[collimul.o1]+1;
      bounce[collimul.o2]=bounce[collimul.o2]+1;
      ballcolli_report(&balls[collimul.o1], &balls[collimul.o2],balls,curr_time,bounce);
      collide_two_balls(&balls[collimul.o3], &balls[collimul.o4]);
       bounce[collimul.o3]=bounce[collimul.o3]+1;
      bounce[collimul.o4]=bounce[collimul.o4]+1;
      ballcolli_report(&balls[collimul.o3], &balls[collimul.o4],balls,curr_time,bounce);
      collide_two_balls(&balls[collimul.o5], &balls[collimul.o6]);   //update velocity
      bounce[collimul.o5]=bounce[collimul.o5]+1;
      bounce[collimul.o6]=bounce[collimul.o6]+1;
      ballcolli_report(&balls[collimul.o5], &balls[collimul.o6],balls,curr_time,bounce);
      collide_two_balls(&balls[collimul.o7], &balls[collimul.o8]);
      bounce[collimul.o7]=bounce[collimul.o7]+1;
      bounce[collimul.o8]=bounce[collimul.o8]+1;
      ballcolli_report(&balls[collimul.o7], &balls[collimul.o8],balls,curr_time,bounce);
      collide_two_balls(&balls[collimul.o9], &balls[collimul.o10]);   //update velocity
      bounce[collimul.o9]=bounce[collimul.o9]+1;
      bounce[collimul.o10]=bounce[collimul.o10]+1;
      ballcolli_report(&balls[collimul.o9], &balls[collimul.o10],balls,curr_time,bounce);
      collide_two_balls(&balls[collimul.o11], &balls[collimul.o12]);
      bounce[collimul.o11]=bounce[collimul.o11]+1;
      bounce[collimul.o12]=bounce[collimul.o12]+1;
      ballcolli_report(&balls[collimul.o11], &balls[collimul.o12],balls,curr_time,bounce);
      collide_two_balls(&balls[collimul.o13], &balls[collimul.o14]);   //update velocity
      bounce[collimul.o13]=bounce[collimul.o13]+1;
      bounce[collimul.o14]=bounce[collimul.o14]+1;
      ballcolli_report(&balls[collimul.o13], &balls[collimul.o14],balls,curr_time,bounce);
      collide_two_balls(&balls[collimul.o15], &balls[collimul.o16]);
      bounce[collimul.o15]=bounce[collimul.o15]+1;
      bounce[collimul.o16]=bounce[collimul.o16]+1;
      ballcolli_report(&balls[collimul.o15], &balls[collimul.o16],balls,curr_time,bounce);

    }

     if (seperate==2){         //seperate=2 go to 2 balls Colli at the same time
      collide_two_balls(&balls[colli2.one], &balls[colli2.two]);   //update velocity
      bounce[colli2.one]=bounce[colli2.one]+1;
      bounce[colli2.two]=bounce[colli2.two]+1;
      ballcolli_report(&balls[colli2.one], &balls[colli2.two],balls,curr_time,bounce);
      collide_two_balls(&balls[colli2.three], &balls[colli2.four]);
      bounce[colli2.three]=bounce[colli2.three]+1;
      bounce[colli2.four]=bounce[colli2.four]+1;
      ballcolli_report(&balls[colli2.three], &balls[colli2.four],balls,curr_time,bounce);
    }
    if (seperate==1){         //seperate=1 go to two balls collison 
      bounce[colli.one]=bounce[colli.one]+1;
      bounce[colli.two]=bounce[colli.two]+1;
      collide_two_balls(&balls[colli.one], &balls[colli.two]);   //update the speed
      ballcolli_report(&balls[colli.one], &balls[colli.two],balls,curr_time,bounce);
    }
    if (seperate==0){        //seperate=0 go to one ball hit the wall
      ////cout<<"hit the wall!!!!\n";
      bounce[colwal.one]=bounce[colwal.one]+1;
      collide_with_wall(&balls[colwal.one]);
      ballcolliwall_report(&balls[colwal.one],balls, curr_time,bounce);
    }
    
    double tinymove=0.00001;
    curr_time=curr_time+tinymove;
    for (int i = 0; i < balls.size(); i++){   //avoid same collison count twice
      update_position(&balls[i], tinymove);
      ////cout<<"increased\n";
    }
    for (int i = (bounce.size()-1); i >=0; i--){
       if (bounce[i]>=times){
        cout<<"disappear "<<balls[i].name<<"\n";
        balls.erase(balls.begin()+i,balls.begin()+i+1);
        bounce.erase(bounce.begin()+i,bounce.begin()+i+1);
      }
    }
    //cout<<"ball size:"<<balls.size();
    if(balls.size()==0){
         break;
    }
  }
  return 0;
}





