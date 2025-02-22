#include<stdio.h>
#include<stdlib.h>

typedef struct tn *tp;
struct tn
{
	int h_key, v_key;
	int d, color; //d=distance, color: 1=BLACK 2=GREY 3=WHITE
	tp up, down, left, right, pred, next;   //pred gia parent sto BFS, next gia list sto BFS
};

#define size 30

void DEFINE_EDGE(tp *new, int v_data, int h_data)
{	
	*new=(tp)malloc(sizeof(struct tn));
	
	(*new)->v_key=v_data;
	(*new)->h_key=h_data;
	(*new)->up=NULL;
	(*new)->down=NULL;
	(*new)->left=NULL;
	(*new)->right=NULL;
	(*new)->color=3;
	(*new)->d=0;
	(*new)->pred=NULL;
	(*new)->next=NULL;
}

tp FIND_EDGE(tp *v_temp, int v_data, int h_data)
{	
    tp aux;
    
    aux=(*v_temp);
	for (int i=1; i<v_data; ++i)
	{
	    aux=aux->down;
	}
	while((aux->right!=NULL) && (aux->right->h_key<= h_data))
	{
		aux=aux->right;
	}
	if ((aux->v_key==v_data) && (aux->h_key==h_data))
	{
	    printf("\n The edge has been found with vertical key %d and horizontal key %d\n", aux->v_key, aux->h_key);
	}
	else
	{
	    printf("\n The edge does not exist\n");
	}
	return aux;
}


void INSERT_EDGE(tp *new, tp *v_temp, tp *h_temp)
{
	tp aux;	
		
	//INSERT VERTICAL ARRAY (aka horizontal lists)
	while ((*new)->v_key>(*v_temp)->v_key)
    {
        (*v_temp)=(*v_temp)->down;
    }
	
	if ((*v_temp)->right!=NULL)
	{
		aux=(*v_temp);
		while((aux->right!=NULL) && (aux->right->h_key < (*new)->h_key))
		{
			aux = aux->right;
		}
		if ((aux->right ==NULL) || ((*new)->h_key != aux->right->h_key) )
		{
			(*new)->right = aux->right;
			aux->right=(*new);
			(*new)->left=aux;
			if ((*new)->right!=NULL)
			{
			    (*new)->right->left=(*new);
			}
		}
		else
		{
		printf("\n The EDGE already exists (vertical)\n");
		}
	} 
	if ((*v_temp)->right==NULL)
	{
		(*v_temp)->right = (*new);
		(*new)->left=(*v_temp);
	}
	
	
	//INSERT HORIZONTAL ARRAY (aka vertical lists)
	while ((*new)->h_key>(*h_temp)->h_key)
    {
        (*h_temp)=(*h_temp)->right;
    }
	
	if ((*h_temp)->down!=NULL)   //an to horizontal keli exei syndedemeni lista katw tou
	{
		aux=(*h_temp);
		while((aux->down!=NULL) && (aux->down->v_key < (*new)->v_key)) //oso paei katw, mexri to vertical key tou new na ginei mikrotero tou epomenou katw
		{
			aux = aux->down;
		}
		if ((aux->down==NULL) ||  ((*new)->v_key != aux->down->v_key) )
		{
			(*new)->down = aux->down;
			aux->down=(*new);
			(*new)->up=aux;
			if ((*new)->down!=NULL)
			{
			    (*new)->down->up=(*new);
			}
		}
		else
		{
		printf("\n The EDGE already exists (horizontal)\n");
		}
	}
	if ((*h_temp)->down==NULL)    //an to horizontal keli den exei syndedemeni lista katw tou
	{
	    (*h_temp)->down=(*new);
	    (*new)->up=(*h_temp);
	}
}

void PRINT(tp *v_temp, tp *h_temp)
{    
    tp aux;
    
    printf("\n PRINTING VERTICAL NODES AND EDGES (aka horizontal lists)\n");
    printf("\n(Vertical key, Horizontal key, Color, Distance)\n");
    
    for (int i=0; i<size; ++i)
    {
        aux=(*v_temp);
        while (aux!=NULL)
        {
            printf("(%d, %d, %d, %d) ", aux->v_key, aux->h_key, aux->color, aux->d);
            aux=aux->right;
        }
        printf("\n");
        (*v_temp)=(*v_temp)->down;
    }
    
    printf("\n PRINTING HORIZONTAL EDGES (aka vertical lists)\n");
    printf("\n(Vertical key, Horizontal key, Color, Distance)\n");
    for (int j=0; j<size; ++j)
    {
        aux=(*h_temp);
        while (aux!=NULL)
        {
            printf("(%d, %d, %d, %d) ", aux->v_key, aux->h_key, aux->color, aux->d);
            aux=aux->down;
        }
        printf("\n");
        (*h_temp)=(*h_temp)->right;
    }
}



