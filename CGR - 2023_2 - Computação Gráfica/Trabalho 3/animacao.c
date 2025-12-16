#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define BOID_COUNT 500  // Número de boids (pássaros)

clock_t startTime;  // Variável para armazenar o tempo de início

typedef struct {
    float x, y;  // Posição do boid
    float vx, vy;  // Velocidade do boid
} Boid;

typedef struct {
    float x, y;  // Posição do predador
    float vx;  // Velocidade do predador
} Predator;

Predator predator;

Boid boids[BOID_COUNT];

// Coordenadas do alvo para Seek (Buscar)
float seekTargetX = 0.5f;
float seekTargetY = 0.5f;

// Coordenadas do alvo para Flee (Fugir)
float fleeTargetX = 0.5f;
float fleeTargetY = 0.5f;


void initBoids() {
	int i;
    for (i = 0; i < BOID_COUNT; i++) {
        boids[i].x = (float)(rand() % 1000) / 1000.0f;
        boids[i].y = (float)(rand() % 1000) / 1000.0f;
        boids[i].vx = 0.001f;
        boids[i].vy = 0.0f;
    }
}

// Comportamento de Seek (Buscar)
void seekBehavior() {
	int i;
    for (i = 0; i < BOID_COUNT; i++) {
        float maxSpeed = 0.001f;

        float desiredVx = seekTargetX - boids[i].x;
        float desiredVy = seekTargetY - boids[i].y;

        float distance = sqrt(desiredVx * desiredVx + desiredVy * desiredVy);

        desiredVx /= distance;
        desiredVy /= distance;

        boids[i].vx = desiredVx * maxSpeed;
        boids[i].vy = desiredVy * maxSpeed;

        // Atualize a posição baseada na velocidade
        boids[i].x += boids[i].vx;
        boids[i].y += boids[i].vy;
    }
}

// Comportamento de Flee (Fugir)
void fleeBehavior() {
	int i;
    for (i = 0; i < BOID_COUNT; i++) {
        float maxSpeed = 0.001f;

        float desiredVx = boids[i].x - fleeTargetX;
        float desiredVy = boids[i].y - fleeTargetY;

        float distance = sqrt(desiredVx * desiredVx + desiredVy * desiredVy);

        desiredVx /= distance;
        desiredVy /= distance;

        boids[i].vx = desiredVx * maxSpeed;
        boids[i].vy = desiredVy * maxSpeed;

        // Atualize a posição baseada na velocidade
        boids[i].x += boids[i].vx;
        boids[i].y += boids[i].vy;
    }
}

// Comportamento de Cardume (Flock)
void flockBehavior() {
    float cohesionFactor = 0.005f;  // Fator de coesão
	int i;
    for (i = 0; i < BOID_COUNT; i++) {
        float averageX = 0.0f;
        float averageY = 0.0f;
        int count = 0;
		int j;
        for (j = 0; j < BOID_COUNT; j++) {
            if (j != i) {
                float dx = boids[j].x - boids[i].x;
                float dy = boids[j].y - boids[i].y;
                float distance = sqrt(dx * dx + dy * dy);

                // Se o boid estiver dentro do raio de coesão, adicione sua posição à média
                if (distance < 0.1f) {
                    averageX += boids[j].x;
                    averageY += boids[j].y;
                    count++;
                }
            }
        }

        if (count > 0) {
            averageX /= count;
            averageY /= count;

            // Calcula a direção para a média das posições dos boids vizinhos
            float directionX = averageX - boids[i].x;
            float directionY = averageY - boids[i].y;

            // Aplica a direção com um fator de coesão
            boids[i].vx += directionX * cohesionFactor;
            boids[i].vy += directionY * cohesionFactor;

            // Atualiza a posição baseada na velocidade
            boids[i].x += boids[i].vx;
            boids[i].y += boids[i].vy;
        }
    }
}

void initPredator() {
	float PREDATOR_SPEED = 0.01f;
    predator.x = 0.1f;  // Posição inicial do predador
    predator.y = 0.5f;  // Posição inicial do predador
    predator.vx = PREDATOR_SPEED;
}

void updatePredator() {
	float PREDATOR_SPEED = 0.005f;
    predator.x += predator.vx;

    // Verifica se o predador atingiu a borda direita
    if (predator.x > 1.0f) {
        predator.x = 1.0f;
        predator.vx = -PREDATOR_SPEED;
    }

    // Verifica se o predador atingiu a borda esquerda
    if (predator.x < 0.0f) {
        predator.x = 0.0f;
        predator.vx = PREDATOR_SPEED;
    }
}

void updateBoidsPredator() {
	float BOID_SPEED = 0.005f;
	int i;
    for (i = 0; i < BOID_COUNT; i++) {
        // Calcula a direção para longe do predador
        float directionX = boids[i].x - predator.x;
        float directionY = boids[i].y - predator.y;

        // Normaliza a direção
        float distance = sqrt(directionX * directionX + directionY * directionY);
        directionX /= distance;
        directionY /= distance;

        // Atualiza a posição do boid com base na direção e velocidade
        boids[i].x += directionX * BOID_SPEED;
        boids[i].y += directionY * BOID_SPEED;
    }
}

void updateBoidsObstacle() {
	int i;
    for (i = 0; i < BOID_COUNT; i++) {
        // Atualiza a posição do boid com base na direção e velocidade
        boids[i].x += boids[i].vx;
        boids[i].y += boids[i].vy;
    }
}

