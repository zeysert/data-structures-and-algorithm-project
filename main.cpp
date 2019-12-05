#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<stdio.h>
#include<string.h>

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <malloc.h>

typedef unsigned int u32;
struct ogrenci_veri{
    char adi[19];
    char soyadi[19];
    int number;
    char bolum[19];
    struct ogrenci_veri *next;
};

struct ogrenci_veri* top = NULL;
struct ogrenci_veri* temp;

struct ogrenci_veri* top_kopya = NULL;
struct ogrenci_veri* temp_kopya;


char adi[19];
char soyadi[19];
int number;
char bolum[19];


struct ogrenci_veri* createPerson(char adi[19], char soyadi[19], int number, char bolum[19])
{
    struct ogrenci_veri* newogrenci = (struct ogrenci_veri*)malloc(sizeof(struct ogrenci_veri));
    strcpy(newogrenci->adi, adi);
    strcpy(newogrenci->soyadi, soyadi);
    strcpy(newogrenci->bolum, bolum);
    newogrenci->number = number;
    newogrenci->next = top;
    return newogrenci;

}



void pushNode(char adi[], char soyadi[], int number, char bolum[19])
{
    struct ogrenci_veri* newogrenci = createPerson(adi, soyadi, number,bolum);
    newogrenci->next = top;
    top = newogrenci;

}

void popNode()
{
    if(top == NULL)
    {
        printf("\n*****\n");
        printf("\n  Stack Bombos ... Eleman Cikaramazsiniz");
    }
    else
    {
        temp = top->next;
        free(top);
        top = temp;
    }
}
void printList()

{
    int i = 1;

    if(top == NULL)
    {
        printf("\n*****\n");
        printf("\n  Ogrenci Yok ...");
    }
    else
    {
            temp = top;
            printf("\n*** Veri Yapilari Ogrenci Listesi**\n");
            while(temp->next != NULL)
            {

                printf("%d-) %s %s %d %s \n", i, temp->adi, temp->soyadi, temp->number, temp->bolum);
                temp = temp->next;
                i++;
            }
             printf("%d-) %s %s %d %s \n", i, temp->adi, temp->soyadi, temp->number, temp->bolum);
    }

}

struct ogrenci_veri* peek()
{
     if(top == NULL)
    {
        printf("\n*****\n");
        printf("\n Stack Bombos ...");
        return 0;
    }
    else
    {
        return top;
    }
}

// veritabani

struct ogrenci_veritabani {
	char soyadi[50];
	char adi[50];
	char bolum[50];
	int number;
	struct ogrenci_veritabani *right;
	struct ogrenci_veritabani *left;
	int height;
};

//Asagidaki fonksiyon dugumun yuksekligini return eden yardimci fonksiyondur.
int yukseklik(struct ogrenci_veritabani* dugum)
{
	if (dugum == NULL)
		return 0;
    return dugum->height;
}

//Bu fonksiyon sart fonksiyonlardan biri olmasa da yardimci amacla kullanilmistir
// Gonderilen 2 sayidan hangisi daha buyukse onu return eder. 
int karsilastir(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}

//Dugum olusturup olusan dugumu return eden fonksiyondur.
struct ogrenci_veritabani* dugumOlustur(char soyadi[50],char adi[50],int number,char bolum[50])
{	
	struct ogrenci_veritabani* yeniOgrenci =new ogrenci_veritabani;
	
	strcpy(yeniOgrenci->soyadi, soyadi);
	strcpy(yeniOgrenci->adi, adi);
	strcpy(yeniOgrenci->bolum, bolum);
	
	yeniOgrenci->number= number;
	
	yeniOgrenci->left = NULL;
	yeniOgrenci->right = NULL;
	
	//Yeni olusturulan dugumlerin (yapraklarin) yukseklikleri 1 olur.
	yeniOgrenci->height = 1;


	return yeniOgrenci;
}

struct ogrenci_veritabani *sagaDondur(struct ogrenci_veritabani *y)
{
    //iliskili dugumleri olusturuyoruz
	struct ogrenci_veritabani *x = y->left;
	struct ogrenci_veritabani *t2 = x->right;
    
