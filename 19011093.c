#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#define SIZE 30

//YILDIZ TEKNÝK ÜNÝVERSÝTESÝ
//Fatih ECEVÝT-19011093

typedef struct ogr{
	int no;
	char ad[SIZE];
	char soyad[SIZE];
	char ode[SIZE][SIZE];
	int sctd_sayisi;
	int sctd_kredisi;
	int d_sctd_sayisi;
	struct ogr *next;
	struct ogr *prev;
}ogrenci;

typedef struct derss{
	char ders_kodu[SIZE];
	char ders_adi[SIZE];
	int kredi;
	int kontenjan;
	int *doe;
	int ogrenci_sayisi;
	int d_ogrenci_sayisi;
	int kalan_kontenjan;
	struct derss *nextt;
}ders;

typedef struct kayitt{
	char ders_kodu[SIZE];
	int no;
	int id;
	char tarih[SIZE];
	char durum[SIZE];
	struct kayitt *next3;
}kayit;

void ayir_ogr(ogrenci* a,char b[255],char sinir[2]){
	char *token;
	token=strtok(b,sinir);
	a->no=atoi(token);
	token=strtok(NULL,sinir);
	strcpy(a->ad,token);
	token=strtok(NULL,sinir);
	strcpy(a->soyad,token);
	token[strlen(token)-1]='\0';
	token=strtok(NULL,sinir);
	a->sctd_sayisi=atoi(token);
	token=strtok(NULL,sinir);
	a->sctd_kredisi=atoi(token);
	token[strlen(token)-1]='\0';
}
ogrenci* ogr_Read(char Dosya_adi[20],char sinir[2]){
	FILE *fp=fopen(Dosya_adi,"r");
	if(fp==NULL){
		printf("OGRENCI DOSYANIZ SU ANDA BOSTUR \n");
		return NULL;
	}
	char b[255];
	ogrenci* head=(ogrenci*)malloc(sizeof(ogrenci));
	ogrenci* curr_data;
	ogrenci* prev_data;
	if(fgets(b,255,fp)!=NULL){
		ayir_ogr(head,b,sinir);		
	}
	prev_data=head;
	while(fgets(b,255,fp)!=NULL){
		curr_data=(ogrenci*)malloc(sizeof(ogrenci));
		prev_data->next=curr_data;
		ayir_ogr(curr_data,b,sinir);
		prev_data=curr_data;
	}
	prev_data->next=NULL;
	fclose(fp);
	return head;
}
void ayir_ders(ders* a,char b[255],char sinir[2]){
	char *token;
	token=strtok(b,sinir);
	strcpy(a->ders_kodu,token);
	token=strtok(NULL,sinir);
	strcpy(a->ders_adi,token);
	token=strtok(NULL,sinir);
	a->kredi=atoi(token);
	token=strtok(NULL,sinir);
	a->kontenjan=atoi(token);
	token=strtok(NULL,sinir);
	a->kalan_kontenjan=atoi(token);
	token=strtok(NULL,sinir);
	a->ogrenci_sayisi=atoi(token);
	token[strlen(token)-1]='\0';
}
ders* ders_Read(char Dosya_adi[20],char sinir[2]){
	FILE *fp=fopen(Dosya_adi,"r");
	char b[255];
	if(fp==NULL){
		printf(" DERS DOSYANIZ SU ANDA BOSTUR \n");
		return NULL;
	}
	ders* head=(ders*)malloc(sizeof(ders));
	ders* curr_data;
	ders* prev_data;
	if(fgets(b,255,fp)!=NULL){
		ayir_ders(head,b,sinir);		
	}
	prev_data=head;
	while(fgets(b,255,fp)!=NULL){
		curr_data=(ders*)malloc(sizeof(ders));
		prev_data->nextt=curr_data;
		ayir_ders(curr_data,b,sinir);
		prev_data=curr_data;
	}
	prev_data->nextt=NULL;
	fclose(fp);
	return head;
}
ogrenci * ogrenci_bul(ogrenci * head, int n){
		while(head!=NULL && head->no!=n){
			head=head->next;
		}
		return head;
}
ders * ders_bul(ders * head2, char n[SIZE]){
	while(head2!=NULL && strcmp(head2->ders_kodu,n)){
		head2=head2->nextt;
	}
	return head2;
}
kayit* kayit_Read(kayit* head2,int * id){
	FILE *fp=fopen("durum.txt","r");
	kayit * ilk,*iki,*head;
	char ders_kodu[30],tarih[30],durum[30];
	if(fp==NULL){
		printf(" DERS DOSYANIZ SU ANDA BOSTUR \n");
		return NULL;
	}
	ilk=(kayit*)malloc(sizeof(kayit));
	fscanf(fp,"%d %s %d %s %s\n",&ilk->id,ders_kodu,&ilk->no,tarih,durum);
	strcpy(ilk->ders_kodu,ders_kodu);
	strcpy(ilk->tarih,tarih);
	strcpy(ilk->durum,durum);
	head=ilk;
	iki=head;
	ilk=NULL;
	ilk=(kayit*)malloc(sizeof(kayit));
	(*id)++;
	while(fscanf(fp,"%d %s %d %s %s\n",&ilk->id,ders_kodu,&ilk->no,tarih,durum)==5){
		strcpy(ilk->ders_kodu,ders_kodu);
		strcpy(ilk->tarih,tarih);
		strcpy(ilk->durum,durum);
		iki->next3=ilk;
		iki=iki->next3;
		ilk=NULL;
		ilk=(kayit*)malloc(sizeof(kayit));
		(*id)++;
	}
	fclose(fp);
	
	return head;
}
void ogrenci_yaz(ogrenci * p){
	FILE * data;
	data=fopen("ogrenci.txt","w");
	while(p!=NULL){
		fprintf(data,"%d,%s,%s,%d,%d\n",p->no,p->ad,p->soyad,p->sctd_sayisi,p->sctd_kredisi);
		p=p->next;
	}
	fclose(data);
}
void ders_yaz(ders * p){
	FILE * data;
	data=fopen("ders.txt","w");
	while(p!=NULL){
		fprintf(data,"%s,%s,%d,%d,%d,%d\n",p->ders_kodu,p->ders_adi,p->kredi,p->kontenjan,p->kalan_kontenjan,p->ogrenci_sayisi);
		p=p->nextt;
	}
	fclose(data);
}
void durum_yaz(kayit * m){
	FILE * data;
	data=fopen("durum.txt","w");
	while(m!=NULL){
		fprintf(data,"%d %s %d %s %s\n",m->id,m->ders_kodu,m->no,m->tarih,m->durum);
		m=m->next3;
	}
	fclose(data);
}
void program_yaz(ogrenci * p){
	FILE * data;
	int i;
	data=fopen("dersprogram.txt","w");
	while(p!=NULL){
		fprintf(data,"%d :",p->no);
		for(i=0;i<p->sctd_sayisi-1;i++){
			fprintf(data,"%s ",p->ode[i]);
		}
			fprintf(data,"%s \n",p->ode[i]);
		p=p->next;
	}
	fclose(data);
}
int ogrenci_ekle(ogrenci **head, ogrenci **tail,int derss, int kredi){
	system("cls");
	ogrenci *k=*head;
	ogrenci *tmp;
	ogrenci *ogr= (ogrenci*)malloc(sizeof(ogrenci));
	printf(" Ögrenci Numarasý : ");  scanf("%d",&ogr->no);
	while(k!=NULL && k->no!=ogr->no){
		k=k->next;
	}
	if( k != NULL){
	printf("%d Numaralý Öðrenci Önceden Eklenmiþ \n", ogr->no);
	free(ogr);
	return 1;
	}
	getchar();
	printf(" Öðrenci ad : ");  gets(ogr->ad);
	printf(" Öðrenci soyad : ");  gets(ogr->soyad);
	ogr->sctd_kredisi=0;
	ogr->sctd_sayisi=0;
	tmp=(*head);
	if((*head)==NULL){
			ogr->next=NULL;
			ogr->prev=NULL;
			(*head)=ogr;
			(*tail)=ogr;
			printf("Liste Oluþturuldu Ýlk Öðrenci Kayýt Edildi \n");
	}
	else if((*head)->no > ogr->no){
		ogr->next=tmp;
		tmp->prev=ogr;
		ogr->prev=NULL;
		*head=ogr;
		printf("Öðrenci Kayýt Edildi \n");
	}	
	else{
		tmp=(*head);
		while(tmp->next!=NULL && tmp->next->no < ogr->no){
			tmp=tmp->next;
		}
		if(tmp->next==NULL){
			(*tail)=ogr;
		}
		else{
			tmp->next->prev=ogr;
		}
		ogr->next=tmp->next;
		ogr->prev=tmp;
		tmp->next=ogr;
		printf("Öðrenci Kayýt Edildi \n ");
	}
	return 1;
}

