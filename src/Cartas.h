#ifndef CARTAS_H_
#define CARTAS_H_
enum CARTA {
		ATAQUEQUIMICO,
		AVIONRADAR,
		CARTABARCO,
		ATAQUEAEREO,
		REPITETURNO,
		TRESMINAS
};
class Cartas {
	//properties
private:
	CARTA carta;
	int cantidad;

public:
	//constructor
	Cartas(CARTA carta);

	//metodos
	CARTA getCarta();

	//propiedades
	int getCantidad();

	void setCantidad(int nuevaCantidad);
};

#endif /* CARTAS_H_ */
