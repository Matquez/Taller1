// Taller1.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafxr.h"
#include "ListaAstronautas.h"
#include "ListaNave.h"
#include "ListaPlaneta.h"
#include "Suministro.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include  <algorithm>
#include <cctype>
using namespace std;
/*
Método para realizar la carga del fichero de astronautas segun los requerimientos del programa
*/
void cargarAstronautas(ListaAstronautas&astronautas) {
	string line;
	ifstream archivo("Astronautas.txt");
	if (archivo.is_open()) {
		while (getline(archivo, line)) {

			//variables para la lectura del fichero
			stringstream lineaS(line);
			string campo;

			//variables para la creacion del objeto
			string nombre;
			int edad = 0;
			int experiencia = 0;
			string nombreNave;

			//cantidad de comas: cantidad de elementos -1
			int comas = count(line.begin(), line.end(), ',');
			
			//recorrer la linea leida para separarla por cada coma en campos
			for (int i = 0; i <= comas; i++) {
				getline(lineaS, campo, ',');

				if (campo.empty() && i < 3) {//cuando esta vacio un elemento obligatorio
					//cout << "-campo vacio-" << endl;
				}
				else {
					if (i == 0) {
						nombre = campo;
					}
					if (i == 1) {
						edad = stoi(campo);
					}
					if (i == 2) {
						experiencia = stoi(campo);
					}
					if (i == 3) {
						nombreNave = campo;
					}
				}
			}
			if (!nombre.empty() && edad > 0 && experiencia > 0 && !nombreNave.empty()) {

				Astronauta astroAux = Astronauta(nombre, edad, experiencia, nombreNave);
				if (astronautas.agregarAstronauta(astroAux)) {
					cout << astroAux.getNombre() << "FUNCIONA :D" << endl;
				}				
			}
			else {
				if (!nombre.empty() && edad > 0 && experiencia > 0) {
					Astronauta astroAux = Astronauta(nombre, edad, experiencia);
					if (astronautas.agregarAstronauta(astroAux)) {
						cout << astroAux.getNombre() << "FUNCIONA :D sin NAVE" << endl;
					}
				}
			}
			
		}
	}
	else {
		cout << "El archivo no se encuentra, por favor revise" << endl;
	}
	//archivo.close();//se cierra el archivo
}
/*método que realiza la carga de datos del archivo Naves.csv
para su posterior uso. lectura segun los requerimientos
*/
void cargarNaves(ListaNave&naves) {
	string line;
	ifstream archivo("Naves.csv");
	if (archivo.is_open()) {//si existe el archivo
		while (getline(archivo, line)) {

			//variables para la lectura del fichero
			stringstream lineaS(line);
			string campo;
			
			//cantidad de comas: cantidad de elementos -1
			int comas = count(line.begin(), line.end(), ',');
			int cantSum = (comas - 2)/2;//cantidad de suministros

			//variables para la creacion del objeto
			string nombre;
			string destino;
			int cantTripulantes = 0;
			string* nombre_sum = new string[cantSum];
			int* cantidad_sum = new int[cantSum];
			int n = 0;
			while (n< cantSum) // se llena la lista de objetos vacios
			{
				cantidad_sum[n] = 0;
				nombre_sum[n] = "";
				++n;
			}
			n = 0;
			
			//recorrer la linea leida para separarla en campos
			for (int i = 0; i <= comas; i++) {
				getline(lineaS, campo, ',');

				if (campo.empty() && i != 1) {//cuando esta vacio un elemento obligatorio
					//cout << "-campo obligatorio vacio-" << endl;
				}
				else {//entra a cada if dependiendo del dato correspondiente
					if (i == 0) {
						nombre = campo;
						
					}
					if (i == 1) {
						destino = campo;
					}
					if (i == 2) {
						cantTripulantes = stoi(campo);
					}
					if (i > 2) {
						if (i%2 != 0) {	//cuando es impar corresponde a nombre del suministro							
							nombre_sum[n] = campo;
						}	else {		//cuando es par es la cantidad de dicho suministro					
							cantidad_sum[n] = stoi(campo);
							++n;//se suma aqui para cambiar de suministro luego de llegar a la cantidad
						}
					}
					

				}
			}
			
			//se verifica que los punteros tengan datos
			bool ver_Sum = true;
			for (int c = 0; c < cantSum; ++c) {
				if (nombre_sum[c].empty() || cantidad_sum[c] == 0) {
					ver_Sum = false;
				}
			}
			
			//se intenta crear y agregar Nave  a la lista		
			if (!nombre.empty() && !destino.empty() && cantTripulantes > 0 && ver_Sum) {//cuando tiene todos los datos
				
				Nave nave = Nave(nombre, destino, cantTripulantes, nombre_sum, cantidad_sum, cantSum);
				
				if (naves.agregarNave(nave)) {
					//cout << nave.getNombresSum() << "FUNCIONA " << endl;//MENSAJE PARA BORRAR
				}
				
			}
			else {
				if (!nombre.empty() && cantTripulantes > 0 && ver_Sum) {//cuando falta destino
					Nave nave = Nave(nombre, cantTripulantes, nombre_sum, cantidad_sum, cantSum);
					naves.agregarNave(nave);
				}
				else {
					//cout << "NO FUNCIONA :(" << endl;
				}
			}
		}
	}
	else {
		cout << "El archivo no se encuentra, por favor revise" << endl;
	}
	archivo.close();//se cierra el archivo
}