    //Saga dondurme islemi burada oluyor
    //Dondurme islemi olduktan sonra dugumler arasindaki iliskileri guncelliyoruz
	x->right = y;
	y->left = t2;

	//Dondurme islemi sonrasinda dugumlerin yuksekliklerini guncelliyoruz.
	y->height = karsilastir(yukseklik(y->left), yukseklik(y->right)) + 1;
	x->height = karsilastir(yukseklik(x->left), yukseklik(x->right)) + 1;

	//Dondurme islemi sonunda olusan yeni root dugumunu return ediyoruz.
	return x;
}

//Saga dondurme isleminde yazdimiz yorum satirlari aynen sola dondurme isleminde de gecerli
// dugumler arasi iliskileri yukaridaki (sitemizdeki) resimlerden kontrol edebilirsiniz.
struct ogrenci_veritabani *solaDondur(struct ogrenci_veritabani *x)
{
	struct ogrenci_veritabani *y = x->right;
	struct ogrenci_veritabani *t2 = y->left;

	y->left = x;
	x->right = t2;

	y->height = karsilastir(yukseklik(y->left), yukseklik(y->right)) + 1;
	x->height = karsilastir(yukseklik(x->left), yukseklik(x->right)) + 1;

	return y;
}

//Denge durumunu kontrol edip return eden fonksiyon
// Sol - Sag yuksekligi esas aldigimiza dikkat edin.
int balanceCheck(struct ogrenci_veritabani* dugum)
{
	if (dugum == NULL)
		return 0;
	else
		return yukseklik(dugum->left) - yukseklik(dugum->right);

}

//AVL Agacina dugum ekleyen ana fonksiyonumuz
struct ogrenci_veritabani* ekle(struct ogrenci_veritabani* kokDugum, char soyadi[50],char adi[50],int number,char bolum[50])
{
	
    /* BST INSERTION Baslangici */
    // Asagidaki satirlar BST uzerine eleman ekleme isleminden ibarettir. O
	if (kokDugum == NULL)
	{
		return dugumOlustur(soyadi,adi,number,bolum);
	}
	
    int siralama=0;	
	siralama = strcmp(soyadi, kokDugum->soyadi);
	
	if (siralama<0)
	{
		kokDugum->left = ekle(kokDugum->left, soyadi,adi,number,bolum);
	}
	else if (siralama>0)
	{
		kokDugum->right = ekle(kokDugum->right, soyadi,adi,number,bolum);
	}
	else
		return kokDugum;
		
	kokDugum->height = karsilastir(yukseklik(kokDugum->left), yukseklik(kokDugum->right)) + 1;
    
	int balance = balanceCheck(kokDugum);

	if( kokDugum->left->soyadi != NULL)
	{
		siralama = strcmp(soyadi, kokDugum->left->soyadi);
	
		if (balance > 1 && siralama<0)
		return sagaDondur(kokDugum);
    
	}
	
    if( kokDugum->left->soyadi != NULL)
	{
	siralama = strcmp(soyadi, kokDugum->left->soyadi);
	if (balance < -1 && siralama > 0 )
		return solaDondur(kokDugum);
	}
	
    if( kokDugum->left->soyadi != NULL)
	{
	siralama = strcmp(soyadi, kokDugum->left->soyadi);
	if (balance > 1 && siralama > 0)
	{
		kokDugum->left = solaDondur(kokDugum->left);
		return sagaDondur(kokDugum);
	}
	}
      if( kokDugum->right->soyadi != NULL)
	{
	siralama = strcmp(soyadi, kokDugum->right->soyadi);
	if (balance < -1 && siralama < 0)
	{
		kokDugum->right = sagaDondur(kokDugum->right);
		return solaDondur(kokDugum);
	}
	}
	return kokDugum;
}

