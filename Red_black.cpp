#include <iostream>
using namespace std;
struct nodo_red_black
{
    bool color;
    int valor;
    nodo_red_black*padre;
    nodo_red_black*der;
    nodo_red_black*izq;
};

class Arbol_RB{
private:
    nodo_red_black*raiz;
public:
    Arbol_RB();
    void anadir(int);
    void ordenar_anadir(nodo_red_black*);
    void rb_transplante(nodo_red_black*,nodo_red_black*);
    nodo_red_black* minimo(nodo_red_black*);
    void eliminar(int);
    void ordenar_eliminar(nodo_red_black*);
    void rotacion_izq(nodo_red_black*);
    void rotacion_der(nodo_red_black*);
    nodo_red_black* devol_raiz();
    void imprimir(nodo_red_black*);
    ~Arbol_RB();
};
Arbol_RB::Arbol_RB(){
    raiz=nullptr;
}
void Arbol_RB::anadir(int n){
    if(raiz==nullptr){
        raiz=new nodo_red_black();
        raiz->padre=nullptr;
        raiz->color=false;
        raiz->valor=n;
        return;
    }
    nodo_red_black * hijo=nullptr;
    nodo_red_black * tmp=raiz;
    while(1){
        if(tmp->valor>n){
            if(tmp->izq!=nullptr){
                tmp=tmp->izq;
            }
            else{
                tmp->izq=new nodo_red_black();
                hijo=tmp->izq;
                break;
            }
        }
        else{
            if(tmp->der!=nullptr){
                tmp=tmp->der;
            }
            else{
                tmp->der=new nodo_red_black();
                hijo=tmp->der;
                break;
            }
        }
    }
    hijo->valor=n;
    hijo->color=true;
    hijo->padre=tmp;
    if(hijo->padre->padre==nullptr){
        hijo->padre->color=false;
        return;
    }
    else{
        ordenar_anadir(hijo);
    }
}
void Arbol_RB::ordenar_anadir(nodo_red_black*tmp){
    nodo_red_black*tmp2;
    while(tmp->padre->color==true){
        nodo_red_black * abuelo=tmp->padre->padre;
        if(abuelo->izq==tmp->padre){
            tmp2=abuelo->der;
            if(tmp2!=nullptr && tmp2->color==true){
                abuelo->izq->color=false;
                abuelo->der->color=false;
                abuelo->color=true;
                tmp=abuelo;
            }
            else{
                if(tmp==tmp->padre->der){
                    tmp=tmp->padre;
                    rotacion_izq(tmp);
                }
                tmp->padre->color=false;
                tmp->padre->padre->color=true;
                rotacion_der(tmp->padre->padre);
            }
        }
        else{
            tmp2=abuelo->der;
            if(tmp2!=nullptr && tmp2->color==true){
                abuelo->izq->color=false;
                abuelo->der->color=false;
                abuelo->color=true;
                tmp=abuelo;
            }
            else{
                if(tmp==tmp->padre->izq){
                    tmp=tmp->padre;
                    rotacion_der(tmp);
                }
                tmp->padre->color=false;
                tmp->padre->padre->color=true;
                rotacion_izq(tmp->padre->padre);
            }
        }
        if(tmp==this->raiz){
            break;
        }
    }
    this->raiz->color=false;
}
void Arbol_RB::rb_transplante(nodo_red_black* u, nodo_red_black* v) {
    if(u->padre == nullptr){
        this->raiz = v;
    }
    else if(u == u->padre->izq){
        u->padre->izq = v;
    }
    else{
        u->padre->der = v;
    }
    v->padre = u->padre;
}
nodo_red_black* Arbol_RB::minimo(nodo_red_black* tmp) {
    while (tmp->izq != nullptr) {
      tmp = tmp->izq;
    }
    return tmp;
}
void Arbol_RB::eliminar(int n){
    if(this->raiz==nullptr)
        return;
    nodo_red_black *alf,*bet,*tmp=this->raiz;
    while(tmp!=nullptr){
        if(tmp->valor==n){
            break;
        }
        else if(tmp->valor>n){
            tmp=tmp->izq;
        }
        else{
            tmp=tmp->der;
        }
    }
    if(tmp==nullptr)
        return;
    if(tmp->izq==nullptr&&tmp->der==nullptr){
        if(tmp->padre!=nullptr){
            if(tmp->padre->der==tmp){
                tmp->padre->der=nullptr;
            }
            else{
                tmp->padre->izq=nullptr;
            }
        }
        delete tmp;
        return;
    }
    alf=tmp;
    int color_original=alf->color;
    if (tmp->izq == nullptr) {
        bet = tmp->der;
        rb_transplante(tmp, tmp->der);
    }
    else if(tmp->der == nullptr) {
        bet = tmp->izq;
        rb_transplante(tmp, tmp->izq);
    }
    else {
        alf = minimo(tmp->der);
        color_original = alf->color;
        bet = alf->der;
        if (alf->padre == tmp) {
            bet->padre = alf;
        }
        else {
            rb_transplante(alf, alf->der);
            alf->der = tmp->der;
            alf->der->padre = alf;
        }
        rb_transplante(tmp, alf);
        alf->izq = tmp->izq;
        alf->izq->padre = alf;
        alf->color = tmp->color;
    }
    delete tmp;
    if (color_original == 0) {
        ordenar_eliminar(bet);
    }
}
void Arbol_RB::ordenar_eliminar(nodo_red_black*tmp){
    nodo_red_black* s;
    while (tmp != this->raiz && tmp->color == 0) {
        if (tmp == tmp->padre->izq) {
            s = tmp->padre->der;
            if (s->color == true) {
                s->color = false;
                tmp->padre->color = true;
                rotacion_izq(tmp->padre);
                s = tmp->padre->der;
            }
            if (s->izq->color == false && s->der->color == false) {
                s->color = true;
                tmp = tmp->padre;
            }
            else{
                if (s->der->color == false) {
                    s->izq->color = false;
                    s->color = true;
                    rotacion_der(s);
                    s = tmp->padre->der;
                }
                s->color = tmp->padre->color;
                tmp->padre->color = 0;
                s->der->color = 0;
                rotacion_izq(tmp->padre);
                tmp = this->raiz;
            }
        }
        else {
            s = tmp->padre->izq;
            if(s->color == true){
                s->color = false;
                tmp->padre->color = true;
                rotacion_der(tmp->padre);
                s = tmp->padre->izq;
            }
            if(s->der->color == false&& s->der->color == false){
                s->color = true;
                tmp = tmp->padre;
            }
            else{
                if (s->izq->color == false) {
                    s->der->color = false;
                    s->color = true;
                    rotacion_izq(s);
                    s = tmp->padre->izq;
                }

                s->color = tmp->padre->color;
                tmp->padre->color = false;
                s->izq->color = false;
                rotacion_der(tmp->padre);
                tmp = this->raiz;
            }
        }
    }
    tmp->color = false;
}
void Arbol_RB::rotacion_izq(nodo_red_black* tmp){
    nodo_red_black* tmp2=tmp->der;
    tmp->der=tmp2->izq;
    if(tmp2->izq!=nullptr){
        tmp2->izq->padre=tmp;
    }
    tmp2->izq=tmp;
    tmp2->padre=tmp->padre;
    if(tmp2->padre!=nullptr){
        if(tmp2->padre->izq==tmp)
            tmp2->padre->izq=tmp2;
        else
            tmp2->padre->der=tmp2;
    }
    else{
        this->raiz=tmp2;
    }
    tmp->padre=tmp2;
}
void Arbol_RB::rotacion_der(nodo_red_black*tmp){
    nodo_red_black* tmp2=tmp->izq;
    tmp->izq=tmp2->der;
    if(tmp2->der!=nullptr){
        tmp2->der->padre=tmp;
    }
    tmp2->der=tmp;
    tmp2->padre=tmp->padre;
    if(tmp2->padre!=nullptr){
        if(tmp2->padre->izq==tmp)
            tmp2->padre->izq=tmp2;
        else
            tmp2->padre->der=tmp2;
    }
    else{
        this->raiz=tmp2;
    }
    tmp->padre=tmp2;
}
nodo_red_black* Arbol_RB::devol_raiz(){
    return this->raiz;
}
void Arbol_RB::imprimir(nodo_red_black*tmp){
    if(tmp!=nullptr){
        cout<<tmp->valor<<": ";
        if(tmp->izq!=nullptr)
            cout<<tmp->izq->valor<<" ";
        else
            cout<<"* ";
        if(tmp->der!=nullptr)
            cout<<tmp->der->valor;
        else
            cout<<"*";
        cout<<endl;
        imprimir(tmp->izq);
        imprimir(tmp->der);
    }
}
Arbol_RB::~Arbol_RB()
{}
int main(){
    Arbol_RB rb1;
    rb1.anadir(33);
    rb1.anadir(13);
    rb1.anadir(53);
    rb1.anadir(11);
    rb1.anadir(41);
    rb1.anadir(21);
    rb1.anadir(61);
    rb1.anadir(15);
    rb1.anadir(31);
    rb1.imprimir(rb1.devol_raiz());
    rb1.anadir(20);
    cout<<"CAMBIOS"<<endl;
    rb1.imprimir(rb1.devol_raiz());
    return 0;
}