void DELETE(tp *v_temp, int v_data, int h_data)
{
    tp aux1, aux2, aux3;
	
	if (((*v_temp)->v_key==v_data) && ((*v_temp)->h_key==h_data))
	{
	    aux2=(*v_temp);
	
	    //DELETE VERTICAL (aka horizontal lists) 
	    aux1=(*v_temp)->left;
		if (aux2->right!=NULL)
		{
			aux3=aux2->right;
			aux1->right=aux3;
			aux3->left=aux1;
			printf("\n EDGE deleted had vertical key %d and horizontal key %d (horizontal list)\n", aux2->v_key, aux2->h_key);
		}
		else
		{
		    aux1->right=NULL;
		    printf("\n EDGE deleted had vertical key %d and horizontal key %d (horizontal list)\n", aux2->v_key, aux2->h_key);
		}
			
		//DELETE HORIZONTAL (aka vertical lists) 
		aux1=(*v_temp)->up;
		if (aux2->down!=NULL)
		{
			aux3=aux2->down;
			aux1->down=aux3;
			aux3->up=aux1;
			printf("\n EDGE deleted had vertical key %d and horizontal key %d (vertical list)\n", aux2->v_key, aux2->h_key);
			
		}
		else
		{
		    aux1->down=NULL;
		    printf("\n EDGE deleted had vertical key %d and horizontal key %d (vertical list)\n", aux2->v_key, aux2->h_key);
		}
	    free(aux2);
	    aux2->up=NULL;
	    aux2->down=NULL;
	    aux2->left=NULL;
	    aux2->right=NULL;
	    aux2=NULL;
	}
}

void MAKE_LIST(tp *h, tp *t, tp aux)
{
	if ((*t)!=NULL)
	{
	    (*t)->next=aux;
		(*t)=aux;
		
	}
	if ((*t)==NULL)
	{
		(*h)=aux;
		(*t)=aux;		
	}
}

tp POP_0F_LIST(tp *h, tp *t)
{
    tp aux; 
    if ((*h)->next==NULL)
    {
        aux=(*h);
        (*h)=NULL;
        (*t)=NULL;
    }
    else if ((*h)->next!=NULL)
    {
        aux=(*h);
        (*h)=aux->next;
        aux->next=NULL;
    }
    return aux;
}

tp POP_0F_LIST_SPECIFIC(tp *h, tp *t, int v_data, int h_data)   //xrisimopoieitai stis listes twn cycles
{                                                               //epeidi molis vrw to prwto koino sto aux->next, meta einai anagkastika oloi koinoi
    tp aux, aux1;                                               //opote apla kanw aux->next=null kai allazw head i tail an xreiazetai
    
    if (((*h)!=NULL) && ((*h)->v_key!=v_data) && ((*h)->h_key!=h_data))
	{
		aux=(*h);
		while ((aux->next!=NULL) && (aux->next->v_key!=v_data) && (aux->next->h_key!=h_data))
		{
			aux=aux->next;
		}
		if ((aux->next!=NULL) && (aux->next->v_key==v_data) && (aux->next->h_key==h_data))
		{
		    aux1=aux->next;
			if (aux1==(*t))
			{
			    (*t)=aux;
			    aux->next=NULL;
			}
			else
			{
			    aux->next=NULL;
			}
            return aux;
		}
	}
	else if (((*h)!=NULL) && ((*h)->v_key==v_data) && ((*h)->h_key==h_data))
	{
		aux1=*h;
		(*h)=(*h)->next;
		return (*h);
	}
}


void DELETE_WHOLE(tp *h, tp *t)
{
	tp aux;
	while ((*h)!=NULL)
	{
	    aux=*h;
		(*h)=(*h)->next;
		aux->next=NULL;
	}
	(*h)=NULL;
	(*t)=NULL;
}