// Dugum yapimizi preorder sekilde yazdiran fonksiyon. (recursive fonksiyon olduguna dikkat edin)
void preorderYazdir(struct ogrenci_veritabani* root)
{
	if (root != NULL)
	{
          
		printf("%s %s %d %s \n",root->soyadi,root->adi,root->number,root->bolum);
		
		preorderYazdir(root->left);
		preorderYazdir(root->right);
	}
}
void VeriYapilariCikar(int findnumber)
{
	if(top == NULL)
    {
        printf("\n*****\n");
        printf("\n  Ogrenci Yok ...");
    }
    else
    {
			struct ogrenci_veri* top_kopya = NULL;
			struct ogrenci_veri* temp_kopya;

            temp = top;
            bool dur=true;
            while(temp->next != NULL && dur)
            {
                
                if(findnumber==temp->number)
                {
                	dur=false;
				}
				else
				{
                	//kopyaya ekleme kodu
    				struct ogrenci_veri* newogrenci_kopya = createPerson(temp->adi, temp->soyadi, temp->number,temp->bolum);
    				newogrenci_kopya->next = top_kopya;
   					top_kopya = newogrenci_kopya;	
   					
               	 	temp = temp->next;
				}
                popNode();		
            }
            
            while(top_kopya->next != NULL)
            {
  				 pushNode(top_kopya->adi, top_kopya->soyadi, top_kopya->number,top_kopya->bolum);
            	
               	 top_kopya = top_kopya->next;	
            }
  			pushNode(top_kopya->adi, top_kopya->soyadi, top_kopya->number,top_kopya->bolum);
          
    }
    
                printList();
	
}


struct ogrenci_veritabani * minValueNode(struct ogrenci_veritabani* node)
{
    struct ogrenci_veritabani* current = node;

    /* Sol alt agacin en solundaki dugumu bulmaya calisiyoruz */
    while (current->left != NULL)
        current = current->left;

    return current;
}
int getBalance(struct ogrenci_veritabani *N)
{
    if (N == NULL)
        return 0;
    return yukseklik(N->left) - yukseklik(N->right);
}
int max(int a, int b)
{
    return (a > b)? a : b;
}
struct ogrenci_veritabani* deleteNode(struct ogrenci_veritabani* root,  char soyadi[50])
{
    // 1. Adim: Standart BST agaci eleman silme islemi

    if (root == NULL)
        return root;

    int siralama=0;	
	siralama = strcmp(soyadi, root->soyadi);
	
    if ( siralama < 0 )
        root->left = deleteNode(root->left, soyadi);

    else if( siralama > 0 )
        root->right = deleteNode(root->right, soyadi);

    // eger silinmek istenen dugum root ise buraya giriyor
    else
    {
        // Eger yalnizca bir cocugu var ya da hic cocugu yoksa
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct ogrenci_veritabani *temp = root->left ? root->left :
                                             root->right;

            // hic cocugu yoksa
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // yalnizca bir cocugu varsa
             *root = *temp; // dugumu kopyaliyoruz
            free(temp);
        }
        else
        {
            // iki cocugu varsa inorder traverse yapiyoruz
            // sag alt agactaki en kucuk dugumu buluyoruz
            struct ogrenci_veritabani* temp_yok = minValueNode(root->right);

            // sag alt agactaki en kucuk dugumu buraya kopyaliyoruz
           strcpy(root->soyadi , temp_yok->soyadi);

            // kopyaladigimiz dugumu siliyoruz
            root->right = deleteNode(root->right, temp_yok->soyadi);
        }
    }

    // Eger yalnizca bir dugum varsa
    if (root == NULL)
      return root;

    // 2. Adim: Dugumun yuksekligini guncelliyoruz
    root->height = 1 + max(yukseklik(root->left),
                           yukseklik(root->right));

    // 3. Adim: Denge durumunu kontrol ediyoruz
    int balance = getBalance(root);

    // Eger dengesizlik durumu varsa 4 durum ortaya cikiyor

    // sol sol durumu
    if (balance > 1 && getBalance(root->left) >= 0)
        return sagaDondur(root);

    // sol sag durumu
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  solaDondur(root->left);
        return sagaDondur(root);
    }

    // sag sag durumu
    if (balance < -1 && getBalance(root->right) <= 0)
        return solaDondur(root);

    // sag sol durumu
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = sagaDondur(root->right);
        return solaDondur(root);
    }

    return root;
}

