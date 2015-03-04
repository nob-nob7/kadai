﻿//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib/random.hpp"

enum Window {
	WIDTH = 512,
	HEIGHT = 512
};

enum { BALL_MAX = 10 };

struct Ball{
	bool active;
	float x;
	float y;
	float r;
	float speed_x;
	float speed_y;
	Color color;
}ball[BALL_MAX];


//初期化
void Init(Random& random){
	for (int i = 0; i < BALL_MAX; ++i){
		ball[i].active = false;
		ball[i].x = 0;
		ball[i].y = 0;
		ball[i].r = 10;
		ball[i].speed_x = random.fromFirstToLast(-4.0f, 4.0f);
		ball[i].speed_y = random.fromFirstToLast(-4.0f, 4.0f);

	}
}

void Ball_create(AppEnv& env, Random& random)
{
	//生成処理
	if (env.isPushButton(Mouse::LEFT)){
		for (int i = 0; i < BALL_MAX; ++i)
		{
			if (!ball[i].active)
			{
				ball[i].active = true;

				ball[i].x = env.mousePosition().x();
				ball[i].y = env.mousePosition().y();

				ball[i].color = Color(random.fromFirstToLast(0.0f, 1.0f), random.fromFirstToLast(0.0f, 1.0f), random.fromFirstToLast(0.0f, 1.0f));
				break;
			}
		}
	}
}

void Ball_Draw()
{
	for (int i = 0; i < BALL_MAX; ++i)
	{
		if (ball[i].active){
			drawFillCircle(ball[i].x, ball[i].y, ball[i].r, ball[i].r, 100, ball[i].color);
		}
	}
}

void Ball_Move()
{
	for (int i = 0; i < BALL_MAX; ++i){
		if (ball[i].active){
			ball[i].x += ball[i].speed_x;
			ball[i].y += ball[i].speed_y;
		}
	}
}

void Bound(int sign)
{
	for (int i = 0; i < BALL_MAX; ++i)
	{
		if (ball[i].active)
		{
			if ((ball[i].x >= WIDTH / 2) || (ball[i].x <= -WIDTH / 2)){
				ball[i].speed_x *= sign;
			}

			if ((ball[i].y >= HEIGHT / 2) || (ball[i].y <= -HEIGHT / 2)){
				ball[i].speed_y *= sign;
			}

		}

	}
}
// 
// メインプログラム
// 
int main() {
	AppEnv env(Window::WIDTH, Window::HEIGHT, false, false);
	Random random;
	Init(random);

	int sign = -1;
	while (env.isOpen()) {
		//生成処理
		Ball_create(env, random);

		//移動処理
		Ball_Move();

		//バウンド処理
		Bound(sign);

		env.setupDraw();

		//描画処理
		Ball_Draw();
		env.update();
	}
}
