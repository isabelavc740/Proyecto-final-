#include<iostream>
using namespace std;

int const filas=4; 
int const columnas=5;

int valorRecaudado(string puertoCarga[filas][columnas],string nombreP[filas]);
int filaPesada(int pesos[filas][columnas],int filas,int columnas);
int columna(int pesos[filas][columnas],int filas,int columnas);
float promedioPeso(int pesos[filas][columnas], bool disponibilidad[filas][columnas]);
int cantidadTipoArticulo(string tipoArticulo[filas][columnas], string articulo);
float promedioPesoPuerto(int pesos[filas][columnas],string puertoCarga[filas][columnas],string puertoBuscado);
string nombreEmpresaContenedorPesado(int pesos[filas][columnas], string marcas[filas][columnas]);
int contenedorLiviano(int pesos[filas][columnas]);

void limpiarMatriz(bool disponibilidad[filas][columnas],int pesos[filas][columnas]);
void imprimirMatrizTexto(string matriz[filas][columnas]);
void imprimirMatrizEnteros(int matriz[filas][columnas]);
void mostrarDisponibles(bool disponibilidad[filas][columnas]);
void llenarMatriz(bool disponibilidad[filas][columnas],string marcas[filas][columnas],int pesos[filas][columnas],string puertoCarga[filas][columnas],string tipoArticulo[filas][columnas]);
void porcentajeOcupacion(int acumuladorPuertos);
void imprimirCantidadContenedores(bool disponibilidad[filas][columnas]);
void burbuja(string nombreP[filas],int npuertos[filas]);
void listadoMarcasEconomicaYpremium(string marcas[filas][columnas]);
int main(){
	int cantidadPuertos=0;        
	cout<<"Bienvenido al barco de carga"<<endl;
	cout<<"Ingrese la cantidad de puertos"<<endl;
	cin>>cantidadPuertos;
	string nombreP[cantidadPuertos];
	for(int i=0;i<cantidadPuertos;i++){
	cout<<"Indique el nombre del puerto"<<i<<endl;
    cin>>nombreP[i];
    }
	
	bool disponibilidad[filas][columnas];
	string marcas[filas][columnas];
	string puertoCarga[filas][columnas];
	string tipoArticulo[filas][columnas];
	int pesos[filas][columnas];
	limpiarMatriz(disponibilidad,pesos);
	bool coordenadaFC=0;
	int acumuladorPuertos=0;
	int npuertos[cantidadPuertos];
	
	for(int i=0;i<cantidadPuertos;i++){
		cout<<"Ingrese la cantidad de contenedores en el puerto "<<nombreP[i]<<endl;
		cin>>npuertos[i];
		acumuladorPuertos=acumuladorPuertos+npuertos[i];
		for(int j=1;j<=npuertos[i];j++){
			cout<<"Las coordenadas disponibles son "<<endl;
			mostrarDisponibles(disponibilidad);
			llenarMatriz(disponibilidad, marcas, pesos, puertoCarga, tipoArticulo);
		}	
	}
	porcentajeOcupacion(acumuladorPuertos);
	valorRecaudado(puertoCarga,nombreP);
	imprimirCantidadContenedores(disponibilidad);
	burbuja(nombreP,npuertos);
	listadoMarcasEconomicaYpremium(marcas);
	filaPesada(pesos,filas,columnas);
	contenedorLiviano(pesos);
	promedioPeso(pesos,disponibilidad);
	nombreEmpresaContenedorPesado(pesos,marcas);
	contenedorLiviano(pesos);
	
	
	cout<<"Matriz marcas"<<endl;
	imprimirMatrizTexto(marcas);
	cout<<"Matriz puerto carga"<<endl;
	imprimirMatrizTexto(puertoCarga);
	cout<<"Matriz tipo articulo"<<endl;
	imprimirMatrizTexto(tipoArticulo);
	
	cout<<"Matriz pesos"<<endl;
	imprimirMatrizEnteros(pesos);

	string articulo="";
	cout<<"ingrese el tipo de articulo que desea buscar"<<endl;
	cin>>articulo;
	cantidadTipoArticulo(tipoArticulo,articulo);
	string puertoBuscado="";
	cout<<"Ingrese el puerto que desea buscar"<<endl;
	cin>>puertoBuscado;
	promedioPesoPuerto(pesos,puertoCarga,puertoBuscado);
	
 return 0;
}