ogrenci *ogrenci_sil(ogrenci *head,ders *head2,kayit *head3){
	system("cls");
	bool sonuc=false;
	ders *f= head2;
	kayit *m=head3;
	int i,j,a,y=0,z=0;
	ogrenci *tmp,*cur;
	if(head == NULL){
		printf("Silinecek Herhangi Bir Öðrenci Yok \n");
		return head;
	}
	int ogrno;
	printf("Silinecek Öðrencinin Numarasýsýn hiriniz : "); scanf("%d",&ogrno);
	
	if(head->no==ogrno && head->next==NULL ){
		if(head->sctd_sayisi != 0){
			for(i=0;i< head->sctd_sayisi;i++){
			y=0;
			z=0;
			while(f!=NULL && strcmp( f->ders_kodu,head->ode[i]) !=0){
			f=f->nextt;
			}
			while(y<f->ogrenci_sayisi && f->doe[y]!=ogrno){
			y++;
			}
			for(z=y ;z < f->ogrenci_sayisi-1;z++){
			f->doe[z]=f->doe[z+1];
			}
			f->kalan_kontenjan++;
			f->ogrenci_sayisi--;
		}
	}
			free(head);
			head=NULL;
			while(m!=NULL){
				if(m->no==ogrno){
					strcpy(m->durum,"ogrenci_silindi");
				}
				m=m->next3;
			}
			printf("Listede Kalan Son Öðrenci Silindi \n");
			sonuc=true;
		}
		else if(head->no==ogrno && head->next!=NULL ){
			
			if(head->sctd_sayisi != 0){
			for(i=0;i< head->sctd_sayisi;i++){
			y=0;
			z=0;
			while(f!=NULL &&strcmp( f->ders_kodu,head->ode[i]) !=0){
			f=f->nextt;
			}
			while(y<f->ogrenci_sayisi && f->doe[y]!=ogrno){
			y++;
			}
			for(z=y ;z < f->ogrenci_sayisi-1;z++){
			f->doe[z]=f->doe[z+1];
			}
			f->kalan_kontenjan++;
			f->ogrenci_sayisi--;
		}
	}		ogrenci *p=head->next;
			free(head);
			head=p;
				while(m!=NULL){
				if(m->no==ogrno){
					strcpy(m->durum,"ogrenci_silindi");
				}
				m=m->next3;
			}
			printf("%d Numaralý Öðrenci Silindi \n",ogrno);
			sonuc=true;
		}
		
		else{
		cur=head;
		while(cur->next!=NULL && cur->next->no!=ogrno){
			cur = cur->next;
		}
		if(cur->next!=NULL){
			
			if(cur->next->sctd_sayisi != 0){
			for(i=0;i< cur->next->sctd_sayisi;i++){
			y=0;
			z=0;
			while(f!=NULL && strcmp(f->ders_kodu,cur->next->ode[i])!=0){
			f=f->nextt;
			}
			while(y<f->ogrenci_sayisi && f->doe[y]!=ogrno){
			y++;
			}
			for(z=y;z < f->ogrenci_sayisi-1;z++){
			f->doe[z]=f->doe[z+1];
			}
			f->kalan_kontenjan++;
			f->ogrenci_sayisi--;
		}
	}
			tmp = cur->next;
			cur->next=cur->next->next;
			free(tmp);
			while(m!=NULL){
				if((m->no==ogrno)){
					strcpy(m->durum,"ogrenci_silindi");
				}
				m=m->next3;
			}
			printf("%d Numarali Öðrenci Silindi  \n",ogrno);
			sonuc=true;
		}
}
	if(!sonuc){
	printf("%d Numaralý Öðrenci Listede Yok \n",ogrno);
	}
return head;
}

