#include <stdio.h>
#include <raylib.h>
#include <string.h>
#include <math.h>
#include "tinyexpr.h"
#include "butao.h"

char texto[20];

bool colar_clicado()
{
	strncpy(texto, GetClipboardText(), 19);
	return true;
}

bool ok_clicado()
{
	return true;
}

int main(void)
{
	InitWindow(1366, 720, "Metodo bisseção");
	Butao butao_colar, butao_ok;
	SetTargetFPS(60);
	Butao_init(&butao_ok, 512, 8, 64, 48, PURPLE, DARKPURPLE, &ok_clicado, "OK");
	Butao_init(&butao_colar, 584, 8, 112, 48, LIGHTGRAY, GRAY, &colar_clicado, "Colar");
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		
		// InputBox
		DrawRectangle(144, 8, 360, 48, LIGHTGRAY);
		DrawText("Função:", 8, 16, 36, BLACK);
		DrawText(texto, 152, 16, 36, BLACK);

		// Butão OK
		Butao_draw(&butao_ok);

		// Butao colar
		Butao_draw(&butao_colar);

		// Tiny Expr
		int err;
		double x, y;
		te_variable vars[] = {{"x", &x}};
		te_expr *funcao = te_compile(texto, vars, 1, &err);
		if (!funcao)
		{
			strncpy(texto, "ERR", 19);
		} else
		{
			for (double i = -10; i < 10; i += 0.005)
			{
				x = i;
				y = te_eval(funcao);
				if (392 - y * 10 > 64)
				{
					DrawPixel(360 + i * 10, 392 - y * 10, BLUE);
				}
			}
		}

		// Tabela
		if (funcao)
		{
			double a_n = 0, b_n = 2, x_n = 0, x_n_o = 1;
			DrawText("n\t\tAn\t\tBn\t\tXn\t\tf(Xn)\t\tE", 720, 64, 36, BLACK);
			for (size_t i = 0; fabs(x_n_o - x_n) > 0.001; i++)
			{
				x_n_o = x_n;
				x = a_n;
				double f_a = te_eval(funcao);

				x = b_n;
				double f_b = te_eval(funcao);
				x_n = fabs(b_n - a_n) / 2 + a_n;
				x = x_n;
				double f_x_n = te_eval(funcao);
				if (f_a * f_b > 0)
				{
					DrawText("Intervalo não satisfatório", 720, 100 + 48 * i, 24, BLACK);
					break;
				}
				
				if (f_x_n == 0)
				{
					DrawText(TextFormat("Xn = %.05f é a raiz exata", x_n), 720, 100 + 48 * i, 24, BLACK);
					break;
				}
				if (i == 0)
				{
					DrawText( TextFormat("%d\t\t%.05f\t\t%.05f\t\t%.05f\t\t%.05f\t\t---", i + 1, a_n, b_n, x_n, f_x_n),
						720, 100 + 48 * i, 24, BLACK);
				}
				else
				{
					DrawText( TextFormat("%d\t\t%.05f\t\t%.05f\t\t%.05f\t\t%.05f\t\t%.05f", i + 1, a_n, b_n, x_n, f_x_n,
						fabs(x_n_o - x_n)), 720, 100 + 48 * i, 24, BLACK);
				}
				if (f_a * f_x_n < 0)
				{
					b_n = x_n;
				}
				else if (f_a * f_x_n > 0)
				{
					a_n = x_n;
				}
			}
		}
		EndDrawing();
		te_free(funcao);
	}
	CloseWindow();
	return 0;
}