void limpiarMatriz(bool disponibilidad[filas][columnas],int pesos[filas][columnas]){
	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			disponibilidad[i][j]=1;	
			pesos[i][j]=0;
		}
	}
}
void mostrarDisponibles(bool disponibilidad[filas][columnas]){
	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			if(disponibilidad[i][j]==1){
				cout<<i<<","<<j<<endl;
			}
		}
        cout<<endl;
	}
}
void llenarMatriz(bool disponibilidad[filas][columnas],string marcas[filas][columnas],int pesos[filas][columnas],string puertoCarga[filas][columnas],string tipoArticulo[filas][columnas]){
    bool coordenadaFC=0;
    int coordenadasFila=0;
    int coordenadasColumna=0;
	while(coordenadaFC==0){
		cout<<"Ingrese coordenada fila"<<endl;
		cin>>coordenadasFila;
		cout<<"Ingrese coordenada columna"<<endl;
		cin>>coordenadasColumna;
		if(coordenadasFila>=0 && coordenadasColumna>=0 && coordenadasFila<filas && coordenadasColumna<columnas && disponibilidad[coordenadasFila][coordenadasColumna==1]){
			disponibilidad[coordenadasFila][coordenadasColumna]=0;
			coordenadaFC=1;
		}else{
			cout<<"coordenadas invalidas"<<endl;
		}
    }
	cout<<"Ingrese marca"<<endl;
	cin>>marcas[coordenadasFila][coordenadasColumna];
	cout<<"Ingrese peso"<<endl;
	cin>>pesos[coordenadasFila][coordenadasColumna];
	cout<<"Ingrese puerto carga "<<endl;
	cin>>puertoCarga[coordenadasFila][coordenadasColumna];
	cout<<"Ingrese tipo de articulo"<<endl;
	cin>>tipoArticulo[coordenadasFila][coordenadasColumna];
	
}
void porcentajeOcupacion(int acumuladorPuertos){
	float porcentajeocu=0.0;
	porcentajeocu=(acumuladorPuertos*100)/(filas*columnas);
	cout<<"El porcentaje de ocupacion es "<<porcentajeocu<<endl;
}
int valorRecaudado(string puertoCarga[filas][columnas],string nombreP[filas]){
	int valorTotal=0;
	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			if(puertoCarga[filas][columnas]==nombreP[i]){
				if((i==1||i==2)&&(j==1||j==2||j==3)){
					valorTotal=valorTotal+300;
				}else{
					valorTotal=valorTotal+100;
				}
			}
		}
	}
	cout<<"el valor total recaudado es "<<valorTotal<<endl;
	return valorTotal;
}
void imprimirCantidadContenedores(bool disponibilidad[filas][columnas]){
	int contador=0;
	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			if(disponibilidad[i][j]==0){
				contador=contador+1;
			}
		}
	}
	cout<<"La cantidad de contenedores en el barco es "<<contador<<endl;
}
void burbuja(string nombreP[filas],int npuertos[filas]){
	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
		    if(nombreP[i]<nombreP[j]){
		    	string auxnombreP=nombreP[i];
		    	nombreP[i]=nombreP[j];
		    	nombreP[j]=auxnombreP;
		    	
		    	int auxnpuertos=npuertos[i];
		    	npuertos[i]=npuertos[j];
		    	npuertos[j]=auxnpuertos;
			}
		}
	}
	cout<<"la cantidad de puertos de mayor a menor es "<<endl;
	for(int i=0;i<filas;i++){
		cout<<nombreP[i]<<":"<<npuertos[i]<<endl;
    }
	
}
void listadoMarcasEconomicaYpremium(string marcas[filas][columnas]){
	string marcaEconomica="";
	string marcaPremium="";
	for (int i=0;i<filas;i++){
        for (int j=0;j<columnas;j++){
            if (marcas[i][j] != "") {
                if ((i == 1 || i == 2) && (j == 1 || j == 2 || j == 3)) {
                    marcaPremium=marcaPremium+marcas[i][j];                 
                } else {
                    marcaEconomica=marcaEconomica+marcas[i][j];          
                }
            }
        }
    }
    cout<<"las marcas en la zona economica son "<<marcaEconomica<<endl;
    cout<<"Las marcas en la zona premium son "<<marcaPremium<<endl;
}
float promedioPeso(int pesos[filas][columnas], bool disponibilidad[filas][columnas]){
	int acumuladorPeso=0;
	int contadorContenedores=0;
	float promedioP=0.0;
	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			if(pesos[i][j]!=0){
				acumuladorPeso=acumuladorPeso+pesos[i][j];
				contadorContenedores=contadorContenedores+1;
			}
		}
	}
	promedioP=acumuladorPeso/contadorContenedores;
	cout<<"El promedio del peso de los contenedores que ocupan una celda es "<<promedioP<<endl;
	return promedioP;
}