void BFS(tp *v_temp, int v_data)
{
    tp h, t, aux1, aux2, temp;
    h=NULL;
    t=NULL;
    
    aux1=(*v_temp);
    while (aux1->v_key<v_data)
	{
	    aux1=aux1->down;
	}
    aux1->color=2;
    aux1->d=0;
    MAKE_LIST(&h, &t, aux1);

    while ((h!=NULL) && (t!=NULL))
    {
        aux1=POP_0F_LIST(&h, &t);
        printf("\nNODE %d is in spanning tree.\n", aux1->v_key);
        aux1->left=aux1;
        
        while (aux1->left->right!=NULL)   //teleiwnei me tous 1ous geitones deksia xreisimopoiontas to nekro pointer left entos tou node 
        {                                          
            aux1->left=aux1->left->right;
            
            aux1->up=(*v_temp);
            while (aux1->up->v_key<aux1->left->h_key)   //vriskei to node sto opoio kataligei to edge "aux1->left" entos tou vertical matrix, xrisimopoiontas to nekro pointer up entos tou node 
	        {
	            aux1->up=aux1->up->down;
	        }
	        if (aux1->up->color==3)  //check an den exei ksanavrei to node
	        { 
	            aux1->left->d=aux1->d +1;        //kanei allages sto edge in spanning tree
	            aux1->left->pred=aux1;
	            aux1->left->color=1;
	            printf("\nEDGE (%d,%d) is in spanning tree.\n", aux1->left->v_key, aux1->left->h_key);
                aux1->up->color=2;  //node grey, in spanning tree and in list
                aux1->up->d=aux1->d + 1;
                aux1->up->pred=aux1;
                MAKE_LIST(&h, &t, aux1->up);
            }
            else if ((aux1->up->color==1) || (aux1->up->color==2)) //an exei ksanavrei to node, markarei seen kai to symmetriko edge (an yparxei) gia eykolia ston cycle
            {
                temp=aux1->up;
                while ((temp->h_key<aux1->left->v_key) && (temp->right!=NULL))   //vriskei symmetriko edge an yparxei
                {
                    temp=temp->right;
                }
                if ((temp->h_key==aux1->left->v_key) && (temp->color==1)) //an yparxei kai einai BLACK tote edge ginetai episis black gia na ksexwrizei apo cycles
                {
                    aux1->left->color=1;
                }
                else if ((temp->h_key!=aux1->left->v_key) || (temp->color!=1))  //an eite den yparxei symmetriko eite to symmetriko den einai BLACK einai cycle kai simadeyetai me WHITE
                {
                    aux1->left->color=3;
                }
                aux1->left->pred=aux1;  //predessesor tou edge to arxiko node se kathe periptwsi
            }
         }
         aux1->color=1;
         aux1->up=NULL; //kanei tous pointer pou xrisimopoiisa NULL wste na ksanaxrisimopoiithoun sto CYCLE
         aux1->left=NULL;
    }        
}

