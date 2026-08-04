//Kauan Henrique Werlich

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>

#define random rand
#define srandom srand

/* Obtem o tempo corrente em msec.*/
unsigned long get_time_msec(void)
{
     struct timeval tv;
     unsigned long time_msec;

     int rc = gettimeofday(&tv, NULL);
     if (rc != 0) {
	  perror("erro em gettimeofday()");
	  exit(1);
     }
     time_msec = 1000L*tv.tv_sec + tv.tv_usec/1000;
     return time_msec;
}

/* Dorme um numero aleatorio de msec, seguindo uma distribuicao
 * exponencial. O parametro t é o tempo médio da distribuicao.
 * O valor de retorno e' o tempo de sleep, em msec.*/
unsigned long exp_msleep(int t)
{
     unsigned long sleep_time;
     float rnd;
     static int init = 0;

     if (!init) {
	  init = 1;
	  srandom(time(NULL));
     }
     rnd = (1.0f * random())/RAND_MAX;
     sleep_time = (unsigned long) round(-t * logf(1.0f - rnd));
     usleep(sleep_time * 1000);
     return sleep_time;
}

int main (int argc, char *argv[ ]) {
	int tcheg = atoi(argv[1]);
	int tserv = atoi(argv[2]);
	int nreq = atoi(argv[3]);
	int nserv = atoi(argv[4]);
	int maxreqs = atoi(argv[5]);
	/*
	int req;
	for (req = 1; req <= nreq; req++) {
		exp_msleep(tcheg);
		se (houver_lugar_na_fila)
			enfileira_requisicao(req);
	}

	while (ha_requisicoes_a_processar) {
		desenfileira_requisicao();
		exp_msleep(tserv); // simula processamento 
		atualiza_estatisticas();
	}
	*/
	
	printf("$ %s %s %s %s %s %s\n", argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
	printf("tempo medio de residencia=%.3f ms", tmedres);
	printf("tempo medio de espera=%.3f ms", tmedesp);
	printf("vazao=%.2f req/s", vazao);
	printf("indice de rejeicao=%.2f%", indrej);

	
	return 0;
}