/*
Método de lectura de datos de los planetas segun los requerimientos especificados
*/
void cargarPlanetas(ListaPlaneta&planetas) {

	string line;//linea de lectura
	ifstream archivo("Planetas.csv");//archivo a leer

	if (archivo.is_open()) {//si existe el archivo
		while (getline(archivo, line)) {

			//variables para la lectura del fichero
			stringstream lineaS(line);
			string campo;

			//cantidad de comas: cantidad de elementos -1
			int comas = count(line.begin(), line.end(), ',');
			
			int cantReq = (comas - 2) / 2;//Cantidad de requirimientos

			//variables para la creacion del objeto
			string nombre;
			double distancia = 0;
			bool habitado = false;
			string habitado_ver;//verificador que en la casilla de habitado, esta no este vacia
			string* nombre_req = new string[cantReq];
			int* cantidad_req = new int[cantReq];

			int n = 0;
			while (n< cantReq) // se llena la lista de objetos vacios
			{				
				cantidad_req[n] = 0;
				nombre_req[n] = "";
				++n;
			}
			n = 0;//se vuelve a 0 para que corresponda a la posicion de los punteros

			//recorrer la linea leida para separarla en campos
			for (int i = 0; i <= comas; i++) {
				getline(lineaS, campo, ',');

				if (campo.empty() && i != 1) {//cuando esta vacio un elemento obligatorio
					//cout << "--campo obligatorio vacio--" << endl;
				}
				else {
					//cuando es el i campo
					if (i == 0) {
						nombre = campo;
					}
					if (i == 1) {
						distancia = stod(campo);
					}
					if (i == 2) {
						habitado_ver = campo;//verificador que este vacio o no

						//cuando indica si esta o no habitado
						if (campo == "No" || campo =="NO"||campo=="no") {
							habitado = false;
						}
						else {
							if(campo =="Si"||campo=="sí"||campo=="SI"){
								habitado = true;
							}
						}
					}
					if (i > 2) {//cuando se llega a la lista de requerimientos
						if (i%2 != 0) {//igual que en naves							
							nombre_req[n] = campo;
						}
						else {							
							cantidad_req[n] = stoi(campo);
							++n;//se suma para pasar al siguiente requirimiento
						}

					}

					
				}
			}
			bool ver_Sum = true;
			//se verifica que los punteros de requirimientos no esten vacios
			for (int c = 0; c < cantReq; ++c) {
				if (nombre_req[c].empty() || cantidad_req[c] == 0) {
					ver_Sum = false;
				}
			}
			//cuando no hay datos nulos o vacios
			if (!nombre.empty() && distancia>0 && !habitado_ver.empty() && ver_Sum) {
				
				//se crea instancia de planeta
				
				Planeta planeta = Planeta(nombre, distancia, habitado, nombre_req, cantidad_req, cantReq);
				cout << "problema despues de esto" << endl;
				// se agrega a la lista
				if (planetas.agregarPlaneta(planeta)) {
					//cout << planeta.getNombreReq() << "FUNCIONA ALTIRO" << endl;
				}				
			}
			
		}
	}
	else {
		cout << "El archivo no se encuentra, por favor revise" << endl;
	}
	archivo.close();//se cierra el archivo
}



