#include "butao.h"
#include <stdio.h>

void Butao_init(Butao *isto, int x, int y, int largura, int altura, Color cor_fundo, Color cor_clicado, bool (*evento)(), char *texto)
{
	isto->rec = (Rectangle) {.x = x, .y = y, .width = largura, .height = altura};
	isto->cor_fundo = cor_fundo;
	isto->cor_clicado = cor_clicado;
	isto->evento = evento;
	isto->texto = texto;
}

void Butao_draw(Butao *isto)
{
	DrawRectangleRec(isto->rec, isto->cor_fundo);
	if (CheckCollisionPointRec(GetMousePosition(), isto->rec)/*&& IsMouseButtonDown(MOUSE_BUTTON_LEFT)*/)
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			DrawRectangleRec(isto->rec, isto->cor_clicado);
		}
		
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			isto->evento();
		}
	}
	DrawText(isto->texto, isto->rec.x + 8, isto->rec.y + isto->rec.height / 6, 36, BLACK);
}