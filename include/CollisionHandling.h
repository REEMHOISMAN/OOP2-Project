#pragma once
#include "GameObject/GameObject.h"

void initCollisionFunctions();
void playerObstacle(GameObject&, GameObject&);
void enemyObstacle(GameObject&, GameObject&);
void pizzaEnemyFloor(GameObject&, GameObject&);
void PlayerStaticBomb(GameObject&, GameObject&);
void PlayerHeart(GameObject&, GameObject&);
void PlayerCoins(GameObject&, GameObject&);
void saltBombObstacle(GameObject&, GameObject&);
void cheeseBulletObstacle(GameObject&, GameObject&);
void playerCheeseBullet(GameObject&, GameObject&);
void enemySaltBomb(GameObject&, GameObject&);