void cargarDatos() {
	string line;
	//ifstream myfile("example.txt");

}

void Menu() {
	int elegir;
	string elegirAgregar = "z";
	string elegirManejar = "z";

	cout << "1) Agregar nuevo dato" << endl;
	cout << "2) Listado de naves" << endl;
	cout << "3) Listado de astronautas ordenado" << endl;
	cout << "4) Manejar astronautas" << endl;
	cout << "5) Estado de mision" << endl;
	cout << "6) Limpiar datos corruptos" << endl;
	cout << "7) Crear archivos" << endl;
	cout << "8) Salir" << endl;
	cin >> elegir;
	
	while ( elegir > 8 || elegir < 0) {
		cout << "1) Agregar nuevo dato" << endl;
		cout << "2) Listado de naves" << endl;
		cout << "3) Listado de astronautas ordenado" << endl;
		cout << "4) Manejar astronautas" << endl;
		cout << "5) Estado de mision" << endl;
		cout << "6) Limpiar datos corruptos" << endl;
		cout << "7) Crear archivos" << endl;
		cout << "8) Salir" << endl;
		cin >> elegir;
	}
	switch (elegir) {
	case 1:
		int numeroParaAgregar;
		while (elegirAgregar != "a" && elegirAgregar != "A" && elegirAgregar != "b" && elegirAgregar != "B" && elegirAgregar != "c" && elegirAgregar != "C") {
			cout << "a. Astronauta" << endl;
			cout << "b. Nave" << endl;
			cout << "c. Planeta" << endl;
			cin >> elegirAgregar;
		}
		if (elegirAgregar == "a" || elegirAgregar == "A") {
			numeroParaAgregar = 1;
		}
		else if (elegirAgregar == "b" || elegirAgregar == "B") {
			numeroParaAgregar = 2;
		}
		else if (elegirAgregar == "c" || elegirAgregar == "C") {
			numeroParaAgregar = 3;
		}
		switch (numeroParaAgregar) {
		case 1:
			cout << "Agregar astronauta" << endl;
			break;
		case 2:
			cout << "Agregar nave" << endl;
			break;
		case 3:
			cout << "Agregar planeta" << endl;
			break;
		}
	case 2:
		cout << "Listado de nave" << endl;
		break;
	case 3:
		cout << "Listado de astronautas ordenado" << endl;
		break;
	case 4:
		int numeroManejar;
		while (elegirManejar != "a" && elegirManejar != "A" && elegirManejar != "b" && elegirManejar != "B") {
			cout << "a. Agregar astronauta a una nave" << endl;
			cout << "b. Mover astronauta" << endl;
			cin >> elegirManejar;
		}
		if (elegirManejar == "a" || elegirManejar == "A") {
			numeroManejar = 1;
		}
		else if (elegirManejar == "b" || elegirManejar == "B") {
			numeroManejar = 2;
		}
		switch (numeroManejar) {
			case 1:
				cout << "Agregar astronauta a una nave" << endl;
				break;
			case 2:
				cout << "Mover astronauta" << endl;
				break;
		}
		break;
	case 5:
		cout << "Estado de mision" << endl;
		break;
	case 6:
		cout << "Limpiar datos corruptos" << endl;
		break;
	case 7:
		cout << "Crear archivos" << endl;
		break;
	case 8:
		cout << "salir" << endl;
		break;
	}
}
void estadoMision(ListaNave naves, ListaPlaneta planetas, ListaAstronautas astronautas){

	for (int i = 0; i < naves.getCant_Naves(); i++) {//cada nave

		if (!naves.getLista()[i].getDestino().empty()) {//cuando tienen destino fijado
			int contador = 0;
			int numero_suministros = naves.getLista()[i].getNumDeSuministro();
			for (int s = 0; s < numero_suministros; s++) {//cada suministro de nave con destino

				Planeta planeta_escogido = planetas.buscarPlaneta(naves.getLista()[i].getDestino());
				for (int r = 0; r < planeta_escogido.getNumDeRequerimientos(); r++) {//se recorren cada requerimiento

					if ((naves.getLista()[i].getNombresSum()[s] == planeta_escogido.getNombreReq()[r])//cuando la nave presenta los requermientos del planeta
						&& (naves.getLista()[i].getCantidadSum()[s] >= planeta_escogido.getCantReq()[r])) {//cuando presenta la cantidad necesaria
						++contador;	

					}	
					cout << contador<<endl;
				}						
			}
			if (contador == naves.getLista()[i].getNumDeSuministro()) {//se cumplen los tres requerimientos del planeta

				if (planetas.buscarPlaneta(naves.getLista()[i].getDestino()).gethabitado()) {//el planeta esta habitado
					cout << naves.getLista()[i].getNombre() << endl;
				}
				else {
					//Si la cantidad de astronautas en esa nave es mayor o igual a la mitad de la cantidad maxima de tripulantes
					if(astronautas.cantAstronautas_Nave(naves.getLista()[i].getNombre()) >= (naves.getLista()[i].getCantMaxTrip()+1)/2 ){
						cout << naves.getLista()[i].getNombre() << endl;
					}
					else {
						cout << "...No hay ninguna nave lista para el despegue..." << endl;
					}
				}
			}		
		}
		else {
			//cout << naves.getLista()[i].getNombre() << "Sin DESTINO" << endl;
		}
	}
}
void limpiarDatos(ListaNave naves, ListaPlaneta planetas) {
	//Lista de Naves
	ofstream archivoN("N_Naves.csv");
	for (int i = 0; i < naves.getCant_Naves();i++) {
		archivoN << naves.getLista()[i].getNombre();
		archivoN << "," << naves.getLista()[i].getDestino();
		archivoN << "," << naves.getLista()[i].getCantMaxTrip();
		for (int n = 0; n < naves.getLista()[i].getNumDeSuministro(); ++n) {
			archivoN << "," << naves.getLista()[i].getNombresSum()[n];
			archivoN << "," << naves.getLista()[i].getCantidadSum()[n];
		}
		archivoN << endl;
	}
	archivoN.close();
	ofstream archivoP("N_Planetas.csv");
	for (int i = 0; i < planetas.getCant_planetas(); i++) {
		archivoP << planetas.getLista()[i].getNombre();
		archivoP << "," << planetas.getLista()[i].getDistancia();
		archivoP << "," << planetas.getLista()[i].gethabitado();
		for (int n = 0; n < naves.getLista()[i].getNumDeSuministro(); ++n) {
			archivoP << "," << planetas.getLista()[i].getNombreReq()[n];
			archivoP << "," << planetas.getLista()[i].getCantReq()[n];
		}
		archivoP << endl;
	}
	archivoP.close();
	
}