void CYCLE(tp *v_temp, int source_data)
{
    tp h1, t1, h2, t2, aux, aux1, aux2, aux3, temp, edge_node1, edge_node2;
    h1=NULL;
    t1=NULL;
    h2=NULL;
    t2=NULL;
    
    aux=(*v_temp);
    while (aux!=NULL)   //perna apo ola ta nodes
    {
        aux1=aux;
        while (aux1->right!=NULL)    //perna apo ola ta edges deksia twn nodes
        {
            aux1=aux1->right;
            if (aux1->color==3)  //vriskei cycles
            {
                printf("\nCycle found at edge (%d,%d)\n", aux1->v_key, aux1->h_key);
                edge_node1=aux1->pred;
                edge_node2=edge_node1->pred;
                while (edge_node1->v_key!=source_data) //vriskei synolo progonwn s(aux(v_key))
                {
                    temp=FIND_EDGE(v_temp, (edge_node2)->v_key, (edge_node1)->v_key);   
                    if (temp!=NULL) 
                    {
                        MAKE_LIST(&h1, &t1, temp);
                        edge_node1=temp->pred;
                        edge_node2=edge_node1->pred;
                    }
                    else    //an den yparxei, prepei na yparxei i symmetriki
                    {
                        temp=FIND_EDGE(v_temp, (edge_node1)->v_key, (edge_node2)->v_key);
                        MAKE_LIST(&h1, &t1, temp);
                        edge_node1=temp->pred->pred;
                        edge_node2=edge_node1->pred;
                    }
                }
                temp=(*v_temp);
                while (temp->v_key<aux1->h_key)    //vriskei to allo akro node tou edge-cycle
                {
                    temp=temp->down;
                }           
                edge_node1=temp;
                edge_node2=edge_node1->pred;
                while (edge_node1->v_key!=source_data) //vriskei synolo progonwn s(aux(h_key))
                {
                    temp=FIND_EDGE(v_temp, edge_node2->v_key, edge_node1->v_key);    
                    if (temp!=NULL) 
                    {
                        MAKE_LIST(&h2, &t2, temp);
                        edge_node1=temp->pred;
                        edge_node2=edge_node1->pred;
                    }
                    else    //an den yparxei, prepei na yparxei i symmetriki
                    {
                        temp=FIND_EDGE(v_temp, edge_node1->v_key, edge_node2->v_key);
                        MAKE_LIST(&h2, &t2, temp);
                        edge_node1=temp->pred->pred;
                        edge_node2=edge_node1->pred;
                    }
                }
                
                aux2=h1;
                while (aux2!=NULL)
                {
                    aux3=h2;
                    while (aux3!=NULL)  //check an oi dyo listes exoyn koina stoixeia
                    {
                        if ((aux2->v_key==aux3->v_key) && (aux2->h_key==aux3->h_key))   //an nai, tote to koino stoixeio bgainei apo tis 2 listes
                        {
                            aux2=POP_0F_LIST_SPECIFIC(&h1, &t1, aux2->v_key, aux2->h_key);
                            aux3=POP_0F_LIST_SPECIFIC(&h2, &t2, aux3->v_key, aux3->h_key);  //diagrafi kai epistrefei pointer sto proigoumeno stoixeio
                            
                        }
                        else
                        {
                            aux3=aux3->next;
                        }
                    }
                    aux2=aux2->next;
                }
                aux2=h1;
                while (aux2!=NULL)  //print ta stoixeia pou sximatizoun kyklo
                {
                    printf("\nEDGE (%d,%d) IN LIST OF CYCLE\n", aux2->v_key, aux2->h_key);
                    aux2=aux2->next;
                }
                aux2=h2;
                while (aux2!=NULL)
                {
                    printf("\nEDGE (%d,%d) IN LIST OF CYCLE\n", aux2->v_key, aux2->h_key);
                    aux2=aux2->next;
                } 
                printf("\nINITIAL EDGE (%d,%d) CLOSING THE CYCLE\n", aux1->v_key, aux1->h_key);   
                
                DELETE_WHOLE(&h1, &t1);     //diagrafi twn listwn gia na xrisimopoiithoun ston epomeno kyklo
                DELETE_WHOLE(&h2, &t2);    
            }   
        }
        aux=aux->down;
    }
}

