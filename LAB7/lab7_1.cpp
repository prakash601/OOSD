#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int Priority ( int a[] , int b[] )
{
    int i = 0 ;
    int flag1 = 0 , flag2 = 0 ;

    for ( i=0 ; i<26 ; i++ )
    {
        flag1 = 0;
        flag2 = 0 ;
        if ( a[i] == 1 and b[i] == 0 )
        {
            return 1 ; 
        }
        if ( a[i] == 0 and b[i] == 1 )
        {
            return 2 ; 
        }

        if ( a[i] == 1 and b[i] == 1 )
        {
            int k = i ;
            int j ;
            for ( j=i+1 ; j<26 ; j++ )
            {
                if ( a[j] == 1 )
                {
                    flag1 = 1 ;
                }
            }
            if ( flag1 == 0 )
            {
                return 1 ;
            }
            for ( j=k+1 ; j<26 ; j++ )
            {
                if ( b[j] == 1 )
                {
                    flag2 = 1 ;
                }
            }
            if ( flag2 == 0 )
            {
                return 2 ;
            }

        }

    }

    return 0 ;
}

string lex ( string s , string s1 )
{
    int n,i=0,j=0,k = 0,l;
    char ch ;
    int a[26] ;

    n = s.length() ;
    for ( j=0 ; j<26 ; j++ )
    {
        a[j] = 0 ;
    }

    while ( i<n )
    {
      //  cout << s[i] << endl ;
        if ( s[i] <= 'z' and s[i] >= 'a' )
        {
            if ( s[i+1] != '^' )
            {
                a[ s[i] - 'a' ] += 1 ;
                i++ ;
               // cout << "Reached1 " << endl ;

            }else{
               // cout << "Reached " << endl ;
                l = s[i] - 'a' ; 
               // cout << l << endl ;
                i = i+3 ;
                k = 0;
                while ( s[i] != ')') 
                {
                  //  cout << s[i] << endl ;
                    k = k*10 + (s[i]-'0') ;
                  //  cout << k << endl ;
                    i++ ; 
                }
               // cout << k ;
                a[l] += k;
                
                i++ ;
            }    
        }

        if ( s[i] == '(' )
        {
            int it = i ;
            i++ ;
            while ( s[it] != ')' )
            {
                it++ ;
            }
            it = it+3 ;
            k = 0 ;
            while ( s[it] != ')') 
            {
                  //  cout << s[i] << endl ;
                k = k*10 + (s[it]-'0') ;
                  //  cout << k << endl ;
                it++ ; 
            }
            it++ ;

            while ( s[i] != ')' )
            {
                a[s[i]-'a'] += k ;
                i++ ;
            }

            i = it ;
        }
    }

    for ( j=0 ; j<26 ; j++ )
    {
        if ( a[j] == 0 )
        {
            continue ;
        }else if ( a[j] == 1 )
        {
            ch = 'a'+j;
            s1 += ch ;
            //cout << ch ;
        }else {
            ch = 'a'+j;
            s1 += ch ;
            s1 += "^(" ;
            s1 += to_string(a[j]) ;
            s1 += ")" ;
            //cout << ch << "^(" << a[j] << ")" ;
        }
    }

    return s1 ;
}

string l_sort( string s , string a )
{
    int j;

    for ( j=0 ; j<s.length() ; j++ )
    {
        if ( s[j] == ' ' or s[j] == '+' or s[j] == '-' or ( s[j] <= '9' and s[j] >= '0') )
        {
            a += s[j] ;
            continue ; 
        }
         
        string r = "" ;
        while( true )
        {
            r += s[j] ;
            j++ ;

            if ( j>=s.length() or s[j] == ' ' or s[j] == '+' or s[j] == '-' )
            {
                if ( s[j] == '+' or s[j] == '-' )
                {
                    j-- ;
                }
                break ;
            }
        }

        string z = "" ;

        //cout << r << endl ;

        r = lex( r,z ) ;
        //cout << r << endl ;
        a += r ; 

        //cout << a << endl ;
       // cout << k << endl ;

    }
   // cout << a << endl ;
    return a ;

}