ogrenci *ogrencileri_yazdir(ogrenci *head,ogrenci *tail){
	system("cls");
	int i;
	if(head==NULL){
		printf(" ÖÐRENCÝ LÝSTESÝ BOÞ \n ");
	}
else{
	ogrenci *p= head;
		while(p != NULL){
			printf("*********************\n");
			printf("NO : %d , AD-SOYAD: %s %s,SEÇTÝÐÝ DERS SAYISI/KREDÝSÝ: %d-%d \n ",p->no,p->ad,p->soyad,p->sctd_sayisi,p->sctd_kredisi);
			if(p->sctd_sayisi !=0){
			printf("ÖÐRENCÝNÝN SEÇTÝÐÝ DERSLERÝN KODLARI : ");
			for(i=0;i<p->sctd_sayisi;i++){
			printf(" %s \t ",p->ode[i]);
		}
			printf("\n");
	}
			p=p->next;
		}
	}
	return head;
}
ders *ders_ekle(ders *head2){
	system("cls");
	ders *l=head2;
	ders *tmp;
	ders *drs= (ders*)malloc(sizeof(ders));
	printf("Ders Kodu : ");  scanf("%s",&drs->ders_kodu);
	while(l!=NULL && strcmp(l->ders_kodu,drs->ders_kodu)!=0){
		l=l->nextt;
	}
	if( l != NULL){
	printf("%s Kodlu Ders Önceden Eklenmiþ \n", drs->ders_kodu);
	free(drs);
	return head2;
	}
	getchar();
	printf("Ders Adi : ");  gets(drs->ders_adi);
	printf("Ders Kredisi : ");  scanf("%d",&drs->kredi);
	printf("Ders Kontenjaný : ");  scanf("%d",&drs->kontenjan);
	if(drs->kontenjan==0){
		printf("Kontenjaný 0 Olan Bir Ders Açýlamaz \n");
		return head2;
	}
	drs->kalan_kontenjan=drs->kontenjan;
	drs->ogrenci_sayisi=0;
	if( head2 == NULL || strcmp(head2->ders_kodu,drs->ders_kodu)>=0){
		drs->nextt=head2;
		head2=drs;
		if(head2->nextt==NULL){
			printf("Liste Oluþturuldu Ýlk Ders Kayýt Edildi \n");
		}else{
			printf("Ders Kayýt Edildi \n");
		}
		
	}else{
		tmp=head2;
		while(tmp->nextt!=NULL && strcmp(tmp->nextt->ders_kodu,drs->ders_kodu)<0 ){
			tmp=tmp->nextt;
		}
		drs->nextt=tmp->nextt;
		tmp->nextt=drs;
		printf(" Ders Kayýt Edildi \n ");
	}
	
	return head2;
}
ders *ders_sil(ders *head,ogrenci *head2,kayit *head3){
	system("cls");
	int i,j,a,y=0,z=0;
	bool sonuc=false;
	ders *tmp,*cur2;
	ogrenci *f= head2;
	kayit *m=head3;
	if(head == NULL){
		printf("Silinecek Herhangi Bir Ders Yok \n");
		return head;
	}
	char derskod[SIZE];
	printf("Silinecek Dersin Kodunu Giriniz : "); scanf("%s",derskod);
	if(strcmp(head->ders_kodu,derskod)==0 && head->nextt==NULL ){
		if(head->ogrenci_sayisi !=0){
			for(i=0;i< head->ogrenci_sayisi;i++){
			y=0;
			z=0;
			while(f!=NULL && f->no!=head->doe[i]){
			f=f->next;
			}
			while(y<f->sctd_sayisi && strcmp(f->ode[y],derskod)!=0){
			y++;
			}
			for(z=y ;z < f->sctd_sayisi-1;z++){
			strcpy(f->ode[z],f->ode[z+1]);
			}
			f->sctd_sayisi--;
			f->sctd_kredisi=f->sctd_kredisi-head->kredi;
		}
			}
			while(m!=NULL){
				if(strcmp(m->ders_kodu,derskod)==0){
					strcpy(m->durum,"kapandi");
				}
				m=m->next3;
			}
			free(head);
			head=NULL;
			printf("Listede Kalan Son Ders Silindi \n");
			sonuc=true;
		}
		else if(strcmp(head->ders_kodu,derskod)==0 && head->nextt!=NULL ){
			if(head->ogrenci_sayisi !=0){
			for(i=0;i< head->ogrenci_sayisi;i++){
			y=0;
			z=0;
			while(f!=NULL && f->no!=head->doe[i]){
			f=f->next;
			}
			while(y<f->sctd_sayisi && strcmp(f->ode[y],derskod)!=0){
			y++;
			}
			for(z=y ;z < f->sctd_sayisi-1;z++){
			strcpy(f->ode[z],f->ode[z+1]);
			}
			f->sctd_sayisi--;
			f->sctd_kredisi=f->sctd_kredisi-head->kredi;
		}
			}
			ders *p=head->nextt;
		while(m!=NULL){
				if(strcmp(m->ders_kodu,derskod)==0){
					strcpy(m->durum,"kapandi");
				}
				m=m->next3;
			}
			free(head);
			head=p;
			printf("%s Numaralý Ders Silindi \n",derskod);
			sonuc=true;
		}
		else{
		cur2=head;
		while(cur2->nextt!=NULL && strcmp(cur2->nextt->ders_kodu,derskod)!=0 ){
			cur2 = cur2->nextt;
		}
		if(cur2->nextt!=NULL){
			if(head->nextt->ogrenci_sayisi !=0){
			for(i=0;i< head->nextt->ogrenci_sayisi;i++){
			y=0;
			z=0;
			while(f!=NULL && f->no!=head->nextt->doe[i]){
			f=f->next;
			}
			while(y<f->sctd_sayisi &&strcmp(f->ode[y],derskod) !=0 ){
			y++;
			}
			for(z=y ;z < f->sctd_sayisi-1;z++){

			strcpy(f->ode[z],f->ode[z+1]);
			}
			f->sctd_sayisi--;
			f->sctd_kredisi=f->sctd_kredisi-head->nextt->kredi;
		}
			}
			tmp = cur2->nextt;
			cur2->nextt=cur2->nextt->nextt;
			free(tmp);
		while(m!=NULL){
				if(strcmp(m->ders_kodu,derskod)==0){
					strcpy(m->durum,"kapandi");
				}
				m=m->next3;
			}
			printf("%s Numaralý Ders Silindi \n",derskod);
			sonuc=true;
		}
		if(!sonuc){
		printf("%s NumaralI Ders Listede Yok \n",derskod);
	}
}
return head;
}

