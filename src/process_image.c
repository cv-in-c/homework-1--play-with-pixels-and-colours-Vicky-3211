#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"
float get_pixel(image im, int x, int y, int c)
{
    if(0<=x&& x<im.c && 0<=y&&y<im.h && 0<=c&&c<im.w)
   return im.data[x+y*im.w+c*im.w*im.h];
   else{
      if (x<0)  x=0;
      if (x>=im.w) x=im.w-1;
      if (y<0) y=0;
      if (y>=im.h) y=im.h-1;
      if (c<0)  c=0;
      if (c>=im.c) c=im.c-1; 
      return im.data[x+ y*im.w +c*im.w*im.h];
   }
}

void set_pixel(image im, int x, int y, int c, float v)
{
    if(0<x<im.c && 0<y<im.h && 0<c<im.w)
   im.data[x+y*im.w+c*im.w*im.h]=v;
    else return;
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    memcpy(copy.data,im.data,im.w*im.h*im.c*sizeof(float));
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    for(int i=0;i<im.h*im.w;i++){
    gray.data[i]=0.299*im.data[i]+0.587*im.data[im.h*(im.w)+i]+0.114*im.data[2*im.h*(im.w)+i];
    }
    return gray;
}

void shift_image(image im, int c, float v)
{   for(int i=c*im.h*im.w;i<(c+1)*im.h*im.w;i++)
im.data[i]+=v;
}

void clamp_image(image im)
{
    for(int i=0;i<im.h*im.w*im.c;i++){
    if(im.data[i]<0) im.data[i]=0;
    else if(im.data[i]>1) im.data[i]=1;
    }
}



// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    float h,h1;
    for(int i=0;i<im.h*im.w;i++){
    float r=im.data[i];
    float g=im.data[(im.w*im.h)+i];
    float b=im.data[(im.w*im.h*2)+i];
    
    float m=three_way_min(r,g,b);

    float val=three_way_max(r,g,b);
    float c=val-m;
    float sat;
    if(r==0 && g==0 && b==0) sat=0;
    else sat=c/val;

    if(c==0) h1=0;
    else if(val==r) h1=(g-b)/(c);
    else if(val==g) h1=((b-r)/c)+2;
    else if(val==b) h1=((r-g)/c)+4;

    if(h1<0) h=h1/6 +1;
    else h=h1/6;
    
    im.data[i]=h; im.data[(im.w*im.h)+i]=sat; im.data[(im.w*im.h*2)+i]=val; 
    }
}


void hsv_to_rgb(image im)
{
    float h,s,v;
    for(int i=0;i<im.w*im.h;i++){
    h=im.data[i];
    s=im.data[im.w*im.h+i];
    v=im.data[2*im.w*im.h+i];

    float c,m;
    c=s*v;
    m=v-c;

    float r=0,g=0,b=0;
    
    
 if(m<=6*(h)*c+m&&6*(h)*c+m<=v) {
        r=v; b=m;g=6*h*c+m;
    }
    else if(m<=m-(6*(h)*c)&&m-(6*(h)*c)<=v){
        g=m; b=m-(6*h*c); r=v;
    }
    else if(m<=(6*h-2)*c + m&&(6*h-2)*c + m<=v){
        r=m; b=(6*h-2)*c + m; g=v;
    }
    else if(m<=m-(6*h-2)*c&&m-(6*h-2)*c<=v){
        g=v; r=m-(6*h-2)*c; b=m;
    }
    else if(m<=(6*h-4)*c+m&&(6*h-4)*c+m<=v){
        r=(6*h-4)*c+m; g=m; b=v;
    }
    else if(m<=m-(6*h-4)*c&&m-(6*h-4)*c<=v){
        g=m-(6*h-4)*c; r=m; b=v;
    }
    
    float h1=6*(h-1);
    if(r==0&&g==0&&b==0){
        
        
          if(m<=h1*c+m&&h1*c+m<=v) {
        r=v; b=m;g=h1*c+m;
    }
    else if(m<=m-(h1*c)&&m-(h1*c)<=v){
        g=m; b=m-(h1*c); r=v;
    }
    else if(m<=(h1-2)*c + m&&(h1-2)*c + m<=v){
        r=m; b=(h1-2)*c + m; g=v;
    }
    else if(m<=m-(h1-2)*c&&m-(h1-2)*c<=v){
        g=v; r=m-(h1-2)*c; b=m;
    }
    else if(m<=(h1-4)*c+m&&(h1-4)*c+m<=v){
        r=(h1-4)*c+m; g=m; b=v;
    }
    else if(m<=m-(h1-4)*c&&m-(h1-4)*c<=v){
        g=m-(h1-4)*c; r=m; b=v;
    }
    }
    im.data[i]= r;
    im.data[im.w*im.h+i]=g;
    im.data[2*im.w*im.h+i]=b;
    }
}
 void scale_image(image im, int c, float v){
      for(int i=c*im.h*im.w;i<(c+1)*im.h*im.w;i++)
im.data[i]*=v;  
    }
