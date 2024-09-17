#ifndef BUTAO_H
#define BUTAO_H

#include <raylib.h>

typedef struct
{
	Rectangle rec;
	Color cor_fundo;
	Color cor_clicado;
	bool (*evento)();
	char *texto;
}
Butao;

void Butao_init(Butao *isto, int x, int y, int largura, int altura, Color cor_fundo, Color cor_clicado, bool (*evento)(), char *texto);

void Butao_draw(Butao *isto);

#endif