int derse_ogr_ekle(ogrenci **head2,ders **head3,kayit **head4,int *id,int kredi,int ders_sayisi){
	system("cls");
	int a,i,j;
	char b[SIZE];
	char tarih[30];
	int tmp;
	char tmp3[SIZE];
	ogrenci *k=*head2;
	ders *p=*head3;
	kayit *tmp2;
	kayit *kyt= (kayit*)malloc(sizeof(kayit));
	printf("Lütfen Ders Seçecek Ögrencinin Numarasýný Giriniz : "); scanf("%d",&a);
	while(k!=NULL && k->no!=a){
		k=k->next;
	}
	if( k == NULL){
	printf("%d Numaralý Öðrenci Bulunamadi \n", a);
	return 1;
	}
	printf("Lutfen Ders Kodunu Giriniz : "); scanf("%s",b);
	while(p!=NULL &&strcmp(p->ders_kodu,b)!=0){
		p=p->nextt;
	}
	if( p == NULL){
		printf(" %s Kodlu Ders Bulunamadi \n", b);
		return 1;
	}
	if(k->sctd_sayisi !=0 ){
		for(i=0;i<k->sctd_sayisi;i++){
		if(strcmp(k->ode[i],b)==0){
			printf("%d Numaralý Öðrenci Bu Dersi Önceden Seçmiþtir \n",k->no);
			return 1;
		}
	}
	}
	if(k->sctd_kredisi+p->kredi > kredi){
		printf("Kredisi Yetmediði Ýçin Öðrenci Bu dersi Seçemez ! \n");
		return 1;
	}
	if(k->sctd_sayisi+1 > ders_sayisi){
		printf("Alabileceði Maximum Ders Sayýnýný Aþtýðý Ýçin Öðrenci Bu Dersi Seçemez ! \n");
		return 1;
	}
	if(p->kalan_kontenjan-1 <0){
		printf("Sýnýf Kontenjaný Dolduðu Ýçin Öðrenci Bu Dersi Seçemez ! \n");
		return 1;
	}
	if(p->ogrenci_sayisi==0){
	 	if(k->sctd_sayisi==0){
			k->sctd_sayisi=1;
		}else{
			k->sctd_sayisi++;
		}
		p->doe=(int*)malloc(sizeof(int));
	 	p->ogrenci_sayisi=1;
	 	k->sctd_kredisi=k->sctd_kredisi+p->kredi;
	 	p->kalan_kontenjan--;
	 	p->doe[p->ogrenci_sayisi-1]=a;
	 	strcpy(k->ode[k->sctd_sayisi-1],b);
	 	strcpy(kyt->ders_kodu,b);
		kyt->no=a;
		*id=*id+1;
		kyt->id=*id;
		printf("Lütfen Ýþlemi Yaptýðýnýz Tarihi Boþluk Býrakmadan Yazýnýz \n");
		scanf("%s",tarih);
		strcpy(kyt->tarih,tarih);
		strcpy(kyt->durum,"kayitli");
		kyt->next3=NULL;
		if(*head4==NULL){
			*head4=kyt;
		 }else{
		tmp2=*head4;
			while(tmp2->next3 != NULL){
				tmp2=tmp2->next3;
			}
		 tmp2->next3=kyt;
		 }
	 	if(k->sctd_sayisi==2){
 			if(strcmp(k->ode[0],k->ode[1])>0){
 				strcpy(tmp3,k->ode[0]);
 				strcpy(k->ode[0],k->ode[1]);
 				strcpy(k->ode[1],tmp3);
			 }
		 }
		 if(k->sctd_sayisi>2){
		 	for(i=0; i< k->sctd_sayisi-1;i++){
			for(j=i+1; j< k->sctd_sayisi; j++){
				if(strcmp(k->ode[i] , k->ode[j])>0){
					strcpy(tmp3,k->ode[i]);
               		strcpy(k->ode[i],k->ode[j]);
					strcpy(k->ode[j],tmp3);
			}
		}
	}
		 }
	 	printf("Öðrenci Derse Baþarýlý Bir Þekilde Eklenmiþtir \n");
 	
	}else{
		p->ogrenci_sayisi++;
		if(k->sctd_sayisi==0){
			k->sctd_sayisi=1;
		}else{
			k->sctd_sayisi++;
		}
		p->doe=(int*)realloc(p->doe,p->ogrenci_sayisi*sizeof(int));
		k->sctd_kredisi=k->sctd_kredisi+ p->kredi;	
		p->kalan_kontenjan--;
 		p->doe[p->ogrenci_sayisi-1]=a;
 		if(p->ogrenci_sayisi==2){
 			if(p->doe[0]> p->doe[1]){
 				tmp=p->doe[0];
 				p->doe[0]=p->doe[1];
 				p->doe[1]=tmp;
			 }
		 }
		 if(p->ogrenci_sayisi > 2){
		 	for(i=0; i<p->ogrenci_sayisi-1;i++){
			for(j=i+1; j<p->ogrenci_sayisi; j++){
				if(p->doe[i] > p->doe[j]){
					tmp = p->doe[i];
               		p->doe[i] = p->doe[j];
					p->doe[j] = tmp;
			}
		}
	}
		 }
 		strcpy(k->ode[k->sctd_sayisi-1],b);
 		strcpy(kyt->ders_kodu,b);
		kyt->no=a;
		*id=*id+1;
		kyt->id=*id;
		printf("Lütfen Ýþlemi Yaptýðýnýz Tarihi Boþluk Býrakmadan Yazýnýz \n");
		scanf("%s",tarih);
		strcpy(kyt->tarih,tarih);
		strcpy(kyt->durum,"kayitli");
		kyt->next3=NULL;
		if(*head4==NULL){
			*head4=kyt;
		 }else{
		tmp2=*head4;
			while(tmp2->next3 != NULL){
				tmp2=tmp2->next3;
			}
		 tmp2->next3=kyt;
		 }
 		if(k->sctd_sayisi==2){
 			if(strcmp(k->ode[0],k->ode[1])>0){
 				strcpy(tmp3,k->ode[0]);
 				strcpy(k->ode[0],k->ode[1]);
 				strcpy(k->ode[1],tmp3);
			 }
		 }
		 if(k->sctd_sayisi >2){
		 	for(i=0; i< k->sctd_sayisi-1;i++){
			for(j=i+1; j< k->sctd_sayisi; j++){
				if(strcmp(k->ode[i],k->ode[j])>0){
				strcpy(tmp3,k->ode[1]);
               	strcpy(k->ode[i],k->ode[j]);
					strcpy(k->ode[j],tmp3);
			}
		}
	}
		 }
 		printf("Öðrenci Derse Baþarýlý Bir Þekilde Eklenmiþtir \n");
	}
}

