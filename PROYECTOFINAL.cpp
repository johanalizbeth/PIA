#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <limits>

using namespace std;

struct Ticket {
    string estatus; //automatico
    int numero; // automatico 
    string vendedor; //manual
    string fecha; //manual
    string articulos; //manual
    double precioArticulos; //manual
    int numArticulos; //manual
    double totalArticulos; //manual
    double descuentos; //manual
    double propina; //manual
    double impuesto; //automatico
    double total; //automatico
    string razonSocial; //manual
};
Ticket tickets[100];

int validarEntero();
double validarDouble();

void imprimirTicket(const Ticket& ticket) {
    cout << "==============================" << endl;
    cout << "Razon social: " << ticket.razonSocial << endl;
    cout << "-----------------------------" << endl;
    cout << "Numero de Ticket: " << ticket.numero << endl;
    cout << "Nombre del Vendedor: " << ticket.vendedor << endl;
    cout << "Fecha: " << ticket.fecha << endl;
    cout << "-----------------------------" << endl;
    cout << "Lista de Articulos: " << endl << ticket.articulos << endl;
    cout << "-----------------------------" << endl;
    cout << fixed << setprecision(2);
    cout << "Numero Total de Articulos: " << ticket.numArticulos << endl;
    cout << "Precio Total de Articulos: $" << ticket.totalArticulos << endl;
    cout << "Descuentos o Promociones: %" << ticket.descuentos << endl;
    cout << "Propina: $" << ticket.propina << endl;
    cout << "Impuesto: $" << ticket.impuesto << endl;
    cout << "-----------------------------" << endl;
    cout << "Total: $" << ticket.total << endl;
    cout << "Estatus: " << ticket.estatus << endl;
    cout << "==============================" << endl;
}
void modificarOrden(Ticket tickets[], int numTickets) {
    cout << "Modificar Orden\n";
    cout << "Ingrese el numero del ticket que desea modificar: ";
    int numTicket;
    numTicket = validarEntero();


    if (numTicket >= 1 && numTicket <= numTickets) {
        Ticket& ticketAModificar = tickets[numTicket - 1];

        cout << "Informacion actual del Ticket #" << numTicket << ":\n";
        imprimirTicket(ticketAModificar);

        cout << "Ingrese la nueva lista de articulos: ";
        cin.ignore();
        getline(cin, ticketAModificar.articulos);

        cout << "Ingrese los nuevos precios de los articulos:\n";
        ticketAModificar.totalArticulos = 0.0;

        for (int i = 0; i < ticketAModificar.numArticulos; i++) {
            double precio;
            cout << "Nuevo precio del Articulo " << i + 1 << ": $";
            precio = validarDouble();
            ticketAModificar.totalArticulos += precio;
        }

        double iva = 0.16;
        double descuento = ticketAModificar.totalArticulos * (ticketAModificar.descuentos / 100.0);
        double propina = ticketAModificar.totalArticulos * (ticketAModificar.propina / 100.0);
        ticketAModificar.impuesto = ticketAModificar.totalArticulos * iva;
        ticketAModificar.total = ticketAModificar.totalArticulos - descuento + propina + ticketAModificar.impuesto;

        cout << "Modificacion exitosa del Ticket #" << numTicket << ".\n";
    }
    else {
        cout << "Numero de ticket no válido.\n";
    }
}

void eliminarOrden();

void crearTXT();

void cancelarOrden();