char Aranan_soyadi[50]="Kus";
void getir(struct ogrenci_veritabani* root_alt)
{
	if (root_alt != NULL)
	{ 
	      int siralama=0;	
		  siralama = strcmp(Aranan_soyadi, root_alt->soyadi);
          if(siralama==0)
          {
			printf("%s %s %d %s \n",root_alt->soyadi,root_alt->adi,root_alt->number,root_alt->bolum);
		  }
		getir(root_alt->left);
		getir(root_alt->right);
			  
	}
}

void HerIkiDersAlan(struct ogrenci_veritabani* root)
{
		if(top == NULL)
    {
        printf("\n*****\n");
        printf("\n  Ogrenci Yok ...");
    }
    else
    {
			struct ogrenci_veri* top_kopya = NULL;
			struct ogrenci_veri* temp_kopya;
int i=1;
            temp = top;
            while(temp->next != NULL)
            {
                
                //kopyaya ekleme kodu
    			struct ogrenci_veri* newogrenci_kopya = createPerson(temp->adi, temp->soyadi, temp->number,temp->bolum);
    			newogrenci_kopya->next = top_kopya;
   				top_kopya = newogrenci_kopya;
				   
				strcpy(Aranan_soyadi,temp->soyadi);
				  getir(root);
   					
               	temp = temp->next;
               	 	
                popNode();		
            }
            
                //kopyaya ekleme kodu
    			struct ogrenci_veri* newogrenci_kopya = createPerson(temp->adi, temp->soyadi, temp->number,temp->bolum);
    			newogrenci_kopya->next = top_kopya;
   				top_kopya = newogrenci_kopya;
				   
				strcpy(Aranan_soyadi,temp->soyadi);
				  getir(root);
   					
               	temp = temp->next;
               	 	
                popNode();	
                
            while(top_kopya->next != NULL)
            {
  				 pushNode(top_kopya->adi, top_kopya->soyadi, top_kopya->number,top_kopya->bolum);
            	
               	 top_kopya = top_kopya->next;	
            }
  			pushNode(top_kopya->adi, top_kopya->soyadi, top_kopya->number,top_kopya->bolum);
          
    }
}
void SadeceVeriYapilari(struct ogrenci_veritabani* root_alt)
{
	if (root_alt != NULL)
	{ 
			  
		bool VeriDeVarMi=false;
		//yigin ici
		struct ogrenci_veri* top_kopya = NULL;
		struct ogrenci_veri* temp_kopya;
		int i=1;
            temp = top;
            while(temp->next != NULL)
            {
                
                //kopyaya ekleme kodu
    			struct ogrenci_veri* newogrenci_kopya = createPerson(temp->adi, temp->soyadi, temp->number,temp->bolum);
    			newogrenci_kopya->next = top_kopya;
   				top_kopya = newogrenci_kopya;
				   
			    int siralama=0;	
		 		siralama = strcmp(temp->soyadi, root_alt->soyadi);
          		if(siralama==0)
          		{
				  VeriDeVarMi=true;
				}
		  				
               	temp = temp->next;
               	 	
                popNode();		
            }
                
                //kopyaya ekleme kodu
    			struct ogrenci_veri* newogrenci_kopya = createPerson(temp->adi, temp->soyadi, temp->number,temp->bolum);
    			newogrenci_kopya->next = top_kopya;
   				top_kopya = newogrenci_kopya;
				   
			    int siralama=0;	
		 		siralama = strcmp(temp->soyadi, root_alt->soyadi);
          		if(siralama==0)
          		{
				  VeriDeVarMi=true;
				}
		  				
               	temp = temp->next;
               	 	
                popNode();	
            
                
            while(top_kopya->next != NULL)
            {
  				 pushNode(top_kopya->adi, top_kopya->soyadi, top_kopya->number,top_kopya->bolum);
            	
               	 top_kopya = top_kopya->next;	
            }
  			pushNode(top_kopya->adi, top_kopya->soyadi, top_kopya->number,top_kopya->bolum);
  			
  			//yigin son
          if(VeriDeVarMi==false)
          {
			printf("%s %s %d %s \n",root_alt->soyadi,root_alt->adi,root_alt->number,root_alt->bolum);
		  }
		  VeriDeVarMi=false;
		SadeceVeriYapilari(root_alt->left);
		SadeceVeriYapilari(root_alt->right);
	}
}
void grubu_Veri(int CiftMiTekMi)
{
		//yigin ici
		struct ogrenci_veri* top_kopya = NULL;
		struct ogrenci_veri* temp_kopya;
		int i=1;
            temp = top;
            while(temp->next != NULL)
            {
                
                //kopyaya ekleme kodu
    			struct ogrenci_veri* newogrenci_kopya = createPerson(temp->adi, temp->soyadi, temp->number,temp->bolum);
    			newogrenci_kopya->next = top_kopya;
   				top_kopya = newogrenci_kopya;
				   
				//	printf("%d %s %s %d %s \n",CiftMiTekMi,temp->number,temp->soyadi,temp->adi,temp->bolum); 
				if (CiftMiTekMi==1)
				{
          			if(temp->number%2==1)
          			{
						printf("%d %d %s %s %s \n",CiftMiTekMi,temp->number,temp->soyadi,temp->adi,temp->bolum);          			
					}
				}
				else
				{
          			if(temp->number%2==0)
          			{
						printf("%d %d %s %s %s \n",CiftMiTekMi,temp->number,temp->soyadi,temp->adi,temp->bolum);          			
					}					
				}
		  			
               	temp = temp->next;
               	 	
                popNode();		
            }
                
                //kopyaya ekleme kodu
    			struct ogrenci_veri* newogrenci_kopya = createPerson(temp->adi, temp->soyadi, temp->number,temp->bolum);
    			newogrenci_kopya->next = top_kopya;
   				top_kopya = newogrenci_kopya;
				   
		 		
          		if (CiftMiTekMi==1)
				{
          			if(temp->number%2==1)
          			{
						printf("%d %d %s %s %s \n",CiftMiTekMi,temp->number,temp->soyadi,temp->adi,temp->bolum);          			
					}
				}
				else
				{
          			if(temp->number%2==0)
          			{
						printf("%d %d %s %s %s \n",CiftMiTekMi,temp->number,temp->soyadi,temp->adi,temp->bolum);          			
					}					
				}
		  				
               	temp = temp->next;
               	 	
                popNode();	
            
                
            while(top_kopya->next != NULL)
            {
  				 pushNode(top_kopya->adi, top_kopya->soyadi, top_kopya->number,top_kopya->bolum);
            	
               	 top_kopya = top_kopya->next;	
            }
  			pushNode(top_kopya->adi, top_kopya->soyadi, top_kopya->number,top_kopya->bolum); 			
	
}