int dersten_ogr_sil (ogrenci **head2,ders **head3,kayit **head4,int *id){
	system("cls");
	int a,i=0,j,tst=0;
	char b[SIZE];
	ogrenci *k=*head2;
	ders *p=*head3;
	ders *tmp=*head3;
	ders *current=*head3;
	kayit *tmp2=*head4;
	kayit *kyt=*head4;
	printf("Lutfen Ders Silecek Ogrencinin Numarasini Giriniz : "); scanf("%d",&a);
	while(k!=NULL && k->no!=a){
		k=k->next;
	}
	if( k == NULL){
	printf("%d Numaralý Öðrenci Bulunamadi \n", a);
	return 1;
	}
	printf("Lutfen Ders Kodunu Giriniz : "); scanf("%s",b);
	while(p!=NULL && strcmp(p->ders_kodu,b) !=0){
		p=p->nextt;
	}
	if( p == NULL){
		printf(" %s Kodlu Ders Bulunamadi \n", b);
		return 1;
	}
	if(k->sctd_sayisi !=0 ){
		for(i=0;i<k->sctd_sayisi;i++){
		if(strcmp(k->ode[i],b)==0){
			tst=1;
		}
	}
	}
	if(tst != 1){
		printf(" Öðrenci Dersi Önceden Seçmemiþtir \n");
		return 1;
	}
	p->kalan_kontenjan++;
	p->ogrenci_sayisi--;
	k->sctd_sayisi--;
	k->sctd_kredisi=k->sctd_kredisi-p->kredi;
	char tarih[20];
	printf("Lütfen Ýþlemi Yaptýðýnýz Tarihi Boþluk Býrakmadan Yazýnýz\n");
	scanf("%s",tarih);
	while(kyt->no!=a || strcmp(kyt->ders_kodu,b)!=0){
		kyt=kyt->next3;
		}
	strcpy(kyt->tarih,tarih);
	strcpy(kyt->durum,"silindi");
	i=0;
	j=0;
	while(i<p->ogrenci_sayisi+1 && p->doe[i]!=a){
		i++;
	}
	for(j=i ;j < p->ogrenci_sayisi;j++){
		p->doe[j]=p->doe[j+1];
	}
	i=0;
	j=0;
	while(i <k->sctd_sayisi && strcmp(k->ode[i],b)!=0){
		i++;
	}
	for(j=i ;j <k->sctd_sayisi;j++){
		strcpy(k->ode[j],k->ode[j+1]);
	}
	printf("Öðrenci Dersten Silinmiþtir \n");
	return 1;
}