int main()
{

    int numTickets = 0;
    int opcion;

    do {
        cout << "\nMenu de Opciones:\n";
        cout << "1. Alta de Ordenes\n";
        cout << "2. Modificar Orden\n";
        cout << "3. Eliminar o Cancelar Orden\n";
        cout << "4. Lista de Ordenes\n";
        cout << "5. Limpiar Pantalla\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cout << "\n";

        opcion = validarEntero();
        switch (opcion) {
        case 1: { // Alta de Ordenes
            if (numTickets < 100) {
                cout << "Ticket #" << (numTickets + 1) << endl;
                tickets[numTickets].numero = numTickets + 1;
                tickets[numTickets].estatus = "Pendiente";



                cin.ignore();
                cout << "Ingrese la razon social" << endl;
                getline(cin, tickets[numTickets].razonSocial);

                cout << "Nombre del Vendedor: ";
                getline(cin, tickets[numTickets].vendedor);

                cout << "Fecha: ";
                getline(cin, tickets[numTickets].fecha);

                cout << "Lista de Articulos: ";
                getline(cin, tickets[numTickets].articulos);

                cout << "Numero de Articulos: ";
                cin >> tickets[numTickets].numArticulos;


                tickets[numTickets].totalArticulos = 0.0;

                cout << "Ingrese los precios de los articulos:" << endl;
                for (int i = 0; i < tickets[numTickets].numArticulos; i++) {
                    double precio;
                    cout << "Precio del Articulo " << i + 1 << ": $";
                    precio = validarDouble();

                    while (precio < 0) {
                        cout << "Por favor, ingrese un precio no negativo: $";
                        precio = validarDouble();
                    }

                    tickets[numTickets].totalArticulos += precio;
                    tickets[numTickets].precioArticulos = precio;
                    tickets[numTickets].articulos += "Articulo " + to_string(i + 1) + ": $" + to_string(precio) + "\n";
                }

                cout << "Descuentos o Promociones: %";
                tickets[numTickets].descuentos = validarDouble();

                cout << "Propina (opcional, ingrese 0 si no desea propina): $";
                 tickets[numTickets].propina = validarDouble();

                double iva = 0.16;
                double descuento = tickets[numTickets].totalArticulos * (tickets[numTickets].descuentos / 100.0);
                double propina = tickets[numTickets].totalArticulos * (tickets[numTickets].propina / 100.0);
                tickets[numTickets].impuesto = tickets[numTickets].totalArticulos * iva;
                tickets[numTickets].total = tickets[numTickets].totalArticulos - descuento + propina + tickets[numTickets].impuesto;


                numTickets++;
            }
            else {
                cout << "No se pueden agregar mas tickets. Ha alcanzado el limite.\n";
            }
        }break;
        case 2: { // Modificar Orden
            if (numTickets > 0) {
                modificarOrden(tickets, numTickets);
            }
            else {
                cout << "No hay tickets para modificar.\n";
            }
        }break;

        case 3: { // Eliminar o Cancelar Orden
            if (numTickets > 0) {
                do {
                    int opcion;
                    cout << "1. Eliminar ticket" << endl;
                    cout << "2. Cancelar ticket" << endl;
                    cout << "3. Salir" << endl;
                    cout << "Seleccione una opcion" << endl;
                    opcion = validarEntero();
                    switch (opcion) {
                    case 1: cout << "Selecciono eliminar orden" << endl;
                        eliminarOrden();
                        break;
                    case 2: cout << "Selecciono cancelar orden" << endl;
                        cancelarOrden();
                        break;
                    case 3: break;
                    }
                } while (opcion != 3);
            }break;
        case 4: { // Lista de Ordenes
            cout << "Lista de Tickets:\n";
            for (int i = 0; i < numTickets; ++i) {
                cout << "Ticket #" << tickets[i].numero << endl;
                imprimirTicket(tickets[i]);
            }
        }break;
        case 5: { // Limpiar Pantalla
            (void)system("clear");
        }break;
        case 6: // Salir
            crearTXT();

            cout << "Saliendo del programa. Hasta luego!\n";
            return 0;
        default:
            cout << "Opcion no valida. Intente de nuevo.\n";
            break;
        }
        }


    } while (opcion != 6);
    return 0;
}

void crearTXT() {
    ofstream archivo("compras.txt");
    for (int i = 0; i < 100; i++) {
        if (!tickets[i].vendedor.empty()) {
            archivo << "==============================" << endl;
            archivo << "Razon social: " << tickets[i].razonSocial << endl;
            archivo << "-----------------------------" << endl;
            archivo << "Numero de Ticket: " << tickets[i].numero << endl;
            archivo << "Nombre del vendedor: " << tickets[i].vendedor << endl;
            archivo << "Fecha: " << tickets[i].fecha << endl;
            archivo << "-----------------------------" << endl;
            archivo << "Lista: " << tickets[i].articulos << endl;
            archivo << "-----------------------------" << endl;
            archivo << "Numero Total de Articulos: " << tickets[i].numArticulos << endl;
            archivo << "Precio total de articulos: $ " << tickets[i].totalArticulos << endl;
            archivo << "Descuento: % " << tickets[i].descuentos << endl;
            archivo << "Impuesto: " << tickets[i].impuesto << endl;
            archivo << "-----------------------------" << endl;
            archivo << "Total: " << tickets[i].total << endl;
            archivo << "Estatus: " << tickets[i].estatus << endl;
            archivo << "==============================" << endl;
        }
    }
    archivo.close();
}

void eliminarOrden() {
    int numeroTicket;
    cout << "Ingrese el numero de ticket de la orden a eliminar: ";
    numeroTicket = validarEntero();

    for (int i = 0; i < 100; i++) {
        if (tickets[i].numero == numeroTicket) {
            tickets[i] = {}; // Eliminar orden
            cout << "Orden eliminada exitosamente." << endl;
            return;
        }
    }
    cout << "No se encontró la orden con el número de ticket ingresado." << endl;
}

void cancelarOrden() {
    int numeroTicket;
    cout << "Ingrese el numero de ticket de la orden a cancelar: ";
    numeroTicket = validarEntero();

    for (int i = 0; i < 100; i++) {
        if (tickets[i].numero == numeroTicket) {
            tickets[i].estatus = "cancelado"; // Cambiar estatus de la orden a cancelado
            cout << "Orden cancelada exitosamente." << endl;
            return;
        }
    }
    cout << "No se encontró la orden con el número de ticket ingresado." << endl;
}

int validarEntero() {
    int numero;
    while (true) {
        cout << "Ingrese un número entero: ";
        cin >> numero;

        // Verifica si la entrada es válida
        if (cin.fail()) {
            cout << "Error" << endl;
            cin.clear();  // Limpia el indicador de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta la entrada incorrecta
        }
        else {
            break;  // Sal del bucle si la entrada es válida
        }
    }
    return numero;
}
double validarDouble() {
    double numero;
    while (true) {
        cout << "Ingrese un número decimal: ";
        cin >> numero;

        // Verifica si la entrada es válida
        if (cin.fail()) {
            cout << "Error: Ingrese un número decimal válido." << endl;
            cin.clear();  // Limpia el indicador de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta la entrada incorrecta
        }
        else {
            break;  // Sal del bucle si la entrada es válida
        }
    }
    return numero;
}