int main ()
{
	char c, s;
	int k, m, v_data, h_data;
	tp new, v_temp, h_temp;
	new=NULL;
	v_temp=NULL;
	h_temp=NULL;
	
    struct tn V_Array[size], H_Array[size];
    for (int i=0; i<size; ++i)
    {
        V_Array[i].v_key=i+1;
        V_Array[i].h_key=0;
        V_Array[i].up=NULL;
        V_Array[i].left=NULL;
        V_Array[i].right=NULL;
        V_Array[i].color=3;
        V_Array[i].d=0;
	    V_Array[i].pred=NULL;
	    V_Array[i].next=NULL;
        
        H_Array[i].h_key=i+1;
        H_Array[i].v_key=0;
        H_Array[i].up=NULL;
        H_Array[i].down=NULL;
        H_Array[i].left=NULL;
        H_Array[i].color=3;
        H_Array[i].d=0;
	    H_Array[i].pred=NULL;
	    H_Array[i].next=NULL;
        
        if (i<size-1)
        {
            V_Array[i].down=&V_Array[i+1];
            H_Array[i].right=&H_Array[i+1];
        }
        else
        {
            V_Array[i].down=NULL;
            H_Array[i].right=NULL;
        }
    }
    
	c='*';
	while(c!='q')
	{
	    v_temp=&V_Array[0];
        h_temp=&H_Array[0];
		
		printf("\n INSERT NEW EDGE (i), FIND EXISTING EDGE (f), DELETE EDGE (d), PRINT SPARCE ARRAY EDGES VERTICALLY AND HORIZONTALLY (p), BREADTH FIRST SEARCH ALGORITHM (b), FIND CYCLE (c), QUIT (q) \n");
		scanf(" %c", &c);
		getchar();
		
		if (c =='i')
		{
			printf("\n INSERT NEW EDGE \n");
			printf("\n Give me the VERTICAL KEY of new EDGE 1 through 30 \n");
	        scanf("%d", &v_data);
	        getchar();
	        printf("\n Give me the HORIZONTAL KEY of new EDGE 1 through 30 \n");
	        scanf("%d", &h_data);
	        getchar();
	        if ((v_data<31) && (v_data>0) && (h_data<31) && (h_data>0))
	        {
			    DEFINE_EDGE(&new, v_data, h_data);  
			    INSERT_EDGE(&new, &v_temp, &h_temp);    //insert edge (x,y)
			    if (v_data!=h_data)
			    {
			        printf("\n Do you wish to insert the symmetrical edge? (y/n)\n");
			        scanf("%c", &s);
	                getchar();
	                if (s=='y')
	                {
			            v_temp=&V_Array[0];
                        h_temp=&H_Array[0];
			            DEFINE_EDGE(&new, h_data, v_data);
			            INSERT_EDGE(&new, &v_temp, &h_temp);    //insert symmetrical edge (y,x)
			        }
			        else if (s!='n')
			        {
			            printf("\n Wrong answer\n");
			        }
			    }
			}
			else 
			{
			    printf("\n HORIZONTAL and/or VERTICAL keys out of range\n");
			}
		}
		else if (c =='f')
		{
		    printf("\n FIND EXISTING EDGE\n");
		    printf("\n Give me the VERTICAL KEY of edge to be found 1 through 30 \n");
	        scanf("%d", &v_data);
	        getchar();
	        printf("\n Give me the HORIZONTAL KEY new edge to be found 1 through 30 \n");
	        scanf("%d", &h_data);
	        getchar();
		    v_temp=FIND_EDGE(&v_temp, v_data, h_data);  //find edge (x,y)
		    if (v_data!=h_data)
		    {
		        printf("\n Do you wish to find the symmetrical edge? (y/n)\n");
			    scanf("%c", &s);
	            getchar();
	            if (s=='y')
	            {
			        v_temp=&V_Array[0];
		            v_temp=FIND_EDGE(&v_temp, h_data, v_data);  //find symmetrical edge (y,x)
			    }
			    else if (s!='n')
			    {
			        printf("\n Wrong answer\n");
			    }
		    }
		}
		else if (c =='d')
		{
			printf("\n DELETE EDGE \n");
			printf("\n Give me the VERTICAL KEY of edge to be deleted 1 through 30 \n");
	        scanf("%d", &v_data);
	        getchar();
	        printf("\n Give me the HORIZONTAL KEY new edge to be deleted 1 through 30 \n");
	        scanf("%d", &h_data);
	        getchar();
	        v_temp=FIND_EDGE(&v_temp, v_data, h_data);
			DELETE(&v_temp, v_data, h_data);   //delete edge (x,y)
			if (v_data!=h_data)
			{    
			    printf("\n Do you wish to delete the symmetrical edge? (y/n)\n");
			    scanf("%c", &s);
	            getchar();
	            if (s=='y')
	            {
			        v_temp=&V_Array[0];
			        v_temp=FIND_EDGE(&v_temp, h_data, v_data);
			        DELETE(&v_temp, h_data, v_data);    //delete symmetrical edge (y,x)
			    }
			    else if (s!='n')
			    {
			        printf("\n Wrong answer\n");
			    }
			}
		}
		else if (c=='b')
		{
		    printf("\n EXECUTING BREADTH FIRST SEARCH ALGORITHM \n");
			printf("\n Give me the VERTICAL KEY 1 to 30 of source vertix to execute \n");
	        scanf("%d", &v_data);
	        getchar();
	        BFS(&v_temp, v_data);
		}
		else if (c =='p')
		{
			PRINT(&v_temp, &h_temp);
		}
		else if (c =='c')
		{
		    printf("\n EXECUTING CYCLE ALGORITHM \n");
			printf("\n Give me the VERTICAL KEY 1 to 30 of source vertix to execute \n");
	        scanf("%d", &v_data);
	        getchar();
	        printf("\n Has BREADTH FIRST SEARCH ALGORITHM already been executed? (y/n) \n");
	        scanf("%c", &s);
	        getchar();
	        if (s=='y')
	        {
	            CYCLE(&v_temp, v_data);
	        }
	        else if (s=='n')
	        {
	            BFS(&v_temp, v_data);
	            printf("\nBreadth First Search algorithm has been executed.\n");
			    CYCLE(&v_temp, v_data);
			}
			else 
			{
			    printf("\n Wrong answer\n");
			}
		}
		printf("\n Press any key to continue...\n");
	}
return 0;
}