int filaPesada(int pesos[filas][columnas],int filas,int columnas){
	int mayor=INT_MIN;
	int filaMayor=-1;
	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			if(pesos[i][j]>mayor){
				mayor=pesos[i][j];
				filaMayor=i;
			}
		}
	}
	cout<<"La fila mas pesada es "<<filaMayor<<endl;
	return filaMayor;
}
int columnaLiviana(int pesos[filas][columnas]){
	int menor=INT_MAX;
	int columnaMenor=-1;
	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			if(pesos[i][j]<menor){
				menor=pesos[i][j];
				columnaMenor=j;
			}
		}
	}
	cout<<"La columna menos pesada es "<<columnaMenor<<endl;
	return columnaMenor;
}
int cantidadTipoArticulo(string tipoArticulo[filas][columnas], string articulo){
	int contenedorArticulos=0;
	for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            if(tipoArticulo[i][j]==articulo){
                contenedorArticulos=contenedorArticulos+1;
            }
        }
    }
    cout<<"El articulo tiene "<<contenedorArticulos<<" contenedores"<<endl;
    return contenedorArticulos;
}
float promedioPesoPuerto(int pesos[filas][columnas],string puertoCarga[filas][columnas],string puertoBuscado){
	int contadorContenedores=0;
	int sumaPeso=0;
	float promedioPeso=0.0;
	for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            if(puertoCarga[filas][columnas]==puertoBuscado){
            	sumaPeso=sumaPeso+pesos[i][j];
            	contadorContenedores=contadorContenedores+1;
			}
        }
    }
    promedioPeso=sumaPeso/contadorContenedores;
    return promedioPeso;
}
string nombreEmpresaContenedorPesado(int pesos[filas][columnas], string marcas[filas][columnas]){
	string marcaPesada="";
	int pesoPesado=INT_MIN;
	for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            if(pesos[i][j]>pesoPesado){
            	pesoPesado=pesos[i][j];
            	marcaPesada=marcas[i][j];
			}
        }
    }
    cout<<"La empresa con el contenedor mas pesado es "<<marcaPesada<<"y su peso es "<<pesoPesado;
    return marcaPesada;
}
int contenedorLiviano(int pesos[filas][columnas]){
	int contenedorMenosPesado=INT_MAX;
	for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            if(pesos[filas][columnas]<contenedorMenosPesado){
            	contenedorMenosPesado=pesos[filas][columnas];
			}
        }
    }
    cout<<"El peso del contenedor mas liviano es "<<contenedorMenosPesado<<endl;
    return contenedorMenosPesado;
}




void imprimirMatrizTexto(string matriz[filas][columnas]){
	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			cout<<matriz[i][j]<<"\t";
		}
		cout<<endl;
	}
}
void imprimirMatrizEnteros(int matriz[filas][columnas]){
	for(int i=0;i<filas;i++){
		for(int j=0;j<columnas;j++){
			cout<<matriz[i][j]<<"\t";
		}
		cout<<endl;
	}
}

