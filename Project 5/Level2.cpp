#include "Level2.h"
#define LEVEL2_WIDTH 14
#define LEVEL2_HEIGHT 8
#define ENEMY_COUNT 3
#define FIRE_COUNT 3

unsigned int level2_data[] =
{
3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 4,
3, 0, 0, 0, 1, 2, 1, 0, 0, 1, 2, 1, 0, 4,
3, 1, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 4,
3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4
};

void Level2::Initialize() {
	state.nextScene = -1;
	state.start = false;

	GLuint mapTextureID = Util::LoadTexture("tileset.png");
	state.map = new Map(LEVEL2_WIDTH, LEVEL2_HEIGHT, level2_data, mapTextureID, 1.0f, 5, 1);

	// Initialize Game Objects

// Initializes the player Arle (The girl with orange hair and the blue and white clothing)
	state.player = new Entity();
	state.player->entityType = PLAYER;
	state.player->direction = RIGHT;
	state.player->position = glm::vec3(2.0f, -3.0f, 0);
	state.player->acceleration = glm::vec3(0, -9.81f, 0);
	state.player->textureID = Util::LoadTexture("Player.png");
	state.player->height = 2.0f;
	state.player->width = 0.9f;
	state.player->isActive = true;

	// Initializes enemies
	state.enemy = new Entity[ENEMY_COUNT];
	//Creating Onion Pixy (The onion creature with a bat)
	state.enemy[0].textureID = Util::LoadTexture("Enemy1.png");
	// Creating Draco (The girl with green hair and red clothes)
	state.enemy[1].textureID = Util::LoadTexture("Enemy2.png");
	// Creating Witch (The character with dark clothes and riding the broomstick)
	state.enemy[2].textureID = Util::LoadTexture("Enemy3.png");
	state.enemy[0].position = glm::vec3(-3.5f, -1.2f, 0.0f);
	state.enemy[1].position = glm::vec3(9.5f, -3.0f, 0.0f);
	state.enemy[1].acceleration = glm::vec3(0.0f, -9.81f, 0.0f);
	state.enemy[2].position = glm::vec3(6.0f, -4.0f, 0.0f);
	state.enemy[0].aiType = RUNNER;
	state.enemy[1].aiType = JUMPER;
	state.enemy[2].aiType = FLYING;
	state.enemy[1].height = 1.8f;
	state.enemy[1].width = 0.8f;
	state.enemy[1].height = 1.8f;
	state.enemy[1].width = 0.8f;
	state.enemy[2].height = 1.8f;
	state.enemy[2].width = 0.8f;

	state.enemy[0].isActive = false;
	state.enemy[1].isActive = false;
	state.enemy[2].isActive = true;

	for (int i = 0; i < ENEMY_COUNT; i++) {
		state.enemy[i].entityType = ENEMY;
	}

	state.fire = new Entity[FIRE_COUNT];

	//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	//music = Mix_LoadMUS("Adventures in Inferno - 11 - Closed World (192  kbps).mp3");

	//Mix_PlayMusic(music, -1);
}

void Level2::Update(float deltaTime) {
	state.player->Update(deltaTime, state.map, state.enemy, ENEMY_COUNT);
	if (state.player->position.x >= 12.5f) {
		state.nextScene = 3;
	}

	state.enemy[2].Update(deltaTime, state.map, state.fire, FIRE_COUNT);

}
void Level2::Render(ShaderProgram* program) {
	state.map->Render(program);
	state.player->Render(program);
	state.enemy[2].Render(program);
}