void A_grupVeriYonetimi(struct ogrenci_veritabani* root_alt)
{
	
	if (root_alt != NULL)
	{
          
   		int siralama=0;	
		siralama = strcmp( root_alt->soyadi,"L");
   	//	printf("%s %d", root_alt->soyadi,siralama);
		if(siralama<0)
		{
			printf("%s %s %d %s \n",root_alt->soyadi,root_alt->adi,root_alt->number,root_alt->bolum);			
		} 
		
		A_grupVeriYonetimi(root_alt->left);
		A_grupVeriYonetimi(root_alt->right);
	}
        
}
void B_grupVeriYonetimi(struct ogrenci_veritabani* root_alt)
{
	
	if (root_alt != NULL)
	{
          
   		int siralama=0;	
		siralama = strcmp( root_alt->soyadi,"L");
		if(siralama>0)
		{
			printf("%s %s %d %s \n",root_alt->soyadi,root_alt->adi,root_alt->number,root_alt->bolum);			
		}
		
		B_grupVeriYonetimi(root_alt->left);
		B_grupVeriYonetimi(root_alt->right);
	}
        
}

void selectionSort() 
{ 
	struct ogrenci_veri* temp_kopya;
    temp_kopya = top;
  
    // Traverse the List 
    while (temp_kopya) { 
        ogrenci_veri* min = temp_kopya; 
        ogrenci_veri* r = temp_kopya->next; 
  
        // Traverse the unsorted sublist 
        while (r) { 
        
          int siralama=0;
          siralama = strcmp(min->adi,  r->adi);
          
            if (siralama >0) 
                min = r; 
  
            r = r->next; 
        } 
  
        // Swap Data 
        char x[19] = "";
		strcpy(x, temp_kopya->adi); 
		strcpy(temp_kopya->adi, min->adi); 
		strcpy( min->adi, x); 
        temp_kopya = temp_kopya->next; 
    } 
    
    temp = top;
            printf("\n*** Veri Yapilari Ogrenci Listesi**\n");
            int i=0;
            
            while(temp->next != NULL)
            {

                printf("%d-) %s %s %d %s \n",i, temp->adi, temp->soyadi, temp->number, temp->bolum);
                temp = temp->next;
                i++;
            }
                printf("%d-) %s %s %d %s \n",i, temp->adi, temp->soyadi, temp->number, temp->bolum);
} 