string S1( string s , int *x )
{
    string t[100] ;
    int i,k,k1[100],nt = 0,j = 0 ;
    int n = s.length() ;
    int a[100][26] ;

    for ( j=0 ; j<99 ; j++ )
    {
        t[j] = "" ;
        k1[j] = 0 ;
    }
    if ( s[0] == '-' )
    {
        t[0] += "-" ;
    }else{
        t[0] += "+" ;
    }

    for ( j=0 ; j<n ; j++ )
    {
        if ( s[j] == '-' and j == 0 )
        {
            continue ;
        }
        if ( s[j] == ' ' )
        {
            continue ;
        }

        if ( s[j] == '+' or s[j] == '-'  )
        {
            nt++ ;
            t[nt] = t[nt]+s[j] ;
            continue ;
        }
        t[nt] = t[nt]+s[j] ;
    }
    /*

    for ( j=0 ; j<=nt ; j++ )
    {
        cout << t[j] << endl ; 
    }
    */

    for ( j = 0 ; j<=nt ; j++ )
    {
        char ch1 = 'a' ;
        while ( ch1 <= 'z' )
        {
            k = 0 ;
            while( k < t[j].length() )
            {
                if( t[j][k] == ch1 )
                {
                    a[j][ch1-'a'] =  1 ;
                    k++ ;
                    break ;
                } 
                k++ ;
            }
            ch1 = ch1 + 1 ;
        }

    }
    /*
    for ( j=0 ; j<=nt ; j++ )
    {
        for ( k=0 ; k<26 ; k++ )
        {
            cout << a[j][k] << "  " ;

        }
        cout << endl ;
    }
    */

   // cout << endl ;
    int b[nt+1] ,c[nt+1] ;
    int order[nt+1] ;
    int l=0 ,l1 = 0 , o = 0,p,p1;  
    
    p = Priority( a[0], a[1] ) ;
    if ( p==1 )
    {
        order[0] = 0 ;
        order[1] = 1 ;
    }
    if ( p==2 )
    {
        order[0] = 1 ;
        order[1] = 0 ;
    }
  //  cout << order[0] << "  " << order[1] << endl ;
    for ( j=2 ; j<=nt ; j++ )
    {
        for ( l=0 ; l<j ; l++ )
        {
            p = Priority( a[order[l]] , a[j] ) ;
           // cout << p << endl ;
            if ( p == 2 )
            {
                for ( l1=j ; l1>l ; l1-- )
                {
                    order[l1] = order[l1-1] ;
                }
                order[l] = j  ;
                break ;
            }

        }
        if ( l==j )
        {
            order[l] = j ;
        }
        /*
        for ( i=0 ; i<=j ; i++ )
        {
            cout << order[i] << "  " ; 
        }    
        cout << endl ;
        */
    }
    
    s = "" ;
    for ( j=0 ; j<=nt ; j++ )
    {
        if ( j==0 )
        {
            if ( t[order[j]][0] == '+' )
            {
                for ( i=1 ; i<t[order[j]].length() ; i++ )
                {
                   // cout << t[order[j]][i] ;
                   s += t[order[j]][i] ; 
                }
            }else{
               // cout << t[order[j]] ;
               s += t[order[j]] ;
            }

        }else{
            //cout << t[order[j]] ;
            s += t[order[j]] ;
        }
        
    }   
    //cout << endl ;
    
    for ( j=0 ; j<=nt ; j++ )
    {
        x[j] = order[j] ; 
    }
    return s ;
    
}