ders *dersleri_yazdir(ders *head2){
	system("cls");
	int i;
	if(head2==NULL){
		printf("DERS LÝSTESÝ BOÞ \n ");
	}
	else{
	ders *p= head2;
		while(p != NULL){
			printf("*********************\n");
			printf("KOD-AD  DERS KREDISI DERS KONTENJANI  KALAN KONTENJAN  OGRENCI SAYISI \n",p->ders_kodu,p->ders_adi,p->kredi,p->kontenjan,p->kalan_kontenjan,p->ogrenci_sayisi);
			printf(" %s %s \t %d \t %d \t \t %d \t \t %d \t \n",p->ders_kodu,p->ders_adi,p->kredi,p->kontenjan,p->kalan_kontenjan,p->ogrenci_sayisi);
			if(p->ogrenci_sayisi !=0){
			printf("DERSÝ SEÇEN ÖÐRENCÝLERÝN NUMARALARI : ");
			for(i=0;i<p->ogrenci_sayisi;i++){
			printf(" %d \t ",p->doe[i]);
		}
			printf("\n");
	}
			p=p->nextt;
		}
	}
	return head2;
}
kayit *durum_yazdir(kayit *head3){
	system("cls");
	if(head3==NULL){
		printf("DURUM LÝSTESÝ BOÞ \n ");
	}
	else{
	kayit *m= head3;
		while(m != NULL){
			printf("*********************\n");
			printf("%d-%s-%d-%s-%s",m->id,m->ders_kodu,m->no,m->tarih,m->durum);
			printf("\n");
				m=m->next3;
	}
		}
	return head3;
}
int ders_programi(ogrenci **head2,ders **head3,kayit **head4){
	int i,j,tmp;
	char tmp3[SIZE];
	ogrenci *k=*head2;
	ogrenci *k2=*head2;
	ders *p=*head3;
	kayit *m=*head4;
	while(k != NULL){
		k->d_sctd_sayisi=0;
		k=k->next;
}
	while(p != NULL){
		p->d_ogrenci_sayisi=0;
		p=p->nextt;
}	
	k=*head2;
	p=*head3;
	while(m != NULL){
		if(!strcmp(m->durum,"kayitli")){
		k=ogrenci_bul(*head2,m->no);
		p=ders_bul(*head3,m->ders_kodu);
		if(p->d_ogrenci_sayisi==0){
	 	if(k->d_sctd_sayisi==0){
			k->d_sctd_sayisi=1;
		}else{
			k->d_sctd_sayisi++;
		}
		p->doe=(int*)malloc(sizeof(int));
	 	p->d_ogrenci_sayisi=1;
	 	p->doe[p->d_ogrenci_sayisi-1]=m->no;
	 	strcpy(k->ode[k->d_sctd_sayisi-1],m->ders_kodu);
	 	if(k->d_sctd_sayisi==2){
 			if(strcmp(k->ode[0],k->ode[1])>0){
 				strcpy(tmp3,k->ode[0]);
 				strcpy(k->ode[0],k->ode[1]);
 				strcpy(k->ode[1],tmp3);
			 }
		 }
		 if(k->d_sctd_sayisi>2){
		 	for(i=0; i< k->d_sctd_sayisi-1;i++){
			for(j=i+1; j< k->d_sctd_sayisi; j++){
				if(strcmp(k->ode[i] , k->ode[j])>0){
					strcpy(tmp3,k->ode[i]);
               		strcpy(k->ode[i],k->ode[j]);
					strcpy(k->ode[j],tmp3);
			}
		}
	}
		 }
	 }
	 
	 else{
		p->d_ogrenci_sayisi++;
		if(k->d_sctd_sayisi==0){
			k->d_sctd_sayisi=1;
		}else{
			k->d_sctd_sayisi++;
		}
		p->doe=(int*)realloc(p->doe,p->ogrenci_sayisi*sizeof(int));
 		p->doe[p->d_ogrenci_sayisi-1]=m->no;
 		if(p->d_ogrenci_sayisi==2){
 			if(p->doe[0]> p->doe[1]){
 				tmp=p->doe[0];
 				p->doe[0]=p->doe[1];
 				p->doe[1]=tmp;
			 }
		 }
		 if(p->d_ogrenci_sayisi > 2){
		 	for(i=0; i<p->d_ogrenci_sayisi-1;i++){
			for(j=i+1; j<p->d_ogrenci_sayisi; j++){
				if(p->doe[i] > p->doe[j]){
					tmp = p->doe[i];
               		p->doe[i] = p->doe[j];
					p->doe[j] = tmp;
			}
		}
	}
		 }
 		strcpy(k->ode[k->d_sctd_sayisi-1],m->ders_kodu);
 		if(k->sctd_sayisi==2){
 			if(strcmp(k->ode[0],k->ode[1])>0){
 				strcpy(tmp3,k->ode[0]);
 				strcpy(k->ode[0],k->ode[1]);
 				strcpy(k->ode[1],tmp3);
			 }
		 }
		 if(k->d_sctd_sayisi >2){
		 	for(i=0; i< k->d_sctd_sayisi-1;i++){
			for(j=i+1; j< k->d_sctd_sayisi; j++){
				if(strcmp(k->ode[i],k->ode[j])>0){
				strcpy(tmp3,k->ode[1]);
               	strcpy(k->ode[i],k->ode[j]);
					strcpy(k->ode[j],tmp3);
			}
		}
	}
		 }
	}
		i=0;
		j=0;
		}
		m=m->next3;
}		
	}
	