int main()
{
	ListaAstronautas astronautas = ListaAstronautas(500);
	ListaNave naves = ListaNave(500);
	ListaPlaneta planetas = ListaPlaneta(500);
	//cargarDatos();
	cargarAstronautas(astronautas);
	cargarNaves(naves);
	cargarPlanetas(planetas);
	Astronauta astronauta = Astronauta("Maikol", 19, 19);
	
	cout << astronautas.getLista()->getNombre() << endl;
	cout << naves.getLista()->getNombre() << endl;
	cout << naves.getLista()->getNombresSum() << endl;
	cout << planetas.getLista()->getNombreReq() << endl;
	cout << planetas.getLista()->getCantReq() << endl;
	cout << astronautas.getCantElementos() << endl;
	astronautas.agregarAstronauta(astronauta);
	cout << astronautas.getCantElementos() << endl;
	cout << naves.getCant_Naves() << endl;
	cout << "------------------------" << endl,
	cout << astronautas.cantAstronautas_Nave(naves.getLista()->getNombre()) << endl;
	cout << planetas.buscarPlaneta("Marte").getNombre() << "WOW" <<endl;
	estadoMision(naves, planetas, astronautas);
	limpiarDatos(naves, planetas);
	//Menu();
	system("PAUSE");
	return 0;
}



