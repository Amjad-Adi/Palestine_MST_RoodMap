/*
Name: Amjad Qaher Sadek Adi
Student ID:1230800
Section number:3
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define FAULT_HANDLER 33
#define MAX_NUMBER_OF_CITIES 501//Always bigger by 1 than neeeded
#define MAX_NUMBER_OF_EDGES 10000
#define PRIME_LESS_THAN_MAX_NUMBER_OF_CITIES 499
#define MAX_City_Name 33
#define MAX_Edge_DESCRIPTION_LINE 80
struct CityNode{
char cityName[MAX_City_Name];
int distance;
int hashIndex;
struct CityNode* next;
};
struct PrimsMinHeapElements{
char srcCityName[MAX_City_Name];
char destCityName[MAX_City_Name];
int distance;
int destHashIndex;
};
struct MST{
char srcCityName[MAX_City_Name];
char destCityName[MAX_City_Name];
int distance;
};
struct KruskalMinHeapElements{
char srcCityName[MAX_City_Name];
int srcHashIndex;
int destHashIndex;
char destCityName[MAX_City_Name];
int distance;
};
typedef struct CityNode* ptrToCity;
typedef  ptrToCity LinkedList;
typedef  LinkedList Graph[MAX_NUMBER_OF_CITIES];
typedef struct PrimsMinHeapElements PrimsMinHeapElements;
typedef struct KruskalMinHeapElements KruskalMinHeapElements;
void makeEmpty(Graph);
void deleteList(LinkedList);
int isEmptyList(LinkedList);
void getFileInformation(Graph);
int hashFunction(char[],Graph G);
void insertFirst(char[] ,int ,int,LinkedList );
unsigned long mapStringToIntX(char *);
double primsAlgorithim(Graph,int *);
void primsInsert(char [],int ,char[],int ,int ,PrimsMinHeapElements [],int [],int flag);
void primsSlide(int ,PrimsMinHeapElements[],int[]);
PrimsMinHeapElements primsDeleteMin(PrimsMinHeapElements [],int[],int );
double kruskalsAlgorithim(Graph,int *);
void kruskalsInsert(char [],int ,int ,char [],int ,int ,KruskalMinHeapElements []);
void kruskalsSlide(int ,KruskalMinHeapElements []);
KruskalMinHeapElements kruskalsDeleteMin(KruskalMinHeapElements[],int );
int findRoot(int ,int []);
int mergeTrees(int ,int ,int [],int []);
void deleteGraph(Graph );
int size=0,order=0;
int main(){
    printf("Welcome to Our Road Network.");
    char selectedOption[FAULT_HANDLER];//used to detect false inputs that can cause Runtime error as entering string not a number
    short numericalRepresentationOfSelectedOption;
    Graph cityGraph={NULL};
    double primsTakenTime,kruskalsTakenTime;
    int primsCost=0, kruskalsCost=0;
    int primsFlag=0;
    int kruskalsFlag=0;
    do{
        printf("\n\nKindly, Choose an option from the following menu:\n1. Load Cities\n2. Apply Prim's Algorithm\n3. Apply Kruskal's Algorithm\n4. Compare the two algorithms\n5. Exit\n\nYour selected option: ");
        gets(selectedOption);
        numericalRepresentationOfSelectedOption=atoi(selectedOption);
        switch(numericalRepresentationOfSelectedOption){
        case 1:{
            makeEmpty(cityGraph);
            getFileInformation(cityGraph);
            break;
        }
        case 2:{
            primsCost=0;
        primsTakenTime=primsAlgorithim(cityGraph,&primsCost);
            printf("\nThe time Taken: %f",primsTakenTime);
            primsFlag=1;
        break;
            }
        case 3:{
            kruskalsCost=0;
        kruskalsTakenTime=kruskalsAlgorithim(cityGraph,&kruskalsCost);
            printf("\nThe time Taken: %f",kruskalsTakenTime);
            kruskalsFlag=1;
        break;
            }
        case 4:{
            if(!primsFlag){
                    primsCost=0;
                printf("\nSince You havent done Prim's Algorithim, we will do it for you:\n");
                printf("\n\nPrim's Algorithim: ");
                primsTakenTime=primsAlgorithim(cityGraph,&primsCost);
                printf("\nThe time Taken: %f\n",primsTakenTime);
                primsFlag=1;
            }
            if(!kruskalsFlag){
                    kruskalsCost=0;
                printf("\nSince You havent done Krukals's Algorithim, we will do it for you:\n");
                printf("\nKruskal's Algorithim: ");
                kruskalsTakenTime=kruskalsAlgorithim(cityGraph,&kruskalsCost);
                printf("\nThe time Taken: %f\n",kruskalsTakenTime);
                kruskalsFlag=1;
            }
            printf("\n\n************************************************************\n\nIn Prim's Algorithim:\nThe Cost: %d\nThe Execution time: %f\n\nIn Kruskal's Algorithim:\nThe Cost: %d\nThe Execution time: %f",primsCost,primsTakenTime,kruskalsCost,kruskalsTakenTime);
        break;
        }
        case 5:{
        printf("\nThanks for using the task managment system, see you again.");
        deleteGraph(cityGraph);
        break;
        }
        default: printf("\nplease enter a correct number.");
        }
    }while(numericalRepresentationOfSelectedOption!=5);
    return 0;
}

void getFileInformation(Graph G){
    FILE *inputFile=fopen("Cities.txt","r");
    if (inputFile==NULL){//checking if the file we tried to open exists
        printf("\nError while opening the file, the file named Cities.txt may not exist.");
    }
    else{
            char dataFromFile[MAX_Edge_DESCRIPTION_LINE],destCityName[MAX_City_Name];
            int distance;
            int hashIndex;
            int destHashIndex;
            int flag=1;
            for(int i=0,lineCount=0;fgets(dataFromFile,MAX_Edge_DESCRIPTION_LINE,inputFile)!=NULL;i=0,lineCount++){//read data till EOF is reached
                char* token=strtok(dataFromFile,"#");//cut dataFromFile into substrings based on #
                while(token!=NULL){
                        if(!i){
                         hashIndex=hashFunction(token,G);
                        }
                        else if(i==1)
                        strcpy(destCityName,token);
                        else if(i==2)
                        distance=atoi(token);
                    token=strtok(NULL,"#");//cut based on # till NULL is reached
                i++;
                }
                if(i==3){
                 destHashIndex=hashFunction(destCityName,G);
                insertFirst(destCityName,distance, destHashIndex,G[hashIndex]);
                size++;
                insertFirst(G[hashIndex]->cityName,distance,hashIndex,G[destHashIndex]);
                }
                else {
                printf("\nInvalid file data format in the line %d.",lineCount+1);
                flag=0;
                break;
            }
            }
            fclose(inputFile);//closing the opened file after reading so the memory allocated with it is removed
            if(flag){
            printf("\nThe Graph Order: %d\nThe Graph Size: %d",order,size);
            }
}
}

void makeEmpty(Graph G){
    if(G){
    for(int i=0;i<MAX_NUMBER_OF_CITIES;i++){
    if(G[i]!=NULL)
    deleteList(G[i]);
   else{
        G[i]=(LinkedList) malloc(sizeof(struct CityNode));
 if(G[i]==NULL)
    printf("\nNo memory, Free memory and come again.");
 else
    G[i]->next=NULL;
   }
}
}
}
void deleteList(LinkedList L){
     if(L==NULL){
           printf("\nNo existing list, try loading the file list, or check if the loaded list exists.");
     }
else if(!isEmptyList(L)){
ptrToCity p=L->next,temp;
L->next=NULL;
while(p!=NULL){
temp=p->next;
free(p);
p=temp;
}
}
}

int isEmptyList(LinkedList L){
    if(L==NULL)
        return -1;
    return L->next==NULL;
}

void insertFirst(char destCityName[],int distance,int hashIndex,LinkedList L){
            if(L==NULL)
           printf("\nNo existing list, try loading the file list, or check if the loaded list exists.");
    else{
      ptrToCity temp=(ptrToCity) malloc(sizeof(struct CityNode));
      if(temp==NULL){
          printf("\nNo memory, Free memory and come again.");
      }
      else{
            strcpy(temp->cityName,destCityName);
            temp->distance=distance;
            temp->next=L->next;
            temp->hashIndex=hashIndex;
            L->next=temp;
}
}
}

unsigned long mapStringToIntX(char* key){
unsigned long mapValue = 0;
while( *key != '\0' )
mapValue = (mapValue << 5 ) + (*key++) ;
return mapValue;
}

int hashFunction(char name[],Graph G){
     unsigned long x=mapStringToIntX(name);
     int hashIndex;
        for(int j=0, foundFlag=0;j<MAX_NUMBER_OF_CITIES&&!foundFlag;j++){
                hashIndex=(x+j*(PRIME_LESS_THAN_MAX_NUMBER_OF_CITIES-(x%PRIME_LESS_THAN_MAX_NUMBER_OF_CITIES)))%MAX_NUMBER_OF_CITIES;
                if(G[hashIndex]->next==NULL){
                    strcpy(G[hashIndex]->cityName,name);
                    G[hashIndex]->hashIndex=hashIndex;
                    foundFlag=!foundFlag;
                    order++;
                    }
                    else if(strcmp(G[hashIndex]->cityName,name)==0)
                    foundFlag=!foundFlag;
                }
                return hashIndex;
}

double primsAlgorithim(Graph G,int *cost){
    if(G)
    if(size){
        PrimsMinHeapElements minHeap[MAX_NUMBER_OF_EDGES+1];
    struct MST goneTo[MAX_NUMBER_OF_CITIES-1];
    int visited[MAX_NUMBER_OF_CITIES]={0};
    int posInMinHeap[MAX_NUMBER_OF_EDGES+1]={0};
    int firstAvailableSpot=1;
    char firstCity[MAX_City_Name];
    int hashIndex;
        int exist=0;
    do{
    printf("\nEnter the source city to start from: ");
    gets(firstCity);
    unsigned long x=mapStringToIntX(firstCity);
      for(int j=0;j<MAX_NUMBER_OF_CITIES&&!exist;j++){
        hashIndex=(x+j*(PRIME_LESS_THAN_MAX_NUMBER_OF_CITIES-(x%PRIME_LESS_THAN_MAX_NUMBER_OF_CITIES)))%MAX_NUMBER_OF_CITIES;
        if(G[hashIndex]->next==NULL)
            break;
                else if(strcmp(G[hashIndex]->cityName,firstCity)==0)
                exist=1;
            }
        if(!exist)
        printf("\nCity not found, please Enter a correct city name.\n");
    }while(!exist);
    ptrToCity p=G[hashIndex]->next;
    char srcname[MAX_City_Name];
    strcpy(srcname,G[hashIndex]->cityName);
    visited[hashIndex]=1;
        clock_t t;
    t = clock();
for(int i=0;i<size-1;i++){// v times
while(p!=NULL){//E times
        if(visited[p->hashIndex]==0){
            if(posInMinHeap[p->hashIndex]==0){
        primsInsert(p->cityName,p->distance,srcname,p->hashIndex,firstAvailableSpot,minHeap,posInMinHeap,0);//E times for LogV
                firstAvailableSpot++;
        }
else if(minHeap[posInMinHeap[p->hashIndex]].distance>p->distance)
    primsInsert(p->cityName,p->distance,srcname,p->hashIndex,firstAvailableSpot,minHeap,posInMinHeap,1);
}
p=p->next;
}
PrimsMinHeapElements min;
    min=primsDeleteMin(minHeap,posInMinHeap,--firstAvailableSpot);//v times for log v
goneTo[i].distance=min.distance;
strcpy(goneTo[i].destCityName,min.destCityName);
strcpy(goneTo[i].srcCityName,min.srcCityName);
visited[min.destHashIndex]=1;
strcpy(srcname,min.destCityName);
p=G[min.destHashIndex]->next;
(*cost)+=min.distance;
}
printf("\nThe MST is:");
for(int i=0;i<order-1;i++)
printf("\n%s -> %s: distance= %d(KM)",goneTo[i].srcCityName,goneTo[i].destCityName,goneTo[i].distance);
printf("\nThe cost is: %d",*cost);
    t = clock() - t;//(E+V) log v
    double takenTime = ((double)t)/CLOCKS_PER_SEC;
    return takenTime;
    }
    else printf("\nNo Cities and Edges in the graph.");
    else printf("The Citie and Edges are not loaded from the file");
    return -1;
}

void primsInsert(char destCityName[],int distance,char srcCityName[],int destHashIndex,int firstAvailableSpot,PrimsMinHeapElements minHeap[],int positionInMinHeap[],int flag){
    if(flag){
        minHeap[positionInMinHeap[destHashIndex]].distance=distance;
            strcpy(minHeap[positionInMinHeap[destHashIndex]].srcCityName,srcCityName);
            primsSlide(positionInMinHeap[destHashIndex],minHeap,positionInMinHeap);
    }
    else{
strcpy(minHeap[firstAvailableSpot].srcCityName,srcCityName);
minHeap[firstAvailableSpot].distance=distance;
minHeap[firstAvailableSpot].destHashIndex=destHashIndex;
strcpy(minHeap[firstAvailableSpot].destCityName,destCityName);
positionInMinHeap[destHashIndex]=firstAvailableSpot;
primsSlide(firstAvailableSpot,minHeap,positionInMinHeap);
    }
}

void primsSlide(int firstAvailableSpot,PrimsMinHeapElements minHeap[],int positionInMinHeap[]){
    PrimsMinHeapElements wanted=minHeap[firstAvailableSpot];
    int i;
for(i=firstAvailableSpot;i>1&&wanted.distance<minHeap[i/2].distance;i/=2){
    minHeap[i]=minHeap[i/2];
     positionInMinHeap[minHeap[i].destHashIndex]=i;
}
minHeap[i]=wanted;
positionInMinHeap[wanted.destHashIndex]=i;
}

PrimsMinHeapElements primsDeleteMin(PrimsMinHeapElements minHeap[],int positionInMinHeap[],int firstAvailableSpot){
int i=1, flag=1;
PrimsMinHeapElements min=minHeap[1];
minHeap[1]=minHeap[firstAvailableSpot];
while (flag){
    int minimum=i;
    if(2*i<firstAvailableSpot&&minHeap[2*i].distance<minHeap[minimum].distance)
    minimum=2*i;
    if(2*i+1<firstAvailableSpot&&minHeap[2*i+1].distance<minHeap[minimum].distance)
    minimum=2*i+1;
    if(minimum!=i){
        PrimsMinHeapElements temp=minHeap[minimum];
        minHeap[minimum]=minHeap[i];
        minHeap[i]=temp;
        positionInMinHeap[minHeap[i].destHashIndex]=i;
        i=minimum;
    }
    else flag=0;
}
positionInMinHeap[minHeap[i].destHashIndex]=i;
return min;
}

double kruskalsAlgorithim(Graph G,int *cost){
    if(G)
    if(order){
        KruskalMinHeapElements minHeap[MAX_NUMBER_OF_EDGES+1];
    struct MST goneTo[MAX_NUMBER_OF_CITIES];
    int firstAvailableSpot=1;
    int rootDistance[MAX_NUMBER_OF_CITIES];
    int sizeofTree[MAX_NUMBER_OF_CITIES];
    clock_t t;
    t = clock();
    int count=0;
for(int i=0;i<MAX_NUMBER_OF_CITIES&&count<MAX_NUMBER_OF_EDGES;i++){
ptrToCity p=G[i]->next;
if(G[i]->next){
rootDistance[G[i]->hashIndex]=i;
sizeofTree[G[i]->hashIndex]=1;
}
while(p!=NULL){//E times
    if(G[i]->hashIndex<p->hashIndex){
kruskalsInsert(G[i]->cityName,G[i]->hashIndex,p->distance,p->cityName,p->hashIndex,firstAvailableSpot,minHeap);//Log E
firstAvailableSpot++;
count++;
}
p=p->next;
}
}
KruskalMinHeapElements min;
for(int i=0;i<order-1;){//V times
    min=kruskalsDeleteMin(minHeap,--firstAvailableSpot);//Log E
    if(mergeTrees(min.srcHashIndex, min.destHashIndex,rootDistance,sizeofTree)){
strcpy(goneTo[i].srcCityName,min.srcCityName);
goneTo[i].distance=min.distance;
strcpy(goneTo[i].destCityName,min.destCityName);
(*cost)+=min.distance;
i++;
}
}
printf("\nThe MST is:");
for(int i=0;i<order-1;i++)
printf("\n%s -> %s: distance = %d(KM)",goneTo[i].srcCityName,goneTo[i].destCityName,goneTo[i].distance);
printf("\nThe cost is: %d",*cost);
    t = clock() - t;//(E+V) LogE
    double takenTime = ((double)t)/CLOCKS_PER_SEC;
    return takenTime;
    }
    else printf("\nNo Cities and Edges in the graph.");
    else printf("The Citie and Edges are not loaded from the file");
    return -1;
}

void kruskalsInsert(char srcCityName[],int srcHashIndex,int distance,char destCityName[],int destHashIndex,int firstAvailableSpot,KruskalMinHeapElements minHeap[]){
strcpy(minHeap[firstAvailableSpot].srcCityName,srcCityName);
minHeap[firstAvailableSpot].srcHashIndex=srcHashIndex;
minHeap[firstAvailableSpot].distance=distance;
minHeap[firstAvailableSpot].destHashIndex=destHashIndex;
strcpy(minHeap[firstAvailableSpot].destCityName,destCityName);
kruskalsSlide(firstAvailableSpot,minHeap);
}

void kruskalsSlide(int firstAvailableSpot,KruskalMinHeapElements minHeap[]){
    KruskalMinHeapElements wanted=minHeap[firstAvailableSpot];
    int i;
for(i=firstAvailableSpot;i>1&&wanted.distance<minHeap[i/2].distance;i/=2)
    minHeap[i]=minHeap[i/2];
minHeap[i]=wanted;
}

KruskalMinHeapElements kruskalsDeleteMin(KruskalMinHeapElements minHeap[],int firstAvailableSpot){
int i=1, flag=1;
KruskalMinHeapElements min=minHeap[1];
minHeap[1]=minHeap[firstAvailableSpot];
while (flag){
    int minimum=i;
    if(2*i<firstAvailableSpot&&minHeap[2*i].distance<minHeap[minimum].distance)
    minimum=2*i;
    if(2*i+1<firstAvailableSpot&&minHeap[2*i+1].distance<minHeap[minimum].distance)
    minimum=2*i+1;
    if(minimum!=i){
        KruskalMinHeapElements temp=minHeap[minimum];
        minHeap[minimum]=minHeap[i];
        minHeap[i]=temp;
        i=minimum;
    }
    else flag=0;
}
return min;
}

int findRoot(int hashIndex,int rootDistance[]){
    if (rootDistance[hashIndex]!=hashIndex)
        rootDistance[hashIndex]=findRoot(rootDistance[hashIndex],rootDistance);
return rootDistance[hashIndex];
}

int mergeTrees(int srcHashIndex,int destHashIndex,int rootDistance[],int sizeofTree[]){
    int firstRoot=findRoot(srcHashIndex,rootDistance),secondRoot=findRoot(destHashIndex,rootDistance);
    if (firstRoot!=secondRoot){
        if (sizeofTree[firstRoot]<sizeofTree[secondRoot]){
            rootDistance[firstRoot]=secondRoot;
            sizeofTree[secondRoot] += sizeofTree[firstRoot];
        }
        else{
            rootDistance[secondRoot] = firstRoot;
            sizeofTree[firstRoot] += sizeofTree[secondRoot];
        }
        return 1;
    }
    return 0;
}

void deleteGraph(Graph G){
for(int i=0;i<MAX_NUMBER_OF_CITIES;i++)
    deleteList(G[i]);
}
