#include<bits/stdc++.h>
#include<windows.h>
#include<Shlobj.h>

using namespace std;

bool KMPSearch(string pat, string txt,int lps[])
{
    int M = pat.length();
    int N = txt.length();
    int j  = 0;
    int i = 0;
    while (i < N)
    {
      if (pat[j] == txt[i])
      {
        j++;
        i++;
      }
      if (j == M) return 1;

      else if (i < N && pat[j] != txt[i])
      {
        if (j != 0)
         j = lps[j-1];
        else
         i = i+1;
      }
    }
    return 0;
}

void computeLPSArray(string pat, int M, int lps[])
{
    int len = 0;
    int i;
    lps[0] = 0;
    i = 1;
    while (i < M)
    {
       if (pat[i] == pat[len])
       {
         len++;
         lps[i] = len;
         i++;
       }
       else
       {
         if (len != 0)
         {
            len = lps[len-1];
         }
         else
         {
           lps[i] = 0;
           i++;
         }
       }
    }
}


void addwordfile(char*filename)
{
    string s,p1,p2,ch;
    int i=0,j,c,k;
    ifstream in;
    ofstream out;
    in.open(filename,ios::in);
    while(getline(in,s))
    {
        i++;
        if(s.find(" n. ")!=-1) c=s.find(" n. ");
        else if(s.find(" v. ")!=-1) c=s.find(" v. ");
        else if(s.find(" adv. ")!=-1) c=s.find(" adv. ");
        else if(s.find(" adj. ")!=-1) c=s.find(" adj. ");
        else if(s.find(" Latin. ")!=-1) c=s.find(" Latin. ");
        else if(s.find(" Greek. ")!=-1) c=s.find(" Greek. ");
        //cout<<c<<" ";
        p1=s.substr(0,c);
        ch=p1;
        for(j=0;j<ch.size();j+=2)
        ch.insert(j,"/");
        p2="root"+ch;
        for(k=5;k<p2.length();k+=2)CreateDirectory(p2.substr(0,k+1).c_str(), NULL );
        p2=p2+"/"+p1+".txt";
        out.open(p2.c_str(),ios::out);
        out<<s;
        out.close();
    }
    cout<<i<<" copied";
}

int main()
{
    ifstream in;
    string ch,p1,p2,m,s;
    int i=0;
    int c;
    //addwordfile("vocab.txt");
    cout<<"Enter the word : ";
    cin>>ch;
    p1=ch;
    int lps[p1.length()];
    computeLPSArray(p1,p1.length(),lps);
    in.open("words.txt",ios::in);
    while(getline(in,s) && i<10)
    {
        if(KMPSearch(p1,s,lps)==1)
        {
            i++;
            cout<<s<<endl;
        }
    }
    in.close();
    for(i=0;i<=ch.size();i+=2)
    ch.insert(i,"/");
    p2="root"+ch+p1+".txt";
    in.open(p2.c_str(),ios::in);
    getline(in,m);
    cout<<m;
}
