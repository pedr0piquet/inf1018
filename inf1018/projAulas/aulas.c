/********************************************************************************
 * MIT License
 *
 * Copyright (c) 2021 Rafael Ribeiro de Carvalho
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************/

/* Version 2.0 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum wdays
{
	DOMINGO=0x0, SEGUNDA=0x1, TERCA=0x2, QUARTA=0x4, QUINTA=0x8, SEXTA=0x10, SABADO=0x20
};

const enum wdays dmap[7] = {DOMINGO, SEGUNDA, TERCA, QUARTA, QUINTA, SEXTA, SABADO};

typedef struct s_class
{
	char codigo_disciplina[8];
	char meeting_id[12];
	char meeting_pass[33];
	unsigned char dias;
	int time;

} Class;

int main(void)
{
	time_t t;
	struct tm tm;
	int n_classes = 7, i;
	int p_classesn = 0;
	Class *p_classes[2];
	Class *s_class = NULL;

	Class classes[7] = {
		{.codigo_disciplina="INF1010", .meeting_id="91389084106", .meeting_pass="TXRrYjczckhyN2VLQ1Vkc0xNNVo1dz09", .dias = (SEGUNDA | QUARTA), .time = 13},
		{.codigo_disciplina="MAT1162", .meeting_id="98031360222", .meeting_pass="RlIrS2RlM0hnbTlKSTdmRm5Xd0t4dz09", .dias = (SEGUNDA | QUARTA), .time = 15},
		{.codigo_disciplina="INF1018", .meeting_id="92135492554", .meeting_pass="OGdYSDFLbWxrbjdFbUJwdXg4V1hxZz09", .dias = (TERCA | QUINTA), .time = 11},
		{.codigo_disciplina="INF1631", .meeting_id="95009806246", .meeting_pass="Zlk0M2g0dGJ4a25JRU84bDFwWW5GQT09", .dias = (TERCA), .time = 13},
		{.codigo_disciplina="INF1631", .meeting_id="95558863178", .meeting_pass="M3JBbExOOGcrYUlubHg4K0NaYkx5dz09", .dias = (QUINTA), .time = 13},
		{.codigo_disciplina="INF1383", .meeting_id="93062647633", .meeting_pass="UTBCdFdnRVp2NVJrbXNlNXEveU1sQT09", .dias = (TERCA | QUINTA), .time = 15},
		{.codigo_disciplina="MAT1162", .meeting_id="92974716688", .meeting_pass="VVNCQm9NZzBOL2NOOFdzbVRqUm9sUT09", .dias = (SEXTA), .time = 15},
	};

	t = time(NULL);
	tm = *localtime(&t);

	for (i = n_classes-1; i >= 0; --i) {
		if (classes[i].dias & dmap[tm.tm_wday] && ((tm.tm_hour >= classes[i].time && tm.tm_hour < classes[i].time+2) || (tm.tm_hour == classes[i].time-1 && tm.tm_min >= 15) )) {
			p_classes[p_classesn++] = &classes[i];
			if (p_classesn == 2) break;
		}
	}

	if (p_classesn == 1) {
		s_class = p_classes[0];
	} else {
		char c;
		printf("1. %s (%02d:00)\n2. %s (%02d:00)\n3. CANCELAR\n\n> ",
				p_classes[0]->codigo_disciplina, p_classes[0]->time,
				p_classes[1]->codigo_disciplina, p_classes[1]->time);

		c = getchar();
		switch (c) {
			default:
			case '1':
				s_class = p_classes[0];
				break;
			case '2':
				s_class = p_classes[1];
				break;
			case '3':
				s_class = NULL;
		}
	}

	if (s_class) {
		char link[84], cmd[95];

		snprintf(link, 84, "zoommtg://zoom.us/join?confno=%s&pwd=%s&zc=0", s_class->meeting_id, s_class->meeting_pass);
		printf("Aula %s (%02d:00), zoom link: %s\nDeseja abrir o Zoom? [Y/n] ", s_class->codigo_disciplina, s_class->time, link);

		if (getchar() != 'n') {

			printf("Abrindo Zoom...\n");

#ifdef __linux__
			snprintf(cmd, 95, "xdg-open \"%s\"", link);
#elif _WIN32
			snprintf(cmd, 95, "start \"\" \"%s\"", link);
#else
			fprintf(stderr, "ERRO: Sistema Operacional não reconhecido/suportado!\n");
			exit(EXIT_FAILURE);
#endif


#ifndef DEBUG
			system(cmd);
#else
			printf("$ %s\n", cmd);
#endif
		}

	} else {
		printf("Nenhuma aula selecionada.\n");
	}

	return 0;
}