struct ogrenci_veri *partition(struct ogrenci_veri *head, struct ogrenci_veri *end, 
                    struct ogrenci_veri **newHead, struct ogrenci_veri **newEnd) 
{ 
    struct ogrenci_veri *pivot = end; 
    struct ogrenci_veri *prev = NULL, *cur = head, *tail = pivot; 
  
    // During partition, both the head and end of the list might change 
    // which is updated in the newHead and newEnd variables 
    while (cur != pivot) 
    { 
        if (cur->number < pivot->number) 
        { 
            // First node that has a value less than the pivot - becomes 
            // the new head 
            if ((*newHead) == NULL) 
                (*newHead) = cur; 
  
            prev = cur;  
            cur = cur->next; 
        } 
        else // If cur node is greater than pivot 
        { 
            // Move cur node to next of tail, and change tail 
            if (prev) 
                prev->next = cur->next; 
            struct ogrenci_veri *tmp = cur->next; 
            cur->next = NULL; 
            tail->next = cur; 
            tail = cur; 
            cur = tmp; 
        } 
    } 
  
    // If the pivot data is the smallest element in the current list, 
    // pivot becomes the head 
    if ((*newHead) == NULL) 
        (*newHead) = pivot; 
  
    // Update newEnd to the current last node 
    (*newEnd) = tail; 
  
    // Return the pivot node 
    return pivot; 
} 
// Returns the last node of the list 
struct ogrenci_veri *getTail(struct ogrenci_veri *cur) 
{ 
    while (cur != NULL && cur->next != NULL) 
        cur = cur->next; 
    return cur; 
} 
  
struct ogrenci_veri *quickSortRecur(struct ogrenci_veri *head, struct ogrenci_veri *end) 
{ 
    // base condition 
    if (!head || head == end) 
        return head; 
  
    ogrenci_veri *newHead = NULL, *newEnd = NULL; 
  
    // Partition the list, newHead and newEnd will be updated 
    // by the partition function 
    struct ogrenci_veri *pivot = partition(head, end, &newHead, &newEnd); 
  
    // If pivot is the smallest element - no need to recur for 
    // the left part. 
    if (newHead != pivot) 
    { 
        // Set the node before the pivot node as NULL 
        struct ogrenci_veri *tmp = newHead; 
        while (tmp->next != pivot) 
            tmp = tmp->next; 
        tmp->next = NULL; 
  
        // Recur for the list before pivot 
        newHead = quickSortRecur(newHead, tmp); 
  
        // Change next of last node of the left half to pivot 
        tmp = getTail(newHead); 
        tmp->next = pivot; 
    } 
  
    // Recur for the list after the pivot element 
    pivot->next = quickSortRecur(pivot->next, newEnd); 
  
    return newHead; 
} 

void quickSort(struct ogrenci_veri **headRef) 
{ 
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef)); 
    return; 
} 

void Radik()
{
	}