string M( string x , string y , string ans )
{
    string z = "" ;
    x = l_sort( x,z ) ;
    z = "" ;
    y = l_sort( y,z ) ;
    //cout << x << endl << y << endl ;

    int a,b,c[26] ;

    int j = 0 ;

    for ( j=0 ; j<26 ; j++ )
    {
        c[j] = 0 ;
    }

    j = 0 ; 
    if ( x[j] == '-' )
    {
        j++ ;
    }
    int sum = 0 ;
    if ( x[j] >= 'a' and x[j] <= 'z' )
    {
        sum = 1 ;      
    }
    while( x[j] <= '9' and x[j] >= '0' )
    {
        sum = sum*10 + (x[j] - '0' );
        j++ ;
    }
    a = sum ;
    if( x[0] == '-' )
    {
        a = (-1)*a ;
    }

    //cout << x[j] <<endl ;

    while( j<x.length() )
    {
        if ( x[j] <= 'z' and x[j] >= 'a' )
        {    
            if ( x[j+1] != '^' )
            {
                c[x[j] - 'a'] += 1 ;
                j++ ;
            }else{
                int sum1 = 0 ;
                int a1 = j ;
                j = j+3 ;
                while( x[j] != ')' )
                {
                    sum1 = sum1*10 + (x[j]-'0') ;
                    j++ ;
                }
                c[x[a1] - 'a'] += sum1 ;
                j++ ;

            }
        }
    }
    /*
    for (j=0 ; j<26 ; j++ )
    {
        cout << c[j] << "  ";
    }
    cout << endl ;
    */
    j = 0 ;
    if ( y[j] == '-' )
    {
        j++ ;
    }
    sum = 0 ;
    if ( y[j] >= 'a' and y[j] <= 'z' )
    {
        sum = 1 ;      
    }
    while( y[j] <= '9' and y[j] >= '0' )
    {
        sum = sum*10 + (y[j] - '0' );
        j++ ;
    }
    b = sum ;
    if( y[0] == '-' )
    {
        b = (-1)*b ;
    }

    while( j<y.length() )
    {
        if ( y[j] <= 'z' and y[j] >= 'a' )
        {    
            if ( y[j+1] != '^' )
            {
                c[y[j] - 'a'] += 1 ;
                j++ ;
            }else{
                int sum1 = 0 ;
                int a1 = j ;
                j = j+3 ;
                while( y[j] != ')' )
                {
                    sum1 = sum1*10 + (y[j]-'0') ;
                    j++ ;
                }
                c[y[a1] - 'a'] += sum1 ;
                j++ ;

            }
        }
        
    }
    /*
    for (j=0 ; j<26 ; j++ )
    {
        cout << c[j] << "  ";
    }
    cout << endl ;
    
    cout << a << endl << b << endl ;
    */
    a  = a*b ;
    
    if ( a==1 )
    {

    }else if( a==-1 ){
        ans += "-" ;
    }else{
        ans += to_string(a) ;
    }
    
    for( j=0 ; j<26 ; j++ )
    {
        if ( c[j] == 0 )
        {
            continue ;
        }else if ( c[j] == 1 )
        {
            ans += 'a'+j ;
        }else{
            ans += 'a'+ j ;
            ans += "^(" ;
            ans += to_string(c[j]) ;
            ans += ")" ;
        }
    }


    return ans ;
}

string SMProduct ( string x , string y )
{
    int i = 0 ;
    string z = "" ,z1 = "" , ans = "" ;

    for ( i=0 ; i<y.length() ; i++ ) 
    {
        z = "" ;
        z1 = "" ;
        if ( y[i] == '-' )
        {
            z1 += y[i] ;
            i++ ;
        }
        if ( y[i] == '+' )
        {
            i++ ;
        }
        
        while ( y[i] != '+' and y[i] != '-' and i<y.length() )
        {
            z1 += y[i] ;
            i++ ;
        }
        if ( (y[i] != '+' or y[i] != '-' ) and i<y.length() )
        {
            i-- ;
        }
        z1 = M( x,z1,z );
        if ( z1[0] == '-' )
        {
            ans += z1 ;
        }else{
            if ( ans.empty() == 1 )
            {
                ans += z1 ;
            }else{
                ans += "+" ;
                ans += z1 ;
            }
            
        }     
    }

    y = ans ;
    return y ;
}

string A( string s1 )
{
    string s = "" , p = "" ;

    int i = 0 ;
    if ( s1[0] == '(' )
    {
        i = 1 ;
        while( s1[i] != ')' )
        {
            p += s1[i] ;
            i++ ;
        }

        i++ ;
        while ( i <= s1.length()-1 )
        {
            s += s1[i] ;
            i++ ;
        }
    }else{
        while( s1[i] != '(' )
        {
            s += s1[i] ;
            i++ ;
        } 

        i = i + 1 ;
        while ( i < s1.length()-1 )
        {
            p += s1[i] ;
            i++ ;
        }

    }

    //cout << s << endl ;
    //cout << p << endl ;

    string z = "" ;
    s = l_sort(s,z) ;
    z = "" ;
    p = l_sort(p,z) ;

    int ab[100] ;
    p = S1( p , ab ); 

    //cout << s << endl ;
    //cout << p << endl ;
    p = SMProduct( s , p ) ;
    //cout << p << endl ;
    
    s1 = S1( p , ab );
    return s1 ;
}

int main()
{
    fstream file ;
    string s1 = "" ;  
    char ch ;
    file.open("input.txt");
    file.get(ch) ;
    while ( ch!= '\n' )
    {
        s1 = s1 + ch ; 
        file.get(ch) ;
    }

    file.close();
    
    cout << s1 << endl ;
    
    s1 = A( s1 ) ;
    
    cout << s1 << endl ;
    return 0 ;
}