void avoidObstacle() {
	float OBSTACLE_RADIUS = 0.1f;  // Raio do obstáculo
	float OBSTACLE_X = 0.5f;  // Coordenada X do obstáculo
	float OBSTACLE_Y = 0.5f;  // Coordenada Y do obstáculo
	float BOID_SPEED = 0.005f;
	int i;
    for (i = 0; i < BOID_COUNT; i++) {
        float obstacleDirectionX = boids[i].x - OBSTACLE_X;
        float obstacleDirectionY = boids[i].y - OBSTACLE_Y;

        float distanceToObstacle = sqrt(obstacleDirectionX * obstacleDirectionX + obstacleDirectionY * obstacleDirectionY);

        // Se o boid estiver muito próximo do obstáculo, muda de direção
        if (distanceToObstacle < OBSTACLE_RADIUS) {
            // Normaliza a direção
            obstacleDirectionX /= distanceToObstacle;
            obstacleDirectionY /= distanceToObstacle;

            // Atualiza a posição do boid com base na direção e velocidade
            //boids[i].vx = obstacleDirectionX * BOID_SPEED;
            boids[i].vy = obstacleDirectionY * BOID_SPEED;
        }
    }
}

void migrate() {
	float MIGRATION_TARGET_X = 1.2f;  // Coordenada X do ponto de migração
	float MIGRATION_TARGET_Y = 0.5f;  // Coordenada Y do ponto de migração
	float MIGRATION_FORCE = 0.0005f;  // Força de migração
	int i;
    for (i = 0; i < BOID_COUNT; i++) {
        // Calcula a direção da migração
        float migrationDirectionX = MIGRATION_TARGET_X - boids[i].x;
        float migrationDirectionY = MIGRATION_TARGET_Y - boids[i].y;

        // Normaliza a direção
        float distanceToMigration = sqrt(migrationDirectionX * migrationDirectionX + migrationDirectionY * migrationDirectionY);
        migrationDirectionX /= distanceToMigration;
        migrationDirectionY /= distanceToMigration;

        // Atualiza a posição do boid com base na direção e velocidade de migração
        boids[i].x += migrationDirectionX * MIGRATION_FORCE;
        boids[i].y += migrationDirectionY * MIGRATION_FORCE;
    }
}

void drawBoids() {
	float OBSTACLE_X = 0.5f;  // Coordenada X do obstáculo
	float OBSTACLE_Y = 0.5f;  // Coordenada Y do obstáculo
	float OBSTACLE_RADIUS = 0.05f;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 1.0f);  // Cor azul para os boids
    glPointSize(5.0f);

    glBegin(GL_POINTS);
    int i;
    for (i = 0; i < BOID_COUNT; i++) {
        glVertex2f(boids[i].x, boids[i].y);
    }
    glEnd();
    
    // Desenha o obstáculo como um círculo preenchido
    /**/
    glColor3f(1.0f, 0.0f, 0.0f);  // Cor vermelha para o obstáculo
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(OBSTACLE_X, OBSTACLE_Y);
    for (i = 0; i <= 360; i++) {
        float angle = (float)i * 3.1415926f / 180.0f;
        glVertex2f(OBSTACLE_X + OBSTACLE_RADIUS * cos(angle), OBSTACLE_Y + OBSTACLE_RADIUS * sin(angle));
    }
    glEnd();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void update(int value) {
	int i;
	clock_t currentTime = clock();
    double elapsedTime = (double)(currentTime - startTime) / CLOCKS_PER_SEC;
	// Alterne entre os comportamentos descomentando a função correspondente
	
    //seekBehavior();
    //fleeBehavior();
	//flockBehavior();
	
	//updateBoidsPredator();
	//updatePredator();//->mexer no main também
	
	/**/
	for (i = 0; i < BOID_COUNT; i++) {
	    boids[i].vx = 0.0f;
	    boids[i].vy = 0.0f;
	}
	migrate();//->só para migrate, usar com avoidObstacle e updateBoidObstacle
	
    avoidObstacle();
    updateBoidsObstacle(); //-> mexer em initBoids
	
	
    int boidsOutsideCount = 0;  // Contador para boids fora da cena

    // Verifica quantos boids estão fora da cena e reinicia suas posições
    for (i = 0; i < BOID_COUNT; i++) {
        if (boids[i].x < 0 || boids[i].x > 1 || boids[i].y < 0 || boids[i].y > 1) {
            // O boid saiu dos limites, incrementa o contador
            boidsOutsideCount++;
            /*
            boids[i].x = (float)(rand() % 1000) / 1000.0f;
            boids[i].y = (float)(rand() % 1000) / 1000.0f;
			*/
        }
    }
    
    // Verifica se passou um determinado tempo (por exemplo, 5 segundos) para reiniciar
    if (elapsedTime >= 10.0) {  // Reinicia após 5 segundos
        // Reinicia a cena reinicializando as posições dos boids
        initBoids();
        startTime = clock();  // Reseta o tempo de início
    }

    // Verifica se todos os boids estão fora da cena antes de chamar novamente
    if (boidsOutsideCount == BOID_COUNT) {
    	for (i = 0; i < BOID_COUNT; i++) {
	        if (boids[i].x < 0 || boids[i].x > 1 || boids[i].y < 0 || boids[i].y > 1) {
	            // O boid saiu dos limites, incrementa o contador
	            boids[i].x = (float)(rand() % 1000) / 1000.0f;
            	boids[i].y = (float)(rand() % 1000) / 1000.0f;
	        }
	    }
	}
	    
        glutTimerFunc(16, update, 0); // 60 FPS (1000ms / 60 = 16.6667 -> 16)

    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Boids Behaviors");

    glutDisplayFunc(drawBoids);
    glutReshapeFunc(reshape);
    initBoids();
    //initPredator();
    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}