int main()
{
	//ilk acilista
	
	struct ogrenci_veritabani* root = NULL;
   pushNode("Zeynep", "Kus", 104,"Bilgisayar Muh");
   pushNode("Cansu", "Yilmaz", 106,"Bilgisayar Muh");
   pushNode("Tolgahan", "Turkoglu", 103,"Bilgisayar Muh");
   pushNode("Irem", "Cakmak", 105,"Makine Muh");
   pushNode("Irem", "Cakmak", 107,"Makine Muh");
   pushNode("Irem", "Cakmak", 1010,"Makine Muh");
   
 	// veritabani
 
	int s;
	
	root = ekle(root,"Turkoglu", "Tolgahan",103,"Bilgisayar Muh"); 
	root = ekle(root,"Kus", "Zeynep",104,"Bilgisayar Muh"); 
	root = ekle(root,"Zuckerberg", "Mark",111,"Bilgisayar Muh"); 
				  
        printf("\n Veri Yapilari  Dersi ... ");
        printf("\n1- Veri Yapilari  Kisi Ekle icin");
        printf("\n2- Veri Yapilari  Kisi Cikar ...");
        printf("\n3- Veri Yapilari  Tepesindeki Kisiyi Goster (En son Ekleneni)...");
        printf("\n4- Veri Yapilari  Listeleme...");        
		printf("\n5- Veritabani Eklemek ...");
        printf("\n6- Veritabani Silmek ...");
        printf("\n7- Veritabani Listelemek icin ...");
        printf("\n8- Her iki derside aliyor mu ...");
        printf("\n9- Sadece Veri Listelemek ...");
        printf("\n10- A Grubu Veri Yapilari...");
        printf("\n11- B Grubu Veri Yapilari...");
        printf("\n12- A Grubu Veritabani(A-K)...");
        printf("\n13- B Grubu Veritabani(L-Z)...");
        printf("\n14- (Adi)Secmeli Siralama...");
        printf("\n15- (Soyadi)Radiks Siralama...");
        printf("\n16- (Numara) Hizli Siralama...");
        printf("\n  ... \n islem No:");
    int choise;
    struct ogrenci_veri* topElement;
    
    while(1 == 1)
    {
        
        scanf("%d", &choise);

        switch(choise)
        {
            case 1:
                printf("\n Adiniz ? ");
                scanf("%s", &adi);
                printf("\n Soyadiniz ? ");
                scanf("%s", &soyadi);
                printf("\n Numara ? ");
                scanf("%d", &number);
                printf("\n Bolum ? ");
                scanf("%s", &bolum);
                pushNode(adi, soyadi, number,bolum);
                printList();
            break;
            case 2:
                printf("\n Silinicek Numara ? ");
                scanf("%d", &number);
            	VeriYapilariCikar(number);
            break;
            case 3:
                topElement= peek();
                if(topElement)
                printf("\n Yiginin Tepesinde ==> %s %s %d", topElement->adi, topElement->soyadi, topElement->number, topElement->bolum);
                break;
            case 4:
               	 printList();
				 break;
			case 5: 
                printf("\n Adiniz ? ");
                scanf("%s", &adi);
                printf("\n Soyadiniz ? ");
                scanf("%s", &soyadi);
                printf("\n Numara ? ");
                scanf("%d", &number);
                printf("\n Bolum ? ");
                scanf("%s", &bolum);
                
				root = ekle(root, soyadi,adi, number,bolum); 
            break;
            case 6:  
               printf(" Silinicek Soyadi ?");
                scanf("%s", &soyadi);
               deleteNode(root,  soyadi);
            break;
            case 7:    
				printf("\n*** Veritabani Ogrenci Listesi**\n");
				preorderYazdir(root);
            break;
            case 8:    
				HerIkiDersAlan(root);
			break;
            case 9:
            	SadeceVeriYapilari(root);
            	break;
            case 10:
            	grubu_Veri(1);
            	break;
            case 11:
            	grubu_Veri(2);
            	break;
            case 12:
            	A_grupVeriYonetimi(root);
            	break;
            case 13:
            	B_grupVeriYonetimi(root);
            	break;
            case 14:
            	selectionSort() ;
            	break;
            case 15:
            Radik();
           		break;
            case 16:
            	quickSort(&top); 
               	 printList();
           		break;
             
        }
    }

    return 0;
}
