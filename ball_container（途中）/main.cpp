﻿//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib/random.hpp"
#include "headers\macros.hpp"
#include <vector>



struct Ball{
	float x;
	float y;
	float r;
	float speed_x;
	float speed_y;
	Color color;
};

Ball Init(Random& random, AppEnv& env)
{
	Ball temp;

	temp.x = env.mousePosition().x();
	temp.y = env.mousePosition().y();
	temp.r = 10;
	temp.speed_x = random.fromFirstToLast(-5.0f, 5.0f);
	temp.speed_y = random.fromFirstToLast(-5.0f, 5.0f);
	temp.color.green() = random.fromFirstToLast(0.0f, 1.0f);
	temp.color.blue() = random.fromFirstToLast(0.0f, 1.0f);

	return temp;
}


void Ball_Move(Ball& temp)
{
	temp.x += temp.speed_x;
	temp.y += temp.speed_y;
}

void Ball_Bound(Ball& temp)
{
	const int sign = -1;

	if ((temp.x >= WIDTH / 2) || (temp.x <= -WIDTH / 2))
	{
		temp.speed_x *= sign;
	}
	if ((temp.y >= HEIGHT / 2) || (temp.y <= -HEIGHT / 2))
	{
		temp.speed_y *= sign;
		if (temp.y <= -HEIGHT / 2)
		{
			temp.y = -HEIGHT / 2 + temp.r;
		}
	}
}

void Ball_Gravity(Ball& temp, AppEnv& env)
{
	if (env.isPressKey('G'))
	{
		temp.speed_y -= 1;
	}
}

void Ball_Draw(Ball& temp)
{
	drawFillCircle(temp.x, temp.y, temp.r, temp.r, 100, temp.color);
}
// 
// メインプログラム
// 
int main() {
	AppEnv env(Window::WIDTH, Window::HEIGHT, false, false);

	Random random;
	Ball temp;
	std::vector<Ball> ball;
	while (env.isOpen()) {

		//生成処理
		if (env.isPushButton(Mouse::LEFT)) {
			ball.push_back(Init(random, env));

		}

		for (auto& it : ball) {
			//移動処理
			Ball_Move(it);

			//反転処理
			Ball_Bound(it);

			//重力処理
			Ball_Gravity(it, env);
		}

		env.setupDraw();

		for (auto& it : ball) {
			//描画処理
			Ball_Draw(it);
		}

		env.update();
	}
}
