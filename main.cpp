#include <cstdio>
#include <cstdlib>
#include <iostream>

class Grafo{

    static bool x;



    int _n;
    int _m;
    int m_max;
    int vecino;
    int vecino2;


    friend void print(Grafo &);
    bool *v;
    int f(int , int);

public:

    int mar[6];
    int Marcado[10];
    Grafo(int);

     // ~ Falta destructor

      bool &edge(int, int) ;

      int m() const;
      int n() const;

      void DeepFirstSearch(int, int, Grafo &);
      void CaminoMasCorto(int, int, Grafo &);
      bool buscarMarcado(int);
      bool buscarMarcado2(int);
      bool Vecindad(int, Grafo &);
      bool Vecindad2(int, Grafo &);
};

 void print(Grafo &);

 class node{

    int _data;
    node *_siguiente;

public:

    node(int x):_data(x){_siguiente = NULL;}
    int dato(){return _data;}
    node *apuntador(node *_a, node *_b){return _a->_siguiente = _b;}
    node *siguiente(node *_a){return _a ->_siguiente;}
 };


class bicola{


    node *_frente;
    int s;
public:


    bicola(){s = 0; _frente = NULL;}

    void Push(int x);
	int Pop();
	int top(node *_a);
	bool Vacia(){return s == 0 ? true : false;}
	int size(){ return s;}
	void mostrar();
	node *frente(node *_a){return _frente = _a;}
	node *nodeFrente(){return _frente;}

 };



 void bicola::Push(int x)
{
	node *nuevo = new node(x);

	if(Vacia())
	{
		frente(nuevo);
		//printf("primer nodo: %i \n", nuevo->dato());
		s++;
	}

	else
	{
 		nuevo->apuntador(nuevo, nodeFrente());
		frente(nuevo);
		//printf("Nuevo nodo en else: %i \n", nuevo->dato());
		s++;
	}
}


int bicola::Pop()
{
	int valor;

	if(nodeFrente() == NULL) return -1;

	node *actual = nodeFrente();

	valor = nodeFrente()->dato();
	frente(actual->siguiente(actual));
	delete actual;
	--s;
	return valor;
}

int bicola::top(node *_a)
{
	return _a->dato();
}

void bicola::mostrar()
{
	node *actual = nodeFrente();
	while(actual != NULL)
	{
		printf("%i ", actual->dato());
		actual = actual->siguiente(actual);
	}
	puts("");
}

    bool Grafo::x = false;

    int Grafo::f(int u, int v){
      if(u== v)return 0;

      if(v>u){

        int aux = v;
        v =u;
        u = aux;

      }

      return (((u -1) * (u -2))/ 2) + v+1;

      }


      Grafo::Grafo(int n): _n(n){
        // _n = n;
        m_max = _n * (_n-1)/2;

        v = new bool[m_max];

       for(int i = 0; i < m_max; i++) v[i]= false;

      }


      bool &Grafo::edge(int i, int j){//devuelve una referencia
        if(i < 1 || i > _n || j < 1 || j > _n || j == i){

           printf("[Grafo]: bad index \n");
            return x;
        }
        return v[f(i, j)];
      }


      int Grafo::n()const{return _n;}
      int Grafo::m() const{return _m;}


        void print(Grafo &g){

            for(int i = 2; i <= g._n; i++){
                for(int j = 1; j < i; j++){
                    printf("[%i:%i] %i\n", i, j, g.v[g.f(i,j)]);
                    //printf("[%i:%i] %i\n", i, j, g.edge(i,j));
                }

            }
            }

bool Grafo::buscarMarcado(int x){

    for(int i = 0; i < 6; i++){
        if(mar[i] == x){
            return true;
        }
    }
    return false;
}

bool Grafo::buscarMarcado2(int x){

    for(int i = 0; i < 10; i++){
        if(Marcado[i] == x){
            return true;
        }
    }
    return false;
}

bool Grafo::Vecindad(int x, Grafo &g){

    for(int j = 1; j <= n();){
        if(g.v[f(x, j)] && !buscarMarcado(j)){
                vecino = j;
            return true;
        }else{
        j++;
        }
    }
    return false;
}

bool Grafo::Vecindad2(int x, Grafo &g){

    for(int j = 1; j <= n();){
        if(g.v[f(x, j)] && !buscarMarcado2(j)){
                vecino2 = j;
            return true;
        }else{
        j++;
        }
    }
    return false;
}

void Grafo::DeepFirstSearch(int source, int target, Grafo &g){
        bicola bi;
        bi.Push(source);
        int j = 0;
        int u;

        while(!bi.Vacia()){
            u = bi.nodeFrente()->dato();
            mar[j] = u;
            j++;
            if(Vecindad(u, g) && !buscarMarcado(vecino)){
               bi.Push(vecino);
                if(vecino == target){
                    return bi.mostrar();
                }
               }else{
                bi.Pop();
               }

        }

        return bi.mostrar();
}

void Grafo::CaminoMasCorto(int source, int target, Grafo &g){

        int j = 0;
        int u;

        bicola Sp;
        Sp.Push(source);
        Marcado[j]= source;
        Grafo E(m_max);

        while(!Sp.Vacia()){

            u = Sp.Pop();
            for(Vecindad2(u, g); !Vecindad2(u, g) && !buscarMarcado(Marcado[j]); Vecindad2(u, g)){
                E.edge(u, vecino2) = true;
                if(vecino2 == target){
                    return E.DeepFirstSearch(source, target, g);
                }
                Sp.Push(vecino2);
                j++;
                Marcado[j] = vecino2;
            }
        }

    return E.DeepFirstSearch(source, target, g);

}

int main(){

    /*int t;
    scanf("%i", &t);

    Grafo g(t);*/
    Grafo g(6);
    int sour, tar;

    g.edge(1, 3) = true;
    g.edge(1, 6) = true;
    g.edge(2, 3) = true;
    g.edge(2, 4) = true;
    g.edge(2, 5) = true;
    g.edge(5, 3) = true;
    g.edge(4, 5) = true;
    g.edge(4, 6) = true;
    g.edge(6, 5) = true;

    print(g);
    printf("Source: \n");
    scanf("%i", &sour);
    printf("Target: \n");
    scanf("%i", &tar);
    printf("Camino mas corto: \n");
    g.CaminoMasCorto(sour, tar, g);

    return 0;
}
