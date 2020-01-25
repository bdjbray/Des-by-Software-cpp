//Copyright 2019 Dingjun Bian braybian@bu.edu

double largest_double(){
  double num=1.0;
  double exp=1;
  double po=1.0;
  for(int ex=1023;ex>0;ex--){
    exp=exp*2;
  }
  for(int i=1;i<53;i++){
    po=1;
    for(int j=i;j>0;j--){
      po=po*0.5;
      }
   num=num+po;
   }
  double ld=num*exp;
  return ld;
}


double smallest_double(){
  double sd=0.0;
  double po2=1.0;
  for(int i2=1;i2<1075;i2++){
    po2=po2*0.5;
  }
  sd=sd+po2;
  return sd;
}
  
float largest_single(){
  float num=1.0;
  float exp=1;
  float po=1.0;
  for(int ex=127;ex>0;ex--){
    exp=exp*2;
  }
  for(int i=1;i<24;i++){
    po=1;
    for(int j=i;j>0;j--){
      po=po*0.5;
    }
  num=num+po;
  }
  float ls=num*exp;
  return ls;
}

float smallest_single(){
  float ss=0.0;
  float po3=1.0;
  for(int i3=1;i3<150;i3++){
    po3=po3*0.5;
  }
  ss=ss+po3;
  return ss;
}