int main() {
	setlocale(LC_ALL, "Turkish");
	int secim,secim2,kredi,derss;
	ogrenci *head=NULL;
	ogrenci *tail=NULL;
	ders *head2=NULL;
	kayit *head3=NULL;
	int id=10000;
	
	printf("DOSYA OKUMA ÝÞLEMÝ YAPARAK BAÞLAMAK ÝSTÝYORSANIZ 1'e ÝSTEMÝYORSANIZ HERHANGÝ BÝR TUÞA'a BASINIZ \n"); scanf("%d",&secim2);
	
	if(secim2==1){
	head=ogr_Read("ogrenci.txt",",\0");
	head2=ders_Read("ders.txt",",\0");
	head3=kayit_Read(head3,&id);
	ders_programi(&head,&head2,&head3);	
	}
	
	printf("*****************************\n");
	printf("ÖGRENCÝ DERS KAYIT SÝSTEMÝ \n");
	printf("Bir Ögrencinin Kaç Adet Ders Alabileceðini Giriniz : "); scanf("%d",&derss);
	printf("Bir Ögrencinin Kaç Kredi Hakký Olacaðýný Giriniz : "); scanf("%d",&kredi);
	
while(1){
		printf("1-- ÖÐRENCÝ EKLE \n");
		printf("2-- ÖÐRENCÝ SÝL \n");
		printf("3-- ÖÐRENCÝLERÝ LÝSTELE\n");
		printf("4-- DERS EKLE \n");
		printf("5-- DERS KAPAT \n");
		printf("6-- DERS LÝSTELE \n");
		printf("7-- DERS ÖGRENCÝ EKLEME \n");
		printf("8-- DERSTEN ÖÐRENCÝ SÝLME \n");
		printf("9-- DURUM YAZDIR \n");
		printf("0-- ÇIKIÞ \n");
		printf("SECÝMÝNÝZÝ YAPINIZ [0-9] \n");
		scanf("%d",&secim);
		switch(secim){
			case 1: ogrenci_ekle(&head,&tail,derss,kredi);
					ogrenci_yaz(head);
			break;
			case 2:head =ogrenci_sil(head,head2,head3);
					ogrenci_yaz(head);
					ders_yaz(head2);
					program_yaz(head);
					durum_yaz(head3);
			break;
			case 3:head =ogrencileri_yazdir(head,tail);
			break;
			case 4:head2 =ders_ekle(head2);
					ders_yaz(head2);
			break;
			case 5:head2 =ders_sil(head2,head,head3);
					ders_yaz(head2);
					durum_yaz(head3);
					ogrenci_yaz(head);
					program_yaz(head);
			break;
			case 6:head2= dersleri_yazdir(head2);
			break;
			case 7:derse_ogr_ekle(&head,&head2,&head3,&id,kredi,derss);
					durum_yaz(head3);
					ogrenci_yaz(head);
					ders_yaz(head2);
					program_yaz(head);
			break;
			case 8:dersten_ogr_sil(&head,&head2,&head3,&id);
					durum_yaz(head3);
					ogrenci_yaz(head);
					ders_yaz(head2);
					program_yaz(head);
			break;
			case 9:head3=durum_yazdir(head3);
			break;
			case 0: exit(0);
			default : printf("HATALI SEÇÝM \n");
	}
}
	return 0;
}
