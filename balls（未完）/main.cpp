//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib/random.hpp"

enum Window {
	WIDTH = 512,
	HEIGHT = 512
};


enum { Balls_random = 5 };
Random random;

struct Balls{
	Vec2f pos;
	Vec2f speed;
	Color color;
	float width;
	float height ;

}balls[Balls_random];

//ボールの跳ね返り関数
void Balls_return(AppEnv& env)
{
	

		for (int i = 0; i < Balls_random; ++i) {

			balls[i].height = 15;
			balls[i].width = 15;

			if (env.isPressKey('G'))
			{
				balls[i].speed.y() += -1;
			}

			if (balls[i].pos.y() + balls[i].height  < -HEIGHT / 2){
				balls[i].pos.y() = -HEIGHT / 2 + balls[i].height;
			}


			
			//// ボールの位置を更新
			balls[i].pos.x() += balls[i].speed.x();
				balls[i].pos.y() += balls[i].speed.y();

			

			if (balls[i].pos.x() >= WIDTH / 2)
			{
				balls[i].speed.x() *= -1;
			}

			if (balls[i].pos.x() <= -WIDTH / 2)
			{
				balls[i].speed.x() *= -1;
			}

			if (balls[i].pos.y() >= HEIGHT / 2)
			{
				balls[i].speed.y() *= -1;
			}

			if (balls[i].pos.y() <= -HEIGHT / 2)
			{
				balls[i].speed.y() *= -1;
			}


		}
		
}
//ボール動き初期化
void Balls_Move(){
	for (int i = 0; i < Balls_random; ++i){
		balls[i].pos.x() = random.fromFirstToLast(-WIDTH / 2, WIDTH / 2);
		balls[i].pos.y() = random.fromFirstToLast(-HEIGHT / 2, HEIGHT / 2);

		balls[i].speed.x() = random.fromFirstToLast(-5.0f, 5.0f);
		balls[i].speed.y() = random.fromFirstToLast(-5.0f, 5.0f);

		balls[i].color.red() = random.fromFirstToLast(0.25f, 1.0f);
		balls[i].color.green() = random.fromFirstToLast(0.25f, 1.0f);
		balls[i].color.blue() = random.fromFirstToLast(0.25f, 1.0f);
	}
}




// 
// メインプログラム
// 
int main() {
	AppEnv env(Window::WIDTH, Window::HEIGHT, false, false);

	Balls_Move();


	while (env.isOpen()) {
		if (env.isPushKey(GLFW_KEY_ESCAPE)) return 0;

	
		Balls_return(env);
		env.setupDraw();
			// 表示
		for (int i = 0; i < Balls_random; ++i){
			drawFillCircle(balls[i].pos.x(), balls[i].pos.y(),
				balls[i].width, balls[i].height,
				10,
				balls[i].color);
		}

			
		
		env.update();
	}
}
